#include <cwchar>
#include <cstdarg>
extern "C" int __cdecl _vswprintf_s(wchar_t*,std::size_t,const wchar_t*,va_list);
namespace th20 {
void __cdecl format_text_447940(wchar_t* output, const wchar_t* pattern, va_list args) {
    _vswprintf_s(output,0x500,pattern,args);
}
}
