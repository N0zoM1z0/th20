// Original 2,227B GDI text generation/upload Boss at 0x00415830.
// SOURCE-PRESENT NONEXACT: all native font, GDI, outline, alpha and
// submission stages are maintained; original compiler/EH and the queued
// functor/task producer have independent source boundaries still open.
// The original 22-pointer font switch and true allocation/color behavior
// are reconstructed. Used horizontal offset mutation and the two-wide-char
// zero initialization now align the first 15 E8 sites and 41/43 in-body
// HIGHLOW fields. The complete COFF contribution is native-sized 2316B,
// including all 22 table entries, but the code return is one byte early.
// This large Boss remains NONEXACT (1566/1956 ordinary byte agreement).
#include "NativeGlyphRenderJob.hpp"
#include "NativeGlyphTextCore.hpp"
#include "NativeGlyphFontResources.hpp"
#include "NativeGlyphTextQueueView.hpp"
#include "NativeGlyphTaskQueue.hpp"
#include "NativeGlyphCanvasView.hpp"
#include "NativeGlyphCanvasStorage.hpp"
#include "LockRegistry.hpp"
#include "DiagnosticAllocator.hpp"
#include <windows.h>
#include <array>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <functional>
#include <mutex>
#include <utility>
namespace th20 {
// Borrowed native font objects, current resource allocation and task queue.
// The matching original absolute-address owners are kept external.
extern bool native_font_extra_padding_5b66ec;
extern float native_font_outline_scale_5ae120;
extern const float native_font_size_56c8d0;
extern const float native_font_size_56c8d4;
extern const float native_font_size_56c8d8;
extern const float native_font_size_56c8dc;
extern const float native_font_size_56c8e0;

// Native original 73B allocator-body owner now has its own canonical
// template instantiation; this large nonexact producer borrows that exact
// executable head instead of a provisional wrapper with the same target.
extern template NativeGlyphCanvasStorage* DiagnosticAllocator::allocate_object<
    NativeGlyphCanvasStorage>(const char*);


// The native 542B canvas alpha processor and 2,245B outline compositor
// are independently accounted for. This Boss invokes those real methods
// rather than replacing their internals with approximations.
std::uint64_t __cdecl native_text_core_415830(
    const NativeTextTransform4* transform, std::int32_t horizontal_offset,
    std::int32_t text_color_word, std::uint32_t outline_color, const char* formatted,
    IDirect3DBaseTexture9* texture, std::int32_t font, std::int32_t align,
    std::int32_t is_special, std::int32_t mode,
    std::function<void()> callback) {
    std::lock_guard<std::recursive_mutex> raster_guard(process_locks.slot(0x12));
    // The original selects an existing native font via array-index helper.
    HFONT selected_font=native_glyph_fonts_5b66f0[font];
    float outline_radius=native_font_size_56c8d0;
    std::int32_t baseline=2;
    auto* canvas=process_allocator->allocate_object<NativeGlyphCanvasStorage>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\grpfont.cpp:920 AflDIB");
    // Original physical switch is directly indexed by font 0..21 (22
    // pointer entries). Distinct 1/2/3, 4/5, 14/15, 16/17 and 20/21
    // cases independently assign BOTH native radius and baseline, even
    // when some values coincide. Only true native aliases are grouped.
    switch (font) {
      case 0: case 7: case 11: default:
        outline_radius=native_font_size_56c8d0; baseline=3; break;
      case 1:
        outline_radius=native_font_size_56c8d0; baseline=3; break;
      case 2:
        outline_radius=native_font_size_56c8d0; baseline=3; break;
      case 3:
        outline_radius=native_font_size_56c8d0; baseline=3; break;
      case 4:
        outline_radius=native_font_size_56c8d4; baseline=3; break;
      case 5:
        outline_radius=native_font_size_56c8d4; baseline=3; break;
      case 6: case 8:
        outline_radius=native_font_size_56c8d8; baseline=3; break;
      case 9:
        outline_radius=native_font_size_56c8dc; baseline=3; break;
      case 10:
        outline_radius=native_font_size_56c8e0; baseline=4; break;
      case 12: case 13:
        outline_radius=native_font_size_56c8d0; baseline=6; break;
      case 14:
        outline_radius=native_font_size_56c8d8; baseline=6; break;
      case 15:
        outline_radius=native_font_size_56c8d8; baseline=6; break;
      case 16:
        outline_radius=native_font_size_56c8e0; baseline=6; break;
      case 17:
        outline_radius=native_font_size_56c8e0; baseline=6; break;
      case 18: case 19:
        outline_radius=native_font_size_56c8d0; baseline=2; break;
      case 20:
        outline_radius=native_font_size_56c8d8; baseline=7; break;
      case 21:
        outline_radius=native_font_size_56c8d8; baseline=7; break;
    }
    outline_radius*=native_font_outline_scale_5ae120;
    native_font_outline_scale_5ae120=1.0f;

    wchar_t unicode[258];
    std::memset(unicode,0,0x202);
    MultiByteToWideChar(932,0,formatted,-1,unicode,0x100);
    const std::int32_t bitmap_width=(transform->field_c-transform->field_a)
                                  +3+static_cast<std::int32_t>(outline_radius);
    const std::int32_t bitmap_height=(transform->field_d-transform->field_b)
                                   +3+static_cast<std::int32_t>(outline_radius);
    reinterpret_cast<NativeGlyphCanvasView*>(canvas)->ensure_format_4153d0(bitmap_width,bitmap_height+6,0x15);
    HDC dc=static_cast<HDC>(reinterpret_cast<NativeGlyphCanvasView*>(canvas)->device_context_415620());
    HGDIOBJ previous=SelectObject(dc,selected_font);
    // Original stack +0x10 supplies the GDI text color. The separate
    // +0x14 word is the glyph-mask outline color: neither is a render layer.
    // Preserve the original three used 8-bit channel stores and masks.
    const std::uint8_t red=static_cast<std::uint8_t>((static_cast<std::uint32_t>(text_color_word)>>16)&0xffu);
    const std::uint8_t green=static_cast<std::uint8_t>((static_cast<std::uint32_t>(text_color_word)>>8)&0xffu);
    const std::uint8_t blue=static_cast<std::uint8_t>(static_cast<std::uint32_t>(text_color_word)&0xffu);
    const COLORREF text_color=RGB(red,green,blue);
    SetBkMode(dc,TRANSPARENT);
    const std::int32_t char_count=static_cast<std::int32_t>(std::wcslen(unicode));
    SIZE extent;
    GetTextExtentPoint32W(dc,unicode,char_count,&extent);

    if (align==0) {
        // Native advances its actual stack argument exactly once before drawing.
        horizontal_offset += 2;
        SetTextColor(dc,text_color);
        if (is_special!=0) {
            TextOutW(dc,horizontal_offset,baseline,unicode,char_count);
            reinterpret_cast<NativeGlyphCanvasView*>(canvas)->composite_glyph_mask_416420(bitmap_height+6,0,bitmap_width,
                                                outline_color,outline_radius);
        }
        TextOutW(dc,horizontal_offset,baseline,unicode,char_count);
    } else {
        wchar_t single_character[2]{};
        SetTextColor(dc,text_color);
        if (is_special!=0) {
            std::int32_t px=horizontal_offset;
            for(std::int32_t k=0;k<char_count;++k) {
                single_character[0]=unicode[k];
                single_character[1]=0;
                TextOutW(dc,px,baseline,single_character,1);
                px+=align;
            }
            reinterpret_cast<NativeGlyphCanvasView*>(canvas)->composite_glyph_mask_416420(bitmap_height+6,0,bitmap_width,
                                                outline_color,outline_radius);
        }
        std::int32_t px=horizontal_offset;
        for(std::int32_t k=0;k<char_count;++k) {
            single_character[0]=unicode[k];
            single_character[1]=0;
            TextOutW(dc,px,baseline,single_character,1);
            px+=align;
        }
    }
    SelectObject(dc,previous);
    reinterpret_cast<NativeGlyphCanvasView*>(canvas)->invert_alpha_417ab0(bitmap_height+6,0,bitmap_width,0);
    SelectObject(dc,previous);
    {
        std::lock_guard<std::recursive_mutex> submit_guard(process_locks.slot(0x13));
        NativeTextTransform4 native_rectangle=*transform;
        NativeTextTransform4 pixel_rectangle{
            0,0,native_rectangle.field_c-native_rectangle.field_a,
            native_rectangle.field_d-native_rectangle.field_b};
        if(pixel_rectangle.field_c>0x400)pixel_rectangle.field_c=0x400;
        if(native_font_extra_padding_5b66ec && font!=0x13 && font!=0x12) {
            pixel_rectangle.field_b=6;
            pixel_rectangle.field_d+=6;
        }
        const std::int32_t glyph_mode=mode;
        // Native upload code proves this original 32-bit argument word
        // becomes a borrowed completion-byte pointer in the captured job.
        // The submit/format caller's external parameter spelling is still
        // unresolved; preserve every i386 pointer bit from that input.
        std::uint8_t* completion_flag=reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(static_cast<std::uint32_t>(mode)));
        NativeGlyphRenderJob glyph_job(canvas,texture,native_rectangle,pixel_rectangle,
                                       completion_flag,callback);
        // The original 56B queue bridge takes an already-constructed
        // std::function lvalue by reference, preserving its owner lifetime.
        std::function<void()> submitted(std::move(glyph_job));
        // Original 0x005B66E0 is the 12B PMR list object itself, not
        // a global pointer. Borrow the identical native head/count layout
        // for its whole-exact 56B member bridge without copying the list.
        reinterpret_cast<NativeGlyphQueueView*>(&native_glyph_task_queue_5b66e0)
            ->submit_4162f0(submitted);
    }
    // Original returned text SIZE is a native EDX:EAX value (not pixels).
    return (static_cast<std::uint64_t>(static_cast<std::uint32_t>(extent.cy))<<32) |
           static_cast<std::uint32_t>(extent.cx);
}
} // namespace th20
