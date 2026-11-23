# Bullet +0x4D8 float setter (0x0049CAE0)

## Native behavior

The 39-byte i386 member function receives a `Bullet*` in ECX and a float on the stack. It forwards that float to the real `Timer::operator=(float)` at `0x0047C5F0`, with the Timer subobject at `Bullet+0x4D8`, then returns with `ret 4`. Ghidra decompiles the body to exactly this forwarding operation.

Two independent calls in the original Enemy opcode-629 callback bosses establish the owner and use: the rotated-animation rectangle clear at `0x00488D25` and the all-bullet reset at `0x00488F30`. The first passes the Enemy clear clock; the second passes the original `1.0f` clock global.

## Natural C++ owner

`src/BulletTimer4D8.cpp` defines `Bullet::set_timer_4d8(float)` as a direct assignment to the real `timer_4d8` member. This is a normal C++ member function, not an assembly stub or byte-padding construct. The source is included in the focused Enemy root host and its i386 COFF object is kept separate for whole-function comparison.

## Native extent and relocation

- Start: `0x0049CAE0`
- Size: 39 bytes (`0x0049CAE0..0x0049CB06`)
- ABI: `__thiscall`, one 32-bit float stack argument, `ret 4`
- Original relocation: `REL32` at function offset `0x1C` to `Timer::operator=(float)` at `0x0047C5F0`
- Existing Timer assignment callee: independently exact 33-byte unit `timer_assign_float`

The source spelling `set_timer_4d8` is an inferred descriptive name; original symbol spelling and authored/compiler provenance remain unclassified. Exactness is tracked independently from that naming uncertainty.
