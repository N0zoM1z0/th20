#include "Worker.hpp"

namespace th20 {

Worker::Worker() noexcept : thread_(), close_requested_(false) {
}

} // namespace th20
