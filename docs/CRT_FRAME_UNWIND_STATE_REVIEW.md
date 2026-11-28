# VCRuntime frame unwinding, state and rethrow filters

Seven whole MSVC 14.44.35207 x86 `libvcruntime.lib` contributions close eight
pending origins and recover five entries in the locked Japanese TH20 Steamless
target. The complete comparison covers 607B of instructions, two terminal
INT3 bytes and the full 40B SEH table. Repartitioning the unwind owner removes
its old overlap with the already listed finally body; no bytes are discarded.

| Entry | Instruction bytes | Role |
| --- | ---: | --- |
| `0x00547435` | 74 | rethrow exception filter |
| `0x0054747F` | 24 | unwind-to-empty wrapper |
| `0x00547497` | 133 | FrameUnwindToState primary |
| `0x0054751C` | 10 | unwind exception filter, recovered |
| `0x00547526` | 3 | unwind exception handler, recovered |
| `0x00547529` | 63 | loop/return continuation, recovered |
| `0x00547568` | 3 | finally entry prefix, recovered |
| `0x0054756B` | 20 | shared finally body, existing entry |
| `0x0054757F` | 5 | terminal abort path, recovered |
| `0x00547585` | 153 | exception-specification membership |
| `0x00547650` | 76 | stdcall CallSettingFrame |
| `0x00547AE5` | 29 | current-state getter |
| `0x00547B02` | 14 | state setter |

The complete FrameUnwindToState section is 238B, including INT3 at
`0x00547584`. The complete specification section is 154B, including INT3 at
`0x0054761E`. Every other selected extent is unchanged. The members are
`frame.obj`, `ehstate.obj` and `lowhelpr.obj`; the call-frame implementation
comes from lowhelpr, not the similarly relevant trnsctrl member.

## Signed state width and unwind-map traversal

The current-state getter tests signed FuncInfo maxState against 128. When
maxState is at most 128 it sign-extends the byte at registration-node+8;
otherwise it reads the full DWORD at that offset. The setter always writes
the full DWORD, regardless of maxState. It ignores its FuncInfo argument,
while the getter ignores the dispatcher-context argument. The installed
`ehstate.cpp` explicitly defines this x86 byte-state convention.

The empty-state wrapper passes target -1 to the complete unwind owner.
That owner obtains the current state and increments VCRT PTD+0x18,
ProcessingThrow. Its x86 loop continues while current state differs from
the target. Each iteration requires current state strictly above -1 and
below maxState; failure calls the original abort. This is not a loop that
quietly stops whenever current state is below the requested target.

The unwind map uses eight-byte entries containing next state and action
pointer. For a nonnull action, the owner publishes next state to the subject
frame before calling CallSettingFrame with code 0x103. Null actions skip
that call and publication. Both paths then advance the saved current state
to next state and repeat. After the loop and finally call, the original
final-state verification and full state write remain before return.

## Full SEH ownership and the two finally entries

The 40B table at `0x005AC118` consists of header `[-2,0,-48,0]`, outer
finally scope `[-2,0,0x00547568]`, and inner scope
`[0,0x0054751C,0x00547526]`. Every pointer has its original HIGHLOW relocation.
The inner filter forwards exception information to the previously reviewed
FrameUnwindFilter. The three-byte handler restores parent ESP and falls
through to the loop continuation. Its empty source handler remains present.

The normal path calls `0x0054756B` directly. The SEH table instead selects
`0x00547568`, whose three-byte prefix reloads saved current state into ESI
before falling into that same body. Finally calls the required VCRT PTD
getter and decrements ProcessingThrow only when it is positive. The old
237B parent candidate included this separate 20B entry; the new disjoint
partitions retain the complete instruction union exactly once.

Ghidra's listing omits the filter, handler and finally reload prefix.
The retained supplemental decode covers their six instructions and sixteen
bytes, while the full archive comparison verifies their original call
relocations and independent scope-table labels.

## CallSettingFrame and notification markers

The complete 76B lowhelpr section implements a stdcall three-argument bridge.
It derives the subject EBP from registration-node+12, not the caller's current
EBP. It notifies the already reviewed NLG helper, preserves ESI/EDI around
the unguarded indirect target call, restores the calling frame, and sends
the second notification. Notification code 0x100 becomes 2 only for that
second notification; other codes, including this unwind caller's 0x103,
remain unchanged. It returns with RET 12.

The COFF symbol NLG_Return at `0x00547677` is an interior notification marker
immediately after the target call, within this same owner. It supplies no
additional function credit. The full comparison retains both calls to
NLG_Notify1 at `0x00547B10` and all frame/register transitions.

## Rethrow recognition and exception-specification traversal

ExFilterRethrow requires code 0xE06D7363, exactly three parameters, magic
0x19930520/21/22 and a null ThrowInfo pointer. Only that combination writes
DWORD one to VCRT PTD+0x20 and returns execute-handler one. Other cases
return continue-search zero without clearing an existing rethrow flag.
This strict predicate differs from the dispatcher's newer-handler gate.

IsInExceptionSpec aborts for a null specification. Otherwise it scans each
16B HandlerType in the specification against the thrown type's catchable
pointer array. It invokes the now-reviewed complete TypeMatchHelper.
A match sets a sticky byte flag and breaks only the inner catchable loop;
later specification entries are still examined. Nonpositive counts return
false through the original loop guards. The result is BOOLEAN in AL.
No caller-owned type array, FuncInfo or unwind map is claimed as local data.

## Evidence and affected scope

Private `.analysis/origin-boundary/frame-unwind/` retains the full ehstate
and lowhelpr members, bounded attested listings, original rows, `review.py`
and `reviewed.json`. It reuses the frame member and unwind listing in
`type-info/`, the complete TypeMatch proof in `frame-dispatch/`, and the
previous context/PTD/NLG/abort identities. Every ordinary byte, branch,
REL32/DIR32 role, HIGHLOW field and complete SEH section agrees. Installed
`frame.cpp`, `ehstate.cpp`, `ehdata.h` and the lowhelpr archive symbols
corroborate the protocol and boundaries.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new authored or maintained-source
exact credit.
