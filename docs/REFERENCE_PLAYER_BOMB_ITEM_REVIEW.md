# Player, Bomb and Item review — ongoing batch

REF-030 reviews these related modules together: Player 611 implementations,
Bomb 83 and Item 190, totaling 884. This is a component checkpoint, not a
terminal review of those 884 entries. Global reference decisions remain
3,381 terminal / 3,563 pending; parser gaps remain 57 reconciled / 56 pending.
The exhaustive review goal remains active.

## Complete shared components

| Canonical unit | Native address | Complete bytes |
| --- | --- | ---: |
| Angle default construction | `0x00447DE0` | 24 |
| Angle float construction | `0x00429210` | 50 |
| Bounded angle normalization | `0x00438540` | 187 |
| Motion construction | `0x00478530` | 142 |
| Vector3 interpolation construction | `0x00447B30` | 97 |
| IntPoint default construction | `0x00414030` | 33 |
| IntPoint addition | `0x004F58F0` | 48 |

These seven contributions add 581 complete bytes. Maintained source extends
actual shared values, without introducing a padded Player or Bomb receiver.
All 144 units cold-build across 38 objects and replay 9,703 complete bytes.
Source presence is 144; pending origins are 83 and library units four.
Authored credit remains 57 functions / 4,074 bytes. Original type spellings
and authored/compiler/shared-code origins remain unresolved.

Every native extent is contiguous through its complete return. Independent
approved-PE instruction decoding verifies all bytes and internal branch targets;
there are no prefix comparisons or removed tables. Native Motion and Orb
constructors identify the shared Vector3, Angle, Timer and interpolation calls.
Option construction identifies the integer-pair zero constructor. Point addition
calls the already recovered coordinate constructor `0x0040DE00`, closing its
owner relationship with the existing atlas value. Ghidra's STL label at the
shared zero constructor does not prove an exclusive original class identity.

Motion is an actual 72-byte value with three Vector3 members and three
four-byte Angle members. Its final four-byte control aggregate selects a mode
in the low four bits; bit 5 freezes both native motion update routines.
Independent velocity/position consumers read the same offsets. Unknown scalar
roles retain offset-based names. Only construction is accepted; original
motion update, snapping, clock and surrounding resource protocols remain open.

VectorInterpolation extends the existing generic implementation to five
Vector3 members, followed by Timer at 60 and duration/mode at 76/80, size 84.
Value initialization supports both scalar and vector members naturally.
All existing byte/float interpolation contributions replay after that change;
no additional vector interpolation operation is credited.

Native angle reduction repeatedly subtracts or adds twice the rounded float pi,
stopping after at most 34 changes. Values already in the inclusive interval,
including signed zero and quiet NaNs, pass through. Infinities remain infinite;
large finite inputs may remain outside the interval after the cap. Float
construction clears its field, calls reduction and stores the x87 result.

Independent PE constants are pi `0x0056E0F0`, negative pi `0x0056E0F8` and two
`0x0056C8D0`; they were read as float words before canonical anchors were added.
Angle.cpp uses a shared mathematical constant and a strict floating-point
profile. Private precise emission was 180 bytes; strict emission with a local
constant was 200, including a local initialization. A shared constant under
strict FP yields the complete natural 187-byte routine. This per-source result
does not establish the original game's global build flags.

IntPoint addition uses unsigned modulo-32 arithmetic before signed conversion,
preserving x86 wraparound and the actual const-member aggregate-return ABI.
Portable C++20/UBSan tests cover signed boundaries, operand nonmutation, dirty
construction, angle boundaries, bounded large inputs, infinity/quiet-NaN/signed
zero behavior and interval/congruence properties across 16,001 finite inputs.
These tests execute shared source; they do not constitute a new Windows CPU
oracle run or proof of the original floating exception environment.

## Batch evidence and remaining work

All 101 indexed source files and all 884 body/file hashes are privately bound
to the pinned, unedited reference. Binding and compilation are not individual
review decisions. All three actual CMake recipes were read. The 52 original
production translation units compiled serially with their inherited include
paths and strict FP option: Player 37, Bomb seven, Item eight. Those initial
receipts precede these maintained-source additions; refresh after final source
freeze before using them for final batch comparisons. No full-batch fresh
COFF audit or terminal ledger entry is claimed at this checkpoint.

The native baseline includes 263 provisional leads; each rejected owner and
large function still needs complete boundary/table reconciliation. Bomb and
Item production bodies/headers and Player's construction, power, collision,
events and firing/callback/geometry/hit families have been read. Remaining
Player lifecycle/frame/adapters, all applicable fixtures and drivers, report
writers/source bindings, static/external COFF symbols, parser gaps and individual
hash-bound decisions are pending. Do not mark the batch reviewed by default.

A natural intrinsic float-to-fixed probe preserves CVTTSS2SI behavior for
nonfinite/out-of-range values but emits 117 bytes against the native complete
61-byte member. It is not accepted. A plain C++ cast would leave those input
values outside its defined domain; no ABI substitution or truncated comparison
is used to conceal that difference.

Native Option and Shot construction contains typed handles, values, arrays,
EH/cookies and untouched padding that the reference's raw initialization does
not reproduce. Reimu Orb's target identifier has an actual typed constructor;
whole Bomb owners need their vtables, interpolation representation and lifetime
closure. Player's source-only services suffix and injected interfaces are not
original owner evidence. These are retained follow-up leads, without enclosing
owner or whole-game acceptance. Reference CPU reports and writers have not been
executed in this batch; gameplay, GPU/resource and allocator ownership remain
independent gates.
