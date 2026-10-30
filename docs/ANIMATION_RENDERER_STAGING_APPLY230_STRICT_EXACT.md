# CORE/RECON-984 — original complete 230B Renderer third-list staged draw/owner-count application strict exact

Immutable Japanese TH20 Steamless v1.00a original executable SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The true game-owned `0x00449FA0` is a complete **230B/69-i386**
Renderer third-list application function. Two real original E8 sites
`0x00449EFC` and `0x00449F5C` in the independently strict-exact
[347B Renderer classification dispatch](ANIMATION_RENDERER_CLASSIFY_DISPATCH347_STRICT_EXACT.md)
call it after the corresponding [382B/394B classification](ANIMATION_RENDERER_CLASSIFY382394_STRICT_EXACT.md).
This method enumerates the actual 24-byte staging list at Renderer
`+0x30`, retrieves each Animation through the genuine
`IntrusiveIterator` and `IntrusiveLink::node_access`, invokes the original
separate **5,993B `AnimationPoolOwner::draw`** at physical
`0x00443880`, then increments the original global pool counter
`AnimationPoolOwner+0xD8`. That enormous 5,993B drawing Boss remains
**source-present but NONEXACT** and cannot inherit credit from this caller.

## Independent original PE proof

[`scripts/verify-animation-renderer-staging-apply230-native.py`](../scripts/verify-animation-renderer-staging-apply230-native.py)
checks every original executable byte, 69 complete instructions and
real `ret`, **all 10 E8 instruction offsets and their actual PE targets**,
**all five original PE HIGHLOW locations**, third-list original offset,
owner counter layout and both physical 347B parent calls.

| Original native code/relocation | Actual original target and role |
| --- | --- |
| E8 `+0x39/+0x45/+0x54` | `0x0040C080 / 0x00412280 / 0x00412540`, authentic iterator auto-init and list begin/end |
| E8 `+0x61/+0x6E/+0x7D/+0x88` | `0x00411C30 / 0x00411BB0 / 0x0040C300 / 0x0040F160`, true iterator advance/condition/get/node accessor |
| E8 `+0x9C` | `0x00443880` — separate **5,993B original Animation draw NONEXACT**, not a 230B inlined operation |
| E8 `+0xC7/+0xDD` | `0x00411B00 / 0x005429EE`, actual iterator destruction and cookie check |
| HIGHLOW `+0x06/+0x15` | `0x0056838D / 0x005B25C0`, genuine MSVC EH handler and cookie |
| HIGHLOW `+0x98/+0xA2/+0xB1` | **three real loads of global `0x005C0028`**, both read and write sides of original `+0xD8` pool counter increment |

The source [`src/AnimationRendererStagingApply230.cpp`](../src/AnimationRendererStagingApply230.cpp)
uses the maintained single
[`NativeRendererClassificationView`](../src/NativeRendererClassificationView.hpp)
type, two genuine already-accepted `AnimationPoolOwner`/`Animation`
interfaces, and natural C++20 iterator lifetime. The `+0xD8`
read-modify-write deliberately fetches the actual global pool pointer
twice, rather than caching a synthetic field and incorrectly reducing
the original HIGHLOW count. This generated **all original 230B/69
instructions and 170/170 matching nonrelocated bytes**, with all 15
physical relocation fields bound to the real original PE destinations
under pinned MSVC 19.44 C++20 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`.

Strict original-target-bound **affected-only** cold replay, including
all three closely coupled already exact Renderer classification units:

```text
animation_renderer_staging_apply_230: exact (230/230 bytes)
animation_renderer_classification_dispatch_347: exact (347/347 bytes)
animation_renderer_classify_primary_382: exact (382/382 bytes)
animation_renderer_classify_secondary_394: exact (394/394 bytes)
Exact replay: 4/4 units, 3 cold objects
```

This adds **one distinct game-authored head/+230 unique original `.text`
bytes**. The already credited 347B/382B/394B parents and their folded
iterator/callback helper code are not credited again. The 806B
classification action, 5,993B draw Boss, 508B/511B active-list
update and 39,470B Animation VM remain separate unfinished code.
No project-wide cold replay and no whole-game linking/playability claim.

```bash
scripts/repo-python scripts/verify-animation-renderer-staging-apply230-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererStagingApply230.cpp --source src/AnimationRendererClassifyDispatch347.cpp --source src/AnimationRendererClassification382394.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
