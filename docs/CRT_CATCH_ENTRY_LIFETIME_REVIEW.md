# VCRuntime catch entry, rethrow and final cleanup

Two complete MSVC 14.44.35207 x86 `libvcruntime.lib(frame.obj)` contributions
close three pending origins and recover four entries in the locked Japanese
TH20 Steamless target. All 592 instruction bytes and the full 40B SEH table
agree. The old CallCatchBlock/finally split is reconciled into seven disjoint
entries without changing the complete instruction union.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x00546AD9` | 129 | CatchIt |
| `0x00547224` | 139 | CallCatchBlock primary |
| `0x005472AF` | 10 | rethrow filter, recovered |
| `0x005472B9` | 146 | rethrow handler, recovered |
| `0x0054734B` | 37 | shared normal continuation, recovered |
| `0x00547370` | 8 | finally entry prefix, recovered |
| `0x00547378` | 123 | shared finally body, existing entry |

CatchIt and the existing finally body retain their old extents. The old
332B CallCatchBlock candidate is repartitioned across primary, filter,
handler and continuation. Its full section is 463B, including the finally
prefix and body; no INT3 or unowned instruction bytes occur in either section.

## Catch entry completes unwind before adding the call frame

CatchIt constructs the catch object only when the conversion pointer is
nonnull. It then unwinds nested frames to the supplied marker, or to the
subject registration node when the marker is null. FrameUnwindToState moves
the subject frame to the selected try's low state, and SetState publishes
tryHigh+1 before invoking CallCatchBlock with NLG code 0x100.

Only after that nested-frame unwind does CallCatchBlock introduce its own
SEH frame. A nonnull returned continuation goes to the reviewed nonreturning
JumpToContinuation bridge. A null continuation denotes rethrow and CatchIt
returns void to the search owner. The x86 body leaves its IsRethrow and
recursive parameters unused, as in the installed source.

## Saved exception state and the rethrow handler

CallCatchBlock initially sets its continuation to the handler address,
retaining a nonnull sentinel before the handler runs. It saves the subject
ESP from registration-4 and inserts an eight-byte FRAMEINFO node for the
original exception object. It saves VCRT PTD+0x10/+0x14, then publishes the
current exception and context in those two distinct fields.

The protected call uses the complete CallCatchBlock2 owner. On normal return
its result becomes the continuation. The inner filter forwards exception
information to the reviewed ExFilterRethrow and returns that decision;
it is not an unconditional catch. Its strict C++/parameter/magic/ThrowInfo
predicate is retained from the preceding review.

The selected rethrow handler restores parent ESP and clears VCRT rethrow
state at +0x20. It obtains current frame state, scans 20B try entries for
the first `tryHigh < state <= catchHigh`, and selects the parent from
unwindMap[tryHigh+1].toState. If none matches, it retains the original state.
It unwinds with dispatcher context null, clears the continuation and joins
the normal finally path. The original handler-address argument passed to
the current-state getter remains; that getter ignores this context argument.

## Two finally entries and destruction order

The complete SEH table at `0x005AC140` has header `[-2,0,-92,0]`, outer
finally scope `[-2,0,0x00547370]` and inner scope
`[0,0x005472AF,0x005472B9]`. All three code pointers retain HIGHLOW relocations.
The normal path clears its abnormal-termination flag and calls
`0x00547378`. The table instead selects `0x00547370`, which reloads EDI zero,
the original exception into ESI and saved continuation into EBX before
entering the same body.

Finally restores the subject ESP first, unlinks this FRAMEINFO node, and
then restores the outer current exception and context. Only afterward does
it consider destroying the original object. Destruction requires the strict
MSVC record predicate, a clear ExceptionObjectDestroyed flag, nonnull
continuation and the reviewed frame-chain eligibility query. An object still
used by another nested catch is retained. Rethrow's null continuation also
suppresses destruction.

The abnormal-termination state is explicitly converted to a zero-extended
BOOLEAN before DestructExceptionObject. Its original member-destructor
termination policy is preserved. The function finally returns the actual
continuation pointer; no returning value is fabricated for CatchIt after
its nonlocal jump.

## Evidence and affected scope

Private `.analysis/origin-boundary/catch-lifetime/` retains `review.py`,
`reviewed.json` and original rows. It reuses the complete frame member and
bounded attested `catch-it-native.txt`/`catch-call-native.txt` in `type-info/`,
plus the complete construction, unwind and transfer proofs. Ghidra omits
61 filter/handler/prefix instructions spanning 164B. The supplemental decode
and whole archive comparison cover every byte and all original call/branch
roles; the scope table independently names their exceptional entries.

Every ordinary byte, REL32/DIR32 role, HIGHLOW field and complete local SEH
section agrees. Installed x86 `frame.cpp` corroborates the ordered unwind,
rethrow, frame-link, context-restoration and destruction protocol.
Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new authored or maintained-source
exact credit.
