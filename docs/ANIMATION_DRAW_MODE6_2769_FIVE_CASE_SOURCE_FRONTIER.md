# CORE/RECON-843 — whole original 2,769B Mode6 renderer source, native 5-case/data roles (NONEXACT)

The locked original Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains a complete game-owned Animation Mode6 render method at **`0x004408B0`**.
The real 5,993-byte parent Animation Draw dispatcher reaches it through the
native `0x00443A25` Mode6 E8. The original whole physical method is
**2,769B /683 genuine x86 instructions**, with original `sub esp,0x64`,
`ret 4`, **28 original E8 calls**, **78 original in-body PE HIGHLOW data
fields**, a **3-byte original after-RET NOP**, and **five original 32-bit
case pointers** at `0x00441384`.

One maintained natural C++ definition now covers the *entire original
function*, not a collection of copied pseudocode blocks:
[`src/AnimationDrawMode6.cpp`](../src/AnimationDrawMode6.cpp),
`AnimationDrawDetailedOwner::draw_complex_mode6(Animation*)`.
This is **SOURCE-PRESENT, NONEXACT**. The pinned MSVC compiler emits the
original **2,769B executable extent and 3B NOP +20B five-way pointer
table at identical original relative positions**, but its actual i386
instruction/register/stack/relocation bytes still differ. **No original
parent exact-game byte credit** or canonical match unit has been added.

## Independently original-PE-attested graph and source role comparison

The new [original-only locked PE audit](../scripts/verify-animation-draw-mode6-native.py)
extracts the whole original function, disassembles all 683 true instruction
heads, parses `.reloc`, and checks **every actual E8 site and physical
destination**, the in-body 78-field HIGHLOW **target histogram**, and all
five *physical* after-RET PE HIGHLOW mode switch entries. Original native
case pointer destinations are:

| Mode | Original target | Source mode partition |
| ---: | --- | --- |
| 0 / 1 | `0x004409FC` | Same original 0/1 case block |
| 2 / 3 | `0x00440CFE` | Same original 2/3 case block |
| 4 | `0x004410D2` | Independent mode4 case block |

The genuine five-pointer data resides at offsets `+0xACC..+0xADC`, after
one real `0F 1F 00` alignment, **not additional executable i386**.
No manual switch array, branch byte patch, or other assembly is present
in the maintained C++: MSVC naturally emits the same physical 5-way
pointer allocation and 2/2/1 target-alias partition.

The [focused whole source verifier](../scripts/verify-animation-draw-mode6-source-roles.py)
recompiles only this **noncanonical** C++ with the locked i386 MSVC profile
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
It checks actual compiler COFF E8 relocation source symbols and original
native destinations in their **entire original physical call order**, all
78 body DIR32 target-class multiplicities, the five table-pointer
relocation positions and alias partition, the whole code+after-data extent,
and independent original `.reloc` targets. The original whole native vs
current source output is:

| Immutable original fact | Current natural C++ pinned-MSVC evidence |
| --- | --- |
| **2,769B executable**, 683 actual x86 instruction heads | **2,769B executable**, **682** actual x86 heads — NONEXACT |
| Original 0x64-byte stack | Candidate `sub esp,0x70` — **12B excess locals**, NONEXACT |
| Original 28 real E8 /9 target classes | **28/28 target roles, exact target multiplicities and entire original call order**; first **6 real E8 instruction offsets** match |
| Original 78 original PE HIGHLOW body fields in 12 target classes | **78/78 genuine candidate DIR32 target-role occurrences**, **15/78 exact site-and-target pairs** |
| One after-RET `0F 1F 00`, five original HIGHLOW switch fields | **Identical code/after-data boundaries, original NOP bytes and 5/5 field offsets**, same original 2/2/1 case alias partition |
| Strict original whole code byte equality | **NOT achieved:** only 389/2,348 non-relocation bytes equal in the provisional comparison |

Original direct-call target multiplicities, checked from immutable physical
E8 displacement bytes:

- **16** calls to original game-owned channel `multiply_color_128_saturating`
  (`0x0043F520`), **four** to original `multiply_color_255`
  (`0x0043F4F0`), and two to the original by-value `Vector3::operator+`
  (`0x00429570`).
- One original call each to the separately whole exact **1,378B mode6
  preparation** (`0x00440340`), Vector3 default ctor (`0x00422E10`),
  Vector3 subtraction (`0x00429440`), separately exact **25B Euclidean
  depth** (`0x00445700`), previously whole strict exact **3,159B quad
  submit** (`0x0043F6A0`), and the natural compiler security checker.

The original 78 PE HIGHLOW target roles are **28 packed quad color words**
(`0x005AEF20`), **21 actual Graphics+0xB00 current viewport
pointers** (`0x005C5840`), **eight existing original 1.0f values**,
**six alpha**, **four green** and **four red** quad channel addresses,
**two original 2.0f values**, one security cookie, the two original
WindowState display dimensions, one native 448.0f, and one genuine
five-way jump table pointer. The C++ does not create fake global data
owners or copy native address fields to emit those target roles.

## Corrections against old decompiler and source assumptions

1. **Original mode6 is a real member method.** The physical caller passes
   `Animation*` on the stack and renderer receiver in ECX. It starts by
   calling the now strict exact 1,378B mode6 screen-projection setup and
   returns `-1` on original failure. A full Vector3 camera-relative value
   is constructed through the real by-value +,+,− operations, optional
   original window offset, and the exact 25B Euclidean depth helper.
2. **Colors are three genuinely different native rendering modes.** Modes
   0/1 select one source color and optionally tint it; modes 2/3 keep
   and separately tint two source colors, placing colors in the native
   0/2 or 0/1 vertex pair order; mode4 multiplies both source colors
   channelwise with the original divide-by-255 game helper, then optionally
   applies native saturating tint. The C++ contains 16 authentic tint
   calls and four authentic multiply-by-255 calls, no artificial duplicate
   function invocations to pad the call list.
3. **Fog arithmetic acts on the real shared quad output.** The first
   source probe mistakenly modified the *local input packed color* in the
   fog branch, then overwrote the shared vertex as one 32-bit word. Original
   SSE writes the B/G/R/A channels individually to the true file-backed
   `native_quad_vertices` fields, with byte conversion/truncation and
   original saturation, including mode-specific cubic vs linear alpha
   fade. Correcting the actual output owner restored the original **12
   additional physical channel-reference classes** (78/78 total PE
   HIGHLOW *target* occurrences), rather than adding dummy loads.
4. **Viewport and tint are live renderer state.** Hoisting a single
   `const FogValue*` into a local suppressed eleven physical original
   viewport loads. Directly reading the actual
   `process_graphics.current_viewport->fog` field at each native use
   restores the original **21** independent live Graphics HIGHLOW target
   occurrences. Similarly, the original reads renderer tint bytes
   directly from ECX receiver+`0x7D40E8C` with the flag at
   +`0x7D40E90`; caching a tint pointer/enable flag changed native
   stack lifetime. The maintained source reads these fields at their
   source-visible original owner offsets, without fake renderer storage.
5. **Native source-mode layout and default branch.** Original switch
   branches over modes 0/1, 2/3, 4 using real 5 case-pointer data. The
   ordinary source switch produces the same direct five-pointer table
   with the exact 2/2/1 alias partition and same physical after-RET
   alignment, not an index-compressed or manually constructed table.
   Removing excess color zero-initialization (all actually read colors
   are initialized on their real source-specific branch) and re-reading
   the real packed Animation mode during per-case color selection also
   recovers the original **2,769B** compiler executable extent.

## Remaining whole-original native-exact frontier

The shared natural source is still genuinely different in register and
local lifetime generation. The original stores the renderer ECX at
`[ebp-0x20]`, its fog-span at `[ebp-0x28]` and the camera-relative
Vector3 at `[ebp-0x18]`, with **`0x64`** stack frame. Current MSVC output
has **`0x70`** frame and a different temporary/packed-color allocation;
its 682 original-sized instruction heads differ from the **683** native
heads. Relative E8 *targets* all agree, but after the first six physical
calls their offsets differ. Only **15 of 78 body HIGHLOW site-and-target
pairs** currently agree. The five true after-RET table data sites do
agree, but those data bytes are not original gameplay instruction credit.

Next: re-examine natural camera-relative temporary and fog-span lifetime,
packed local animation color, byte-valued mode dispatch, and the native
near/far fog case shared return blocks. Fix true source semantics/owners
rather than forcing stack size with inert locals. Do not add an exact
match unit until **all 2,769 original executable bytes plus authentic
23B after-RET extent and relocation ownership** pass canonical strict
zero-difference replay.

This checkpoint adds exactly **one source-present original game-owned
mode6 method mapping**, not exact game bytes, strict units or accepted
compiler object providers. Existing game-authored exact totals remain
**600 original physical functions /201,103 bytes**, **1,247 strict units,
265 canonical providers**. Source-present count becomes **1,247**. The
only modified native C++ is previously **source-absent/noncanonical**
`src/AnimationDrawMode6.cpp`; its single isolated MSVC probe is the only
native build needed. No previously accepted shared header, exact source,
compiler profile, manifest unit, original executable or pinned receipt was
changed. **Affected exact replay scope: zero; no full cold replay.**

## Reproduce only this NONEXACT source and independent original PE

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-draw-mode6-native.py
nice -n 15 scripts/repo-python scripts/verify-animation-draw-mode6-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/build.py --check
```

Private preserved variant source objects and actual code comparisons are
under `.analysis/core843-mode6/` and `build/core843-probe/`. The earlier
source-present **5,993B** main Animation Draw dispatcher and the fully
strict exact **1,378B** mode6 setup remain independently verified, with
no additional original-parent code bytes credited to either.
