# UCRT signal actions, raise boundaries and exception filtering

Seven complete Windows SDK 10.0.26100.0 x86 `libucrt.lib` contributions from
`signal.obj` and `exception_filter.obj` establish nine pending origins and
three recovered entries in the locked Japanese TH20 Steamless target. Their
1,102 instruction bytes, one trailing INT3 and all 228B of owned state,
constants, default action table and SEH metadata agree. The old overlapping
raise candidate is replaced by disjoint partitions of its complete owner.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x005529D7` | 326 | `_seh_filter_exe` |
| `0x005572D3` | 89 | SIGABRT guarded-query primary |
| `0x0055732C` | 3 | recovered query exception entry |
| `0x0055732F` | 12 | query unlock funclet |
| `0x0055733B` | 66 | global action lookup |
| `0x0055737D` | 40 | per-thread signal lookup |
| `0x005573A5` | 39 | `__acrt_get_sigabrt_handler` |
| `0x005573CC` | 30 | `__acrt_initialize_signal_handlers` |
| `0x005573EA` | 376 | raise primary |
| `0x00557562` | 18 | recovered raise exception entry |
| `0x00557574` | 16 | raise conditional unlock funclet |
| `0x00557584` | 87 | recovered raise continuation and default exit tail |

## Complete owners and corrected overlap

The 104B guarded query comprises 89B primary, recovered 3B exception prefix
and the existing 12B unlock. Its 28B SEH table at `0x005AC460` has header
`-2,0,-44,0` and record `-2,0,0x0055732C`. That exception entry reloads ESI
before falling into the unlock closure. Ordinary completion calls the
12B unlock directly. The outer 39B getter constructs closures containing
signal lock ID 3; decoding the abort handler occurs while holding that lock.

Raise's old 497B primary overlapped the separately listed 16B unlock. The
whole 498B SDK section instead contains 376B primary, 18B exception prefix,
16B unlock, 87B continuation and one INT3 at `0x005575DB`. All original
497 instruction bytes remain covered once. Its full 28B SEH table at
`0x005AC440` has header `-2,0,-72,0` and record `-2,0,0x00557562`. The
exception prefix reloads the signal, PTD, global-action flag, saved handler
and ignore flag, then enters the existing conditional unlock. Normal
completion calls the 16B entry directly. Primary branches establish the
continuation's ownership, including the shared epilogue and `_exit(3)` tail.

Ghidra omits both exception prefixes. Pinned decoding covers all seven
missing instructions, while whole SDK sections and original relocated SEH
targets establish their roles. The signal interval is contiguous from
`0x005572D3` through `0x005575DB`; the separate 326B executable filter retains
its complete original extent. No tail is shortened to obtain agreement.

## Global state and default exception table

Four complete 32-bit BSS slots occupy `0x005E55E8..0x005E55F7`:

| Signal | Slot | Storage |
| --- | --- | --- |
| SIGINT/2 | `0x005E55E8` | encoded global handler |
| SIGBREAK/21 | `0x005E55EC` | encoded global handler |
| SIGABRT/22 and compatibility value 6 | `0x005E55F0` | shared encoded global handler |
| SIGTERM/15 | `0x005E55F4` | encoded global handler |

The 30B initializer copies its supplied encoded-null value into every slot;
it does not encode its argument again. Loader-zero BSS is distinct from
the initialized encoded SIG_DFL value. The separately defined console-handler
registration flag is not referenced by these compared owners and remains
unlocated. Unsupported global lookup returns null without setting errno.

The complete default table at `0x00599348` has twelve 12B records: exception
number, signal number and zero default action. The first three are access
violation/SIGSEGV and illegal/privileged instruction/SIGILL. Nine consecutive
FPE records follow: denormal, divide-by-zero, inexact, invalid, overflow,
stack check, underflow, multiple faults and multiple traps. All 144 bytes
match a unique complete SDK data contribution; earlier reviewed PTD
construction/destruction references independently identify the same table.

The full DWORD constants at `0x005993D8`, `0x005993DC` and `0x005993E0`
are respectively table count 12, first FPE index 3 and FPE count 9. The
per-thread lookup scans 12B records and returns the first matching signal.
The unreferenced SDK table-size constant receives no target address claim.
Together, the 16B globals, 144B table, 12B constants and two 28B SEH tables
form the complete 228B data scope.

## Raise dispatch, reset and restoration

Raise accepts global signals 2, 6, 15, 21 and 22, and per-thread exception
signals 4, 8 and 11. The latter use the nullable PTD getter and its action
table. Missing PTD returns -1 without adding an errno store; missing table
entry or unsupported signal sets EINVAL/22, calls the returning invalid
parameter dispatcher and returns -1.

Only global actions acquire signal lock 3 and decode their stored pointer.
Per-thread actions are loaded raw. SIG_IGN/1 returns zero through the
finally path. SIG_DFL/0 explicitly releases any global lock before the
nonreturning `_exit(3)` call. Other handlers are reset before invocation,
and the global lock is released before user code runs.

For exception signals, PTD exception pointers at +4 are saved and cleared.
SIGFPE also saves the code at +8, assigns `_FPE_EXPLICITGEN`/0x8C and resets
all nine local FPE action fields to raw zero. The non-FPE reset writes the
encoded-null cookie even when the selected action was per-thread; the
original source and native store both retain this behavior. No normalized
raw-zero replacement is introduced.

SIGFPE invokes the handler with two cdecl arguments `(8, fpecode)`; other
signals pass only the signal number. The previously reviewed guard-check
pointer remains on each indirect callback path. Saved PTD exception pointers
and FPE code are restored after an ordinary handler return. The finally
protects the global lock, rather than providing a separate restoration
handler around user callbacks.

## Executable SEH filter

The executable filter uses the same nullable PTD and twelve-record exception
table. Missing PTD, absent exception or SIG_DFL returns continue-search/0.
SIG_DIE/5 resets that action to zero and returns execute-handler/1.
SIG_IGN/1 returns continue-execution/-1. A user handler temporarily receives
the actual exception-pointer structure in PTD +4.

The FPE path resets all nine action fields and maps the native exception to
its original FPE code: invalid 0x81, denormal 0x82, divide 0x83, overflow
0x84, underflow 0x85, inexact 0x86, stack overflow 0x8A, multiple traps
0x8D and multiple faults 0x8E. It invokes the two-argument handler and
restores the previous FPE code. Other signals reset their action to raw
zero and invoke the one-argument handler. Normal return restores exception
pointers and resumes execution with -1. The SDK's DLL-filter wrapper and
separate lookup have no complete target match and receive no body credit.

## Evidence and next scope

Private `.analysis/origin-boundary/signal-actions/` retains complete SDK
members, full-section search/relocation results, attested `native.txt` and
`filter-native.txt`, `review.py`, `reviewed.json`, and the original overlapping
ledger rows. The audit compares every ordinary byte, original REL32/DIR32
role and PE HIGHLOW, complete branch/call closure, both exceptional prefixes,
all owned data and alignment. The already reviewed 27B pointer decoder is
also compared as a shared dependency, without duplicate origin credit.
Source is `ucrt/misc/{signal,exception_filter}.cpp` and the installed
`signal.h`/`float.h` definitions.

The preceding reporter search found no ASCII or UTF-16 copies of its runtime
banner, unknown-program text, library caption or abort message. The already
reviewed abort body follows the SDK release path, whose runtime-message call
is debug-only. Larger reporter sections have no complete match. Continue
from actual retained calls instead of assigning a nearby body to that
reporter. Unlocated signal installation, console-event handling, abort
behavior setter and error-mode setter remain separate questions.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes are unchanged. Exact replay
scope is **zero units**; no authored or maintained-source exact credit is added.
