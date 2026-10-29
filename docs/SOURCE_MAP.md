# Source and build ownership

Production declarations and implementations live in `src/`. Each owner has one
canonical declaration and one semantic body independent of its compiler profile.
Translation-unit placement is maintained build ownership; it does not establish
the original game's translation-unit partition.

## Navigation

| Protocol | Maintained source | Focused evidence |
| --- | --- | --- |
| Animation lifetime/parameters | Animation.hpp/cpp, AnimationFile.hpp/cpp, AnimationParameters.cpp | [Lifetime](EXACT_ANIMATION_LIFETIME_RECONSTRUCTION.md), [File/template arrays](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md), [PMR retirement](ANIMATION_PMR_RETIREMENT_RECONSTRUCTION.md), [descriptors/binding](ANIMATION_DESCRIPTOR_RECONSTRUCTION.md) |
| Animation pool allocation and recycled slot | AnimationPoolAllocate.cpp, AnimationRuntimeOwner.hpp, Animation.hpp, IntrusiveLink.hpp | [Complete original 298B Animation pool allocate/reuse boss exact](ANIMATION_POOL_ALLOCATE_298_EXACT_RECONSTRUCTION.md), typed natural +0x6000718 free-list and folded helper roles, huge Renderer lifetime remains separate |
| Direct Animation script loading and VM owner forwarding | AnimationFileScriptLoad.cpp, AnimationPoolUpdate.cpp, AnimationFile.hpp, AnimationRuntimeOwner.hpp | [338B native script load + 21B VM forward whole strict exact](ANIMATION_DIRECT_SCRIPT_359_EXACT_RECONSTRUCTION.md), two newly reconstructed native roots, giant Animation VM still NONEXACT |
| Animation traversal/templates | AnimationChildren.cpp, AnimationBinding.cpp, AnimationFile.hpp/cpp | [Children](ANIMATION_CHILDREN_RECONSTRUCTION.md), [binding](ANIMATION_BINDING_RECONSTRUCTION.md) |
| Animation frame/geometry/operands | AnimationUpdates.cpp, AnimationGeometry.cpp, AnimationOperands.cpp | [Updates](ANIMATION_UPDATE_RECONSTRUCTION.md), [geometry](ANIMATION_GEOMETRY_RECONSTRUCTION.md), [operands](ANIMATION_OPERAND_RECONSTRUCTION.md), [17 origin-reviewed exact gameplay methods](ANIMATION_FRAME_5527_EXACT_ORIGIN_AUDIT.md) |
| Animation callback protocol | AnimationCallback.hpp/cpp, Bullet.hpp, BulletStyle.hpp | [Callbacks](ANIMATION_CALLBACK_RECONSTRUCTION.md) |
| Whole native ECL/Bullet/Animation/Archive game-source origin audit | EclFileLoader.cpp, ConfigurationValue.cpp, PlayerStorage.cpp, BulletController.cpp, Card.cpp, Item.cpp, EnemyControllerConstruction.cpp, EclArguments.cpp, ScriptStackCopy.cpp, ShotMetadata.cpp, AnimationChildren.cpp, ArchiveLzssTree.cpp, Session.cpp, DamageQueryProtocol.cpp | [21 original 251–556B game methods, 6,836B whole strictly exact](ECL_BULLET_ANIMATION_6836_EXACT_ORIGIN_AUDIT.md), real 11,110B ECL runtime callers and 41,967B Enemy ECL parent still nonexact |
| ECL stack/runtime/manager/loader | ScriptStack*, EclRuntime*, EclManager*, EclLoader*, EclFileLoader* | [Whole tick](EXACT_ECL_TICK_RECONSTRUCTION.md), [call protocol](EXACT_ECL_CALL_RECONSTRUCTION.md), [buffers](ECL_BUFFER_RECONSTRUCTION.md) |
| Game exact Animation/ECL/Player/Item leaf and medium original methods | AnimationChildren.cpp, AnimationBinding.cpp, AnimationParameters.cpp, EclManagerAsync.cpp, Item.cpp, PlayerStorage.cpp, ScriptStack.cpp | [Seven original game-owned full strict methods /1,283 native bytes with authentic large-game original E8 caller graphs](GAME_PLAYER_ANIMATION_ECL_SEVEN_ORIGINAL_1283_EXACT_ORIGIN.md). Actual whole native sources preserved across seven affected-only canonical MSVC cold object rebuilds, 66/66 old units strict; original larger 3,111B Player, 12,140B Bullet and 41,967B Enemy parents remain NONEXACT. |
| Graphics, Player, Bullet, Item, replay, Progress and Archive game owner construction | Graphics.cpp, Player.cpp, PlayerRecord.cpp, Bullet.cpp, Item.cpp, ProgressStorage.cpp, ArchiveLzss.cpp, InputState.cpp, PbgFile.cpp | [Ten whole original authored game-owner functions (941–319B), 6,057 exact native bytes](GAME_OWNER_CONSTRUCTION_6057_EXACT_ORIGIN_AUDIT.md); original project-specific constructor/data/codec xrefs, no full-program link claim |
| Whole native Enemy / Motion game bosses | EnemyAnimation.cpp, EnemyState.cpp, EnemyVariables.cpp, EnemySpawnApplication.cpp, EnemyTick.cpp, MotionUpdates.cpp | [Ten original 416–967B whole Enemy/Motion methods, 7,204B native authored exact](ENEMY_MOTION_7204_EXACT_ORIGIN_AUDIT.md); original 41,967B Enemy ECL dispatcher still NONEXACT |
| Enemy movement/script/parameters | Enemy*, Motion*, ShotMetadata*, Laser* | [Movement](EXACT_ENEMY_UPDATE_RECONSTRUCTION.md), [whole dispatcher](CORE_ENEMY_DISPATCH_LAYOUT.md), [temporaries](EXACT_ENEMY_TEMPORARY_RECONSTRUCTION.md) |
| Enemy rank destinations and script time | EnemyScriptAdvance.cpp, EclSelection.cpp, EclArguments.cpp | [Rank/control protocol](ENEMY_RANK_CONTROL_RECONSTRUCTION.md) |
| HUD owner and boss markers | HudGauge.hpp/cpp | [FrontInf owner and script callers](FRONT_OWNER_RECONSTRUCTION.md) |
| Text queue/resource owner | TextLine.hpp/cpp | [AsciiInf storage and shared resources](ASCII_OWNER_RECONSTRUCTION.md) |
| Dialogue initialization and ready state | DialogueText.hpp/cpp, HudGauge.hpp/cpp, AnimationHandle.hpp/cpp | [Whole Dialogue owner and callbacks](DIALOGUE_OWNER_RECONSTRUCTION.md) |
| Laser controller storage/context | LaserParameters.hpp/cpp, Context.hpp/cpp | [Dialogue cancellation receivers](DIALOGUE_OWNER_RECONSTRUCTION.md); [original 936B typed Laser parameter lifetime provenance](LASER_PARAMETERS_936_ORIGINAL_GAME_EXACT_ORIGIN.md) from 12,140B Bullet + 41,967B Enemy original commands, both giants still NONEXACT |
| Scheduler/observation/locking | FunctionChain*, IntrusiveLink*, LockRegistry*, DiagnosticAllocator* | [Scheduler](FUNCTION_CHAIN_CONTROLLER_RECONSTRUCTION.md), [allocation/release](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md), [iteration](CORE_ITERATION_EXACT_RECONSTRUCTION.md) |
| Whole collision geometry and polygon/ellipse sampling | RectangleCollisions.cpp, CollisionShapes.cpp, CollisionGeometry.hpp | [19 whole native exact authored functions, 13,360B](GEOMETRY_ORIGIN_13360_EXACT_RECONSTRUCTION.md), [original rectangle/segment protocol](EXACT_RECTANGLE_COLLISIONS_RECONSTRUCTION.md) |
| Player main-frame whole source and original input selectors | PlayerMainFrame.cpp, Player.hpp, InputInf.hpp/cpp | [Whole 3,111B nonexact source frontier](PLAYER_MAIN_FRAME_3111_TYPED_SOURCE_FRONTIER.md), [signed view index correction](INPUT_INF_VIEW_INDEX_ABI_CORRECTION.md), [earlier exact children](PLAYER_MAIN_FRAME_3111_NATIVE_FRONTIER.md), [current 3,111B whole Player gameplay call/ABI correction](PLAYER_FRAME_3111_GAMEPLAY_ABI_CORRECTION.md), [native 22B Timer postfix E8 correction and unresolved equality ABI](PLAYER_MAIN_TIMER_POSTFIX_3111_NATIVE_ABI.md) |
| Legacy compiler/STL shared_ptr ownership | ShotSharedPtrMoveLegacy.cpp, ShotMetadata.hpp, EclLoaderBuffer.cpp | [Complete original 63B `std::shared_ptr<EtamaArgInf>` move-assignment strict exact library unit](SHOT_SHARED_PTR_LEGACY_MOVE_63_EXACT_COMPILER_SUPPORT.md), 8B physical std::move/addressof alias no duplicate original credit; C++20 compatibility specialization isolated and excluded from authored game coverage |
| Bullet emitter complete original game boss and real old STL helpers | BulletEmitter.cpp, ShotSharedPtrMoveLegacy.cpp, Bullet.hpp, BulletStyle.hpp, ShotMetadata.hpp | [Entire 3,735B native Bullet emission boss now strict exact](BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md), including **3,832/3,832** whole compiler-code, original post-body NOP and 13+11 jump-table bytes, **129 independently anchored original E8/HIGHLOW relocations** and true 4.0f initial velocity scalar; one new source/provider strict 1/1 cold replay. Historical nonexact x87/order notes are superseded. Separate 12,140B Bullet command dispatcher still NONEXACT. |
| Bullet original whole 12,140B command sequencer (NO complete source yet) | Bullet.hpp declaration; genuine exact callers BulletEmitter.cpp and BulletPhysics.cpp | [Original 2,490-x86/34+8+11 native switches, 210 E8/38 body HIGHLOW + 53 table HIGHLOW; bounded 204/210 E8 case CFG and two exact large C++ callers](BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md). Source owner Bullet::run_extended_commands high-confidence; no maintained definition, exact unit or source-present mapping. **NONEXACT**, zero game body credit; old notes calling it a BulletController parent were imprecise. |
| Bullet command-11 whole source and typed polar link alias | BulletCommand11.cpp, MotionMath.cpp, Bullet.hpp | [Complete 1,404B original strict exact command-11 boss and shared 89B polar](BULLET_COMMAND11_1404_EXACT_RECONSTRUCTION.md); 12,140B parent remains open |
| Gameplay ownership/damage | Player*, Bomb*, Bullet*, Item*, Context*, Session*, Damage*, HitCtrlInf* | [Player/SHT](PLAYER_SHT_RECONSTRUCTION.md), [Bomb](BOMB_OWNER_RECONSTRUCTION.md), [Item](ITEM_OWNER_RECONSTRUCTION.md), [damage](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md), [Region allocation/ownership](DAMAGE_REGION_ALLOCATION_EXACT_RECONSTRUCTION.md), [four exact Player-frame effects/Enemy leafs](PLAYER_FRAME_LEAF_120_EXACT_RECONSTRUCTION.md) |
| Archive/File/resource I/O | ArchiveLzssEncode.cpp, ArchiveLzss.cpp, Archive*, PbgFile*, GameFileIo*, GameResourceIo* | [Complete original 1,036B LZSS compressor strict exact](ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md), paired 706B decoder; [resource graph](ARCHIVE_RESOURCE_EXACT_RECONSTRUCTION.md), [historical write frontier](ARCHIVE_WRITE_RECONSTRUCTION.md) |
| Progress persistence | Progress*, SecureCrt.hpp | [File protocol](PROGRESS_FILE_EXACT_RECONSTRUCTION.md), [loading/lifetime](PROGRESS_LOAD_LIFETIME_EXACT_RECONSTRUCTION.md), [parser](PROGRESS_FILE_PARSE_RECONSTRUCTION.md) |
| Graphics/mesh/sound | Graphics*, RenderMesh*, MeshResourceAccess*, SoundInf.hpp, SoundLoading.cpp | [Texture formats/accessors](ANIMATION_TEXTURE_FORMAT_RECONSTRUCTION.md), [mesh](RENDER_MESH_RECONSTRUCTION.md), [mesh flags](MESH_FLAGS_EXACT_RECONSTRUCTION.md), [sound](SOUND_PROTOCOL_RECONSTRUCTION.md) |
| Shared math/time/random | Vector*, Angle*, Timer*, ClockScalar*, Interpolation*, GameRandom* | [Interpolation](EXACT_INTERPOLATION_RECONSTRUCTION.md), [random/locks](EXACT_LOCK_RANDOM_RECONSTRUCTION.md), [ten whole native game interpolation exact bodies](INTERPOLATION_BOSSES_8571_EXACT_ORIGIN_AUDIT.md); [seven complete 199B original Bullet Vector3/Float interpolation tangent and Timer methods, 114-object 542-old-unit strict closure](BULLET_199_INTERPOLATION_TANGENT_TIMER_EXACT.md) |
| Input device frame and owner | InputDeviceFrame.cpp, InputState.hpp/cpp, InputInf.hpp/cpp | [Whole native 3,490B polling boss strict exact](INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md), [device construction](INPUT_DEVICE_BUTTON_CTORS_442_EXACT_RECONSTRUCTION.md) |
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
accepted source and independently replayed EH code/data. Six integrated clear,
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
remaining maintained defeat dependencies. The ten complete roots and three SDK
callback helpers are strict exact. PlayerFeedback's actual counter getter reads
+38 and folds to the existing physical duration-getter unit without duplicate
credit. The list constructor and SDK callback invocation retain separate emission
differences. See [whole defeat acceptance](ENEMY_DEFEAT_RECONSTRUCTION.md).

PlayerStorage.cpp owns the actual Timer-backed Feedback operations; the complete
update remains 114/native115 and nonexact. PlayerRecord.cpp owns all four reward
channels and the complete dispatcher/table. EclSelection.cpp owns indexed loader
selection, cached Manager routing and the direct index setter. The integrated
defeat fixture uses these actual bodies and the maintained ECL reset, with
remaining VM/resource calls explicitly captured. See
[defeat state protocols](ENEMY_DEFEAT_STATE_RECONSTRUCTION.md).
