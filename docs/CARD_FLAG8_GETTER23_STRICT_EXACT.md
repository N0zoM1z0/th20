# Card bit-8 getter — original 23/23B strict exact

The locked Japanese Steamless TH20 v1.00a executable (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
has a **23-byte /11 i386-instruction** original game Card method at
`0x004888A0..0x004888B6`, complete original SHA-256
`6d3efa8c9ea19f397f043aaab853c9e94fb88993764800ad7205dbf2ae30ea8f`.
It reads the genuine `Card::spell_flags` word at receiver +`0x78`, shifts
right by eight and masks one bit. No native E8 calls or PE HIGHLOW fields
occur in this entire function. Ghidra's provisional fastcall decompilation
is not evidence of a separate fastcall function: the original machine code
uses **ECX as `this`** and returns the unsigned flag in EAX without a stack
argument.

It is called twice by the original **875B Card periodic update**
`0x00486F60` at `0x0048708E` and `0x004870BD`, and four times by the
original **6,073B battle controller Boss** `0x004B2C90`, at
`0x004B2F82`, `0x004B2FB6`, `0x004B3075` and `0x004B30A9`.
The caller at `0x004B2F82` first calls the real Card getter at
`0x00478EA0`, then passes that result in ECX to this bit-8 method,
confirming the actual Card receiver and showing that this is a genuine
per-frame gameplay flag test rather than a fabricated standalone wrapper.
Neither larger caller is thereby accepted as exact.

[`src/CardFlag8Getter23.cpp`](../src/CardFlag8Getter23.cpp) defines a
non-instantiated borrowed `NativeCardBit8GetterView` whose method reads
`(Card::spell_flags.bits >> 8) & 1u`. The actual `Card` layout already
has `static_assert(offsetof(Card,spell_flags)==0x78)`. Pinned MSVC 19.44
x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
generates exactly **23/23B** with all 11 original instructions and zero
COFF relocations. The original-only SHA/body, six complete physical E8
callsite roles, compiled function and canonical build receipt are checked
by [`scripts/verify-card-flag8-getter23-native.py`](../scripts/verify-card-flag8-getter23-native.py).
No dummy locals, inline assembly, fabricated NOPs, modifications of the
existing `Card` class or double credit for compiler helpers were used.

Scoped cold verification:

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardFlag8Getter23.cpp
scripts/repo-python scripts/verify-card-flag8-getter23-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

**One new game-authored original whole-exact function, 23 credited bytes.**
The 875B Card update was subsequently reconstructed
[whole strict exact](CARD_TICK_BOSS875_AND_UI32_STRICT_EXACT.md) using this
23B getter at its two actual original E8 sites. It adds **no second
credit for this getter**. The 6,073B battle controller remains an
unaccepted Boss. No full-graph cold replay, link, or runtime-playable build is claimed.
