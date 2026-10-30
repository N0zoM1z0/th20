# CORE/RECON-934 — complete 182B solo ribbon group configuration Boss strict exact

> **CORE/RECON-935 update:** The previously separate 123B palette callee
> `0x0045DBF0` is now [independently whole strict exact](ANIMATION_RIBBON_SOLO_PALETTE_123_STRICT_EXACT.md).
> The original 182B parent source and accepted receipt remain unchanged;
> references below to a source-absent palette are historical.


Original Japanese TH20 1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045DB30` is the entire **182B/57-i386** polymorphic
one-segment ribbon configuration Boss, called at physical E8
`0x0045DC96` from the independently exact
[47B solo ribbon wrapper](ANIMATION_RIBBON_SOLO_WRAPPER_47_STRICT_EXACT.md).
This is not a truncated 252B three-segment configuration: its one
native color action is for a single segment at owner offset +8.

## Original physical call graph and game state

[`scripts/verify-animation-ribbon-solo-config182-native.py`](../scripts/verify-animation-ribbon-solo-config182-native.py)
decodes the whole immutable original function through its `ret 8`, checks
**all seven E8 physical sites AND true target addresses**, **zero native
HIGHLOW**, real owner fields and the independent 47B calling instruction:

| Original E8 | Target | Verified native effect |
| --- | --- | --- |
| `+0x2F` | `0x00423520` | Reset Timer at `+0x3CC` |
| `+0x42` | `0x0045D690` | Original whole-exact 23B segment index, actual stride `0x3C0`, index zero |
| `+0x52` | `0x0045DBF0` | Distinct **123B** solo segment palette initializer, not yet independently accepted |
| `+0x67` | `0x0045DD60` | Set Animation world position from config Vector3 |
| `+0x7A` | `0x00450350` | Set Animation layer 11 |
| `+0x96` | `0x00438C60` | Set Animation style values (30,0,255,0) |
| `+0xA9` | `0x0045DD40` | Set Animation flag byte 1 |

Original memory stores owner token `+0x3DC`, control bits
`+0x3C8` read from config `+0x24`, and resets its real Timer
`+0x3CC`. The native packed palette argument is **`0x00FF0000`**.

The natural maintained [`src/AnimationRibbonSoloGroupConfig182.cpp`](../src/AnimationRibbonSoloGroupConfig182.cpp)
uses the **same** `NativeRibbonSoloGroup` class and typed Animation/
Timer API as the independently exact constructor, factory, update and
draw functions. It defines a minimal options view with a genuine
Vector3 at zero and 32-bit control at `+0x24`; unresolved intervening
bytes remain named as such, not inferred gameplay settings.
The 123B palette is an explicitly nominal ABI-only callee view,
not a claimed exact child. No target byte copying, invented instructions,
manual padding or compiler-specific no-op statements are needed.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` generates the exact complete original body
with seven genuine REL32 fields and 154/154 nonrelocated byte matches:

```text
animation_ribbon_solo_group_config_182: exact (182/182 bytes)
Exact replay: 1/1 new unit, 1 cold object
Affected factory/wrapper/config closure: 3/3 strict units, 3 cold objects
```

This adds **one game-authored original whole function /182 native `.text`
bytes**. The distinct 123B palette child is still an independent
reconstruction task; no child exactness is assumed. The complete game
remains unlinked/unplayable. No global cold replay ran.

```bash
scripts/repo-python scripts/verify-animation-ribbon-solo-config182-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSoloGroupConfig182.cpp --source src/AnimationRibbonSoloConfigWrapper47.cpp --source src/AnimationRibbonSoloGroupFactory156.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
