# Bullet, Laser and Damage Regions review (REF-029)

EXACT-063 independently reconstructs ShotMetadata construction at47BB90/255,
including five alignment bytes and complete native flags5 exception metadata.
Its body-hash-bound review now associates the complete canonical constructor;
reference arrays/byte fields/explicit padding are replaced with actual typed
storage. Four laser parameter lifetime owners and metadata move assignment also
close. Type3 +30 is float; Type2 flags are a neutral aggregate with original
spelling unknown. Factory/queue/laser entity roots remain pending. See
EXACT_ENEMY_TEMPORARY_RECONSTRUCTION.md. The REF-029 counts below are historical.

All 413 indexed implementations have individual, body-hash-bound decisions.
The earlier REF-028 component checkpoint absorbed two predicates; REF-029 closes
the remaining 411 decisions and adds the complete bullet-radius query.

| Module | Implementations | Absorbed exact | Nonexact | Support reviewed |
| --- | ---: | ---: | ---: | ---: |
| Bullet | 100 | 1 | 46 | 53 |
| Laser | 216 | 0 | 119 | 97 |
| Damage Regions | 97 | 2 | 49 | 46 |
| Total | 413 | 3 | 214 | 196 |

Global coverage is 3,381 terminal / 3,563 pending of 6,944. Parser gaps are
57 reconciled / 56 pending. The exhaustive goal remains active. Support review,
source presence, compiler diagnostics and native execution remain separate facts.

## Complete natural exact components

Eight additions pass complete canonical relocation replay against the approved
Japanese v1.00a Steamless executable. All 137 configured units were cold-built
serially across 36 objects and replayed, totaling 9,122 complete bytes. These
components contribute 658 bytes. All eight origins remain pending: authored
credit remains 57 functions / 4,074 bytes, pending-origin 76, library equivalents 4.
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
| Bullet-style radius query | 0x00485700 | 18 |

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

## Style data and original storage

The complete startup initializer at 0x00401280 is 38,669 bytes, ending with RET
at 0x0040A98C. Independent decoding checks all 5,126 contiguous instructions.
A closed straight-line interpreter follows integer/SSE scalar operations,
approved-PE literal loads, 3,415 direct word stores and 20 checked memset calls.
All 17,200 bytes in the writable BSS range [0x005C06A8, 0x005C49D8) are assigned.
Every one of the reference's 4,300 literal words matches the independently
derived result: 50 actual records of 344 bytes, radius at offset 0x144.

The resulting data SHA-256 is
`35d796ee81e65835bbaebca3c537ab39d188f3b22941a2f27abba2baf09fa56e`.
This audit does not execute native initialization or establish initializer code
exactness. The original reference recovery tool and its hardcoded Windows path
were read, not run. Its literal array is const; original storage is writable.
Maintained production source declares the actual array externally, without
defining its storage or copying original table constants. The natural unchecked
radius query accepts valid indices 0..49 and returns through x87 ST0. Its DIR32
anchor uses independently derived BSS base plus the real COFF member addend.
Portable tests use synthetic tables and verify all records, IEEE payloads and
whole-table nonmutation. They do not supply original global initialization.

## Complete contributions and owner limits

All 56 unmodified actual CMake production TUs compile serially with their
declared strict-FP/include dependencies. All objects and receipts were refreshed
after the final maintained-source freeze and re-attested. External and static
function symbols are included. The 236 complete contribution diagnostics find
222 size disagreements, one complete structural mismatch and 13 structural
matches. Only radius adds canonical acceptance here. The other 12 structural
matches need original enclosing owner/vtable/lifetime acceptance, including the
Bullet destructor, Laser position/no-op and Type3 shared literal methods.
No COFF contribution is sliced to a target-sized prefix.

The 250 attested native leads have no instruction-cap truncation. Independent
approved-PE reads recover 37 omitted direct JMP instructions and one nine-byte
range containing LEA/CALL/NOP skipped by normal control flow. Ownership of that
disconnected range remains open. Rejected switch-bearing extents/tables stay
provisional. Four actual laser constructors independently bind 34-slot vtables
at 0x00571148 / 0x005712E8 / 0x00571214 / 0x00571374; all 136 entries are checked.
Neither the executable nor the Ghidra database was modified.

The existing reference uses actual large Bullet528 / Controller286DA8, Laser
base6F8 / concrete beams18F8/1338/1370/1D30, RegionC4 / ControllerC460 layouts
(sizes here are hexadecimal).
Their typed arrays, intrusive ownership, shared metadata, PMR paths, ANMs,
callback vtables, EH and allocation/destruction protocols remain open. Native
constructors call typed member constructors where reference source clears raw
aggregate storage. LaserSegment flags and CurveNode angle/EH remain follow-ups;
no one-element array or inert local was added to force their constructor output.

Individual records distinguish the two linear-acceleration entries merged by a
source bool, extracted command/spawn helpers, shift-count policy, stage reset of
live shared_ptr storage, style invalid-color guards and full hit/ANM ownership.
Damage group subtraction occurs before duplicate-target gating; finite fixtures
exclude heap retirement followed by further Region reads. Type1 phase fallthrough,
Type0 versus Type1 sampling limits, Type2 mutating split and real child allocation
are recorded individually. No padded giant owner or inert compiler-shaping local
is introduced to accept a tiny setter or literal return.

## Retained oracle evidence

All module headers, production bodies, included fixture bodies, drivers, CMake
recipes and both evidence writers were read. Retained CPU fixtures normalize
selected vptr/allocation/style/callback addresses,
record some external events and use finite synthetic ANM programs. Bullet ETEX13
metadata tail padding is excluded in independently allocated comparisons;
constructor fill tests are separate. Offscreen-delay excludes the isolated CRT
NaN sqrt fault. Type2 ETEX13 checked-copy source behavior is explicitly distinct
from native copying into a two-command allocation. Neither historical report
totals nor compiling their production inputs establishes game/GPU equivalence.

| Retained report | Comparisons / failures | Current source bindings | Qualification |
| --- | ---: | --- | --- |
| Bullet pool | 341,623 / 0 | 389; shared digest current | All counted as native CPU observations |
| Laser pool | 431,652 / 0 | 389; shared digest current | 431,588 native CPU; 64 source-only |
| Damage CPU | 296,121 / 0 | 45 | Writer can bind hashes after the run |
| Shared Sprite | 2,915,831 / 0 | 389; digest current | Overlaps module reports; do not sum |

Historical Bullet first-batch 551,354/0 has six stale hashes; retire-before-fix
600,506/70 has seven; shoot-before-grouping 790,285/222 has eleven. Historical
Laser shape-padding 1,151,539/1,304 has fourteen stale hashes. Their copied relative
keys use the Sprite report namespace, an explicit path-base inference. None is
silently refreshed. Bullet's writer checks shared hashes before module extraction;
Damage's writer attaches current hashes to an already passed report without a
new binary-bound run. Source bindings do not prove which binary was executed.

Type2 opcode13 copies 420 bytes into original two-command metadata storage;
the source instead bounds-checks and throws after advancing its cursor. Its
64 source-only checks are kept separate. The ECL reachability note's queue-reset
and command7/3 analysis assumes normal entry, sequential VM execution and its
documented rank/memory conditions; it does not close cross-thread/reentrant or
whole native behavior. Damage's Bomb fixture covers inactive Bomb only; callbacks
and Item events are replaced. Full hit effects, GPU, native allocator/EH, malformed
inputs, startup, thread behavior and whole-game linkage remain open. No native
Windows CPU oracle or reference evidence writer was executed in this checkpoint.

Four parser-gap files are manually reconciled: Bullet style and Laser Type1/Type2
headers contain __cdecl declarations only; Laser pool's three __fastcall fixture
hooks are already indexed bodies. Six annotation sites omit no implementation.
Reference source remains unedited. Continue the remaining 3,563 implementations
and 56 gap files, next batching Player611 / Bomb83 / Item190 together.
