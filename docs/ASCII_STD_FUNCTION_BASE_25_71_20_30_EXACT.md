# CORE/RECON-1041 — four whole-native std::function<void()> base members, 146 exact code bytes

Locked original: Japanese TH20 v1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **578B/139-i386 ASCII text render Boss** at `0x0044B020` and its
separately reconstructed **294B/106-i386 text submission child** at
`0x0044FFF0` use the same actual `std::function<void()>` copy and
cleanup primitives. Previously accepted exact physical heads
`0x004140F0` (93B copy constructor) and `0x00414400` (20B destructor)
contain further original STL call dependencies that were still untracked.

Four new, distinct physical native heads are now whole strict exact:

| Physical original | Body | Independently original call graph |
| --- | ---: | --- |
| `0x00413F80` | **25B/12 i386** | `std::_Func_class<void()>::_Func_class`, called from the already exact 93B copy constructor E8 `+0x29`; own E8 `+0x0C -> 0x00414C60` |
| `0x00414B90` | **71B/27 i386** | `std::_Func_class<void()>::_Reset_copy`, original exact 93B copy E8 `+0x3C`; own E8 `+0x0C -> 0x00414A80`, `+0x1B -> 0x00414AD0`, `+0x3B -> 0x00414C60` |
| `0x00414310` | **20B/10 i386** | `std::_Func_class<void()>::~_Func_class`, called from the already exact 20B std::function destructor E8 `+0x0A`; own E8 `+0x0A -> 0x00414D50` |
| `0x00414C60` | **30B/12 i386** | `std::_Func_class<void()>::_Set`, called by the new native 25B ctor E8 `+0x0C` and 71B reset E8 `+0x3B`; no nested E8 |

The entire **146B** is independently SHA-pinned in
[`verify-ascii-func-class-chain-native.py`](../scripts/verify-ascii-func-class-chain-native.py).
The verifier reads original PE function bounds, all nested native call
fields and actual destinations, returns through the complete native
instruction extents and authentic *absence* of PE HIGHLOW fields. It
also checks the complete previously exact original 93B/20B parent
bodies and verifies actual physical E8 parent-child edges.

The maintained *one* natural source
[`AsciiTextRender578.cpp`](../src/AsciiTextRender578.cpp)
passes a real `std::function<void()>` by value and therefore
instantiates all four genuine standard-library C++ methods with the
pinned MSVC 19.44 i386 C++20 profile `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`. No per-head cloned C++ translation unit,
artificial padding, fake owner struct, raw disassembly or additional
library forwarding source is needed. Four new canonical units reuse
**the existing `AsciiTextRender578.cpp` object provider**; the two
prior exact std::function methods remain covered in the *same*
focused source replay:

```text
ascii_function_copy_93: exact (93/93 bytes)
ascii_function_dtor_20: exact (20/20 bytes)
ascii_func_class_ctor_25: exact (25/25 bytes)
ascii_func_class_reset_copy_71: exact (71/71 bytes)
ascii_func_class_dtor_20: exact (20/20 bytes)
ascii_func_class_set_30: exact (30/30 bytes)
Exact replay: 6/6 units, 1 cold objects
```

All four newly accepted physical heads are C++ standard-library/
compiler implementation methods, `origin=unknown/review`. Their
**146 distinct original `.text` bytes add four whole strict units**,
but contribute **zero new game-authored heads/bytes**. Their already
exact 93B/20B parents and still-unaccepted 578B ASCII Boss are not
credited twice. The 294B text submit and original 2,227B renderer
core also remain NONEXACT/source-absent respectively. No full cold
replay was run.

```sh
scripts/repo-python scripts/verify-ascii-func-class-chain-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AsciiTextRender578.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
