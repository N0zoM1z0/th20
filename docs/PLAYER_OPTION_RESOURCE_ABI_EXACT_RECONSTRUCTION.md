# CORE/EXACT-330 — complete AnimationFile non-spatial flag-2 spawn and Player file accessor

Locked comparison target is Japanese TH20 v1.00a Steamless, original SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint closes **two complete original function boundaries, 74 original
native bytes**, both in the still-open 1,518-byte
`Player::rebuild_option_animations` call graph (`0x004FACA0`).

| Whole native method | Original entry | Bytes | Original interval SHA-256 |
| --- | --- | ---: | --- |
| `AnimationFile::spawn_flag2` | `0x0049CBF0` | **57** | `11ffc26ea66275092b11cc14a10e27e19831276446c7e2d15f6dd18d4fbd133d` |
| `Player::animation_file_ref` | `0x00421810` | **17** | `55b6e58404a3e0e3a48be30a93afd471c029dbaec0b52893db79c4f37241b821` |

The **57-byte** native `AnimationFile` wrapper owns the original i386
`__thiscall` aggregate return convention, with a hidden four-byte
`AnimationHandle` return buffer, `const char* expected_stem`, signed script
index, draw layer and optional `Animation**`. It calls the full seven-argument
Renderer/Animation-file spawn **once**, with *original native* null position,
zero floating rotation, flag value **2**, and preserved expected stem,
script index, draw layer, output and return buffer. The complete original
single `REL32` relocation at **`+0x2C`** targets the independently observed
`0x00450CB0` full-spawn implementation. Original and compiler-generated
caller prologues, `xorps` zero load, 57 bytes, relocation and `ret 0x14`
all strictly match. The initial manifest-probe field guess at `+0x1D` was
rejected and corrected from the **original E8 displacement**, not inferred
from the bytes being compared.

This method is naturally authored in the same existing owner source
`src/MeshResourceAccess.cpp` as the previously accepted AnimationFile
wrappers, not invented as a standalone game engine. The correct native
5-parameter wrapper is distinct from calling the 7-parameter spawn directly,
a difference that matters when rebuilding the whole 1,518-byte Player parent.

The **17-byte** original `Player::animation_file_ref() const` returns the
actual typed `Player::animation_file` pointer at `Player+0x1C` in `EAX`,
without another conversion or dispatch. It is naturally authored in the
existing `src/Player.cpp` object and returns the real `AnimationFile*`.

## Strict scoped replay (no unfiltered graph build)

The two original functions match **57/57 and 17/17 bytes** in canonical
objects using each existing owner source's own exact MSVC x86 profile.
The 57-byte wrapper uses its provider's existing C++17 `/fp:strict` setup;
the 17-byte accessor uses the Player provider's C++20 `/fp:precise` profile.
Neither compiler profile was silently changed to force matching.

Only `src/AnimationFile.hpp` and `src/Player.hpp` changed besides the two
already owned source implementations. Fresh previous receipt include-closure
analysis selected exactly **49 affected source providers**, with **230
previously exact canonical units** plus **two new exact functions**.
All **232/232 affected strict units in 49 cold objects** passed in ten
serial, reduced-priority batches of **63+8+7+34+22+31+32+10+12+13**.
Proof sources and logs:
`.analysis/core330-replay-groups.json`,
`.analysis/core330-replay-batch{0..9}.log`.

Twelve compiler-private MSVC `$SG` string labels in eight previous units
renumbered after header declaration changes; their original relocation
positions/types, independently grounded native string addresses, complete
non-relocation bytes and object receipts remained unchanged. Every identity
was reconciled under the strict original-oracle rules before final full-unit
replay. See ignored `.analysis/core330-reconciled-private-symbols.json`.
There was **no unfiltered full cold replay**, and no change to the immutable
target, Ghidra database or previous original function ranges.

These new exact ABI edges are useful for the **entire** Player option rebuild
boss, but do **not** make the 1,518-byte caller, its AnimationHandle lifetime
or full-game linker/runtime state exact.


## Subsequent CORE/EXACT-369 whole-parent closure

The *separate* complete **1,518-byte** Player option rebuild boss at
0x004FACA0 is now independently **1,518/1,518 native strict exact**,
with all 418 original instructions and 60 independently attested
E8/HIGHLOW references. Any earlier reference in this historical
checkpoint to that parent as still nonexact/open is **superseded**.
This proof's own helper or original function is not double counted.
Read the [new entire Player option rebuild exact proof](PLAYER_OPTION_REBUILD_1518_EXACT_RECONSTRUCTION.md).
