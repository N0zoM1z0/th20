#include "EclFileLoader.hpp"
#include "EnemyController.hpp"
#include "Context.hpp"
#include "EclDiagnostic.hpp"

namespace th20 {

EclFileLoader::EclFileLoader() : player_index(0), context(nullptr) {}

std::int32_t EclFileLoader::load(const char* path) {
    for (auto& name : context->enemy_controller()->loaded_names) {
        if (name == path) {
            ecl_diagnostic_hint(ecl_duplicate_file_format, path);
            return -1;
        }
    }
    context->enemy_controller()->loaded_names.emplace_back(std::pmr::string(path));
    std::uint8_t* data = nullptr;
    for (auto& record : process_ecl_cache) {
        if (record.second == path) {
            data = record.first;
            ecl_diagnostic_hint(ecl_cached_file_format, path);
            break;
        }
    }
    if (!data) {
        data = read_game_resource(ecl_resource_path(path), nullptr, 0);
        process_ecl_cache.emplace_back(EclCachedFile(data, path));
    }
    if (append(data) < 0) {
        return -1;
    }
    return 0;
}

} // namespace th20
