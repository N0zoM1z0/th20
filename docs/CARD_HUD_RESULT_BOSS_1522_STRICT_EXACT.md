# CORE/RECON-1004 — complete 1,522B Card HUD bonus/result dispatcher strictly exact

Target: immutable Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The actual game-owned result HUD routine at `0x004B90E0` is now fully
reconstructed as natural C++20, with **1,522 original bytes /416 original
i386 instructions** strictly identical after a pinned MSVC 19.44 build.
Its complete source is
[`src/CardHudResult1522.cpp`](../src/CardHudResult1522.cpp), implementing
`NativeCardHudView::report_spell_result_4b90e0(mode,score)` on a genuine
borrowed non-owning UI owner view. The entire independently accepted
**602B `Card::finish_spell`** at `0x004878B0` calls this Boss at **two
real E8 offsets `+0xD0/+0x235`**; no inferred transitive or duplicate
credit is needed.

## Whole original physical extent — code, padding, real pointer table

[`scripts/verify-card-hud-result1522-native.py`](../scripts/verify-card-hud-result1522-native.py)
SHA-pins the complete original code (`af638942de7619ec46f71a2adafdea6b612ead352799a29d91a27ee9d650aaa0`)
from the locked PE and independently proves **all 51 native E8 instruction
positions/actual destinations and 12 genuine in-body PE HIGHLOW fields**.
The original ends with `ret 8` at 1,522B; there are then **two actual
`66 90` alignment bytes**, followed by the **seven four-byte direct
switch case pointers** at `0x004B96D4`. The table points to genuine
code addresses `0x004B9106`, `0x004B9414`, `0x004B94D2`, `0x004B9553`,
`0x004B95D3`, `0x004B96CC`, and `0x004B9651`.

All **seven table pointer words** have their own actual PE HIGHLOW entries,
so the authentic whole compiler contribution is **1,552B**: 1,522B game
source code +2B compiler alignment +28B compiler switch data. It has
**51 REL32 +19 DIR32 =70 independently documented relocations**; the
body references the pointer-table base at the genuine original `+0x22`.
These 30 extra bytes are **not** counted as game-authored executable code,
and the 7-entry table is not compressed into a fake byte selector. All
source comparisons preserve the entire contribution with `size = 1522`
and `compare_size = 1552`, not a truncated or padded prefix.

Original direct-call role histogram, checked from immutable physical E8s:

| Native callee | Calls | Actual role |
| --- | ---: | --- |
| `0x00414580` | 23 | original two-element and ten-element AnimationHandle array indices |
| `0x00450C70` | 11 | genuine AnimationFile name/script spawn helper |
| `0x0044FCD0` | 9 | actual AnimationHandle retire method |
| `0x00437950` | 3 | active Renderer AnimationFile accessor |
| `0x0044BD70` | 3 | original digit/display state update |
| `0x00450120` / `0x0044FA30` | 1 each | original leading-digit hide and show paths |

## Recovered complete game behavior and source-level corrections

The original `mode` selects six meaningful cases: 0 (spell bonus
success, full 8-digit display), 1 (failed spell result), 2/3/4
(alternate result animations) and 6 (another result variant), plus
one default/switch entry. The game retains the HUD's real two borrowed
AnimationHandle slots at `+0xBC` and ten independent digit slots at
`+0x94`, plus its live AnimationFile pointer at `+0x2CC`. Mode 0
retires and restarts `front` script `0x31`, iterates the real eight
score digits with signed division and leading-zero visibility, and
conditionally displays special scripts `0x0C` and `0x0D`. The other
modes select the genuine `front` script `0x32..0x36`, as visible in the
original. Success/failure cases also publish result state at `+0x138`
and script `0x54` at `+0x114`.

Two earlier *plausible but wrong* source hypotheses were tested against
actual native machine code instead of accepted from prior notes:

1. Caching all three owner references (`two`, `digits`, and `file`) at
   method entry compiled to only **1,076B** (including a generated
   seven-entry switch table). The original repeatedly evaluates the
   true receiver/AnimationFile/array locations across calls. Restoring
   the actual live reads yields the authentic **1,552B** contribution,
   all **51 exact native E8 sites** and every one of the **19 original
   HIGHLOW positions**.
2. Code written as `score > 999999` and `score > 999` generated a
   **full-length** and otherwise structural-exact candidate, but with
   **four different original instruction bytes**. The original source
   uses *inclusive* `score >= 1000000` and `score >= 1000` comparisons
   (`jl` instead of `jle` and their actual immediate operands).
   Restoring these meaningful numeric thresholds reproduces the
   original four bytes. No fake stack local, volatile, dead branch,
   assembly, manual opcode, or artificial linker padding is involved.

The final whole-function structural score is **1,272/1,272 original
non-relocated contribution bytes**, plus all **70 field positions,
types, symbols and independently anchored original destination roles**.
The `card_hud_spell_result_boss_1522` canonical unit then successfully
replays every original comparison byte, including the exact real
compiler-provided padding and all seven jump-table words:

```text
card_hud_spell_result_boss_1522: exact (1522/1522 coverage bytes; 1552/1552 compared bytes)
Exact replay: 1/1 units, 1 cold objects
PASS immutable 1,522B/416 original Card HUD Boss, 51 E8/12 body HIGHLOW
PASS original 2B alignment, 7 switch pointer HIGHLOW, and both 602B parent calls
```

## Credit, limits and bounded reproduction

This checkpoint adds **one new complete game-authored head /1,522
original `.text` bytes** and one canonical source/receipt object.
Previously accepted 602B Card finish, 71B/22B HUD finish/VM bridge,
AnimationFile spawn, and folded array index functions remain unaffected
and are **not** credited again. The narrow HUD, glyph and renderer
views only describe observed receiver ABIs, not original whole-class
layouts. The original 1,896B Card start Boss, 39,470B Animation VM,
Renderer resource ownership, full game linking and runtime behavior
remain independently unresolved. No project-wide cold replay was run.

```sh
scripts/repo-python scripts/verify-card-hud-result1522-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardHudResult1522.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1005 — real 20-byte borrowed file getter now exact

The three original `0x00437950` calls in the 1,522B HUD Boss now have a
[separately accepted whole 20B/9-i386 source unit](CARD_HUD_FILE_GETTER20_STRICT_EXACT.md)
in the **same** canonical C++ provider. The parent still replays its
complete 1,552B contribution; the generic getter retains uncertain
original source ownership and does not add authored-game byte credit.
