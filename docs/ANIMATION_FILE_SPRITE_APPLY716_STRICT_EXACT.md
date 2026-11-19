# AnimationFile::apply_sprite — complete 716B native reconstruction

The original TH20 v1.00a Steamless executable is SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its complete `0x00438620` body is **716 bytes / 179 i386 instructions**,
with a `__thiscall` receiver, explicit `Animation*` and sprite-index
arguments, and `ret 8`. The original whole-body SHA-256 is
`588b789deec72290b8fd75c577751531b00f231ad30f890a8d8c032ca69bf860`.

## Recovered ownership and callers

The receiver is the actual `AnimationFile`, not a derived ABI surrogate and
not the destination Animation. Its loaded-byte sentinel is
`AnimationFile+0x3C`; its `SpriteData*` array is at `+0x50`, and each native
sprite record is **0x58 bytes**. The existing exact
`AnimationFile::sprite` accessor at `0x00437C80` is the single original E8
callee. The public `AnimationFile` declaration now owns the method directly;
no data member or object layout was added.

The function is called directly by the original 39,470B Animation VM
(`0x0042B5D0`), by the 29B `0x0044BD50` wrapper, and by the 56B
`0x004708E0` setup path. The latter resets an Animation, copies the file
identity into Animation+0x1C, and then applies the selected sprite. These
original consumers establish the game-owned AnimationFile protocol; the
39,470B VM itself remains a separate NONEXACT parent.

## Exact behavior

1. Return `-1` without touching the Animation if `AnimationFile::bytes`
   is null.
2. Store the selected sprite index at `AnimationBase+0x20` and retrieve
   `sprites[index]` through the original `AnimationFile::sprite` method.
3. Fill the four UV corners in native order:
   - `vectors_378[0] = (u0, v0)`
   - `vectors_378[1] = (u1, v0)`
   - `vectors_378[2] = (u0, v1)`
   - `vectors_378[3] = (u1, v1)`
4. Store `(u1-u0, v1-v0)` in `vector_398` and the source-scaled width/height
   (`extent_4c`, `extent_48`) in `vector_70`.
5. Copy the original identity matrix into `matrix_3b8` and `matrix_3f8`.
   Scale the first matrix's diagonal by the native 256.0 constant; scale
   the second by the SpriteData texture extents and scale factors.
6. Copy `matrix_3b8` into the Animation's `matrix_57c` and convert the
   four source rectangle edges with the original signed float-to-int
   truncation into `+0x3A8..+0x3B4`.
7. Return zero.

The natural member implementation is `src/AnimationFileSpriteApply.cpp`.
The x86 `AnimationFile` owner asserts the original offsets of `bytes`
(`+0x3C`) and `sprites` (`+0x50`), in addition to its existing 0x70-byte
size assertion.

## Whole-function proof

The independent original PE parser pins the whole 716B SHA and decodes all
**179/179** instructions through the final `ret 8`. It independently
recovers one original E8 at `+0x2C -> 0x00437C80` and four physical PE
HIGHLOW fields:

| Offset | Original destination | Role |
|---:|---:|---|
| `+0x17E` | `0x0056E068` | identity matrix |
| `+0x193` | `0x0056E068` | identity matrix |
| `+0x1A5` | `0x0056CDA0` | native 256.0 |
| `+0x1D4` | `0x0056CDA0` | native 256.0 |

Pinned MSVC 19.44 x86 C++20 emits the complete **716B** member function
from natural source. The canonical comparison reports **696/696 ordinary
bytes** and all **20/20 relocation bytes** exact, with zero ordinary-byte
differences. The candidate's five relocations solve to the same original
destinations and offsets. The focused verifier is
`scripts/verify-animation-file-sprite-apply716-native.py`; the standalone
probe is `scripts/probe-animation-file-sprite-apply716.py`. The canonical
unit is `animation_file_apply_sprite` and is replayed independently of the
rest of the cold graph.

This is a real 716B AnimationFile state-application method, not a getter,
synthetic wrapper, assembly stub, or padding contribution. Its exactness
does not grant any byte credit to the 39,470B Animation VM parent.
