# CORE/RECON-851 — complete original 534B Animation strip mode11 renderer strict exact

The locked Japanese TH20 v1.00a Steamless original PE (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains the full game-authored **534B/159-i386** Animation strip draw
method at original physical `0x00445130`. It has native frame `0x3C`,
one renderer ECX receiver, three stack arguments (`Animation*`, vertex
pointer, vertex count) and native `ret 0xC`. Its larger, still-NONEXACT
5,993B Animation Draw dispatcher calls it at actual original E8
`0x00443B28`.

One new natural maintained
[`src/AnimationDrawStripMode11.cpp`](../src/AnimationDrawStripMode11.cpp)
now strictly reproduces **534/534 bytes of the entire original function**
under the pinned MSVC x86 C++20 profile, with all original 10 E8
call-site/destinations and six PE HIGHLOW physical global sites exact.
There is no copied original machine code, shortened prefix, manual NOP or
fabricated extra renderer allocation.

## Original-only PE evidence and semantics

[`scripts/verify-animation-strip-mode11-native.py`](../scripts/verify-animation-strip-mode11-native.py)
independently reads the locked original native `.text` and original PE
`.reloc`, verifies 159 complete real i386 instruction heads, frame0x3C,
`ret 0xC`, **10 exact E8 physical site/target pairs**, and six genuine
PE HIGHLOW fields all resolving to the live Graphics owner
`0x005C4D40`. This source-independent evidence also confirms the real
5,993B parent original call site.

The original Mode11 path rejects counts below three, flushes pending
AnimationPool primitive draws, and checks the genuine Animation flag
bit21. On the first needed update it marks bit21 and applies receiver
`+0xD0/+0xD4` XY offsets to the submitted **28B-stride SpriteTexturedVertex**
stream via its real seven-float record layout, once per vertex. It then
uses actual FVF `0x144` when the state cache at receiver
`+0x6000E0E` differs from three, invokes original
`prepare_texture_states` at `0x00445BA0`, obtains actual Animation
sprite/texture data (`0x00437CD0/0x00445A00`), updates the live texture
cache `+0x6000E08`, calls the independently exact Graphics depth-write
disable at `0x004DDF80`, restores original D3D9 stage-state values
`(0,6,0)` and `(0,3,0)` if the cache differs from one, and issues the
native `DrawPrimitiveUP` call with triangle fan, original count-minus-two,
real supplied stream and `0x1C` vertex stride.

The original ten E8 call destinations and multiplicities are independently
attested: one AnimationPool flush `0x004455C0`, five real Graphics
`get_device` `0x00412730`, original `prepare_texture_states` `0x00445BA0`,
`Animation::sprite_data` `0x00437CD0`, renderer texture resolution
`0x00445A00`, and depth disable `0x004DDF80`. Six real HIGHLOW references
are all original Graphics global `0x005C4D40` at native offsets
`+0xC4/+0x12C/+0x16A/+0x184/+0x1AC/+0x1DE`.

## Strict canonical result and counted native progress

One actual pinned source object `build/core851-canonical/AnimationDrawStripMode11.obj`
backs exactly one `animation_strip_mode11_534` unit in
[`config/match-units.toml`](../config/match-units.toml). Its entire
**470/470 original non-relocation bytes** and all 16 actual real COFF
symbol/type/offset/destination roles match the original PE, so the
fresh strict canonical build/receipt and full original relocation replay
report:

```text
animation_strip_mode11_534: exact (534/534 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This adds **one original game-authored exact function, 534 native code
bytes**, one distinct source mapping, one strict match unit and one
canonical compiler provider. Existing exact Mesh, Mode6/7/8, quad and
Graphics functions receive no duplicate code credit. Current authored
strict totals become **605 whole original functions /210,981 original
`.text` bytes**, with **1,251 source-present mappings /1,252 strict
units /270 providers**. The 5,993B main Draw parent remains distinct
**SOURCE-PRESENT/NONEXACT**.

Only the one newly added source is cold-built and replayed; no previously
accepted exact source/header/profile changed, and **no full graph cold
replay** was performed.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-strip-mode11-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawStripMode11.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
