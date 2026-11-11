# Graphics camera sqrt wrapper 35B — whole source exact, origin review

Original TH20 Japanese Steamless v1.00a executable at 0x00439850
contains 35 bytes /13 x86 instructions, full SHA-256
883a31db55344f543fa8f0c7823bf4aa241c5e0db38e7dac33a591917ce25f7a.
Its one original E8 opcode at +0x11 calls physical 0x00550000
(sqrt of a double). There are zero PE HIGHLOW data fields.

The real 846B D3DX Graphics camera Boss calls this wrapper to
calculate the square root of a camera field-of-view scale.
The new source src/GraphicsCameraSqrtAdapter35.cpp simply
casts float to double, evaluates std::sqrt(double), then
converts the result back to float. Pinned MSVC 19.44 x86 C++20
/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
naturally emits the complete original **35/35 bytes**,
including x87 float return preparation, all 31/31 ordinary
bytes and the original single E8 relocation. One source
was cold replayed, 1/1 exact. The distinct 846B camera Boss
remains whole 846/846 native exact.

**Source exact does not imply game-authored origin.** This is
an archetypal standard math wrapper, possibly generated from
library templates/CRT; the author provenance remains unknown.
It is marked origin=unknown and disposition=review, and is
not entered in config/matches.csv. Accordingly **zero new
game-authored original heads or bytes are credited**.
Other game-owned callers cannot claim its bytes as their own.

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/GraphicsCameraSqrtAdapter35.cpp
    scripts/repo-python scripts/verify-graphics-camera-sqrt35-native.py
