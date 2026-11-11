# Window device timestamp pipeline: 113B whole strict exact

The immutable TH20 Japanese Steamless v1.00a game original contains
the native 113B /34-i386 Window frame timestamp pipeline at 0x004AC0E0,
SHA-256 9ad2cf3886f3d23a07838f2577d9298bb21c6c548c69b39fd4fdf448edc22f6e.

The source src/WindowFramePipeline113.cpp recovers the real three-step
process: a helper at 0x004AC170 fills and returns a temporary 8B time pair
stored at real device offset +0xD0; a separate 0x004AC200 helper computes
the 64-bit time value stored at +0xD8; the 0x004AC270 helper expands it
into the device's existing display/breakdown fields at +0xE0. The
function returns the actual device +0xD0 pair pointer in EAX. The
type and return value are now declared in
src/NativeWindowFrameClockView.hpp, rather than the earlier incorrect
void method prototype. The entire 437B parent and 32B dispatch remain
independently exact with this corrected ABI.

The first natural source compiled to 133B/40 instructions with extra
security-cookie prologue/epilogue, although the original 113B function
has no GS cookie or HIGHLOW fields. MSVC /sdl forces the cookie even if
/GS- appears earlier. Selecting the **original-observed source security
mode /GS- without /sdl**, while retaining C++20 /Od /Ob0 /Gy /Zl
/arch:SSE2 /fp:precise /EHsc, naturally produces the entire original
**113B /34 instructions**. All **three original E8 opcode offsets and
callee destinations**, and **101/101 ordinary bytes** match; zero
DIR32 fields exist in either source or original. No manual instruction,
NOP, duplicate pointer wrapper or discarded return value was inserted.

The original game parent at 0x004ABD50 calls this native head at +0x1A7.
The independent original-only verifier
scripts/verify-window-frame-pipeline113-native.py pins the complete
original SHA, three original E8 destinations and code boundaries,
original parent callsite and the three canonical compiler receipts.
Only these real affected sources were cold compiled:

    window_frame_pipeline_113: exact (113/113 bytes)
    window_frame_device_clock_boss_437: exact (437/437 bytes)
    window_frame_clock_dispatch_32: exact (32/32 bytes)
    Exact replay: 3/3 units, 3 cold objects

Reproduce:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowFramePipeline113.cpp --source src/WindowFrameDeviceClock437.cpp --source src/WindowFrameClockDispatch32.cpp
    scripts/repo-python scripts/verify-window-frame-pipeline113-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target

One new game-authored whole-exact original head, **113 native bytes**.
The 437B and 32B parents are not credited again; the child date/time
conversion methods at 0x004AC170, 0x004AC200 and 0x004AC270 were subsequently [recovered as whole exact source](WINDOW_FRAME_TIME_LEAVES109_NATIVE_EXACT.md) with authorship held review. A playable game binary has not been linked or tested.
