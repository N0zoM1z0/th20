# Whole ECL async creation, lookup, invalidation and call setup

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-082 separates VM task invalidation from destructive owner cleanup and
connects the accepted VM to actual Manager/Runtime/Stack/Loader bodies. Seven
complete contributions add 524 bytes on the locked Japanese v1.00a Steamless
target. No opcode fragment receives separate credit.

| Maintained contribution | Native entry | Complete bytes |
| --- | --- | ---: |
| EclManager::spawn | 0053E390 | 182 |
| EclManager::find_runtime | 0053E920 | 72 |
| EclManager::invalidate_async | 0053E560 | 82 |
| DiagnosticAllocator::allocate_object<EclRuntime> | 0053B3D0 | 57 |
| EclLoader::activate | 0053FDF0 | 97 |
| EclManager::loader_value | 00437660 | 17 |
| ScriptStack::frame_value | 0041CA90 | 17 |

## Correct owner and retirement protocol

VM opcode 21 calls `invalidate_async`, which walks from the real sentinel's next
node, saves next and marks both offset and subroutine -1 on each child. It excludes
main and performs no allocation, destruction, release, unlink or current-runtime
restoration. Subsequent Manager tick retires ended children with the established
Runtime-destruction-before-detach-before-node-release protocol.

Destructive `terminate_async` remains the separate native `4973C0`/93 owner-cleanup
method. It releases children and leaves the sentinel stale until surrounding
reset/retirement. Its destructor callers retain that contract.

Previously, the VM's canonical relocation used the name `terminate_async` for
`53E560`, while the production definition and destructor callers used that same
name for `4973C0`. Independent function byte comparisons passed with contradictory
callee identities; the older VM dependency fixture did not exercise real owner
cleanup. The VM now names the actual invalidation method. Its original destination
and full native instruction bytes stay unchanged. A target-independent check
verifies that consumers of accepted ECL member definitions resolve to their
actual accepted owners. Real VM/Manager/PMR traversal exercises opcode 21.

## Creation and lookup

Spawn allocates a real Runtime and node through the process DiagnosticAllocator,
sets manager, zero time, both inactive position words and the supplied signed ID,
copies the caller's rank byte, initializes the five-pointer link and inserts it
after the real sentinel. It then passes the target, argument skip and zero name
skip to the caller's actual `call_into`, returning the full status.

Success restores the saved current runtime through `call_into`. Missing lookup
returns -1, retains the new target as current and its node in the list, and
invalidates the caller. No synthetic rollback or error guard is added. New nodes
inserted during tick wait for subsequent traversal because tick caches next.

Find begins at the sentinel, includes main and returns the first matching **node**,
including duplicate and negative IDs. It preserves cached-next/accessor behavior
and returns null when absent. It does not return a Runtime reference.

The Runtime scalar factory is an actual `new T` instantiation. Position performs
only scalar initialization; Stack and the PMR interpolation vector capture their
resource without allocation. Their genuine nonthrowing initialization contracts
support noexcept Position/Runtime construction. Locked-compiler traits verify the
member contracts. Position's complete 33-byte body and the original 104-byte Runtime,
86-byte Manager constructor and 88-byte Manager destructor contributions remain
identical. The factory's complete 57 bytes now match without an artificial helper,
clear or altered return ABI. Original annotation spelling remains inferred; no
executable-wide compiler flags are claimed.

The different node scalar factory at `53B410` still clears through `40C080` before
construction. That complete 73-byte contribution remains unclosed. Production
spawn retains its actual declared factory dependency; the semantic test explicitly
supplies this factory. Allocation failure and process allocator startup are not
closed by these positive allocation checks.

## Actual activation and shared lookup owner

Loader activation assigns the loader, selects the named subroutine, resets offset
and time, and returns one when the actual current instruction is null, otherwise
zero. Its real sorted-record lookup and existing setters execute in owned tests.
Writable instruction-buffer resolution remains an explicit dependency fixture.

The existing `499310`/22 instruction lookup belongs to the actual Manager base;
Enemy inherits it. Its maintained body moves from EnemyScript to EclCallSetup,
with the same native address, complete extent and canonical current-instruction
call. Its existing legacy unit key is retained; no additional coverage is claimed.
Stack pointer read/set at `411700`/17 and `412DA0`/22, link initialization at
`44A670`/61 and insertion at `411EE0`/76 match independently known folded heads
without duplicate credit. Original C++ source names remain reconstruction names.

## Verification and limits

The owned O2/UBSan pipeline executes the real complete VM tick and 923-byte
`call_into`, Runtime allocation/lifetimes, Loader activation/selection, Manager
spawn/find/invalidation/tick and State script progression. Checks cover signed ID
extremes, sentinel precedence, skips 0/1/3, four numeric descriptor conversions,
five-word return frames, successful and missing subroutines, deferred unnamed and
named-ID VM spawn, flag set/clear, signaling, offset-only ending, whole-child ending
and real PMR destruction order. Existing script-gate/callback/IEEE checks remain.
Bit 0's wider role stays unknown; setting it does not stop this tick's time tail.

Node factory, buffer resolution, allocator startup, unused interpolation/frame
routes and Enemy movement/opcode/outer retirement remain explicit fixtures.
This closes the selected protocol and does not establish whole-game runtime.
Authored origins, the 41 KB Enemy root, whole readers/State tick and Player's full
storage owner remain pending. All maintained owners use a single semantic body;
there is no matching-only source branch, padding, assembly or fake ABI.

The frozen graph contains 604 units /115 objects /104816 disjoint comparison bytes.
Per-unit flags retain the pinned compiler, C++20, Od, Ob0, GS, Gy, Zl, SSE2,
fp:precise, sdl and EHsc for the new protocol. The inherited lookup uses its new
canonical translation-unit recipe. Raw native exports, failed hypotheses, full
relocation replays and retirement inventories stay private. Completed probe builds
are retired only after verification, with source/header/receipt history preserved.

The full public CI passes52 tests. The animation harness follows the migrated
Manager lookup owner and retains aborting activation-only dependencies outside
its selected scope. Cleanup retires16 completed probe products and losslessly
archives252 private headers, original receipts and seven changed input versions;
net savings597030 bytes. All230 current canonical hashes remain unchanged and
604/604 strict comparison passes again using existing objects without a rebuild.
