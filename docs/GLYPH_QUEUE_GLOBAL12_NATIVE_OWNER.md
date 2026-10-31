# CORE/RECON-1077 — actual native 12B PMR glyph task-list global, correction to 2,227B text Boss

Original TH20 Japanese Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The physical original address **`0x005B66E0` is the 12B C++
`std::pmr::list<std::function<void()>>` object itself**, not a
pointer to a separately allocated `NativeGlyphQueueView`. The old
nonexact 2,227B GDI text producer source incorrectly declared
`extern NativeGlyphQueueView* native_glyph_queue_5b66e0` and used
`native_glyph_queue_5b66e0->submit_4162f0(submitted)`. This was a
material source layout error: a dereference of the first 4B word
would use the PMR allocator resource pointer as the queue owner.

## Independent original PE evidence — two real game Bosses share one global

[`verify-glyph-queue-global12-native.py`](../scripts/verify-glyph-queue-global12-native.py)
independently SHA-attests the original entire game-owned **254B/74-i386
queue dispatcher** `0x00416140`, original entire **2,227B/470-i386**
text rasterizer `0x00415830`, and original **56B/22-i386** queue
submission bridge `0x004162F0`. It pins original physical E8 and
PE HIGHLOW fields from the immutable PE, not from compiled COFF:

- Native 254B dispatcher has **four distinct physical PE HIGHLOW
  `+0x29`, `+0x7C`, `+0x94`, `+0xAB`**, *each pointing directly to
  the same `0x005B66E0` list object*. Its E8 `+0x2D` calls the
  already exact 17B native `std::list::size()` getter `0x00412730`
  that reads the actual list **count at receiver `+0x08`**. This
  establishes the true native 12B list layout and real global owner.
- Native 2,227B GDI text producer has actual physical **PE HIGHLOW
  `+0x820 -> 0x005B66E0`** immediately before its E8
  `+0x824 -> 0x004162F0`. Thus the producer also passes the
  *address of the global list object* as its queue receiver, not the
  contents of the global's first pointer word.
- The separately whole-exact original 56B queue submission bridge
  reads **receiver `+0x04`** for the current list node/sentinel and
  calls the genuine native 151B PMR `_Emplace` at E8 `+0x2C`.
  The borrowed view with one `memory_resource*`, one node pointer,
  and one `uint32_t` count exactly describes this original 12B i386
  storage. No second global `NativeGlyphQueueView*` exists here.

## Correct maintained types and local exactness

[`src/NativeGlyphTaskQueue.hpp`](../src/NativeGlyphTaskQueue.hpp)
remains the one real global definition-side interface:
`extern GlyphTaskQueue native_glyph_task_queue_5b66e0;`, where
`GlyphTaskQueue = std::pmr::list<std::function<void()>>` and the
original x86 object is exactly 12B.
[`src/NativeGlyphTextQueueView.hpp`](../src/NativeGlyphTextQueueView.hpp)
now contains only a nonowning borrowed 12B field view (`+0x00` PMR
resource, `+0x04` list node, `+0x08` count) for the already exact 56B
submission method. It no longer falsely declares an **external
global pointer** of that view type. The 2,227B game producer source
[`GlyphTextCore2227.cpp`](../src/GlyphTextCore2227.cpp) now takes
the actual address of `native_glyph_task_queue_5b66e0` and borrows
that layout when calling the 56B submit method. No list object is
copied, and the original callback is still borrowed as a true
`std::function<void()>&`.

With pinned MSVC 19.44 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, the producer
source remains a legitimate **2,080B/486-i386, 25 E8/54 DIR32**
nonexact candidate against the original **2,227B/470-i386, 25 E8/43
PE HIGHLOW**. It now has one real global list DIR32 input field and
one real E8 to the correct 56B bridge; the exact constructor and
destructor of the original 0x58B task remain unaffected.
**The entire 2,227B original remains SOURCE-PRESENT, NONEXACT**, and
no original parent code or data bytes are credited exact here.

The change directly affects only three accepted source owners;
source-scoped replay verified **13/13 strict units across three cold
objects**: 2 game glyph-job ctor/dtor units, 1 exact 56B queue bridge,
1 exact 254B queue pump and its 9 generic child units. The original
254B pump and 56B bridge retain independent full native proofs. No
full-project cold replay or synthetic pointer object is used.

```sh
scripts/repo-python scripts/verify-glyph-queue-global12-native.py \
  --candidate-object build/core1059-canonical/GlyphTextCore2227.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextCore2227.cpp \
  --source src/GlyphTextQueueSubmit56.cpp \
  --source src/GlyphTextQueuePump254.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
