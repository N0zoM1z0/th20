# CORE/RECON-813 — complete original 1,163B D3D9 four-mode texture-stage state boss, strict native exact

Immutable Japanese TH20 v1.00a Steamless executable SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
**The entire original game-owned `0x00446690` D3D9 texture-stage state machine
is now strict whole-native exact** under the maintained method
`AnimationQuadSubmitOwner::select_render_color_mode(std::uint8_t)` in
`src/AnimationQuadBlendState.cpp`. This is a complete substantial game function,
not a compiler/runtime helper and not a prefix or a source-only approximate
match. The enclosing **3,159B** quad submission and **5,993B** Animation draw
parent functions remain independently **SOURCE-PRESENT / NONEXACT**.

## Original x86 truth, four real modes, and 54 physical call/data fields

The real original function starts at **`0x00446690`** and ends its native
`ret 4` at **`0x00446B18`**. It contains exactly **1,163 executable bytes /
343 x86 instruction heads**, plus a real **one-byte alignment NOP** and a
**16-byte direct 4-pointer switch table** at `0x00446B1C`. Original four
code-pointer targets (all actual original instruction heads) are:

| Native mode | Original PE table field | Original branch target |
| --- | --- | --- |
| 0 | `0x00446B1C` | `0x004466CE` |
| 1 | `0x00446B20` | `0x004467C4` |
| 2 | `0x00446B24` | `0x004468DE` |
| 3 | `0x00446B28` | `0x004469F8` |

The original first compares the incoming mode with the actual first
byte of its ECX renderer-owner instance. An unchanged value skips the
entire operation. On change it calls the already separate **192B
strict-exact `AnimationPoolOwner::flush_draws()` at `0x004455C0`** before
modifying device state. The main dispatch has an actual unsigned
`cmp [ebp-8],3`, one true `ja` fallback, and one **absolute indirect x86
`jmp [ecx*4+0x00446B1C]`**. After a selected state transition, it writes
the new one-byte mode into the original receiver at `+0x00`.

All **24 actual D3D9 `SetTextureStageState`** calls are indirect
through the original device's **vtable slot +`0x10C`**. For each mode,
there are exactly six stage-zero operations, each preceded by a separate
`Graphics::get_device()` **native `E8`**. Their actual stage-state
operations are:

| State argument | Default/mode 0 | Mode 1 | Mode 2 | Mode 3 |
| --- | ---: | ---: | ---: | ---: |
| `D3DTSS_ALPHAARG1` | 2 | 2 | 0 | 2 |
| `D3DTSS_ALPHAARG2` | 0 | 3 | 0 | 0 |
| `D3DTSS_COLORARG1` | 2 | 2 | 0 | 2 |
| `D3DTSS_COLORARG2` | 0 | 3 | 0 | 0 |
| `D3DTSS_ALPHAOP` | 4 | 4 | 2 | 3 |
| `D3DTSS_COLOROP` | 4 | 4 | 2 | 4 |

The immutable original whole body contains **25 actual direct `E8`
operands**: **one** call to `0x004455C0` and **24** calls to
`0x00412730` (`Graphics::get_device()`). It also contains **29 genuine
original PE32 `IMAGE_REL_BASED_HIGHLOW` fields** over the full
**1,180-byte code+padding+table extent**: 24 original references to
`process_graphics` **`0x005C4D40`**, one instruction-field pointer to
the real four-way switch table **`0x00446B1C`**, plus all **four original
PE-relocated switch target entries**. The 24 D3D9 `SetTextureStageState`
virtual calls are not incorrectly counted as direct `E8` relocations.
Original parent quad submission calls this physical method at native
`0x0044015B`, without granting that enclosing 3,159-byte parent
any new byte credit.

`scripts/verify-animation-quad-blend-native.py` independently verifies all
these facts from the locked original PE, `.reloc` directory and disassembled
x86, not from our modern compiler or old Ghidra function names.

## The actual original C++ control-flow/codegen frontier

Prior source hypotheses already had correct device-method behavior but
were **NONEXACT**. When the source used a locally cached renderer-byte
reference, pinned MSVC emitted extra receiver spills and a 1,192B COFF
contribution. Even with the direct byte view, an ordinary `default:`
followed by cases 1..3 produced a 1,176B non-table code contribution
based on a sequence of three `cmp/je` branches, rather than the original
four-entry x86 jump table.

An ordinary, semantically valid **explicit `case 0:` merged with
`default:`**, paired with directly reading and writing the one-byte
renderer owner state, made MSVC emit the original 4-way jump-table
lowering. The whole resulting emitted **1,180B** contribution has exactly
**1,163 executable bytes /343 real original x86 instructions**, followed
by the same **one byte NOP and four original 32-bit jump table fields**.
All 54 COFF relocation entries match the original *kind*, *physical
offset*, *MSVC symbol*, and *independently original PE target*. Every
other source byte matches. No NOP, hard-coded machine instruction, inline
assembler, fake dead branch, patched binary or truncated prefix was used.

This includes original D3D9 state lifetimes and all 24 genuine repeated
device getter calls: the C++ intentionally does not cache one device
across the six separate native setters.

## Full canonical match, scope, and honest accounting

The pinned MSVC **19.44.35211 i386** `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` cold compiles exactly one new
translation unit `src/AnimationQuadBlendState.cpp`, with protected receipt,
into `build/core813-canonical/AnimationQuadBlendState.obj`. The new unit
`animation_quad_blend_stage_boss_1163` uses original `size = 1163` for
**real game-owned executable code credit** and `compare_size = 1180` to
also require **all 17 original padding/table data bytes and four table
relocation fields** to match. Thus the original 17 trailing data bytes
are not falsely credited as extra game instructions.

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-animation-quad-blend-native.py
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationQuadBlendState.cpp
    scripts/repo-python scripts/validate-tracking.py --require-target

Strict acceptance: **1/1 whole-native function**, **1,163/1,163 code
bytes**, **1,180/1,180 comparison bytes**, **343/343 x86 heads**,
**25/25 original E8** and **29/29 genuine PE HIGHLOW fields**. No
pre-existing canonical source/header was changed, so the old protected
strict-unit replay closure is **zero**; exactly one new provider/object
was compiled. There was **no unfiltered all-repository cold replay**.

Original authored game exact advances from **587 distinct physical
functions /189,624 nonoverlapping `.text` bytes** to **588 /190,787B**;
source-present methods **1,236 →1,237**, configured native strict units
**1,236 →1,237**, protected distinct compiler object/receipt providers
**257 →258**. The original 3,159B renderer parent retains its previously
verified 40/40 game E8 source-role graph, but **remains NONEXACT**;
the unrelated 5,993B Animation draw dispatcher, 12,140B Bullet command,
41,967B Enemy ECL and 39,470B Animation VM also remain not whole exact.
