# Player, Bomb and Item review

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

REF-030/031 reviews all 884 existing implementations in these related modules,
including production, adapters, inline bodies, local closures, fixtures, drivers
and the evidence writer. All 101 indexed files were read completely against the
unedited pinned reference. Each terminal decision binds its own body hash;
compilation or a file-level scan does not replace that review.

| Module | Bodies | Absorbed | Nonexact | Support |
| --- | ---: | ---: | ---: | ---: |
| Player | 611 | 1 | 114 | 496 |
| Bomb | 83 | 0 | 63 | 20 |
| Item | 190 | 0 | 44 | 146 |
| Total | 884 | 1 | 221 | 662 |

Global reference review now has 4,265 terminal decisions / 2,679 pending out of
6,944. Eight files with 27 grammar sites were manually reconciled; 65 gap files
are reconciled and 48 remain pending. The exhaustive review goal remains active.
Terminal nonexact decisions record difficulties and follow-up work; they do not
assert those implementations have been reconstructed.

## Shared exact components

| Canonical unit | Native address | Complete bytes |
| --- | --- | ---: |
| Angle default construction | `0x00447DE0` | 24 |
| Angle float construction | `0x00429210` | 50 |
| Bounded angle normalization | `0x00438540` | 187 |
| Motion construction | `0x00478530` | 142 |
| Vector3 interpolation construction | `0x00447B30` | 97 |
| IntPoint default construction | `0x00414030` | 33 |
| IntPoint addition | `0x004F58F0` | 48 |
| Motion update orchestration | `0x0047A1F0` | 28 |
| Motion outside rectangle | `0x0047A400` | 156 |

These nine contributions add 765 complete bytes across the two checkpoints.
All 146 canonical units cold-build across 38 objects and replay 9,887 complete
bytes. Source presence is 146; pending origins are 85 and library units four.
Authored credit remains 57 functions / 4,074 bytes. Original type spellings and
origins remain unresolved; no enclosing Player or Bomb facade was introduced.

Every accepted extent is contiguous through its complete return. Independent
approved-PE decoding verifies all bytes and internal branch targets. Native typed
constructors and consumers establish Angle4, Motion72, VectorInterpolation84 and
the existing IntPoint8. The integer pair's shared coordinate constructor at
`0x0040DE00` closes its relationship with the existing atlas value. Ghidra's STL
label on the shared zero constructor does not establish exclusive class identity.

Motion contains three Vector3 and three Angle members, unknown scalar fields
retaining their offsets, and a genuine four-byte control aggregate. The low four
bits select mode; bit 5 freezes the two underlying native updates. The accepted
wrapper calls velocity at `0x00453E40`, then position at `0x00453AC0`, on the same
receiver without a new clock argument. Those two dependency methods remain
undefined; this wrapper does not accept their implementations or game linkage.

The bounds member returns full-width integer zero or one; its independent Orb
caller tests EAX at `0x00479787`. It evaluates left, right, top and bottom in that
order using half dimensions and strict outside comparisons. Boundary equality
is inside; an unordered comparison alone does not report outside. It reads only
position x/y and retains the entire receiver. The reference free helpers and
bool declarations do not reproduce this native member/return protocol.

VectorInterpolation extends the existing generic implementation to five
Vector3 members, Timer at 60 and duration/mode at 76/80, size 84. All old scalar
interpolation contributions replay; only vector construction is accepted.

Native angle reduction stops after at most 34 additions/subtractions of twice
the rounded float pi. Signed zero and quiet NaNs pass through; infinity remains
infinite, and large finite inputs may remain unreduced. Independent PE constants
are pi `0x0056E0F0`, negative pi `0x0056E0F8` and two `0x0056C8D0`. These were read
before canonical anchors were added. A shared pi constant under strict FP emits
187 bytes, versus precise180 and local-constant strict200. This per-source
profile does not prove the game's global flags.

The one absorbed reference implementation is wrapping fixed-coordinate
addition. Maintained IntPoint restores the actual const receiver and hidden
aggregate return, calls the independently observed coordinate constructor and
preserves defined modulo32 arithmetic. The raw reference free-helper object is
not claimed exact. Portable C++20/UBSan tests check dirty construction, IEEE and
bounded-angle behavior, 16,001 finite angle cases, wrapping addition and operand
nonmutation. Motion tests observe the two undefined dependency calls and verify
order/receiver identity; rectangle lattice, nextafter, NaN/infinity/signed-zero,
negative dimensions and bytewise receiver preservation cover the predicate.
These are synthetic shared-source tests, not a new Windows CPU oracle run.

## Compiler, native boundaries and owners

All 52 unmodified production translation units compile serially after final
maintained-source freeze with actual inherited CMake include paths and strict FP:
Player37, Bomb7, Item8. Every current object and receipt attests. Defined static
and external function symbols are included. Complete contribution comparisons
cover all real emitted overloads rather than forcing header instantiations.

There are 434 unsliced comparisons: 420 size differences, two mismatches and
12 diagnostic structural matches. This includes 114 comparisons for all31
initialization,16 update and10 hit indices: both their real emitted adapter and
the merged source dispatcher are checked against each native table entry.
The two initially unresolved template symbols are covered by this explicit
instantiation inventory. No solved diagnostic relocation becomes a canonical
anchor. Complete rejected extents, associated tables and owner uncertainty remain
recorded; no prefix or table was removed to produce a match.

Native queries cover 341 heads below their limits. The large `0x0042B5D0`
interpreter was expanded to its complete exported flow after the initial cap.
All 62 ranges omitted by Ghidra disassembly independently decode as direct JMP
ranges in the approved PE. Six constructor-bound Bomb/character/Player/Item
vtables and three shot callback tables expose 87 observed slots. The selected
callback domains are31/16/10; trailing null words do not establish additional
valid indices. These observations route review and do not accept all provisional
function/table extents or original ownership.

The 12 structural matches are small Bomb/Controller/character members and shared
destructors. Actual B8/3C/CC/14F8 owners, typed interpolation, handles, CallbackOwner
and vtable/EH/resource lifetime must close before canonical absorption. The Orb
constructor calls the typed four-byte constructor at animation, target identifier
and damage-handle offsets; replacing them with raw words is insufficient. The
native array genuinely has24 D8 records, not an artificial one-element owner.

Player's native1485C prefix and source-only Services suffix remain distinct.
Raw Option/Shot/Feedback/ShotController construction does not explain original
typed member/array/EH emission. A defined intrinsic CVTT float-to-fixed probe
emits117 versus native61 bytes; it remains rejected. A plain C++ cast would leave
nonfinite/out-of-range inputs undefined. Item's repeated raw reset similarly
does not close lifetimes of its two typed ANMs per slot.

## Retained oracle and semantic scope

All relevant recipes, complete fixtures/drivers/writer and report bindings were
read. None of these Windows CPU oracles or evidence writers was executed here.
Existing report counts remain historical observations, without a current build
or executed-binary receipt.

Player's duplicate JSON reports are byte-identical: 1,032,161 checks, including
1,029,407 original CPU checks and 2,754 source assertions. All81 declared source
hashes are current. CMake generates the hash header at configuration; that does
not independently bind all linked dependencies or the retained executable.
Valid SHT relocation/factory/error/heap-overflow assertions are source-only.
Collision's positive invulnerability excludes actual hit effects; nonfinite
CRT trig faults are outside its retained isolated-image domain.

Firing's reuse fixture bypasses initialization; the native initializer group
uses callback0/sound-1 and common native ANM/Damage/RNG services on both paths.
Shot callbacks have synthetic Weapon/SoundCOM and shared native queries/resources;
Bullet/Laser lists are empty in those groups. Hit retirement uses fixed-pool
regions, so writing old Motion after retirement does not validate a genuinely
freed overflow heap object. Effect cursors are limited to0..1023. Geometry retains
collinear NaN output ordering and unchanged output z, but its finite-domain CPU
result does not establish native return ABI or instruction identity.

The complete main-frame fixture patches12 external endpoints in its isolated
mapped clone and restores them. It leaves the approved target/database unchanged.
Shots/Options start inactive and higher power allocation is suppressed; original
Movement/Death/ShotController/Feedback and shared ANM/interpolation still execute.
Movement has one live Option. Standalone death uses Sessionmode2, empty Enemy,
absent HUD and four ANMs. These are explicit limits on composition/resource
acceptance, not whole-game execution.

Bomb state68,387/0 binds current state.cpp and bomb.hpp only. The shared Sprite
report contains137,408 Bomb-related checks: core31,168, character97,024 and
cancellation9,216. These are subsets of its2,915,831 total, not additional totals.
Cancellation's report digest and all389 source bindings are current. Core uses
an observation Bomb vtable; character uses70 stopped ANM scripts and quiet Reimu
retirement; cancellation uses32 actual Bullets with empty Lasers. Nonempty Laser,
full character resources and continuous multi-frame gameplay remain untested.

Item287,824/0 binds33 current files and one stale rewards.hpp hash, also stale in
module_status.json. Its writer attaches hashes after a retained run without
rebuilding/rerunning; executing it now would not prove the older executable.
Frame traces replace activation/power and ANM/effect/HUD/score/phase boundaries;
full-type dispatch still hooks activation, with separate restored-body activation
cases. Invalid indexes, zero power unit, OOM and pool exhaustion are excluded.

Review records preserve observable quirks: recursive Item bonus before type
rejection, signed versus unsigned score adds,
20000+20000 full-power reward, captured extend threshold, Player publication and
retained-resource ownership, global0 versus selected context, hit callback
ordering, quiet Orb retirement and late shared timer/color/resource operations.
Whole graphics, threads, actual allocators, startup and playable game remain
independent acceptance gates.

CORE-108 independently audits the complete Item update and corrects the earlier
reference-frame interpretation: native states one and two both use ordered
outside-bounds branches, and forced collection uses ordered threshold greater
than Player y. The reference's negated comparisons differ for quiet NaNs with
masked SSE exceptions. Historical trace/fixture results do not prove those
original branches. See [complete Item update evidence](ITEM_UPDATE_RECONSTRUCTION.md).

The eight grammar files have27 calling-convention sites. Marisa's one is a
callback declaration; the other26 are already indexed Windows/fastcall/stdcall
fixture bodies. All complete files and body ranges were reconciled without
editing the reference. Individual records retain their hashes and scope.
