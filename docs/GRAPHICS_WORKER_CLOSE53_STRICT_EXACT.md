# Graphics Worker close 53B — whole strict native exact

Original TH20 Japanese Steamless v1.00a at 0x004D9E30:
53 bytes /17 i386 instructions, complete native SHA-256
6b70ab34d6c494c1230f2f3328ddc8907caee1ed9cfab5fc01ce7fd62732f903.
It has three original E8 calls and one PE HIGHLOW data reference.

Maintained src/GraphicsWorkerClose53.cpp uses the authentic Graphics
owner. It reports the original SyncCloseSubThread diagnostic string
from physical 0x00571E48, then operates on the real Worker at
Graphics+0xD90 using close_and_detach and close_and_join. The source
naturally emits the original MSVC NOP after the final Worker call.
The Worker and diagnostic method bodies are separate existing
functions and are not credited again.

Pinned MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc reproduces the full 53/53B
original body: 17/17 instructions, all three E8 sites/destinations
(0x0040C6B0, 0x004BA8B0, 0x0040BCF0), the original HIGHLOW
diagnostic-string pointer, and 37/37 ordinary bytes.

Only this newly changed source was cold replayed:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/GraphicsWorkerClose53.cpp
    scripts/repo-python scripts/verify-graphics-worker-close53-native.py

One new distinct game-authored original exact head /53 bytes.
Its already exact 370B, 433B, 583B Window callers are retained.
