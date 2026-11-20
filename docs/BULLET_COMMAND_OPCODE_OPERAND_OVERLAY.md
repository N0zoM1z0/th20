# Bullet command operand words: native 44-byte overlay

The original `Bullet::run_extended_commands` at `0x0047DCF0` consumes
`BulletCommand` values from the `std::pmr::vector<BulletCommand>` embedded in
`EtamaArgInf`. The command record is **44 bytes (`0x2C`)**. Its first eight
payload slots occupy `+0x00..+0x1F`; opcode and flags are at `+0x20/+0x24`,
and opcode 24 uses the pointer at `+0x28`.

A fixed C++ interpretation of the first eight slots is not valid. The
original command interpreter reads the same 32-bit slot as a float in some
opcodes and as a signed integer or bit mask in others. The previous source
exposed the first four as floats and the next four as integers because those
were the known consumers in the already-exact emitter. That was an incomplete
view of the shared record, not evidence that the underlying words had fixed
types.

`src/BulletValues.hpp` now exposes named union views for each of the eight
32-bit payload words:

- `operand_00` through `operand_0c`: float, signed integer, and raw word views.
- `operand_10` through `operand_1c`: signed integer, float, and raw word views.
- `opcode`, `flags`, and `script` retain their established offsets and types.

The unions do not add storage, padding, or another object. Compile-time
assertions pin all eight payload offsets and the trailing three fields; the
existing x86 assertion continues to pin `sizeof(BulletCommand) == 44`.

## Compatibility proof against the existing large caller

The edit was compiled with the same pinned MSVC x86 profile used by the
canonical `bullet_emitter_whole_3735` object:

`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

A fresh probe of `src/BulletEmitter.cpp` was compared to the accepted
`build/core645-canonical/BulletEmitter.obj` at the complete COFF function
contribution, including relocations:

- `BulletController::emit`: **3,832 / 3,832 bytes identical**.
- Relocation records: **129 / 129 identical**, including their symbol names,
  offsets, kinds, and targets.

Thus the additional views preserve the complete original large-caller object
and its ABI. This is a type/layout preparation for restoring the 12,140-byte
interpreter; it does **not** claim any new exact bytes for that still
source-absent parent.
