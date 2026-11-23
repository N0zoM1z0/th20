# Enemy ECL opcode 632 — borrowed script pointer into queued BulletCommand

## Status and boundary

Opcode 632 is represented by natural C++ in src/EnemyStateScriptPointerOpcode.cpp,
routed through the maintained EnemyState::execute_opcode root and executed
by the ASan/UBSan root host. Its original inline case is **252 bytes / 62 x86
instructions / 10 direct E8 calls**, at 0x00493831..0x0049392D, selector
index **150**, SHA-256
45cdbd018eea322e53dcffa4af1834acceeb26b2f9ba2aa72d6a17d41535f277.

This is a case fragment inside the original 41,967-byte dispatcher, not a
standalone native function. The parent remains **NONEXACT** and receives no
whole-parent byte credit.

## Native call order

The original ten direct calls are:

| Site | Target | Role |
| --- | --- | --- |
| 0x00493839 | 0x004AB080 | integer argument 0 |
| 0x0049384C | 0x004AB080 | integer argument 1 |
| 0x0049386B | 0x00498B80 | writable queued record/metadata selector |
| 0x00493877 | 0x0040B280 | pair move |
| 0x00493880 | 0x0048B180 | pair first element |
| 0x00493895 | 0x0040B280 | pair move |
| 0x0049389E | 0x0048B160 | pair second element |
| 0x004938B7 | 0x00486600 | command-vector size |
| 0x004938EA | 0x004862F0 | command-vector resize |
| 0x00493920 | 0x0047C6C0 | command-vector indexed access |

The focused PE verifier pins the selector pointer, exact case extent/hash,
all 62 decoded instructions and all ten ordered direct calls.

## Natural C++ semantics

Both integer operands are read before writable_shot() is called. The
returned pair is extracted with std::get<0> / std::get<1>. The selected
ShotMetadata::commands vector is grown to index + 1 only when necessary,
then the selected BulletCommand::script field is assigned the borrowed
address reinterpret_cast<const char*>(&instruction) + 0x1c.

The pointer is the original fourth trailing ECL payload word. It is not a
copied string, does not allocate, and does not advance or rewrite the
metadata command cursor. The COW selector is real: when metadata is shared,
the selected record receives a cloned metadata owner before vector growth.

## Root-host regression coverage

The maintained root host removes the former false-returning
execute_enemy_script_pointer_opcode stub and links the production helper.
Tests cover:

- both integer operand reads in native order before writable COW;
- shared metadata cloning and preservation of the original command vector;
- PMR vector growth from one command to three;
- exact pointer identity with EclInstruction + 0x1c and the borrowed
  script bytes;
- preservation of pre-existing command fields;
- an exception on integer operand 1, proving no COW, resize or pointer
  publication occurs before both indexes are available.

The locked-profile i386 COFF check preserves both integer reads, the writable
selector, ordered pair extraction, vector size/resize/index calls and the
borrowed +0x1c pointer store. The maintained root verifier currently runs
114 focused host source units under ASan/UBSan and compiles 50 locked-profile
i386 COFF source units.

No ASM, padding, synthetic wrapper or string-copy substitute is used. No full
cold replay was run.
