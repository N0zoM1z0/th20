#include "EclRuntime.hpp"

namespace th20 {

EclLoader::EclLoader()
    : file_count(0), subroutine_count(0), files{}, fields_10c{} {}

EclLoader::~EclLoader() = default;

std::int32_t EclLoader::load(const char*) { return 0; }

std::int32_t EclLoader::include_resources(std::uint8_t*) { return 0; }

} // namespace th20
