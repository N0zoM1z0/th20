# CORE/EXACT-394 — complete 123B Bomb and 92B HitCtrlInf game factories

Comparison original: immutable Japanese TH20 v1.00a Steamless executable,
whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Two existing whole-but-nonexact, genuinely game-owned typed factory
functions have now been recovered as **215 disjoint complete original
native bytes**, with both entire original x86 functions strictly exact
in their existing maintained C++20 source owners. Neither exactness
nor ownership is based on an isolated matchable prefix, a guess at
what the compiler wanted, or a historical incomplete Ghidra range.

| Entire native game-owned factory | Native original entry | Full native bytes | Full x86 instructions | Native E8 / HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `th20::create_bomb_controller(int)` | `0x00478300` | **123/123** | **41/41** | **5 / 4** |
| `th20::create_hit_controller(int)` | `0x004C20D0` | **92/92** | **32/32** | **3 / 3** |

Entire independent original function SHA-256 values respectively:
`6b4a5a50b1f3b8ab9e717b76b78dfa73e62239467f0a86c021be1b6d7e8b2345`
and
`77311a242dcdab2184276758433e0e97d3dae49f7a8124c2a13229e7021d5c43`.

## Actual game resource semantics and independently original callers

The Bomb factory is an authentic TH20 game-controller operation:
native diagnostic `src/game/bomb.cpp:87 BombInf`, real
`DiagnosticAllocator::allocate_object<BombController>`, actual
`BombController::initialize(index)` at `0x00477DC0`,
and on success the native current `Session::context(index)`
at `0x0040BBC0` followed by
`Context::set_bomb_controller` at `0x0041DE90`.
Failure destroys/retires the allocated controller through the real
allocator's Bomb-specialized release at `0x0041F7C0`. Its
independent original caller at `0x004BAD40` participates in Player
bomb setup. These custom typed game objects, source-local diagnostic
and original caller establish game authorship, not linker or
compiler/STL-only origin.

The Hit controller factory is the matching actual game collision/
damage owner: diagnostic `src/game/hit.cpp:73 HitCtrlInf`,
`allocate_object<HitCtrlInf>` at `0x004BFDE0`, real
`HitCtrlInf::initialize` at `0x004C0B30`, and the same genuine
original allocator release at `0x0041F7C0` on failure. Its
independent original caller at `0x004FFFF0` is a gameplay setup
path. This factory had already been classified game-authored; the
Bomb factory's previously unknown/review origin is newly accepted
only after checking these independent production relationships.

## Why old complete C++ was short: error-cleanup control flow

The earlier maintained sources emitted **113/123** and **82/92**
native bytes. Each source correctly allocated and initialized its
owner, but a flattened if/return expression reduced the native
failure cleanup branch to one conditional jump and omitted the
original local-owner invalidation. The **real complete original**
does more:

- Null allocation returns null without constructing or publishing
  either controller.
- When initialization returns nonzero, control enters a common
  allocation **`cleanup:`** path that invokes the actual scalar
  release only for an allocated owner, then explicitly performs
  **`owner = nullptr`** to invalidate the now-retired local
  pointer, and returns null.
- Successful initialization returns the real owner. The Bomb
  success path first publishes it to the actual Context for the
  specified game index. The selected Context reference lives in
  the same real lexical scope as the success return, avoiding an
  unobserved post-publication NOP.
- The natural actual C++ error path uses
  `if (owner->initialize(index)) goto cleanup;`. This is a
  conventional resource cleanup flow, not a fabricated state
  machine branch, random NOP or unused local value.

Both original functions contain an otherwise **unreachable short
jump** following the initialization-result dispatch:
at Bomb original relative `+0x35`, and Hit relative `+0x33`.
Ghidra's current `body_addresses` exposes only **121** Bomb and
**90** Hit bytes because it does not count that branch head;
the original physical native functions are actually **123B and
92B**, including both internal jump encodings. The new C++ source
naturally emits those short jumps as part of the complete
failure cleanup flow. The strict original oracle compares both
full physically observed byte extents. No omitted native
instruction is ignored or counted as padding-only coverage.

## Independent original x86 and PE relocation audit

Original x86 E8 displacement operands and original `.reloc`
HIGHLOW sites were independently extracted from the **unmodified
original PE**, after the full 123/92-byte original instructions
were decoded. All **15 original relocation sites and native
destinations** agree with the actual freshly emitted COFF functions:

**Bomb (nine fields):**
- `+0x07` DIR32 `0x0056FACC`, native Bomb allocation diagnostic;
  `+0x0D` DIR32 `0x005B8894`, real allocator pointer.
- `+0x12` REL32 `0x00477960`, actual BombController allocation;
  `+0x2B` REL32 `0x00477DC0`, actual Bomb initialization.
- `+0x3C` DIR32 `0x005BA568`, actual Session global;
  `+0x41` REL32 `0x0040BBC0`, real Context lookup;
  `+0x50` REL32 `0x0041DE90`, Context publication.
- `+0x65` DIR32 `0x005B8894`, allocator pointer;
  `+0x6A` REL32 `0x0041F7C0`, real scalar Bomb release.

**Hit (six fields):**
- `+0x05` DIR32 `0x00570CC4`, native HitCtrlInf diagnostic;
  `+0x0B` DIR32 `0x005B8894`, allocator global.
- `+0x10` REL32 `0x004BFDE0`, actual Hit controller allocation;
  `+0x29` REL32 `0x004C0B30`, actual Hit initialization.
- `+0x46` DIR32 `0x005B8894`, allocator global;
  `+0x4B` REL32 `0x0041F7C0`, true Hit release.

Complete independently original evidence, including original
SHA-256 and compiler symbols/addends:
`.analysis/core394-original-factories-references.json`.
Existing independent native canonical symbol targets corroborate
both typed allocation, Session/Context, initialization and release
call interfaces. All native external offsets/types and original
targets agree. Both full functions were then admitted using
their original locked MSVC 19.44.35211 i386 C++20 compiler
profiles, not the structural diagnostic alone.

## Strict actual-source-only replay and accounting

The **only** real changed source inputs are
`src/BombCreation.cpp` and `src/HitCtrlInfCreation.cpp`.
No public header, object layout, compiler profile, linker-folded
helper, target PE or other exact source provider was modified.
They retain their original canonical owners
`build/core180-canonical/BombCreation.obj` and
`build/core180-canonical/HitCtrlInfCreation.obj`.

Exactly the **six** prior strict units owned by these two
source objects plus the **two** newly complete game-owned
factories were rebuilt and re-compared:
**8/8 strict units in two cold original objects**, including
Bomb context release, Bomb destroy/allocate and all three
existing Hit/Region allocation/initialization helpers.
The full filtered proof is
`.analysis/core394-bomb-hit-factories-replay.log`.
No unfiltered whole-repository cold replay was run.

This checkpoint adds **215 original game-authored exact bytes**,
**two new canonical strict units** and **zero duplicate source
object providers**. Other Bomb state update, character-specific
gameplay, Hit damage queries, allocator startup and full-game
binary linkage remain independent reconstruction work.
