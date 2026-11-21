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
  recursive-clear leaf is also strict exact with all three relocations. The
  helper is expressed on `EnemyAnimationLink` because the native call receives
  its leading handle address; this does not assert the original type name. Both
  functions have strict byte/relocation matches, while their original source
  origin remains unclassified and no authored-byte credit is claimed.
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
The remaining inline cases in the original 41,967B body—including most of the
300-series, unhandled 500-series cases, other 520-series operations and
additional opcode ranges—still need source recovery. Unknown opcodes currently
fall through the provisional zero return and must not be treated as proven
native no-ops. The 41,967-byte root remains NONEXACT and has no whole-root match
unit; the exact callee units above are credited separately.

## Focused evidence

The spawn leaf and dispatcher compile as MSVC-compatible i386 COFF under the
locked `/Od /Ob0` profile. The animation-link clear and opcode-303 spawn units
strictly replay as 50/50 and 398/398 bytes with all original relocation
targets. The 43-byte selected-Enemy guard leaf also strictly replayed. Because
`EnemyState.hpp` changed, the affected include closure was rebuilt locally: 125
units across 30 cold objects passed; no whole-graph replay was run. The 653-byte
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
