# ScreenInf ten-mode initializer — original 637B native Boss whole exact

The original Japanese TH20 v1.00a Steamless ScreenInf initializer is
`0x00423BF0..0x00423E6C`, exactly **637B / 202 i386 instructions**.
Its full immutable game body SHA-256 is
`7fe3011c872c1e88346d2d995ec8dd21d0ee16e4dcb709fdfa17e135fa9f70b0`.
After the function return is the original three-byte compiler alignment
`0F 1F 00`, followed by the genuine ten-entry/40B mode jump table at
`0x00423E70`. The complete 680B contribution's independent SHA-256 is
`cfb1f3db1be2f16636978929be0ce9eb293aa05c2260ae89484ad032326f19d6`.

`src/ScreenInitialize637.cpp` restores the actual **ten-case `switch`
(0..9)** and typed registration of FunctionChain update callbacks at
priority 24 and mode-dependent draw callbacks at the requested priority.
Mode 3 writes the actual 255 intensity at `ScreenInf+0x18`. After the
mode-specific registration, the initializer sets its real update-node
shutdown callback (`0x00425070`), zero-assigns the native `Timer` at
`+0x30` with the actual `Timer::operator=(int)` destination `0x00423520`,
and retains the native mode plus four scalar inputs at offsets
`+0x10`, `+0x1C`, `+0x20`, `+0x24`, and `+0x28`.

`src/NativeScreenEffect.hpp` uses the **existing 16B TaskInfo base**,
actual FunctionChain nodes at +0x08/+0x0C, the true 16B Timer and
observed scalar/view fields. Total original ScreenInf storage is
`0x44` bytes. No invented padding, shadow scheduler, naked function,
assembly, byte array or artificial code-size shaper is used.

## Original switch control-flow recovery

The initial natural C++ case-ordered switch compiled to 636B body,
plus 40B switch pointers. It had all **20 real E8 and 20 body data
roles** but was one byte shorter before the table and structurally
mismatched. Original native i386 has a short unsigned range branch to a
**separate default-case jump** physically before case zero. Putting the
semantically real `default: break;` **before** `case 0` in the C++
switch naturally restores that exact two-branch control flow. MSVC
therefore emits the original 637B body, the real 3B alignment, and the
40B compiler-generated jump table, without adding any inert instructions.

## Complete cold canonical proof

`scripts/verify-screen-init637-native.py` separately attests the
immutable native body, physical **20 E8 site/destination pairs**,
**30 original PE HIGHLOW fields** (20 in-body callback/table pointers
and the ten local switch labels), alignment, true table targets, and
all compiler COFF fields. It reports 480/480 comparable ordinary bytes.
The match-unit `screen_init_boss_637` then cold-compiles the maintained
source using pinned MSVC 19.44 C++20 and replays every relocation using
the independently enumerated original target identities.

**Result: exact (637/637 authored body coverage; 680/680 complete
comparison, including 30 HIGHLOW/DIR32 and 20 E8/REL32 fields), 1/1
new unit and one cold object.** The 43B alignment/table extension is
not credited as additional authored game *code*. The original
81B ScreenInf allocation factory and its larger animation/update
callbacks are distinct boundaries and receive no credit from this Boss.

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/ScreenInitialize637.cpp
scripts/repo-python scripts/verify-screen-init637-native.py
```
