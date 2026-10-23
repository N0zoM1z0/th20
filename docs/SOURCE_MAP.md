# Source and build ownership

Production declarations and implementations live in `src/`. Each owner has one
canonical declaration and one semantic body independent of its compiler profile.
Translation-unit placement is maintained build ownership; it does not establish
the original game's translation-unit partition.

## Navigation

| Protocol | Maintained source | Focused evidence |
| --- | --- | --- |
| Animation lifetime/parameters | Animation.hpp/cpp, AnimationFile.hpp/cpp, AnimationParameters.cpp | [Lifetime](EXACT_ANIMATION_LIFETIME_RECONSTRUCTION.md), [File/template arrays](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md), [PMR retirement](ANIMATION_PMR_RETIREMENT_RECONSTRUCTION.md), [descriptors/binding](ANIMATION_DESCRIPTOR_RECONSTRUCTION.md) |
| Animation traversal/templates | AnimationChildren.cpp, AnimationBinding.cpp, AnimationFile.hpp/cpp | [Children](ANIMATION_CHILDREN_RECONSTRUCTION.md), [binding](ANIMATION_BINDING_RECONSTRUCTION.md) |
| Animation frame/geometry/operands | AnimationUpdates.cpp, AnimationGeometry.cpp, AnimationOperands.cpp | [Updates](ANIMATION_UPDATE_RECONSTRUCTION.md), [geometry](ANIMATION_GEOMETRY_RECONSTRUCTION.md), [operands](ANIMATION_OPERAND_RECONSTRUCTION.md) |
| Animation callback protocol | AnimationCallback.hpp/cpp, Bullet.hpp, BulletStyle.hpp | [Callbacks](ANIMATION_CALLBACK_RECONSTRUCTION.md) |
| ECL stack/runtime/manager/loader | ScriptStack*, EclRuntime*, EclManager*, EclLoader*, EclFileLoader* | [Whole tick](EXACT_ECL_TICK_RECONSTRUCTION.md), [call protocol](EXACT_ECL_CALL_RECONSTRUCTION.md), [buffers](ECL_BUFFER_RECONSTRUCTION.md) |
| Enemy movement/script/parameters | Enemy*, Motion*, ShotMetadata*, Laser* | [Movement](EXACT_ENEMY_UPDATE_RECONSTRUCTION.md), [whole dispatcher](CORE_ENEMY_DISPATCH_LAYOUT.md), [temporaries](EXACT_ENEMY_TEMPORARY_RECONSTRUCTION.md) |
| Scheduler/observation/locking | FunctionChain*, IntrusiveLink*, LockRegistry*, DiagnosticAllocator* | [Scheduler](FUNCTION_CHAIN_CONTROLLER_RECONSTRUCTION.md), [allocation/release](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md), [iteration](CORE_ITERATION_EXACT_RECONSTRUCTION.md) |
| Gameplay ownership/damage | Player*, Bomb*, Bullet*, Item*, Context*, Session*, Damage*, HitCtrlInf* | [Player/SHT](PLAYER_SHT_RECONSTRUCTION.md), [Bomb](BOMB_OWNER_RECONSTRUCTION.md), [Item](ITEM_OWNER_RECONSTRUCTION.md), [damage](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md), [Region allocation/ownership](DAMAGE_REGION_ALLOCATION_EXACT_RECONSTRUCTION.md) |
| Archive/File/resource I/O | Archive*, PbgFile*, GameFileIo*, GameResourceIo* | [Resource graph](ARCHIVE_RESOURCE_EXACT_RECONSTRUCTION.md), [writing](ARCHIVE_WRITE_RECONSTRUCTION.md) |
| Progress persistence | Progress*, SecureCrt.hpp | [File protocol](PROGRESS_FILE_EXACT_RECONSTRUCTION.md), [loading/lifetime](PROGRESS_LOAD_LIFETIME_EXACT_RECONSTRUCTION.md), [parser](PROGRESS_FILE_PARSE_RECONSTRUCTION.md) |
| Graphics/mesh/sound | Graphics*, RenderMesh*, MeshResourceAccess*, SoundInf.hpp, SoundLoading.cpp | [Texture formats/accessors](ANIMATION_TEXTURE_FORMAT_RECONSTRUCTION.md), [mesh](RENDER_MESH_RECONSTRUCTION.md), [mesh flags](MESH_FLAGS_EXACT_RECONSTRUCTION.md), [sound](SOUND_PROTOCOL_RECONSTRUCTION.md) |
| Shared math/time/random | Vector*, Angle*, Timer*, ClockScalar*, Interpolation*, GameRandom* | [Interpolation](EXACT_INTERPOLATION_RECONSTRUCTION.md), [random/locks](EXACT_LOCK_RANDOM_RECONSTRUCTION.md) |
| Platform/UI/value components | Window*, Input*, Cursor*, text/flags/record owners | [Reference evidence index](EVIDENCE_INDEX.md) |

Bullet type/color accessors and its script callback currently share
AnimationCallback.cpp. OverlayCounter::add_reward lives in Item.cpp and uses the
real Item controller. These are actual maintained definitions, not undefined
fixture interfaces. AnimationEntryCallback describes the observed VM-entry hook;
the former Hit label had no evidence for a collision trigger.

## Authoritative ledgers

| File | Records |
| --- | --- |
| config/functions.csv | Provisional target boundaries and reviewed status |
| config/function-origins.csv | Authored/compiler/library classification |
| config/reccmp-functions.csv | Unique physical source mappings |
| config/implemented.csv | Source-presence list |
| config/matches.csv | Confirmed authored exact functions |
| config/match-units.toml | Complete physical units, source/object/profile/symbol/extents/anchors |
| config/reference-function-reviews.csv | Hash-bound reference implementation decisions |

Read these ledgers rather than inferring coverage from file names or a header's
method declarations. An accepted caller may call an independently anchored,
undefined dependency. A folded implementation can explain several semantic
roles without duplicate physical credit. Runtime/library units do not silently
become authored exact functions.

The current handoff and generated progress separate physical strict units,
mapped whole nonexact functions and authored coverage. Private diagnostic/support probes
are not production admission. File::clear and the two Renderer texture creators
have reviewed authored origins without maintained bodies or source mappings.
The full AnimationFile spawn producer also remains source-absent. The five existing MeshResourceAccess helper
origins are reviewed in [the resource audit](MESH_RESOURCE_ORIGIN_AUDIT.md).
EnemyMesh.cpp owns nested mesh retirement and typed scalar release;
MeshInterfaces.cpp owns EnemyMeshOwner value allocation and emits the defaulted
constructor. See [ownership](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md) and
[allocation evidence](ENEMY_MESH_ALLOCATION_EXACT_RECONSTRUCTION.md).
MeshResourceAccess.cpp owns the parameterized RenderMesh scalar factory under its
verified C++17 profile; see [allocation evidence](MESH_ALLOCATION_EXACT_RECONSTRUCTION.md).
Graphics accessors fold to existing physical units without duplicate credit.
The actual File destructor also emits complete SDK string-retirement units;
their library/compiler origins remain separate from authored exact coverage.
Do not use stubs or forced unresolved linkage to claim a whole-program product.

PbgFileAllocation.cpp owns the scalar Pbg::File factory under its verified local
profile without /EHsc; PbgFile.cpp retains the File/IFile methods and destructor
EH profile. Archive, Progress, Player SHT and DamageQuery fixtures link this provider. See
[allocation profile and admission](PBG_FILE_ALLOCATION_PROFILE.md).

EclRuntimeLifetime.cpp owns both Runtime and asynchronous-node scalar factories.
IntrusiveLink.hpp exposes the same five-pointer protocol through a public class
declaration; native layout and noexcept construction are preserved. The complete
ECL fixture uses production node allocation. See
[node allocation](ECL_NODE_ALLOCATION_EXACT_RECONSTRUCTION.md).

Animation.hpp declares the actual 65,536-record AnimationPool; Animation.cpp owns
its construction, defaulted destruction and the shared slot lifetime. The full
owner fixture uses real geometry/callback retirement. See
[pool lifetime](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md).

GameRandomStream.cpp owns the complete raw uint16 sampler alongside next/seed.
It advances the engine under the same real mutex and bypasses modulus division.
The Enemy movement opcode candidate remains private whole-root source work;
it is not an implemented production dispatcher or a separate exact unit. See
[movement source frontier](ENEMY_DISPATCH_MOVEMENT_RECONSTRUCTION.md).
EnemyInitialization.cpp owns the complete phase/timeout producers; EnemyState.hpp
retains implicit member defaults for life/time and both complete name arrays.
The original private constructor guess is superseded by independent evidence
from value construction and complete strict replay. See
[phase protocol](ENEMY_PHASE_PRODUCER_INVESTIGATION.md).
Session.cpp owns the field70 predicate and mutating field1F4 queries;
PlayerRecord.cpp owns the wrapping fieldDC/E0 updates. These support four more
paths in the same private whole-dispatcher draft. See
[state opcode frontier](ENEMY_DISPATCH_STATE_RECONSTRUCTION.md) for source and
fixture boundaries; the production dispatcher remains undefined.
EnemyPattern.cpp owns the count/kind/duration/radius operations; ItemSpawn.cpp
owns the complete drop and scatter protocols alongside the real Item producer.
Enemy.cpp owns the actual entity flag query. Seven complete dependencies are
strict exact; the full scatter source remains 628/native630 and nonexact. The
same private dispatcher draft includes all nine observed callers. See
[drop protocol](ENEMY_DROP_PROTOCOL_RECONSTRUCTION.md).
EnemyData.cpp owns checked selected-slot publication, scalar handle assignment
and the Data flag-bit write; EnemyHealth.cpp owns raw-health reads and scaled
writes. The current private dispatcher also includes life, boss, bounds and
timer paths. Scalar-return and checked-helper emission remain separate open
boundaries. See [health and boss state](ENEMY_HEALTH_BOSS_STATE_RECONSTRUCTION.md).
Card.cpp owns three complete flag requests/writes; EnemyHealth.cpp owns scaled
mode selection. Card.hpp declares the genuine resource-owning start/finish
interfaces, whose full bodies remain undefined. Ten more private dispatcher
paths preserve decoding, live metadata and post-call health/Timer sequencing.
See [Card caller protocol](ENEMY_CARD_STATE_RECONSTRUCTION.md).

## Build freshness and local products

Use scripts/repo-python, the compile wrapper and recorded per-source profiles.
Canonical products and their receipts are ignored build artifacts; their current
paths come from match-units.toml. Shared source/header changes require affected
fresh compilation and strict replay. Preserve original SHA-bound input archives
before retiring superseded products. See [oracles](ORACLES.md) and
[build/matching](BUILD_MATCHING.md).

EnemySpawning.cpp owns four complete Controller clear variants over the real
observer list; EnemyState.cpp owns the bit30 query. Enemy.hpp declares the genuine
whole defeat boundary. EnemySpawnApplication.cpp now maintains its complete
source candidate; canonical relocation/EH acceptance remains pending. Six integrated clear,
selection and return paths extend the same private whole-root candidate; see
[clear protocol](ENEMY_CLEAR_PROTOCOL_RECONSTRUCTION.md).

EnemyController.hpp now uses the native normalized Angle at +128. Enemy.cpp
forwards animation-file lookup through the actual Context/Controller, whose full
resource dispatcher remains undefined. ItemResourceOwners.hpp separates the
identified file pointers from scalar cursor words; ItemLifecycleAccess.cpp owns
the complete effect-handle selection and tagged publication protocol. See
[defeat resources](ENEMY_DEFEAT_RESOURCE_RECONSTRUCTION.md).

WeaponStoneInfo.hpp declares the independently identified 0xB4 StoneEnemyController;
WeaponStoneInfo.cpp owns its construction, byte getter and process-slot access.
Player.cpp, PlayerStorage.cpp, PlayerRecord.cpp and GeometryMetrics.cpp own the
remaining maintained defeat dependencies. These ten complete source candidates
have no new ledger or exact credit yet. See
[whole defeat source and acceptance boundary](ENEMY_DEFEAT_RECONSTRUCTION.md).
