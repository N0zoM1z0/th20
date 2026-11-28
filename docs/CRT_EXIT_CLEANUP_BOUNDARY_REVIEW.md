# UCRT exit cleanup modes, TLS callbacks and CLR termination

Twelve whole Windows SDK 10.0.26100.0 x86 `libucrt.lib` contributions from
`exit.obj` establish eleven pending origins and four recovered entries in
the locked Japanese TH20 Steamless target. All 818 instruction bytes, thirteen
INT3 bytes and 184B of state, strings, SEH and C++ EH agree. Existing extents
remain unchanged, including common_exit's one already included INT3 byte.

| Entry | Ledger bytes | Role |
| --- | ---: | --- |
| `0x00552B1D` | 65 | cleanup guarded-call primary |
| `0x00552B5E` | 12 | exit-lock unlock funclet |
| `0x00552B6A` | 196 | cleanup action primary |
| `0x00552C2E` | 27 | recovered C++-exception filter |
| `0x00552C49` | 8 | recovered terminate handler |
| `0x00552C52` | 185 | common_exit, 184 instructions plus INT3 |
| `0x00552D10` | 45 | process termination selector |
| `0x00552D3E` | 125 | CLR exit lookup |
| `0x00552DC0` | 15 | TLS-exit callback initializer |
| `0x00552DCF` | 15 | recovered `_c_exit` |
| `0x00552DDE` | 15 | `_cexit` |
| `0x00552DED` | 22 | physical `_exit` / `_Exit` alias |
| `0x00552E03` | 38 | TLS-exit callback registration |
| `0x00552E29` | 22 | `exit` |
| `0x0056B2B6` | 29 | recovered common_exit cookie/EH handler |

## Real guarded closure and complete exceptional boundaries

The 77B guarded-call section has three ordinary-byte matches. Common_exit's
actual call selects `0x00552B1D`, whose action is the full cleanup owner at
`0x00552B6A`. The other candidates at `0x00555A94` and `0x0055E85A` call
different actions and are rejected. The outer caller constructs lock-ID-2
closures. The 65B primary and existing 12B unlock cover the entire section;
its 28B SEH table at `0x005AC320` has header `-2,0,-40,0` and record
`-2,0,0x00552B5E`.

The cleanup action's full 232B SDK contribution contains the existing 196B
primary, a 27B filter, an 8B handler and INT3 at `0x00552C51`. Its complete
28B scope table at `0x005AC300` has header `-2,0,-52,0` and record
`-2,0x00552C2E,0x00552C49`. The filter reads the actual exception code and
accepts only Microsoft C++ exception `0xE06D7363`. The handler restores ESP
from the parent frame and calls terminate. Ghidra omitted both entries;
whole SDK comparison, original scope relocations and pinned decoding cover
all 35 instruction bytes. Other exceptions continue the SEH search.

Common_exit's full section is 190B: 184 instruction bytes and six INT3 bytes
at `0x00552D0A..0x00552D0F`. Its existing 185B ledger row retains the first
INT3; the remaining five are also compared. The process selector has 45B
instructions plus one INT3, and CLR lookup has 125B instructions plus five
INT3. With the cleanup handler's one INT3, the complete main interval is
`0x00552B1D..0x00552E3E`, without an omitted tail or alignment gap.

## Modes, cleanup order and distinct completion flags

| Public entry | Return code | Cleanup mode | Return mode |
| --- | --- | --- | --- |
| `exit` | caller argument | full / 0 | terminate process / 0 |
| `_exit`, `_Exit` | caller argument | none / 2 | terminate process / 0 |
| `_cexit` | zero | full / 0 | return to caller / 1 |
| `_c_exit` | zero | none / 2 | return to caller / 1 |

Both full SDK `_exit` and `_Exit` sections select the same physical head;
there is one ledger entry. The SDK quick_exit wrapper has no complete target
match and gains no separate identity. The cleanup action still retains its
quick-cleanup mode-1 branch.

The action first tests the one-byte `c_exit_complete` latch at `0x005E5498`.
If clear, it atomically exchanges TRUE into the separate four-byte
`c_termination_complete` state at `0x005E5490`. Full cleanup decodes and
invokes any registered main-thread TLS callback before executing the normal
atexit table. The callback receives `(nullptr, DLL_PROCESS_DETACH, nullptr)`,
three zero arguments here. Quick cleanup selects the quick-exit table;
no-cleanup skips both tables and the TLS callback.

For this static release CRT, full cleanup next executes the `__xp` range;
the `__xt` range executes for every cleanup mode. Only terminate-process
mode sets `c_exit_complete` and the caller's uninitialization-required flag.
Returning cleanup therefore does not set that latch, even though it sets
the separate termination-started state. These are not one interchangeable
Boolean or an unconditional once-only cleanup guarantee.

The external normal/quick onexit tables at `0x005E55B8`/`0x005E55C4`,
executor at `0x00553825`, `_initterm` at `0x005559FE` and linker ranges
`__xp_a/z = 0x0056C440/0x0056C450`, `__xt_a/z = 0x0056C454/0x0056C458`
are named dependencies of the complete SDK owner. This review does not add
body or data ownership credit for those external contributions.

The two ordinary-byte candidates for `_is_c_termination_complete` access
different state addresses, neither `0x005E5490`; both are rejected. In
particular, the previously reviewed new-mode getter at `0x005571C0` keeps
its established identity. The termination getter remains unlocated.

## TLS registration and full local state

The 15B initializer stores the supplied encoded-null value into callback slot
`0x005E5494`, without encoding it again. Its real storage and the earlier
reviewed CRT pointer initializer reject four other same-shaped setters.
Registration requires the current slot to equal the encoded-null cookie.
Otherwise its conditional tail transfer enters terminate. Success encodes
the raw callback with the shared cookie/rotate helper and stores it. There
is no added rejection of a null callback or atomic once-registration store.

The four-byte termination state, four-byte callback slot and one-byte
completion latch are three complete SDK BSS contributions, all loader-zero
in the locked PE. Their combined extent is exactly nine bytes. Runtime
encoded-null initialization is distinct from those loader zeros.

## Managed pre-exit and process termination fallback

Terminate-process mode first tests the already reviewed managed-image helper
at `0x00543B86`. If managed, it tries CorExitProcess before C cleanup. On
return, common_exit runs the lock-2 cleanup, then obtains process-end policy
before choosing its terminal call. Policy value 1 selects ExitProcess;
otherwise an enabled application verifier also selects ExitProcess, and
the remaining case selects TerminateProcess. No release CRT uninitialization
call is introduced from the source's debug-only branch.

The selector calls TerminateProcess(GetCurrentProcess(), code) when requested.
If that call returns, it still tries CLR exit and finally ExitProcess(code).
These are independently named PE imports; their fallback order remains in
the complete 45B instruction owner.

CLR lookup uses GetModuleHandleExW with flags zero and the full UTF-16
`mscoree.dll` literal, acquiring a reference to an already loaded module.
It does not load a new module. GetProcAddress searches for `CorExitProcess`;
a found target is called through the existing guard check using its stdcall
ABI. Ordinary completion releases any nonnull module with FreeLibrary,
including the missing-export path. Both full literals are retained at
`0x005993E4` (24B) and `0x005993FC` (15B).

## C++ EH, evidence and affected scope

The recovered 29B common_exit handler retains two NOPs, the real frame-cookie
check and tail transfer to CxxFrameHandler3. Its full 44B metadata section at
`0x005AC274` starts with the unwind record `-1,0x005465A0` and has FuncInfo
at `0x005AC27C`: one state, that unwind map, and flags 5. The target is the
named `__std_terminate` dependency; its body is outside this review. CLR lookup
reuses the already reviewed
29B handler at `0x005679A0` and full zero-state 36B FuncInfo at `0x005A91B8`.
Both full closures are compared without duplicate physical credit.

The nine BSS bytes, 39 literal bytes, two 28B SEH tables and 44B/36B EH
sections form the complete 184B owned data scope. Shared pointer encode/decode
helpers and the managed-image helper are also compared as dependencies.

Private `.analysis/origin-boundary/exit-paths/` retains the SDK member,
complete search/relocation results, bounded attested listings, `review.py`,
`reviewed.json` and original ledger rows. The audit covers all ordinary
bytes, REL32/DIR32 roles, PE HIGHLOW, direct branches/calls, complete metadata,
owned state and alignment. Source is `ucrt/startup/exit.cpp` and the existing
internal exit-mode, lock, pointer and handle definitions.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**; no authored or maintained-source exact credit
is added. Next inspect the actual onexit executor and initialization ranges,
retaining callback order, table updates, recursive registration and all
exception/lock paths.
