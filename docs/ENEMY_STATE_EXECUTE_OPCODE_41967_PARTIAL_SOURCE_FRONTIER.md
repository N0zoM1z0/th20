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

The remaining inline cases in the original 41,967B body—including most of the
300-series, unhandled 500-series cases, other 520-series operations and
additional opcode ranges—still need source recovery. Unknown opcodes currently
fall through the provisional zero return and must not be treated as proven
native no-ops. The 41,967-byte root remains NONEXACT and has no whole-root match
unit; the exact callee units above are credited separately.

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
