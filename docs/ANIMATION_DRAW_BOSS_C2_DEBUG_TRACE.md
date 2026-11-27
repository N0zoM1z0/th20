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

This establishes that the C2 backend consumes typed IL through an in-memory pointer for this translation unit. A later live capture now preserves the complete five-segment object; its segment formats are still opaque and the function-level lowering path remains unlocated.

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

The driver entry's control flow now explains why the earlier `0x1d3d3c` breakpoint did not fire. At RVA `0x1d01a8`, after its startup allocations and TLS setup, it tests a global configuration word at the branch around `0x1d0284`. The observed `/Od` compile takes the zero-config path through `0x1d0124` and `0x1ce92c`; only the alternate nonzero-config path at `0x1d0373` calls `0x1d3d3c`. Therefore `0x1d3d3c` is not a mandatory per-function pass for this compile, and its non-hit is expected. Do not classify it as lowering or register allocation.

The function at `0x1d1e20..0x1d223b` (1,051 bytes) remains independently classified as an instrumentation-record writer, not function lowering or register allocation. It walks a record-buffer cursor, tests current/end pointers, emits six 0x30-byte records with tags `0x140002`, `0x140004`, `0x140005`, `0x140006`, `0x140007`, and `0x140003`, calls append helpers at `0x264e8c`/`0x264c48`, clears the record byte at `+0x28`, and advances by `0x30`. The tag/data pairs draw from six global table offsets `+0x60` through `+0x100`.

The earlier debugger run without a VCTIP listener faulted at RVA `0x1d1fed`, the record-tag store, with `eax=0x140002` and an invalid `rdi=0x6fffff483f07` in the Wine KernelBase mapping. That failure is now distinguishable from a source or C2 lowering failure: after supplying a local named-pipe sink, the same writer entry is reached without reproducing the fault and the compiler completes. The causal role of the missing VCTIP service is strongly supported by this A/B result, although the original record-buffer ownership is still not fully proven.

**2026-11-27 VCTIP runtime and typed-IL capture:** Wine Mono is still absent, so the bundled .NET `vctip.exe` cannot be launched. A separate native C++ named-pipe sink was instead hosted beside `cl.exe` by a Windows supervisor in the same Wine process tree. This is a byte-stream sink for the optional telemetry connection, not a claim to have reimplemented the full VCTIP service. The C1xx/C2 clients connected and disconnected normally; the sink captured three messages of 80, 261, and 412 bytes. The targeted `AnimationDrawBoss.cpp` compile then returned zero and produced a 14,581-byte COFF object.

At `InvokeCompilerPassW`, `-il` resolves to an in-memory object whose first five qwords are pointers and whose next five qwords are 64-bit segment lengths. The five complete segments were captured using those lengths, not guessed fixed windows:

| Segment | Length | SHA-256 | Observed printable content (not a full format classification) |
| --- | ---: | --- | --- |
| 0 | `0x346db` | `d955ba6a3215b090c8f202ade3f5a7bbf5135a901d651cecac3c6e591899ebff` | source/include paths and serialized records |
| 1 | `0x1e321` | `cbb3b8db1f670d3d16348f30edf27c0bc520be49a0110698b3a215c4860dc0f3` | identifiers such as `_Right`, `_Left`, `_SourceSize`, `_DestinationSize` |
| 2 | `0x6b6c5` | `15169a0cffa7fc6838d315383b59476cb49e54248b7279cc8a2d2f8cd810aff0` | sparse/record-like binary data; not yet decoded |
| 3 | `0x3aaf` | `486340f461613df3be4cc10cd22dae894e63f91c0f77577bcd9b3e19294329ef` | exception diagnostic strings, including `bad allocation` and `bad cast` |
| 4 | `0x760d1` | `d0641480ba94366b6ade387e875ff5be514224cb5b1d8932eb4b91c193a130b2` | type names including `std::byte` and MSVC RTTI-style names |

These observations prove the five-segment typed-IL payload is accessible and reproducible for the targeted translation unit. They do **not** yet identify the semantic schema of each segment or the C2 function-level lowering/register-allocation pipeline. Eight C2 worker threads are created during the compile, so the next live trace must follow their task-entry/dispatch path rather than assume that all useful work occurs on the main thread.

A naive GDB attempt to skip the record writer by popping a return address remains rejected: one entry had a zero stack-top value, so it is not safe to treat every entry as an ordinary call/return.

**Corrected conclusion:** `InvokeCompilerPassW` and the `0x1d01a8` argv entry
prove that C2 receives typed in-memory IL and 22 wide arguments. They do not
identify the function-level lowering, physical-register selection, or spill
insertion passes. Those remain open and require new breakpoints grounded in
static/live call flow rather than names guessed from nearby telemetry.

## Wine/VCTIP debugger caveat

`c1xx.dll` contains a VCTIP named-pipe path whose literal is `\\.\pipe\VCTIP_14.44.35211.0_PIPE`; the nearby diagnostic text is `Failed to open connection to VCTIP`. One path can raise Windows exception `0x80000003` around C1xx RVA `0x1b1b14`. Treat this as a compiler telemetry/debug-break path, not as proof of a codegen failure. GDB must distinguish this event from a real compiler exception and verify the compiler's final exit status and object output.

## Next debugging steps

1. Decode the five typed-IL segments structurally and trace their pointer/length consumers; do not infer segment semantics from a few printable strings.
2. Follow the eight C2 worker threads from their task-entry/dispatch path and locate the per-function compile work.
3. Identify the C2 functions responsible for SSE scalar lowering, physical-register selection, and spill insertion, then inspect their live operands/register state for the four residual mode-45/46 cases.
4. Keep all compiler probes targeted to `AnimationDrawBoss.cpp`; do not run a full cold replay for each experiment.
5. Preserve each useful source/codegen frontier in a local commit with the required `gpt-web:` prefix. A successful compile or commit is not exactness evidence; only the repository's canonical targeted replay can establish accepted exactness.
