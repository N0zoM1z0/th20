# Renderer Window capture pending loop 88B — whole strict exact

Native TH20 Japanese Steamless v1.00a, original 0x0041BFC0:
**88B /28 x86 instructions**. Complete original SHA-256
28b4d96cdaad162015839d6d31defaf58be14a5b964128fb603fd78617baa468.

The function is called by the 574B screenshot/scene Boss at 0x00419760.
It examines exactly four authentic 40-byte surface-blit commands
beginning at Renderer receiver +0x18. Any entry with nonnegative
file_index is submitted to the real Renderer 439B D3D9 surface blit
at 0x0044BB10, and its file_index becomes -1. The record is borrowed
from the actual process Renderer, not synthesized or allocated.

Maintained sources: src/NativeWindowCaptureRenderer.hpp and
src/WindowCapturePending88.cpp. They reuse the previously strict-exact
NativeSurfaceBlitCommand and NativeRendererSurfaceBlitView interface.
The dependent 574B source now includes the same borrowed Renderer
header in place of its old declaration-only shadow. The 574B source
remains NONEXACT, with its verified 20/20 E8 and 12/12 data roles intact.

Pinned MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc naturally emits the original **88/88 bytes**:
28/28 instructions and 84/84 non-relocated original bytes.
Its single true E8 opcode occurs at +0x3E (REL32 at +0x3F),
targeting original 0x0044BB10; original data relocations are zero.
No dummy locals, manual NOPs or control-flow padding are present.
The actual 439B callee was accepted previously and is not credited again.

Source-bounded cold replay and native SHA evidence:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowCapturePending88.cpp
    scripts/repo-python scripts/verify-window-capture-pending88-native.py
    scripts/repo-python scripts/verify-window-snapshot-scene574-native-frontier.py

One distinct game-authored whole-exact original head /88 original bytes,
with a single new exact unit. The enclosing 574B and 884B Window
parents remain NONEXACT, so none of their parent bytes are credited.
