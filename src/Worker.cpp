#include "Worker.hpp"

namespace th20 {

Worker::Worker() noexcept : thread_(), close_requested_(false) {
}

Worker::~Worker() { close_and_join(); }

void Worker::close_and_join() {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(6));
    close_requested_ = true;
    if (thread_.joinable()) thread_.join();
}

void Worker::detach() {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(6));
    if (thread_.joinable()) thread_.detach();
}

void Worker::close_and_detach() {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(6));
    close_requested_ = true;
    detach();
}

template void Worker::start<std::int32_t(void*), void*>(
    std::int32_t (&function)(void*), void*& argument);

} // namespace th20
