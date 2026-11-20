# WeaponStone progress animation callback — exact reconstruction

## Native callback chain

The progress-mesh initializer at `0x005348D0` installs `0x00532720` on the
root animation. The 20-byte entry wrapper constructs a one-byte
`WeaponStoneProgressCallback` object on its stack and forwards the incoming
`Animation*` to its `update` method at `0x00532A90`. That 32-byte method
resolves `weapon_stone_info(0)`, calls the 1,780-byte
`WeaponStoneInfo::update_progress_mesh()` routine, and returns zero.

The native entry wrapper is cdecl (`RET`, not `RET 4`); the callback-object
method is thiscall and cleans its one `Animation*` argument with `RET 4`. The
method body is not a no-argument global function: the wrapper's local object
provides its `this` pointer.

## Exact replay

`src/WeaponStoneProgressCallback.cpp` naturally expresses both bodies. The
locked x86 MSVC `/Od /Ob0 /GS-` profile reproduces the native 20-byte wrapper
and 32-byte method. The 20-byte function has one REL32 to `0x00532A90`; the
32-byte method has REL32 references to `weapon_stone_info(0)` at
`0x00464230` and `WeaponStoneInfo::update_progress_mesh()` at `0x00533970`.
All non-relocation bytes match and every relocation resolves to its native
target. Both functions are admitted as game-authored application behavior;
this does not grant exactness to the called 1,780-byte mesh updater.

Scoped replay command: `scripts/replay-exact-units.py --source
src/WeaponStoneProgressCallback.cpp`.
