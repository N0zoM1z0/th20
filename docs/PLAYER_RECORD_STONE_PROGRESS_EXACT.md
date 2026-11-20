# PlayerRecord stone progression boundaries

Four native PlayerRecord helpers used by the WeaponStoneInfo item-drop path
are restored as ordinary C++:

- 0x0051B8A0 — PlayerRecord::clamped_field_4c(), 64 bytes
- 0x0051B920 — PlayerRecord::clamped_field_50(), 64 bytes
- 0x00533920 — PlayerRecord::add_field_4c_clamped(int), 75 bytes
- 0x00534390 — PlayerRecord::field_a4_value(), 21 bytes

The first three retain the original std::clamp call at 0x00471170 and match
all 191 non-relocation bytes. The byte accessor matches all 21 bytes. All
four strict match units replay independently from one source/object.

WeaponStoneInfo::process_item_drop(int) at 0x00533780 is now a complete
406-byte natural C++ match in src/WeaponStoneItemDrop.cpp. Its separate
FrontInf/phase guards, 10/15-item interval, passive-weapon trigger, progress
threshold branches and phase-completion call match all 290 non-relocation
bytes and all 29 original relocations. See
[the full item-drop exact receipt](WEAPON_STONE_ITEM_DROP_EXACT.md). The
separate 201-byte phase transition at 0x00534D00 retains its own
[whole-function exact evidence](WEAPON_STONE_ITEM_PROGRESS_EXACT.md).
