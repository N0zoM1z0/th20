# CORE/EXACT-348 — complete native 87-byte PlayerRecord graze counter accumulator

Comparison oracle: immutable user-selected Japanese TH20 v1.00a Steamless
original, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire native `PlayerRecord::add_field_e4(int)` lives at
`0x004FE8D0..0x004FE926`: **87 original bytes, 26 i386 instructions**,
original interval SHA-256
`1a7b71c907b1fead8710a7c3f998ee5de6a9c8424b5344648f14891e212df9f7`.
Its actual caller includes the now independently strict 332-byte
`Player::record_bullet_graze` at `0x004F8B90`. The maintained complete
C++20 source belongs to the *preexisting* real `src/PlayerRecord.cpp` owner.

## Native behavior and independent call

The original method adds the signed incoming delta to the actual
`PlayerRecord+0xE4` word using native 32-bit wraparound semantics, then
clamps the resulting *signed* integer to the inclusive range
**`[0,99999999]`** and returns `void` with the native `ret 4`.
The C++ implementation explicitly performs the addition using
`std::uint32_t` operands before casting to the native signed field,
so it does not invent undefined signed-overflow behavior on the host.
It then uses the real `std::clamp<int>` expression with actual field
storage. The original whole function's **only native `E8 / REL32` call**
at offset **`+0x3F`** targets `0x00471170`, the independently established
compiler `std::clamp<int>` helper, not an assumed `_Find_unchecked` search.

The natural compiler result is **87/87 complete original bytes**, including
all 26 native instructions, 83 nonrelocated bytes, the four-byte call
field and every stack-frame/local value. Its pinned MSVC i386 canonical
unit is `player_record_graze_counter_add` in
`config/match-units.toml`, reusing the actual PlayerRecord owner's
previously established C++20 `/Od /Ob0 /GS- /Gy /Zl /arch:SSE2
/fp:precise` profile, with no synthetic padding, assembly, shortened
range, alternative comparison target or fake return.

## Smallest actual strict replay scope

The typed declaration `PlayerRecord::add_field_e4` was already accepted
in the earlier **332-byte complete Player graze feedback** checkpoint;
this checkpoint changes **only the existing `src/PlayerRecord.cpp` source**
and the exact native tracking/evidence records. No public header, class
layout or other exact object profile changes.

Exactly **59/59 strict canonical units in one freshly compiled owner object**
`build/core156-canonical/PlayerRecord.obj` passed. This includes all **58**
previously accepted PlayerRecord roots, their 712-byte constructor, real
clamps, reward tracking, and the new complete 87-byte method. The focused
private log is `.analysis/core348-player-record-replay.log`; there was no
whole-graph cold replay.

The other independently unresolved original Player graze-effect callees
(`EffectInfo::queue_effect` and `EnemyController::graze_reward_active`),
Renderer/EffectInfo lifetimes, and whole-game linker/runtime closure do
**not** inherit exactness merely from this independent native counter.
