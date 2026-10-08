#include "Worker.hpp"
#include <cassert>
#include <chrono>
#include <cstring>
#include <future>
#include <type_traits>

namespace th20 { LockRegistry process_locks; }

// Observe only quiescent owned storage, after all flag writers have returned.
// Native x86 puts atomic<bool> after jthread12; the host thread size differs.
static bool closing(const th20::Worker& worker) {
    static_assert(std::is_standard_layout_v<th20::Worker>);
    static_assert(alignof(std::atomic<bool>) == 1);
    unsigned char value;
    const auto* bytes = reinterpret_cast<const unsigned char*>(&worker);
    std::memcpy(&value, bytes + sizeof(std::jthread), 1);
    return value != 0;
}

struct Task {
    std::promise<void> entered;
    std::promise<void> release;
    std::promise<void> finished;
    std::atomic<unsigned> executions{0};
};

static std::int32_t execute(void* argument) {
    auto& task = *static_cast<Task*>(argument);
    ++task.executions;
    task.entered.set_value();
    task.release.get_future().get();
    task.finished.set_value_at_thread_exit();
    return -17;
}

static void start(th20::Worker& worker, Task& task) {
    void* argument = &task;
    worker.start(execute, argument);
    task.entered.get_future().get();
    assert(task.executions == 1 && !closing(worker));
}

struct Receiver {
    std::atomic<unsigned> first_calls{0}, second_calls{0};
    void first(void* argument) { ++first_calls; execute(argument); }
    void second(void* argument) { ++second_calls; execute(argument); }
};

static void member_tasks() {
    using namespace std::chrono_literals;
    Receiver receiver, other;
    Task old_task, new_task;
    auto old_entered=old_task.entered.get_future();
    auto old_done=old_task.finished.get_future();
    auto new_entered=new_task.entered.get_future();
    auto new_done=new_task.finished.get_future();
    th20::Worker worker;
    Receiver* owner=&receiver;
    auto operation=&Receiver::first;
    void* argument=&old_task;
    worker.start(owner, operation, argument);
    owner=&other;
    operation=&Receiver::second;
    argument=&new_task;
    old_entered.get();
    assert(receiver.first_calls==1 && other.first_calls==0);
    worker.start(&receiver, operation, argument);
    new_entered.get();
    assert(receiver.second_calls==1 && !closing(worker));
    assert(old_done.wait_for(0ms)==std::future_status::timeout);
    new_task.release.set_value();
    worker.close_and_join();
    new_done.get();
    assert(old_done.wait_for(0ms)==std::future_status::timeout);
    old_task.release.set_value();
    old_done.get();

    // The callable owns values even before thread decay/capture takes place.
    Task direct;
    owner=&receiver;
    operation=&Receiver::first;
    argument=&direct;
    th20::Worker::MemberTask<Receiver, decltype(operation), void*> bound(owner, operation, argument);
    owner=&other;
    operation=&Receiver::second;
    argument=nullptr;
    direct.release.set_value();
    bound();
    assert(direct.executions==1 && receiver.first_calls==2 && other.second_calls==0);
}

int main() {
    using namespace std::chrono_literals;
    member_tasks();
    {
        th20::Worker worker;
        assert(!closing(worker));
        worker.detach();
        assert(!closing(worker));
        worker.close_and_join();
        worker.close_and_join();
        assert(closing(worker));
        worker.close_and_detach();
        assert(closing(worker));
    }
    {
        Task task;
        th20::Worker worker;
        worker.close_and_join();
        assert(closing(worker));
        start(worker, task);
        auto joined = std::async(std::launch::async, [&] { worker.close_and_join(); });
        assert(joined.wait_for(10ms) == std::future_status::timeout);
        task.release.set_value();
        joined.get();
        assert(closing(worker) && task.executions == 1);
        worker.close_and_join();
    }
    {
        Task task;
        auto done = task.finished.get_future();
        {
            th20::Worker worker;
            start(worker, task);
            worker.detach();
            assert(!closing(worker) && done.wait_for(0ms) == std::future_status::timeout);
        }
        // Detached task outlives Worker, but owns no pointer into its storage.
        assert(done.wait_for(0ms) == std::future_status::timeout);
        task.release.set_value();
        done.get();
    }
    {
        Task task;
        auto done = task.finished.get_future();
        th20::Worker worker;
        start(worker, task);
        worker.close_and_detach();
        assert(closing(worker) && done.wait_for(0ms) == std::future_status::timeout);
        worker.close_and_join();
        assert(done.wait_for(0ms) == std::future_status::timeout);
        task.release.set_value();
        done.get();
    }
    {
        Task old_task, new_task;
        auto old_done = old_task.finished.get_future();
        th20::Worker worker;
        start(worker, old_task);
        start(worker, new_task);
        assert(old_done.wait_for(0ms) == std::future_status::timeout);
        new_task.release.set_value();
        worker.close_and_join();
        assert(closing(worker) && old_done.wait_for(0ms) == std::future_status::timeout);
        old_task.release.set_value();
        old_done.get();
    }
    {
        Task task;
        auto entered = task.entered.get_future();
        th20::Worker worker;
        auto& mutex = th20::process_locks.slot(6);
        mutex.lock();
        auto launch = std::async(std::launch::async, [&] {
            void* argument = &task;
            worker.start(execute, argument);
        });
        assert(launch.wait_for(10ms) == std::future_status::timeout);
        assert(entered.wait_for(0ms) == std::future_status::timeout);
        mutex.unlock();
        launch.get();
        entered.get();
        assert(!closing(worker));
        task.release.set_value();
        worker.close_and_join();
        assert(closing(worker));
    }
    {
        Task task;
        std::promise<void> entered;
        auto worker_deleted = std::async(std::launch::async, [&] {
            th20::Worker worker;
            start(worker, task);
            entered.set_value();
        });
        entered.get_future().get();
        assert(worker_deleted.wait_for(10ms) == std::future_status::timeout);
        task.release.set_value();
        worker_deleted.get();
    }
}
