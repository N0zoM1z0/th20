# CORE/RECON-922 — complete 252B ribbon group configuration Boss strictly exact

> **CORE/RECON-923 follow-up:** The original 88B segment palette child
> and both 31B forwarding wrappers are now [independently whole strict
> exact](ANIMATION_RIBBON_PALETTE_88_31_STRICT_EXACT.md). This does not
> change the previously accepted 252B canonical object or receipt.

Locked Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045EB10` is **252B /77-i386** of genuine
polymorphic ribbon-group gameplay/configuration logic, called by the
[whole-exact 47B allocation wrapper](ANIMATION_RIBBON_CONFIG_WRAPPER_47_STRICT_EXACT.md)
at physical E8 `0x0045EC96`.

## Complete original PE role census

[`scripts/verify-animation-ribbon-group-config252-native.py`](../scripts/verify-animation-ribbon-group-config252-native.py)
independently authenticates all 252 original bytes, the return `ret 8`,
all **11 actual E8 call sites and destinations**, and **zero** physical
in-body HIGHLOW fields. The original function saves the passed token at
`+0xB5C`, copies the option word at `+0x24` into the group's `+0xB48`
control field, resets Timer at `+0xB4C`, initializes three separate
segment palettes, and updates the attached Animation:

| Original E8 offsets | Native destinations and meaning |
| --- | --- |
| `+0x2F` | `0x00423520` Timer assignment zero |
| `+0x42`, `+0x65`, `+0x88` | `0x0045D690` genuine [23B 0x3C0-stride array indexing](ANIMATION_RIBBON_SEGMENT_AT23_STRICT_EXACT.md) for segments 0/1/2 |
| `+0x52`, `+0x75`, `+0x98` | `0x0045EC10` separate **88B** ribbon segment palette setup (still a distinct reconstruction target) |
| `+0xAD` | `0x0045DD60` Animation position assignment |
| `+0xC0` | `0x00450350` Animation layer selection (layer 11) |
| `+0xDC` | `0x00438C60` Animation mode setup (30,0,255,0) |
| `+0xEF` | `0x0045DD40` Animation flag-byte setter (value 1) |

The actual game-specific palette values are `0xFFFF4040`, `0xFFC040FF`
and `0xFFFFFF40` in this order, not an assumed generic palette.

## Natural source, full relocated-byte acceptance and scope

[`src/AnimationRibbonGroupConfig252.cpp`](../src/AnimationRibbonGroupConfig252.cpp)
models the real `NativeRibbonGroupOptions` at `+0x24`, uses the
same canonical pointer-bearing token field and actual 3×0x3C0
segment array, then calls existing Animation methods. Its natural
`NativeRibbonSegmentArray::at_45d690` child is independently
**23/23 strict exact**; the still-separate 88B palette method is not
credited merely because this caller matches.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` emits **all 252 original relocated
machine bytes**, with real original E8 site/target roles:

```text
animation_ribbon_group_config_252: exact (252/252 bytes)
animation_ribbon_segment_at_23: exact (23/23 bytes)
Exact replay: 2/2 units, 2 cold objects
```

The newly accepted **252B whole original group configuration** earns
one authored-game exact head and **+252 unique `.text` bytes**. The
23B indexed helper remains `origin=unknown/review` and adds no authored
code credit. The shared class header change preserved the exactness of
all **12 previously accepted affected ribbon units** across ten
other cold objects. No unfiltered whole-graph cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-ribbon-group-config252-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonGroupConfig252.cpp --source src/AnimationRibbonSegmentAt23.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
