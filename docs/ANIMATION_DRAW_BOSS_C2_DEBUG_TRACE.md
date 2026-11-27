# TH20 AnimationPoolOwner::draw — MSVC C2 debugger trace

Date: 2026-11-27

## Scope

This note records a compiler-debugging checkpoint for the large `AnimationPoolOwner::draw` reconstruction at target VA `0x00443880` (the 5,993-byte native body). It is investigation evidence only: it does not claim a codegen match, semantic ownership, or accepted replay evidence. The current local source frontier remains the 24-byte residual described by the draw-boss frontier note.

## Compiler host and ABI

The installed compiler backend is at:

` .tools/msvc/VC/Tools/MSVC/14.44.35207/bin/HostX64/x86/c2.dll `

The game target is x86, but this backend DLL is hosted by the x64 compiler process. Debugger work must therefore use the x64 Windows ABI and 64-bit GDB registers (`rcx`, `rdx`, `r8`, `r9`, `rip`, etc.); do not copy VC7.1/TH10 32-bit register assumptions or absolute addresses.

The C2 exports found in the PE export table include:

- `DllGetObjHandler` — RVA `0x268530`
- `InvokeCompilerPassW` — RVA `0x268c60`
- `InvokeCompilerPass` — RVA `0x4d85bc`
- `AbortCompilerPass` — RVA `0x4d83d0`
- `CloseTypeServerPDB` — RVA `0x2993a8`

The runtime image base is relocated by Wine/ASLR. Derive it from the loaded-module range in GDB on every run; never hardcode a prior session's base.

## Live compiler observations

A targeted compile of `src/AnimationDrawBoss.cpp` was launched under `winedbg --gdb --no-start`, and GDB successfully caught the C2 DLL load and stopped at `InvokeCompilerPassW`. The entry used the x64 ABI and received 22 wide command-line arguments. The observed backend arguments include:

- `-il` followed by a decimal in-process address
- `-typedil`
- `-in_memory_il`
- `-f` followed by `src/AnimationDrawBoss.cpp`
- `/Ob0`, `/Gy`, `/Zl`, `/archSSE2`, `/GS`, `/EHs`, and the SDL mode switch
- object and PDB output paths

This establishes that the C2 backend consumes typed IL through an in-memory pointer for this translation unit. The `-il` address is a promising next observation point; the bytes behind it have not yet been successfully captured or decoded.

The first internal functions reached after `InvokeCompilerPassW` include startup, argument parsing, and tracing/telemetry. Static disassembly shows that some candidate addresses (including the command-line parser and trace callback) are not register-allocation or code-generation passes. Do not label them as such merely because they are called from the C2 entry path. The actual per-function lowering/register-allocation path remains to be identified.

## 2026-11-27 follow-up: reclassify the C2 RVA `0x1d01a8` entry

A second targeted trace used the particle-grid translation unit to validate the
internal C2 entry reached after `InvokeCompilerPassW`. The function at C2 RVA
`0x1d01a8` is **not** a per-function code-generation pass or register allocator.
Its disassembly begins by preserving `rdx` in `rsi` and `ecx` in `r14d`, then
publishes those values as the compiler argument count and argument-vector
pointer. At runtime the values were `rcx = 0x16` and `rdx` pointed to 22
wide-character command-line argument pointers. This is command-line/driver
setup, consistent with its downstream startup and option-processing calls.

The same trace observed calls into C2 RVAs `0x1d5a00`, `0x1d764c`, `0x1d4294`,
`0x1d59e0`, and `0x1d1490`, but their roles are **not yet established**. The
candidate phase-dispatch address `0x1d3d3c` was not hit in that run. A nearby
C2 `int3` at RVA `0x1d1e1f` precedes an unclassified record/vector-append path;
a later write at RVA `0x1d1fed` faulted while targeting the Wine
`RaiseException` code address. The compiler still emitted its object and
returned zero after GDB detached, but this is not code-generation evidence and
must not be interpreted as a failed source compile or as a register-allocation
pass. The C1xx VCTIP path and this C2 record path are kept distinct.

**Corrected conclusion:** `InvokeCompilerPassW` and the `0x1d01a8` argv entry
prove that C2 receives typed in-memory IL and 22 wide arguments. They do not
identify the function-level lowering, physical-register selection, or spill
insertion passes. Those remain open and require new breakpoints grounded in
static/live call flow rather than names guessed from nearby telemetry.

## Wine/VCTIP debugger caveat

`c1xx.dll` contains a VCTIP named-pipe path whose literal is `\\.\pipe\VCTIP_14.44.35211.0_PIPE`; the nearby diagnostic text is `Failed to open connection to VCTIP`. One path can raise Windows exception `0x80000003` around C1xx RVA `0x1b1b14`. Treat this as a compiler telemetry/debug-break path, not as proof of a codegen failure. GDB must distinguish this event from a real compiler exception and verify the compiler's final exit status and object output.

## Next debugging steps

1. Capture the `-il` in-memory pointer at `InvokeCompilerPassW`, validate its mapping and extent, and preserve a bounded dump.
2. Continue from the C2 entry into the actual compile dispatch; distinguish option parsing and telemetry from function lowering.
3. Identify the C2 functions responsible for SSE scalar lowering, physical-register selection, and spill insertion, then inspect their live operands/register state for the four residual mode-45/46 cases.
4. Keep all compiler probes targeted to `AnimationDrawBoss.cpp`; do not run a full cold replay for each experiment.
5. Preserve each useful source/codegen frontier in a local commit with the required `gpt-web:` prefix. A successful compile or commit is not exactness evidence; only the repository's canonical targeted replay can establish accepted exactness.
