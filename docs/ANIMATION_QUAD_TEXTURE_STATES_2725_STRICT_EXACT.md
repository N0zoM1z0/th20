# CORE/RECON-819 — complete original 2,725-byte D3D9 renderer texture/sampler state boss strictly native exact

The immutable Japanese TH20 v1.00a Steamless comparison PE has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint reconstructs the **ENTIRE original game-authored 2,725-byte /
699-x86-instruction** texture/sampler-state backend at **`0x00445BC0`**
with natural C++ `AnimationQuadSubmitOwner::bind_native_texture_state(Animation*)`
in **one maintained source** `src/AnimationQuadTextureStates.cpp`.
It is not a truncated prefix, extracted case, synthetic shim, assembly patch,
compiler helper or a claim of complete parent linkage. The genuine
**3,159-byte** quad submit and **5,993-byte** Animation draw parents still
remain **SOURCE-PRESENT / NONEXACT**.

## Independent original native evidence and real graph

The game-owned method is called through the independently strict-exact
**26-byte wrapper** `0x00445BA0` at original `E8` `0x00445BAE`, with one
native `Animation*` parameter and the existing ECX game Renderer receiver.
The real native full `0x00445BC0..0x00446664` function ends with the
complete original `ret 4` at `0x00446662`. Original x86 and PE `.reloc`
independently prove:

| Physical original evidence | Verified value |
| --- | --- |
| Whole game-authored code | **2,725B /699 genuine x86 instructions**, including original `ret 4` |
| Real source D3D9 device retrievals | **46 separate E8** to `0x00412730` (`Graphics::get_device()`) |
| Actual draw-queue state barriers | **4 E8** to previously separately strict `0x004455C0` (192B flush) |
| Other direct E8 calls | **None** — total **50 genuine E8** across two source game target heads |
| Indirect D3D9 virtual calls | **36** `SetRenderState` through device vtable **+0xE4**, **10** `SetSamplerState` through **+0x114** |
| In-function PE HIGHLOW | **47**, comprising 46 real references to `process_graphics` `0x005C4D40`, plus the original indirect branch's case-table pointer |
| Original after-return data | Three native alignment bytes `0F 1F 00` followed by a real **10-entry /40-byte PE HIGHLOW code pointer table** |
| Original comparison extent | **2,768B =2,725 real .text code +3 aligned bytes +40 original table bytes** |
| Total original PE HIGHLOW relocated fields | **57 =47 inside +10 actual table entries**; with 50 E8 fields gives **107 whole-native COFF references** |

The independent real original case-table is at `0x00446668`. It is not a
compiler-generated indexed-byte table. All ten original field addresses
are actually relocated by the PE's **IMAGE_REL_BASED_HIGHLOW** directory
and point to verified original instruction entry heads:

| Mode | Table entry | Original target |
| ---: | --- | --- |
| 0 | `0x00446668` | `0x00445D08` |
| 1 | `0x0044666C` | `0x00445D95` |
| 2 | `0x00446670` | `0x00445E22` |
| 3 | `0x00446674` | `0x00445EAF` |
| 4 | `0x00446678` | `0x00445F68` |
| 5 | `0x0044667C` | `0x00446082` |
| 6 | `0x00446680` | `0x00445FF5` |
| 7 | `0x00446684` | `0x0044610F` |
| 8 | `0x00446688` | `0x004461AE` |
| 9 | `0x0044668C` | `0x00446256` |

A separate original-PE-only verifier
`scripts/verify-animation-quad-texture-states.py` reads the exact locked
original PE sections, checks every physical E8 displacement, the
**47+10** actual `.reloc` fields, all real case entry heads, the original
**36/10 indirect D3D9 calls**, the entire real function boundary and
three-byte alignment. It then compiles only this source and validates
all original code/data bytes and all COFF relocation fields independently
from the canonical strict replay.

## True original ten-mode renderer protocol, plus three sampler caches

The existing no-new-storage `AnimationQuadSubmitOwner` ECX receiver has
four real single-byte state caches at native offsets
`+0x6000E0C`, `+0x6000E12`, `+0x6000E13` and `+0x6000E14`.
The first compares `Animation+0x499` with the cached byte, flushes before
changing state, stores the new byte, makes **five genuine D3D9
SetRenderState** calls (`0x0F/0xCE/0xCF/0xD0/0xD1`), then selects one
of **ten real original code paths**. Each selected mode performs three
more SetRenderState calls, except mode 3 which performs four. The default
path shares mode zero's actual rendering values. The remaining sampler
cache gates independently inspect actual one-byte source fields:

- `Animation+0x4A0`, native bits **2..3**, updates sampler states **5 and 6**
  after a flush when owner `+0x6000E12` changes.
- `Animation+0x4A2`, native bits **0..1**, updates sampler state **1**
  according to its real original three-way branch when owner
  `+0x6000E13` changes.
- `Animation+0x4A1`, native bits **5..6**, updates sampler state **2**
  according to its separately real original three-way branch when owner
  `+0x6000E14` changes.

Original source then increments the genuine renderer counter at owner
`+0xC0`. These are true game-owned state transitions, not an invented
separate graphics singleton: each real setter calls the existing
`process_graphics.get_device()` and uses its authentic IDirect3DDevice9
vtable. The local `NativeRenderByteA1`/`NativeRenderByteA2` types in the
maintained `.cpp` are one-byte bitfield views of actual original
`AnimationFlags` data, with `sizeof ==1`, not persistent fields, copied
game memory or a new allocation. No public header/ABI was changed.

## Recovering the actual original compiler codegen, not trusting old hypotheses

The first complete semantic source emitted **2,793B/716 x86**, with a
full original-looking switch but genuine extra per-byte array-index
multiplications and branch temporaries. The actual initial alternative
uncommitted worktree source emitted **2,893B/742 x86**, and was preserved
in ignored `.analysis` as a rejected candidate rather than retained as a
second public owner definition.

A systematic isolated MSVC experiment showed that direct typed
single-byte fields and local **two-bit source view** operations restore
the native **`mov byte`, `shr/and byte`, `movzx`** sequences, instead of
compiler-expanded 32-bit arithmetic. Expressing the two three-state
sampler branches as genuine source `switch` statements recovers their
original stack-byte materialization, native comparison and conditional
branch topology. This recovered **2,725B/699 x86**, the exact original
number of bytes and instructions; however, the first whole-byte comparison
still exposed **four real nonrelocated byte differences**.

Those four differences were the actual `D3D_SET_RENDER` immediate values
for two distinct switch modes: immutable original `0x00445F68` physically
contains mode 4, then mode **6**, then mode **5**, before 7. An ordinary
C++ numerically ordered `case 5` then `case 6` generated identical total
machine-code length but placed those two cases in the wrong emitted
physical order. Reordering the *two entire semantic case blocks* to
**case 6 before case 5** resolves all four differences and restores
both actual original table destination identities. No arithmetic value
was falsified, no bytes were patched, and the original per-mode output
behavior is preserved.

The final pinned MSVC **19.44.35211 i386** `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` emits **exactly the entire real
2,768-byte original contribution**: **2,725/2,725B native game code**,
**699/699 original instruction heads**, **3/3 native padding bytes** and
**40/40 original ten-way pointer table bytes**, after full relocation
replay. All **107 COFF relocation entries** have the actual original
source symbol names, type, offset and independently original PE
physical target: 50 E8, 46 Graphics globals, one jump table operand
and ten table pointers. Zero extra nonrelocated byte differences remain.

## Protected scoped replay and accurate game-origin counting

The new canonical unit `animation_quad_texture_state_boss_2725` in
`config/match-units.toml` records `size = 2725` for original authored
game-function **code credit** and `compare_size = 2768` to require all
original table/alignment bytes too. Exactly one new compiler source/object
provider (`src/AnimationQuadTextureStates.cpp` →
`build/core819-canonical/AnimationQuadTextureStates.obj`) was cold built,
and **1/1 whole original strict unit** passed. No previously protected
canonical source, shared header, compiler flag, object or receipt was
changed; **zero old exact units** were in this change's build closure.
No unfiltered or repository-wide cold replay ran.

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-animation-quad-texture-states.py
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationQuadTextureStates.cpp
    scripts/repo-python scripts/validate-tracking.py --require-target

Game-authored whole-native strict code advances from **588 functions
/190,787 bytes** to **589 distinct original functions /193,512 code bytes**.
Source-present mappings advance **1,237 →1,238**, canonical strict units
**1,237 →1,238** and protected compiler object/receipt providers
**258 →259**. The 43 after-return bytes are not falsely counted as new
game instructions. The distinct 3,159B quad submit Boss retains its
separately original **40/40 E8 game call roles** but is **still NONEXACT**;
the 5,993B Animation draw parent and the 12,140B Bullet command parent
remain unfinished independently.
