# Player storage construction

EXACT-076 maintains seven complete construction contributions for the actual
Player subobjects required by the larger Enemy reader investigation. These are
typed native records with complete array and exception protocols. The complete
enclosing Player, its resources and gameplay remain open.

## Native storage evidence

The diagnostic allocator at `4F32B0` requests `0x1485C` bytes (84,060), invokes
the native compiler pre-clear helper and calls the 794-byte constructor at
`4F46A0`. Its calls establish ten and twelve Option elements, Feedback, the
ShotController and actual Animation storage. The reference's Services suffix
and raw memset constructors do not establish this owner or its original ABI.

The maintained Option is `0x12C` bytes. It contains actual Vector3, IntPoint,
Identifier32, AnimationHandle and Timer subobjects in native call order.
Floating-point stores establish the scalar types at `D8` and `110`. Its state
at `100` is an eight-byte flags/focus aggregate; the aggregate initialization
also covers the natural gap following its byte member. Unknown gameplay roles
retain offset names. The original names are not claimed.

Feedback is `0x5C` bytes with three separately constructed Timers, a Vector3,
an AnimationHandle, byte state, index and Context pointer. CollisionBounds is
the genuine `0x20` member with two float radii and two Vector3 extents; native
`4F4610` constructs it at Player `2094`. MotionParameters is the genuine five
float, `0x14` member at Player `2080`, constructed by `4F4650`.

Shot is `0x124` bytes. Its actual detached intrusive link is followed by state,
handles, Timers, flag words, the shared 72-byte Motion, Identifier32, more
scalar state, Vector2 extent, two eight-word arrays, damage identifier,
Vector3, byte state, player index and owner/Context pointers. The scalar at
`A4` defaults to one; the other constructed values default to zero/null.
DamageHandle at `DC` represents the independently observed damage identifier;
its constructor shares the native PackedColor physical head at `4142A0`.
This folding receives no duplicate comparison credit or exclusive type claim.

ShotController is `0x12598` bytes (75,160). Its actual pool constructs exactly
256 Shot objects at stride `0x124`; it also owns two intrusive lists, six
Timers, two thirty-word counter arrays and scalar state. The pool's explicit
nonthrowing constructor preserves the observed array-owner lifetime contract.
Shot itself retains its separately observed potentially throwing constructor
ABI. Original container/class spelling is unknown. The two lists initialize
their tails to their own sentinels; their independently emitted constructor
still differs from native code and is not newly credited here.

No maintained record contains an explicit padding field. Natural alignment
accounts for byte-state gaps. Static x86 assertions check sizes and important
offsets; portable tests do not assert that host pointer width reproduces x86.

## Complete contributions and comparison

| Native address | Maintained contribution | Body / comparison bytes |
| --- | --- | --- |
| `4F49C0` | `PlayerOption::PlayerOption` | 440 / 445 |
| `4F4580` | `PlayerFeedback::PlayerFeedback` | 133 / 133 |
| `4F4610` | `PlayerCollisionBounds::PlayerCollisionBounds` | 58 / 58 |
| `4F4650` | `PlayerMotionParameters::PlayerMotionParameters` | 68 / 68 |
| `4F4CB0` | `PlayerShot::PlayerShot` | 413 / 413 |
| `4F41D0` | `PlayerShotPool::PlayerShotPool` | 81 / 86 |
| `4F4B80` | `PlayerShotController::PlayerShotController` | 291 / 291 |

Together these add 1,484 body /1,494 disjoint comparison bytes. Option and
pool include all five following INT3 bytes. Both complete 29-byte EH handlers
and 36-byte nonthrowing information records match native support. The shared
24-byte damage handle constructor and 56-byte array construction iterator are
independently checked without duplicate credit. All relocation destinations
come from native member calls, fixed counts/strides and prior independent
canonical units, rather than solving the compared bytes.

One `src/PlayerStorage.cpp` owns `build/PlayerStorage.obj`, with flags
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The frozen graph strictly replays 575 units /105 fresh objects /100,616
disjoint comparison bytes. Origins are 502 pending, nine library and
64 authored /16,948 authored bytes. Four complete reference associations
close, including both the pool and controller targets in their shared row;
all 6,945 reviews remain terminal with 184 absorbed. Historical raw reference
bodies are not imported or asserted exact. All 47 public tests pass
(87.568 seconds); target, tracking, reference and progress gates pass.

## Owned semantic checks and unresolved boundaries

The O2/UBSan test constructs every actual production record in dirty guarded
storage, checks every typed default and all 256 Shot elements, then links,
transfers and removes the entire pool using the production intrusive protocol.
It checks sentinel recovery, detached state and defaults after removal.
Production Timer/Motion/Angle/handle/vector/point constructors are used; there
are no substitute construction bodies. The test discards unreferenced methods
when linking, and does not exercise Motion gameplay updates or native EH.
Exact x86 code and support are independently checked by canonical replay.

Native Player writes the identifier at `1484C`, index at `14854` and Context
pointer at `14858`; its constructor does not write the four bytes at `14850`.
The original declaration/type of that region is unresolved. A locked `.text`
scan finds the byte pattern `50 48 01 00` only inside the unrelated relative
CALL at `49612C`; bounded disassembly confirms it is not a Player field access.
The scan does not prove that no alternate instruction encoding or indirect
access exists. No placeholder word or padded Player facade is promoted.

Complete Player/Animation construction, allocation/destruction, callbacks,
resource loading, Option/Shot updates and gameplay remain open. Neither whole
Enemy variable reader nor the 41 KB opcode root is newly accepted. Child
constructor comparisons do not establish a linked native game.

Private evidence includes `core076-player-owner-support.asm`,
`core076-player-typed-support.asm`, `core076-player-tail-consumer.asm`, the
previous full owner construction export, and `core076-audit.py`. Failed
constructor probes are retained: applying noexcept to Feedback/Bounds/Shot/
Controller adds unwanted 47-byte exception protocol, while std::array-based
pool construction does not reproduce the complete 81-byte array owner.
The final genuine fixed pool preserves both owner and child exception ABI.
Sources, logs, receipts and original evidence remain separate from acceptance.

Completed configuration, registration and retirement writers are one-time
operations. Whole canonical receipts are compressed from the outset. Cleanup
preserves current objects/receipts, original target/reference/tools and all
native/failed source evidence; post-cleanup verification reuses current objects.

Protected retirement removes six completed probe object/receipt files,
126,345 bytes. All 210 current canonical hashes and native/failed source
files remain unchanged. Post-cleanup strict replay passes 575/575 with 105
existing objects and no rebuild. Private inventory and compressed proof are
`core076-probe-cleanup.json` and `core076-post-cleanup-results.json.gz`.
Cumulative retired build products are 2,538 files /1,002,311,858 bytes; separate
lossless archival savings remain 12,617,291 bytes. Analysis is approximately
74 MiB and build 4.6 MiB; installed tools are protected.
