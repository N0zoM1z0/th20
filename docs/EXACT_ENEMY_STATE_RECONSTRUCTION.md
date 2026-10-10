# Enemy state lifetime and ECL argument protocol

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-058 closes eleven complete functions supporting the whole Enemy dispatcher.
They add 1,581 disjoint bytes. The accepted graph contains 408 whole units in 76
cold objects over 75,637 comparison bytes. All new origins remain pending;
authored coverage remains 64 functions / 16,948 instruction bytes.

| Complete function | Address | Bytes |
| --- | --- | ---: |
| EnemyState constructor | 004A3060 | 765 |
| EnemyState destructor | 004A3AC0 | 65 |
| EnemyState initialization | 004A7170 | 416 |
| EnemyAnimationLink constructor | 0048B3D0 | 43 |
| EnemyQueuedRecord constructor | 0048B500 | 66 |
| EnemyBounds constructor | 004398D0 | 57 |
| Enemy virtual opcode entry | 004969E0 | 25 |
| Enemy integer argument | 004AB0E0 | 36 |
| Enemy float argument | 004AB010 | 36 |
| EnemyState integer argument | 004AB080 | 36 |
| EnemyState float argument | 004AAFB0 | 36 |

The maintained bodies are `src/EnemyState.cpp` and `src/EnemyScript.cpp`, with
shared owner declarations in `src/EnemyState.hpp` and `src/Enemy.hpp`. Each unit
uses pinned MSVC 19.44.35211 x86, C++20, `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl`. All 53 relocations are replayed from independently bound
definitions. Complete contribution lengths match; no prefix, case fragment,
padding insertion, profile-specific body, assembly or target bytes are used.

## Actual owners

Native Enemy construction at 004A33C0, destruction at 004A3B10 and initialization
at 004A73F0 independently establish the 0x428-byte enclosing owner. EclManager
occupies the first 0x70 bytes; a flags word and twenty-byte intrusive link precede
EnemyState at +0x88. SpawnParameters is the existing EnemySpawn value at +0x378.
The child list, parent link, real `std::function<void(Enemy*)>`, player index and
Context pointer occupy +0x3CC, +0x3E4, +0x3F8, +0x420 and +0x424. Normal pinned
compiler layout satisfies these offsets without a packing override. The
enclosing constructor/destructor and four virtual variable resolvers remain
declarations only.

The State constructor establishes a real 752-byte owner. It reuses maintained
Identifier32, AnimationHandle, Vector2/Vector3, EnemyCounters, Timer, Motion,
EnemyMovement, EnemyHealth and EnemyPattern types. Scalar stores distinguish
floats at +38/+3C/+40/+4C/+274 from surrounding integer storage. The reference's
raw integer arrays would conceal these types and cannot reproduce the complete
constructor. Three flags words at +2C8 initialize as one value; their independent
word accesses are observed, while their complete named bitfield model remains
open. Callback-address words retain raw storage pending their complete ABI.

| Owned State container | Offset | Native element layout |
| --- | --- | --- |
| PMR vector of animation links | +0C | 20 bytes: AnimationHandle, Vector3, signed parent |
| PMR vector of movement records | +158 | Existing EnemyMovement, 388 bytes |
| PMR forward_list of queued shot records | +168 | 76-byte value; 80-byte node |
| PMR vector of phase records | +2B8 | 136 bytes: signed life/time and two 64-byte script names |

The queued constructor calls the actual shared-pointer constructor at 0047B880,
ShotParameters at 0047BD20, and two Vector3 constructors at +34/+40, with a scalar
at +30. Shot metadata is its provisional pointed-to role; the metadata object's
full layout, factory and native control-block implementations remain undefined.
This is a real `shared_ptr` member, not an opaque array or replacement owner.
Default initialization calls its constructor directly. A rejected value-initialized
probe added an outer eight-byte zeroing pass and emitted 76 instruction bytes
instead of the native 66; it receives no exact credit.

Independent phase consumers 004AB650/004AB780 identify life/time and two bounded
name-copy destinations at +08/+48. Vector size 004ABA00 and indexing 0048BD40
independently use stride 0x88. This replaces the reference's undifferentiated
34-word record. Complete record factory/resize semantics remain outside this
checkpoint. The bounds constructor 004398D0 initializes four floats; opcode 504
and movement bounds consumers corroborate center coordinates and dimensions.

## Initialization and destruction

State initialization returns integer zero, contrary to the reference's `void`
facade. It clears movement records before resizing to one, but resizes animation
records directly, preserving an existing first element. It clears phase records
without releasing vector capacity. The queued list is untouched. Four selected
timers are assigned zero; the third late timer at +2A8 survives. Health reset
retains scaled health, threshold and other flags, while Pattern reset follows
the existing complete native reset protocol. Both native stores to +254 are
preserved.

The defaulted State destructor reproduces the reverse container destruction
order: phases, queued records, movement records, then animation links. It does
not invent destruction of raw mesh/context/entity pointers; enclosing Enemy
destruction is a separate unresolved body.

Portable owned C++20/O2/UBSan tests construct State in dirty guarded storage and
use a counting PMR resource. They check initialization with existing animation,
movement and phase elements; retained queued shared ownership; partial health
reset; timer and flags retention; zeroed movement; and complete allocation release
at destruction. The metadata payload is explicitly a test fixture, not a native
object implementation. These checks establish component state/lifetime behavior,
not native allocation failures, exception unwinding or full gameplay.

## Dispatcher entry and argument forwarding

The virtual Enemy entry at 004969E0 forwards to the entire State dispatcher at
0048C010 after adjusting the receiver by +0x88. Its callee remains undefined;
accepting this complete wrapper does not accept any part of the 41,967-byte root.

The two State argument helpers load `entity` at +08. Their Enemy helpers load
the inherited current Runtime at +0C, then call the existing Runtime argument
entry declarations 0053ED50/0053E970. Each receiver is retained through a named
reference, matching the observed two-local frame. Integer return uses EAX and
float return uses the native x87 convention. These are State/Enemy helpers,
not EclManager methods. Runtime readers themselves remain pending.

## Independent exact evidence and open root

Private read-only Ghidra exports cover construction/initialization/destruction,
container implementations, phase consumers, value constructors and argument
forwarding. Existing canonical child/math/Timer/Runtime anchors are reused.
New container and record anchors come from their independently inspected
definitions, not solved comparison fields. The 24.0f constant at 0056F7B4 is
corroborated by external consumers at 0047242D/00472450 and hash-attested .rdata;
the existing canonical 1.0f anchor remains 0056C8CC.

The complete Enemy root has 8,896 instructions, 174 primary jump-table entries,
704 compressed opcode indices and 236 distinct direct dependencies. Its full
read-only interval and table audit survive cleanup. Physical case intervals
group related protocols for subsequent reconstruction, but are not claimed as
accepted function boundaries. The whole decompilation remains private and is
used only as a guide to native evidence.

A natural enclosing Enemy constructor probe emitted 168 bytes versus the native
210, missing the original EH frame. That body is rejected and remains undefined.
Do not add an unproven nonthrowing contract or change child declarations merely
to reproduce EH emission. The next priority is the complete 0048C010 root and
its rendering, shot, animation and Context/controller dependencies. Unrelated
leaf harvesting remains deferred.

Private audit artifacts are `.analysis/core058-*` and
`.analysis/exact058-replay.log`; public reproduction uses the configured units.
Configuration and registration writers are one-time checkpoint tools and must
never be rerun after registration.

## Retired artifact cleanup

Before reconstruction, 1,944 obsolete generated files were removed, freeing
56,330,189 bytes. They included old reference/probe objects and receipts, retired
portable CMake trees, a stale public checkout, temporary standard-library setup
and bytecode caches. The existing 74 canonical objects and their receipts were
protected by manifest path and before/after SHA-256, then all 397 previous whole
units strictly replayed without rebuilding. Native exports, review records,
private probe source, current Enemy work, locked tools, Ghidra and supplied game
files were preserved. Cleanup grants no reconstruction coverage.
