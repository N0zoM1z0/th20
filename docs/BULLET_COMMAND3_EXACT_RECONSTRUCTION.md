# CORE/EXACT-244 — whole 898-byte original Bullet command-3 boss with seven-way native switch table

Source of truth is immutable Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This is the **entire native** Bullet command3 angle/speed gameplay function
at `0x00483580..0x00483901`, with **898 original x86 bytes and 257 complete
instructions**, original function SHA-256
`39d3270bf65e77f9b82b4df5348e009410e3260c5d3b870d758754455beaa786`.
The two original alignment bytes at `0x00483902..0x00483903` and real
**seven-entry native 28-byte switch table** at `0x00483904..0x0048391F`
are included in the full **928-byte** compiler contribution, SHA-256
`abe499abe3bc76d2da90e827540da52f31a38ff25715a60c16cabd6dce219228`.
The immediately following original function begins at `0x00483920`.

The normal maintained C++20 `Bullet::advance_command3()` in
`src/BulletCommand3.cpp` is a **single complete game-authored member**,
not seven standalone arms, a native byte array or an assembly reproduction.
It preserves the real `BulletExtendedCommands::at(3)` owner and
`Timer::at_least(command.word_30)` gate. On expiry it optionally emits the
original live Bullet sound, increments the command counter at +`0x38`, and
switches on the true command mode at +`0x3C`, with all seven original
case entries:

| Native index | Whole switch action | Original label |
| ---: | --- | --- |
| 0 | `Angle += scalar_14` | `0x0048364A` |
| 1 | Player direction to Bullet plus scalar offset | `0x0048367E` |
| 2 | Assign direct scalar angle | `0x004836E5` |
| 3 | Assign direct scalar angle | `0x00483717` |
| 4 | Assign direct scalar angle | `0x00483749` |
| 5 | Same real case body as 0 | `0x0048364A` |
| 6 | Same real case body as 1 | `0x0048367E` |

All seven actual table values above were read independently as native
little-endian dwords from the locked PE, not inferred from successful
relocation comparison. The separate original jump-through pointer at
`+0xC6` targets `0x00483904`. The code's real `Context::player()` at
`0x0040FF90` and the independently exact whole Player direction method
`0x004FF350` supply the player-relative angle, with native `Angle` addition
and assignment operators. On expiry it writes the true Bullet speed from
`scalar_10`, resets the command Timer, and completes when signed counter
`word_38 >= word_34`; on completion the real `polar` updates Bullet
velocity and bit `0x10` of low Bullet command flags is cleared, returning 1.
Otherwise the original speed interpolation takes the Timer's fractional
age, the current Bullet speed and the **signed** command duration, updates
velocity with its current Angle, advances the original Timer and returns 0.

## Independent native codegen and exactness proof

The first entire natural MSVC `/Od` probe produced **960 bytes including
its switch table**, using a **wrong unsigned** integer-to-float conversion
for `word_30`. The original x86 uses signed `cvtsi2ss` directly. Correcting
the duration's true signedness reduced the entire contribution to **924B**,
but the compiler still differed on the order of preparing two command-slot
accesses and generated a memory-operand float division rather than the
original separate SSE register. A **single natural** expression with
`speed * commands.at(3).timer.fraction()` (the original multiply operand
order), divided by a signed-converted duration, caused the locked MSVC
compiler to generate **exactly the original 898B code plus 30B table and
alignment**. The original integer signedness and natural arithmetic order
are both actual behavioral/ABI evidence, not inert compiler-shaping locals.

The canonical target has **41 relocations**, **164 relocation-covered
bytes**, and **764/764 matching non-relocation bytes** across the entire
928B contribution. They include all real command-slot getters, sound and
Timer/Angle/Player/polar callees, the switch-table pointer, and all **seven
original exact switch case addresses**. `config/match-units.toml` explicitly
records the whole source/object/profile, **`size = 898`** and
**`compare_size = 928`** so the jump table is never silently discarded by a
prefix-only match. The locked MSVC 19.44 x86 C++20 profile
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` recompiled this
entire object and the **strict canonical replay passed 898/898 authored
coverage bytes and 928/928 complete compared bytes**, including the 41
independent original relocation fields. No assembly, padding tricks or
relaxed comparator were used.

Because the new native command method is declared on shared `Bullet.hpp`,
its actual compiler-receipt closure comprises **22 fresh source objects
and 60 complete accepted native units**, **59 older + 1 new**. Every old unit
was cold recompiled and strictly replayed, including already reconstructed
707B rectangle cancellation, 832B four-way boundary, 339B BulletFire,
662B cancellation *callers*, and the exact 2-bit flag owner.
All **60/60 strict units passed**. Compiler-private local BulletController
`$SG85508` changed to `$SG85509`; four Dialogue literals
`$SG117853..117856` changed to `$SG117854..117857`. Only those COFF symbol
names changed; their native original data destinations and relocation fields
remained identical. The original 898B/928B object and all affected sources
were checked with **no unfiltered whole-graph cold replay**.

Focused evidence logs:
`.analysis/core244-bullet-command3-native-replay.log`,
`.analysis/core244-bullet-header-affected-replay-part-0.log` and
`.analysis/core244-bullet-header-affected-replay-part-1.log`.
The original complete native disassembly and switch bytes are preserved in
`.analysis/core244-native-00483580.asm`.

The **662-byte** Bullet cancellation core, **781-byte** screen-wrap boss,
**898-byte** command3 boss's upstream parent at `0x0047DCF0` (**12,140B**),
**3,735-byte** single Bullet emitter and **41,967-byte** Enemy opcode root
remain nonexact. Matching this complete function does not prove the rest of
the game can be linked or executed.
