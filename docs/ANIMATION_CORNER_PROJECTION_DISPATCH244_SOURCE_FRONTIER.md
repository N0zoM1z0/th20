# Animation corner projection dispatch: source-present NONEXACT frontier

The original Animation corner-mode dispatcher is the complete **244B**
function at **`0x00445770`**, with **79 i386 instructions**, a `ret 4`
ABI, three genuine E8 calls and four original PE HIGHLOW fields. Its
independent original SHA-256 is
`16c02538c572c3e989500be8e565718ad06648de0ddf07436d07aa95267785c4`.

## Actual mode and receiver semantics

The receiver is the Animation object. The mode byte is
`AnimationBase::flags.bytes_00.animation_mode` at **`+0x498`**:

- modes **0, 2, 3** call the original normal corner projector at
  `0x0043EB40` (985B);
- mode **1** calls the original rotated corner projector at
  `0x0043EF20` (1486B);
- all other mode values return without projecting.

Each child receives the Animation pointer and four contiguous Vector3
corner records. The child projector's unused ECX receiver is the real
`current_animation_pool` owner global at `0x005C0028`; it is not the
Animation pointer. The Animation pointer is passed as the first explicit
argument. The maintained C++ uses that real owner and the existing exact
projector methods, without creating storage or a second projector.

The immutable original has call sites `+0x63 -> 0x0043EB40`,
`+0xA7 -> 0x0043EF20`, and `+0xE8 -> 0x0043EB40`. Its four PE HIGHLOW
fields are at `+0x26` (switch-table address), `+0x5F`, `+0xA3`, and
`+0xE4` (the three renderer-owner loads). The independent checker pins the
whole native SHA, complete decoded extent, return cleanup, all three call
targets and all four physical fields.

## Connection to the 39,470B Animation VM

The original 39,470B `Animation::update`/VM at `0x0042B5D0` has two real
uses of this dispatcher. In opcode **`0x5A`**, it constructs four contiguous
Vector3 records with the native array constructor, calls this mode switch,
normalizes the four projected points through the now whole-exact 95B
`normalize_coordinates_438eb0`, and writes width/height at Animation
`+0x398/+0x39C`. The final VM epilogue repeats the same projection and
normalization sequence when Animation flag bit 11 is set. The same helper
is also called by `0x00504480`.

The 95B coordinate normalizer is whole-native exact; the two projection
leaves at `0x0043EB40` and `0x0043EF20` are independently whole-native
exact. This dispatch wrapper now has natural C++ source in
`src/AnimationCornerProjectionDispatch244.cpp` and a reproducible scoped
probe in `scripts/probe-animation-corner-projection-dispatch244.py`.

## Exactness boundary

Pinned MSVC x86 C++20 currently emits a **192B whole COFF contribution**:
**176B/65-i386 executable code plus a real 16B compiler switch table**.
The original function body is 244B/79-i386, with its switch table outside
the function extent. The candidate retains all three original projector
callee roles, all three `current_animation_pool` absolute references, the
four-way switch and `ret 4`, but its call sites are displaced. It is therefore
**SOURCE-PRESENT, NONEXACT**. No strict match unit, `matches.csv` entry or
original authored-byte credit is added. The 68B executable-codegen gap is
explicitly open; no ASM, padding, fake calls or synthetic data are used.

The enclosing **39,470B** Animation VM remains source-absent/NONEXACT.
This dispatch child and its exact projector/normalizer descendants do not
close or credit any bytes of that parent.
