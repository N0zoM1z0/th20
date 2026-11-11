# Three Window time-wrapper children: 46B, 42B, 21B source exact

Target: Japanese Steamless TH20 v1.00a executable with locked SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

The original 113B timestamp pipeline at 0x004AC0E0 calls three separate
time helpers. New source in src/WindowFrameTimeLeaves109.cpp matches
each complete function byte-for-byte through pinned MSVC 19.44 x86:

| Original head | Behavior and real callees | Complete native |
| --- | --- | --- |
| 0x004AC170 | Get CRT native ticks, construct an eight-byte time-pair temporary, then assign it into the destination | **46/46B**, 18 i386, 3 E8 |
| 0x004AC200 | Convert an eight-byte pair to a 64-bit time value with two genuine 8B intermediate objects | **42/42B**, 17 i386, 3 E8 |
| 0x004AC270 | Pass the real output and time input to CRT time-breakdown helper 0x0055139C | **21/21B**, 10 i386, 1 E8 |

All seven original E8 source positions and independent physical
destinations match, as do all **109 non-relocation native bytes**.
The three original whole-body SHA-256 values are:

- 46B: 7129bd713e1005057ae65f87ab760622e2e9dee565e275730786b18ed9c20b0a
- 42B: f2807246a258ad6b62875747413f8099ec02ab47b6b2c86ad81666214718c570
- 21B: d25a69e45b400e7e84fc251062ba62e839abdd04fc7f682d7f6540e1593c5b83

The native 46B uses two real external 32B copy methods (constructor
at 0x00446DA0, assignment at 0x00447D20). Storing the native tick
value and assigning the result of an explicit **temporary time-pair
construction** is essential. An ordinary named-local assignment
compiled to 48B or 45B and lacked native NOP at +0x26. The natural
temporary expression generates that instruction automatically and
yields the exact 46B/18-instruction original without inserted filler.
The 42B method similarly requires direct nested construction and
conversion, rather than an extra local pointer receiving the returned
intermediate result.

These time wrappers do not use an original GS security cookie. They
use source-scoped compiler /GS- without /sdl, while leaving the
pre-existing 437B and 32B providers on their own accepted /sdl mode.
The shared NativeFrameTimePair definition in
src/NativeWindowFrameClockView.hpp remains a trivial 8B pair so
the already accepted 113B parent still emits its original two-word
copy rather than a new constructor call. Only a separate borrowed
8B value view in the 46B helper declares the two actual native
out-of-line copy operations.

Independent proof is in
scripts/verify-window-frame-time-leaves109-native.py. Only the
four affected source files were cold rebuilt:

    frame_time_pair_read_46: exact (46/46 bytes)
    frame_time_u64_convert_42: exact (42/42 bytes)
    frame_time_breakdown_21: exact (21/21 bytes)
    window_frame_pipeline_113: exact (113/113 bytes)
    window_frame_device_clock_boss_437: exact (437/437 bytes)
    window_frame_clock_dispatch_32: exact (32/32 bytes)
    Exact replay: 6/6 units, 4 cold objects

Reproduce:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowFrameTimeLeaves109.cpp --source src/WindowFramePipeline113.cpp --source src/WindowFrameDeviceClock437.cpp --source src/WindowFrameClockDispatch32.cpp
    scripts/repo-python scripts/verify-window-frame-time-leaves109-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target

All three source wrappers are complete **whole-original exact** at
the compiler level. Their distinction from generated chrono/CRT library
source is not yet proven, so function origins remain **under review**.
They are *not* entered in the game-authored matches ledger and do not
increase authored game byte totals. The three existing game-authored
parents and all their accepted bytes remain exact with no duplicate credit.
