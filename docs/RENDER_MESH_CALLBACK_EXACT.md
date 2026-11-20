# `RenderMesh::set_update_callback()` — exact reconstruction

The native 37-byte method at `0x0052CD50` publishes an
`AnimationEntryCallback` through the `AnimationHandle` stored at
`RenderMesh+0x8`. Its complete natural C++ body is:

```cpp
void RenderMesh::set_update_callback(AnimationEntryCallback callback) {
    root.set_entry_callback_forward_44f100(callback);
}
```

The locked x86 MSVC `/Od /Ob0 /GS-` profile reproduces all 37 bytes. All 33
non-relocation bytes match, and the single REL32 at `+0x1A` resolves to the
existing 39-byte `AnimationHandle::set_entry_callback_forward_44f100` at
`0x0044F100`. The original function has three observed callers, including the
WeaponStone progress-effect initializer at `0x005348D0` and its sibling at
`0x00534AB0`.

This is the actual RenderMesh owner wrapper, not a synthetic callback stub.
The exact replay is recorded as `CORE/EXACT-1204` in
`config/match-units.toml`.
