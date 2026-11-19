# Glyph Text Core: real queued job rvalue/reference lifetime improves 2,227B Boss

Original TH20 v1.00a Japanese Steamless GDI glyph text rasterizer has a
complete **2,227-byte/470-i386** native function at `0x00415830`, followed by
one original NOP and 22 genuine pointer-switch entries (total **2,316B**).
The maintained complete C++20 source remains **SOURCE-PRESENT, NONEXACT**.

## Native task construction and reference ownership

The original constructs an `0x58`-byte `NativeGlyphRenderJob` at native E8
`+0x7E7` to the separately exact `0x00413EC0` constructor. The return value
from that constructor is a real pointer to the constructed task. The native
sequence preserves that pointer through stack locals `-0x290` and `-0x294`
before passing the task by reference to the original std::function capture
constructor at E8 `+0x80F` (`0x00412F20`). After the queue borrows the
function at E8 `+0x824`, the separate original `std::function` and job
retirement callees occur in the order `+0x833` and `+0x842`.

The maintained source already used a named job, but the move expression
passed it directly. The current natural C++ introduces a genuine **used**
rvalue reference to that existing job:

```cpp
NativeGlyphRenderJob&& queued_job=std::move(glyph_job);
std::function<void()> submitted(std::move(queued_job));
```

This is a reference to the same live `NativeGlyphRenderJob`, not a dummy
buffer, dead variable, new object, artificial NOP, ASM or altered call ABI.
The object is still destroyed in its existing scope after the queue submit;
`std::function` destructor still precedes `NativeGlyphRenderJob` destructor.
The extra referenced-object address lifetime now approaches the original
explicit task pointer staging.

## Whole-function convergence, not a cropped prefix

Pinned MSVC 19.44 x86 C++20 with `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` produces:

| Complete evidence | Previous source | Current source | Original |
| --- | ---: | ---: | ---: |
| Complete code + generated switch table | 2,296 B | **2,308 B** | 2,316 B |
| Decoded code instructions | 466 | **468** | 470 |
| Local stack frame | `0x30C` | **`0x310`** | `0x310` |
| Original E8 targets and order | 25/25 | **25/25** | 25/25 |
| E8 sites physically aligned | 17/25 | **17/25** | 25/25 |
| Sum of absolute E8 location deltas | 148 | **52** | 0 |
| Original body PE data target roles | 43/43 | **43/43** | 43/43 |
| Original body data sites aligned | 41/43 | **41/43** | 43/43 |
| Ordinary same-position bytes | 1,626/1,936 | **1,629/1,948** | all |
| Generated switch pointers / aliases | 22 / 17 | **22 / 17** | 22 / 17 |

The candidate retains all original real call/data classes, including the
independently exact folded 8B `std::addressof` pointer identity helper at E8
`+0x7BC`. The `std::function` construction E8 now occurs at `+0x809` instead
of the previous `+0x7FD`, just six bytes before its native `+0x80F` site.
The queue, constructor and destructor roles remain in their native order.

The strict whole-candidate structural verifier has been adjusted to require
**2,308B**, **468 decoded instructions**, all **90 actual COFF fields**,
**17 aligned E8 sites**, E8 absolute delta sum **52**, **41/43** aligned
body data relocations and **1,629/1,948** ordinary bytes. These comparisons
are to the **full native source contributions**, not to a shortened body;
none of the residual eight missing bytes or x86 instructions is fabricated.

The directly affected `GlyphTextCore2227.cpp` translation unit was cold-built
alone. Its **132B capture constructor** and **23B job destructor** remain
**2/2 strict whole-native exact**. Original GDI Text Core remains
**NONEXACT** with zero new parent authored `.text` credit; the outstanding
source issues are the remaining task constructor pointer lifetime and
post-queue cleanup/return compiler lowering.
