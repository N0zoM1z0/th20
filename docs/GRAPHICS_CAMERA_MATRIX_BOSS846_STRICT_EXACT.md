# Graphics D3DX9 camera matrix Boss 846B — strict whole-native exact

Japanese Steamless TH20 v1.00a original 0x004DA1F0:
**846 bytes /194 x86 instructions**, full original SHA-256
6f96ef09b5688b5ca16322fd909a925ac579bbc15e3f7e817c0aa7fd798a0a2c.
The original body contains **seven genuine E8 and twenty PE
HIGHLOW fields**. Maintained game source:
src/GraphicsCameraMatrixBoss846.cpp, using the existing
NativeGraphicsModeAction and real ViewportState owners.

This Boss builds actual camera Vector3 eye, target and up vectors
and computes D3DX9 View and Projection matrices. It uses unsigned
32-bit viewport x/y/width/height, the source viewport and actual
current ViewportState fields, and the existing Vector3(float,float,float)
native constructor at 0x00422DD0 exactly three times. The z-distance
comes from the genuine native float sqrt helper at 0x00439850
applied to the viewport FOV/2; eye and target X/Y add the true
width/height half offsets. The up vector is (0,-1,0).

It then calls the authentic imported
D3DXMatrixLookAtLH at 0x005406BA and D3DXMatrixPerspectiveFovLH
at 0x005406C0. The perspective uses the genuine field-of-view,
unsigned aspect ratio, near plane 1.0 and far plane 10000.0.
The original four-byte data constants come from locked native
PE addresses 0x0056C8D0, 0x0056C8CC, 0x0056E0F4 and 0x00571EA0.

**Original unsigned conversion evidence:** Pinned MSVC x86
compiles cast<float>(uint32_t) to x86 cvtsi2sd with an SSE
double correction table and later cvtsd2ss. The native PE table
at 0x0056CDD0 has the exact double entries 0.0 and 2^32.
The new C++ source naturally emits the compiler-owned
__xmm@41f... constant for the same original table at all
eleven physical HIGHLOW sites. The canonical manifest anchors
its symbol to the real PE address; no handmade conversion code,
uninitialized scratch, dummy locals, inline assembly, or NOP
was inserted.

The **first full C++ source probe** with pinned MSVC 19.44 x86
/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc matched the complete **846B/194 instructions,
all 7/7 E8 and 20/20 PE data physical fields/targets, and
all 738/738 ordinary original bytes**. The source was
subsequently accepted as a strict canonical unit, independently
replaying **846/846B exact**.

Only the changed file was cold replayed:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/GraphicsCameraMatrixBoss846.cpp
    scripts/repo-python scripts/verify-graphics-camera-matrix846-native.py

The 194B D3D9 transform stage and 284B Graphics viewport
caller were already independent whole-exact functions and
remain separate. The sqrt helper is treated as a native callee;
this work does not credit it as a new authored original head.
One distinct new **846B game-authored whole exact** Boss head.

The native 35B sqrt adapter at 0x00439850 subsequently reached
[35/35B original source exact](GRAPHICS_CAMERA_SQRT_ADAPTER35_SOURCE_EXACT_ORIGIN_REVIEW.md),
but its compiler/CRT authorship is under review and **not credited**
as a new game-authored exact head. The camera Boss owns only its
own 846 original bytes.
