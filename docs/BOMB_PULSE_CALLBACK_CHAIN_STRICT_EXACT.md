# Four whole-native Bomb pulse animation callback and position boundaries

Locked Japanese Steamless TH20's derived Bomb-start vtable at `0x0056FB10`
points to the previously recovered but nonexact 500-byte start routine.
That parent publishes the **same** genuine C callback `0x00478380`
twice at data addresses `+0xE6` and `+0x158`, following two `"pl01"`
AnimationFile spawns. The callback's original complete execution chain is:

| Address | Size | Original native behavior | Exact scoped unit |
| --- | ---: | --- | --- |
| `0x00478380` | 20B | Construct natural stateless delegate and invoke its update member | `bomb_pulse_callback_20` |
| `0x00478610` | 39B | Read `Animation::user_data` at `+0x5C8`, take actual derived Bomb's `spawn_position` at `+0xB8`, pass to relay, return zero | `bomb_pulse_animation_update_39` |
| `0x00450320` | 33B | Pass real Animation receiver/position to `current_animation_pool` global `0x005C0028` | `bomb_pulse_animation_position_relay_33` |
| `0x004502F0` | 40B | Copy all three float components to `Animation::vector_5bc` at `+0x5BC` | `bomb_pulse_animation_pool_position_40` |

The two native REL32 links from `0x00478380` to `0x00478610` and from
`0x00478610` to `0x00450320` are verified as separate physical calls.
The 33-byte relay has one real DIR32 global and a REL32 to the 40-byte
pool method. The final 40-byte method has zero relocation fields.
All four complete original bodies are independently reproduced: **132
disjoint bytes** across the full callback chain, with original runtime
file ownership still explicitly open.

The 20-byte callback uses a genuine stack-resident **empty C++ class**
for its member-call receiver. Its original 20-byte stack frame contains
no security-cookie code. The `/GS /sdl` setting would *add* an extraneous
22 bytes for this local, while a separate pinned source profile
`/GS- /Gy /Zl /Od /Ob0` compiles the correct 20-byte original.
This changes an ordinary compiler switch, not the source semantics:
there is no assembly, dummy padding, copied bytes or artificial NOP.

The other three units compile with the ordinary `/GS /sdl` profile.
Each exact unit is individually cold-compiled and canonical relocation
replayed. The recovered 500-byte parent remains **NONEXACT** and no
extra whole-parent authored-byte credit is claimed.

Scoped canonical replays (four independent cold objects):

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/BombPulseAnimationCallback20.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/BombPulseAnimationUpdate39.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/BombPulseAnimationPositionRelay33.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/BombPulseAnimationPoolPosition40.cpp
```
