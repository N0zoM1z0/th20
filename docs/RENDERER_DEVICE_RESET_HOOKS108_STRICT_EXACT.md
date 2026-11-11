# Renderer D3D9 reset hooks 108B — five distinct whole exact functions

Original Japanese Steamless TH20 v1.00a has five individual game-owned
Renderer state setters called by the original 1,954B device reset-state
Boss at 0x0041A2C0. Each has **nine original x86 instructions**,
zero E8 and zero PE HIGHLOW relocations. Their native fields belong
to the genuine large AnimationPoolOwner object, not five invented
standalone allocations.

| Original head | Size | Authentic Renderer field write |
| --- | --- | --- |
| 0x0041DB40 | 21B | byte at +0x6000E0C = 0x0B |
| 0x0041DB60 | 21B | byte at +0x6000E0D = 0xFF |
| 0x0041DB80 | 21B | byte at +0x6000E0E = 0xFF |
| 0x0041DBA0 | 24B | DWORD at +0x6000E08 = 0xFFFFFFFF |
| 0x0041DBC0 | 21B | byte at +0x6000E10 = 0xFF |

Maintained sources are src/NativeAnimationResetHooksView.hpp
and src/RendererDeviceResetHooks108.cpp. The borrowed view inherits
only the existing AnimationPoolOwner ABI; it allocates no storage.
Its true byte and DWORD writes are also called in the right order
by the now complete C++ source of the original 1,954B Window
D3D9 state reset Boss. Both source files now share a single
declaration instead of divergent shadow views.

Pinned MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc emits all five native
complete bodies without artificial local variables, padding,
handwritten opcodes or NOPs: **21/21, 21/21, 21/21, 24/24,
21/21 original bytes**. Each is independently SHA-pinned and
instruction/field-attested by
scripts/verify-renderer-device-reset-hooks108-native.py.

Five exact manifest units were cold replayed using only this
single source file — **5/5 exact, one cold MSVC object**:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/RendererDeviceResetHooks108.cpp
    scripts/repo-python scripts/verify-renderer-device-reset-hooks108-native.py

The 1,954B reset-state parent was compiled and its source
frontier verified separately. Its **1,911B typed C++ candidate
remains NONEXACT** because of original GS cookie/frame lowering;
no game parent bytes are credited through these exact children.
Five distinct game-authored original heads and **108 new exact
game bytes** are credited only once.
