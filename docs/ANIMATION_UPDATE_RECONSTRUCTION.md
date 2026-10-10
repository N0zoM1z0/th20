# Animation motion, interpolation and parent binding

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-120 closes six complete native functions in the existing canonical
Animation and File owners. Maintained source uses one body per operation, with
no copied decompiler code, assembly, arbitrary padding or profile branches.
The original VM and geometry update bodies remain open.

## Complete contributions

| Native head | Complete bytes | Maintained operation | Evidence scope |
| --- | ---: | --- | --- |
| `0x004382B0` | 194 | `AnimationFile::bind_animation(parent)` | Template preparation, parent inheritance, one VM call |
| `0x004374B0` | 67 | `Animation::slowdown` | Conditional recursive parent inheritance |
| `0x00435520` | 931 | `Animation::update_motion` | Rotation, scale and UV velocity updates |
| `0x004358D0` | 944 | `Animation::update_interpolations` | Twelve actual typed interpolation channels |
| `0x00438600` | 29 | `add_angles` | Scalar addition followed by bounded native reduction |
| `0x00437750` | 17 | `IntegerTripleInterpolation::current_value` | Reference to actual stored current state |

These add 2,182 disjoint comparison bytes and 67 independently resolved
relocations. Eleven complete supports are replayed separately: four signed
17-byte duration aliases, the 16-byte Angle float conversion and the six typed
sample bodies used by the frame update. Shared physical heads receive no duplicate
coverage. `AnimationUpdates.cpp` owns the four protocol bodies; the existing
Angle and Interpolation translation units retain their value operations.

Ghidra's function-only slowdown listing omits the internal two-byte jump at
`0x004374E4`. The complete 67-byte contribution includes it. A natural explicit
`else` retains that native control flow; a guard-return trial produced 65 bytes
and is rejected. Neither the native extent nor the compiler contribution is
shortened. The 931-byte motion trial with clock-first multiplication had 54
instruction differences. Velocity-first multiplication retains the native operand
load order without shaping locals. The common strict profile reproduces the four
AnimationUpdates bodies; Angle keeps its existing strict profile and Interpolation
its existing precise profile. These per-TU observations do not prove global game
compiler flags. The private Angle helper also matched under precise; production
routing and all old Angle contributions are checked under the existing strict
profile.

## Native storage and interpreter interface

The canonical Animation still has its actual 4C0 trivially-copyable base and
5E4 complete x86 size; File remains 70 bytes. A 32-bit view of the existing flag
word exposes only the corroborated bit24, keeping the other 31 bits unnamed.
The interpreter's native case at `0x0042D25B` reads one input byte, narrows it to
bit0, shifts to bit24 and merges it into the same word at Animation+49C.
The independent binding consumer clears that same bit and inherits it from its
parent. The view does not invent storage, padding or a meaning for that flag.
Its union representation follows the repository's existing native flag views;
portable tests exercise the actual compiler representation separately from x86
layout assertions.

The full VM entry at `0x0042B5D0` passes the actual Animation in ECX and returns
with no stack arguments. Ordinary and already-stopped exits clear full EAX;
the deletion exit writes full EAX=1. An independent complete 508-byte owner
consumer at `0x00449870` calls it and tests full EAX before removing the Animation.
This establishes the genuine `int32_t Animation::update()` interface, rather
than a narrowed return or a fabricated void body. The 39,470-byte interpreter
body remains undefined in production; declaring its observed ABI is separate
from reconstructing it. Its epilogue invokes the complete motion and interpolation
functions, followed by the still-open 5,388-byte geometry update at 435C80.
Function-only interpreter evidence can omit switch cases even without truncation.

## Preserved behavior

Parent binding first runs the accepted template preparation. With a parent it
inherits only bit24, invokes the real layer-update operation, records the supplied
parent at +55C, and selects exactly one +558 hop when present. It copies +4E8
from that selected object and publishes it at +558. Without a parent it clears
both pointers. It then calls the actual integer-return VM interface exactly once
and ignores its return. The parent can be the destination itself or the selected
template; read order follows the native template copy. It does not walk to the
last ancestor. Template storage must be valid and the base copy nonoverlapping;
resource ownership and observer topology are retained.

Slowdown follows +558 while flag bit12 is clear, otherwise returns the current
object's +560 float. The finite acyclic test domain does not claim behavior for
malformed cycles or unbounded recursive depth.

Motion samples the default clock separately for each nonzero velocity, including
NaN as nonzero. X/Y/Z rotation uses scalar angle addition, scale updates run Y
before X, and the two UV channels add their respective velocity. Each UV update
subtracts 2 when at least 2, or adds 2 when below zero, exactly once. Large deltas
can therefore remain outside the nominal range. Rotation/scale dirty bits follow
the actual modified channels; UV updates do not set those bits. NaN, infinity
and signed-zero paths retain the native comparisons. Bounded angle reduction is
inherited from the accepted scalar helper.

Interpolation tests the complete signed duration for nonzero, including negative
values. Position chooses +2C or +484 from flag bit6. The twelve channels update
position, two RGB/alpha pairs, three Vector2 destinations, Vector3 rotation,
scalar Z angle and two UV velocities in native order. RGB sampling discards its
returned aggregate and reads stored current separately for red, green and blue.
On positive terminal duration the accepted sample clamps its Timer and returns
the endpoint without updating current: RGB therefore retains old current, while
alpha uses the returned endpoint. The reconstruction preserves that difference.
Dirty bits and byte narrowing follow the actual destinations. No endpoint repair
or activity-boolean substitution is applied.

## Independent checks and remaining scope

The private and maintained production O2/ASan/UBSan fixtures exercise 49,664
cases with full object-state expectations: 15,360 velocity/clock combinations,
32,768 twelve-channel activation combinations, 768 parent/template/alias cases
and 768 slowdown selections. Position routing is varied independently from its
activation. Linear, velocity and acceleration interpolation contracts use a
separate table oracle and component arithmetic; the tests also check terminal
current behavior, negative durations, byte wrap, dirty flags and Timer state.
NaN classification is checked without claiming portable NaN payload identity.
Native exact comparison supplies the separate byte-identity oracle.

The fixture borrows templates and captures the unresolved VM entry's complete
state, call count and mutations. It does not simulate or implement the original
interpreter. The actual diagnostic allocator, geometry retirement and intrusive
observer lifetimes are exercised. Original File loading/retirement, VM execution,
full linkage, startup and gameplay runtime remain open.

The frozen 271-source graph passes 800 strict units across 156 fresh objects
and 151,717 disjoint bytes. The six new roots do not establish application origin;
authored credit remains 94 functions/30,383 bytes, with 98 confirmed authored
functions, separate from the 815 component mappings and fifteen whole nonexact
methods. Reference review stays at 238 absorbed functions and all 6,945 terminal
reviews; claims remain header-only.

Keep the CORE120 frozen source, complete production proof/results, semantic
receipt, original 155 canonical and three private SHA-bound input closures and
attested native exports under ignored analysis storage. Superseded failed trials
are retired only after preserving their original closures and checking the
replacement. Final cleanup protects current pairs and strictly replays existing
objects without rebuilding unchanged source. The unknown Renderer+6000DFC
interval, whole 922-byte File VM creation, 226/338-byte reset lifetime contracts,
39,470-byte interpreter, 5,388-byte geometry update and Item main update/draw
remain independent next scopes. No guessed Renderer prefix is introduced.

All76 public tests pass in281.266 seconds; the complete public gate
passes in283.083 seconds. Whole production roots/supports
strictly replay and actual maintained O2/ASan/UBSan passes49664 cases. Each of156
affected objects compiles once;45 independent complete literal roles reconcile
30 label changes without solving a compared target field.

Protected final retirement removes324 files/8927535B;
combined with four mid-batch files, 328 files/
9045917B (8.63 MiB) retire.
Original155 canonical and three private compiler/SDK closures are SHA-verified
before deletion. All800 completed results,271 source hashes,312 current canonical
hashes,28 native evidence hashes and three original
closure archive hashes remain unchanged. Only superseded pairs, copied host TUs
and regenerable bytecode retire. No compiler runs for cleanup; original target,
reference, tools, database, current products and native evidence are protected.
