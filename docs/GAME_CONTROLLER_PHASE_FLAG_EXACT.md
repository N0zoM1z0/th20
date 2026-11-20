# GameController phase-cancellation flag — exact reconstruction

The native 26-byte helper at `0x00534300` reads the GameController flag word
at `+0xE8`, shifts right by six, masks to one bit, and returns a full 32-bit
integer. Its only observed call site in the current WeaponStone frame path is
`0x00532B38`.

`GameController::flag_6_set()` is a natural C++ member returning
`(game_flags.bits >> 6) & 1u`. The scoped MSVC x86 `/Od /Ob0 /GS-` COFF
contribution structurally replays 26/26 bytes with no relocations. The owner
class and flag-word offset are independently established by the existing
GameController storage reconstruction. The source origin remains unknown,
so this is not entered as authored exact coverage.
