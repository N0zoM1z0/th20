# CORE/RECON-1029 — original 64B Card text capture move constructor whole native exact

Locked original: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The native `0x00486AF0` is a complete **64B/24-i386** move constructor for
the actual **36-byte** Card text capture: Card* `+0`, real
`std::pmr::string` `+4`, Animation* `+0x20`. Its immutable original
SHA-256 is `73fe6bdfd5aaa84445e1648d41ce27562dd4717d3af492a96b14cb3a28f6ad3b`.
The real original 66B lambda's target wrapper at `0x004867B0` calls
it at **E8 `+0x33`**, after selecting its actual vtable and forwarding
the source capture. The move constructor calls genuine original
**108B PMR string move constructor `0x0046A710`** via E8 `+0x26`;
no original PE HIGHLOW fields occur within the 64B body.

Unlike an artificial generated copy, the natural maintained
[`NativeCardTextPayload`](../src/NativeCardTextPayload.hpp) has an explicit
move overload taking `NativeCardTextPayload&&`, with real semantic
member initialization `card(source.card),
text(std::move(source.text)), animation(source.animation)`.
This preserves original move ownership and the actual capture layout.
The associated complete 56B capture constructor, 23B destructor,
and 167B PMR copy constructor remain in **one existing canonical source
owner** [`CardTextPayloadNative.cpp`](../src/CardTextPayloadNative.cpp).
No duplicate look-alike type, copied disassembly or fake source branch is
introduced. The native name/callback constructor still needs reconstruction.

[`verify-card-text-payload-move64-native.py`](../scripts/verify-card-text-payload-move64-native.py)
SHA-attests the entire 64B body and real `ret 4`, its original
PMR move E8 target, the independent complete 66B wrapper SHA
`f91c1c12104a5688a3ef89f1b971eb7695e4b4520449c78e3b5bfa007dc3a802`,
and its original E8 `+0x33` into the 64B move. No target relocation
is inferred from the candidate object. Locked MSVC 19.44 i386 C++20
generates the **complete 64B/24** and the one genuine original REL32
field at `+0x27` targeting `0x0046A710`.

Because the public capture header changed, the captured include closure
identifies **two affected exact objects/four earlier exact units**;
just those two objects were cold recompiled once. The four earlier
functions and this newly exact move function all replay successfully:

```text
card_text_payload_ctor_56: exact (56/56 bytes)
card_text_payload_dtor_23: exact (23/23 bytes)
card_text_payload_pmr_copy_167: exact (167/167 bytes)
card_start_pmr_string_char_ctor_128: exact (128/128 bytes)
card_text_payload_move_64: exact (64/64 bytes)
Exact replay: 5/5 units, 2 cold objects
```

This adds **one whole strict unit/64 unique original bytes**, but its
original compiler-generated lambda/capture source ownership remains
`origin=unknown/review`; no new game-authored head or bytes are claimed.
The called **108B original PMR move** is still distinct: a natural
source-generated candidate currently measures **99B**, one fewer
9-byte `std::move` forwarding sequence than the original. A similarly
missing semantically meaningful `std::move` call affects the native
102B `std::function` capture constructor and 65B `_Reset` helper.
They remain NONEXACT rather than having code manually padded to match.
The complete original 1,896B Card start parent is likewise NONEXACT.

```sh
scripts/repo-python scripts/verify-card-text-payload-move64-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardTextPayloadNative.cpp \
  --source src/CardStartSpell1896.cpp
```

## CORE/RECON-1030 — copyable target ownership and unchanged move ABI

The actual `std::function<void()>` target must be copy constructible.
A normal PMR-string copy overload and the **declaration only** of the
unreconstructed 111B original lambda `operator()()` are now maintained
beside the real exact 64B move constructor. The scoped source closure
has three existing canonical objects and seven exact units (56B, 23B,
167B, 64B, 128B, 153B, 32B); all seven were freshly rebuilt and remain
whole exact. The original 1,896B Card parent remains NONEXACT. See the
[true text producer frontier](CARD_START1896_TEXT_TASK_CONSTRUCTION_FRONTIER.md).
