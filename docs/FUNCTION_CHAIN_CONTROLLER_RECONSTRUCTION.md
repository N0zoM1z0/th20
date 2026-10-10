# Complete function-chain controller protocol

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-099 now closes both full insertion methods and update/draw,
including original tables and alignment. Shared iterator initialization and
actual scopes explain the prior differences. Unlocked removal and node factory
remain nonexact. See [current core evidence](CORE_ITERATION_EXACT_RECONSTRUCTION.md).

CORE/EXACT-097 reconstructs the actual 56-byte controller and complete update,
draw, insertion, registration and removal methods. This closes the scheduler
ownership dependency required by HitCtrlInf initialization and destruction.
Process startup, controller shutdown and game runtime remain open.

The native constructor at 0x00418A80 establishes current link at +0, two real
24-byte observer-aware lists at +4/+1C and shutdown word at +34. Registration
and HitCtrlInf destruction independently read the process pointer at 0x005B66D8.
The maintained owner uses the existing FunctionChainNode, IntrusiveList,
IntrusiveIterator, LockRegistry and DiagnosticAllocator bodies.

## Corrected node destruction ownership

Native scalar deleting destructor 0x00411CB0 calls 0x00411B80, then conditionally
uses sized delete for the complete 44-byte node. Native destroy_at at 0x00411960
calls that deleting destructor with flags zero. This independently identifies
0x00411B80 as ordinary FunctionChainNode destruction. Its three callback pointer
stores were previously given the provisional name clear_callbacks.

The actual destructor now owns those stores. The misleading helper API is
removed; the portable state test uses the existing set_callback(nullptr)
operation. The legacy canonical unit ID chain_clear_callbacks stays stable,
but its function name and COFF symbol now identify the actual destructor.
The existing 41-byte physical root receives no additional coverage credit.
DiagnosticAllocator::release_object uses the same shared destroy_at and locked
scalar deletion protocol as other actual owners, with no node-specific factory.

## Whole behavior and emission

Four distinct cdecl registration bodies preserve update/draw and enabled/
disabled variants. Each creates an owned node, assigns userdata, selects the
flag and calls the corresponding insertion method. Native code assumes that
allocation succeeds; no new null guard is introduced. The original create
diagnostic identifies core/func.cpp:317 funcChainInf.

Before-insert callbacks run before acquiring lock slot 0 and clear only after
returning. Insertion places a new node before the first greater or equal
priority, so newer equal-priority nodes run first. Removal searches update
then draw, advances the owner's current link when necessary, detaches with
observer repair and clears callback before conditionally releasing owned nodes.
Foreign and null nodes are ignored.

Update and draw acquire tracked slot 0, release it around enabled callbacks
and reacquire it before interpreting returned actions. Non-null disabled
callbacks count; null callbacks do not. Shutdown callbacks run while the lock
is held. The complete update table has nine distinct destinations; draw has
six. Both preserve retry, early return and observer cleanup; update additionally
preserves restart and shutdown. Restart resets the count.

| Action | Update | Draw |
| --- | --- | --- |
| 0 | Remove current node | Remove current node |
| 1 | Continue | Continue |
| 2 | Retry current enabled test | Retry current enabled test |
| 3 | Return 1 | Return 1 |
| 4 | Return 0 | Return 0 |
| 5 | Return -1 | Return -1 |
| 6 | Restart iteration/count | Continue |
| 7 | Call shutdown callback | Continue |
| 8 | Return 0 | Continue |
| Other | Continue | Continue |

| Complete contribution | Native compared bytes | Result |
| --- | ---: | --- |
| Controller construction | 55 | Canonical exact |
| Owned node creation | 57 | Canonical exact |
| Locked removal | 134 | Canonical exact |
| Four registration entries | 272 | Canonical exact |
| Unlocked removal | 162 | 156, nonexact |
| Each sorted insertion | 381 | 371, nonexact |
| Whole update, including table/alignment | 648 | 640, nonexact |
| Whole draw, including table/alignment | 612 | 592, nonexact |

Update's body is 611 bytes; draw's is 587. Independently decoded pointer tables
and their original one-byte NOP alignment remain part of subsequent complete comparisons. Ghidra's
function export omits one head in each body. Full locked-PE decoding retains
both omitted jumps and all nine/six actual destinations; no interval is shortened.

The natural iterator callers still disagree with native eight-byte compiler
initialization. Native unlocked removal also clears an otherwise unused local
pointer after release. These observations remain emission questions; the source
adds no inert initialization or dead reset merely to force a match. The shared
scalar allocation template still has unresolved original preclear emission.

## Verification and remaining scope

The public O2/UBSan fixture executes the actual owner and shared node/list/lock/
allocator bodies. It covers every action, negative/out-of-range actions, retry,
restart, shutdown, enabled/null counts, equal-priority ordering, current-link
repair, foreign/null removal, deletion of a pending node, all four registrations
and actual owned destruction. Cross-thread mutex probes check release around
callbacks and retention around shutdown callbacks. Remaining observers and
list tail restoration are checked. A private precursor also passes ASan/UBSan.

The fixture supplies process object lifetime and allocator startup; those are
explicit external dependencies. It does not establish original startup, native
game execution, factory byte identity, arbitrary concurrent callback mutation
or exception behavior. HitCtrlInf initialization, region disposal and the full
damage query remain the next reconstruction scope.

Private reproducible evidence: core097-scheduler-native.asm,
core097-scheduler-support.asm, core097-lifetime-native.asm,
core097-node-destruction.asm, core097-update-audit.json,
core097-draw-audit.json, core097-whole-bindings.json,
core097-staged.json and core097-semantic-check.json. The frozen production graph passes 666/666 strict units across 132 fresh
objects and 129,954 disjoint compared bytes. Seven new canonical roots add
518 bytes and 39 independent relocations. The five complete nonexact methods
are mapped separately. All 63 public tests pass; authored exact coverage stays
84 functions/24,209 bytes and reference absorption stays 238. New origins remain
unknown pending independent classification. The existing destructor root is
renamed without duplicate credit.

Canonical evidence: core097-final-frozen-source.json,
exact097-canonical-results.json.gz, core097-cold-audit.json,
core097-registered.json and core097-production-lifetime-support.json. The complete
46-byte deleting destructor, 16-byte destroy_at and 97-byte release_object
strictly replay as support only. The refreshed active HitCtrlInf probe is
build/core097-HitCtrlInf.obj, supported by core097-hit-whole-bindings.json.
Protected retirement is recorded in core097-cleanup.json after semantic CI;
original private inputs and receipts are preserved losslessly. Completed
proof/replay/retirement writers must not rerun.
