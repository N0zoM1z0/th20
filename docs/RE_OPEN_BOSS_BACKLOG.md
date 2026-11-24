# TH20 — open native reconstruction Bosses and source frontiers

**Live backlog checked 2026-11-22.** This is a *working priority map*;
original native addresses/sizes and status are corroborated against
`config/functions.csv` and the original PE evidence named below.
For authoritative admission status, consult `config/match-units.toml`,
`config/matches.csv` and the [short handoff](RE_HANDOFF.md). A game
function is **not exact** merely because its caller or all children
are exact. Historical proof documents preserve their original
source/byte mismatches; some old status prose predates later commits.

## A. Major source-present, still NONEXACT game functions

The former **508B/511B Renderer list-update pair is no longer open**:
[CORE/RECON-1110 whole native strict exact proof](ANIMATION_RENDERER_LIST_508_511_STRICT_EXACT.md)
recovered the original `/sdl` class-key preclear, with **82/82** prior
strict units preserved. Keep the original 40B list constructor and 42B reset
on their *separate* NONEXACT helper backlog; they were not credited here.
A [bounded 40B constructor double-tail probe](ANIMATION_RENDERER_LIST_HELPERS_40_42_NATIVE_FRONTIER.md)
now reproduces all 40 original code bytes in length/16 i386 instructions,
34/36 ordinary bytes, original folded E8; two ModRM bytes and the reason
for the same-address duplicate tail write remain open and are **not**
canonically accepted.

| Original physical Boss | What is recovered; genuine next work |
| --- | --- |
| **Animation main Draw** `0x00443880`, **5,993B/1,501-i386** | `src/AnimationDrawBoss.cpp` preserves the original full 6,316B code+switch-pointer contribution, `0x204` stack, **123 ordered real E8 target roles**, 32 body HIGHLOW role multiplicities and both 49+31 jump-table alias partitions. Current whole-source comparison: **114/123** physical E8 sites, **27/32** body data site/target pairs and **4,835/5,376** ordinary bytes. **NONEXACT:** nine E8 positions and five body data locations remain; the active frontier is mode35/36 x87/SSE lifetimes and the final mode46 renderer call. [Current whole-source convergence and proof](ANIMATION_DRAW_BOSS_5993_MODE35_MODE45_SITE_CONVERGENCE.md); [earlier native frame/table source frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md). |
| **Glyph mask compositor** `0x00416420`, **2,245B/612-i386** | Maintained `src/GlyphMaskComposite2245.cpp` now uses the native direct `pixel_stride*rows` length expression, hoists the BGRA32 stencil pointer across the row loop, and writes the four-byte `PackedColorChannels` view only on the outline branch. Full current compiler candidate **2,118B/561 i386**, **37/37 E8 target roles**, **9/9 stride E8**, all four folded 22B array-index calls, **4/37 physical E8 sites** and **4/5 PE HIGHLOW site/target pairs** aligned; aggregate E8 offset distance **965**. The parent remains **NONEXACT** with 127B/51 instructions missing. Scoped source replay passed **24/24** existing exact PMR/color descendants. [Full native call-role frontier](GLYPH_MASK_BOSS2245_RGBA4444_SOURCE_STRIDE_37_CALLS.md), [prior row increment](GLYPH_MASK_BOSS2245_ROW_INCREMENT_FRONTIER.md). |
| **Glyph Unicode/GDI text core** `0x00415830`, **2,227B/470-i386** | Maintained `src/GlyphTextCore2227.cpp` reconstructs the 22 genuine font-switch pointers/17 alias groups, allocator/font/GDI color semantics, native completion pointer slot `+0x2C`, and a named glyph task alive until after queue submission. The 8B folded canvas-reference helper is exact as an existing library alias; original E8 `+0x7BC/+0x7E7` both align. Full current candidate **2,296B** versus original **2,316B** contribution; all 25 original call roles and 43 body data roles agree, with **17/25 E8 sites, 41/43 data sites, 1,626/1,936 ordinary bytes** aligned. Still **NONEXACT**, no parent credit. The 132B constructor/23B destructor stay exact (2/2 scoped replay); 294B submit remains its independently verified 292B frontier. [Current task/ABI proof](GLYPH_TEXT_CORE2227_QUEUE_TASK_ABI_FRONTIER.md), [earlier canvas/GDI source](GLYPH_TEXT_CORE2227_COLOR_AND_CANVAS_ABI_FRONTIER.md). |
| **Card spell-start Boss** `0x00487C30`, **1,896B/512-i386** | `src/CardStartSpell1896.cpp` now reproduces all **62/62 original E8 target roles** and **26/26 PE HIGHLOW data-target roles**, in native sequence: two real 20B renderer file getters, one 16B shared text getter, original `"text"` spawn, seven fresh script-table global loads, original boss-position branch order, and PMR display name destroyed after effect/script work. Whole current candidate **1,848B/490 i386**, still **NONEXACT** (zero new parent exact credit), while 128B PMR+7B callable and original 1,522B HUD+20B getter pass focused exact checks. [Current whole 62-call/26-data evidence](CARD_START1896_FULL_CALL_DATA_ROLES_FRONTIER.md), [prior text-task frontier](CARD_START1896_TEXT_TASK_CONSTRUCTION_FRONTIER.md). |
| **Renderer ANM resource group decoder** `0x0044EBF0`, **336B/83-i386** | `src/AnimationFileGroupParse336.cpp`; real 0x28B group header with **BYTE flag +0x20**, global Renderer owner, CP932 diagnostics, external texture loader. Compiler emits 336B/83 and correct 6 E8/8 HIGHLOW, but **278/280 ordinary bytes**, two local-stack/frame byte differences. Do not invent an inert stack local. Its 1,022B loader and 269B preloader are whole exact. [Full proof](ANIMATION_FILE_GROUP336_NATIVE_FRONTIER.md). |
| **ASCII text render and submit** `0x0044B020` **578B**, `0x0044FFF0` **294B** | `src/AsciiTextRender578.cpp` and `src/AsciiTextSubmit294.cpp`. Genuine variadic call/hidden result/std::function ownership reconstructed. 578B still has SSE/local-operand differences; 294B is only two original post-destructor compiler NOPs apart. **Both still NONEXACT**, while 93B/20B std::function copy/destructor and other children are independently strict exact. [578B native proof](ASCII_TEXT_RENDER578_NATIVE_FRONTIER.md), [294B frontier](ASCII_TEXT_SUBMIT294_TYPED_NATIVE_FRONTIER.md). |
| **Centered Unicode Renderer text** `0x0044ADD0` **586B/140-i386** | Source now maintained in `src/AnimationRendererCenteredText586.cpp` under the same borrowed Renderer owner as the separately **417B WHOLE STRICT EXACT** Unicode formatted-text function. Native E8 (11) and HIGHLOW (9) sites were independently decoded. Pinned C++20 now yields **586B/140**, 10/11 native physical E8 positions and 399/506 ordinary bytes; four of nine original HIGHLOW positions agree. The full expression changes advance/strlen evaluation order, so SSE register lifetime and physical relocations still differ (**NONEXACT**). [Whole 586B frontier](ANIMATION_RENDERER_CENTERED_TEXT_586_NATIVE_FRONTIER.md); [417B accepted proof](ANIMATION_RENDERER_FORMATTED_TEXT_417_STRICT_EXACT.md). |
| **Player main/update** `0x004F9C30` **3,111B**, movement `0x004FFA10` **555B** | Source-present/NOT whole exact, historically unresolved input/position operands and movement prologue/SSE effects. [Frame proof](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md), [movement proof](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **200-particle virtual grid update** `0x0045C360`, **2,884B/768-i386** | The complete game method is **now SOURCE-PRESENT, NONEXACT** in `src/AnimationParticleGridUpdate2884.cpp`. All **99 native E8 call roles/25 HIGHLOW fields** were independently attested, and the prior false four file/palette calls were repaired to the genuine Session→Context→EffectInfo→AnimationFile→83B spawn pipeline; existing 26B owner, 83B spawn, 25B age and 19B color accessors are separately exact. The distinct **51B virtual Event** is also now [whole strict exact](ANIMATION_PARTICLE_GRID_EVENT51_AGGREGATE_TIMER_STRICT_EXACT.md), with a true aggregate Timer forwarding ABI; all eight dependent exact units survived a focused six-object rebuild. The natural original-sized caller is **not** yet matched: pinned C++20 emits **2,876B/760 i386** versus 2,884B/768 native. The [ESI/polar/shared-child convergence](ANIMATION_PARTICLE_GRID_UPDATE_2884_ESI_POLAR_LIFETIME_CONVERGENCE.md) restores original ESI lifetime, matches the 0x19C stack frame, aligns eight E8 sites and reduces total E8 offset delta to 1,463 without losing any original call/data role; the remaining polar SSE/argument ABI is still open. [Full source/native frontier](ANIMATION_PARTICLE_GRID_UPDATE_2884_TYPED_OWNER_SOURCE_FRONTIER.md). |
| **Enemy mesh lifetime** `0x004A4190`, **1,649B** | `src/EnemyMesh.cpp` has reconstructed behavior but is not whole strict exact. [Original work](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md). |
| **Window D3D9 reset-state Boss** 0x0041A2C0, **1,954B/507-i386** | Maintained source is 1,911B/499-i386 with all 43 game E8 roles and 47 PE data-target roles in order, but the original GS-cookie/stack lifetime remains unmatched; NONEXACT. [Full source frontier](WINDOW_DEVICE_RESET_STATES_BOSS1954_FULL_SOURCE_FRONTIER.md). |

## B. Very large native dispatcher Bosses still NONEXACT

- **Bullet extended command** `0x0047DCF0`, **12,140B**. The natural-C++ source
  in `src/BulletRunExtendedCommands.cpp` now represents all **34/34 primary
  command IDs** (31 gameplay handlers plus three shared no-op entries); the
  12,140B parent remains NONEXACT. Commands 4/9/13/18/24/27 cover the nested
  subtype/style switches, Bullet pattern fire, angle/speed transition, Enemy
  creation and both Laser lifetimes. The next frontier is whole-parent
  ABI/SEH/stack/codegen convergence and the separate 41,967B Enemy ECL dispatcher.
  Preserve original branch/table boundaries; see the
  [34/34 primary source frontier](BULLET_12140_PARTIAL_CPP_DISPATCHER_FRONTIER.md),
  [complex branch closure](BULLET_12140_PRIMARY_OPCODE_34_OF_34_RESTORED.md),
  [command-9 call proof](BULLET_12140_COMMAND9_STYLE_ANIMATION_FRONTIER.md), and
  [original command coverage verifier](../scripts/verify-bullet-command-call-coverage.py).
- **Enemy ECL opcode dispatcher** at 0x0048C010, **41,967B**. CORE/RECON-1196–1199/1210–1215/1245–1269
  maintain the partial natural-C++ root entry and wire the complete 400–448 movement
  family, nine Pattern cases, 21 bounds/health/controller/state cases, five controller
  selection/clear cases, six timer/mode/runtime-time cases, five Card/health cases,
  front sound/gauge/title cases 516/519/527/534/548, laser reset 539,
  membership 549, fog 551, controller setters 553/554, animation/sound Boss
  555, bit flag 552, selected-position Boss 324, script-control cases
  800/801/802, reserved selector 569, global-owner opcodes
  524/575, StageResource selection/callback opcodes 622–626/631, four indexed parameter-copy cases and the
  independently maintained opcode fragments. The focused root host now executes
  the production 549/551/553/554/555 helpers, with real controller setter
  leaves, Context-retarget/operand-failure tests and full BulletController
  owner-image checks. It also executes 800/801/802 script-control paths with
  real EclManager reset/select, EnemyPhase filtering and VM XY destination
  checks; selector/call maps for 324/549/551/553/554/555/800/801/802 are checked.
  The 328B `SoundInf::enqueue` dependency
  is now whole strict exact (all 15 relocations). CORE/RECON-1245 also fixes
  the shared scalar allocator's unconditional destroy_at call for trivial
  intrusive nodes; 130/130 affected units pass across 17 source-scoped objects.
  The 1,457B shared shot-command branch 609/610/611/612 is now also executed
  by the root host using the real writable-shot COW selector and PMR vector;
  all four explicit/cursor and base/extended variants plus partial-write
  exception behavior are covered. The native 29-E8 map and 26-call COFF
  helper order are checked (CORE/RECON-1246).
  The four large Laser cases 702/703/711/713 are now also executed in the
  root host using real parameter lifetimes, writable-shot COW and late Context
  selection; the factory remains a capture-only test boundary. Their 2,699B /
  607-head / 62-E8 native maps and 47 ordered COFF relocations are checked
  (CORE/RECON-1247).
  The 572B opcode-614 queue-copy branch is now also executed in the root
  host with the real PMR forward_list and exact 119B typed record assignment.
  Full record/shared metadata ownership, self-copy, both growth paths and
  second-operand exception-before-mutation are covered; the original
  572B/129-head/19-E8 case and ordered COFF calls are verified. The assignment
  leaf replays 1/1 exact (CORE/RECON-1249).
  The 175B opcode-616 paired radial cancellation branch is now executed in
  the root host with the real 320B BulletController and 288B LaserController
  cancel_near Bosses. Tests cover live Enemy position aliasing during Bullet
  traversal, Context retargeting before the Laser phase, Bullet/Laser state
  filters, virtual circle-cancel arguments and radius exception-before-effects.
  Bullet::cancel and concrete Laser::cancel_circle remain explicit leaf test
  boundaries; the 47-unit COFF / 111-source ASan/UBSan root verifier passes
  (CORE/RECON-1254).
  The 627/628 pair each restore a separate 182B capped radial-cancellation
  branch and now execute the complete 401B BulletController::cancel_near_limited
  Boss plus 288B LaserController::cancel_near Boss. The native 99,999 limit,
  effects/mode arguments, live Context/position retargeting, Bullet state/field
  filters, effect-bit reset and radius exception-before-side-effects are
  checked under ASan/UBSan; both 7-E8 maps are pinned (CORE/RECON-1255).
  Opcode 632's 252B borrowed script-pointer branch now executes the production
  helper with both integer indexes before real writable metadata COW, PMR
  command-vector growth and the borrowed EclInstruction+0x1C payload pointer.
  Shared-owner preservation, old command data and second-index exception
  before COW/growth are tested; its 10-E8 map and ordered COFF relocations are
  checked (CORE/RECON-1256).
  The 622–626/631 StageResource cluster is now routed through the production
  root helper. Opcode 622 calls the whole 133B `StageResourceOwner::select_record`
  leaf, which strictly replays all 132 ordinary bytes plus its Timer assignment
  relocation; its variable-stride records, negative sentinel and miss-preserving
  Timer/offset behavior are host-tested. Opcode 623 captures the Context
  EnemyController before the operand and calls the real bit-0 setter. 624/631
  install the two original Bullet callback targets; 625/626 read the separate
  overlapping zero-table views. The six native case blocks total 337B/64
  instruction heads/9 ordered E8 calls. StageResource subsystem ownership is
  established but original source origin remains unknown (CORE/RECON-1269).
  The 653B `EnemyState::spawn_from_opcode()` Boss at `0x00496FB0` is now
  whole-function strict exact: all 577 ordinary bytes and 19 original
  relocation destinations match. Both float-default call sites preserve the
  native outgoing stack-slot/load order through an identity C++ cast; no asm
  or padding is used. Source origin remains unknown (CORE/RECON-1263).
  Opcode 629 now dispatches through its original three-entry member callback
  table to two complete natural-C++ EnemyState callback Bosses. The 758B
  rotated-animation rectangle body and 291B all-active-Bullet reset body now
  strictly replay all 59 original relocations and all 813 ordinary bytes; the
  rectangle's separate 10B INT3 alignment tail is not source credit. Real
  AnimationHandle resolution, geometry, Bullet intrusive traversal, Timer,
  color, field and Player setters remain exercised; original 6.0f/10.0f
  globals, callback table and all 51 E8 call sites are pinned (CORE/RECON-1262).
  Opcode 630 now awards score through the real Session owner and enqueues the
  popup through Context+0x1C and the strict-exact 255B ItemRewardPopupQueue
  Boss. Native 109B/24-instruction/5-E8 case, -1 marker, live Enemy position,
  Context retarget and operand exception are tested (CORE/RECON-1261).
  The 39B Bullet::set_timer_4d8 wrapper is independently strict exact, with
  all 35 non-relocation bytes and its single Timer::operator=(float) REL32
  checked against the original PE (CORE/RECON-1260).
  The 203B opcode-617 Player-relative angle branch is now executed in the
  root host with real Player construction, Context::player and
  Player::position_ref leaves, existing atan2 and float-destination writeback.
  Two independent live Player lookups preserve Context retargeting between VM
  operands; direct atan2(0,0)==0 behavior and second-operand exception
  preservation pass under ASan/UBSan. Context/DamageQueryProtocol affected
  replay passes 17/17. The shared 17B +4 getter is not double-credited
  (CORE/RECON-1253).
  The 243B opcode-618 shared queued-polar case is now executed in the root
  host using the real ensure-only shared_shot, pair extraction, Vector3
  constructor and polar leaf. Argument order, XY-only publication, shared
  metadata ownership and second-float exception-before-growth pass the native
  branch verifier and ASan/UBSan root host (CORE/RECON-1252).
  The 250B opcode-620 shared queued-vector case is now executed in the root
  host with the real ensure-only shared_shot selector and std::pair access.
  The -990.0f threshold, COMISS/JBE NaN path, shared metadata ownership and
  second-operand exception order are tested; the 48-unit COFF/root-host
  verifier passes (CORE/RECON-1251).
  The 148B opcode-619 writable metadata radial-offset branch is now executed
  through the production helper and real writable_shot COW selector. Ordered
  pair extraction, float operand 1 after COW, radial field_00 writeback and
  exception-after-clone/before-store are checked against the original
  148B/35-instruction/7-E8 case.
  The 163B opcode-633 queued-record decrement is also executed through the
  production helper. Its six-call native map, writable-shot COW, pair
  extraction, wrapping uint32 decrement, signed high-bit clamp and
  selector-exception-before-COW are checked under ASan/UBSan. The 48-unit
  locked-profile COFF / 112-source root verifier passes for both cases.
  The 346B opcode-621 mesh lifecycle is now also executed in the root host
  with real allocator templates and EnemyMeshOwner release; zero/negative/
  positive radius and operand-exception order are covered. RenderMesh
  ctor/dtor and allocator startup remain host fixtures. The int32 view cast
  binds the existing exact 213B MeshResourceAccess specialization. EnemyMesh
  7/7, MeshInterfaces 10/10 and MeshResourceAccess 8/8 affected replays pass
  (CORE/RECON-1248).
  The 196B opcode-712 rectangle-cancel branch is now executed in the root
  host through its production helper and the real 707B rectangle-cancel Boss.
  Rotated geometry, states 1/2, state/field gates, the second 384x448 viewport
  filter and second-float exception order are covered. Opcode 518 also uses
  the real 242B BulletController cancel-all and 19B active-list methods. The
  456B AnimationPoolOwner resolver and 662B Bullet::cancel remain host
  boundaries. BulletRectangleCancellation 1/1, RectangleCollisions 12/12,
  BulletCollisionHandle 2/2, AnimationGeometry 6/6 and BulletCancellation
  2/2 affected exact replays pass (CORE/RECON-1250).
  The 626B FrontInf command parent is
  still 622/626 and the 156B Dialogue allocator remains NONEXACT. The root remains
  incomplete/NONEXACT; continue restoring the other inline case families and converge
  the complete original 41,967B body, stack, calls and switch data.
- **Animation VM update** `0x0042B5D0`, **39,470B**. The complete 161-opcode
  semantic C++ body is now source-present in `src/AnimationUpdate39470.cpp`;
  the typed `AnmInstruction` header/variable-operand model preserves all 505
  original call targets. Current 39,764B COFF candidate remains NONEXACT
  (19/505 E8 offsets coincide, first fourteen consecutive sites aligned; aggregate
  E8 offset distance 53,958; no exact parent credit). Continue converging the whole-body instruction, relocation
  and stack layout, not just the leaves.
  [Native VM report](ANIMATION_UPDATE_VM_RECONSTRUCTION.md).

## C. Smaller outstanding ABI and ownership frontiers

These should be addressed *alongside* major Bosses, not instead of them.

- The **104B polygon draw wrapper** has an original saved-ESI lifetime
  mismatch despite surrounding 233B/827B/1,204B exact parents.
  [Scoped proof](ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md).
- **Three separate 75B Vector2 array constructors** retain a
  `struct`/`class`/`noexcept` and shared-header ABI issue; changing
  the global declaration affects a huge existing exact include closure.
  [Whole original evidence](ANIMATION_VECTOR2_ARRAY_60_64_61_NOEXCEPT_FRONTIER.md).
- **35B PMR glyph offset vector insertion**, 108B/488B growth and
  original 158B glyph task-node constructor differ under modern STL.
  Preserve genuine PMR allocator/ownership behavior.
  [35B](GLYPH_MASK_EMPLACE35_NATIVE_FRONTIER.md),
  [growth](GLYPH_OFFSET_PMR_FIVE_PARENTS_NATIVE_FRONTIER.md),
  [158B node](GLYPH_QUEUE_NODE_CTOR158_NATIVE_FRONTIER.md).

## D. Recent large exact closures — do NOT rework as pending

- **Window frame scheduler** 0x004193E0, **884/884B strict exact**:
  239 i386, 32 E8 calls, 21 PE HIGHLOW fields and 672 ordinary bytes.
  [Whole proof](WINDOW_FRAME_SCHEDULER_BOSS884_STRICT_EXACT.md).
- **Window frame pipeline and controllers:** the 113B pipeline, 164B/385B
  Presenters, 370B/433B/583B controllers, 574B screenshot scene, 31B repeat
  selector, 346B clock, 32B dispatch and 88B pending-capture leaf are exact.
  The separate 1,954B D3D9 reset-state Boss remains NONEXACT (listed in A).
- **Graphics D3D9:** 846B camera matrix, 194B device transform, 284B viewport
  clip switch, 136B resource release and 53B worker-close leaf are exact.
- **Card:** 875B update, 797B draw, 645B clock plus 37B callback, 121B
  registration plus two 13B callback bridges, 32B HUD leaf and 38B/41B archive
  selectors are exact. The 1,896B Card Start and 6,073B battle controller
  remain open.
- **Animation resources/rendering:** 1,022B loader, 269B preloader, 182B
  find/wait, 40B file lookup, 417B formatted-text caller and the four
  BGRA/ARGB texel helpers are exact. The adjacent 586B Unicode text caller
  and 294B submit remain open.
- **Textures and surfaces:** 2,745B texture finalizer, 562B uploader, 439B
  surface copy and 581B surface effect are exact.
- **Filesystem and provenance:** the 157B game-file existence helper is exact.
  The four texel helpers' 692B are reclassified as custom game code, not
  counted twice. See the [evidence index](EVIDENCE_INDEX.md) for the complete
  proof map and additional exact leaves.

## Safe continuation contract

The canonical status source is the live CSV/TOML, not this dated list.
Use the original immutable target with hash checks and exact physical
E8/PE HIGHLOW proof before accepting an original body. Keep meaningful
C++ with correct owner, ABI, original branches, EH and return semantics;
no padding, asm, fabricated locals, shortened extent or false authored
credit. `git status` dirt belongs to the active agent and must be
resolved, not ignored. Commit stable source work with **`gpt-web:`**;
only replay source units actually touched, never a full cold replay.
For documentation/ignored-artifact-only cleanup there are **zero affected
native units** and no reason to rebuild MSVC objects.
