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

## 2026-11-27 typed-IL segment and worker-dispatch follow-up

The VCTIP pipe is now serviced by a local diagnostic stub in the pinned Wine
prefix. This is deliberately a minimal consumer, not a replacement for the
Microsoft telemetry service. With it running, the real `cl.exe` → C1xx → C2
compile completes successfully; the `AnimationPoolOwner::draw` object body is
**5,969B/1,497 i386 instructions** against the **5,993B/1,501-instruction**
native body. The object as a whole is 14,573B. The live C2 `InvokeCompilerPassW`
entry still receives 22 arguments and is reached with `-il` pointing to an
in-memory typed-IL object.

The `-il` object is not a flat byte stream. Its first five qwords are pointers
to five separately allocated segments; the next five qwords at `+0x28` are
their lengths: **0x346DB, 0x1E321, 0x6B6C5, 0x3AAF, 0x760D1** respectively
(about 1.28MB total). All five full ranges were captured from the live compiler
process. Initial string inspection identifies source/file and identifier
material in the first segments and C++ type names in the final segment; the
opaque middle record stream and exact per-segment schemas remain undecoded.
The dumps are temporary investigation artifacts under `.analysis/`, not
canonical source or committed binaries.

The C2 instrumentation-record entry at RVA `0x1D1E20` is now reached with a
valid vector object while the local pipe consumer is present. The previously
faulting growth/write path at `0x1D1FED` is not taken in this run. The stub
observed pipe messages of 80B, 261B and 412B; these are transport/diagnostic
records, not evidence that any compiler optimization pass has been identified.

**Worker-thread frontier:** C2 imports MSVC threadpool helpers, but the
`__std_create_threadpool_work` / `__std_bulk_submit_threadpool_work` entrypoints
were not called in this compile. The actual worker creation path is through
`_beginthreadex`; `NtCreateThreadEx` and `RtlCreateUserThread` were each observed
eight times. A `_beginthreadex` stack exposes a C2 worker entry candidate at
RVA `0x36CB38`. Static disassembly shows a generic wait/dispatch loop: it uses
worker-context fields at `+0x10` and `+0x20`, then calls the function pointer at
`+0x20`. This is a worker trampoline, **not yet the function-level codegen
callback**. The callback target and context schema remain the next concrete
breakpoint target. A multi-thread GDB all-stop attempt caused an internal
remote-debugger error when several worker threads reached one shared entry
breakpoint, so future tracing should capture the `_beginthreadex` callback
before resuming the new thread and use one-shot breakpoints.

No boss-function exactness credit is claimed by these diagnostics. The
remaining 24B/4-instruction difference is still open; the typed-IL and worker
callback evidence is intended to explain it at the compiler level rather than
mask it with padding or assembly.

## 2026-11-27 `/Od` interference-to-stack-allocation state trace

The pass-name strings were cross-referenced through RIP-relative loads inside
real `.pdata` function extents, then checked against a live compile of the
current `AnimationDrawBoss.cpp`. This distinguishes normal code from chained
EH funclets: the `RegSimpleAssign` string at `.rdata+0x872010` is referenced
from the chained range `0x3DF56A..0x3DFB8A`, not from a separately executed
normal-path function. Do not use that funclet range as the allocator entry.

The actual normal-path sequence for the target function is:

| Role | C2 RVA | Live evidence |
| --- | ---: | --- |
| Build Interferences | `0x0F7964` | Hit once on the draw worker |
| Stack/codegen allocation pipeline | `0x0F7604` | Hit once on the same worker |
| RegSimpleAssign wrapper call site | `0x0F769F` | Hit once between those stages |
| RegSimpleAssign wrapper | `0x3153A0` | Hit once, called with the draw function object |
| Wrapper metadata helper | `0x034044` | Hit once with argument `4` |
| Predicate | `0x315488` | Called with `4` and `0x25`; both return `1` |

Static disassembly shows the wrapper's other helper at `0x31540C` saves/restores
a TLS bit around the pass. `0x034044` initializes a per-thread 0xB0-entry
pointer table and walks the function's linked type/symbol metadata, invoking
`0x119FF8` and `0x123F8C` for qualifying nodes. The wrapper and both predicate
calls leave the sampled function-object bytes unchanged. This is evidence
about the pass boundary and its setup, not proof that the predicate itself
performs physical-register assignment.

A live object snapshot provides a stronger boundary than pass-name guessing.
At `Build Interferences` entry, function-object `+0x10` points to
`0x...E0118` and the qword at `+0x148` is `0x0020680A00000000`. By the time
`Stack Allocation` starts, `+0x10` points to `0x...952B18` and `+0x148` is
`0x0030680A00000004`; `+0x150` remains `0x4000`. The RegSimpleAssign wrapper
runs after that state transition and does not further change those sampled
fields. The exact owner of the `+0x10` replacement and the flag-bit meanings
remain open; do not label them as a register map until their consumers are
identified.

The captured C1 typed-IL identifier segment also contains the actual local
names used by this function. In segment 1, the shared `position`/`height`/
`width` declarations precede the mode-local `adjusted_scale`, `quad_count`,
`second_color`, `aux_half`, `inherited_scale`, and `first_color` records; later
records contain the mode45/46 `half_for_scale`, `secondary_color`, and
`primary_color` names. The surrounding record bytes are retained, but their
field schema is not yet decoded, so the names alone do not establish stack
slot ownership.

**Next experiment:** trace the `+0x10` object through the Build Interferences
return and the Stack Allocation return, decode the referenced local-record
metadata against the typed-IL segment, and only then alter the current
5,969B/1,497-instruction C++ candidate. The native 5,993B parent remains
NONEXACT; no padding, inline assembly, or exactness credit is claimed.

## 2026-11-27 C2 function-arena cleanup and exact reset callsites

A hardware write watchpoint on the target function object's +0x10 field was
correlated with entry breakpoints on C2's cleanup routine. This corrects the
earlier coarse interpretation that the pointer replacement belonged to the
Stack Allocation entry itself.

The writer at C2 RVA 0x04C4D2 is inside a chained EH funclet, not an
independent normal-path function. .pdata identifies parent
0x04C340..0x04C3D7; the child range 0x04C3D7..0x04C599 has unwind flags
CHAININFO and points back to that parent. The parent traverses the
function-owned linked metadata list and checks node byte +0x0C and function
state at +0x14C. Its cleanup funclet reinitializes a 0x58-byte pool header:
type 3 at +0x20, chunk size 0x2A0 at +0x28, alignment 0x40 at +0x30,
then installs it with mov [rsi+0x10],rbx. This establishes +0x10 as a
function-owned pool/arena handle; it is not a physical-register map.

The live compile was repeated with both the parent entry and a write watchpoint
installed before C2 started. For the same AnimationPoolOwner::draw object,
the nine parent-cleanup invocations and two actual pointer changes correlate
as follows:

| Parent hit | Caller return RVA | Pointer before | Pointer after |
| ---: | ---: | --- | --- |
| 1 | 0x0DF6F8 | 0x...A30118 | unchanged |
| 2 | 0x0DBCDF | 0x...A30118 | unchanged |
| 3 | 0x0DBCDF | 0x...A30118 | unchanged |
| 4 | 0x0DF76C | 0x...A30118 | 0x...A25618 |
| 5 | 0x0DBCDF | 0x...A25618 | unchanged |
| 6 | 0x0C1630 | 0x...A25618 | 0x...9A2B18 |
| 7-9 | 0x0DBBFA | 0x...9A2B18 | unchanged |

The two changing callsites are reached from within the target
Build Interferences function (0x0F7964): its call at 0x0F7D9A enters
helper 0x0DF6A4, whose cleanup call at 0x0DF767 performs the first reset;
its call at 0x0F8017 enters helper 0x0C13FC, whose cleanup call at
0x0C162B performs the second. The direct call at 0x0F8094 is a different
cleanup path and did not account for either watched pointer change.

The later cleanup invocations at caller 0x0DBBFA update the opaque qword at
+0x148 without changing the arena pointer: it advances from
0x0020680A00000000 to 0x0030680A00000000, then to
0x0030680A00000004. Their bit meanings are not yet decoded. Stack Allocation
entry (0x0F7604) sees the final arena pointer and final sampled state.

This gives a concrete lifetime boundary for C2's function-owned temporary
arena across the interference subroutines. It does not yet map the
C1-named half_for_scale/adjusted_scale records to individual arena nodes,
nor explain the four missing scalar XMM reloads. Do not infer either from the
arena reset alone.

## 2026-11-27 mode 35/36 first inherited-scale result: native frame slot recovered

The apparent mode-36 four-byte frame displacement was traced to the first
`animation_inherited_aux_scale_x(animation)` call in each case. The
reconstruction previously expressed these as discarded expression statements.
In the current C2 output that lowers to `fstp st(0)`, so no local home is
reserved. The original native function instead stores each first getter result
to `[ebp-0x160]`.

A natural source-level local restores this behavior:

```cpp
[[maybe_unused]] float first_inherited_scale;
```

Both case 35 and case 36 now assign their first getter result to that local.
The local is function-scoped and the same home slot is reused by the two
mutually exclusive switch cases. No inline assembly, padding, volatile access,
or synthetic instruction was introduced.

The C2 pass trace proves the new symbol is present before stack allocation as
`_first_inherited_scale` with provisional slot `-4`. At
`Calculate Frame Info`, it becomes `-352`, i.e. native EBP displacement
`-0x160`. The final object emits `fstp dword ptr [ebp-0x160]` for both
first getter calls.

The resulting mode-35 native stack layout is recovered:

| Local | EBP displacement |
| --- | ---: |
| first inherited-scale result | `-0x160` |
| adjusted_scale | `-0x15C` |
| quad_count | `-0x158` |
| second_color | `-0x150` |
| first_color | `-0x154` |
| aux_half | `-0x14C` |
| inherited_scale | `-0x148` |

The resulting mode-36 layout is also recovered:

| Local / temporary | EBP displacement |
| --- | ---: |
| first inherited-scale result | `-0x160` |
| first color result | `-0x16C` |
| second color result | `-0x170` |
| quad_count | `-0x174` |
| half_for_scale | `-0x168` |
| inherited_scale | `-0x164` |
| adjusted_scale | `-0x178` |

This corrects the earlier working hypothesis that the three mode-36 C1
symbols absent from the C2 named-local table were responsible for the
four-byte shift. They remain relevant to the named-local versus temporary
lowering investigation, but they are not the cause of this frame displacement:
the decisive difference was the discarded first getter result.

Validation used only the AnimationDrawBoss translation unit and C2 pass
breakpoints, not a full cold replay. The source build's target function is
6300 bytes and is byte-identical to the tested first-function source variant;
all 235 COFF relocation records also compare identical. The C2 frame-info
snapshot agrees with the original native offsets above.
