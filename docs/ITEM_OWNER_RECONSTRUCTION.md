# Actual Item pool, lifetime and reward protocol

CORE/EXACT-104 reconstructs the complete Item/ItemInf storage and lifetime,
the full pool initializer, Context publication, scheduler registration, bulk
spawn caller and OverlayCounter reward consumer. Sixteen complete roots replay
2,195 disjoint bytes and 93 independently anchored relocations. This includes
three complete five-byte compiler padding tails. The 22-byte Context setter
shares an existing physical contribution and receives no duplicate credit.

## Complete functions and storage

The maintained bodies share `src/Item.cpp`; actual declarations live in
`src/Item.hpp`, `src/Context.hpp` and `src/GameRandom.hpp`.

| Function | Native address | Body / full comparison bytes |
| --- | --- | ---: |
| Item::Item | 0x004C21B0 | 298 |
| Item::~Item | 0x004C2490 | 37 |
| ItemInf::ItemInf | 0x004C22E0 | 330 / 335 |
| ItemInf::~ItemInf | 0x004C24C0 | 150 / 155 |
| Item::select_context | 0x004C4F90 | 54 |
| ItemInf::select_context | 0x004C4FD0 | 54 |
| ItemInf::enable | 0x004C4650 | 74 |
| ItemInf::initialize_pool | 0x004BC220 | 596 |
| ItemInf::initialize | 0x004C3C00 | 141 |
| ItemInf::spawn_many | 0x004C45B0 | 147 |
| Context::item_controller | 0x0041CAB0 | 17 |
| item_controller | 0x00498FD0 | 26 |
| GameRandom::signed_range | 0x004298B0 | 44 |
| OverlayCounter::add_reward | 0x00533720 | 90 |
| std::array<Item,1536> constructor | 0x004C2180 | 44 |
| std::array<Item,1536> destructor | 0x004C2430 | 78 / 83 |

Item is 0xC4C bytes on x86. Its five-pointer link is followed by a free-list
pointer and two actual 0x5E4 Animation values at +18 and +5FC. The real
AnimationHandle is at +BE0, position/velocity at +BE4/+BF0, and two Timer
values at +C04/+C14. State/type, attraction, generation, sound, view index
and Context fields occupy their observed offsets through +C48. There is no
invented receiver prefix, opaque replacement Animation or padding field.

ItemInf is a real TaskInfo-derived 0x49C89C-byte owner. A third scheduler node
at +14 precedes 1,536 actual Item values at +18. Active, ordinary-free and
special-free sentinel lists begin at +49C818/+49C830/+49C848. Scalar counters,
speed/attraction state, attraction center and view/Context follow through
+49C898. Locked-compiler size/offset assertions check the complete storage.

## Native ownership and initialization

Item construction builds both Animations, vectors, handle and timers through
their real maintained constructors. Destruction implicitly releases the two
Animation members in reverse order. The array constructor uses the original
five-argument EH vector-construction helper with both Item constructor and
destructor pointers. Item retains an ordinary potentially throwing declaration;
ItemInf's nonthrowing declaration reproduces its complete zero-state EH
handler/FuncInfo. These are compiler/ABI observations; the original declaration
syntax and template spelling remain inferred.

The complete 596-byte initializer independently calls array size/data and
the original CRT memset for the entire Item array. This observed byte clear
requires resource-free Item/Animation storage and no live pool observers.
It does not release existing resources. Maintained source preserves that
operation with the actual array extent; no fabricated tail clear is introduced.
It rebuilds the active sentinel, then partitions slots 0..511 into the ordinary
free list and slots 512..1535 into the special free list. Each slot gets its
actual Item pointer, owning free-list pointer and complete list attachment.

Only spawn_counter, point_counter and generation are initially reset. The
tail sets speed_scale=1, field_49c880=0, field_49c87c=100 and bonus_counter=0.
Processed/special counts, attraction state/center and view/Context survive.
This is a bounded native initialization contract, not a general owner reset.

Initialization publishes actual this through Context+0C, then selects the
same context. It registers disabled update priority39, disabled draw priority35
and disabled secondary draw priority19 callbacks. Enable checks all three nodes.
The inherited TaskInfo disable affects only the first two nodes; source and
tests preserve that asymmetry. Destruction removes all three nodes through the
real scheduler before implicit array/Item/Animation/base destruction. It does
not clear Context publication, so a destroyed pointer must not be consumed.

## Reward and random consumers

The complete bulk-spawn caller uses a while loop with decrement after spawn.
Its angle is signed_range(pi/180*10)-pi/2 and speed is two. Type/position are
forwarded with colorFFFFFFFF, zero delay/extra and sound=-1. The genuine primary
spawn return is discarded, including a null result. The shared /fp:strict TU
profile naturally preserves the observed floating divisions/multiplication;
no volatile values, inert local constants or assembly shape the output.

GameRandom::signed_range multiplies the actual signed_unit result by its
float argument. The real process stream at 0x005BA4A8 is independently known
from startup and existing ECL consumers. All five relevant complete float
payloads are verified separately from relocated instruction fields.

The real eight-byte OverlayCounter adds amount modulo32 and repeatedly spawns
one Item through global Context 0 while current is strictly greater than threshold.
It subtracts threshold modulo32 after each call. Equality does not spawn.
The constructor's threshold is 1500; progressing execution requires a positive
threshold and a published live Item owner. No new invalid-domain guard changes
the original loop.

## Verification and remaining boundaries

Private actual O2/ASan/UBSan execution verifies complete construction, both
free-list partitions, retained owner fields, publication, original disabled
registration, enable3/disable2 and all three node removals. Geometry is allocated
only after pool initialization; actual destruction releases all 3,072 allocations
through the maintained allocator and Animation destructor. The reward scope
checks equality, multiple rewards, signed wrap, negative amounts, Context 0
selection, scaled RNG state consumption and zero/negative/multiple spawn counts.
The public test runs the maintained bodies with O2/UBSan and temporary binaries.

Process startup and identity matrix remain explicit fixtures. Original frame
callbacks abort if invoked; primary spawn only captures arguments in the test.
Animation callback release accepts null only. Unrelated Overlay destruction and
activation bindings abort to supply their required host RTTI. These fixtures
do not supply or accept original gameplay implementations.

Seventeen complete compiler/template/EH/vtable contributions replay as support,
including the full three-slot ItemInf weak E/G virtual table, scalar-deleting
body and shared zero-state metadata. Two pre-existing shared list implementations
remain nonexact: the natural constructor is 31/native 40 bytes because it omits
an original redundant tail store; reset differs in one register-selection byte.
They retain their existing independently identified native ABI boundaries.
No duplicate/inert store is added and no supporting or full link exactness is
claimed for them. Whole-function canonical credit remains separate from those
dependencies, authored/compiler attribution and full executable reconstruction.

The primary spawn at 0x004C3C90, update/draw callbacks, complete creator/factory,
original RTTI identities, weak-symbol resolution in a full link, game startup
and native runtime remain open. The complete damage query is still a private
1,685/native1,707-byte candidate; its original post-retirement heap lifetime
and hit callbacks are not accepted by this Item batch. Authored coverage remains
84 functions/24,209 bytes; reference absorption remains 238, all 6,945 reviews
stay terminal and claims stay header-only.

The frozen 253-file graph passes 747/747 canonical units across 143 fresh
objects and 140,553 disjoint compared bytes. Source mappings are 761; fourteen
whole nonexact methods remain. All 68 public tests pass in 207.343 seconds.
Periodic/final cleanup retires 179 products, releasing 916,533 bytes net of the
retired-input archive; all 286 current canonical hashes and 253 source hashes
remain protected, and all 747 existing-object results match the frozen proof.
Completed private Item/host graphs and original receipts are archived before
retirement. Current canonical objects, native evidence and active historical
whole-query inputs remain available. No unchanged graph is rebuilt for cleanup.
