# Window snapshot/scene update 574B — entire typed source, NONEXACT

The immutable original TH20 Japanese Steamless v1.00a executable is pinned
to SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.
The true Window scene/screenshot update function at 0x00419760 is
574B / 132 i386 with complete SHA-256
12c08490acf889b9d6ef21f67e6f85051f7eeb7bc00bb7b576450899b48ead57.
Its full original code has exactly **20 native E8 calls and 12 physical
PE HIGHLOW fields**.

The maintained source src/WindowSnapshotScene574.cpp reconstructs this
actual game behavior as compilable C++20, not a call-count placeholder:

- Invokes original Renderer/Animation preparation at 0x0041BFC0 from the
  true Renderer process pointer at 0x005C0028.
- Reads the original third InputButtonState pointer from original global
  0x005B889C and tests pressed mask 0x40000. The native source takes
  integer index 4, shifts it by one to form a **byte offset of 8**;
  the earlier hypothesis erroneously treated 8 as a pointer-array
  index. Reading the third 32-bit pointer restores the actual owner.
  It then checks original snapshot prohibition flag bit 6 at 0x005B87E8.
- Constructs a real std::filesystem::path from the existing WindowState
  user_data_directory at physical address 0x005B67E1, appends original
  ASCII snapshot subdirectory from 0x0056CAAC, and creates it using
  the genuine filesystem::create_directories implementation.
- Searches indices 0 to 9,999, formatting the genuine 14-byte
  th20_%.3d.png original filename pattern at 0x0056CABC into a
  256-byte buffer, reconstructing the root/snapshot/filename path.
  Each candidate is converted to std::string and checked with the
  already accepted original game_file_exists_4107a0 helper.
- When an unused filename is found, invokes the original Graphics
  screenshot method at 0x004DE040 with the genuine global Graphics
  owner at 0x005C4D40 and the narrow filesystem path.
  Natural std::string/path destruction and MSVC EH scopes remain
  present, with no replacement allocation or fabricated cleanup.

## Actual MSVC source experiments

Pinned MSVC 19.44 x86 C++20
/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
was used for source-only probes. Multiple actual source forms
varied the input pointer array index vs byte offset, explicit null
fallback, and original snapshot bit test. The initial code compiled
to **541B /123 instructions** with all 20 E8 and 12 data roles but
only 59 ordinary positional bytes agreeing. The corrected native
input pointer (+8 bytes, not pointer entry 8) and explicit fallback
compiled into the chosen current **551B /125 instructions**, preserving
the full authentic snapshot control path and improving the ordinary
positional agreement to **88 bytes**.

The current source COFF has **20/20 original E8 callee destination
roles and 12/12 PE data destination roles in native order**; it has
only **1/20 original E8 and 3/12 data physical field positions**.
The original remains **574B/132 instructions**, so this new 551B
candidate remains **NONEXACT**. No full-original 574B game byte credit
is claimed. The surviving debt concerns native input/graphics
branch lowering, local stack and EH lifetime and pathname evaluation.
No handwritten NOP, artificial local, source byte patch or unused
call was introduced to force the original size.

Independent evidence at
scripts/verify-window-snapshot-scene574-native-frontier.py checks
the complete immutable original SHA, all 20 genuine PE E8 physical
sites and original call destinations, all 12 PE HIGHLOW locations
and real data destinations, both original narrow literal strings,
the complete current compiler COFF role sequence, and the exact
31B active Window RepeatCounter child.

The actual parent 884B Window frame scheduler at 0x004193E0
already uses this same Window receiver; src/WindowFrameSchedulerBoss884.cpp
now calls update_scene_419760 directly through the shared authentic
NativeWindowFrameScheduleView, rather than casting to an unrelated
borrowed GraphicsState type. The 884B parent's previously pinned
32-E8/21-HIGHLOW full original role graph is still NONEXACT and
has been independently rechecked.

## Bounded verification and remaining work

Only the two changed nonexact source functions were independently
compiled; the shared-header-affected accepted 31B Window getter
was source-scoped cold replayed 1/1 and remained exact. All other
exact children remain on protected prior receipts. No full graph
cold replay occurred.

    nice -n 15 scripts/compile-probe.sh src/WindowSnapshotScene574.cpp build/gptweb20-window574/WindowSnapshotScene574.obj /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
    nice -n 15 scripts/compile-probe.sh src/WindowFrameSchedulerBoss884.cpp build/gptweb20-window884/WindowFrameSchedulerBoss884.obj /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowActiveRepeat31.cpp
    scripts/repo-python scripts/verify-window-snapshot-scene574-native-frontier.py
    scripts/repo-python scripts/verify-window-frame-scheduler884-native-frontier.py
    scripts/repo-python scripts/validate-tracking.py --require-target

The entire 574B screenshot function and enclosing 884B Window
frame scheduler are both **game-authored source-present, NONEXACT**;
neither is accepted in config/matches.csv. Current exact totals
should be retrieved from the live authoritative script, not copied
from this historical frontier.
