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
exact. The maintained source now expresses the dispatcher as the real
`Animation::project_corners(Vector3*)` member, declared on `Animation` without
adding storage or changing object layout. Both VM paths call it directly as
`this->project_corners(corners)`; the temporary ABI-compatible receiver-view
struct has been removed. This keeps the native Animation receiver explicit
in the natural class that owns the mode byte. The source remains in
`src/AnimationCornerProjectionDispatch244.cpp`, with a reproducible scoped
probe in `scripts/probe-animation-corner-projection-dispatch244.py`.

## Exactness boundary

Pinned MSVC x86 C++20 now emits a **244B whole COFF contribution**:
**228B/76-i386 executable code plus a real 16B compiler switch table**.
The original function body is 244B/79-i386, with its switch table outside
the function extent. The source now uses one explicit dispatch scratch union:
the mode word is dead after the switch selects an arm, so that same word holds
the 12-byte `Vector3` stride used to form the four contiguous corner pointers.
This is ordinary C++ object/byte-pointer arithmetic, not padding or assembly.

The candidate retains all three original projector callee roles, all three
`current_animation_pool` absolute references, the four-way switch and `ret 4`.
Its call sites are at `+0x62/+0x9C/+0xD6`, versus original `+0x63/+0xA7/+0xE8`;
the 228B code remains 16 bytes shorter and has three fewer instructions.
It is therefore still **SOURCE-PRESENT, NONEXACT**. No strict match unit,
`matches.csv` entry or original authored-byte credit is added. The focused
probe pins the complete candidate extent, 76 instruction heads, three call
roles, all owner/data relocations, and the compiler switch table. No ASM,
padding, fake calls or synthetic data are used. The enclosing VM probe also
retains 161 opcode cases and all 505 original call-target multiplicities.
The changed `Animation.cpp` owner/header closure was strict-replayed 38/38
units in one cold object; no full-project cold replay was run.

The enclosing **39,470B** Animation VM is now source-present/NONEXACT in
`src/AnimationUpdate39470.cpp`; this dispatch child and its exact projector/
normalizer descendants do not close or credit bytes of that parent.
