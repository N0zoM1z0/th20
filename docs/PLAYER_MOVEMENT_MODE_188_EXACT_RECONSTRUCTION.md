# CORE/EXACT-420 — three entire original Player movement-mode and secondary-option methods (188 bytes)

Comparison original: user-approved Japanese TH20 v1.00a Steamless
`resources/th20.exe` with whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Three **physically distinct entire game-authored native methods**
called by the original **3,111-byte Player frame boss**
at `0x004F9C30` are now complete original byte-exact
in the real typed `PlayerOptionManagement.cpp` source
and `Player.hpp` / `PlayerStorage.hpp` class ABI:

| Whole original gameplay method | Native entry | Full native bytes | Entire original x86 instructions | Original E8 / PE HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `Player::movement_mode() const` | `0x004FF870` | **23/23** | 11 | **0 / 0** |
| `Player::set_movement_mode(uint32_t)` | `0x004FFF10` | **75/75** | 25 | **1 / 0** |
| `Player::set_secondary_option_field_fc(int)` | `0x004FB340` | **90/90** | 29 | **2 / 0** |

Total: **188 entirely original nonoverlapping native bytes**
and **65 full original instruction heads**, without
duplicate credit for existing exact Player, Timer or
PlayerValues helpers. Respective full original interval
SHA-256 values are:

- `e5b6620a7006473353ea86ecc7dfc5bd516ecbc8cda82a68f78d70e4919be753`
- `833ea709b57aefa9a4b50bff9b84b08c9d998957a967ec7fc3e3a5fa29066ded`
- `2429112396e35aaec33b15abf6dd93c0a25ea5c0b3c5619d8ce13c0d16781e5a`

## Real two-bit movement state and Timer control

The native Player `entity_flags` word at `+0x14`
has an actual two-bit movement-mode field at **bits 6
and 7**. The real C++ `PlayerWordFlags` is a
four-byte union of native raw-word and true bit-field
views. This checkpoint adds only another four-byte
view, with six lower bits, two mode bits and 24
upper bits, preserving every old member, class offset,
existing constructors and all other bit fields.

The 23-byte getter reads that actual two-bit mode
using native `shr 6; and 3`, preserving the original
`__thiscall` receiver in ECX. The full 75-byte
setter calls the real `Timer::operator=(int)` on
`Player::timer_2070` with zero, masks the requested
movement mode to its low two bits, and changes
only the corresponding bits of `entity_flags`.

**The exact C++ assignment-expression ABI matters.**
Ordinary source

`timer_2070 = 0;
 return entity_flags.mode_6_view.mode = value;`

generates the original complete 75-byte code:
one genuine stack local carries the freshly masked
word to the real native four-byte Player flags slot,
and its two-bit inserted value is returned through
EAX. A superficially equivalent, separate
`field = value; return field` formulation
generated **70 bytes** and unobserved reloads,
whereas an explicit bitmask expression could match
length but emit a different native register
sequence. Neither was falsely promoted to exact.
The accepted form expresses the actual original
value of the bit-field assignment, not an inert
compiler-shaping temporary.

The setter's sole original native E8/REL32 reference
at **`+0x15`** independently targets the already
whole-exact `Timer::operator=(int)` at
`0x00423520`. The getter has zero relocated fields.

## Real twelve-option hold/delay update and original alias

The complete original 90-byte
`set_secondary_option_field_fc(int)` receives
a value by stack and iterates only over the
twelve 300-byte `PlayerOption` objects in the actual
`secondary_options` array at `Player+0x123C`,
writing their native `field_fc` at `+0xFC`.
It **does not** modify the separately stored
ten primary option objects. The original begins
with an independently typed `PlayerValues<PlayerOption,12>`
begin pointer, reads its end once, then advances
through exactly 12 contiguous entries with 0x12C
byte stride. The real maintained C++ uses
the genuine array's `begin()` and `end()`
and a typed `PlayerOption*` current pointer.

The two original E8 fields are:
- **`+0x18` -> `0x0040BDA0`**:
  the genuine 14-byte begin method. It shares an
  *identical folded physical code interval* with the
  previously canonical `Motion::position_ref()`,
  but this is still **one** original physical
  function body, not another game-authored code credit.
- **`+0x23` -> `0x004FCE80`**:
  the separately exact 19-byte
  `PlayerValues<PlayerOption,12>::end()`.

All 3/3 PE E8 reference offsets/types/targets
across the three original methods agree with the
compiled locked MSVC COFF function references.
The original PE `.reloc` section independently
shows **zero HIGHLOW fields** across these
whole functions. The unchanged strict comparator
accepts **23/23, 75/75 and 90/90 complete native
bytes**. Evidence
`.analysis/core420-player-mode-original-refs.json`
records the full original code hashes, native
call sites, real independently accepted callee
entry addresses, COFF symbols and addends.

## Strict actual-header-receipt scoped replay

All three methods were added to the
**existing** `src/PlayerOptionManagement.cpp`
object provider, preserving its locked MSVC 19.44
i386 C++20 `/Od /Ob0 /GS /sdl /EHsc /fp:precise`
profile and five previously complete functions.
The public `Player.hpp` method declarations
and `PlayerStorage.hpp` four-byte bit-field
view are the only shared-header changes.

The old canonical compiler receipts were captured
**before** modifying those two headers. The real
prior include closure contains exactly **28 old
source providers with 81 strict native units**.
Adding three distinct exact methods to an
existing source object gives **84/84 actual affected
strict native units across 28 freshly cold-built
source objects**, in six serialized low-priority
batches of **5 + 31 + 10 + 13 + 11 + 14**.
Full scope:
`.analysis/core420-player-mode-preedit-closure.json`;
actual rebuilt groups:
`.analysis/core420-player-mode-replay-groups.json`;
complete strict logs:
`.analysis/core420-player-mode-replay-batch0.log`
through `batch5.log`.

One MSVC-private string `$SG` counter in the
full Player constructor renumbered after the
shared-header change. Its original PE
destination remained `0x00572BB8` and its
relocation offset/type plus complete
nonrelocation native bytes were independently
attested before accepting only that private
compiler symbol's spelling.
See `.analysis/core420-reconciled-private-symbols.json`.

The previously exact entire **1,081-byte
Player::update_option_frame**, **1,518-byte
option animation rebuild**, **966-byte Player
initial reset**, and **165-byte ordinary option
management** remain strictly exact, with all
their original native references. The
**3,111-byte original enclosing Player frame
boss remains independently nonexact/open**:
three exact callees do not prove that entire
caller or whole-game runtime linkage.

No unfiltered full-repository cold replay was run.
