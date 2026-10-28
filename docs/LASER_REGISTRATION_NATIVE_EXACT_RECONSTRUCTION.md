# CORE/EXACT-194: complete native LaserController registration

A genuine complete native member, `LaserController::register_laser(Laser*)`
at `0x004C9300`, is now **75/75-byte exact** with the locked MSVC 19.44.35211
x86 compiler. The function is a real dependency of the separately still-open
**474-byte LaserController creator at `0x004D47F0`**, called once in each
of its four native type-switch arms. It is not an isolated portion of that
474-byte function and receives no credit for the larger caller or the
41,967-byte Enemy opcode boss dispatcher.

The maintained production source is `src/LaserRegistration.cpp` with the
minimal nonvirtual member declaration in the actual
`src/LaserParameters.hpp`. It uses the *existing* genuine `Laser` storage:
`chosen->link` at `+0x8` is initialized to its owner, then inserted at the
front of `LaserController.active` at `+0x10`, and finally the controller's
native count at `+0x28` increments. This order matters because a real
observer can see list mutation before the counter changes. No new dummy
Laser type, fabricated pool padding or raw-pointer shadow class was added
into the maintained production graph.

## Independent native evidence

The locked original native 75-byte function (SHA-256
`28a24828af40e6eb1ed92008242b513cc07f56742a87ee9aaca0222a570c480f`)
has exactly two original REL32 calls, reconstructed from the real PE
instruction bytes, not solved from a prospective COFF diff:

| Original relocation | Original destination | Observed role |
| --- | --- | --- |
| `+0x1A` | `0x0044A670` | `IntrusiveLink<Laser>::initialize(Laser*)` |
| `+0x32` | `0x0044A6B0` | `IntrusiveList<Laser>::prepend(link)` |

A further independent check of the original 474-byte factory confirms
four exact call sites to this genuine 75-byte member:
`0x004D48A1`, `0x004D4902`, `0x004D4960` and `0x004D49B8`.
They are reached only after type-specific allocation and successful virtual
initializer calls; the factory's other allocation and lifetime paths are
not claimed complete. Native callee control flow increments the controller
count **after** both link calls. The four original Laser subtype allocation
sites are independently visible in the 474-byte native disassembly; no
concrete subtype factory has been invented as an accepted production body.

## Exact codegen and affected-only regression

The natural source was first tested in a private derived-type compiler probe
to check the real owner layout without changing source. All **67/67
non-relocation bytes** matched and both original pointer/link destinations
were established independently. After adding the production method, its
canonical unit `laser_controller_register_laser` strictly replayed **all
75/75 bytes including both original relocations** with zero differences.
The accepted object is `build/core194-canonical/LaserRegistration.obj`
and its receipt, with source/object/target hashes protected privately in
`.analysis/core194-native-laser-registration-audit.json`.

The single shared header change affects exactly **three receipt-derived
canonical translation units**: `DialogueText.cpp`, `LaserParameters.cpp` and
`LaserRegistration.cpp`. Only these **3 objects** were cold-built and all
**22/22 complete** old/new canonical units passed strict relocation-aware
replay. The original target literal addresses and roles remained unchanged;
the MSVC internal `$SG` labels for one Laser initialization hint and four
Dialogue `text` literals were renumbered and verified against their fresh
COFF symbol identities. No function size, original target address or
relocation offset was edited to suppress a mismatch. The scoped full log is
`.analysis/core194-affected-replay.log`.

This adds **one authored exact function, 75 native bytes**, bringing accepted
TH20 to **221 authored exact / 57,517 bytes**, 1,007 canonical units and
1,016 mapped source-present entries. No full native cold replay was run.
The current full Enemy source draft's **40,941** prior GCC UBSan/ASan scenarios
remain protected as a separate completed checkpoint; the new production
registration method has **not yet** been exercised by those older private
laser-creation fixtures. A future whole-root host can use this actual method
on the successful creation path after independently reconstructing the
**474-byte** LaserController creator and its real virtual initializer ABI.
