# Graphics D3D9 transform stage 194B — whole original strict exact

Locked original Japanese Steamless TH20 v1.00a head 0x004DA120:
**194B /55-i386**, full original SHA-256
47f84290a4acb9348b8c74c3de8dad80751aa344472f98d129353ba8afafa011.
The original body contains **3 E8 and 7 physical HIGHLOW fields**.

The maintained src/GraphicsPrepareDevice194.cpp implements the
actual Graphics device matrix state. It flushes real Animation
Renderer draw commands when an owner exists, then fetches the
global process Graphics device twice and performs the genuine
D3D9 SetTransform calls for the View and Projection matrices
stored at ViewportState+0x60 and +0xA0. It propagates the first
ViewportState point into the real Animation Renderer fields
+0xC8/+0xCC when present.

The initial whole source compiled to 190B instead of 194B.
Its two device accesses used this->get_device(), which generates
three-byte register reloads. The original accesses the actual
global Graphics owner at **0x005C4D40**, for which MSVC generates
five-byte immediate mov instructions. Replacing those two
expressions with process_graphics.get_device() precisely recovers
the four native bytes; the original first-point array indexing
naturally generates the same imul-by-zero instructions.

Pinned MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc reproduces all **194/194
bytes**: native 55 instructions, original 3 E8 and 7 data
relocation physical sites/targets and **154/154 ordinary bytes**.
There are no fake locals, padding or manually inserted NOPs.
The related already-exact 284B viewport clip caller is not
recredited.

Single-source strict replay only:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/GraphicsPrepareDevice194.cpp
    scripts/repo-python scripts/verify-graphics-prepare-device194-native.py

One new distinct game-authored original whole-exact head, 194 bytes.
The separate 846B Graphics camera recompute source at 0x004DA1F0
is a substantial independent open target.
