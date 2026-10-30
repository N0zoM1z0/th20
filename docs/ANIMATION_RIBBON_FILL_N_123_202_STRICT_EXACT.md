# CORE/RECON-925 — two complete native std::fill_n bodies 123B/202B strictly exact

Locked original Japanese TH20 Steamless 1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
These are the genuine separate native **123B/45-i386** packed-color
and **202B/73-i386** float/radius array application functions called
by the independently exact ribbon palette's two 31B forwarding helpers.
The C++20 template instantiation bodies are reproduced whole, **not**
merely short `std::fill_n` call wrappers or size-matched code sketches.

## Independently original-native full physical evidence

[`scripts/verify-animation-ribbon-fill-n-native.py`](../scripts/verify-animation-ribbon-fill-n-native.py)
attests both complete immutable original PE functions, actual return
boundaries, **all 11 physical E8 sites and targets, both PE HIGHLOW
cookie fields, original control-flow signedness**, and the real
non-inlined caller E8 from each accepted 31B native forwarding helper.

| Original function | Full native roles |
| --- | --- |
| `0x0045D430`, **123B/45 i386** | E8 `+0x24 -> 0x0040B2A0` (`_Get_unwrapped_n`), `+0x2F -> 0x00411170` (`is_constant_evaluated`), `+0x62 -> 0x004185E0` (`_Seek_wrapped`), `+0x72 -> 0x005429EE` (cookie check); PE HIGHLOW `+0x07 -> 0x005B25C0`; true **unsigned `jbe` at `+0x1A` and `+0x4C`** |
| `0x0045D360`, **202B/73 i386** | E8 `+0x28 -> 0x0040B2A0` (unwrap), `+0x33 -> 0x00411170` (constant evaluation), `+0x43 -> 0x0045D270` (zero-bit check), `+0x5A -> 0x00425320` (zero-fill fast path), `+0x76/+0xB1 -> 0x004185E0` (wrapped seek), `+0xC1 -> 0x005429EE` (cookie); PE HIGHLOW `+0x07 -> 0x005B25C0`; **unsigned `jbe` at `+0x1A`, `+0x9B`** |

Original forwarder E8 `0x0045DD31 -> 0x0045D430` and
`0x0045DD11 -> 0x0045D360` physically bind these functions to the
60-color/60-radius arrays. The E8/HIGHLOW positions and destinations
are original PE facts; decoded function labels and template provenance
are separately provisional.

## C++20 unsigned count fixes a meaningful ABI error

Natural initial pinned compiler tests produced exact function sizes
(**123B and 202B**) and instruction counts but failed the original
whole nonrelocation comparison by exactly two bytes per function.
The initial `int32_t count` hypothesis used signed `jle` where the
original PE physically uses unsigned `jbe`. Switching to genuine
**`uint32_t` count** in `std::fill_n` reproduces the entire native
branch topology and exact bytes without changing source semantics to
satisfy compiler padding. The 202B native float implementation
additionally keeps the original constant-evaluation and all-bits-zero
memset optimization branches.

[`src/AnimationRibbonFillN123202.cpp`](../src/AnimationRibbonFillN123202.cpp)
contains just two explicit ordinary standard-library C++20 template
instantiations; no copied decompiler code, inline assembly, custom
unchecked memory copy or fake source function is needed. Locked MSVC
19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` produces the real full native functions. Original-bound
canonical **relocation-aware strict replay** confirms:

```text
animation_ribbon_color_fill_n_123: exact (123/123 bytes)
animation_ribbon_radius_fill_n_202: exact (202/202 bytes)
Exact replay: 2/2 units, 1 cold objects
```

These two generated C++/STL instantiations add **325 native bytes of
whole-exact compiler/template function coverage**, but **zero new
authored-game code bytes**. Historical template folding/unique original
source attribution remains `unknown/review`. The previously accepted
88B palette and 31B wrappers do not change and do not receive duplicate
original code credit. No broad graph replay is needed: the only new
compiler input is this one C++20 source/object provider.

```bash
scripts/repo-python scripts/verify-animation-ribbon-fill-n-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonFillN123202.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
