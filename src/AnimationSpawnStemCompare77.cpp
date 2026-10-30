#include "NativeAnimationSpawnStem.hpp"
namespace th20 {
bool NativeStemStringView::equals_44b400(const char* requested) const {
    const std::int32_t requested_size=native_stem_strlen_411180(requested);
    const std::int32_t current_size=count_14;
    char* const data=const_cast<NativeStemStorageView*>(&value_04)->myptr_40f2c0();
    return native_stem_equal_len_447200(data,current_size,requested,requested_size);
}
bool __cdecl native_spawn_stem_equals_446de0(const std::pmr::string* stem,
                                               const char* requested) {
    return reinterpret_cast<const NativeStemStringView*>(stem)->equals_44b400(requested);
}
}
