# x86 catch guards, translators and continuation transfer

Ten complete MSVC 14.44.35207 x86 `libvcruntime.lib(trnsctrl.obj)` contributions
identify ten pending library origins in the locked Japanese TH20 Steamless
target. All 962 instruction bytes and two INT3 bytes in
`0x00544394..0x00544757` agree. The guards build their registration records
on the stack; this provider owns no local EH data tables.

| Entry | Instruction bytes | Role |
| --- | ---: | --- |
| `0x00544394` | 110 | try-block search range |
| `0x00544403` | 96 | guarded catch invocation |
| `0x00544463` | 255 | SE translator invocation and continuation |
| `0x00544562` | 48 | jump to catch continuation |
| `0x00544592` | 84 | nested-frame unwind |
| `0x005445E6` | 49 | catch guard handler |
| `0x00544617` | 36 | frame-info chain insertion |
| `0x0054463B` | 71 | frame-info chain unlink |
| `0x00544683` | 159 | translator guard handler |
| `0x00544722` | 54 | shared public C++ frame handler |

The try-range and unlink sections each include one final INT3, at
`0x00544402` and `0x00544682`. JumpToContinuation's old 43B extent now covers
its full 48B contribution, including the original unreachable five-byte
epilogue. Every other existing extent remains unchanged. TranslatorGuardHandler
also retains its original unreachable branch and return-value instructions.
The supplemental decode covers all ten omitted bytes/six instructions.

## Catch and translator registration layouts

CallCatchBlock2 builds a 24B guard: next pointer, handler, cookie XOR node
address, FuncInfo, subject registration node and catch depth plus one. It
links that record through FS:[0], invokes the reviewed CallSettingFrame,
restores the old FS head on normal return and returns the continuation pointer.
Its guard handler clears DF, validates the cookie, then forwards to the
reviewed internal FrameHandler3 wrapper with this guard as marker, saved
depth and recursive false. It has no separate local unwind shortcut.

CallSETranslator builds a 40B guard with the same first five fields,
followed by depth, parent marker, saved ESP, saved EBP and DidUnwind DWORD.
It links the node before calling the translator. The source's special
exception-pointer value 0x123 selects a separate query path: it writes the
internal continuation address `0x00544536` through the second argument and
returns integer one without reading an exception record or installing a node.

The ordinary path maps the exception code through the reviewed x86 SSE2
filter, builds EXCEPTION_POINTERS, and loads the cdecl translator from VCRT
PTD+8. It calls the existing fastcall guard thunk before the indirect call.
DidTranslate is initially one; a normal translator return writes zero.
Thus a translator that returns normally reports no translation.

TranslatorGuardHandler clears DF and checks its cookie before examining
exception flags. Flags masked with 0x66 mark DidUnwind and return
ExceptionContinueSearch, value one. During search it invokes FrameHandler3
with recursive true and the saved parent marker. If DidUnwind remains false,
it unwinds the translator context through the complete nested-unwind helper.
It then queries the special continuation address, restores ESP/EBP from the
guard and jumps there. This preserves the original nonlocal transfer.

At the continuation, a completed unwind replaces the translation dispatcher's
marker with the saved original marker; otherwise the translator node is
unlinked normally. Both paths return the saved DidTranslate value. The
complete guard handlers are the first two RVAs in the target's 256-entry
central SafeSEH table. Their registration does not introduce an owner-local
SEH table.

## Unwind markers and continuation frames

UnwindNestedFrames saves FS:[0], then calls the independently named
RtlUnwind import with subject node, its own ReturnPoint label, exception
record and zero. On return it clears only exception-flag bit 2, relinks the
saved dispatcher marker onto the current FS head and restores EBX/ESI/EDI.
The original NOP between the import call and ReturnPoint remains an instruction.
The stdcall bridge returns with RET 8.

JumpToContinuation removes exactly the current FS head. It sets EBP to
registration+12, restores ESP from registration-4 and jumps to the supplied
target. There is no fabricated returning path. The compiler's unreachable
pop/leave/RET 8 bytes after that jump still belong to the complete section.

## Try ranges and exception-object frame links

GetRangeOfTrysToCheck scans the 20B try-map entries backwards, using
`tryHigh < currentState <= catchHigh` to count enclosing catches. Its
predecremented-index accesses occur before the wrapped-index test in the
original expression; that evaluation order is retained. The original abort
checks guard the starting sentinel and final unsigned range. The cdecl
function writes a 16B iterator pair through its hidden result pointer:
`[map,start,map,end]`, then returns that pointer in EAX.

CreateFrameInfo fills an eight-byte node with exception-object pointer and
old next pointer, pushes it onto the distinct VCRT PTD+0x24 frame-info chain,
and returns the supplied node. FindAndUnlinkFrame removes either its head or
a matching later link. A missing node in a nonempty chain reaches abort;
the original traversal has no added empty-chain guard. These helpers do not
allocate, destroy or free exception objects and do not manipulate FS:[0].

## Shared public handler and independent dependencies

The three public C++ handler versions have identical whole 54B contributions
and the same wrapper relocation, folded at `0x00544722`. They receive
FuncInfo in EAX in addition to four cdecl stack arguments, save it before
clearing registers, clear DF and call the complete internal wrapper with
catch depth zero, marker null and recursive false. The incoming EAX channel
is part of the native ABI; an ordinary four-argument C++ declaration alone
does not express it. One physical entry receives credit.

The cookie-check callee independently matches the complete unique 14B
`libcmt.lib(secchk.obj)` signature and the already reviewed cookie storage.
The checker and failure owners now have their
[complete state/ABI review](CRT_SECURITY_COOKIE_FAILURE_ORIGIN_REVIEW.md). Existing cookie, PTD,
CallSettingFrame, guard-thunk and wrapper proofs retain their bindings.
The object's explicit alternatename directive binds its SSE2-filter call to
the already reviewed default filter at `0x0056746F`.

## Evidence and affected scope

Private `.analysis/origin-boundary/catch-transfer/` retains `review.py`,
`reviewed.json`, original ledger rows and the secchk identity member. It
reuses trnsctrl.obj and bounded attested `transfer-native.txt` in
`frame-unwind/`. All ordinary bytes, branches, REL32/DIR32 roles, HIGHLOW
fields, original NOPs, unreachable instructions and alias contributions agree.
The RtlUnwind import is checked through the PE import directory, and both
SafeSEH RVAs through the load-config table. Installed
`crt/src/i386/trnsctrl.cpp` supplies the guard layouts and protocol evidence.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new authored or maintained-source
exact credit.
