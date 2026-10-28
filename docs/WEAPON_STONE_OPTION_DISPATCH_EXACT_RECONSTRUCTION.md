# CORE/EXACT-326 — complete WeaponStone option script and two-weapon initialization dispatch

Target: unmodified Japanese TH20 v1.00a Steamless original, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Two more complete real game-owned methods in the `Player::rebuild_option_animations`
call graph are now independently strict exact in
`src/WeaponStoneOptionOffsets.cpp`:

| Whole method | Original entry | Native extent | Entire native evidence |
| --- | --- | ---: | --- |
| `WeaponStoneInfo::option_script_variant` | `0x00534130` | **77** bytes | Full x86 conditional and 2 original `REL32` sites |
| `WeaponStoneInfo::initialize_option_pair` | `0x00533180` | **90** bytes | Two complete original virtual dispatches |

The 77-byte method calls `player(0)` at **native field `+0x0A ->
0x00460830`**, then the actual Player focused-mode predicate at **`+0x14
-> 0x004FF5E0`**. Its two original branches call the corresponding virtual
`Weapon::script_variant()` at **vtable slot `+0x4C`**, using the actual
`WeaponStoneInfo::weapon_2c` or `weapon_30` member. The method preserves
the original return register `EAX`. Its *actual* C++ branch structure uses
an explicit `else` with both arms returning the virtual call result.
A private candidate with an implicit trailing return had only 75 bytes;
the explicit semantic `else` naturally emits the original additional
2-byte jump and is **77/77 byte exact**, without injected NOPs or filler.

The second complete 90-byte method calls both real Weapon virtual option
initializers in original order: focused at slot `+0x28` via `weapon_2c`,
then unfocused at slot `+0x2C` via `weapon_30`, forwarding the exact
`PlayerOption*` pointer and signed index arguments. It is **90/90 byte
exact**, without static relocations. Both methods use the real vtable
already declared in `src/Weapon.hpp`; no manually fabricated vtable or
raw memory callback address appears in maintained C++.

All **167 distinct new original bytes** and the two independent `REL32`
locations/targets pass fresh locked MSVC 19.44.35211 i386 full-function
canonical replay. These new methods share the preexisting
`src/WeaponStoneOptionOffsets.cpp` provider with its separately exact 52B
focused and 52B unfocused offset forwarders. Only the genuinely affected
`src/WeaponStoneInfo.hpp` method declarations and source changed. The
previous strict receipt include closure identifies **8 source providers**;
all **39/39 affected strict units** in those **8 cold rebuilt objects**
pass across two serialized reduced-priority batches **23+16**. The original
2,018-byte Bullet collision remains exact. Proof logs are privately
retained at `.analysis/core326-replay-batch{0,1}.log` with sources in
`.analysis/core326-replay-groups.json`; no full cold replay was run.

These two native exact dispatchers are dependencies of the separate
**1,518-byte Player option rebuild parent** `0x004FACA0`, which remains
nonexact at this checkpoint. Their original return/virtual ABIs do not
establish complete Player options resource handling, whole-executable
linkage or runtime equivalence.


## Subsequent CORE/EXACT-369 whole-parent closure

The *separate* complete **1,518-byte** Player option rebuild boss at
0x004FACA0 is now independently **1,518/1,518 native strict exact**,
with all 418 original instructions and 60 independently attested
E8/HIGHLOW references. Any earlier reference in this historical
checkpoint to that parent as still nonexact/open is **superseded**.
This proof's own helper or original function is not double counted.
Read the [new entire Player option rebuild exact proof](PLAYER_OPTION_REBUILD_1518_EXACT_RECONSTRUCTION.md).
