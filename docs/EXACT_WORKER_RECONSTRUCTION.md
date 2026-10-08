# Worker launch, replacement and shutdown lifetime

EXACT-053 closes five complete Worker lifecycle bodies: 666 instruction bytes
and five destructor alignment bytes. The canonical graph has 377 units across
67 cold objects and 58,903 disjoint complete comparison bytes. These five
contributions retain unknown origins; authored attribution stays at 57 functions
and 4,074 bytes. The existing 44-byte constructor remains exact.

## Actual owner and protocol

Worker retains its independently established x86 layout: a real 12-byte
`std::jthread` followed by `std::atomic<bool>` at offset 12, with total size 16.
Its constructor creates an empty thread and a false close flag. All maintained
lifecycle methods use the actual shared LockRegistry and recursive mutex slot 6.
These ordinary guards operate independently of tracked locking's enabled byte.

Start acquires slot 6, calls the separate guarded detach member, assigns false
to the close flag, constructs a temporary jthread from the function and argument
references, moves its ownership into the member, destroys the temporary and
releases the guard. Native callers pass a function address and the address of a
stored argument pointer. The maintained specialization uses `int(void*)` and
`void*`; original template/class spelling remains unknown. Argument capture
uses the actual standard thread implementation, with no callback adapter or
substitute thread service.

Starting a replacement detaches the old thread; it does not wait for that task.
The old task may still execute when the close flag resets. This is original
behavior, not a reconstructed cancellation guarantee. Callers must own any data
needed by detached tasks; these component bodies do not establish their larger
owners' lifetimes.

Close-and-join acquires the same slot, assigns true using atomic assignment,
and joins only when joinable. It holds the mutex while joining. Detach acquires
the mutex and detaches only when joinable, without changing the flag.
Close-and-detach acquires the mutex, assigns true, then calls detach, which
recursively acquires the same mutex. The destructor calls close-and-join before
normal jthread destruction. The native atomic assignment returns its input and
delegates to a sequentially consistent byte exchange; using a free `store`
facade would change this contribution and call partition.

| Address | Body bytes | Operation |
| --- | ---: | --- |
| 0040B1D0 | 176 | Start and replace the task |
| 0040BC60 | 136 | Detach if joinable |
| 0040BCF0 | 150 | Request close and join if joinable |
| 004BA8B0 | 133 | Request close and recursively guarded detach |
| 0040B980 | 71 | Destructor and normal member destruction |

The entire destructor contribution is 76 bytes, including five trailing INT3
bytes. Padding gets no body or authored credit. All native instructions,
branches, returns, compiler extents and relocation identities are reconciled.

## EH and compiler evidence

One precise-FP/GS/EHsc/Gd/SDL profile covers all six Worker functions, including
the earlier constructor. GS alone emits 137/123/120-byte guarded close/join,
detach and close/detach bodies instead of 150/136/133; SDL restores the full
native security-cookie frame. The 176-byte start body also matches completely.
This is a local compiler recipe, not an executable-wide build identification.

Fourteen complete generated EH contributions strictly replay with independently
decoded anchors: destructor handler and FuncInfo, three guarded methods' handler,
cleanup and complete unwind/data section, and the same three start supports.
Destructor handler 567600 refers to the previously established 36-byte FuncInfo
5A91B8 with flags 5. Guard handler 56762D and start handler 56755D independently
select flags-1 metadata at 5A91E4/5A9210. Each has one unwind state whose cleanup
releases the live guard at stack offset -14. Handler cookie locations preserve
the native guarded/start frame distinction. Generated cleanup alignment is
included; helpers and shared metadata get support evidence, not extra coverage.

The actual native jthread destructor, joinable, join, detach and atomic
assignment contributions agree with the locked headers. Two other library
contributions remain nonexact: jthread's function constructor is 120 versus
native 150 bytes, and its move assignment is 76 versus 94. The locked headers
mark named casts as `[[msvc::intrinsic]]`, omitting the native forward/move
helper calls. Microsoft's [attribute documentation](https://learn.microsoft.com/en-us/cpp/cpp/attributes2)
explains that compile-time replacement; an explicit Oi-off probe does not close
the differences. Original header/flag identity remains unresolved. Their actual
ABI and standard thread protocol corroborate the independent native call
anchors; their bodies receive no exact credit. No headers or compiler were
modified and no substitute standard-library implementation was added.

## Larger native callers and deferred scope

The full 4,119-byte loading body at 4BAD40 contains 1,064 instructions, 219
direct calls and five indirect calls. The eight-entry table at 4BBD58 selects
file paths and has a separate 32-byte extent. Fourteen otherwise unreferenced
jumps in the body still route to the shared failure path at 4BBD18; they are
included in the complete native audit. Failure marks flag bit 3, resets graphics
state, requests close/detach on the actual graphics Worker and invokes the
owner's virtual cleanup. Success likewise detaches that worker and performs
the observed state/resource transitions before virtual cleanup and returning
zero. The body includes actual configuration copying, callback registration,
record/replay decisions, resource factories and view/state globals. Its full
owner, allocator, resources and cleanup interfaces remain pending, so it is
not maintained as an artificial layout facade and receives no exact credit.

The complete graphics launch 4B99F0/164, graphics close 4D9E30/53 and snapshot
capture 4DE040/425 are also audited. Graphics close is a receiver method using
Worker at +D90 and a diagnostic call before detach-then-join; it is not a Worker
member. Launch also belongs to that graphics owner. Snapshot capture closes
another Worker at +DA0 and preserves surface/allocator/copy/release semantics.
Reference merged free helpers cannot establish these receiver or lifetime ABIs.
Original graphics, surface, resource and process-global ownership stays open.

## Verification and practical limits

All 377 units replay from 67 fresh cold compiler objects after the Worker/header
profile changes. Complete disjoint comparison coverage is 58,903 bytes.
The new owned C++20/UBSan test runs real tasks and shared recursive locking:
empty/repeated close, reset on restart, blocking join, plain detach, close/detach,
replacement while the old task remains active, slot-6 cross-thread exclusion
and destructor waiting. Detached-task completion is observed at thread exit;
fixture storage survives every task. Quiescent flag observation uses the actual
host thread size and does not claim the x86 layout for a portable compiler.
All 24 public tests and CI pass; target and full Ghidra text attest unchanged.

These checks establish the component protocol and accepted byte contributions.
They do not establish detached-task owner safety, self-join/fault execution,
exception injection, production registry startup, exact library constructor/move
emission, complete game linkage or playable runtime. In particular, a callback
that needs slot 6 while another thread holds it across join can block; the native
lock order is retained. Cross-owner lifetime recovery remains required.

## CORE/EXACT-086 member-task extension

The actual SaveManager specialization now uses a captured receiver, four-byte
member operation and copied argument, rather than a no-argument lambda. The
whole189-byte start,48-byte capture constructor and44-byte invocation strictly
replay281bytes. Complete native heap-tuple/invoke consumers establish the real
three-word protocol; EH39/13/44 also agrees without duplicate coverage. The
jthread helper's ABI is established but its native123-byte body remains nonexact.
The existing free-function/lifecycle units preserve their exact bytes. Actual
thread tests now exercise changed capture inputs, different member operations,
detached replacement and complete receiver/task lifetimes. See
[SaveManager evidence](EXACT_PROGRESS_SAVE_MANAGER_RECONSTRUCTION.md) for the
whole owner, copy/merge, pending disk callbacks and compiler disagreements.
