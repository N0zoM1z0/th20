#pragma once
#include <cstdint>
#include <string_view>
namespace th20 {
struct Vector3;
// Real process AsciiInf renderer at 0x005C0698. The three tiny native
// setters are owned here, while the substantial text/number/format draw
// methods retain their independently observed ABI and unaccepted sources.
// This borrowed view adds no storage and does not instantiate a replacement
// AsciiInf class.
struct NativeCardAsciiDrawView {
    void set_font_488b00(std::int32_t value);
    void set_layer_488a00(std::int32_t value);
    void set_color_alpha_488940(std::uint8_t value);
    void render_number_46cd40(const Vector3& position,std::uint32_t value,std::int32_t precision,char pad);
    void render_text_46ce90(const Vector3& position,std::string_view text);
    // Variadic member functions use x86 __cdecl: receiver is the LAST
    // outgoing argument, as in the genuine 797B Card Draw source.
    void __cdecl render_format_46c990(const Vector3& position,const char* format,...);
};
}
