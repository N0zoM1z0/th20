#include "TaskInfo.hpp"

namespace th20 {
TaskInfo::TaskInfo() noexcept : flag_word{}, update_node(nullptr), draw_node(nullptr) {
    flag_word.bits |= 2u;
}
}
