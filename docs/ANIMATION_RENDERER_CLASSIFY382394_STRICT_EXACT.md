# CORE/RECON-982 — both original 382B/394B Renderer Animation classification Bosses whole strict exact

Immutable Japanese TH20 Steamless v1.00a original executable SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Two full original game-authored Renderer classification methods are now
complete **whole-function strict exact**:

| Native original | Source behavior | Exact native size |
| --- | --- | --- |
| `0x0044A090` **382B/114-i386** | Traverse actual primary list at Renderer `+0x00`; map layer indices **46..53 → 29..36**, special **45 → 26**, and compare the requested identifier | **382/382** |
| `0x0044A210` **394B/117-i386** | Traverse actual secondary list at Renderer `+0x18`; map layer indices **29..36 → 46..53**, special **26 → 45**, otherwise **47**, and compare identifier | **394/394** |

Both return the actual number of matching live Animations. They clear
and reinitialize the real third **24B IntrusiveList** at Renderer
`+0x30`, only examine Animations whose native `+0x570` retirement
state is zero, read the layer code from `AnimationBase::field_14`,
then initialize the matching Animation's true `link_500` at
`Animation+0x500` and append the link to the third list. These are
meaningful Renderer list ownership/publication operations, not
replacements for the 508B/511B update loops.

## Immutable original PE, real callers and exact relocations

[`scripts/verify-animation-renderer-classification382394-native.py`](../scripts/verify-animation-renderer-classification382394-native.py)
independently validates every original 382B and 394B executable
byte using full-body SHA-256 hashes
`f082fc24af310a6bc549544c7d0b85d838e2a5464ba3601f5da71f304cc993e7`
and
`ff1c8467dbc1284fd69c55f09cdf62168f395e54f6bc4d57b9825522ecf918f1`,
the entire 114/117 x86 instruction boundaries and genuine `ret 4`,
all **16 original E8 site/physical target pairs plus 2 genuine PE
HIGHLOW fields per method**, and the true `INT3` trailing alignment.
The two HIGHLOW sites each are original exception handler
`+0x06 -> 0x005683CD` and cookie `+0x15 -> 0x005B25C0`.
The original parent **347B** Renderer selection method `0x00449E40`
physically calls both whole new functions at **`0x00449EC5`** and
**`0x00449F24`**. That parent remains separately **NONEXACT**.

The physical original E8 family includes real `0x0044A640` staging
reset, `0x0040C080` iterator auto-initialization, original
begin/end/advance/differs/get helpers, **five** genuine
`0x0040F160` `node_access` references, original `0x0044A670`
`IntrusiveLink::initialize`, real **57B** `0x00411EA0` staged
append, iterator destructor and security-cookie verifier. No
separate physical helper head is double-credited.

## Exact source expression ordering

[`src/NativeRendererClassificationView.hpp`](../src/NativeRendererClassificationView.hpp)
shares the *actual* previously accepted two-list
`NativeSpawnRendererView`, adding a non-owning third 24B list at the
original `+0x30` offset, not a fake 96MiB pool allocation.
[`src/AnimationRendererClassification382394.cpp`](../src/AnimationRendererClassification382394.cpp)
reconstructs the two natural C++20 `int`-returning source functions.

Their first compiler probes were **already exactly 382B/114** and
**394B/117**, but did **not** match the original instruction semantics:
21 nonrelocated bytes differed in each due to storing a temporary
`Animation*` before `link_500.initialize`. The correct natural
source-level nested expression
`link->node_access()->link_500.initialize(link->node_access())`
retains the original **two separate native node-access calls**,
calculates the receiver's `+0x500` field first, then obtains the
argument from the second call, and naturally emits the original
register/stack ordering. It produces **310/310** and **322/322**
matching nonrelocation bytes respectively, with every genuine
original PE-target-bound relocation. No manual assembly, dummy NOP,
target byte patch or shortened function interval.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` original-target-bound local replay:

```text
animation_renderer_classify_primary_382: exact (382/382 bytes)
animation_renderer_classify_secondary_394: exact (394/394 bytes)
Exact replay: 2/2 units, 1 cold object
```

This adds **two original game-authored heads /776 unique native `.text`
bytes**. The prior native list/iterator/append helpers are not counted
again. The 347B parent, 508B/511B Animation update loops, 2,884B
particle Update and 39,470B Animation VM remain separate unfinished
work, with no whole-game build/link/playability claim.
No full-graph cold replay occurred.

```bash
scripts/repo-python scripts/verify-animation-renderer-classification382394-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererClassification382394.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
