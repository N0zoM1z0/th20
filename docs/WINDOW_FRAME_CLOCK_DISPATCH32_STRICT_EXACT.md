# Window/Frame clock dispatch 32B — whole native strict exact

The pinned Japanese TH20 Steamless v1.00a executable has a complete
**32B /11 i386** game frame dispatcher at 0x004193C0, SHA-256
fc38d8ab189161a0f23b5f052a00e5e0e52c747701e01b05bca72d045f2d125a.

The source **src/WindowFrameClockDispatch32.cpp** is a natural C++20
translation: it reads the real process frame device pointer twice from
the original global 0x005C4A00, conditionally calls the device's
frame_seconds_4abd50 method, and then always invokes the separate
original 37B Card clock callback at 0x00487560. The first device
method is a **437B original at 0x004ABD50 (subsequently whole strict exact)**. The
Card clock callback and its 645B settlement parent have already been
accepted whole-exact and are not counted a second time.

Original byte-level targets: two PE HIGHLOW fields at +0x05 and +0x0E
both point to 0x005C4A00. Genuine original E8 calls at +0x12 and
+0x18 point to 0x004ABD50 and 0x00487560 respectively. The pinned
MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc naturally generated **32/32B full exact**,
with all four physical relocation offsets and targets and all
**16/16 ordinary bytes** identical to the SHA-pinned native body.

The independent **scripts/verify-window-frame-clock-dispatch32-native.py**
verifies the original complete SHA and native call/data fields, source
COFF, exact protected receipt, and still-exact separate Card callback.
Only this translation unit was cold rebuilt, not the game graph:

    window_frame_clock_dispatch_32: exact (32/32 bytes)
    Exact replay: 1/1 units, 1 cold objects

Reproduce:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowFrameClockDispatch32.cpp
    scripts/repo-python scripts/verify-window-frame-clock-dispatch32-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target

This credits **one new distinct game-authored head /32 native bytes**.
The 437B device tick owner was subsequently [reconstructed whole strict exact](WINDOW_FRAME_DEVICE_CLOCK437_STRICT_EXACT.md). Other larger Window/frame scheduling parents remain open.
