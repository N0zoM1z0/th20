# Animation::world_position_for_spawn — complete 236B native reconstruction

Locked Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0044CB80` is a complete game-authored **236B/77-i386**
`Animation` recursive world-position method. It returns a composed
`Vector3` by reference and recurses through the real `parent_558` without
adding viewport/window scaling. Its caller graph includes the original
`0x004512B0` recursive animation-spawn path.

## Original native behavior

The method composes `vector_5bc + base.vector_2c + base.vector_484` in that
order. It recurses only if a real parent exists and native
`base.flags.word_04` bit 12 is clear. If bit 5 is set, it rotates the result's
XY lanes by the parent's rotation Z, then recursively adds the parent's
world position. It does not apply unrelated viewport scaling or parent
scale. Parent-cycle policy is outside this source reconstruction.

## Whole-function proof

`scripts/verify-animation-world-position-for-spawn236-native.py` pins the
whole original body SHA-256
`390a97772793da5a55b5398aa28a11db73e87c9c5af50fc2ba70e94c07eb6dc8`,
all **77/77** i386 instructions through `ret 4`, eight native E8 sites and
their physical destinations, the single original security-cookie HIGHLOW
`+0x07 -> 0x005B25C0`, and the recursive self-call at `+0xC7`.

The natural C++ member now lives on the actual `Animation` class in
`src/AnimationWorldPositionForSpawn236.cpp`; no derived ABI view or extra
object storage is used. Pinned MSVC 19.44 x86 C++20 emits the complete
**236B** body: **200/200 ordinary bytes** and **36/36 relocation bytes**
match, with zero ordinary-byte differences and all nine relocations solving
to the original destinations. The canonical unit retains its existing
physical identity `animation_raw_world_position_236` and replays separately
from the rest of the cold graph.

The method is now also the natural parent-position dependency for the
619B recursive AnimationFile child-spawn reconstruction at `0x004512B0`.
The original 39,470B Animation VM remains a separate NONEXACT parent.

```bash
scripts/repo-python scripts/probe-animation-world-position-for-spawn236.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationWorldPositionForSpawn236.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
