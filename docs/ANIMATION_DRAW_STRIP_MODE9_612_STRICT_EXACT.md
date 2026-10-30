# CORE/RECON-852 — whole original 612B Animation strip mode9 renderer, strict exact

The immutable Japanese TH20 v1.00a Steamless executable has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its actual original strip-mode renderer at **`0x00445350`** is **612B /
182 genuine i386 instructions**, native `sub esp,0x40` and `ret 0xC`,
with one renderer ECX receiver plus original Animation*, vertex stream
and vertex-count stack inputs. The 5,993B Draw dispatcher directly
calls this physical head at its independently attested E8 `0x00443B01`.

The maintained natural C++
[`src/AnimationDrawStripMode9.cpp`](../src/AnimationDrawStripMode9.cpp)
now passes an original **612/612B strict canonical zero-difference
whole-function replay**, including all eleven direct native E8 physical
site-and-target pairs and five original PE HIGHLOW site-and-target pairs.
The sibling 534B strip-mode11 has separate original source/physical
function identity; no code or match unit is credited twice.

## Original native PE evidence independent of source/COFF

The original-only
[`scripts/verify-animation-strip-mode9-native.py`](../scripts/verify-animation-strip-mode9-native.py)
extracts and decodes all 182 original i386 heads, verifies native
`0x40` stack, `ret 0xC`, all **11 actual E8 sites with original targets**,
and all **five** PE `.reloc` HIGHLOW fields pointing at real global
Graphics `0x005C4D40`. It independently checks the 5,993B parent's
original call, real `Animation+0x4A0` byte-based 2-bit color selection,
`SHR dl,4; AND dl,3; MOVZX eax,dl; CMP eax,3; JE` code, and the true
absence of an extra NOP after native `prepare_texture_states`.

Actual original E8 target roles: one Animation draw-enabled guard
`0x00445AB0`, original pool flush `0x004455C0`, sprite data
`0x00437CD0`, **five** separate Graphics get-device E8
`0x00412730`, renderer texture lookup `0x00445A00`, real texture-state
prep `0x00445BA0`, and quad color-mode selection `0x00446690`.
The physical five original PE Graphics global references are at
`+0x120/+0x171/+0x198/+0x1C0/+0x22C`.

## Source-level discoveries and rejected hypotheses

The original rejects insufficient vertex counts, failed Animation draw
enablement, an unset active-display flag or an alpha-zero Animation
byte at `+0x493`. It flushes pending renderer output, then on a first
original Animation bit21 transition offsets every vertex by receiver
`+0xD0/+0xD4` using genuine **28-byte seven-float** stride. It binds
original sprite texture caching, authentic FVF `0x144`, the real D3D9
texture-stage settings `SetTextureStageState(0,6,0)` and `(0,3,0)`,
then invokes native texture prep and color-mode selection before the
true triangle-strip `DrawPrimitiveUP(vertex_count-2,stream,0x1C)`.

The independent original x86 disproved two seemingly equivalent source
assumptions:

1. Reading the original packed color mode as a raw indexed
   `uint8_t*` at `Animation+0x4A0` made `/Od` emit additional address
   multiplication. Using the actual existing `AnimationFlags::bits_08`
   two-bit C++ field `field_4_5` naturally produces all original
   8-bit `MOV/SHR/AND/MOVZX` operands and native `JE` direction.
2. When the texture-prep function call and subsequent field comparison
   were written as two separate C++ expression statements, the pinned
   compiler inserted a non-original one-byte `NOP` after the call.
   The original always performs this *observable* function call before
   testing the real Animation flags. Expressing that sequential dependency
   naturally with C++'s sequencing/comma operator inside the real
   conditional caused the pinned compiler to emit the original
   immediately following `mov ecx`, without an inert statement,
   handwritten NOP, copied machine bytes or changed ABI. The source
   compiler then naturally emitted the original **612B/182 x86** body.

## Canonical strict byte replay, owned game credit and scope

A single new native `animation_strip_mode9_612` unit in
[`config/match-units.toml`](../config/match-units.toml) compiles the
one source using project pinned MSVC 19.44.35211 C++20 x86 flags
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
All **eleven** COFF REL32 call symbols and **five** DIR32 Graphics global
relocations are independently mapped from the original PE before strict
byte comparison. The generated **548/548 non-relocation native bytes**
also agree in their exact physical positions. Fresh pinned source
receipt and whole relocated replay:

```text
animation_strip_mode9_612: exact (612/612 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This admits **one new distinct original game-authored function /612 native
`.text` bytes**. Live totals become **606 whole game-authored strict exact
functions /211,593 bytes**, with **1,252 source mappings /1,253 strict
units /271 pinned object/receipt providers**. No previously exact
source/header/profile is touched; only this new source is cold-compiled
and replayed. No unfiltered all-graph cold replay occurs. The enclosing
5,993B Animation Draw main dispatcher remains **SOURCE-PRESENT/NONEXACT**.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-strip-mode9-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawStripMode9.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
