# Window D3D9 Present/Reset 164B — whole original strict exact

Original TH20 Japanese Steamless v1.00a head 0x004199A0,
**164 bytes /49 i386 instructions**, SHA-256
88a1ce526edc201f959f36a1e0656b9287e053884985441bc3bde9a9354e906e.
This game Window frame path has **nine original E8 calls** and
**eight original PE HIGHLOW data pointers**.

Maintained natural C++20: src/WindowPresentNoWait164.cpp, extending
the existing borrowed Window frame receiver in
src/NativeWindowFrameScheduleView.hpp. It:

- Calls original 574B screenshot/scene updater at 0x00419760.
- Borrows the real Graphics owner and a real IDirect3DDevice9,
  executing device Present with four null parameters.
- On a negative Present HRESULT, calls original Graphics recovery,
  Renderer device loss, obtains a **new** D3D9 device pointer for
  Reset using the genuine presentation record at 0x005C4E24,
  calls Renderer restoration, Graphics completion and window reset
  initialization, and writes original status 2 at 0x005C586C.
- Always runs the previously exact 32B Window/frame clock dispatcher.

The first C++ candidate had correct complete call/data roles but
was only **163B/48 instructions**; its one missing instruction was
the original compiler-emitted NOP after the scene call. Giving
the Present operation its own genuine lexical scope restores that
NOP naturally, while keeping separately acquired Present and Reset
D3D9 device pointers restores the original 0x14-byte stack frame.
Sixteen combinations of actual scope/device lifetimes were compiled
to distinguish these effects. No hand-inserted NOP, padding, unused
locals or invented game state is present.

Pinned MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc now emits **164/164 bytes exactly**:
49/49 x86 instructions, all nine E8 plus eight HIGHLOW
relocation fields at the **exact physical native positions**,
all original targets, and **96/96 original ordinary bytes**.
The original NOP is at +0x11; the dispatch-return NOP at +0x9F.

Independent native proof:
scripts/verify-window-present-no-wait164-native.py.
The 574B screenshot callee remains source-present/NONEXACT, but
this caller is its own distinct original whole-exact function.
The already exact 32B clock dispatch is not re-credited.

Source-local cold replay:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowPresentNoWait164.cpp
    scripts/repo-python scripts/verify-window-present-no-wait164-native.py

Only the shared-header-affected 31B RepeatCounter unit additionally
needed a separate 1/1 cold replay; the 884B and 574B nonexact
source consumers were compiled/compared alone, not the full graph.

One new distinct game-authored exact original head, **164 bytes**.
