# CORE/EXACT-362 — two whole native effect-spawn paths: 202B alternate boss + 55B flag-4 wrapper

The original user-selected Japanese TH20 v1.00a Steamless game executable is
immutable, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Two **distinct entire native game-owned functions** in the EffectInfo
animation lifecycle are now separately **strict exact**. They share genuine
prior source owners without double-counting earlier whole functions:

| Complete original method | Original native entry | Extent | Original whole-function SHA-256 |
| --- | --- | ---: | --- |
| `EffectInfo::spawn_effect_variant` | `0x0049DCF0` | **202B, 70 instructions** | `ab61b2008b047362322b2270a7b0e9440836326d83466ce35a362b77bfd43d5f` |
| `AnimationFile::spawn_flag4` | `0x0049E080` | **55B, 24 instructions** | `13df5aed26f5f699e70df5caa37b1df86c17d40b8e44a86847176bb78879e1e5` |

These are **257 new, physically nonoverlapping original bytes**, 94 native
instructions, with independent immutable-PE reference audits and fresh
locked-compiler receipts. Earlier 227-byte `EffectInfo::spawn_effect`
(`0x0049DB70`) and its previous exact animation wrappers remain independent.

## Complete alternate 202-byte gameplay behavior

The source owner is the existing `src/EffectQueue.cpp`, with real
`EffectInfo`, `AnimationFile`, `AnimationHandle`, `EffectParameters` and
`Animation` types. The method indexes the *original* 32-byte native
`EffectScriptSpec` table at `0x005AFAB8` using the signed effect kind.
Native fields observed: 16-bit signed file index at +0, signed script
index at +2, optional three-argument callback pointer at +4. Other table
words remain explicitly unclassified; **no static table definition was
fabricated**.

It constructs and clears the hidden-result `AnimationHandle`. Negative
script indices return this cleared handle. Otherwise, when no existing
animation was passed, it accesses `EffectInfo::files[spec.file_index]`,
uses the *newly reconstructed* flag-4 wrapper to spawn from the native
16-bit script number, and resolves the real `Animation*`. When an existing
`Animation*` is supplied, it uses the genuine zero-handle assignment
and skips new animation allocation. Finally, the original optional
callback is called with (animation pointer, effect parameter reference,
view index), and the true `AnimationHandle` is returned using native
`__thiscall` aggregate/hidden-return ABI.

Unlike the distinct full **227-byte** original sibling at `0x0049DB70`,
the 202-byte alternate does **not** call
`Animation::set_flag0_recursively`. The two original entire control flows
are both independently exact, and the difference is preserved as a real
source distinction rather than a compiler-only stub.

## Complete native 55-byte AnimationFile flag-4 wrapper

`AnimationFile::spawn_flag4(const char*,int,Animation**)` is a real
five-argument original stack/hidden-return wrapper in the existing
`src/MeshResourceAccess.cpp` owner, where its sibling spawn wrappers
already live. It naturally forwards to the actual seven-argument
`AnimationFile::spawn` at `0x00450CB0` with null position, 0.0f
rotation, draw layer **-1**, creation flag **4**, and the original
script/stem/output parameters. Its **55/55 native bytes and all 24
instructions** are exact using that object's existing locked **C++17
`/fp:strict`** profile, verified separately rather than silently changing
the owner to the C++20 profile used for EffectInfo.

## Independently observed native relocations

The 202B original contains exactly **six E8/REL32 direct calls plus one
actual PE `HIGHLOW`/DIR32 static table field**:

| Original field | Type | Original target | Actual role |
| --- | --- | --- | --- |
| `+0x10` | DIR32 | `0x005AFAB8` | native EffectScriptSpec table |
| `+0x1B` | REL32 | `0x00425CC0` | AnimationHandle constructor |
| `+0x23` | REL32 | `0x0049DA50` | complete exact handle value clear |
| `+0x51` | REL32 | `0x00414580` | three-file array index |
| `+0x74` | REL32 | `0x0049E080` | whole exact flag-4 spawn wrapper |
| `+0x83` | REL32 | `0x0044CED0` | actual handle resolve |
| `+0x92` | REL32 | `0x004117A0` | native handle assignment |

The 55B wrapper has a single `E8/REL32` field at original **`+0x2A ->
0x00450CB0`**. The original PE `.reloc` and `E8` displacements were
extracted independently *before* manifest acceptance, and all eight
original fields exactly match the actual COFF symbols, offsets, types
and relocated native destinations. Complete original evidence:
`.analysis/core362-original-0049dcf0-refs.json` and
`.analysis/core362-original-0049e080-refs.json`. Every full native byte
is accepted under strict canonical replay, not merely opcode mnemonic
alignment or a structural-matching diagnostic.

## Strict cold replay restricted to actual receipt include closures

The only shared interfaces changed were `src/AnimationFile.hpp` and
`src/ItemResourceOwners.hpp`, declaring real methods without changing
sizes/offsets. The implementations were added to their **existing
canonical source objects**, `src/MeshResourceAccess.cpp` and
`src/EffectQueue.cpp`; no new object provider or fake owner was created.

The actual *previous* compiler receipt include closures selected exactly
**52 existing source providers, 237 old strict units**. The two new
complete original functions add two units, giving **239/239 strict
units across 52 freshly cold-built original owner objects**, passing
11 serialized, reduced-priority batches of
**63+8+7+37+18+20+39+18+7+11+11**. The previous exact original
227-byte spawner, 271-byte frame, 143-byte producer, 332-byte graze
caller, Bullet cancel/collision and other large roots remain exact.
**No unfiltered all-repository cold replay was run.**

Twelve MSVC compiler-private `$SG` identities in eight existing exact
units renumbered after header changes. They were reconciled **only**
after checking the current object/receipt hashes, equal native
nonrelocation bytes, unchanged independent original PE addresses,
unchanged relocation offsets and types; then each unit was reaccepted
by the unchanged strict oracle. Private audit:
`.analysis/core362-reconciled-private-symbols.json`; receipt scope:
`.analysis/core362-affect-original-headers.json` and
`.analysis/core362-replay-groups.json`; full strict logs:
`.analysis/core362-replay-batch0.log` through `batch10.log`.

The alternate route is complete at its 202B game-owned entry, but other
large EffectInfo initialization/destruction functions, native table
lifetime, 1,518B Player options boss, and whole executable linking/
runtime equivalence remain independent open work.
