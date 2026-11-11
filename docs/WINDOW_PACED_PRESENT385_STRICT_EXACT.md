# Window paced D3D9 Present Boss 385B — complete strict original exact

The Japanese Steamless TH20 v1.00a original at 0x00419A50 is a
**385B /94-i386 game-authored frame pacing and device presentation
Boss**, whole original SHA-256
0df260cff4e294279f3836178fe78ef891f39c2ebd0f86b977d4ef175fbdd19a.
The complete native has 12 genuine E8 and 17 physical PE HIGHLOW
fields, including direct Win32 Sleep import at +0xBF.

Maintained source: src/WindowPacedPresent385.cpp, a real member of
the shared borrowed NativeWindowFrameScheduleView. It samples the
already exact 346B Window seconds clock and updates the actual
WindowState +0x20C8 current-time field. Only when process pacing
flag at 0x005C4F89 equals 1, actual elapsed time is shorter than
1.0/60.0 seconds but longer than the genuine lower-threshold
double at 0x0056CD50, it calculates a real millisecond sleep budget
using original 1.0/60.0, 1000.0 and bias at 0x0056CD80. It calls
Win32 Sleep only for strictly positive budgets.

The same game function updates WindowState frame clock +0x20F0,
runs the authentic 574B screenshot/scene function, and uses a
separately scoped true IDirect3DDevice9 Present with complete
Renderer/Graphics device-loss, Reset and recovery behavior. The
device pointer for Reset is retrieved independently; the actual
D3D9 presentation record resides at 0x005C4E24 and process reset
status is written as 2 at 0x005C586C. It then updates the actual
previous-frame time at +0x20E8 and calls the independently exact
32B Window clock dispatcher.

Pinned MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc emits the **entire original 385/385B
on the first complete source compilation**. It reproduces
**94/94 instructions, all 12 E8 and 17 PE HIGHLOW physical
positions and target destinations**, all **269/269 ordinary
original bytes**, and the three genuine compiler NOPs at
+0xC3, +0xDD and +0x17C. No artificial code, dummy locals or
padding. The source was subsequently attached to the actual
Window receiver with identical native bytes.

Source-specific 1/1 cold replay:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowPacedPresent385.cpp
    scripts/repo-python scripts/verify-window-paced-present385-native.py

The changed shared Window header required only independent 1/1
replays of the already exact 31B RepeatCounter and 164B no-wait
Present units. The original 574B screenshot/scene callee was subsequently made
exact, but the 884B scheduler parent is still NONEXACT, so no byte credit flows
into those parent functions.

**One new distinct whole-exact game-authored function /385B**
is credited. The separate whole-exact 164B no-wait frame presenter
and 346B clock are not duplicated.

The paced Window frame controller at original 0x0041A030 is now
[whole 370B strict exact](WINDOW_FRAME_PACED_BOSS370_STRICT_EXACT.md),
with a physical original E8 into this already exact 385B Presenter.
Each distinct game function is credited only once.
