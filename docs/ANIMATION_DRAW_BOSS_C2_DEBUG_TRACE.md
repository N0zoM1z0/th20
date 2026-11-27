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

## Wine/VCTIP debugger caveat

`c1xx.dll` contains a VCTIP named-pipe path whose literal is `\\.\pipe\VCTIP_14.44.35211.0_PIPE`; the nearby diagnostic text is `Failed to open connection to VCTIP`. One path can raise Windows exception `0x80000003` around C1xx RVA `0x1b1b14`. Treat this as a compiler telemetry/debug-break path, not as proof of a codegen failure. GDB must distinguish this event from a real compiler exception and verify the compiler's final exit status and object output.

## Next debugging steps

1. Capture the `-il` in-memory pointer at `InvokeCompilerPassW`, validate its mapping and extent, and preserve a bounded dump.
2. Continue from the C2 entry into the actual compile dispatch; distinguish option parsing and telemetry from function lowering.
3. Identify the C2 functions responsible for SSE scalar lowering, physical-register selection, and spill insertion, then inspect their live operands/register state for the four residual mode-45/46 cases.
4. Keep all compiler probes targeted to `AnimationDrawBoss.cpp`; do not run a full cold replay for each experiment.
5. Preserve each useful source/codegen frontier in a local commit with the required `gpt-web:` prefix. A successful compile or commit is not exactness evidence; only the repository's canonical targeted replay can establish accepted exactness.
