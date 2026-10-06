#pragma once

#include <atomic>
#include <thread>

namespace th20 {

// REF-003: default jthread followed by the close-request flag at x86 +12.
// Native locked join/detach and destruction remain pending; this declaration
// does not provide a linked worker lifetime implementation.
class Worker {
public:
    Worker() noexcept;
    ~Worker();

    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;

private:
    std::jthread thread_;
    std::atomic<bool> close_requested_;
};

static_assert(sizeof(void*) != 4 || sizeof(std::jthread) == 12);
static_assert(sizeof(void*) != 4 || sizeof(Worker) == 16);

} // namespace th20
