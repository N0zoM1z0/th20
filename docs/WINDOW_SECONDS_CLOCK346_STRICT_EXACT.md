# WindowState 346B real-time seconds clock — whole strict exact

The Japanese TH20 Steamless v1.00a original executable has locked SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.
Its complete WindowState clock function at 0x0041CB10 has original SHA-256
0ca56b4953b8cd383b37eeab4cf3798be6abcfb7cda1b0210f694d5818598538
and comprises **346B / 79 i386 instructions / 8 E8 / 19 PE HIGHLOW**.
The new real source is **src/WindowSecondsClock346.cpp**.

The code locks the existing LockRegistry slot 5 and selects between two
real timing backends. The high-precision branch samples
QueryPerformanceCounter, subtracts the 64-bit WindowState origin,
converts the signed numerator and unsigned frequency to doubles and
computes elapsed seconds. The two original conversion symbols are
__ltod3 and __ultod3, each resolving to the same physical native
0x00542E00 head. Both original Windows IAT and conversion callsites
are independently pinned. The clamped clock offset is the real
WindowState member at +0x20E0, not a made-up global time value.

The timeGetTime fallback converts an unsigned DWORD to double through
the actual two-element correction table at original 0x0056CDD0,
with elements **0.0 and 4294967296.0**. The maintained source uses
a local static const double[2] with these genuine values, rather than
emitting a compiler-invented XMM array. It subtracts the clamped clock
offset multiplied by the genuine original **1000.0** value and returns
seconds. The game does not initialize the LARGE_INTEGER before calling
QueryPerformanceCounter, because the API writes that output.

The decisive machine-code difference was local lifetime: the original
shares **one actually-used double elapsed** across the disjoint
performance-counter and millisecond branches. Using separate true but
independent temporaries generated a complete 346B/79-instruction
candidate with the correct call/data sites but only 224/238 ordinary
byte agreement. Sharing the used arithmetic value restored the native
stack slots. Multiple actual MSVC compile attempts varied timer
initialization, signed/unsigned conversions, and temporary arithmetic.
No synthetic local, handwritten opcode, NOP or jump was used.

Pinned MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc generates **346/346B whole exact**.
All original **8/8 E8 and 19/19 PE HIGHLOW** physical positions and
target roles (including WindowState member relocation addends) match,
as do all **238/238 ordinary bytes**. The independent original-native
verifier **scripts/verify-window-seconds-clock346-native.py**
attests complete SHA, IAT targets, 64-bit helper aliases, the real
original double table, and both original E8 caller sites in the
previously exact 645B Card-clock Boss.

Only this changed source was cold rebuilt, not the entire graph:

    window_seconds_clock_boss_346: exact (346/346 bytes)
    Exact replay: 1/1 units, 1 cold objects

Reproduce:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowSecondsClock346.cpp
    scripts/repo-python scripts/verify-window-seconds-clock346-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target

**One new game-authored original whole-exact function, 346 native
.text bytes.** The upstream 645B Card clock, existing lock/CRT
functions and folded helpers are not double-credited. Whole-game
linking and playable runtime validation have not been performed.
