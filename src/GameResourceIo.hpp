#pragma once
#include <cstdint>
namespace th20 {
// Archive mode zero has no loose-file fallback; other modes use local HANDLEs.
// Original ownership/failure contracts are retained and documented separately.
std::uint8_t* read_game_resource(const char*, std::int32_t*, std::int32_t);
}
