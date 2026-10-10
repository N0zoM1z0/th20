# Source and build ownership

Production declarations and implementations live in `src/`. Each owner has one
canonical declaration and one semantic body independent of its compiler profile.
Translation-unit placement is maintained build ownership; it does not establish
the original game's translation-unit partition.

## Navigation

| Protocol | Maintained source | Focused evidence |
| --- | --- | --- |
| Animation lifetime/parameters | Animation.hpp/cpp, AnimationParameters.cpp | [Lifetime](EXACT_ANIMATION_LIFETIME_RECONSTRUCTION.md) |
| Animation traversal/templates | AnimationChildren.cpp, AnimationBinding.cpp, AnimationFile.hpp/cpp | [Children](ANIMATION_CHILDREN_RECONSTRUCTION.md), [binding](ANIMATION_BINDING_RECONSTRUCTION.md) |
| Animation frame/geometry/operands | AnimationUpdates.cpp, AnimationGeometry.cpp, AnimationOperands.cpp | [Updates](ANIMATION_UPDATE_RECONSTRUCTION.md), [geometry](ANIMATION_GEOMETRY_RECONSTRUCTION.md), [operands](ANIMATION_OPERAND_RECONSTRUCTION.md) |
| Animation callback protocol | AnimationCallback.hpp/cpp, Bullet.hpp, BulletStyle.hpp | [Callbacks](ANIMATION_CALLBACK_RECONSTRUCTION.md) |
| ECL stack/runtime/manager/loader | ScriptStack*, EclRuntime*, EclManager*, EclLoader*, EclFileLoader* | [Whole tick](EXACT_ECL_TICK_RECONSTRUCTION.md), [call protocol](EXACT_ECL_CALL_RECONSTRUCTION.md), [buffers](ECL_BUFFER_RECONSTRUCTION.md) |
| Enemy movement/script/parameters | Enemy*, Motion*, ShotMetadata*, Laser* | [Movement](EXACT_ENEMY_UPDATE_RECONSTRUCTION.md), [whole dispatcher](CORE_ENEMY_DISPATCH_LAYOUT.md), [temporaries](EXACT_ENEMY_TEMPORARY_RECONSTRUCTION.md) |
| Scheduler/observation/locking | FunctionChain*, IntrusiveLink*, LockRegistry*, DiagnosticAllocator* | [Scheduler](FUNCTION_CHAIN_CONTROLLER_RECONSTRUCTION.md), [iteration](CORE_ITERATION_EXACT_RECONSTRUCTION.md) |
| Gameplay ownership/damage | Player*, Bomb*, Bullet*, Item*, Context*, Session*, Damage* | [Player/SHT](PLAYER_SHT_RECONSTRUCTION.md), [Bomb](BOMB_OWNER_RECONSTRUCTION.md), [Item](ITEM_OWNER_RECONSTRUCTION.md), [damage](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md) |
| Archive/File/resource I/O | Archive*, PbgFile*, GameFileIo*, GameResourceIo* | [Resource graph](ARCHIVE_RESOURCE_EXACT_RECONSTRUCTION.md), [writing](ARCHIVE_WRITE_RECONSTRUCTION.md) |
| Progress persistence | Progress*, SecureCrt.hpp | [File protocol](PROGRESS_FILE_EXACT_RECONSTRUCTION.md), [parser](PROGRESS_FILE_PARSE_RECONSTRUCTION.md) |
| Graphics/mesh/sound | Graphics*, RenderMesh*, MeshResourceAccess*, SoundInf.hpp, SoundLoading.cpp | [Mesh](RENDER_MESH_RECONSTRUCTION.md), [sound](SOUND_PROTOCOL_RECONSTRUCTION.md) |
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

The configured graph currently has 827 units / 160 objects. Fifteen additional
mapped whole functions are nonexact; the current handoff and generated progress
separate these totals from authored coverage. Private diagnostic/support probes
are not production admission. Do not use stubs or forced unresolved linkage to
claim a whole-program product.

## Build freshness and local products

Use scripts/repo-python, the compile wrapper and recorded per-source profiles.
Canonical products and their receipts are ignored build artifacts; their current
paths come from match-units.toml. Shared source/header changes require affected
fresh compilation and strict replay. Preserve original SHA-bound input archives
before retiring superseded products. See [oracles](ORACLES.md) and
[build/matching](BUILD_MATCHING.md).
