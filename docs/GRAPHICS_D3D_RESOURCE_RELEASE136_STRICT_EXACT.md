# Graphics D3D9 resource release 136B — strict whole-original exact

Original Japanese Steamless TH20 v1.00a physical 0x004DD840
is **136B /35 x86 instructions**, locked whole original SHA-256
1d64e1c20d778cd77e8f322d2c08780602a512c030de01df187c3ca6694f05f6.
It has **thirteen native PE HIGHLOW data fields and no E8 calls**.
The three Release operations are genuine virtual COM calls at
vtable +0x08 and not direct E8 calls.

Maintained src/GraphicsReleaseD3DResources136.cpp reconstructs
the real Graphics owner and the native D3D9 resources. The
original PE absolute resource pointers are process Graphics
base 0x005C4D40 plus actual member offsets +0x19C, +0x1A0
and +0x1A4, corresponding to Graphics.resource_19c,
resource_1a0 and resource_1a4. For each live IUnknown resource,
the source calls the real COM Release method and clears the
slot. It also clears primary resource_19c unconditionally,
exactly as the locked original code does.

The source naturally compiled to **136/136B and 35/35 i386**
on the first complete pinned MSVC 19.44 x86 C++20 probe:
all thirteen HIGHLOW fields at their native physical offsets,
all 84/84 ordinary bytes and real vtable call positions.
The COFF relocations anchor the actual process_graphics
symbol at 0x005C4D40 and retain its original +0x19C, +0x1A0
and +0x1A4 member addends. Using the already-relocated
effective PE pointer as a symbol base would incorrectly
add those offsets twice and is not allowed.

Only this source was locally cold replayed:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/GraphicsReleaseD3DResources136.cpp
    scripts/repo-python scripts/verify-graphics-d3d-resource-release136-native.py

The already exact 884B Window scheduler, 164B no-wait Presenter
and 385B paced Presenter call this genuine leaf. Their
existing original bytes are independently credited and not
counted again here.

One newly accepted **136B distinct game-authored exact head**.
