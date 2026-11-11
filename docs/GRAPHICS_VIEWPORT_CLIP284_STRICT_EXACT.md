# Graphics viewport/clip switch 284B — whole native strict exact

TH20 Japanese Steamless v1.00a original 0x0041DCE0,
**284B /67 i386**, SHA-256
84fc878beeb6de276535c36c79312e1be8f1d574305fe2c749ba55d90afbd857.
It is a game-authored Graphics member used by fifteen original
callers, including the newly exact 433B, 583B and 370B Window
controllers.

Maintained C++20 source is src/GraphicsViewportClip284.cpp,
a member of the existing shared NativeGraphicsModeAction receiver,
not a new Graphics clone. It selects the real 0x16C-stride
ViewportState at Graphics+0x278, stores current_viewport at +0xB00,
prepares the unadjusted viewport member at ViewportState+0xE0,
invokes the real device viewport preparations at 0x004DA1F0
and 0x004DA120, and calls the D3D9 SetViewport vtable method
using the adjusted viewport at +0x104. It copies actual selected
X/Y offsets into the Renderer floating-point fields +0xD0/+0xD4,
copies its third point coordinates to +0xC8/+0xCC, and resets
Graphics+0xB04 to zero.

The already strict exact 280B sibling at 0x0044F720 shares the
same receiver ABI but differs meaningfully: it prepares the
adjusted viewport, selects a different point element, and accepts
an additional argument. Starting from that existing proven C++
source and expressing these genuine differences produced a
complete **284/284B exact native body on the first compile**,
with **67/67 instructions, 2/2 E8, 4/4 PE HIGHLOW physical
positions and target identities, 260/260 ordinary bytes**.
No added filler, dummy locals or manual instructions.

Compiler: pinned MSVC 19.44 x86 /std:c++20 /Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc.

Only the new source was cold replayed:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/GraphicsViewportClip284.cpp
    scripts/repo-python scripts/verify-graphics-viewport-clip284-native.py

The previously accepted 280B sibling is independently attested,
not re-credited. One new distinct game-authored original exact
head / **284 executable bytes**. The 884B Window scheduler remains
a separate source-present but NONEXACT parent.
