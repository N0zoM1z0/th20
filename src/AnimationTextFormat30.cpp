#include "AnimationTextFormat.hpp"
#include "SecureCrt.hpp"
namespace th20 {
void __cdecl format_text_447940(char* output, const char* pattern, std::va_list args) {
    vsprintf_s(output,0x500,pattern,args);
}
}
