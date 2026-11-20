# ItemInf update callback gate — complete native 79B

The original 0x004C46F0 callback is now a natural static C++ member,
ItemInf::update_callback(void*), in src/ItemInfUpdateGate.cpp.

The callback has two independent early-return gates:

1. A non-null current_game_controller whose native
   GameController::update_suppressed() predicate is nonzero returns 1.
2. A non-null controller with bit 11 set in its +0xE8 game flag word also
   returns 1.

Otherwise it forwards the caller's ItemInf pointer to the separate
ItemInf::update_main() owner at 0x004C25A0. The declaration preserves
the original __fastcall ECX receiver ABI at the boss boundary; the wrapper
itself remains __cdecl.

Pinned x86 MSVC /std:c++20 /Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise
produces 79/79 bytes. All six original relocation fields are preserved:
four references to current_game_controller at 0x005BA828, the
GameController::update_suppressed call at 0x00424030, and the ItemInf
boss call at 0x004C25A0. All 55 non-relocation bytes are identical.

The large 4757B ItemInf::update_main() body is still an independent open
target. This gate does not claim credit for it.
