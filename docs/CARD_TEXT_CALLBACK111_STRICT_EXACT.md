**CORE/RECON-1192 erased-target vtable closure:** The concrete
`std::_Func_impl_no_alloc<NativeCardTickCallback>` now has all six original
vtable methods separately reconstructed from the same natural C++ source:
47B `_Copy`, 104B `_Move`, 26B `_Do_call`, 16B `_Target_type`, 35B
`_Delete_this`, and 26B `_Get`. The 14B `std::invoke<NativeCardTickCallback>`
bridge is also exact and calls the distinct 34B `NativeCardTickCallback`
operator target. Every original E8/DIR32/PE HIGHLOW role is preserved.
The `_Move` contribution includes five compiler-generated trailing INT3
bytes that exactly match the native adjacent alignment span; the function
coverage remains 104B and the comparison span is 109B. No source padding or
assembly is used. The 34B operator body and its 22B AnimationHandle event-4 bridge are now
whole exact under CORE/RECON-1193. The callback's native field access is
`Card::info_handles[1]` at `+0x18`, not the Card age Timer at `+0x24`.

**CORE/RECON-1190 nested callable extension:** The callback's own
`std::function<void()>` now has its original 102B constructor at `0x00486740`
and 90B `_Reset` at `0x004869D0` restored whole exact. The maintained source
explicitly instantiates `std::forward<NativeCardTickCallback>` with
`__declspec(noinline)`, preserving both original E8 calls to the shared 8B
`0x0040B280` forwarding leaf. The constructor matches 102/102 bytes with
five relocations; `_Reset` matches 90/90 with five E8 destinations. The
53B `std::_Func_impl_no_alloc<NativeCardTickCallback>` move constructor at
`0x004866B0` is also now whole exact: 41/41 ordinary bytes, two E8 targets,
and its original vtable HIGHLOW. This is a separate nested callable from the
102B/65B `NativeCardTextPayload` callable
used by Card start; neither result grants exactness to the 578B draw Boss or
1,896B Card start parent.

# CORE/RECON-1037 — complete original 111B Card name-display callback strict exact; corrected 22B PMR receiver

Target: the locked Japanese TH20 Steamless v1.00a executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `NativeCardTextPayload::operator()() const` at
`0x00486E80..0x00486EEE` is a **complete 111B/42-instruction game-specific
Card name-display callback**, SHA-256
`12212f28b9331ddb3041bea74034cf798e3bc7ab873eb2372b2146cb430d21ae`.
Natural C++20 source [`CardTextCallback111.cpp`](../src/CardTextCallback111.cpp)
now produces the entire **111/111 original bytes** with the same four
native E8 calls and one genuine PE HIGHLOW. The exact continuation is not
inferred from the still nonexact 578B renderer or 1,896B Card start.

## Original physical call and data graph

[`verify-card-text-callback111-native.py`](../scripts/verify-card-text-callback111-native.py)
independently SHA-attests the full original body through its real `ret`,
all four E8 instruction positions/destinations and the sole PE HIGHLOW:

| Original field | Physical original destination | Real source role |
| --- | --- | --- |
| E8 `+0x10`, REL32 `+0x11` | `0x0044BAF0` | actual embedded `std::pmr::string::c_str` member |
| E8 `+0x36`, REL32 `+0x37` | `0x004142A0` | one-word `Card*` callable constructor, physically folded with earlier 24B value constructor |
| E8 `+0x3E`, REL32 `+0x3F` | `0x00486740` | real original 102B `std::function` constructor for Card callable |
| DIR32 `+0x5D` | `0x005C0028` | real current Animation/Renderer owner global |
| E8 `+0x62`, REL32 `+0x63` | `0x0044B020` | genuine variadic `__cdecl` **member** text renderer, hidden 8B return object |

The original callback first takes the captured PMR string at `+4`,
reads the `Animation*` capture at `+0x20`, constructs a four-byte
`Card*`-capturing `std::function<void()>` directly in the call stack,
and issues a real native 578B formatted text call with native
font 4, color `0xFF000000`, and layer **`0x00FFFFFF`**.
An early source trial used `-1`, which is **not** equal to native
`0x00FFFFFF`: MSVC emitted a 2-byte `push -1` instead of original
5-byte `push 0x00FFFFFF`. Correcting the meaningful value restored
the original three bytes without a fake local, NOP, assembly or
manually copied target instructions.

## Correction of a misleading earlier source hypothesis

[CORE/RECON-1031](CARD_TEXT_CAPTURE_CSTR22_STRICT_EXACT.md) previously
accepted the complete physical `0x0044BAF0` getter code but gave it
an **incorrect C++ receiver**: a custom method
`NativeCardTextPayload::name_c_str_44baf0() const`.
The immutable original Card callback begins by **adding 4 to the capture
`this` before E8 `+0x10`**. Therefore `0x0044BAF0` receives the
real **embedded `std::pmr::string`**, not the entire 36B Card payload.
Inside that 22B getter, MSVC then adds another 4 to the PMR string
receiver to reach its genuine `_String_val`, calling the original
`_String_val::_Myptr` head at `0x0040F2C0`.

The corrected maintained source therefore uses plain `text.c_str()`
in the 111B callback. The C++20 compiler naturally emits
`std::pmr::string::c_str` as the same **whole original 22B/10-i386**
function, with **18/18 ordinary bytes** and exactly its original
one REL32 field. The old custom getter was **removed**; the existing
canonical `card_text_capture_cstr_22` unit has been **migrated** to
the real `std::pmr::string::c_str` symbol in the new callback owner.
The physical 22B head remains one previously accepted native unit:
**no duplicate code head/bytes are credited**. The original PMR
receiver was wrong in the older source documentation despite its
incidental machine-byte match, and is explicitly corrected here.

## Strict canonical acceptance and scope

The full 111B callback has **91/91 nonrelocated bytes** and all five
independently anchored original fields; `card_text_callback_111`
replays the entire 111B original physical function. The migrated 22B
PMR `c_str` method independently replays the same original physical
extent. Both are ordinary C++20, sharing real types and the original
MSVC 19.44 i386 pinned profile.

`NativeCardTextPayload.hpp` and the original capture owner were changed,
so their captured dependency closure was inspected. Only **three
canonical objects** are recompiled: Card text payload, Card start
nested PMR/string operations, and this new Card callback object.
All **eight affected exact units** pass, including the previous 22B
unit under its corrected natural C++ owner:

```text
card_text_payload_ctor_56: exact (56/56 bytes)
card_text_payload_dtor_23: exact (23/23 bytes)
card_text_payload_pmr_copy_167: exact (167/167 bytes)
card_text_payload_move_64: exact (64/64 bytes)
card_start_pmr_string_char_ctor_128: exact (128/128 bytes)
card_text_callable_test_7: exact (7/7 bytes)
card_text_capture_cstr_22: exact (22/22 bytes; corrected PMR receiver)
card_text_callback_111: exact (111/111 bytes)
Exact replay: 8/8 units, 3 cold objects
```

This contributes **one new game-authored function /111 original `.text`
bytes**, from the complete Card-specific callback. The 22B PMR `c_str`,
102B `NativeCardTickCallback` std::function constructor and 90B `_Reset`
remain generic C++ runtime/template bodies with **zero new game-authored
credit**; the folded 24B `Card*` constructor at `0x004142A0` is **not**
credited again. The nested constructor and reset are now independently whole
exact with their original 5/5 relocations each, including both out-of-line
`std::forward` calls to `0x0040B280`. The separate 578B ASCII render Boss and
enclosing 1,896B Card start remain NONEXACT and gain no transitive exactness.
Whole-game linking and frame-time runtime behavior remain unproven. No full
cold replay ran.

```sh
scripts/repo-python scripts/verify-card-text-callback111-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardTextPayloadNative.cpp \
  --source src/CardStartSpell1896.cpp \
  --source src/CardTextCallback111.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1038 — native PMR pointer dependency whole exact

The actual original `std::pmr::string::c_str()` method used by this
111B Card callback itself invokes a [complete exact 54B `_String_val::_Myptr`
implementation](CARD_TEXT_STRING_MYPTR54_STRICT_EXACT.md) at `0x0040F2C0`.
Its 42B capacity test and 8B pointer-unfancy callee were already exact.
One original 54B STL source head is newly covered without duplicating
its PMR/c_str/callback callers or changing any authored-game credit.
