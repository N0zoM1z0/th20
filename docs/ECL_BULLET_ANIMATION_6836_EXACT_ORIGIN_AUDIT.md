# CORE/ORIGIN-555 — twenty-one full original ECL, Bullet, Animation and game-owner functions, 6,836 bytes

Immutable source of truth: Japanese TH20 v1.00a Steamless original
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Twenty-one whole original game/project-authored native methods,
6,836 distinct physical game-body bytes and their full original compiler
contributions are now formally admitted as authored exact.** Every one
was already maintained as real C++20 game source and a fully exact
canonical native unit; their remaining status was `origin=unknown,
disposition=review`, not unknown source byte identity. This is an
independent origin/provenance audit of those complete functions, not
a claim that twenty-one new C++ sources were typed during this step.
The parallel new work on the **3,111B Player main-frame boss** is
[documented independently](PLAYER_FRAME_3111_GAMEPLAY_ABI_CORRECTION.md)
and remains NONEXACT.

## Entire original methods, not folded child fragments

| Native physical original | Whole game body | Real project-specific source / role |
| --- | ---: | --- |
| `0x004A74D0` | **556B** | `EclFileLoader::load` — duplicate file, actual ECL source resource cache and PMR storage |
| `0x004B9C10` | **473B** | `Configuration::Configuration` — true TH20 game config defaults |
| `0x004F49C0` | **440B** | `PlayerOption::PlayerOption` — real 300B Option state construction |
| `0x004F4CB0` | **413B** | `PlayerShot::PlayerShot` — original Player shot parameters and nested state |
| `0x0047B8A0` | **386B** | `BulletController::BulletController` — real bullet intrusive active/free lists and state |
| `0x00486BB0` | **348B** | `Card::Card` — original card effects, item/Animation handles, typed game fields |
| `0x004C22E0` | **330B** | `ItemInf::ItemInf` — whole original game-owned item controller constructor |
| `0x004A2E80` | **312B** | `EnemyController::EnemyController` — original enemy controller arrays and resource lifetime |
| `0x00422F20` | **298B** | `PlayerTable::PlayerTable` — actual Session-owned two-view player records |
| `0x004C21B0` | **298B** | `Item::Item` — original reusable 0x58 item records and list ownership |
| `0x004F4B80` | **291B** | `PlayerShotController::PlayerShotController` — Player-owned real shot array |
| `0x0053E970` | **287B** | `EclRuntime::float_argument` — actual ECL payload words/stack reference protocol |
| `0x00539060` | **284B** | `archive_lzss_insert` — original game LZSS match-tree insertion/search |
| `0x0044F2C0` | **272B** | `Animation::set_flag_4b4_recursively` — typed child-list recursion |
| `0x0044FA70` | **272B** | `Animation::set_flag0_recursively` — typed child-list recursion |
| `0x0044F170` | **272B** | `Animation::clear_flag_4b4_recursively` — typed child-list recursion |
| `0x00450160` | **272B** | `Animation::clear_flag0_recursively` — typed child-list recursion |
| `0x0053F260` | **265B** | `ScriptStack::push` — typed ECL stack-growth and byte/word write protocol |
| `0x0053EB70` | **261B** | `EclRuntime::consuming_float` — original ECL float argument stack consume |
| `0x0047BB90` | **255B** | `ShotMetadata::ShotMetadata` — actual Bullet/ECL shot command metadata |
| `0x00498A80` | **251B** | `EnemyController::find` — real Enemy handle lookup, ECL native callers |

All twenty-one original whole body regions are physically disjoint
from each other and from the **476 previously credited** game-authored
original ranges. Their real C++ lives in **fourteen already canonical
source providers**: `src/AnimationChildren.cpp`, `ArchiveLzssTree.cpp`,
`BulletController.cpp`, `Card.cpp`, `ConfigurationValue.cpp`,
`DamageQueryProtocol.cpp`, `EclArguments.cpp`, `EclFileLoader.cpp`,
`EnemyControllerConstruction.cpp`, `Item.cpp`, `PlayerStorage.cpp`,
`ScriptStackCopy.cpp`, `Session.cpp` and `ShotMetadata.cpp`.
No public header, existing C++ source, recipe, output offset or linker
folded original symbol was changed to obtain this exactness.

## Independent original call graph and confidence

Every original function head was matched against actual native
`E8` instructions decoded from the immutable game `.text`, rather
than accepting old proposed names as provenance. Examples:

- Already accepted **11,110B entire `EclRuntime::tick`** at
  `0x0053B5C0` contains **35 direct E8s** to the 287B float
  argument interpreter, **45** to the 265B script stack push and
  one to the 261B consuming-float interpreter. These are true runtime
  gameplay/parser operations, not generic CRT code.
- The independently exact full **1,036B** LZSS compression boss
  `0x00539550` has the genuine native E8 at `0x00539898` calling
  the **284B** dictionary/match-tree insert at `0x00539060`. Its
  last-turn exactness [is recorded here](ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md).
- Original **41,967B Enemy ECL dispatcher** at `0x0048C010` calls
  both the 255B `ShotMetadata` constructor and the **251B** Enemy
  lookup multiple times. The giant dispatcher is **not** itself
  native exact; its independently decoded calls into these real
  game-owned callees still attest their game role.
- Separately whole-exact **794B** `Player::Player` invokes the
  **291B** PlayerShotController constructor at original
  `0x004F496E`. The original `Session::Session` constructs the
  298B two-view `PlayerTable`. The whole-exact 941B Graphics
  constructor directly invokes the 473B Configuration constructor.
- The four 272B Animation child-recursion methods call their own
  physical original heads and are also called by independent game
  effect, RenderMesh and Animation visibility controllers, including
  the whole exact 227B `EffectInfo::spawn_effect` and 878B RenderMesh.

**Thirteen** roots have independently observable original gameplay
caller relationships and receive **high** original authored
confidence. **Eight** have **medium** provenance: the EclFileLoader
load function has no discovered incoming direct E8, as do the
PlayerOption and Item constructors; the PlayerShot, BulletController,
Card, ItemInf and EnemyController constructors are reached from
anonymous original 73–92B factory wrappers whose exact ownership is
not fully established. All eight are still project-specific game
classes rather than default STL/CRT methods; absence of an incoming
`E8` in the current provisional boundary inventory is not proof of
unreachability or of library origin. No incoming-call conclusion is
silently upgraded to high confidence.

Original exact caller counts, each original call site and its caller
size/source/status are stored in
`.analysis/core554-ecl-bullet-animation-21-original-callers.json`.

## Independent whole native PE byte, call and `.reloc` proof

The complete **6,836 original game-body bytes** decode to **1,829
original i386 instructions** through every original native last
instruction. In total, their original complete MSVC compiler
contributions span **6,876 bytes**: **40 genuine additional compiler
alignment/`CC` bytes** are compared in full but not re-credited as
original game-authored function bytes. The original PE provides:

- **187 original direct E8 call fields**, resolved by decoding
  the independent original instruction's signed relative displacement.
- **62 actual HIGHLOW absolute fields** independently recovered from
  the immutable original PE's genuine `.reloc` blocks, including
  original game constants, global pointers and EH/switch contribution.

**All 249 original field positions, kinds and original absolute
destinations** match the already pinned MSVC COFF relocation symbol,
manifest original anchor and ordinary linker addend. Every
remaining original nonrelocated byte matches the freshly compiled
natural source at the original offset. Code instruction count, whole
physical size and attached alignment are separately checked for
**all 21/21** original functions. There is no shortened comparison,
missing instruction, fabricated global, candidate-derived PE target,
shared library alias double credit or compiler byte patch.

Complete original body hashes, original E8 and HIGHLOW field
positions/destinations, original code and attached alignment extents,
per-unit original instruction counts and physical no-overlap evidence
are retained in `.analysis/core553-ecl-bullet-animation-21whole-original-pe.json`
and `.analysis/core553-ecl-bullet-animation-native-original-audit.log`.

## Focused fresh exact replay and ledger scope

Only the **fourteen real source/object providers** listed above were
cold rebuilt under their **existing pinned MSVC 19.44.35211 x86
source-specific profiles**. Existing-object replay with an explicit
fourteen-source filter proved **122/122 full original strict native
units exact**, including the 21 newly game-origin-admitted bodies,
other previously accepted shared state and callback helpers, and
original constructors in those same objects. This is a scoped replay,
**not** an unfiltered cold replay across the 1,182-unit graph.

Fresh real compiler receipts, 14-source selection and exact native
replay evidence are in `.analysis/core552-ecl-bullet-animation-fourteen-source-build.log`,
`.analysis/core552-ecl-bullet-animation-fourteen-source-build.json`
and `.analysis/core552-ecl-bullet-animation-fourteen-source-replay.log`.

**Authored original exact coverage rises from 476 whole functions /
168,855 bytes to 497 whole functions / 175,691 nonoverlapping original
body bytes.** The total **1,182 canonical strict units**, **242 unique
compiled source/object providers** and **1,181 source-present whole
function mappings** remain unchanged because each selected function
already had existing source and canonical native whole-byte proof,
but was waiting for actual original project-authored origin evidence.

The independent **41,967B Enemy ECL dispatcher** is still NONEXACT,
despite its original direct calls into these children. The
3,111B Player main frame, 555B Player movement, 3,735B Bullet emitter,
39,470B Animation VM and native 73B Animation factory are also
independent unresolved full functions. The original game runtime,
whole PE linkage and unsafe-input behavior are not established by
this source-origin checkpoint.
