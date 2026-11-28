# UCRT onexit registries, reentrant callbacks and initializer traversal

Eleven whole Windows SDK 10.0.26100.0 x86 `libucrt.lib` contributions from
`onexit.obj` and `initterm.obj` identify twelve pending origins and three
recovered compiler entries in the locked Japanese TH20 Steamless target.
All 964 instruction bytes, five INT3 bytes and 124B of registries, SEH and
C++ EH agree. Every existing candidate extent remains unchanged.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x0055356C` | 76 | execution guarded-call primary |
| `0x005535B8` | 3 | recovered execution exception entry |
| `0x005535BB` | 12 | execution unlock funclet |
| `0x005535C7` | 76 | registration guarded-call primary |
| `0x00553613` | 3 | recovered registration exception entry |
| `0x00553616` | 12 | registration unlock funclet |
| `0x00553622` | 275 | registration action |
| `0x00553735` | 218 | execution action |
| `0x0055380F` | 22 | `_crt_atexit` |
| `0x00553825` | 57 | `_execute_onexit_table` |
| `0x00553863` | 41 | `_initialize_onexit_table` |
| `0x0055388C` | 51 | `_register_onexit_function` |
| `0x005559FE` | 43 | `_initterm` |
| `0x00555A29` | 46 | `_initterm_e` |
| `0x0056B2F0` | 29 | recovered executor cookie/EH handler |

## Registry identities and initialization

Each registry is three encoded 32-bit pointers: first, last and allocation
end. The complete normal table at `0x005E55B8` and quick table at
`0x005E55C4` are separate 12B SDK BSS definitions, all loader-zero. Earlier
reviewed CRT initialization independently names both addresses. Runtime
initialization fills them with encoded null, whose value is the cookie,
rather than treating loader-zero bytes as configured empty pointers.

The initializer returns -1 for a null table without writing errno or calling
an invalid-parameter handler. It compares the stored first and end fields
directly. If unequal, it returns zero without changing anything. If equal,
it writes encoded null into all three fields, without inspecting last.

The 22B `_crt_atexit` wrapper passes the normal table to registration. The
SDK `_crt_at_quick_exit` has the same ordinary bytes and the same one candidate,
but requires the independently named quick table. The actual target field
selects the normal table, so the quick-wrapper candidate is rejected. These
are not credited as a folded physical alias. The quick registry remains a
real definition used by the previously reviewed common exit cleanup owner.

## Registration and allocation ownership

The public wrapper constructs exit-lock-2 closures around the registration
action. A null table returns -1 under that lock. Otherwise the action
decodes first, last and end. Only last equal to end triggers growth.

Growth computes old capacity from the four-byte slot range. The first
attempt adds the smaller of old capacity and 512; a zero result selects
32 initial slots. This attempt runs only when the new count is at least
the old count. If it fails or is skipped, the fallback requests old count
plus four. Both use the previously reviewed recalloc base with element
size four. The fallback retains its original count arithmetic without a
new overflow check. Failure returns -1 without publishing new table fields.

Successful growth preserves the used count and fills every additional slot
with encoded null, replacing recalloc's raw zero fill. The original
detached-heap ownership leaves a free-of-null call after each attempted
allocation; both native calls remain in the full contribution. The callback
is encoded into the next slot, last advances by four, and first/last/end
are encoded and stored in the table. No extra null-callback rejection is
added: an encoded null callback is later skipped as an empty slot.

## Reverse execution and callback-driven table changes

The execution wrapper also supplies exit lock 2. A null table returns -1.
Decoded first equal to null or -1 returns zero before freeing or resetting
the table. Otherwise execution decrements last and scans backwards over
encoded-null entries, using the original unsigned pointer comparisons.

For each live slot, it decodes the callback and marks that slot encoded-null
before invoking user code. After the callback, it reloads and decodes the
table's first and last fields. If either differs from the saved bounds, it
restarts from the new last and first. This preserves registrations that
append or move storage during callback execution; a fixed snapshot or a
post-call visited mark would change the protocol.

Ordinary completion frees the current first allocation unless it is -1,
then sets all three table fields to encoded null and returns zero. The
complete outer guarded owner retains the recursive critical-section lock
through callbacks. Its exception path releases the lock. The executor's
one-state C++ unwind map then targets `__std_terminate`; no exception path
is invented to finish the normal free-and-reset sequence after a callback
throws. The SDK global-state-reset scope emits no additional native state
operations in these compared contributions.

## Guarded owners and full exceptional metadata

Both 91B guarded sections have the same three ordinary-byte candidates:
`0x00551F19`, `0x0055356C` and `0x005535C7`. Complete public calls, action
targets and scope tables identify execution at `0x0055356C` and registration
at `0x005535C7`. Each consists of a 76B primary, a recovered 3B exception
prefix and an existing 12B unlock. The prefix reloads ESI from the parent
frame; normal completion calls the unlock directly.

The full 28B scope tables have header `-2,0,-44,0`. Execution's table at
`0x005AC3C0` has record `-2,0,0x005535B8`; registration's at `0x005AC3A0`
has record `-2,0,0x00553613`. Ghidra omits the prefixes. Whole SDK sections,
original relocated scope targets and pinned decoding cover both missing
instructions without changing the database.

The public executor's 57B instructions and five original INT3 bytes form
its whole 62B section. Its recovered 29B handler retains both initial NOPs,
the actual parent-frame cookie check and tail transfer to CxxFrameHandler3.
The full 44B metadata section at `0x005AC370` contains unwind record
`-1,0x005465A0` and FuncInfo at `0x005AC378`: one state, that unwind map,
and flags 1. The named unwind target is `__std_terminate`; its body is
outside this review. EH_prolog3 and EH_epilog3 are named compiler-runtime
dependencies, without new body credit here.

All 851 bytes at `0x0055356C..0x005538BE` are covered by complete onexit
code/alignment. The 24B registries, two 28B SEH sections and 44B C++ EH
section form the complete 124B data scope.

## Raw initializer traversal

The separate `_initterm` and `_initterm_e` owners traverse raw function
pointers forward in four-byte steps until the pointer equals the supplied
end. Both skip null slots and retain the existing guard check before
indirect cdecl callbacks. They neither decode pointers nor repair a malformed
range. `_initterm` calls void callbacks; `_initterm_e` returns the first
nonzero integer callback result unchanged, including a negative value, or
zero for an empty or successful range. Their complete 43B/46B sections have
no additional alignment or owned tables.

## Evidence and affected scope

Private `.analysis/origin-boundary/onexit-execution/` retains the SDK members,
complete searches and relocation details, bounded attested listings,
`review.py`, `reviewed.json` and original ledger rows. The audit covers every
ordinary byte, REL32/DIR32 role, HIGHLOW entry, direct branch/call, exceptional
prefix, data closure and alignment byte. It rejects all four wrong guarded
action choices and the wrong-table quick wrapper. Shared encoder sections
are compared at their existing physical owner without duplicate credit.
Source is `ucrt/startup/{onexit,initterm}.cpp` and the existing internal
pointer, lock and heap-ownership definitions.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**; no authored or maintained-source exact credit is added.
