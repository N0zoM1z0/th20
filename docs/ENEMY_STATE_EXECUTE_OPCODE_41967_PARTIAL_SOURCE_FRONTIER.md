# CORE/RECON-1196 — 41,967B EnemyState::execute_opcode partial C++ source

The original `EnemyState::execute_opcode` root at `0x0048C010` is 41,967
bytes. It is still **NONEXACT** and its full original inline switch has not
been recovered. This checkpoint changes the status from source-absent to a
real maintained C++ entry point and restores the complete contiguous native
movement opcode family 400–448 as a separate natural source fragment.

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
- The root now also routes to the maintained phase, card-start, controller
  setter, fog, membership, mesh, animation-spawn, queued-shot, script-pointer,
  shot-fire, shot-command, laser-parameter, and laser-creation opcode fragments.
- Opcode 560 retains its distinct `return 1` behavior when `Enemy::defeat()`
  requests an immediate same-tick ECL exit. Ordinary handled fragments return
  zero so `EclRuntime::tick` performs the normal instruction advance.

## Remaining scope

This is a **partial root reconstruction**, not an exact or complete dispatcher.
The remaining inline cases in the original 41,967B body—including the other
500-series control/state cases and other unhandled opcode ranges—still need
source recovery. Unknown opcodes currently fall through the provisional zero
return and must not be treated as proven native no-ops. The parent receives no
strict exact-byte credit and no match unit has been added.

## Focused evidence

Both new C++ translation units compile as MSVC-compatible i386 COFF under the
repository's locked `/Od /Ob0` profile:

```bash
scripts/compile-probe.sh src/EnemyStateMovementOpcode.cpp build/core209-canonical/EnemyStateMovementOpcode.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/compile-probe.sh src/EnemyStateExecuteOpcode.cpp build/core209-canonical/EnemyStateExecuteOpcode.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
```

No assembly, byte padding, or synthetic instruction sequences are used. The
next major step is to restore and test the remaining inline case families in
the original root, then compare whole-root code and relocation boundaries.
