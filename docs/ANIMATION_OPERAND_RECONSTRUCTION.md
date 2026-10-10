# Animation operands and recursive direction

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-122 reconstructs eight complete methods needed by the main animation
interpreter. The four operand methods have 308 direct calls in its whole native
body. The interpreter itself remains open: its 39,470-byte body, two alignment
bytes and both 644/636-byte tables require one complete future comparison.

## Complete comparison contributions

| Maintained method | Entry | Code bytes | Alignment / pointer / index bytes | Complete bytes |
| --- | --- | ---: | ---: | ---: |
| `Animation::integer_argument` | `00437220` | 165 | 3 / 32 / 30 | 230 |
| `Animation::float_argument` | `00437310` | 244 | 0 / 64 / 32 | 340 |
| `Animation::integer_value` | `00437D00` | 301 | 3 / 72 / 36 | 412 |
| `Animation::float_value` | `00437EB0` | 835 | 1 / 144 / 0 | 980 |
| `Animation::rotation_sum` | `00437770` | 196 | 0 / 0 / 0 | 196 |
| `Animation::transform_direction` | `00437840` | 226 | 0 / 0 / 0 | 226 |
| `AnimationFile::script` | `00437490` | 25 | 0 / 0 / 0 | 25 |
| `GameRandom::range` | `00429800` | 44 | 0 / 0 / 0 | 44 |

These disjoint contributions total 2,453 bytes: 2,036 code, seven alignment,
312 pointer-table and 98 index-table bytes. Every one of 78 pointer entries,
98 compressed selections and 36 direct floating-value selections is retained.
Four independent complete native dispatcher audits reconcile all instruction
heads and selector paths without omitted heads or outside direct branches.
The complete 196/226-byte recursive functions independently reconcile against
attested Ghidra listings and the locked executable.

The natural source is [AnimationOperands.cpp](../src/AnimationOperands.cpp).
Declarations extend the existing complete `Animation`, `AnimationFile` and
`GameRandom` owners; their established x86 sizes remain `5E4`, `70` and `28`.
Graphics reads use the genuine `DE8` owner and its six `16C`-byte viewports.
No partial owner, invented padding, byte array, assembly or profile branch is
introduced. Original names and translation-unit partition remain inferred.

## Mutable argument protocol

The native instruction prefix contains signed 16-bit opcode at `+0`, unsigned
16-bit byte advance at `+2`, signed 16-bit time at `+4` and unsigned 16-bit
argument mask at `+6`. Argument words begin at `+8` with four-byte stride.
The main VM increments its signed opcode before unsigned dispatch: normalized
selections `0..635` correspond to actual opcodes `-1..634`. These native facts
do not establish packet storage lifetime or a maintained packet owner.

The argument helpers receive a live mutable argument pointer, the full mask
and an integer bit index. An unset mask bit returns the original pointer
without reading it, including a null pointer. A set bit can return a writable
alias into the real animation. Unsupported selectors retain the original
argument pointer. The floating selector converts to `int32` by truncation;
fractional encodings therefore participate in the same selector protocol.

| Selectors | Integer writable aliases | Floating writable aliases |
| --- | --- | --- |
| `10000..10003` | Variables `00/04/08/0C` | Original argument storage |
| `10004..10007` | Original argument storage | Variables `10/14/18/1C` |
| `10008..10009` | Variables `2C/30` | Original argument storage |
| `10013..10015` | Original argument storage | Position `AnimationBase+2C`, XYZ |
| `10023..10025` | Original argument storage | Rotation `AnimationBase+38`, XYZ |
| `10027..10028` | Original argument storage | Variables `34/38` |
| `10029` | Variable `3C` | Original argument storage |
| `10033..10035` | Original argument storage | Variables `20/24/28` |

Maintained tests cover all 65,536 masks, every bit index `0..15`, all register
selectors and nearby literal selectors, fractional floating encodings, null
masked inputs, pointer identity, writes through aliases and complete owner
images. A set bit requires readable typed argument storage. Floating selectors
must be finite and representable as `int32`; the fixture enables
`float-cast-overflow` checking instead of extending C++ behavior beyond that
domain. Instruction buffers cannot be presumed immutable from this protocol.

## Value evaluation and the shared random stream

Integer evaluation reads the seven integer registers and converts the nine
floating variables selected by `10004..10007`, `10027..10028` and
`10033..10035`. Selector `10022` calls `bounded` with variable `3C` converted
to `uint32`. A zero bound returns zero without consuming a sample; a negative
bound is the corresponding unsigned bound. Other integer inputs return
unchanged. Floating-register to integer conversions require finite,
representable values.

Floating evaluation includes the integer and floating aliases above. Its
additional selectors are:

| Selector | Native effect |
| --- | --- |
| `10010`, `10030` | Signed random range with variable `38` |
| `10011`, `10031` | Unit random range with variable `34` |
| `10012`, `10032` | Signed random range with variable `34` |
| `10016..10018` | Viewport 3: vector `00` plus vector `3C`, XYZ |
| `10019..10021` | Viewport 3: vector `24`, XYZ |
| `10022` | Unconditional random sample converted to float |
| `10026` | Z component of the mutating recursive rotation cache |

All these draws use native `005BA4C4`, the already established
`progress_random` stream shared with Progress. The separate `script_random`
at `005BA4A8` belongs to ECL/Item uses. Existing whole canonical Progress
relocation roles independently establish the former global. A random range
with a zero limit still draws; the zero-bound integer operation does not.
Duplicate random selector cases retain their actual separate native heads.

The 44-byte range method calls the established `unit` body and multiplies by
the limit. The 44-byte signed sibling remains in its existing genuine
[Item.cpp](../src/Item.cpp) body. The semantic fixture links that actual source,
its real RTTI dependencies and the real random engine/locking bodies. Its
independent scalar model computes the 48,271-multiplier recurrence modulo
2,147,483,647, models float operation boundaries and checks complete random
objects. The other random stream and the complete Graphics image stay
unchanged. The unsigned-to-floating compiler correction literal is verified
as the full 16-byte payload, including both double values and prior canonical
roles; a matching zero prefix would be insufficient evidence.

## Recursive rotation and direction

`rotation_sum` first copies its own current rotation into `vector_5D0`. If
parent `+558` exists and flag bit 12 permits inheritance, it adds the parent's
recursive cache, then normalizes each component of its own original rotation.
The cache captures the local angle before wrapping. A root or blocked node
does not wrap its own angle. Repeated queries can therefore return different
values while changing original angles and caches throughout the visited
chain. Selector `10026` has these same side effects.

`transform_direction` visits the permitted parent first, passing its own bits
5 and 22 as that parent's rotate/scale arguments. It then rotates XY with its
own rotation Z if its caller's rotate argument is nonzero, and scales X/Y
with its own scale if the caller's scale argument is nonzero. The arguments
are full `int32` predicates: values such as `256` and `-256` are true. Z is
retained. Position, window offsets and projection do not enter this operation.

An independent root-to-leaf model covers all three-node combinations of bits
12, 5 and 22, repeated cache reads, full owner images, mutable cache/reference
identity, positive/negative full-width direction arguments, external vectors
and aliases to an owner's position vector. Accepted parent storage is live,
acyclic and finite. Mutating aliases to angle/scale inputs themselves are
outside this fixture's supported alias domain.

The file getter returns `scripts[index]` without checks or packet access.
Tests use a genuine file owner, an interior borrowed pointer-table origin,
valid positive/negative indices, null entries and an unchanged complete image.
The original file destructor, resource loading and packet lifetimes remain
undefined interfaces; the fixture releases its borrowed table before an
explicit resource-absent destructor boundary.

## Acceptance and remaining scope

Private strict replay passes all eight complete roots and 123 independently
resolved relocations, plus ten whole canonical dependencies. Local COFF labels
are resolved within their owning section and function: reused label names in
different methods are not global identities. A first structure-only trial used
the wrong random global and a position getter in place of `rotation_sum`; its
original compiler inputs are archived and it receives no exact credit.

The maintained O2 fixture passes 157,851 actual-owner cases under ASan, UBSan
and float-cast-overflow checking. Allocator startup, resource-absent Graphics
and file destruction are explicit fixture boundaries. Animation construction,
destruction, math, Workers, locks, random draws and the tested methods use real
maintained bodies. An initial fixture null allocator was caught by the actual
Animation destructor and corrected; failed inputs and diagnostics are retained.

The affected frozen production graph passes 818 strict units, 159 fresh
objects, 160,507 disjoint comparison bytes and 274 source files. Mappings become
833; fifteen whole nonexact roots remain. No new authored-origin credit is
inferred: authored 94 / 30,383 bytes, confirmed 98 and all 6,945 terminal
reference reviews remain separate. Full production root/support replay, maintained semantics and all 78 public tests
pass. Protect current canonical products and the immutable original input
archives during periodic cleanup.

The whole VM, Renderer storage at offset `+06000DFC`, five indirect VM callback calls,
full file VM creation, native buffer allocation/lifetime and gameplay rendering
remain open. Closing the operand protocol supports the main VM reconstruction;
it does not establish partial exact credit for that interpreter.

Protected retirement removes 469 files / 10057259 bytes
(9.59 MiB). All 818 exact replay results, 274 source hashes,
318 current canonical products, 60 native evidence hashes and five original
input archives remain unchanged. The old158 canonical pairs, migrated private
pair, archived host input copies, wrong-anchor trial and regenerable caches retire;
current159 pairs, native evidence and original compiler inputs stay protected.
