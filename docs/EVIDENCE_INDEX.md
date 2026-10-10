# Focused evidence index

These documents retain unique native observations, source contracts, compiler
results, fixture domains and reference-review decisions. Counts and pending-work
statements are dated to each document's checkpoint; later admissions do not
retroactively change historical compiler receipts. For present status, use the
[handoff](RE_HANDOFF.md), [source map](SOURCE_MAP.md), [progress](PROGRESS.md) and
live ledgers. Superseded cumulative session logs remain available in Git history.

## Animation and rendering

- [Animation template preparation and scoped child lookup](ANIMATION_BINDING_RECONSTRUCTION.md)
- [Animation callback owners and calling conventions](ANIMATION_CALLBACK_RECONSTRUCTION.md)
- [Animation child traversal and recursive flags](ANIMATION_CHILDREN_RECONSTRUCTION.md)
- [Animation geometry and parent position](ANIMATION_GEOMETRY_RECONSTRUCTION.md)
- [Animation operands and recursive direction](ANIMATION_OPERAND_RECONSTRUCTION.md)
- [Animation motion, interpolation and parent binding](ANIMATION_UPDATE_RECONSTRUCTION.md)
- [EXACT-060: ANM construction, resource lifetime and reset](EXACT_ANIMATION_LIFETIME_RECONSTRUCTION.md)
- [Mesh geometry and enemy deformation](RENDER_MESH_RECONSTRUCTION.md)

## ECL and Enemy

- [Core ECL and Enemy dispatch reconstruction](CORE_ECL_DISPATCH_RECONSTRUCTION.md)
- [Whole Enemy dispatcher control flow and compiler tables](CORE_ENEMY_DISPATCH_LAYOUT.md)
- [ECL buffer registration and instruction resolution](ECL_BUFFER_RECONSTRUCTION.md)
- [Whole ECL argument and tagged stack protocol](EXACT_ECL_ARGUMENT_STACK_RECONSTRUCTION.md)
- [Whole ECL async creation, lookup, invalidation and call setup](EXACT_ECL_ASYNC_RECONSTRUCTION.md)
- [ECL invocation and frame protocol](EXACT_ECL_CALL_RECONSTRUCTION.md)
- [Whole ECL file loading and derived lifetime](EXACT_ECL_FILE_LOADING_RECONSTRUCTION.md)
- [Whole ECL resource initialization and destruction](EXACT_ECL_RESOURCE_LIFETIME_RECONSTRUCTION.md)
- [Whole ECL Runtime/Manager lifetime and async disposal](EXACT_ECL_RUNTIME_LIFETIME_RECONSTRUCTION.md)
- [Complete ECL runtime dispatcher](EXACT_ECL_TICK_RECONSTRUCTION.md)
- [Whole Enemy animation dispatch and parameter protocol](EXACT_ENEMY_ANIMATION_RECONSTRUCTION.md)
- [Whole Enemy creation, initialization and script selection](EXACT_ENEMY_CREATION_RECONSTRUCTION.md)
- [EXACT-047: current-first Enemy position interpolation](EXACT_ENEMY_INTERPOLATION_RECONSTRUCTION.md)
- [Enemy movement composition and nonthrowing construction](EXACT_ENEMY_MOVEMENT_RECONSTRUCTION.md)
- [Enemy State and ECL Manager script pipeline](EXACT_ENEMY_SCRIPT_PIPELINE_RECONSTRUCTION.md)
- [Enemy spawn and time-scale orchestration](EXACT_ENEMY_SPAWN_TICK_RECONSTRUCTION.md)
- [Enemy state lifetime and ECL argument protocol](EXACT_ENEMY_STATE_RECONSTRUCTION.md)
- [EXACT-063: Enemy dispatcher temporary owners](EXACT_ENEMY_TEMPORARY_RECONSTRUCTION.md)
- [Whole Enemy movement update and its actual owners](EXACT_ENEMY_UPDATE_RECONSTRUCTION.md)
- [Whole Enemy variable destinations and Controller data](EXACT_ENEMY_VARIABLE_RECONSTRUCTION.md)
- [EXACT-064: actual shot allocation and shared-control protocol](EXACT_SHOT_ALLOCATION_RECONSTRUCTION.md)
- [Enemy damage, drops, defeat, cleanup and mesh review](REFERENCE_ENEMY_DAMAGE_REVIEW.md)
- [Enemy frame, movement, spawn and variable review](REFERENCE_ENEMY_MOVEMENT_REVIEW.md)
- [Gameplay and ECL implementation review](REFERENCE_GAMEPLAY_ECL_REVIEW.md)

## Ownership, gameplay and shared values

- [Actual Bomb ownership and dispatch](BOMB_OWNER_RECONSTRUCTION.md)
- [Whole core iteration and dispatch exact reconstruction](CORE_ITERATION_EXACT_RECONSTRUCTION.md)
- [Damage controller and whole query evidence](DAMAGE_CONTROLLER_RECONSTRUCTION.md)
- [Actual damage-query consumer protocol](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md)
- [Bullet ownership, construction and resource release](EXACT_BULLET_STORAGE_RECONSTRUCTION.md)
- [Actual Card construction and time state](EXACT_CARD_RECONSTRUCTION.md)
- [EXACT-048: native collision shapes and vector dependencies](EXACT_COLLISION_SHAPES_RECONSTRUCTION.md)
- [Actual Enemy Controller and Task construction](EXACT_CONTROLLER_CONSTRUCTION_RECONSTRUCTION.md)
- [Damage Region routing and configuration](EXACT_DAMAGE_REGION_RECONSTRUCTION.md)
- [Actual Game construction and state](EXACT_GAME_CONTROLLER_RECONSTRUCTION.md)
- [EXACT-046: shared easing and interpolation evaluation](EXACT_INTERPOLATION_RECONSTRUCTION.md)
- [Intrusive observation and nonthrowing Region construction](EXACT_INTRUSIVE_LIFETIME_RECONSTRUCTION.md)
- [Shared locks, callback nodes and random stream state](EXACT_LOCK_RANDOM_RECONSTRUCTION.md)
- [EXACT-045: complete Motion update protocol](EXACT_MOTION_RECONSTRUCTION.md)
- [Player storage construction](EXACT_PLAYER_STORAGE_RECONSTRUCTION.md)
- [EXACT-049: rectangle/segment neighborhood and planar dependencies](EXACT_RECTANGLE_COLLISIONS_RECONSTRUCTION.md)
- [Actual process Session and player-table reconstruction](EXACT_SESSION_RECONSTRUCTION.md)
- [Worker launch, replacement and shutdown lifetime](EXACT_WORKER_RECONSTRUCTION.md)
- [Complete function-chain controller protocol](FUNCTION_CHAIN_CONTROLLER_RECONSTRUCTION.md)
- [Hit controller lifecycle reconstruction](HIT_CONTROLLER_LIFECYCLE_RECONSTRUCTION.md)
- [Item main-function evidence](ITEM_MAIN_RECONSTRUCTION.md)
- [Actual Item pool, lifetime and reward protocol](ITEM_OWNER_RECONSTRUCTION.md)
- [Complete Item update investigation](ITEM_UPDATE_RECONSTRUCTION.md)
- [Player construction and SHT consumer reconstruction](PLAYER_SHT_RECONSTRUCTION.md)
- [Bullet, Laser and Damage Regions review (REF-029)](REFERENCE_BULLET_LASER_DAMAGE_REVIEW.md)
- [Player, Bomb and Item review](REFERENCE_PLAYER_BOMB_ITEM_REVIEW.md)

## Archive, Progress and sound

- [Whole archive-owner and resource-reader candidates](ARCHIVE_OWNER_RECONSTRUCTION.md)
- [Whole archive and resource production protocol](ARCHIVE_RESOURCE_EXACT_RECONSTRUCTION.md)
- [Whole compression and encryption protocol](ARCHIVE_WRITE_RECONSTRUCTION.md)
- [Archive codec, shared dictionary and allocation](EXACT_ARCHIVE_CODEC_RECONSTRUCTION.md)
- [Whole Profile construction](EXACT_PROGRESS_PROFILE_RECONSTRUCTION.md)
- [SaveManager ownership, member tasks and record merge](EXACT_PROGRESS_SAVE_MANAGER_RECONSTRUCTION.md)
- [Complete Snapshot and Metadata construction](EXACT_PROGRESS_STORAGE_RECONSTRUCTION.md)
- [Native Pbg file protocol](PBG_FILE_RECONSTRUCTION.md)
- [Complete progress-file serialization and parsing](PROGRESS_FILE_EXACT_RECONSTRUCTION.md)
- [Whole progress-file loading, saving and native file I/O](PROGRESS_FILE_IO_RECONSTRUCTION.md)
- [Complete progress-file parser and checksum](PROGRESS_FILE_PARSE_RECONSTRUCTION.md)
- [Whole progress-file serialization protocol](PROGRESS_WRITE_PROTOCOL_RECONSTRUCTION.md)
- [SoundInf owner and whole command dispatcher](SOUND_PROTOCOL_RECONSTRUCTION.md)

## Reference review

- [Effect and Special State reference review (REF-027)](REFERENCE_EFFECT_SPECIAL_REVIEW.md)
- [Entity opcode, adapter and fixture review](REFERENCE_ENTITY_OPCODE_REVIEW.md)
- [Exhaustive reference implementation review](REFERENCE_FUNCTION_REVIEW.md)
- [Game loading, player state and frame review](REFERENCE_GAME_LOADING_REVIEW.md)
- [Overlay, HUD, SmallScore and StageCompletion review](REFERENCE_OVERLAY_HUD_SCORE_COMPLETION_REVIEW.md)
- [REF-001: reference review and verified absorption](REFERENCE_REVIEW.md)
- [Sprite, ANM, rendering and texture review](REFERENCE_SPRITE_REVIEW.md)
- [Stage background, fog, camera and STD review](REFERENCE_STAGE_BACKGROUND_REVIEW.md)
- [REF-044: tooling, historical bridges and exhaustive review closure](REFERENCE_SUPPORT_REVIEW.md)
- [REF-026: Title batch review](REFERENCE_TITLE_REVIEW.md)
