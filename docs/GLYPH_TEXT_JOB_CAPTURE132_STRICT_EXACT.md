# CORE/RECON-1059 — complete original 132B glyph text job capture, whole strict exact

Original target: immutable Japanese TH20 v1.00a Steamless executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x00413EC0..0x00413F43` is a **complete 132B/49-i386**
TH20-owned queued-glyph-text job constructor, native SHA-256
`1bdff818be6f3097007f19698a72a5e969b7e0922c69ca783a23efa6148247fa`.
Its actual native direct caller is the complete **2,227B glyph text core**
`0x00415830`, original E8 `+0x7E7`. This C++ function is a real
TH20-specific member constructor; it is not the folded 93B standard
library copy constructor it calls internally.

## Native structure and corrected resource-lifetime ABI

The original captures an existing canvas pointer, one color/mode word,
**two 16B transform/region values**, one extra 32-bit field at `+0x28`,
and a **40B `std::function<void()>`** at owner `+0x30`, with the
entire object occupying **0x58B**. The `+0x2C` word exists in the
native layout, but is **not written by this original constructor**;
it is left as observed, not forcibly zero-initialized.

The previous ordinary C++20 hypothesis took the input
`std::function<void()>` **by value**, moved that owned parameter into
the member, and explicitly initialized `+0x2C`. It generated a
**150B/53-i386** constructor with two cleanup/move calls rather than
the original one. Copying a by-value parameter instead generated
**196B** with EH/unwind and additional function destruction.
The immutable original has **exactly one real E8 at `+0x75` to
`0x004140F0`**, the independently whole-exact **93B std::function
copy constructor**, and **no PE HIGHLOW** within the 132B body.

Correcting the real input to `const std::function<void()>&`, copying
it into the actual 40B member, and leaving the genuinely unwritten
`+0x2C` word alone naturally generates the original
**132B/49 instructions**, all **128/128 nonrelocated bytes**, and the
exact one original E8 site/target under pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The accepted maintained body is the `NativeGlyphRenderJob` constructor
in [`GlyphTextCore2227.cpp`](../src/GlyphTextCore2227.cpp). The compiler
spelling of the 0x58B closure owner is still provisional; no fake
executable data, helper body or opcode transplant is used.

## Independent original validation and exact scope

[`verify-glyph-text-job-capture132-native.py`](../scripts/verify-glyph-text-job-capture132-native.py)
SHA-attests the full original 132B/49 body, its native `ret 0x18`, the
only actual E8 `+0x75`, absence of PE HIGHLOW and the entire original
2,227B/470 caller, including physical E8 `+0x7E7`. It separately
pins the 93B standard-library copy target and checks its already
accepted original unit. Exactly **one new complete native head** is
admitted, not the 2,227B parent or 93B generic callee.

```text
glyph_text_job_capture_132: exact (132/132 bytes)
Local dependency replay (glyph capture + existing std::function owner):
  7/7 units exact, 2 cold objects
```

This contributes **one new game-authored physical head /132 original
`.text` bytes**. The adjacent real **2,227B text rasterizer** remains
SOURCE-PRESENT, NONEXACT, with a separate C++ source candidate
**2,052B/481-i386 (24 E8/54 DIR32)** vs original **2,227B/470-i386
(25 E8/43 physical PE HIGHLOW)**. The two genuine native
`std::function` constructor/copier paths, the original 294B submit
and 578B formatter are independently tracked. Source-exactness of
this 132B job does **not** imply exact execution of its callback or
successful whole-game linkage.

```sh
scripts/repo-python scripts/verify-glyph-text-job-capture132-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextCore2227.cpp \
  --source src/AsciiTextRender578.cpp
```

## CORE/RECON-1060 — job submission lifetime corrected without changing capture

The separate native [56B glyph queue submit bridge](GLYPH_TEXT_QUEUE_SUBMIT56_STRICT_EXACT.md)
now receives the callback wrapped by this exact 132B capture as a
borrowed `std::function<void()>&`, forwards through genuine native
`std::_Unfancy`, then calls the original 151B append. This corrects
the 2,227B parent source's earlier by-value temporary assumption.
The 132B whole-exact constructor is unchanged and replays 132/132
under the affected source-object closure.
