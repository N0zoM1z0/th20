# Window D3D9 reset-state Boss 1,954B — complete compiled C++ frontier

TH20 Japanese Steamless v1.00a original at **0x0041A2C0** is
**1,954B /507 x86 instructions**, original whole SHA-256
47eeb9e563d439887c764aa863415a55551f7d8a2d6065a019897a86d147137a.
The complete function is called by the now strictly exact 884B
Window scheduler and the already exact 164B and 385B presenters
on successful device Reset.

Maintained source src/WindowDeviceResetStatesBoss1954.cpp is a
real complete C++20 D3D9 device-state initialization procedure.
It does **not** use a loop to fake the native individual calls:
each required state transition is an actual independent C++ D3D9
method invocation using the true process Graphics device.

The original contains exactly **38 device getter calls**, in order:
24 distinct IDirect3DDevice9::SetRenderState invocations
(native vtable +0xE4), eight SetTextureStageState invocations
(+0x10C) and six SetSamplerState invocations (+0x114).
The source preserves the original numeric types and values of
each render state, texture stage and sampler state. In particular,
the three actual float-valued render states read the game data
at 0x0056C8CC (1.0), 0x0056CDB0 (1000.0), and 0x0056CDB8
(5000.0) into meaningful DWORD API arguments **before**
calling the device getter, restoring native data destination order.

The game function then tests the real AnimationPoolOwner process
global at 0x005C0028 and invokes five distinct Renderer/device
recovery hooks whose original physical heads are 0x0041DB40,
0x0041DB60, 0x0041DB80, 0x0041DBA0 and 0x0041DBC0,
again with genuine repeated owner accesses.

## Actual MSVC variants and remaining codegen frontier

Pinned MSVC 19.44 x86 C++20
/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc was used for the complete source.

The initial full C++ attempt compiled to 1,914B/501 instructions
and 43 actual game E8 calls, with a real Renderer pointer local
which lowered the repeated recovery-hook global loads differently.
Restoring the five individual real process-global accesses gave
a 1,911B/499-instruction candidate and the actual six Animation
Renderer data roles. Introducing three meaningful original
float-value API locals puts each real float-data reference in
the correct physical call sequence.

The independent proof
scripts/verify-window-device-reset1954-native-frontier.py
verifies the immutable original SHA, all native call targets and
PE data identities, all 24/8/6 authentic D3D9 vtable roles,
and the entire compiled C++ function. It confirms **43/43 real
game E8 destination roles** and **47/47 PE data destination roles
in exact original order**. The native contains one additional
MSVC security-cookie E8 and security-cookie data reference.

**This parent is NONEXACT.** Original 1,954B/507 instructions
versus maintained candidate 1,911B/499, with only 95 ordinary
same-position bytes. The original GS stack lifetime/cookie
prologue and epilogue are not naturally reproduced by the
present gameplay source. No dummy buffer, unused local,
handwritten NOP or inserted security instruction is used
to force a size match. **Zero game-authored exact bytes** are
credited for this 1,954B parent.

Only the one new nonexact source was compiled (no canonical
exact unit, no full cold graph):

    nice -n 15 scripts/compile-probe.sh src/WindowDeviceResetStatesBoss1954.cpp build/gptweb23-window1954/WindowDeviceResetStatesBoss1954.obj /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
    scripts/repo-python scripts/verify-window-device-reset1954-native-frontier.py
    scripts/repo-python scripts/validate-tracking.py --require-target

The separately exact 884B Window scheduler and its other exact
callers retain their receipts and their original byte credit.

The five real Renderer reset-hook callees now have a shared borrowed
C++ declaration and [five separate whole-exact implementations totaling
108B](RENDERER_DEVICE_RESET_HOOKS108_STRICT_EXACT.md).
Their canonical replay is 5/5 units in one MSVC cold source object.
This improves the real source linkage boundary but does not change
the 1,954B parent GS/cookie mismatch; it remains NONEXACT.
