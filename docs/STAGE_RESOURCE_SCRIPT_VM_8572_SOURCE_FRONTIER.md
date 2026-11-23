# StageResource Background VM — 8,572-byte source frontier

## Native boundary and owner

The native VM entry is `0x004751B0`, with function extent `0x004751B0..0x0047732B` (8,572 bytes). Ghidra reports 8,557 instruction addresses within that extent; the remaining 15 bytes are retained as part of the native function range and are not separately attributed here. The original caller is the Background update path at `0x00472100`, which supplies the `0x3310`-byte ScriptState subobject at Background owner `+0x10`.

The production view is `StageBackgroundScriptState` (an alias over the established `StageBackgroundFogOwner` layout) and the enclosing neutral `StageResourceOwner`. The original C++ class spellings remain unproven. The recovered owner layout is `0x336C` bytes; ScriptState is `0x3310` bytes. The instruction stream pointer is owner `+0x3330`; the primitive animation pointer and file header are `+0x3320` and `+0x3324`. `StageResourceFileHeader` is now a complete `0x90`-byte header view with signed `animation_count` at `+0x02`.

Each instruction begins with signed time at `+0x00`, opcode at `+0x04`, signed byte size at `+0x06`, and arguments at `+0x08`. The VM advances the cursor by the signed instruction size, preserving the original variable-length stream protocol.

## Restored boss behavior

`src/StageResourceScript.cpp` restores the main interpreter and camera update behavior as natural C++:

- Timer gating, instruction cursor updates, jumps, and variable-size instruction advancement.
- Camera position, direction, up-vector, FOV and fog interpolation.
- Camera motion modes, including their individual timer periods, wrap behavior and vector updates.
- Background clear color, animation script selection, stop/clear operations, mesh-reset dispatch, animation interruption, and primary rotation-flag dispatch.
- ECL interpolation easing uses explicit scalar SSE rounding after each operation. Reusing the generic `Easing.cpp` evaluation path produced native mismatches; the Background/ECL evaluation order is retained locally.
- Interpolation completion returns the selected endpoint and clamps Timer/duration without overwriting the interpolation object's stored `current` field. This endpoint detail was found by original-CPU differential testing.

The source entry now uses the native one-receiver `__fastcall` ABI. Its clock comes from `timer_clock_sources[0]`, the pointer at `0x005AEFE0`; the CPU test sets the corresponding production and original-image clock pointers to the same rate value.

## Adjacent owner leaves and origin boundary

Three neighboring game-owned helpers are kept as separate C++ source boundaries:

- `0x00477480`, 160 bytes: iterates `file->animation_count` primitive animations and then the eight inline ScriptState animations, forwarding each event to the already exact `0x00477450` bridge. `StageResourceOwner::interrupt_animations` now strictly replays the entire 160-byte body and both original E8 destinations (relocations at `+0x4D` and `+0x93`).
- `0x00477790`, 45 bytes: updates only bit 4 of the primary owner `state_flags` word at `+0x3344`. The natural C++ source is present; its current compiler register ordering is not byte-exact and no exact credit is claimed.
- `0x004776C0`, 130 bytes: the existing exact fog-interpolation setter in `StageResourceFog.cpp`.

The primary owner pointer at `0x005C069C` is now represented as `process_stage_resource`. The Card UI dirty-bit view at the same address is a partial view of the same owner word at `+0x3344`: the UI path uses bit 0, while Background opcode 22 uses bit 4. This is an aliasing owner boundary, not two independent global objects.

These VM and owner helpers are classified as game-authored behavior rather than CRT, SDK, or compiler-generated code. The descriptive source class names remain reconstruction names, not claims about original RTTI or PDB spelling.

## Verification and remaining boundary

Run the focused original-CPU comparison with:

```text
scripts/repo-python scripts/run-stage-resource-vm-cpu.py
```

The current result is **43,080 checks, 0 failures**, comparing the complete `0x3310`-byte ScriptState and the clear-color/rotation global side effects against the locked original PE. This is semantic CPU-oracle evidence, not byte-exactness evidence.

The oracle deliberately leaves resource-owning branches outside its scope: positive ANM rebind, RenderMesh destruction/recreation (opcode 17), and animation interruption (opcode 19). Their production adapters and owner methods are present as natural C++; opcode 19's 160-byte owner traversal has a separate strict native replay, but the runtime resource lifetime path still needs a dedicated native CPU test. Whole Background lifecycle, resource loading, draw integration and exact object-byte replay of the 8,572-byte boss also remain open. The extracted camera/interpolation helpers are source decompositions; no separate native function boundary is claimed for them.
