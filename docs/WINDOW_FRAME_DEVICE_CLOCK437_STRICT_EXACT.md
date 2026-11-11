# Window device frame-rate accountant 437B — whole strict exact

The selected Japanese Steamless TH20 v1.00a original target has the
complete game frame-accounting method at 0x004ABD50. Its original
**437B /105 i386 instructions** have SHA-256
8df209582a9bf10136297e2ab5dd135e6911eb7eab5553ff5355d33162ca7bb7.

The maintained **src/WindowFrameDeviceClock437.cpp** reconstructs
the real device/frame metrics at receiver +0x18 through +0x38, using
a borrowed non-allocating view with a 0x18 offset to the actual known
fields. These store last clock sample, slow-frame count, sample count,
two accumulated double times, and current FPS float. The frame routine
samples the now exact **346B WindowState clock**, clamps backward
time, and processes intervals of at least the original **1.0 seconds**.
The sample count is converted from unsigned 32-bit to double through
the actual two-double 0 and 2^32 correction table at original
0x0056CDD0, before division by elapsed seconds and conversion to FPS.

The original **65.0 FPS** threshold increments or resets the slow
count. If the real GameController exists and neither original flags
bit4 nor bit2 is set, the accumulated realtime value increases by the
original **60.0**, while presented time increases by 60.0 or by the
float FPS depending on the original **57.0 FPS** threshold. The
GameController flag bit8 is then cleared; the per-window frame
count is reset and advanced by the original process byte at 0x005C4F84
plus one. The final call is the real borrowed device member method at
0x004AC0E0, an independently open 113B pipeline function. The
437B function returns 1.

The initial meaningful C++ implementation compiled to **444B /110
instructions**, containing the actual two E8 and fourteen data roles,
but extra receiver alias pointer operations and an unsuitable pooled
XMM conversion table. Replacing the alias with direct typed access to
real used frame fields, restoring the member ABI for the pipeline
call and expressing the genuine indexed 0/2^32 conversion table
produced the full original **437B /105 i386**.
It matches all **2/2 original E8** and **14/14 PE HIGHLOW** physical
sites and target roles, plus **373/373 ordinary machine-code bytes**.
No dummy local, inserted NOP, byte patch or hand-coded assembly was
used. The C++ source corrects the earlier 32B dispatch declaration
to reflect the genuine integer return ABI, rather than leaving
inconsistent method signatures across translation units.

The common borrowed interface lives in
**src/NativeWindowFrameClockView.hpp**; it defines no new device
storage or vtable. The dedicated
**scripts/verify-window-frame-device-clock437-native.py**
attests the complete original SHA, all call/data source symbols and
their original target addresses, original frame constants, and
canonical strict source receipts.

Scoped cold replay was limited to the new 437B source and its
affected 32B dispatch source, two MSVC objects:

    window_frame_clock_dispatch_32: exact (32/32 bytes)
    window_frame_device_clock_boss_437: exact (437/437 bytes)
    Exact replay: 2/2 units, 2 cold objects

To reproduce:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowFrameDeviceClock437.cpp --source src/WindowFrameClockDispatch32.cpp
    scripts/repo-python scripts/verify-window-frame-device-clock437-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target

**One newly credited game-authored original head /437 native bytes**.
The 32B dispatch, 346B WindowState seconds clock, and 645B Card time
settlement are already separately credited, with no duplicate bytes.
The 113B frame-pipeline function and still-larger Window scheduling
Bosses remain open, and no playable full-game executable is claimed.
