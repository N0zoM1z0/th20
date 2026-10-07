# EXACT-045: complete Motion update protocol

This is the first native reconstruction batch after the exhaustive reference
review. It closes the two shared Motion update bodies and their immediate
angle/vector/math dependency family with natural maintained C++. The existing
reference remains reviewed historical evidence; no reference source or
reference probe driver was imported.

## Complete contributions

| Maintained operation | Native entry | Code bytes | Complete comparison bytes |
| --- | --- | ---: | ---: |
| Motion::update_velocity | 0x00453E40 | 694 | 716 |
| Motion::update_position | 0x00453AC0 | 809 | 832 |
| Motion::snap_position | 0x004543D0 | 119 | 119 |
| Motion::motion_vector | 0x004562C0 | 17 | 17 |
| Motion::set_motion_z | 0x004591F0 | 26 | 26 |
| Angle::operator=(float) | 0x00452F20 | 40 | 40 |
| Angle::operator+=(float) | 0x004530C0 | 47 | 47 |
| Angle::operator+(float) | 0x00452FC0 | 42 | 42 |
| Angle::operator-(const Angle&) | 0x004294E0 | 61 | 61 |
| Vector3::operator+ | 0x00429570 | 88 | 88 |
| Vector3::operator-= | 0x00429740 | 85 | 85 |
| polar | 0x00439330 | 89 | 89 |
| rotate_xy | 0x00458FA0 | 137 | 137 |
| vector_direction | 0x00456210 | 40 | 40 |
| floor_scalar | 0x004592B0 | 35 | 35 |
| angle_difference | 0x004396C0 | 150 | 150 |
| C++ float cosine overload | 0x004371D0 | 24 | 24 |
| C++ float sine overload | 0x00439530 | 24 | 24 |

The batch contributes 2,527 code bytes and 2,572 complete comparison bytes.
The two main bodies account for 1,503 code bytes. Their complete COFF
contributions include five-entry dispatch tables and natural alignment NOPs:
velocity has two alignment bytes and a table at 0x004540F8; position has three
alignment bytes and a table at 0x00453DEC. No comparison slices a prefix.

## Independent native evidence

The locked PE and wrapper-attested Ghidra disassembly establish all reachable
instructions, complete returns, member offsets, call targets and dispatch
blocks. A separate whole-range decode reconciles velocity's unreachable
five-byte case-1 jump at 0x00453F8E, which Ghidra excludes from its function
body. The actual case-1 table entry reaches the epilogue at 0x004540F2.
All direct branches and all ten table entries reach audited instruction
boundaries inside their respective code extents. Padding and tables are
accounted for separately from code coverage.

Constants are independently identified native float objects: zero at
0x0056E0E8, pi at 0x0056E0F0, two at 0x0056C8D0 and one hundred at 0x0056E04C.
The default clock is the float slot at 0x005AEFE4. Native callees establish
all external function anchors before canonical replay; compiler relocation
names and offsets bind to those reviewed destinations. Structural diagnostic
solutions are not the source of canonical anchors.

Callers connect these operations to the existing shared 72-byte Motion value
used by Bomb, Damage and Enemy. The maintained Motion field layout is
unchanged. The vector getter returns offset 0x38, and the Z setter writes
that vector's offset 0x40. It does not write velocity at 0x0C or damping at
0x34. Flags expose the observed low-four-bit mode, spin bit 4 and freeze bit 5.
Other bits are preserved.

## Recovered protocol

Freeze suppresses both updates. Mode 0 advances using the clock-scaled polar
vector, with positive damping applied to that vector and optional spin applied
to the angle. Modes 2 and 3 advance radius and angle; mode 3 scales one local
axis before rotating it around the stored base angle. Mode 4 advances phase,
updates a planar velocity vector, accumulates velocity and combines it with a
perpendicular oscillation. Its direction comes from movement before snapping.
Mode 1 and unsupported modes leave velocity unchanged; nonfrozen position
updates still round X and Y downward to hundredths. Z is preserved by snapping.

Polar and XY rotation preserve destination Z. Rotation computes the original
X contribution before writing Y, so source and destination may alias.
Angle assignment and addition retain the existing bounded normalization.
Angle subtraction uses the observed one-turn difference helper before normal
Angle construction; it is not an unrestricted modulo operation.
The float view emitted for Angle shares native entry 0x004292E0 with the
already canonical ClockScalar view, so it receives no duplicate unit credit.

## Compiler and validation

Angle retains its existing strict floating-point profile; Vector3 retains its
precise profile. MotionUpdates and MotionMath use strict floating point.
MotionUpdates enables /GS and explicitly requests strict GS checking for
update_position, whose native prologue/epilogue contain the cookie at
0x005B25C0 and check routine at 0x005429EE. The other functions retain their
observed unguarded frames. This is a recorded per-function security policy;
it does not establish the original executable-wide compiler flags.

MotionMath's calls through the standard C++ float sine/cosine overloads emit
two additional complete 24-byte header contributions. Their native callees
are the independently canonical float math wrappers. Matching those
contributions does not classify the original functions as library or authored.

All 259 units across 59 cold comparison objects strictly replay with zero
differences over 20,892 disjoint complete comparison bytes. Public C++20/UBSan
checks replace the old undefined-update test stubs with the maintained bodies.
They cover all 16 modes, both spin settings, frozen byte preservation, four
clock rates, three damping values, guarded receivers, composed update order,
independent finite trigonometric expectations, alias rotation, radial
invariants, negative coordinate snapping and signed zero.

The behavioral checks establish this finite component domain. They do not
establish original CRT exceptional-input/startup behavior or complete enclosing
game owners, resources, linkage or playable runtime. Original names and origins
remain pending. Authored exact credit stays 57 functions / 4,074 bytes;
source-present comparisons rise to 259, with 198 pending origins and four
previously classified library comparisons. Reference review totals remain
6,945 terminal bodies and 113 reconciled grammar files.
