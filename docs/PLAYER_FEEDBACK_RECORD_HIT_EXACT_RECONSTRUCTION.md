# CORE/EXACT-316 — complete 115-byte PlayerFeedback capped hit recorder

Target: the immutable user-selected Japanese TH20 v1.00a Steamless game,
whole-file SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire original `PlayerFeedback::record_hit(int)` at
`0x004FB3A0..0x004FB412` is **115 bytes / 42 x86 instructions**, with
complete original interval SHA-256
`bb8284deafa365ea772f01b37d124870cd84a0f428380d68711f40781d613ba8`.
Its full maintained source already existed in `src/PlayerStorage.cpp`, but a
previous probe emitted only 114 bytes. The exact natural C++20 statement
structure now yields the *entire original 115 bytes*, with no inline
assembly, shortened comparison, synthetic return, fake dependency or manually
inserted NOP.

## Actual gameplay and independent native evidence

The complete original method advances its real inherited `Timer` by the
signed incoming amount; only if the updated timer's signed value is greater
than 30 does it invoke the genuine `Timer::operator=(30)`. It increments the
raw unsigned `PlayerFeedback+0x38` counter (naturally wrapping at 32 bits),
copies the result to the `+0x30` current record field, and updates `+0x3C`
only if its *signed* value is lower than the new signed current record.
Every branch, all counter writes and the complete `ret 4` are matched.

Independently decoded **three original `REL32` call relocations**:

| Native offset | Original callee | Meaning |
| --- | --- | --- |
| `+0x11` | `0x0045C300` | exact `PlayerFeedback::operator+=(int)` |
| `+0x22` | `0x00461070` | real `Timer::greater_than(30)` |
| `+0x33` | `0x00423520` | real `Timer::operator=(30)` |

There are **103 non-relocation bytes and 12 relocated bytes**; all match
under complete original anchored relocation replay. The native one-byte
`nop` at original `+0x15` naturally appears under the locked MSVC x86
`/Od` profile when the real Timer accumulation is expressed as its own
ordinary C++ scope before the subsequent capped-value evaluation. This
scope contains a real side-effecting statement and is not padding or an
inert compiler-shaping local. The original conditional's own naturally
emitted `nop` after Timer assignment remains identical too.

## Scoped proof and relationship to the large Player reset

The canonical `player_feedback_record_hit` manifest unit in
`config/match-units.toml` passes **115/115 full original native bytes and
all three independently attested references** using MSVC 19.44.35211 x86
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
Only the existing `src/PlayerStorage.cpp` implementation changed; no shared
header, type layout, compiler profile or other exact source inputs changed.
Exactly **9/9 scoped original units in one freshly built canonical object**
pass, preserving all eight previously exact Player storage/Feedback methods.
The focused complete proof is `.analysis/core316-feedback-replay.log`.
No whole-graph cold replay was performed.

This entire method is **separate** from the 332-byte Player graze feedback
effect at `0x004F8B90`, which remains nonexact. The independently exact
966-byte Player initialization/reset boss is likewise a separate complete
parent; this smaller exact method does not replace its evidence or imply
whole-executable linkage/runtime completeness.
