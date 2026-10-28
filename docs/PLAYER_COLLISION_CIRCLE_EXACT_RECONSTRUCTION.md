# CORE/EXACT-273 — entire original 466-byte Player circular collision and graze boss, with genuine 73/23-byte dependencies

Immutable native target: Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **complete 466-byte** game-owned circular collision boss at
**`0x004F8FF0..0x004F91C1`** is now fully authored in natural C++20 as
`Player::collision_circle(const Vector3&,float,int)` and strict-exact.
The entire original function is **121 x86 instructions / 466/466 native
bytes**, with **18 original independently verified relocated sites**.
A pair of true Player/PlayerRecord methods used directly by this boss
is also accepted as entire original functions. No partial native branch,
assembly, binary array, fake owner, padding or source-selected body exists.

| Complete original game-owned method | Native entry | Bytes | Original relocs | Canonical exact |
| --- | --- | ---: | ---: | ---: |
| `Player::collision_circle` | `0x004F8FF0` | **466** | **18** | **466/466** |
| `PlayerRecord::collision_radius_multiplier` | `0x004FF490` | **73** | **1** | **73/73** |
| `Player::collision_expansion_enabled` | `0x004FF800` | **23** | **0** | **23/23** |

Three complete native original functions, **562 game-authored native bytes
and 19 independently attested real PE relocation targets**. Whole
original native interval SHA-256 values, in table order:
`1dbd80b4fa999a78339fcfea4f1ad584b300b0bc7b8d1eb6873a35e3a4a28607`,
`78c30f309bb786a5f1197bca270044e47c6c156a8212cfefb2ee0dcecb3ecfb1`,
`5845e0c4a23e9e37d1b80cb548b31334261453c2c7793ecdc314a177d4f4e28e`.

## Real full Player circular hit/graze path

The original thiscall receiver is the actual already established
`Player` storage with native position at Player+`0x614`, selected by
the strictly accepted `Player::position_ref()` at `0x00460850`. The
original method computes **XY squared distance**, not square-root
distance, using the genuine existing
`geometry::squared_distance_xy(const Vector3&,const Vector3&)` at
`0x004560D0`, whose x87 float result is stored in a real native local.
It tests the existing `Player::focused` byte at +`0x204C` and selects
the corresponding actual collision radius from
`PlayerCollisionBounds::normal_radius` (Player+`0x2094`) or
`focus_radius` (Player+`0x2098`).

It then calls real `Context::player_record()` at `0x0041CAF0` through
the actual Player+`0x14858` Context pointer and reads the normalized
player radius multiplier by the separate whole native 73B
`PlayerRecord::collision_radius_multiplier()` at `0x004FF490`. The
returned integer is converted to float, multiplied by the selected
radius and divided by native **100.0f** at `0x0056E04C`. The separate
whole native 23B `Player::collision_expansion_enabled()` at
`0x004FF800` extracts exactly bit 4 of `Player::entity_flags` at +`0x14`;
when active the radius is multiplied by real `Player::collision_expansion`
at +`0x2238`, original **3.6f** at `0x00573164` and the existing radius.

The main path checks squared distance against adjusted Player radius
squared **plus the incoming Bullet radius squared**. When that test
fails, the original evaluates the graze range: the Bullet radius is
divided by native **2.5f** at `0x0056C8D4`, with a minimum **40.0f**
from native `0x00570560`. The graze limit is the squared sum of
adjusted Player radius and this margin, plus the same Bullet radius
squared. Non-overlap returns **0**; proximity inside the expanded
limit returns the native graze code **2**.

For a real hit, the method respects the true `FrontInf*` global at
`0x005C06A4` and its native `has_dialogue()` method at `0x00478160`.
A live dialogue masks the hit. If the caller supplies `mode != 0`,
it reports original code **2** instead of triggering player damage.
Otherwise the original tests Player life states **2**, **4** and **3**
through three genuine calls to `Player::state_value()` at `0x00411700`,
then checks the original `Timer+0x2050::greater_than(0)` at
`0x00461070`. Active immunity returns **1** without replaying damage;
otherwise the function invokes the external original full **336-byte**
`Player::apply_player_hit()` at `0x004F86F0` and returns **1**.
The complete native method uses a true original `0x18` local frame,
its actual C++ thiscall stack ABI and full **`ret 0x0C`** epilogue.

The exact 73B `PlayerRecord::collision_radius_multiplier()` uses the
**real PlayerRecord+`0xE8` field**, whose native original clamp range
is **0 through 100**. Ordinary `std::clamp(field_e8,0,100)` on the
actual `PlayerRecord` produces the original 73B code, including MSVC
`std::clamp<int>` reference semantics, native call at `0x00471170`
(`+0x2A REL32`), writing the selected integer back into `field_e8`
and returning its current value. The separate 23B Player flag getter
uses exactly `shr 4` and `and 1` without any relocation or invented
bitfield owner.

## Whole-body C++ codegen convergence, not a partial match

The first complete typed C++ circle boss, with the correct native
0x18 stack frame and real owners, emitted **473B** but had only
**97/121** native instruction mnemonics in original order. An
important difference was native source control flow: original code
places the **non-hit graze check first**, then the shared hit path.
Rewriting the hit test with a natural inverse guard reduced the
source to **467B** and aligned **118/121** original instruction kinds,
leaving the SSE compare/return order on the second graze threshold
incorrect. Distinguishing the real “out of graze range returns zero”
condition from “within graze range returns two” recovered the
**entire original 121/121 instruction mnemonic sequence** but produced
471B due to an unnecessary 5-byte jump skipping a nested `else`.

The genuine source structure is a **graze-first early-return guard with
no trailing `else`**, followed by the original shared hit handler.
This eliminates exactly that extra long jump through ordinary control
flow, giving a complete **466-byte object code contribution**,
**121/121 original instruction sequence** and **394/394 original
non-relocation bytes**, plus all **18** original relocation words.
No artificial codegen local, padding, assembler or source opcode switch
was used. The exact whole source lives in `src/PlayerCollisionCircle.cpp`.

For all **19** original relocation sites across the three methods,
independent Capstone x86 disassembly of the **locked original PE**
identifies the actual direct-call target or relocated data address
from the original semantic instruction operand, independently of the
COFF comparison solver. These include the original 100.0f/3.6f/2.5f/
40.0f float addresses, authentic Player/Context/FrontInf getters,
true `std::clamp<int>` call and original Player damage method.
The private original-site attestation is recorded in
`.analysis/core273-player-circle-record-native-attestation.json` and
`.analysis/core273-player-circle-native-attestation.log`.
The accepted canonical unit proofs are recorded in
`.analysis/core273-player-circle-canonical-replay.log`:
**466/466, 73/73 and 23/23 entire original bytes; 3/3 units in one
fresh MSVC object**.

## Only actual shared-header affected sources recompiled

The narrowly declared real methods on `src/Player.hpp` and
`src/PlayerRecord.hpp` alter the original include-receipt closure of
**29 previously strict source providers / 249 previously exact native
units**. All 29 were rebuilt with locked MSVC x86 C++20 and
**249/249 existing units remained strictly machine-code exact**, including
all **58** previously accepted `PlayerRecord.cpp` units, the complete
777B rectangle Player collision, real Bullet command3/7 and Bullet
firing, Bomb, Hud, Session, Item, Hit controller and Player roots.
Some MSVC-private `$SG` string literal symbol identifiers renumbered;
updates were restricted to those labels, keeping original relocation
offset, COFF type and independently anchored native data destination
unchanged, followed by strict source recompile and replay. No other
native byte, symbol or target discrepancy was waived.

With the three new whole functions the actual changed-header replay
total is **252/252 strict native units across 30 freshly compiled
objects**. The original locked executable SHA remains unchanged. The
old-source logs are
`.analysis/core273-circle-affected-replay-part-{0..2}.log` and private
symbol audits are in `.analysis/core273-circle-sg-corrections.jsonl`.
No unfiltered whole-repository cold replay was performed.

The **777B Player rectangle** and **466B Player circle** collision
paths are now both whole-function exact, but their parent
**2,018-byte Bullet collision state machine** `0x00484A20`, the
**336-byte** Player damage handler, original **1,404B** Bullet command11,
**273B** single group drawer, **3,735B** shot emitter, **12,140B**
command sequencer and **41,967B** Enemy opcode root still require
independent full-function reconstruction. Native-source identity,
complete linking and game runtime remain separate acceptance goals.
