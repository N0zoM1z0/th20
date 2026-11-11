# CORE/RECON-1105 — complete 586B centered Unicode Renderer text source, SSE frontier

The original Japanese TH20 Steamless v1.00a executable (SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`) contains a distinct **586-byte /140-instruction** Renderer text function at `0x0044ADD0..0x0044B019`. The entire native body SHA-256 is `f6f5cc2d5565eb50d13a16813098118685183bbaedbcb678eb6b766371f5f829`. A real `ret` ends at `0x0044B01A`; the following `0x0044B020` is the **different 578B ASCII renderer**. The original 586B centered function has two observed callers, at `0x004DECF0` and `0x0052DF30`.

The full natural C++ source is now maintained in [`AnimationRendererCenteredText586.cpp`](../src/AnimationRendererCenteredText586.cpp). Its `__cdecl` variadic member belongs to the same borrowed [`NativeRendererFormattedTextView`](../src/NativeRendererFormattedTextView.hpp) owner as the separately whole-exact **417B** formatted-text function. Both methods pass `this` and the eight-byte hidden result pointer on the stack, rather than impersonating a nonmember caller; both delegate to the original `0x0044FFF0` submit method using the same Renderer `this`. The 417B exact unit was rebuilt and passed **417/417** after adding this sibling declaration, with no wider shared-header changes.

## Original game behavior and width calculation

The complete original acquires `process_locks.slot(9)`, loads a float font advance from the genuine `0x0056C768` indexed table, formats variadic input with the separately exact `0x00447940` wide-text helper into a 640-`wchar_t` stack buffer, obtains `Animation::sprite_data()`, copies the four Animation transform words at `+0x3A8..+0x3B4`, sets bit zero of the actual **byte** at `Animation+0x49A` and independently reads bit ten of the **word** at `Animation+0x49C`.

The centered-horizontal displacement is the integer truncation of `sprite->extent_4c / 2.0f - ((font_advance * 2.0f - 1.0f) * float(strlen(formatted_bytes))) / 4.0f`. The original uses a real **unsigned 32-bit `strlen`** conversion, including its `0.0/4294967296.0` correction table, rather than a signed-only conversion or the unrelated scale used by the 578B ASCII caller. It looks up the Sprite texture, copies the original 40-byte `std::function<void()>` callback, passes the integer offset and `align << 1` to the 294B `submit_text_44fff0`, and releases the lock and callback under the genuine destructor/EH path. Formatting/encoding limitations of the native 0x500-byte stack region are not independently established.

## Complete physical call and data sites

All **11 physical E8 calls**, read from the immutable original machine-code relative displacements, are:

| Native call opcode offset | Original destination / role |
| --- | --- |
| `+0x39`, `+0x45` | `0x0040C310` lock registry slot, `0x0040B730` guard construction |
| `+0x7D`, `+0x92` | `0x00447940` formatter, `0x00437CD0` sprite lookup |
| `+0x12A`, `+0x1A4` | `0x0054FE20` byte `strlen`, `0x00445A00` texture lookup |
| `+0x1BE`, `+0x20A` | `0x004140F0` function copy, `0x0044FFF0` text submit |
| `+0x219`, `+0x228`, `+0x241` | `0x0040B900` guard release, `0x00414400` function destruction, `0x005429EE` security cookie check |

All **nine native PE HIGHLOW** fields are independently located at `+0x06 -> 0x00568578` (EH), `+0x18 -> 0x005B25C0` (cookie), `+0x35 -> 0x005C0240` (lock registry), `+0x56 -> 0x0056C768` (font table), `+0x10F -> 0x0056C8D0` (`2.0f`), `+0x117 -> 0x0056C8CC` (`1.0f`), `+0x14E -> 0x0056CDD0` (unsigned length correction), `+0x172 -> 0x0056C8E0` (`4.0f`), and `+0x185 -> 0x0056C8D0` (`2.0f`). These physical sites are measured from the original PE, not guessed by reverse-solving a candidate COFF field.

## Reproduced native compiler frontier, not exact

Pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` builds the maintained C++ into a complete **594B /140-instruction** COFF contribution with all **11 REL32 + nine DIR32** roles. Before the centered-width expression, original and generated source are identical apart from two ordinary frame/local-offset operands (the generated frame uses `sub esp,0x548` versus the original `sub esp,0x544`). In the mathematical suffix, `/Od` materializes an additional intermediate `formatted_width` float at a stack slot; the original keeps the pre-subtraction width in an XMM register, using `movss xmm1,[char_width]`, `mulss xmm0,xmm1`, then `subss xmm1,xmm0`. The modern 594B expression instead spills width and uses a memory-source `mulss`/`subss`, accounting for the net eight-byte native-length difference and changed operand/relocation offsets.

Multiple ignored/private natural source shapes were compiled as focused experiments: distinct float intermediates (622B), a single direct expression (602B), precomputed advance with a length variable (594B), direct `strlen` plus a named computed width (594B), and a length-first expression (582B, but wrong original evaluation order). The maintained 594B version keeps the real advance-first, length-second behavior and avoids fictitious padding, unused locals, inline assembly, or truncating the original native extent. **`0x0044ADD0` remains SOURCE-PRESENT, NONEXACT**; neither this function nor its separate 294B text-submit callee receives original exact credit. The private alternatives remain under ignored `.analysis/gptweb-centered586-probes/`.

Reproduce the scoped compiler frontier:

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AnimationRendererCenteredText586.cpp \
  build/core1105-probes/AnimationRendererCenteredText586.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
# Separate already accepted header consumer, rebuilt only for its changed include:
nice -n 15 scripts/repo-python scripts/build.py --unit animation_renderer_formatted_text_417
scripts/repo-python scripts/compare-coff-function.py --unit animation_renderer_formatted_text_417
```

Next work: recover the original intermediate float lifetime/register allocation that preserves the actual length-conversion order, prove the nine relocation targets against the unchanged machine-code positions, and only then consider adding a 586B strict unit. Do not count the independent whole-exact 417B parent again.
