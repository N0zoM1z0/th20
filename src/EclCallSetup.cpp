#include "EclRuntime.hpp"
namespace th20 {
int EclLoader::activate(EclManager* manager, const char* name) {
    manager->set_loader(this);
    manager->select_subroutine(name);
    manager->set_offset(0);
    manager->set_time(0.0f);
    return manager->current_instruction() == nullptr ? 1 : 0;
}
EclLoader* EclManager::loader_value() const { return loader; }
EclInstruction* EclManager::current_instruction() { return current_runtime->current(); }
std::int32_t ScriptStack::pointer_value() const { return pointer; }
void ScriptStack::set_pointer(std::int32_t value) { pointer = value; }
std::int32_t ScriptStack::frame_value() const { return frame_base; }
}
