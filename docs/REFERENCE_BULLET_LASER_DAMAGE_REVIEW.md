# Bullet, Laser and Damage Regions review (REF-028)

This related batch contains 413 indexed implementations: Bullet100, Laser216
and Damage Regions97. The exhaustive individual review is ongoing. This first
component checkpoint records two absorbed geometry bodies; the other411 remain
pending. Global coverage is2,970 terminal /3,974 pending of6,944. Parser gaps
remain53 reconciled /60 pending. Compilation and source reading do not count as
terminal review decisions.

## Complete natural exact components

Seven additions pass complete canonical relocation replay against the approved
Japanese v1.00a Steamless executable. All136 configured units were cold-built
serially across35 objects and replayed, totaling9,104 complete bytes. The new
components contribute640 bytes. All seven origins remain pending: authored
credit remains57 functions /4,074 bytes, pending-origin75, library equivalents4.
Original class/function spellings are not established by neutral maintained names.

| Actual component | Original address | Complete bytes |
| --- | --- | ---: |
| Vector2 constructor | 0x004398A0 | 35 |
| ExtendedCommand constructor | 0x0047BD90 | 106 |
| ShotParameters constructor | 0x0047BD20 | 106 |
| BulletCommand constructor | 0x0047BCA0 | 127 |
| Comparison-based absolute value | 0x00445680 | 49 |
| Circle point predicate | 0x00456FE0 | 95 |
| Axis-aligned rectangle point predicate | 0x00457300 | 122 |

ExtendedCommand is an actual64-byte value with Timer, two scalar floats, two
Vector3 members and four32-bit command-dependent words. Independent native array
constructors47B740 and4C81F0 pass stride64 and counts14/24 with constructor47BD90;
Bullet47BE00 places its array at+A0. Full enclosing Bullet/Laser owners and their
exception/runtime protocols remain open.

ShotParameters is an actual40-byte record. Position begins at+8, angle at+14,
angle step at+18, speed at+1C and speed step at+20. Shoot481780 independently
reads signed16-bit count+24 and rows+26. Its two leading32-bit fields select
type/color in shooting; full resource/shooting behavior is not accepted here.

BulletCommand is44 bytes on x86. Independent allocation47A790 requests44 bytes
before calling its constructor. Native initialization distinguishes four float
operands from later32-bit operands, opcode, flags and script slot. ETEX opcode24
in47DCF0 passes slot+28 as a character pointer to4A8920; that consumer then binds
the script through4A73F0. Host tests retain natural pointer width. Other opcode
aliases and original declarations remain hypotheses, not resolved type names.

Vector2 is an actual two-float value. Independent Region4BFFB0, Bullet47BE00 and
LaserSegment4C8240 construct it at their respective member offsets. It adds no
raw enclosing facade or fictitious storage to promote a small method.

The geometry absolute value uses `0 > value ? -value : value`. It preserves
negative zero and quiet-NaN sign. Circle comparison includes equality and squares
negative radii. Rectangle comparison uses full dimensions divided by two,
short-circuits and excludes equality. Native ordered comparisons reject NaN.
Independent approved-PE reads establish float2 at56C8D0 and the four-lane sign
mask at56D7D0; other native geometry/vector consumers corroborate these constants.
Timer422D90 and Vector3422E10 were independently recovered before this batch.
No solved diagnostic relocation field supplies a canonical anchor.

Portable C++20/UBSan checks cover dirty construction, retained natural pointer
layout, positive/negative zero, subnormals, infinity, quiet-NaN payload/sign,
translated integer lattices and immediate inside/outside boundary values. These
tests establish component invariants, not the original floating exception state
or whole-game behavior.

## Ongoing owner and oracle review

All56 unmodified actual CMake production TUs compile serially with their declared
strict-FP/include dependencies. The frozen-source receipts were refreshed after
adding the three maintained TUs. These compilations do not establish original
code identity. Full owner comparisons and per-body decisions remain ongoing.

The existing reference uses actual large Bullet528 / Controller286DA8, Laser
base6F8 / concrete beams18F8/1338/1370/1D30, RegionC4 / ControllerC460 layouts.
Their typed arrays, intrusive ownership, shared metadata, PMR paths, ANMs,
callback vtables, EH and allocation/destruction protocols remain open. Native
constructors call typed member constructors where reference source clears raw
aggregate storage. LaserSegment flags and CurveNode angle/EH remain follow-ups;
no one-element array or inert local was added to force their constructor output.

Retained CPU fixtures normalize selected vptr/allocation/style/callback addresses,
record some external events and use finite synthetic ANM programs. Bullet ETEX13
metadata tail padding is excluded in independently allocated comparisons;
constructor fill tests are separate. Offscreen-delay excludes the isolated CRT
NaN sqrt fault. Type2 ETEX13 checked-copy source behavior is explicitly distinct
from native copying into a two-command allocation. Neither historical report
totals nor compiling their production inputs establishes game/GPU equivalence.
Full retained-report/source-hash and fixture review remains pending. No native
Windows CPU oracle or reference evidence writer was executed in this checkpoint.

Continue all411 remaining bodies, their independent native boundaries and
complete COFF diagnostics, style initializer data, oracle/report bindings and
four parser-gap files. Keep each difficult case specific and continue the batch.
