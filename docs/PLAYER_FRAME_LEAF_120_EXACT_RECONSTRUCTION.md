# CORE/EXACT-510 — four Player-frame-dependent game leafs: 120 whole original bytes

Immutable comparison target: Japanese TH20 v1.00a Steamless,
`resources/th20.exe` SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Four complete, independently disjoint game-authored original functions**
previously had C++ source and strict canonical MSVC units but remained
origin-pending. The original 3,111-byte Player main frame at
`0x004F9C30` and independent other gameplay callers establish their
real game roles; newly admitted authorship contributes **four functions
and 120 nonoverlapping original body bytes**. Neither the 3,111B main
frame nor its separate 555B movement child is byte-exact, and no partial
piece of either whole parent is credited.

## Four newly origin-verified entire native bodies

| Original entry | Whole native bytes | Actual semantic owner and original Player main-frame call |
| --- | ---: | --- |
| `0x00449430` | **45** | `EffectAnimationHandle::matches_value(uint32_t)` — genuine handle-word equality predicate, Player original direct E8 at `0x004FA273` |
| `0x0041CAD0` | **17** | `Context::effect_info()` — actual Context+0x20 game effect resource, Player original E8 at `0x004FA288` |
| `0x0045D100` | **38** | `EffectInfo::animation_file(int)` — indexed actual three-file resource storage, Player original E8 at `0x004FA29B` |
| `0x00478080` | **20** | `EnemyController::count()` — signed native controller+0x124 active enemy count, Player original E8 at `0x004FA0EF` |

Their natural maintained C++ lives in `src/ItemLifecycleAccess.cpp`
(three bodies) and `src/EnemySpawning.cpp` (one body), with original
types from `ItemResourceOwners.hpp`, `Context.hpp`, `EnemyController.hpp`,
`AnimationHandle.hpp` and real Player/Enemy game owners. Existing
`effect_select_handle_slot()` also calls original handle-word equality
at `0x00449430`; independent original user functions in resource,
card and effect controllers invoke these same physical functions. The
original whole 45-byte equality function is **not** the 45-byte
`AnimationHandle::operator!=` inequality function: those compile to
opposite original conditional branch senses (`jne` versus `je`) and
cannot be treated as byte-identical ICF aliases just because both
are boolean word comparisons. The 3,111B parent still has an
outstanding exact call-target/protocol difference there.

The original complete `EffectInfo::animation_file` uses exactly **one
E8** call field at `0x0045D11A` targeting the native `0x00414580`
array index operation. The other three complete bodies have **zero
E8 calls and zero PE HIGHLOW relocations**. Independent Capstone
entire-return verification finds **15, 9, 15 and 9** instruction
heads respectively, and all four emit precisely identical ordinary
(non-relocated) original bytes in the pinned C++ objects. Actual
original E8 and PE `.reloc` fields and native destinations are parsed
from the immutable original, not inferred from candidate byte values.
The four functions do **not overlap** any previously credited authored
function or each other.

## Exact typed option-iteration ICF without duplicate native credit

The original Player main frame has **two** direct E8 calls to
`0x0040BDA0`, at `0x004FA793` and `0x004FA7EB`, during the primary and
secondary PlayerOption loops. Entire original physical body at that
address is **14 bytes**:
`55 8B EC 51 89 4D FC 8B 45 FC 8B E5 5D C3`.

The two existing typed compiler instantiations of
`PlayerValues<PlayerOption,10>::begin()` and
`PlayerValues<PlayerOption,12>::begin()` both emit **exactly these
14 bytes / no relocations**, verified from the freshly retained whole
MSVC object `build/core320-canonical/PlayerOptionManagement.obj`.
Both expressions naturally return the actual first address of the
existing contiguous PlayerOption arrays. The physical original
`0x0040BDA0` was previously mapped under a generic Motion getter;
its original source symbol / exact historical ICF setting is not
established by this observation. This is independent **native
linker-folded role evidence**, not a fifth physical exact credit and
not proof that the enclosing 3,111-byte parent is complete machine-code
exact. The original copy/iteration register lifetimes remain open.

## Whole original code/strict replay scope

The source and public headers are **unchanged** in this checkpoint.
Because older compiler receipts were stale, only two canonical native
object providers were freshly cold built under their **existing**
locked MSVC 19.44.35211 x86 profiles:
`build/core178-canonical/ItemLifecycleAccess.obj` and
`build/core178-canonical/EnemySpawning.obj`. All **20/20 configured
whole original units** in these two source providers passed genuine
native strict replay with fresh input-hash receipts. No full cold
replay, cropped comparison range, NOP patch, fabricated relocation,
manual assembly or artificial local variable was added.

Independent original caller audit found **22 direct E8 calls** to
`0x00449430` across 21 original functions, **35** to the Context
resource getter across 21, **13** to `EffectInfo::animation_file` across
10, and **six** to EnemyController count across six. The precise whole
original code hashes, original E8 locations/targets, PE HIGHLOW
references, native original caller census, disjointness proof, and
folded begin bytes/calls are saved in ignored
`.analysis/core510-player-leaf-and-fold-proof.json`, with the
source-scoped cold replay in
`.analysis/core510-leaf-20unit-strict-replay.log`.

**Authoritative authored coverage** grows from **437 whole exact
functions / 143,806 bytes** to **441 / 143,926 disjoint original
bytes**. The **1,177 configured canonical units, 237 distinct old
compiler source/object providers and 1,177 source-present function
mappings** do not increase: these source files and complete unit
receipts already existed, only the independently proven original
**game-authored classification** and match ledger admission were
pending. No new original assembly bytes are credited for the folded
`PlayerValues::begin` examples, and none of the big original Player
parent is claimed exact. The full Player parent remains documented in
[the maintained 3,111B source frontier](PLAYER_MAIN_FRAME_3111_TYPED_SOURCE_FRONTIER.md).
