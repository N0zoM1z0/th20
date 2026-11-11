# Card time settlement: 645B Boss and 37B callback whole strict exact

Target: TH20 Japanese Steamless v1.00a, SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

Two distinct original game-authored heads were recovered from native code:

| Original head | Complete original | Pinned MSVC C++20 |
| --- | --- | --- |
| 0x004872D0 | **645B**, 164 i386, **14 E8 / 12 PE HIGHLOW** | **645/645B exact**, 541/541 ordinary bytes and all 26 physical relocation sites/targets |
| 0x00487560 | **37B**, 15 i386, **3 E8 / 0 HIGHLOW** | **37/37B exact**, 25/25 ordinary bytes and all 3 original E8 targets |

The complete original 645B SHA-256 is
9e7b7674f89795cf5c67db7779ca48fd470fa1d06fe7c023418f6060ca3f95fe;
the 37B original SHA is
5c138796ce302ea43cc3e97829b34f5bd9f18194f5757739dde41bc876b5e2ac.

## Authentic Card owner and timing behavior

The maintained **src/CardClockBoss645.cpp** uses the real Card fields:
flags at +0x78, capture index +0x88, frames +0x8C, last frames +0x90,
start time +0x98, elapsed +0xA0 and encoded time +0xA8. When the Card
starts, it records the real WindowState clock at global 0x005B6758 and
sets bit6. On completion it stores the last frame, subtracts the start
time, applies native double-precision fmod by the original **0.0167**
seconds/tick, then rounds at half a tick using native **2.0**. Seconds
are capped at 999; the fractional remainder is scaled by original
**100.0**, before the genuine existing Card::encode_time method.

It clears bit6 and writes the encoded time through the original native
38B per-difficulty archive accessor when the GameController is not
restarting. In the restart branch, it uses the distinct 41B archive
accessor to recover a stored code, checks its checksum and publishes
the original 999/99 sentinel when invalid. Both paths increment the
capture index once. These are genuine used local byte offsets and
archive bases, not fake stack variables.

The 37B callback in **src/CardClockCallback37.cpp** performs two
independent native card(0) lookups and calls the exact 645B method only
if the Card exists. Its real final E8 targets 0x004872D0.

## The original floating-point exception mode

The initial natural 645B gameplay source compiled to **630B/157 i386**
and all 14 E8 and 12 data target roles, but not original machine code.
Using the direct receiver removed an unnecessary local alias; expressing
real mutable record byte offsets and +0x1C record bases reduced the
remaining gap to **644B/163 i386**.

The original native code at +0x132 calls **__ftol2_sse_excpt
(0x00543310)** and follows it with **FWAIT (0x9B) at +0x137**.
The pinned MSVC default exception mode instead calls __ftol2_sse with
no FWAIT. The original behavior requires floating-point exception
synchronization. A scoped **MSVC float_control(except, on)** pragma
around the real function, with the previous compiler state restored
after the method, reproduces the original exception converter and
its FWAIT. It yields the complete **645B/164 i386** body, with every
original E8 and HIGHLOW field and all 541 ordinary bytes identical.
No machine opcodes, NOPs, dummy locals or assembly were inserted.

Signed/unsigned conversion, short, long long, explicit temporary and
within-function pragma variants were also compiled and did not match.

## Scoped strict acceptance

Pinned compiler: MSVC 19.44 x86, C++20, /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc. The independent
**scripts/verify-card-clock645-callback37-native.py** attests both whole
SHA bodies, all original PE call/data locations and destinations, original
fmod/floor, native constants, FWAIT and __ftol2_sse_excpt, and both
protected build receipts.

Only the two new source translation units were cold rebuilt:

    card_clock_boss_645: exact (645/645 bytes)
    card_clock_callback_37: exact (37/37 bytes)
    Exact replay: 2/2 units, 2 cold objects

Reproduce with scoped source replay only:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/CardClockBoss645.cpp --source src/CardClockCallback37.cpp
    scripts/repo-python scripts/verify-card-clock645-callback37-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target

**Two new original whole-exact game heads, 682 native .text bytes.**
The 346B WindowState clock callee is not credited here; the 38/41B archive selectors were subsequently [closed separately](CARD_TIME_ARCHIVE_ACCESSORS_38_41_NATIVE_EXACT.md), and their bytes are credited only in that checkpoint. The 1,896B Card Start and 6,073B battle-control parents
remain NONEXACT; game linking and runtime validation are open.
