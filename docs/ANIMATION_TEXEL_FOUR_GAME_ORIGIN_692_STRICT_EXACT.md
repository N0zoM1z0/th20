# CORE/RECON-1102 — re-attest four WHOLE-EXACT original Renderer texel kernels and correct game-origin attribution

Immutable target: Japanese TH20 Steamless v1.00a executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

This is a **provenance correction, not four new exact code units**.
All four source-backed format-specific texel accumulation kernels were
already accepted as whole-native strict exact in the historical **REF-042**
Sprite review, but their game/compiler/library origins were still marked
`unknown`, so they earned no game-authored byte credit. The independently
recovered whole original [2,745B Renderer alpha-fringe finalizer](ANIMATION_TEXTURE_FINALIZER2745_NATIVE_FRONTIER.md)
now establishes their concrete *game-specific owner and purpose*, instead of
historical speculative standalone texel names. The finalizer itself is still
SOURCE-PRESENT/NONEXACT and gains **zero game-owned exact bytes**.

| Complete original physical kernel | Whole exact original native code and SHA-256 | Actual four E8 in original 2,745B game finalizer |
| --- | --- | --- |
| `0x00451880` BGRA8888 alpha/color neighbor accumulation | **139B/46 i386**, `256e84d8c656400232a00d5e608bd748bbfcbe09642036993da93c0df08eceaa` | `+0x18C`, `+0x1B6`, `+0x1E4`, `+0x215` |
| `0x00451640` ARGB1555 neighbor accumulation | **183B/57 i386**, `2aa5d4dc48a27a2c145a83ee7243f1120ed52e256404d4af72b66c3f1e14d1d6` | `+0x3C3`, `+0x3ED`, `+0x417`, `+0x444` |
| `0x00451700` ARGB4444 neighbor accumulation | **183B/57 i386**, `055a3aa98aff47c9d79add63f2fbd065e9cdbd0056ee64ad91b221b786987f86` | `+0x652`, `+0x67C`, `+0x6A6`, `+0x6D3` |
| `0x004517C0` ARGB8332 neighbor accumulation | **187B/58 i386**, `44ddd8633afe50deac4cef887897e2f3c072ffea4e089b5bcbf8d7a7a0beddd6` | `+0x8E5`, `+0x90F`, `+0x939`, `+0x966` |

All four **entire original function extents are disjoint**, have **zero
native PE HIGHLOW and zero nested E8** within the helpers, and naturally
compile whole-byte-identically from the existing original
[`TextureTexels.cpp`](../src/TextureTexels.cpp) / genuine small packed
[`TextureTexels.hpp`](../src/TextureTexels.hpp) types. They each preserve a
null RGB pointer guard before touching the pixel/count, the real native
alpha-bit/byte check, unsigned component adds and one increment of the
shared sample count. Original little-endian BGRA and 1/4/8-bit packed alpha
and RGB field widths match the native code. The original 2,745B Renderer
main body has **exactly four real original E8 to each of these FOUR
physical function heads**, plus its separate cookie check. No memcpy,
C library algorithm, STL template, or D3DX imported routine implements
these manually specialized four-way alpha-fringe neighbor rules.

## Authorship inference: custom game Renderer code, not compiler/library

The original parent `0x00451910` is a real custom game Renderer
method, reached from the separately WHOLE-EXACT game `0x0044E8F0`
562B D3DX9 texture upload. Each of these four separate native heads
implements a distinct manually expressed, domain-specific transparent
texel color-neighbor accumulator, *solely* invoked in the parent format
scan. They are **bespoke game rendering implementation**, not compiler
scaffolding or unmodified standard-library algorithms. Combined original
control-flow proof now supports upgrading their `function-origins.csv`
from historical `origin=unknown/disposition=review` to
`origin=authored/disposition=authored`, with **`confidence=medium`**:
although game ownership is well supported by the native code shape
and parent, the exact historical source spelling, programmer identity,
and potential private shared-code origin cannot be absolutely proven.
This confidence is recorded explicitly rather than silently declaring
a new native source provenance. Their existing natural C++ body and
original byte-exact source receipts were not changed or re-registered.

The independent read-only
[`verify-animation-texel-four-native-origin.py`](../scripts/verify-animation-texel-four-native-origin.py)
SHA-pins the entire 2,745B/759 original parent and each whole
139B/183B/183B/187B child, verifies the real **16 original physical
E8 site/destination pairs**, complete child instruction/return
boundaries, absence of physical PE relocations in each child, and
rechecks all **four existing** original-native strict receipts.
It also attests the previously accepted 562B upstream game upload
original E8 into the 2,745B parent; the large parent remains NONEXACT.
After **one affected-source cold replay** of the unchanged C++ file:

```text
accumulate_texel1555: exact (183/183 bytes)
accumulate_texel4444: exact (183/183 bytes)
accumulate_texel8332: exact (187/187 bytes)
accumulate_texel8888: exact (139/139 bytes)
Exact replay: 4/4 original units, ONE source object
```

**Accounting:** This adds **zero new strict units and zero newly matched
physical `.text` bytes**, because all four were exact already under
REF-042. It **reclassifies four existing physically distinct whole
functions, totaling 692 original native bytes, as authored-game code**
with medium provenance confidence, increasing the game-authored credit
from 764/260,630B to **768 heads/261,322B** without double-counting
any source or original function. The game parent 2,745B remains
NONEXACT, and the original 562B caller stays independently exact.
No full-project cold replay or changed target was used.

```sh
scripts/repo-python scripts/verify-animation-texel-four-native-origin.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/TextureTexels.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1103 — whole 2,745B Renderer finalizer now native exact

The original game Renderer alpha-fringe finalizer at `0x00451910`
is now [WHOLE STRICT EXACT 2,745/2,745 source-produced game code](ANIMATION_TEXTURE_FINALIZER2745_STRICT_EXACT.md), with independently verified full 2,798B COFF contribution and post-return jump/format tables. The four game-owned
texel helper functions remain independently exact and already
credited, and the upstream 562B original game texture uploader
remains separately exact. Neither existing game function nor the
53B following original data receives duplicate code credit.
