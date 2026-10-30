# CORE/RECON-848 — original 2,136B Animation mesh24/25 renderer, strict exact

The locked Japanese TH20 v1.00a Steamless PE, SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897,
contains the complete original game-owned renderer at **0x00443020**.
Its enclosing 5,993B Animation Draw Boss calls it at 0x00443B4F,
0x00443B76 and 0x00443B9D. The native function has **2,136 bytes,
504 i386 instruction heads, frame 0x130, and ret 0xC** for Animation*,
mesh stream pointer and vertex count. No after-RET comparison data exists.

The natural typed source
[src/AnimationDrawMesh2425.cpp](../src/AnimationDrawMesh2425.cpp)
compiles under pinned MSVC 19.44.35211 x86 C++20
(/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc)
to a complete **2,136/2,136-byte zero-difference canonical strict match**.

## Independent original PE and canonical evidence

The immutable
[original-only PE verifier](../scripts/verify-animation-draw-mesh2425-native.py)
decodes the complete original 504 x86 instructions and reads the original
PE .reloc directory independently from compiled C++.

| Independently native-verified original | Whole maintained C++ |
| --- | --- |
| 2,136B /504 x86, frame 0x130, ret 0xC | **2,136/2,136 strict exact** |
| 32 genuine E8 call sites / original target heads | **32/32 matching physical offsets/targets** |
| 20 original HIGHLOW data fields | **20/20 original positions and target identities** |
| Non-relocated native bytes | **1,928/1,928 identical** |
| Complete relocation replay | **52/52 COFF fields; zero differences** |

The original data relocations include nine live Graphics global fields,
two WindowState globals, a real 64-byte identity matrix, three genuine
double-zero constants, two float-zero values, two float-one values and a
compiler cookie. The 32 direct calls include eight physical calls to folded
14B original matrix construction/identity getters at 0x0040BDA0;
three D3DX rotations and multiplies, two native window getter targets
0x0041CAD0/0x0041CAF0, seven Graphics device accessors, real texture
and sprite methods, D3D9 state changes and the compiler security checker.
The provisional C++ method names for the folded matrix/window accessors
are not claims about the historical original source spellings, and those
dependency bytes are not credited again.

## Corrections verified from original instructions

1. The original performs **two real matrix-address getter calls per axis**
   immediately before D3DX matrix multiplication. Directly taking the
   matrix address skipped six E8 calls, despite superficially similar math.
2. Actual receiver caches at +0x6000E08, +0x6000E18 and +0x6000E0E
   are accessed as typed member lvalues, not separately stored
   temporary pointers. This recovers the native stack frame, all 32
   physical E8 positions and all original machine instruction heads.
3. The original depth-write flag bit4 emits **SHR 4 / AND 1 / JNE**,
   falling through to enable depth write and branching to disable.
   Reordering the C++ if/else to the actual native flow fixes the jump.
4. The original two D3D9 texture-stage calls pass **(stage 0, state 6,
   value 0)** and **(stage 0, state 3, value 0)**. Initial source had
   confused state with value. Correcting true renderer semantics fixes
   the last four non-relocated bytes.

The original World and Texture0 transformations, material texture/cache,
FVF/state and native 24-byte-stride D3D triangle-strip draw are preserved.

## Exact-unit accounting and bounded reproduction

The single canonical unit **animation_draw_mesh2425_2136** points to
build/core848-canonical/AnimationDrawMesh2425.obj and its pinned
receipt. All 32 REL32 plus 20 DIR32 original physical sites and targets
are independently established, not solved from target bytes.

    animation_draw_mesh2425_2136: exact (2136/2136 bytes)
    Exact replay: 1/1 units, 1 cold objects

One transient duplicate match-unit was reconciled before admission.
There is **exactly one match unit and one authored credit** for original
0x00443020: **one new original game function /2,136 disjoint bytes**.
Live tracking becomes **602 game-authored exact functions /206,008 native
bytes; 1,248 source mappings /1,249 canonical units /267 providers**.
The 5,993B enclosing Draw dispatcher remains independently NONEXACT.

Only this new source/provider is cold-compiled and replayed, not all
canonical units or their existing source dependencies. Reproduce:

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-animation-draw-mesh2425-native.py
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMesh2425.cpp
    nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
    scripts/repo-python scripts/validate-tracking.py --require-target
