// Original full 73B equality and 34B native byte-compare forward.
#include "NativeAnimationSpawnStem.hpp"
#include <cstring>
namespace th20 {
#include <cstring>
std::int32_t __cdecl native_stem_compare_bytes_44be00(const char* first,const char* second,std::int32_t length) {
    std::int32_t compared=std::memcmp(first,second,static_cast<std::size_t>(length));
    return compared;
}
bool __cdecl native_stem_equal_len_447200(const char* first, std::int32_t first_size,
                                            const char* second, std::int32_t second_size) {
    if (first_size!=second_size) return false;
    if (first_size == 0) return true;
    return native_stem_compare_bytes_44be00(first,second,first_size)==0;
}
}
