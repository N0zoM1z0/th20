#include "TaskInfo.hpp"

namespace th20 {

TaskInfo::~TaskInfo() {
}

void TaskInfo::enable() {
    enable_callbacks();
}

void TaskInfo::disable() {
    disable_callbacks();
}

void TaskInfo::enable_callbacks() {
    if (update_node) update_node->enable();
    if (draw_node) draw_node->enable();
}

void TaskInfo::disable_callbacks() {
    if (update_node) update_node->disable();
    if (draw_node) draw_node->disable();
}

} // namespace th20
