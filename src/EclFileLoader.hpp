#pragma once

#include "EclRuntime.hpp"
#include "GameResourceIo.hpp"
#include <list>
#include <utility>

namespace th20 {
struct Context;

// The process cache owns the filename strings and retains resource buffers.
// Explicit buffer release and process cache startup remain under reconstruction.
using EclCachedFile = std::pair<std::uint8_t*, std::pmr::string>;
extern std::pmr::list<EclCachedFile> process_ecl_cache;
extern const char ecl_duplicate_file_format[], ecl_cached_file_format[];

// Resource-path construction and process archive startup remain dependencies.
// The resource reader is shared with the actual archive/file protocol.
const char* ecl_resource_path(const char* filename);

class EclFileLoader : public EclLoader {
public:
    std::int32_t player_index;
    Context* context;

    EclFileLoader();
    ~EclFileLoader() override = default;
    std::int32_t load(const char* path) override;
    std::int32_t include_resources(std::uint8_t* block) override;
    void bind_player(std::int32_t index);
};

#if defined(_M_IX86)
static_assert(sizeof(EclCachedFile) == 32);
static_assert(sizeof(std::pmr::list<EclCachedFile>) == 12);
static_assert(sizeof(EclFileLoader) == 572);
static_assert(offsetof(EclFileLoader, player_index) == 564);
static_assert(offsetof(EclFileLoader, context) == 568);
#endif
}
