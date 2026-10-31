# CORE/RECON-1031 — exact native 22B Card lambda capture name getter

Target: immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original game Card's captured lambda at `0x00486E80` is a complete
**111B/42-i386** callback body (native SHA-256
`12212f28b9331ddb3041bea74034cf798e3bc7ab873eb2372b2146cb430d21ae`).
Its E8 `+0x10` goes to the original **22B/10-i386** native member
getter `0x0044BAF0` (SHA-256
`43bd0312020d597cfa7218127be88cc8f928d51c1671f92cda054524d49f043b`).
That getter reads the existing `NativeCardTextPayload`'s real
`std::pmr::string` at `+4`, then invokes the genuine original
`std::pmr::string::c_str` at `0x0040F2C0` via E8 `+0x0D`.
There are **no original PE HIGHLOW relocations** inside the getter.

The natural maintained method
`NativeCardTextPayload::name_c_str_44baf0() const` in
[`CardTextPayloadNative.cpp`](../src/CardTextPayloadNative.cpp)
uses the actual data member and returns `text.c_str()`. No look-alike
struct, dummy buffer, special exact-only branch or fabricated string
pointer is needed. The initial typed probe and actual shared source
both reproduce **22B/10** with all **18/18 nonrelocation bytes** and
the genuine original single REL32 destination `0x0040F2C0`.

Read-only native verifier
[`verify-card-text-name-getter22-native.py`](../scripts/verify-card-text-name-getter22-native.py)
independently hashes the complete original 22B and 111B function
bodies, their real end-of-function instructions, the callback's
four actual E8 roles, the getter's sole original PMR call and PE
HIGHLOW absence. With the locked MSVC 19.44 i386 C++20 profile,
the affected Card text source and nonexact Card start nesting are
rebuilt only once:

```text
card_text_payload_ctor_56: exact (56/56 bytes)
card_text_payload_dtor_23: exact (23/23 bytes)
card_text_payload_pmr_copy_167: exact (167/167 bytes)
card_start_pmr_string_char_ctor_128: exact (128/128 bytes)
card_text_payload_move_64: exact (64/64 bytes)
card_text_capture_cstr_22: exact (22/22 bytes)
Exact replay: 6/6 units, 2 cold objects
```

This adds **one distinct whole-exact 22B original native function**.
Original compiler/generic wrapper versus authored lambda ownership
is not settled; it is marked `origin=unknown/review`, so **zero newly
credited authored-game heads/bytes**. The original 111B callback body,
its own 102B intermediate `std::function` constructor and the 578B
text-rendering function at `0x0044B020` remain separate, nonexact
reconstruction targets. The full 1,896B Card start Boss is still
SOURCE-PRESENT/NONEXACT, and a matching name getter does not close it.

```sh
scripts/repo-python scripts/verify-card-text-name-getter22-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardTextPayloadNative.cpp \
  --source src/CardStartSpell1896.cpp
```
