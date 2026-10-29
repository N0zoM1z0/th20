# CORE/EXACT-696 — complete original 73B Animation allocation factory, one coherent class owner

**Original TH20 `0x00447800..0x00447848` is now full canonical native strict exact: 73/73 game-owned bytes.** This is a real maintained C++ implementation with three independently anchored original physical E8 destinations, not a private probe-only or an artificial compiler byte pattern. Previously exact large game-owned parents are preserved. Whole-game link/runtime remain outside this acceptance.

Original target: Japanese TH20 v1.00a Steamless `resources/th20.exe`, 1,858,560 bytes, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## True original complete game function and source

The immutable original function contains **73 bytes /22 x86 instructions**. It invokes `operator new(0x5E4)`, clears the complete allocation before construction, calls the real `Animation::Animation()` and returns a valid initialized game `Animation*`, or null on allocation failure. Its three independently decoded original E8 callee locations/physical destinations are:

| Original E8 field | Original physical callee | Provenance |
| --- | --- | --- |
| `+0x0F` | `0x0054275D` | Actual native `operator new`, independently used by previously strict-exact 67B AnimationFile factory |
| `+0x28` | `0x0040C080` | Native 31B compiler-generated `Animation::__autoclassinit2`, itself originally calls `_memset` at `0x00544760` |
| `+0x30` | `0x00448B40` | Complete already exact 498B `Animation::Animation` game object ctor |

The *complete exact original 298B game-owned Animation pool allocate/reuse boss* at `0x0044C9B0` physically E8-calls this original head at **`0x0044CAAE → 0x00447800`** on its new-allocation path. The original physical body is a game-authored instance of the game's diagnostic allocator template. The original 31B zero helper and original 498B ctor are distinct physical methods **not credited a second time**.

Canonical owner: newly maintained `src/AnimationFactory.cpp`, a natural explicit instance of `DiagnosticAllocator::allocate_object<Animation>(const char*)`, using the unchanged generic `new T()` template from `src/DiagnosticObjectFactories.hpp`. There is **no manual memset, C++ placement trick, dummy call, assembly, padding, forged object or patched MSVC binary**. The real game type stays one C++ class with authentic public fields and the same verified 0x5E4-byte layout. Under pinned MSVC i386 `/sdl`, `class Animation` causes the original class zero-initializer to be emitted automatically. The factory's real compiled body is **73B /22 x86**, exactly matching all **61 original non-relocated bytes**, with **three physical REL32 relocation fields** matching the independent original PE caller/callee anchors. The actual canonical comparator reports:

`animation_factory_whole_73: exact (73/73 bytes)`

The generated separate 31B automatic zero helper also has **27/27 identical original nonrelocated bytes**, plus the genuine original `_memset` E8 field. It is a shared compiler helper, not an additional 31 authored game bytes.

## Correct single class tag and no duplicated 60B factory body

Previous `struct Animation` was an incorrect type-tag hypothesis: under otherwise matching `/sdl` flags, the generic allocator produced only **60B** and omitted the original clear helper. Independently probing **seven real user-facing header declarations** with coherent `class Animation` restored native semantics, while preserving layout. Formal source edits now consistently use one legal declaration in:

- `src/Animation.hpp` (the single complete public `class Animation` with all original public fields/methods) and six true forward declarations: `AnimationHandle.hpp`, `AnimationCallback.hpp`, `AnimationFile.hpp`, `AnimationRuntimeOwner.hpp`, `EffectParameters.hpp`, and `RenderMesh.hpp`.

MSVC encodes that class-tag change in its **decorated symbols** (`UAnimation` → `VAnimation` and compressed `U12` → `V12`). The 298B `AnimationPoolOwner::allocate_animation` is compiled with `/GS-`, without `/sdl`. Its natural call would otherwise cause a separate **same-symbol 60B** instantiation and a potential linker/ODR conflict. The maintained pool source now has the ordinary C++ `extern template` declaration, so the pool object has **one undefined external** factory reference, and the standalone `/sdl` factory object provides **one defined 73B instance** under the same exact class symbol. This is a valid single owner, not two binary-compatible fake implementations.

The independent original 298B pool boss remains:

`animation_pool_allocate_whole: exact (298/298 bytes)`

The original 498B constructor remains `animation_ctor` strict exact, and the separately accepted **3,735B Bullet emitter boss** remains `bullet_emitter_whole_3735` strict exact with its complete 3,832B compiler/NOP/tables comparison.

## Whole pre-edit receipt closure, not whole-project cold replay

Crucially, the header change affects **seven** direct/forward header paths, not just the full `Animation.hpp`. Old pinned compiler receipt files were parsed **before** editing, identifying **117 previously accepted native object providers / 492 exact original units** (of 244 previous object providers / 1,186 prior whole canonical units). 55 of these native objects did **not** include the full Animation header and would have been missed by a 62-provider/284-unit-only replay.

Before touching the real headers, all **117 actual source TUs** were compiled in a private coherent-header shadow; each of the **492 complete original native methods** structurally matched the full original PE, with zero nonrelocated byte differences and unchanged physical relocation kinds/positions. Then the same **117 actual source providers were cold rebuilt in place** using their pinned original MSVC profiles and new real headers, with fresh hash-attested COFF receipts. The freshly generated real original PE/COFF byte audit again verified **492/492** previous native code bodies. Only compiler names changed:

- **30** canonical method definitions: class-tag-dependent function decorations;
- **186** genuine class-tag-dependent COFF relocation symbol names;
- **17** MSVC-private `$SG` string label identities, each independently verified by checking the newly compiled NUL-terminated string bytes against the unchanged *already anchored* original PE string at its original address.

The 233 manifest changes are **symbol-only** and preserve the actual previous original method byte lengths, target addresses, relocation offsets, kinds, original physical destinations and all unrelated units. After this audit, **all twelve serial, affected-only `--existing-objects` replay batches passed**: **492/492 original exact units /117/117 freshly cold MSVC objects**. The new 73B factory was separately `1/1` strict, so total affected scope is **493 strict native units**, not an unfiltered whole-graph cold replay. No previously accepted exact original body was dropped.

Reproducible ignored evidence:

- `.analysis/core685-animation-factory-compiler-tag-native-proof.py/json` — independent original 73B code, 31B helper and original physical relocations;
- `.analysis/core689-preedit-full-class-header-closure.json` — all seven header pre-edit compiler receipt include-closure, exact source/object/binary hashes;
- `.analysis/core687-shadow-original-audit-0.json`..`7.json` and `.analysis/core690-extra-shadow-original-audit-0.json`..`6.json` — private 492/492 full original strict-structure checks;
- `.analysis/core692-animation-class-cold-0.json`..`11.json` — **117 real canonical cold object/receipt rebuilds**, grouped by the affected old provider set;
- `.analysis/core693-animation-coherent-class-real-coff-audit.json` — real 492/492 original PE and native COFF code/field reconciliation, all 233 changes enumerated;
- `.analysis/core694-animation-class-verified-manifest-delta.json` — assertion that all pre-existing original target address, size, physical relocation offsets/kinds and physical target fields remain unchanged;
- `.analysis/core695-animation-class-strict-0.log`..`11.log` — actual 12 fully accepted native-original strict replays, no unfiltered cold replay;
- `.analysis/core696-animation-factory-complete-exact-proof.py/json` — whole 73B original E8, 31B auto-helper, 298B parent, one real linker-compatible factory definition and complete 492 old units.
- `build/core691-canonical/AnimationFactory.obj` plus its pinned MSVC source+header receipt.

## Conservative accounting

Previous game-authored exact count **503 / 179,538 original `.text` bytes** becomes **504 / 179,611**, adding exactly **one complete game-owned 73-byte original method**. The original 31B compiler helper, original 498B Animation constructor, original 298B pool boss and original 3,735B Bullet emitter are not added a second time. Configured native exact units increase from 1,186 to **1,187**, source-present functions from 1,184 to **1,185**, canonical COFF provider+receipt objects from 244 to **245**. Original class/compiler RTTI for every unrelated object is still not proven, and the game still cannot be claimed linked/playable. The 39,470B Animation VM and 12,140B Bullet command dispatcher are separate **NONEXACT** large original functions.
