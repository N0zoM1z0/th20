# CORE/RECON-1034 — native 7-byte Card std::function callable test, whole exact

The immutable original TH20 Japanese Steamless v1.00a target, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains a complete **7B/5-i386** true-valued callable test at
`0x00413910..0x00413916`, native SHA-256
`8c802cff817fdf6fe5a54e1838577f97a5b842ea2a87ef4faf70abd2b500b8eb`.
Its machine code returns a native one-byte `bool`, without an in-body
relocation, highlow field or function-padding subtraction.

This is not an inferred parent closure. The original, independently
SHA-pinned **65B/26-i386 std::function::_Reset** method at `0x00486A30`
physically invokes it via E8 at **`+0x0B -> 0x00413910`**; the same
method's remaining three actual E8s go to `0x0040B280`, `0x00486920`
and `0x00414C60`, exactly as attested by
[`verify-card-text-callable7-native.py`](../scripts/verify-card-text-callable7-native.py).
The original 65B parent still differs from the current source-generated
56B `_Reset`: the native original has an additional genuine 9B
`std::move` forwarding call. The 102B std::function constructor
similarly differs by a real 9B forwarding call. The original
1,896B Card start parent and 111B Card callback are independently open.

The already maintained natural
[`CardStartSpell1896.cpp`](../src/CardStartSpell1896.cpp)
constructs a real `std::function<void()>` with a copyable 36B
`NativeCardTextPayload`. Pinned MSVC 19.44 x86 C++20 generates a
concrete standard-library instantiation
`std::_Test_callable<NativeCardTextPayload>` whose whole **7/7B**
are identical to the original code. The canonical unit
`card_text_callable_test_7` reuses the same one source provider as
the previously accepted 128B PMR char* constructor and passes:

```text
card_start_pmr_string_char_ctor_128: exact (128/128 bytes)
card_text_callable_test_7: exact (7/7 bytes)
Exact replay: 2/2 units, 1 cold objects
```

This adds **one distinct complete native exact unit /7 original bytes**,
but it is a generic compiler/template body: `origin=unknown/review`,
**zero new game-authored exact heads or bytes**. No source/header
changes are required to obtain it, and no all-repository cold replay
was used.

```sh
scripts/repo-python scripts/verify-card-text-callable7-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardStartSpell1896.cpp
```
