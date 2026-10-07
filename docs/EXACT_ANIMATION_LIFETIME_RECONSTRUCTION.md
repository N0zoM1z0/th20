# EXACT-060: ANM construction, resource lifetime and reset

Ten whole functions add 2,855 instruction bytes and fifteen alignment bytes.
The frozen maintained graph strictly replays 427 units / 79 cold objects /
79,802 disjoint comparison bytes. New origins remain pending; authored coverage
remains 64 functions / 16,948 bytes. This batch supplies actual ANM owners and
extent dependencies for the pending Enemy movement root, rather than accepting
individual switch fragments.

| Native entry | Body bytes | Comparison bytes | Maintained role |
| --- | ---: | ---: | --- |
| 00448D70 | 725 | 730 | AnimationBase construction |
| 00448B40 | 498 | 503 | Animation construction |
| 00449370 | 62 | 67 | Nontrivial Animation destruction |
| 004299D0 | 1,106 | 1,106 | Partial state reset |
| 0044C240 | 171 | 171 | Resource release and handle retirement |
| 0044CB60 | 17 | 17 | Position reference |
| 004458E0 | 93 | 93 | Recursive inherited Y scale |
| 00445940 | 93 | 93 | Recursive inherited X scale |
| 004459A0 | 45 | 45 | Scaled height |
| 004459D0 | 45 | 45 | Scaled width |

## Real storage and compiler contracts

Animation.hpp owns Base0x4C0, Animation0x5E4 and pooled storage0x600 on native
x86. It uses the existing Timer, Vector2/Vector3, Matrix4, Angle and typed
interpolation, AnmVariables, AnimationHandle and five-pointer intrusive links.
All observed scalar fields have real storage. Offset names preserve unresolved
roles; there are no synthetic gaps, packing overrides or empty owner facades.
The Base+442, Animation+57A and pooled+5F9 gaps are implicit ABI padding and
are left untouched by construction.

The four Vector2 values at Base+378 form a real C array. Native construction
passes stride8/count4 and Vector2's constructor to the compiler vector iterator.
The interpolation at Base+1B4 uses Angle, established by its independent nested
constructor. The reference models that value as float and uses packed/raw
storage and range clearing; those declarations are not imported.

Array allocation at 4476C0 passes the actual 5E4 stride and both constructor
448B40 and destructor449370 to the EH vector iterator. This independently
establishes a nontrivial Animation lifetime. Its destructor calls the entire
171-byte resource release body. It is not modeled as an implicitly trivial
type merely because that initially gives a shorter pooled constructor.

Base construction and destruction register native handler567600; Animation
construction registers5682E0. All refer to the independently reviewed 36-byte
FuncInfo5A91B8 with flags5, establishing nonthrowing contracts. The natural
compiler emits matching complete handlers and metadata. These supporting
contributions receive no extra function or byte credit. The three corresponding
code contributions include five trailing INT3 bytes each; all are compared.

Animation.cpp uses one precise-FP /Od/Ob0/GS/Gy/Zl/SSE2/SDL/EHsc recipe. This
is a local matching recipe, not recovery of the game's global compiler flags
or original translation-unit partition. Shared child exception contracts remain
unchanged. Natural PooledAnimation construction now emits115/native59 under
this recipe because the real Animation destructor requires exception cleanup.
That complete mismatch remains pending. The earlier59-byte trivial-lifetime
probe is rejected. No prefix or exception-contract substitution is accepted.

## Partial reset and inherited extents

Reset is a state transition, not whole-object clearing. It writes the primary
identity matrix, default scale/color/flags, two timers, three variable defaults,
parent pointers, selected vectors and scalar angles, stops twelve interpolation
durations and clears +570. It preserves resource pointers and their size,
the handle, Base timer, other variable words, secondary color, vertex values,
other matrices, interpolation timers/modes/samples and other suffix state.
Natural brace assignments to vectors reproduce all1,106 bytes. A rejected
functional-constructor assignment probe emitted1,091 bytes with different
temporary/copy emission. Shared vector copy/move contracts were not changed.

Scale follows the Animation pointer at +558 recursively. Flag word Base+49C
bit12 suppresses inheritance on each receiver. The +55C pointer does not take
part in these scale getters. Width and height combine inherited scale with the
two float extents at Base+70. Native member read/call order and float/x87 return
behavior are preserved, including signed zero and NaN propagation.

The constant at56E068 is independently checked as all sixteen identity-matrix
floats. Two other complete file-binding bodies,438620 and438F10, copy that same
64-byte value. It is therefore an independent reset relocation anchor. Source
declares the real const Matrix4 owner; its production data definition and global
initialization contract remain pending. Public tests use an explicitly bounded
logical identity fixture, not copied native bytes or a claimed data unit.

## Resource release and independent anchors

Release frees nonnull geometry through the existing real DiagnosticAllocator,
clears geometry and byte count, calls callback release even for null, clears
the callback, clears the handle and sets Base+28 to -1. If +550 is nonzero,
the native body repeatedly clears the handle forever. The maintained body
preserves that path; it does not invent a return, exception or volatile field.
The semantic role of +550 and the neighboring +554 word remains unresolved.

Native41F7C0 independently establishes a callback pointer on the actual
eight-byte DiagnosticAllocator owner. It invokes virtual destruction through
41F880, acquires shared lock1 and deletes storage. The maintained owner declares
that dependency; its production body and the complete callback vtable remain
pending. Accepting the caller does not accept this dependency's implementation
or establish complete allocation-failure behavior.

Shared intrusive value/default construction reproduces complete native64/63
bytes at411970/418A10. AnimationHandle word assignment independently reproduces
21 bytes at4117A0, already accepted as Identifier32's physical head. These are
logical aliases with no duplicate credit. Existing whole value/Timer/matrix/
interpolation definitions and already audited constant/cookie/iterator symbols
anchor the other relocations. Every native instruction is decoded over its
complete body and agrees with attested Ghidra. Every canonical relocation is
replayed from these independent definitions, not solved from compared fields.

## Verification and remaining core work

Owned C++20/O2/UBSan tests cover dirty construction, five distinct self links,
free-node initialization and implicit-padding retention. They exercise chained
and locally suppressed scale inheritance, ignored +55C for scale, position
aliasing, signed zero and NaN. Dirty reset checks retained ownership and timer/
interpolation state, all flag bytes and both reset/retained matrices. Actual byte
allocation/release runs with an owned shared lock registry. A bounded callback
fixture verifies call argument/order without pretending to reconstruct its
virtual lifetime. Nontrivial destruction invokes cleanup; a separate timed
process confirms the nonzero+550 path does not return.

All31 public tests and private target/tracking/progress/full Ghidra gates pass.
All427 canonical units cold-build and strictly replay after shared declarations
change. Current receipts, reference/game files and native evidence stay intact.
Cleanup now removes1,957 obsolete files /56,669,951 bytes, about54 MiB. The
latest two duplicate probe object/receipt files total50,431 bytes; all158 current
canonical object/receipt hashes are unchanged. Native evidence and probe source
remain intact.

The whole Enemy movement update4A7710/1675 and dispatcher48C010/41967 remain
pending. This batch closes their actual Animation construction/reset/extents
dependencies. Controller/Context/file binding, handle resolution/retirement,
global viewport ownership, production callback destruction and enclosing Enemy
lifetimes remain the next coherent core work. No leaf-only diversion, partial
switch credit or whole-game linkage claim follows from this checkpoint.
