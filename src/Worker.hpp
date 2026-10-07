#pragma once

#include <atomic>
#include <thread>
#include "LockRegistry.hpp"

namespace th20 {

// REF-003: default jthread followed by the close-request flag at x86 +12.
// Lifecycle operations serialize through shared recursive mutex slot 6.
// Starting a new task detaches the previous thread before resetting the flag.
class Worker {
public:
    Worker() noexcept;
    ~Worker();

    void close_and_join();
    void detach();
    void close_and_detach();

    template<class Function, class Argument>
    void start(Function& function, Argument& argument) {
        std::lock_guard<std::recursive_mutex> guard(process_locks.slot(6));
        detach();
        close_requested_ = false;
        thread_ = std::jthread(function, argument);
    }

    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;

private:
    std::jthread thread_;
    std::atomic<bool> close_requested_;
};

static_assert(sizeof(void*) != 4 || sizeof(std::jthread) == 12);
static_assert(sizeof(void*) != 4 || sizeof(Worker) == 16);

} // namespace th20
