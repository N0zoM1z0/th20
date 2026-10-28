# CORE/EXACT-361 — complete original 227-byte EffectInfo animation creation boss

The user-approved Japanese TH20 v1.00a Steamless original remains immutable,
whole-target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original whole `EffectInfo::spawn_effect` at `0x0049DB70..0x0049DC52`
is **227 native bytes, 78 complete x86 instructions**, original interval
SHA-256
`418378dae14cb2b39fc71607c7c611057b8a5030e654b531b1b5f8167fc6e097`.
It is now strictly exact in the **same real** `src/EffectQueue.cpp` object as
the already exact 143-byte producer and 271-byte frame consumer. Its original
original-source spelling is unknown; entire ABI and function body are
independently grounded in the actual PE and typed game objects.

## Complete resource table, creation branches, callback and result ownership

The routine uses its actual integer `kind` parameter to select a **32-byte
native effect-specification record** at original static table `0x005AFAB8`.
Real consumed record fields are signed 16-bit `file_index` at `+0`, signed
16-bit `script_index` at `+2`, and a function pointer at `+4` that accepts
an `Animation*`, a `const EffectParameters&` and a view index. The remaining
24 physical record bytes are preserved as explicitly **unclassified**
record data, not invented game states or artificial alignment. The
original data words of the first nine records were checked directly in
the immutable PE; the enclosing table's full record count and separate
initialization/lifetime are not claimed complete.

The caller supplies the real MSVC i386 hidden `AnimationHandle` return
buffer, kind, parameter reference, and optional **`Animation*`
`existing_animation`** pointer. The function constructs the actual
four-byte handle and calls the separately exact `clear_animation_handle_value`
at `0x0049DA50`, preserving the original natural source scope and one
original MSVC NOP at `+0x27`.

If `script_index` is negative, it returns the cleared handle. Otherwise:

- If `existing_animation` is null, it obtains an `AnimationFile*` from
  the real `EffectInfo::files[spec.file_index]` three-slot array. It
  creates an animation via the native 57-byte `AnimationFile::spawn`
  wrapper at `0x00450C70`, forwarding the **actual** signed script and
  current view index. The full four-byte hidden-result `AnimationHandle`
  is assigned by **natural whole-object copy**, not by a reordered
  `.value` field assignment. It then resolves the handle to the actual
  `Animation*` and invokes the existing, real
  `Animation::set_flag0_recursively()` at native `0x0044FA70`.
- If the caller supplies an existing `Animation*`, it skips allocation
  and uses the real `AnimationHandle::operator=(0)` while preserving the
  caller's animation pointer.
- In either case, if the specification's callback is nonnull, it calls
  that original function pointer with the animation pointer, actual
  `EffectParameters&` and current view index, using the native three
  `cdecl` arguments and caller cleanup. It returns the original hidden
  `AnimationHandle` result with `ret 0x10`.

The real signed script and view locals are both used in the spawn call.
Their natural `/Od` evaluation order restores the original native code;
inline expressions emit 216 instead of 227 bytes. A full-handle copy
restores the original three-register move order that a direct `.value`
assignment does not. No bogus free-function adapter, mock vtable, dummy
compiler-shaping local, fake return, inline assembly, copied instruction
bytes, manual NOP, or shortened exact range is used.

## Independent immutable-original relocation proof

A fresh original `E8` decode and the actual original `.reloc` table
independently establish **7 direct `REL32` calls and 1 `HIGHLOW/DIR32`
static table reference**. Their complete locations and native destinations
are:

| Original offset | Type | Original destination | Actual original role |
| --- | --- | --- | --- |
| `+0x10` | DIR32 | `0x005AFAB8` | original effect specification table |
| `+0x1B` | REL32 | `0x00425CC0` | AnimationHandle constructor |
| `+0x23` | REL32 | `0x0049DA50` | exact AnimationHandle value clear |
| `+0x51` | REL32 | `0x00414580` | three-file std::array index |
| `+0x84` | REL32 | `0x00450C70` | native AnimationFile spawn wrapper |
| `+0x93` | REL32 | `0x0044CED0` | actual AnimationHandle resolve |
| `+0x9E` | REL32 | `0x0044FA70` | genuine Animation recursive flag setter |
| `+0xAB` | REL32 | `0x004117A0` | zero-value AnimationHandle assignment |

All eight offsets/types/targets match the canonical COFF relocations
without guessing addresses from the reference field being compared.
The independently prepared private proof is
`.analysis/core361-independent-effect-spawn-refs.json`.
Pinned MSVC 19.44.35211 i386 `/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` now produces **227/227 original
strict exact bytes**, all **78 original instructions**, 195
non-relocated bytes and 32 independently attested relocated bytes.
The existing `Animation::set_flag0_recursively()` callee remains a
**separate** original 272-byte reconstruction, not credited as strict
whole-function exact by this caller's acceptance.

## Correction of prior +8 EffectRequest schema and scoped regression

The previously accepted 143-byte `EffectInfo::queue_effect` and 271-byte
`process_queued_effects` had been structurally/canonically exact while
incorrectly *naming and typing* request offset `+8` as a signed integer
`policy`. The earlier conclusion was **wrong**: this separately decoded
227-byte original consumer tests the corresponding argument for null,
passes its nonzero value as a true `Animation*` to a callback, and uses
its absence to decide whether to spawn a new animation. Thus
`EffectRequest+8` is again typed as **`Animation* animation`**, and the
request producer's final parameter and spawner's third explicit parameter
are typed `Animation*`. The independently established `+0xC` signed
delay count, `+0` type and `+0x10` 56-byte payload remain unchanged.

This ABI correction changes the **MSVC-decorated names** of the existing
queue and spawn calls in other original exact functions, not their
physical native targets or call offsets. Only five old canonical
symbol-reference occurrences were updated while retaining their original
independently attested `0x0049DB70`/`0x0049DC60` destinations, all native
relocation positions/types and original function extents. Specifically,
the entire 332-byte Player graze feedback, 2,018-byte Bullet collision,
662-byte Bullet cancel and the 143/271-byte queue/frame were recompiled
and remain strict exact.

Changes affect real `src/EffectParameters.hpp`, its existing constructor,
`src/ItemResourceOwners.hpp`, and `src/EffectQueue.cpp`; **no** broad
`src/Animation.hpp` declaration or layout was edited. Using **previous
canonical receipt include closures**, precisely **9 source providers
and 31 previously strict units** were affected. The new 227-byte whole
method adds one unit in the **same existing canonical EffectQueue object**.
All **32/32 strict units across 9 freshly built objects** passed in three
serialized low-priority batches of **7+9+16**; no full-graph cold replay
was run. Private evidence:
`.analysis/core361-impact-preedit.json`,
`.analysis/core361-replay-groups.json`,
`.analysis/core361-replay-batch{0,1,2}.log`.

This checkpoint establishes complete native game-owned function exactness;
it is not evidence for fully linked executable equivalence, a complete
Renderer/Animation lifetime, or the separately open Enemy/ECL and Bullet
large bosses.

## CORE/EXACT-362 separate alternate-spawn closure

The *different* complete **202-byte** EffectInfo spawner at `0x0049DCF0`
and its actual **55-byte** `AnimationFile::spawn_flag4` dependency at
`0x0049E080` are now separately strict exact, with native flag **4** and
fixed layer **-1**, and no recursive Animation flag setter after resolve.
These are distinct physical original functions, not extensions of the
already exact 227-byte spawner. See the
[complete alternate-spawn proof](EFFECT_SPAWN_FLAG4_VARIANT_EXACT_RECONSTRUCTION.md).
