# Window frame controller 433B Boss — whole strict exact

Original TH20 Japanese Steamless v1.00a at **0x00419C20** has
**433 bytes / 110 x86 instructions**, SHA-256
654fba82d5f91a2b76d3fafe839c887812ab20086ae9f7a3a35a58b42432df76.
The complete native has **15 E8 calls** and **18 PE HIGHLOW
fields**. Maintained src/WindowFrameControllerBoss433.cpp is a
method on the existing borrowed Window frame receiver.

The game code manages the next-update deadline (WindowState +0x20D8)
and a 1.0/60.0 seconds interval, Renderer queued draw flush,
viewport selection, the true 611B FunctionChain update and 587B draw
callbacks, and both error exits. When the genuine 8-bit frame-skip
counter permits drawing it executes D3D9 BeginScene, Renderer staging
reset, **true 32-bit global 0x005C5AF8 = 0xFF**, disables fog,
draws the FunctionChain, flushes again, performs D3D9
SetTexture(0, nullptr) and EndScene, and calls the separate 884B
Window frame scheduler. It records elapsed seconds using the
already exact 346B Window clock and calls the existing folded
13B frame-end method, not claiming duplicate byte credit.

The first real source compiled to 466B because a logically
redundant extra frame-time inequality was evaluated twice.
Removing that test restored the native frame interval loop,
yielding 437B/110 instructions. Exploring genuine early-return
scope variants recovered the original two error-return branches.
A separate lexical scope around the frame-end member call
naturally adds the original MSVC NOP at +0x1AA.

The final three missing bytes were a real native type error:
the original writes a DWORD to global 0x005C5AF8, not a byte.
Restoring its actual uint32_t type closes the entire function.

Pinned MSVC 19.44 x86 C++20 profile
/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc emits **433/433 exact original bytes**, all
**15/15 E8 and 18/18 PE data relocations** at native physical
positions and targets, and **301/301 ordinary original bytes**.
There are no dummy locals, handwritten NOPs or padding.

Only source-local replay, not a full cold graph:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowFrameControllerBoss433.cpp
    scripts/repo-python scripts/verify-window-frame-controller433-native.py

One distinct game-authored original whole-exact head, **433 bytes**.
The 884B Window scheduler remains separately NONEXACT.

Its sibling synchronized Window frame controller 0x00419DE0 is now
[whole 583B strict exact](WINDOW_FRAME_NO_WAIT_BOSS583_STRICT_EXACT.md),
with a separately authentic deadline clock and 1ms Sleep stage.
These are distinct original physical game functions.
