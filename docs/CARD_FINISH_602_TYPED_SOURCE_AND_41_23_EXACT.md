# CORE/RECON-1000 — original 602B Card::finish_spell complete typed source, and 41B/23B exact caller leaves

The target is Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## Entire 602-byte original, without shortened acceptance extents

The original `Card::finish_spell` at `0x004878B0..0x00487B09` is an authored
game function of **602 bytes /172 i386 instructions**, SHA-256
`17601f659a19106028345e6ea7349827979a354946d8f728d56cd3a12b08003f`.
[`verify-card-finish602-native.py`](../scripts/verify-card-finish602-native.py)
reads the immutable PE and verifies **every one of its 26 E8 locations and
physical destinations** as well as the **13 authentic PE HIGHLOW sites**.
It checks the whole body through the original `ret`, not a target-sized prefix
of an unrelated generated object.

The complete maintained algorithm in
[`src/CardFinishSpell602.cpp`](../src/CardFinishSpell602.cpp) uses the genuine
`Card` (`0xC8`) owner and typed, non-owning dependencies in
[`src/NativeCardFinishViews.hpp`](../src/NativeCardFinishViews.hpp):

- An inactive Card returns immediately without changing its resources.
- The active path marks a UI owner dirty; cancels all three info handles;
  clears the active bit; retires the background handle; clears bit 5;
  clears the UI effects; then retires the Card effect handle.
- On a missed capture it requests the distinct UI miss path. On capture it
  credits the true Session score, reports the capture bonus, and—unless the
  play-state flag at `+0x10` indicates pause—updates both primary and secondary
  spell record groups using real `0xE0`-stride entries.
- The update stores the original capped counter and scans **all 113** spell
  records for nonzero `+0xC0` or `+0xC4` counters; completion raises the
  achievement `0x28`. It then requests sound `0x2E` on capture or the UI
  miss report on failure. The independent Card `+0x78` bit-7 predicate
  triggers the extra `0x45` sound request.

This is a **complete behavioral C++ reconstruction candidate, NONEXACT**.
Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` generates a **577-byte complete body versus the immutable
original 602 bytes**. It has the expected **26 call relocations plus 13 data
relocations** (39 total), but differs in evaluation order, index locals,
member-operand addressing, branch CFG and frame allocation. In particular,
the original first checks Card bit0 **inline**, then tests bit1 using a
shift and AND. Initial natural source attempts calling `Card::active()`
emitted an original-absent E8 and compiled to 582B; source was corrected to
actual native bit behavior. The remaining 25-byte discrepancy is **not**
patched with inserted padding, fake variables, hand assembly, original-target
field solving or a truncated comparison window.

The real 1,896-byte `Card::start_spell` parent and the large HUD UI/capture
producers are still separately unfinished. As yet **zero new authored whole
exact bytes** are credited to the 602-byte Card parent, and no complete
link/playable-game claim is made.

## Two originally overlooked complete physical leaves

| Whole original function | Independently proved original | Source/C++20 result | Original parent call |
| --- | --- | --- | --- |
| `0x00488800` `NativeCardPlayView::is_paused_488800` | **41B/14 i386**, no E8/HIGHLOW; play-state word `+0x10` equals 1 | **41/41 exact** | Card E8 `+0xDC` |
| `0x00488880` `NativeCardEndFlagView::requires_extra_sound_488880` | **23B/11 i386**, no E8/HIGHLOW; Card flag word `+0x78`, shift 7/AND1 | **23/23 exact** | Card E8 `+0x23E` |

A read-only Ghidra result suggested a C++ `bool` return for the first leaf,
but the original **returns a full 32-bit EAX** value. `bool` compiled to
**42B** with `movzx eax,byte ptr [ebp-4]`, while the corrected natural
`std::int32_t` return compiles to the complete **41B** original with
`mov eax,dword ptr [ebp-4]`. This independently demonstrates why old
Ghidra prototypes must be tested rather than treated as binding ABI claims.

The 23-byte Card-specific bit-7 helper is game-authored and contributes
**one new exact game head /23 original `.text` bytes**. The 41-byte play-state
predicate is physically exact but its original ownership is not proven;
it remains `origin=unknown/review` with **zero added game-authored credit**.
Both share one ordinary owner [`CardFinishStatusHelpers.cpp`](../src/CardFinishStatusHelpers.cpp)
with no copied x86 code and without changing the public Card layout.

Canonical affected-only replay:

```text
card_play_pause_41: exact (41/41 bytes)
card_extra_sound_flag_23: exact (23/23 bytes)
Exact replay: 2/2 units, 1 cold objects
```

Reproduce without full-graph cold replay:

```bash
scripts/repo-python scripts/verify-card-finish602-native.py \
  --helper-object build/core1000-canonical/CardFinishStatusHelpers.obj \
  --parent-object build/core1000-probes/CardFinishSpell602.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardFinishStatusHelpers.cpp
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/CardFinishSpell602.cpp build/core1000-probes/CardFinishSpell602.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/validate-tracking.py --require-target
```

The previously accepted four 32B/61B/19B/23B spell helpers are unchanged
and remain individually exact under the prior [Card leaf audit](CARD_SPELL_FINISH_FOUR_LEAVES_STRICT_EXACT.md).

## CORE/RECON-1001 follow-up — HUD cleanup child chain accepted

The prior HUD child boundary is now independently reconstructed as a whole
**71B** HUD two-animation cleanup, plus the **22B** event-3 wrapper and the
**34B** native Animation VM-event setter. See the [separate original and
canonical proof](CARD_HUD_CLEANUP_71_22_34_STRICT_EXACT.md). These add
three authentic game heads/+127 exact bytes; they do **not** make the
602B parent or the 39,470B Animation VM exact.
