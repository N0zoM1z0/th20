#pragma once
// Real original AnimationFile stem comparison ABI, with non-owning PMR string
// view at the native 0x20 member offset. Content equals via native 77B
// four-argument length-aware comparison; source spelling is provisional.
#include <cstddef>
#include <cstdint>
#include <string>
#include <memory_resource>
namespace th20 {
std::int32_t __cdecl native_stem_strlen_411180(const char* text);
bool __cdecl native_stem_equal_len_447200(const char* first,std::int32_t first_size,
                                             const char* second,std::int32_t second_size);
struct NativeStemStorageView {
    char* myptr_40f2c0();
};
struct NativeStemStringView {
    char reserved_00[4];
    NativeStemStorageView value_04;
    char reserved_05[15];
    std::int32_t count_14;
    bool equals_44b400(const char* requested) const;
};
static_assert(offsetof(NativeStemStringView,count_14)==0x14);
bool __cdecl native_spawn_stem_equals_446de0(const std::pmr::string* stem,
                                               const char* requested);
}
