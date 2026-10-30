# CORE/RECON-852 — whole original 612B Animation strip mode9 strict exact

The immutable Japanese TH20 v1.00a Steamless PE, locked SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
has a game-authored full strip-mode9 renderer at native `0x00445350`:
**612B /182 real i386 instruction heads**, native `sub esp,0x40` and
`ret 0xC` for its three stack arguments (`Animation*`, vertex stream,
vertex count). The still-NONEXACT 5,993B Animation main Draw dispatcher
calls the real physical head at E8 `0x00443B01`.

The maintained natural C++ method
[`src/AnimationDrawStripMode9.cpp`](../src/AnimationDrawStripMode9.cpp)
strictly matches the **entire original 612/612B**, not an arbitrary code
prefix or a copied native instruction block. It is **one original physical
game-owned function** separate from the previously strict 534B strip11
renderer and all other exact Animation/Graphics helpers.

## Independent native PE and correct gameplay semantics

[`scripts/verify-animation-strip-mode9-native.py`](../scripts/verify-animation-strip-mode9-native.py)
reads original executable `.text`, disassembles all 182 real instructions
through the original native return, independently parses the PE
`.reloc` directory and asserts **all 11 true E8 site/destination pairs**
and **five genuine HIGHLOW physical fields and target values**. All five
original absolute data fields point to the live Graphics state owner
`0x005C4D40`, at native method offsets
`+0x120/+0x171/+0x198/+0x1C0/+0x22C`.

Native gameplay operations preserved in source:

1. Check count at least three, Animation draw enable/flag bit0 and the
   original single alpha byte at `Animation+0x493`. Rejected draws return
   -1; successful draws return zero using the native `ret 0xC` ABI.
2. Flush pending render draws when the genuine renderer queue at
   `this+0x6000E70` is nonempty. On first execution gated by Animation
   bit21, set the real `0x200000` flag and offset original X/Y vertex
   coordinates at `this+0xD0/+0xD4` across the actual **28B/sprite**
   vertex stream, respecting the original per-vertex loop and count.
3. Read original SpriteData texture ID, compare/update renderer cache
   `this+0x6000E08`, bind the real texture through the original
   `Graphics::get_device()` and texture-for-sprite methods.
4. When cached FVF state differs from three, apply original FVF `0x144`,
   D3D9 texture stage states `(0,6,0)` and `(0,3,0)`, and store the real
   state cache byte at `this+0x6000E0E`.
5. Invoke the actual already-strict `prepare_texture_states` method at
   `0x00445BA0`, then test the original Animation `+0x4A0` three-lane
   flags' **two-bit field at positions 4–5**. The source reads the bitfield
   in native `SHR 4; AND 3; MOVZX` form, selects color mode 0 or 3,
   invokes original `select_render_color_mode` at `0x00446690`, then
   submits a real triangle strip via D3D9 `DrawPrimitiveUP` with
   `vertex_count-2` primitives and original 28-byte stride.

The real native original has **no NOP** between the texture preparation
E8 at method `+0x1F8` and the color-mode field read at `+0x1FD`.
An initial apparently equivalent two-statement source compiled with an
extra `/Od` NOP (613B instead of original 612B) and shifted the last
E8/data sites. Using a **natural C++ comma expression** makes the true
observed dependency explicit: first the real texture-state method executes,
then the Animation mode field is read. This is real evaluation order, not
an inert compiler-shaping local or manufactured no-op. Pinned MSVC
naturally produces the native 612B/182-i386 original instructions, original
11 E8 positions, **548/548 nonrelocation bytes** and all five matching
original Graphics data references.

## Full canonical acceptance and bounded replay

A single `animation_strip_mode9_612` unit in
[`config/match-units.toml`](../config/match-units.toml) compiles one
ordinary natural source object with pinned x86 MSVC C++20 flags
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The complete manifest independently fixes 11 authentic E8 REL32 and five
real PE HIGHLOW/DIR32 symbol/offset/target roles. The original PE census
was performed independently of candidate COFF values. A newly generated
compiler receipt and entire original 612-byte relocation replay confirm:

```text
animation_strip_mode9_612: exact (612/612 bytes)
Exact replay: 1/1 units, 1 cold objects
```

Only **one new original game function, 612 native `.text` bytes**, is
credited. The associated Graphics, texture and neighboring strip11
functions retain their existing code credit without duplication. No
previously accepted source/header/provider is modified, so **only the
one newly affected canonical source** is cold compiled and replayed.
No full graph cold replay is run.

| Verified live metric | Before | After |
| --- | ---: | ---: |
| Distinct game-authored whole strict exact functions | 605 | **606** |
| Strict original game native bytes | 210,981 | **211,593** |
| Source-present mapped physical functions | 1,251 | **1,252** |
| Canonical strict match units | 1,252 | **1,253** |
| Distinct pinned exact compiler object/receipt providers | 270 | **271** |

The enclosing original Animation main Draw dispatcher at `0x00443880`
remains **SOURCE-PRESENT/NONEXACT**. The entire game is not yet linked
or playable from the reconstructed sources.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-strip-mode9-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawStripMode9.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
