# CORE/RECON-1196 — 41,967B EnemyState::execute_opcode partial C++ source

The original `EnemyState::execute_opcode` root at `0x0048C010` is 41,967
bytes. It is still **NONEXACT** and its full original inline switch has not
been recovered. This checkpoint changes the status from source-absent to a
real maintained C++ entry point and restores the complete contiguous native
movement opcode family 400–448 plus nine EnemyPattern opcode cases as natural
source fragments.

## New maintained source

- `src/EnemyStateExecuteOpcode.cpp` defines the actual declared
  `EnemyState::execute_opcode()` method. It retrieves the live instruction
  from `entity->current_runtime->current()` and dispatches to independently
  reconstructed source fragments. The original `EclInstruction` and trailing
  packet payload are borrowed, not copied.
- `src/EnemyStateMovementOpcode.cpp` contains the complete 49-value opcode
  family 400–448, extracted from the previously exercised whole-root semantic
  draft and expressed as ordinary C++ over the real `EnemyState`, `Motion`,
  interpolation, player, and random owners.
- `src/EnemyStatePatternOpcode.cpp` restores the nine native EnemyPattern
  cases 506/507/508/509/510/556/567/568/572. They call the maintained real
  `EnemyPattern` setters and exact `drop` protocol; opcode 509 preserves its
  two-player Session guard before touching the Enemy or Pattern owners.
- `src/EnemyStateControlOpcode.cpp` restores 20 original bounds, health,
  controller-selection, state and PlayerRecord-counter cases, including the
  295B opcode-512 handle publisher, 239B opcode-511 health branch, and the
  225B/119B opcode-563/564 pending field-counter protocol.
- `src/EnemyStateDynamicParameterOpcode.cpp` restores the 4-way/8-way integer
  and float copy cases 529/530/570/571, preserving the ECL reference-bit and
  negative manager-variable destination path for operand 0.
- `src/EnemyStateControllerManagementOpcode.cpp` restores selection/clear
  cases 520/525/545/565/573. Opcode 520 propagates its special `-1` return;
  the other four call the real 501B/521B/514B/526B EnemyController clear leaves.
- `src/EnemyStateTimeOpcode.cpp` restores five timer/mode cases 538/540/541/542/574,
  including the real global clock setter, three ordered Session mode queries,
  and inherited current-runtime time subtraction.
- `src/EnemyStateCardOpcode.cpp` restores Card spell/flag and scaled-health
  cases 523/536/537/561/562, reusing the existing exact 602B finish-spell leaf
  and real Card/EnemyHealth setters without duplicating their byte credit.
- `src/EnemyStateFrontendOpcode.cpp` restores sound/dialogue cases 516/519,
  including position-before-sound-operand evaluation and the special `-1`
  return when an existing dialogue is not ready.
- Native switch case `0` routes direct spawn opcodes 300/301/304/305/321 to
  the maintained 653-byte `EnemyState::spawn_from_opcode()` implementation in
  `src/EnemyStateSpawnOpcode.cpp`. It reconstructs the script-name payload,
  default operands, relative/mirrored position, spawn flags, counters, identity
  and `EnemyController::create` handoff. The leaf remains NONEXACT: its extent
  and all 19 relocation destinations match, but 14 ordinary bytes differ in
  the two float argument stack-slot/load sequences.
- Native switch case `6` handles 309/310/311/312 through the exact
  `EnemyController::selected(0)` leaf at `0x00485660`; when the slot is empty it
  branches to the same spawn leaf, otherwise it skips creation. The leaf keeps
  the native per-opcode relative-position and direction-flag distinctions.
- Native switch case `2` routes opcode 303 to `EnemyState::spawn_animation()`
  at `0x00496A00`, now a strict whole-function 398/398-byte C++ match with all
  18 original relocation targets. It resizes the PMR animation-link vector,
  retires the old handle, selects the controller AnimationFile, creates the
  flag-2 animation, updates primary animation dimensions and conditionally
  clears the recursive flag-0 state. Its 50-byte `0x00450120` handle-first
  recursive-clear leaf is strict exact with all three relocations. The adjacent
  50-byte `0x0044FA30` handle-first recursive-set leaf is now also strict exact;
  its generic `AnimationHandle*` source view is used by opcode 503 and the Card
  HUD, while the original class/source owner remains unknown. Both flag leaves
  have strict byte/relocation matches, but their original source origins remain
  unclassified and no authored-byte credit is claimed.
- Native switch case `0x43` / opcode 517 now creates a mode-1 ScreenInf by
  reading integer operands 2, 1 and 0 in that order, then calling the existing
  exact 81-byte `screen_factory_4250f0` with those values as parameters 1/2/3
  and zero for parameter 4, priority and view. The native 99-byte case block,
  selector/pointer entry and four ordered E8 targets are verified; no callee
  bytes are re-credited. See
  [the opcode-517 ScreenInf fragment](ENEMY_OPCODE_517_SCREEN_EFFECT_SPAWN_FRONTIER.md).
- Native switch case `74` / opcode 524 now updates the published
  `current_game_controller` through the exact 36-byte
  `GameController::set_field_34` method. The root reads integer operand zero
  first, calls the GameController setter with the complete 32-bit word, then
  stores the original signed value in `field_280` and clears `field_284`.
  The original 76-byte case body, compressed selector index and both ordered
  E8 targets are independently checked.
- Native switch case `120` / opcode 575 now saves `player(0)` before reading
  integer operand zero, then calls the exact 42-byte
  `Player::set_entity_flag_10` setter with the complete 32-bit word. The
  original 59-byte case body, compressed selector index and all three ordered
  E8 targets are independently checked. Neither inline case receives separate
  root byte credit.
- Native case `77` / opcode 527 now restores the FrontInf boss-gauge update.
  It reads float operand 1, integer operand 2, the signed
  `EnemyHealth::field_04` denominator, integer operand 0, and the current boss
  index in native order, then calls the exact 65-byte
  `FrontInf::set_boss_gauge`. The source deliberately reads `health.field_04`:
  the native offset-four Timer conversion is applied to the real EnemyHealth
  receiver at `EnemyState+0x18C`, not to current health or a fabricated Timer.
  Its 169-byte case block, selector entry and six ordered E8 targets are checked.
- Native case `80` / opcode 534 reads integer operand zero and writes the
  complete signed word through the exact 25-byte `FrontInf::set_field_180`.
  Its 43-byte case block, compressed selector entry and two ordered E8 targets
  are checked.
- Native selector entry `85` / opcode 539 obtains the actual LaserController from the
  EnemyState Context and calls the exact 263-byte
  `LaserController::reset_all_lasers` method. The 30-byte case block, selector
  entry and both ordered E8 targets are checked; the reset method's own exact
  bytes are credited only by its independent match unit.
- Native case `98` / opcode 552 updates only bit 3 of `flags.word_04`, preserving
  every other bit. Its 65-byte case block, compressed selector entry and
  original integer-argument E8 target are checked.
- Native selector entry `94` / opcode 548 calls the exact 75-byte
  `FrontInf::show_stage_title` method. The original 17-byte case block includes
  the global FrontInf load, one E8 call, the native NOP and shared-exit jump;
  the compressed selector entry and complete block boundary are checked.
- Native opcode 569 is a reserved selector: its compressed entry `173` points
  directly to the common return-zero epilogue at `0x004963DF`. The root has an
  explicit operand-free `return 0` case, and the verifier checks the selector,
  target and full 31-byte epilogue. The host fixture checks that representative
  EnemyState fields remain unchanged.
- Native switch case `3` (opcode 306) now reconstructs the second animation
  creation path. It uses integer operands 0/1 as link index/script, retires and
  replaces the PMR link with a flag-2 animation, refreshes dimensions and
  conditionally clears recursive flag 0. For link zero it additionally sets
  `flags.word_04` bit 4 and publishes `field_28 = script`, `field_2c = 0`,
  `field_24 = script`, and `field_20 = field_1c`. Unlike opcode 303, this native
  path does not reject a negative script before calling `spawn_flag2`.
- Native switch case `7` (opcode 313) now restores the related animation path
  using integer operand 0 as the link index and `field_28 + 5` as the script.
  It shares the PMR handle retirement/replacement, primary-dimension refresh
  and conditional recursive flag-clear sequence, but does not publish the
  opcode-306 secondary-state fields. These two inline case bodies are restored
  in natural C++; the 41,967-byte root remains NONEXACT and no separate byte
  credit is claimed for inline code.
- Native switch case `11` covers opcodes `181/193/317`: it selects the
  `EnemyAnimationLink` by integer operand 0 and forwards operand 1 to the
  existing exact `AnimationHandle::interrupt` wrapper at `0x0044EF90`, which
  delegates to the real animation-pool descendant interrupt protocol.
- Native switch case `12` covers opcodes `41/318`: it retires animation link
  zero, spawns `field_28` from the controller file at `field_1c` with layer
  `field_34 + 7` and flag 2, then resets `field_2c`, publishes `field_24` and
  `field_20`, and clears `flags.word_04` bit 4. This path does not resolve the
  new handle, refresh dimensions or run the recursive flag-0 clear.
- Native case `14` (opcode 320) writes an indexed `EnemyAnimationLink` XY
  offset from float operands 1/2 and zeros its Z component; case `15` (opcode
  322) writes the indexed link parent from integer operand 1 (read before the
  index operand 0). Case `16` (opcode 323) stores integer operands 0/1 in
  `field_258` and `field_254`.
- Native case `17` aliases `17/21/25/45/260`: it resolves the Enemy identifier
  from integer operand 2 and copies the selected Enemy position into float
  destinations 0/1, falling back to the current EnemyState position when no
  Enemy is found. The exact `EnemyController::find`, `Enemy::position_ref`,
  `EnemyState::position_ref` and destination leaves are reused.
- Native opcode `324` is a separate 276-byte / 53-instruction case at
  `0x004960C1..0x004961D5`, selected by compressed index 17. It caches the
  Context's EnemyController before reading integer operand 2, calls the exact
  251-byte `EnemyController::find`, then copies the selected Enemy's X/Y into
  float destinations 0/1. If no Enemy is found, it reads the current
  EnemyState position instead. The same natural-C++ operation is shared with
  the lower 17/21/25/45/260 routes. The verifier checks all 11 ordered E8
  targets; the ASan/UBSan host exercises both selected-Enemy and fallback paths.
  See the [opcode-324 source/call-order frontier](ENEMY_41967_324_SELECTED_POSITION_FRONTIER.md).
- Native opcode `549` is a 95-byte / 20-instruction membership query at
  `0x00495D7F..0x00495DDE`, selector index 95. It caches the Context's
  EnemyController before integer operand 1, calls the exact 244-byte intrusive
  membership predicate, then resolves integer destination 0 and writes the
  zero-extended boolean. The verifier checks all four ordered E8 targets; the
  root host executes the actual helper with a predicate boundary, while the
  complete 244-byte leaf independently replays exact.
- Native opcode `551` is a 257-byte / 58-instruction FogValue update at
  `0x00495C1F..0x00495D20`, selector index 97. It reads integers 0/1/2,
  then floats 4/3, builds the real PackedColor and FogValue in blue/green/red/
  alpha byte order, and only then loads the live StageResource owner and calls
  `set_fog`. The verifier checks all nine ordered E8 targets. The root host
  executes the actual helper and constructors, capturing the final owner call;
  the three StageResource owner methods and six FogValue methods independently
  replay exact.
- Native opcode `553` is a 66-byte / 14-instruction cached-EnemyController
  setter at `0x00495860..0x004958A2`, selector index 99. It loads the live
  Context's EnemyController before integer operand 0, then calls the real
  `EnemyController::set_field_88` with the full 32-bit value. The root host
  executes the production helper and 25-byte setter: operand evaluation
  retargets both Context and EnemyState, yet only the original cached
  controller changes; an operand exception leaves it untouched.
- Native opcode `554` is a 106-byte / 22-instruction BulletController vector
  setter at `0x004961D5..0x0049623F`, selector index 100. It caches the live
  Context's BulletController before reading float operand 1 (Y) and then 0 (X),
  and passes `(X,Y)` to the real 39-byte `BulletController::set_vector_4c`.
  The root host constructs two real BulletController owners and executes the
  production setter. It verifies the whole owner image changes only in the two
  vector words, Context retargeting cannot redirect the cached receiver, and
  exceptions on either operand prevent the write.
- Native opcode 614 is the 572-byte / 129-instruction queued-record
  copy branch at 0x004925C7, with 19 original E8 calls. The maintained
  ASan/UBSan root host executes the production helper, actual PMR forward_list
  and exact 119B EnemyQueuedRecord assignment. Full 76B record/metadata-owner
  copy, self-assignment, destination and source growth, and a second-operand
  exception before mutation are tested. The assignment leaf replays 1/1
  exact; the 41,967B parent remains NONEXACT.
- Native opcode 621 is the 346-byte / 70-instruction mesh-owner lifecycle
  branch at 0x00495A9A, with seven original E8 calls. The ASan/UBSan root host
  executes the production helper, real DiagnosticAllocator allocation/release
  templates and EnemyMeshOwner destructor. It covers positive/zero/negative
  radius, replacement, 17x17 RenderMesh arguments and partial writes when
  float or integer operands throw. Renderer-dependent RenderMesh ctor/dtor
  and allocator startup remain host fixtures; the 41,967B parent is NONEXACT.
- Native opcode 712 is the 196-byte / 42-instruction rectangle bullet
  cancellation case at 0x0049540D, selector index 164, with nine original E8
  calls. The production helper reads both VM dimensions, resolves animation
  link zero, obtains the Context BulletController and Animation rotation, then
  calls the real 707B rectangle-cancellation Boss. The ASan/UBSan root host
  exercises rotated geometry, both eligible Bullet states, state/field gates,
  the fixed 384x448 viewport filter and second-operand exception ordering.
  The 456B AnimationPoolOwner resolver and 662B Bullet::cancel child remain
  explicit test boundaries; the 41,967B parent remains NONEXACT.
- Native opcodes 609/610/611/612 share the 1,457-byte / 314-instruction
  branch at 0x004931DD, selector index 130, with 29 original E8 calls. The
  maintained root host now links and executes the production shot-command
  helper, real EnemyState::writable_shot COW selector and PMR command vector;
  all four explicit/cursor and base/extended modes plus partial-write exception
  behavior are tested under ASan/UBSan. This is inline case coverage, not a
  standalone native function or parent byte credit.
- Native Laser opcodes 702/703/711/713 cover **2,699 bytes / 607
  instruction heads / 62 E8 calls**. The maintained root host now executes the
  production helper with real LaserType0/1/2/3 parameter lifetimes,
  writable-shot COW, PMR command copies, both position branches and late
  handle reads that retarget Context before the capture-only factory boundary.
  The verifier checks the four original CFGs and 47 ordered COFF relocations;
  LaserParameters replays 12/12 and LaserFactory 1/1. No parent byte credit.
- Native opcode `800` is a 144-byte / 30-instruction script-selection branch
  at `0x00495FC1..0x00496051`, selector index 167. It reads integer operand 0,
  resolves the target through `EnemyController::find`, then terminates async
  runtimes, resets the target EclManager, and selects the borrowed script
  name at EclInstruction + 0x18. The 40-byte EclManager::select wrapper at
  `0x00540200` is now a separate strict-exact natural-C++ leaf.
- Native opcode `801` is a 168-byte / 32-instruction selected-Enemy position
  writeback at `0x00495DDE..0x00495E86`, selector index 168. It reads the
  target identifier from integer operand 2, then independently reads X and Y
  through Enemy::position_ref before resolving float destinations 0 and 1.
- Native opcode `802` is a 315-byte / 66-instruction phase-script restart loop
  at `0x00495E86..0x00495FC1`, selector index 169. It reads the phase index
  once, walks selected slots 0–2, skips field_270 and negative-life phases,
  and restarts eligible Enemies using the borrowed EnemyPhase::script.
  Enemy::state_value is a typed natural-C++ alias of the existing shared
  19-byte +0x88 getter at `0x004989F0`; it adds no duplicate physical credit.
  The root host exercises all three slots, the current-slot skip and the
  negative-life skip using real phase vectors and EclManager runtime reset/
  selection.
- Native opcode `555` is the 388-byte / 81-instruction animation-and-sound
  Boss at `0x0048C3F4..0x0048C578`, selector index 101. Its two independent
  signed gates preserve sound-before-animation ordering. The animation path
  computes the XY squared-distance threshold from the original 0.2f constant,
  selects -pi/2 or the real XY direction, resolves the live Context controller
  and AnimationFile, then spawns at layer 3 without consuming ECL operands.
  The verifier checks all ten ordered E8 targets and the three original float
  constants. The root host executes the real helper across both gate outcomes,
  near/far direction paths and combined ordering; the SoundInf request,
  EnemyController file selector and AnimationFile spawn are explicit host
  boundaries, with their real leaves independently replayed exact.
- Native cases `22/23/24` (opcodes 341/342/343) set, clear, or assign the
  corresponding low bits in `flags.word_08`. Case `25` (opcodes 44/73/344)
  writes whether the integer-operand-1 identifier resolves through
  `EnemyController::find` into integer destination zero.
- Native case `18` (opcode 334) requests an EffectInfo handle slot using
  integer operand 0 and the current EnemyState position view. The new
  `EffectInfo::spawn_effect_at_position` method at `0x004974D0` reproduces the
  108-byte wrapper exactly: it selects a free slot, invokes the real
  `EffectInfo::spawn_effect` callback path, stores the resulting handle in the
  slot array and returns the high-bit-tagged slot token (ignored by this
  opcode). All three native relocations strictly replay. The source-level
  owner/origin remains provisional and receives no authored-byte credit.
- Native case `19` (opcode 338) builds a position from float operands 2/3,
  adds the current EnemyState position, then spawns a positioned flag-2
  animation using file operand 0, script operand 1 and rotation operand 4. The
  resulting handle is published through `EffectInfo`.
- Native case `20` (opcode 339) creates a null-position flag-2 animation from
  file/script operands 0/1, publishes its handle, resolves it and invokes the
  actual `Animation::update` once per operand-2 iteration. The native loop
  re-reads operand 2 on each condition check; the source preserves that order.
- Native case `21` (opcode 340) resolves an Enemy by identifier operand 0 and,
  when found, sets its `EnemyState::flags.word_04` bit 9. The 35-byte
  `0x00497240` fastcall leaf is now strict exact in
  `src/EnemyStateFlagBit9.cpp`; its source owner/origin remains provisional.
- Native switch case `10` maps opcodes `48/173/177/201/316` to a further
  indexed animation replacement path, now restored in
  `src/EnemyStateAnimationVariantOpcode.cpp`. Operand 0 selects the link; a
  negative operand-1 selector uses `field_28` directly, while a nonnegative
  selector uses `field_28 + 5 + selector`. It retires/replaces the PMR handle
  with a flag-2 animation, refreshes primary dimensions for link zero and
  conditionally clears recursive flag 0. Unlike opcode 303, it has no negative
  script guard and does not publish the opcode-306 state fields. This is inline
  dispatcher logic and receives semantic progress only.
- Native cases `4/5/8/9` (opcodes 307/308/314/315) now restore the
  EffectInfo animation-handle publication paths. Opcode 307 creates a
  positioned flag-2 animation; 308 creates a null-position flag-2 animation;
  314 creates a positioned flag-zero animation; and 315 creates a positioned
  flag-2 animation, then reapplies the current position and operand-2 rotation
  when its handle resolves. All four publish the resulting handle through the
  real `EffectInfo::publish_handle` owner.
- The positioned flag-2 factory wrapper at `0x0049CBB0` is now a separate
  natural C++ method, `AnimationFile::spawn_flag2_position`, with strict
  61/61-byte and relocation replay. It forwards the expected stem, script,
  position, rotation, layer and output to the existing native spawn producer
  with flag value 2. Its source-level owner/origin remains provisional; no
  authored-byte credit is claimed.
- Native switch case `1` now restores opcode 302 as the scalar field setter:
  `field_1c = integer_argument(0)`. This matches the native `FUN_004AB080`
  argument read followed by the store at EnemyState offset `0x1C`.
- Native switch case `0x0d` now routes all 13 animation-setter opcodes
  `319/325–333/335–337` through the existing `EnemyState::change_animation`
  owner at `0x00496B90`. The original root case is a single call to that
  967-byte method; this closes the dispatcher-to-animation boundary without
  duplicating its implementation.
- The root now also routes to the maintained phase, card-start, controller
  setter, fog, membership, mesh, animation-spawn, queued-shot, script-pointer,
  shot-fire, shot-command, laser-parameter, and laser-creation opcode fragments.
- Opcode 560 retains its distinct `return 1` behavior when `Enemy::defeat()`
  requests an immediate same-tick ECL exit. Ordinary handled fragments return
  zero so `EclRuntime::tick` performs the normal instruction advance.

## Remaining scope

This is a **partial root reconstruction**, not an exact or complete dispatcher.
Native movement case `48` also aliases opcode `117` to the existing
`447`-style branch, and case `49` aliases `121/125/204` to the `field_44`
setter at opcode 448. These low-numbered entries are now routed through the
same movement provider.

Native case `52` aliases `88/502`: it ORs integer operand 0 into the low 14
bits of `flags.word_00`; if bit 5 is active afterward, it walks every
`EnemyAnimationLink` and invokes the exact recursive flag-0 clear leaf at
`0x00450120`. Adjacent case `53` / opcode 503 now clears the selected low 14
bits and, when bit 5 is inactive afterward, walks the same animation-link
vector and invokes the exact recursive flag-0 setter at `0x0044FA30`.
The original native case blocks are each 1,472 bytes / 296 instructions, with
four ordered calls apiece; the focused verifier checks both selector/pointer
entries and all eight E8 targets. A host regression test covers the active,
cleared, and already-inactive bit-5 paths. The 41,967-byte parent remains
partial and NONEXACT.

The movement boundary has also been expanded from only the 400-448 range
to its native jump-table aliases. The aliases are canonicalized to the matching
movement operation before entering the same maintained helper: `57/61 -> 402`,
`13/56 -> 403`, `53/108/180 -> 430`, `49/77 -> 411`, `65 -> 414`,
`69/236 -> 415`, `89 -> 419`, `133 -> 410`, `76/93/120 -> 426`, `97 -> 432`,
`101/149 -> 433`, `153 -> 435`, `157/212 -> 442`, `105 -> 443`, and
`109/113 -> 446`. These are native shared-case aliases, not new independent
function bodies; no duplicate byte credit is assigned.

The remaining inline cases in the original 41,967B body, including most of the
300-series, unhandled 500-series cases, other 520-series operations and
additional opcode ranges, still need source recovery. The maintained root now
also represents 609/610/611/612, 614, 621, 702/703/711/712/713 and
800/801/802, alongside 324, 524/575, 527/534, 539, 548, 549, 551, 552,
553/554, 555 and reserved selector 569. These fragments do not close their
surrounding switch tables or the dispatcher as a whole. Unknown opcodes
currently fall through the provisional zero return and must not be treated
as proven native no-ops. The 41,967-byte root remains NONEXACT and has no whole-root
match unit; exact callee units are credited separately.

## Focused evidence

The spawn leaf and dispatcher compile as MSVC-compatible i386 COFF under the
locked `/Od /Ob0` profile. The animation-link clear and opcode-303 spawn units
strictly replay as 50/50 and 398/398 bytes; the positioned flag-2 AnimationFile
wrapper strictly replays as 61/61 bytes, each with all original relocation
targets. The 43-byte selected-Enemy guard leaf also strictly replayed. The
`AnimationFile.hpp` change rebuilt its affected include closure locally: 345/345
units across 113 cold objects passed. No whole-graph replay was run. The 653-byte
spawn leaf remains limited by the 14 float-argument stack-order bytes noted
above.

The five pre-existing helper/root translation units also compile as MSVC-compatible i386 COFF
under the repository's locked `/Od /Ob0` profile:

```bash
scripts/compile-probe.sh src/EnemyStateMovementOpcode.cpp build/core209-canonical/EnemyStateMovementOpcode.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/compile-probe.sh src/EnemyStatePatternOpcode.cpp build/core210-canonical/EnemyStatePatternOpcode.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/compile-probe.sh src/EnemyStateControlOpcode.cpp build/core211-canonical/EnemyStateControlOpcode.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/compile-probe.sh src/EnemyStateDynamicParameterOpcode.cpp build/core212-canonical/EnemyStateDynamicParameterOpcode.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/compile-probe.sh src/EnemyStateExecuteOpcode.cpp build/core209-canonical/EnemyStateExecuteOpcode.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
```

The maintained dispatcher verifier currently compiles **35** locked-profile
i386 COFF source units and executes the committed root-host case families
under ASan/UBSan. Its focused native checks include the 609-612 shared
1,457B/314-instruction/29-E8 branch, the 614 572B/129-instruction/19-E8
queue-copy branch, the 621 346B/70-instruction/7-E8 mesh branch, the four
Laser branches (2,699B/607 CFG heads/62 E8), the 712 196B/42-instruction/9-E8
rectangle-cancel branch, and the 800-802 script-control branches
(627B/128 instructions/25 E8). It also checks the committed 553/554 setter
maps and their ordered COFF relocations. Exact leaf replay receipts and
explicit host-fixture boundaries are recorded in each linked case frontier.
This 35-unit result is the committed baseline before the uncommitted opcode
620 work described in [the current handoff](RE_HANDOFF.md). No full cold
replay or whole-root byte credit is claimed.

No assembly, byte padding, or synthetic instruction sequences are used. The
next major step is to restore and test the remaining inline case families in
the original root, then compare whole-root code and relocation boundaries.

## Animation flag cases 502/503

The two adjacent native switch cases have now both been reconstructed in the
maintained C++ root. Case 52 / opcode 502 ORs the low fourteen operand bits and
recursively clears flag zero when bit five is active. Case 53 / opcode 503
clears those operand-selected bits and recursively restores flag zero when bit
five is inactive after the update. The 50-byte setter at `0x0044FA30` is a
separate strict-exact leaf; the root and its inline opcode cases are still
NONEXACT. `scripts/verify-enemy-state-dispatch-frontier.py` checks the native
1,472-byte case ranges, selector and jump-table entries, ordered call maps,
source routing, i386 compilation, and the three opcode-503 runtime conditions.

## ScreenInf opcode 517

The 99-byte native case at `0x00493F8E` reads ECL operands 2/1/0, then creates
a mode-1 ScreenInf through the already whole-exact 81-byte factory at
`0x004250F0`, passing operands 0/1/2 and three trailing zero values. The
maintained helper uses explicit sequential reads and preserves the native
argument order. The focused verifier checks the native selector and pointer,
all 25 instructions and the four E8 targets; its host fixture checks the
resulting factory arguments. The 41,967-byte dispatcher remains NONEXACT.

## Opcode 518 FrontInf dialogue lifetime dependency

The adjacent opcode 518 case calls the 626-byte FrontInf dialogue-command
method at `0x004B9740`, then clears Bullet, Laser and Enemy controllers. Its
existing-dialogue replacement path now has a strict-exact 97-byte release
wrapper at `0x004AE830` and a strict-exact 16-byte `std::destroy_at<Dialogue>`
helper at `0x004AE9F0`. The release wrapper preserves its original lock-slot-1
and scalar-delete sequence. The 626-byte parent and opcode-518 case are still
open; no completion credit is inferred from these lifetime leaves.

The same opcode-518 dialogue path uses `SoundInf::enqueue` at `0x00428C90`
for its voice/music command. That 328-byte command-queue writer now has a
natural C++ source frontier and a focused host test; its 324-byte candidate is
explicitly NONEXACT. Its 23-byte indexed `SoundCommand` view is independently
strict exact. See [the SoundInf queue frontier](SOUND_INF_ENQUEUE_323_NATIVE_FRONTIER.md).
