# Intrusive observation and nonthrowing Region construction

EXACT-051 closes the shared linked-node/sentinel/observer protocol that the damage
controller requires, plus Region construction/update and two position/vector
dependencies. Twenty new complete units add 1,827 body bytes and 15 compiler
alignment bytes. All 363 units / 66 cold objects / 57,534 disjoint complete comparison
bytes strictly replay. Original authored credit remains 57 functions / 4,074 bytes.

## Independently established lifetime and EH

The previous Region constructor hypothesis preserved defaults but emitted 317
bytes against native 359. Native constructor, iterator constructor and iterator
destructor register distinct handlers 5679A0, 5674F0 and 567750. Independently decoding
those complete 29-byte handlers shows their actual frame-cookie offsets and common
FuncInfo pointer 5A91B8. The entire 36-byte record is:

`magic=19930522; maxState=0; unwindMap=0; tryBlocks=0; tryMap=0; ipCount=0; ipMap=0; exceptionSpec=0; flags=5`.

A private nonthrowing-constructor compiler experiment emits the identical complete
metadata and closes the 359-byte instruction body. Normal throwing construction
omits the frame; introducing a nontrivial link destructor instead creates cleanup
states absent from native. That destructor hypothesis is rejected. The source
now declares Region and iterator construction `noexcept`; the iterator destructor
retains its natural implicit nonthrowing contract. This contract is supported by
the native metadata, independently matching compiler metadata and current bodies,
not merely by finding an instruction sequence that fits.

Locked MSVC contributes five trailing INT3 alignment bytes for each of these
three complete EH-bearing functions. Native padding contains the same bytes.
The manifests retain body sizes 359/172/111 and compare entire contributions
364/177/116. No prefix is sliced away and alignment receives no body/authored
credit. Fresh cold objects also reproduce all three complete 29-byte handlers after
replaying independently observed security-check, CRT and metadata anchors, plus
the complete 36-byte FuncInfo. These remain supporting evidence without
additional function coverage units or copied source tables.

## Actual typed storage and semantics

All member offsets below are hexadecimal.
`IntrusiveLink<T>` is 20 bytes on x86: value pointer at 0, next at 4, previous at 8,
list owner at C,
observer at 10. `IntrusiveList<T>` is a 24-byte sentinel link and tail pointer at 14.
`IntrusiveIterator<T>` is 8 bytes: current at 0 and pending at 4. Complete native zero
construction 418A10, list construction 418A50, reset 44A640, append 411EA0,
remove 411D20, iteration and original consumers corroborate all six list slots and
both iterator slots. Base/member spelling is still an inference; the typed
sentinel protocol is actual storage, with no padding or unrelated owner facade.

A list does not own the pointed-to value. Append links after tail, registers list
owner and advances tail. Remove updates tail from the removed link's previous
pointer before unlinking. Detach uses its recorded owner or repairs neighbors
without a list. Neighbor/owner fields clear, while the value pointer remains.

Only one observer slot exists per link. Construction registers current and its
next link. Advance clears the old current observer, promotes pending and watches
its next link. Destruction clears the current/pending observations. Removing a
current link nulls current; removing pending moves the pending observation to
its next link. This permits advancing after removing the current link and skips
a removed pending link. End is a null iterator pointer; non-null comparison
compares current pointers, and null comparison tests current existence.

Use detached storage for initialize/reset and keep observed nodes alive. Multiple
simultaneous observations or copying a live iterator are outside the established
native domain. Locking, allocation and enclosing list/controller lifetimes remain
separate protocols. FunctionChainNode and DamageRegion share one maintained
header body with actual typed value/neighbor/owner/observer pointers. Neither is
cast to the other; the previous three exact link units remain unchanged.

## Accepted contributions

| Address | Body bytes | Operation |
| --- | ---: | --- |
| 00418A10 | 63 | Link default construction |
| 00412730 | 17 | Link previous pointer |
| 0040F160 | 19 | Link value reference through its actual first subobject |
| 0044A670 | 61 | Link initialization/reset |
| 00411CE0 | 55 | Link owner-aware detach |
| 00411D50 | 216 | Link unlink and observation repair |
| 00411E30 | 60 | Link forward search including the receiver |
| 00411D20 | 47 | List remove and tail repair |
| 00411EA0 | 57 | List append |
| 00411E70 | 33 | List search through sentinel |
| 00412280 | 53 | List begin with real hidden iterator result |
| 00412540 | 13 | List null end |
| 004119B0 | 172 | Nonthrowing iterator construction |
| 00411B00 | 111 | Iterator destruction |
| 00411C30 | 121 | Iterator advance/reference result |
| 00411BB0 | 91 | Iterator inequality/AL bool |
| 004BFFB0 | 359 | Nonthrowing Region construction |
| 004C03D0 | 164 | Region update and lifetime decision |
| 0048BD70 | 38 | Motion position by-value/hidden result |
| 004C0240 | 77 | Vector3 divide assignment/reference result |

Typed getters of 17/16/14 bytes, setter of 22 bytes, value constructor of 64 bytes
and insertions of 76 bytes share existing
canonical physical heads 40FF90, 40C300, 40BDA0, 412DA0, 412DC0, 411970, 411EE0 and 411F30.
These receive independently audited aliases only, with no duplicate units. In
particular next at 40FF90 is already the canonical Timer current-word view and
owner at 412DC0 the FunctionChain before-insert pointer store. Shared code does not
establish original semantic tags, template spelling or source origins.

Region update calls the existing Motion update, grows radius by scalar at 20, advances
angle by angular velocity, clears target, decrements Timer and cooldown and calls
native retirement when the resulting timer is nonpositive. Cooldown retains
modulo-word decrement at INT32_MIN. Radius/angle/cooldown advance per invocation
independently of the Timer clock. The real Region member `retire()` is declared
but remains undefined; its original controller/allocator lifecycle is not replaced
by a production stub. Public fixtures only observe that dependency invocation.

Motion copies actual XYZ into its hidden result and leaves the receiver unchanged.
Divide assignment updates all three actual float members and returns the receiver.

## Reviewed but deferred controller neighborhood

Complete damage control at 4C0480 (1,707 bytes) is now reviewed: Player gate,
bullet callback,
three four-element group arrays indexed by group 1..4, largest raw group damage,
target de-duplication, per-region cap/retirement, optional callbacks/position,
Enemy lookup/effect flags, final Player cap and score update. Iterator/EH supports
its traversal, but actual Player/Bullet/Enemy/Effect/score owner interfaces and
retirement liveness remain unresolved. No complete Controller/Player facade or
invented calling convention is introduced to obtain its bytes.

Constructor 4BFEE0 (191 bytes) and initialize 4C0B30 (265 bytes) establish a
16-byte TaskInfo, a real 256-element array of 196-byte Regions at 10, generation
at C410, two sentinel lists at C414/C42C,
count at C444, Timer at C448, view index at C458 and Context pointer at C45C.
End 4C0C40 is relative to the array receiver and adds C400, not to the entire controller. Setter 4C2090
stores view index then selects Context from the global 48-byte-stride table;
40BBC0 proves that stride. Field C458 is an integer view index, not a Context
pointer. Region's distinct C0 remains its actual opaque Context pointer.

Getter 424010 reads Context+18, getter 412710 reads Context+28, and the first-state
access 40FF90 reads Context+4. Full Context slot identities/global initialization,
Player lifetime and full controller production ownership remain pending. Native
477CF0 conditionally calls its dependency's virtual slot 14 but returns zero;
that surprising return is observed, not rewritten as the virtual result.

List constructor 418A50 (40 bytes) remains nonexact: natural construction of 31 bytes omits the
native second tail store and uses different store registers. Reset 44A640 (42 bytes)
preserves semantics but has one reversed register assignment. Both are maintained
naturally and receive no exact credit. Sorted FunctionChain insertion at 411F80 and
412100 (381 bytes each) additionally require its real registry lock guard and enclosing
controller owner. Full bodies are inspected; those contracts remain deferred.
Allocator 40C080 (29 bytes), view/global lookup and neighboring Controller initialization,
update, handles and unrelated Player/Enemy helpers are evidence, not additional
accepted functions.

## Verification and limits

All 363 units cold-build from 66 canonical objects and strictly replay their full
relocations. One precise-FP/GS/EHsc recipe covers all nine Region members, including
the seven previously accepted bodies; the shared-header change also requires a
fresh replay of every other unit. IntrusiveLink uses precise-FP/GS/EHsc, while
Motion/Vector3 retain their existing profiles. These are local recipes, not a
globally recovered game build configuration.

Public C++20/UBSan checks cover sentinel/owner/tail state, node search and value
references, current/pending removal, observation migration and destruction,
empty iterators, configuration preservation, nonthrowing contracts, per-tick
Region growth, frozen Motion, positive/zero/negative/stopped timer decisions,
cooldown wrapping and independent copied/divided XYZ results. Retirement tests
record only calls; they do not claim controller cleanup, heap deletion or playable
runtime. Full previous public checks pass. Target/database/reference 6945/113
remain unchanged. Original names, source partition, origins, unobserved domains,
locking, resource ownership, full controller and whole-game linkage remain open.
