# WeaponStoneInfo item-progress transition

`WeaponStoneInfo::complete_item_progress()` at `0x00534D00` matches the full
201-byte native body through the return at `0x00534DC8`. The locked MSVC x86
build reproduces 157 ordinary bytes and 44 bytes across nine direct calls
and two PE HIGHLOW fields.

The established Player, Sound, AnimationHandle and AnimationFile bindings
account for eight calls. The other call enters `0x005348D0`, whose native
ordered call sequence agrees with the separate mesh and particle initializer.
The PE data fields reference the established Sound owner and the matching
string literal in `.rdata`. The final virtual call and phase store are
ordinary bytes in this unit.

The phase transition has its own translation unit. Its particle-effect
initializer and the item-update body remain separate open boundaries.
The `WeaponStoneInfo.hpp` include closure passed all 43 existing units
across 11 rebuilt providers.
