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

WeaponStoneInfo::process_item_drop(int) at 0x00533780 is also now represented
by maintained natural C++ in src/WeaponStoneItemDrop.cpp. It checks the
FrontInf dialogue gate and phase, selects the 10/15-item interval, toggles
the passive weapon at the +0x4C progression interval, increments and clamps
the PlayerRecord stone counter, and dispatches the phase-complete transition.
Its current strict-profile candidate is 395 bytes against the 406-byte native
body, so it is deliberately tracked as reconstructed/nonexact with no original
byte credit. The phase-complete 201-byte WeaponStoneInfo boundary at 0x00534D00
is the next dependency to restore.
