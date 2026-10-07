#include "EclRuntime.hpp"
#include <cstring>

namespace th20 {

std::int32_t EclLoader::subroutine_index(const char* name) {
    std::int32_t first = 0;
    std::int32_t last = static_cast<std::int32_t>(subroutine_count - 1);
    while (first <= last) {
        auto middle = (last - first) / 2 + first;
        auto& table = records;
        auto order = std::strcmp(name, table[static_cast<std::size_t>(middle)].name);
        if (order == 0) return middle;
        else if (order < 0) last = middle - 1;
        else first = middle + 1;
    }
    return -1;
}

void EclManager::reset() {
    main.time = 0.0f;
    main.position.offset = -1;
    main.position.subroutine = -1;
    main.async_id = -1;
    main.manager = this;
    main.flags.bits &= ~1u;
    main.signal = 0;
    main.interpolators.clear();
    current_runtime = &main;
    main.stack.reset();
    auto& list = runtimes;
    list.initialize(&main);
}

int EclLoader::select(EclManager* manager, const char* name) {
    manager->set_loader(this);
    manager->select_subroutine(name);
    manager->set_offset(0);
    manager->set_time(0.0f);
    return 0;
}

void EclManager::set_loader(EclLoader* value) { loader = value; }
void EclManager::select_subroutine(const char* name) {
    auto& source = *loader;
    auto index = source.subroutine_index(name);
    current_runtime->position.subroutine = index;
}
void EclManager::set_offset(std::int32_t value) { current_runtime->position.offset = value; }
void EclManager::set_time(float value) { current_runtime->time = value; }

} // namespace th20
