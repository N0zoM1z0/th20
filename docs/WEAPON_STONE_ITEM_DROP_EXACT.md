# `WeaponStoneInfo::process_item_drop()` — exact reconstruction

The native method at `0x00533780` is a 406-byte thiscall member on the actual
`WeaponStoneInfo` owner. The natural C++ source matches the complete function
under the scoped MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` profile.

## Behavior

1. Return when the current FrontInf has dialogue, then independently return
   when the WeaponStone phase is nonzero. The separate guards preserve the
   native short-branch/common-epilogue layout.
2. Select the drop interval from PlayerRecord `field_2f`: 15 when nonzero,
   otherwise 10.
3. When `field_a4` is enabled and the clamped stone-progress count is at the
   final position of that interval, increment the incoming amount and enable
   the passive weapon at `weapon_34`.
4. Compare the clamped progress count with the clamped threshold. The native
   `count >= threshold` branch comes first; if phase is zero it writes the
   threshold and invokes the separate `complete_item_progress()` method.
5. Otherwise add the amount through the original clamped PlayerRecord helper.
   If the resulting count reaches the threshold, write the threshold and
   invoke the same phase-completion method.

## Exactness receipt

The complete COFF contribution is 406 bytes. All 290 non-relocation bytes
match the native body, and all 29 native relocation fields (116 bytes) resolve
to their original destinations: FrontInf dialogue, Session/PlayerRecord lookup,
PlayerRecord mode/progress helpers, passive Weapon setter, clamped increment,
threshold setter, and the separate 201-byte phase-completion method. The
scoped canonical replay is registered as `weapon_stone_item_drop`; no
assembly, NOPs, padding, or duplicate helper-byte credit is used.
