# Animation corner projection dispatcher — strict exact reconstruction

The original Animation corner-mode dispatcher at `0x00445770` is now restored
as natural C++ in `src/AnimationCornerProjectionDispatch244.cpp`. Its complete
native body is **244B / 79 i386 instructions**, with three real E8 calls and a
`ret 4` member-function ABI.

## Mode and receiver semantics

The receiver is the `Animation` object. The mode byte is
`AnimationBase::flags.bytes_00.animation_mode` at `+0x498`:

- modes **0, 2 and 3** call the original normal corner projector at
  `0x0043EB40`;
- mode **1** calls the original rotated corner projector at `0x0043EF20`;
- all other modes return without projecting.

The child projectors receive the Animation pointer and four contiguous
`Vector3` records. Their unused ECX receiver is the real
`current_animation_pool` owner at `0x005C0028`. The maintained source views the
input as its actual four-element `Vector3` array and passes the four element
addresses in order; it creates no new storage or duplicate projector.

The three original physical calls are `+0x63 -> 0x0043EB40`,
`+0xA7 -> 0x0043EF20` and `+0xE8 -> 0x0043EB40`. The four in-body PE HIGHLOW
fields are at `+0x26`, `+0x5F`, `+0xA3` and `+0xE4`. The original 16-byte
four-entry switch table begins immediately after the function at `0x00445864`
and contains targets `0x0044579A`, `0x004457DE`, `0x0044581F` and
`0x0044581F`.

## Exact source and compiler result

The pinned MSVC x86 C++20 source compiles to the original **244B / 79-head**
body plus its **16B** switch table. The complete 260B COFF contribution has
11 relocations: the switch-table base, three `current_animation_pool`
references, three projector calls and four local switch targets. All 244 body
bytes and all 16 table bytes match the original after independent relocation
resolution. The canonical unit is
`animation_corner_projection_dispatch244` (`size = 244`, `compare_size = 260`).

A local array-reference variable initially added a redundant stack pointer
copy and moved all three calls six bytes later. Keeping the four-element array
view in each argument expression removes that extra local and reproduces the
native prologue, pointer calculations, call sites and switch table without
assembly or synthetic padding.

## Integration and remaining scope

The 39,470B Animation VM calls this dispatcher from opcode `0x5A` and its
projection epilogue; the separate caller at `0x00504480` uses the same
interface. The 985B normal projector and 1,486B rotated projector are
independently strict exact. The enclosing Animation VM remains NONEXACT.

The implementation and complete native bytes are exact; the original
historical source provenance remains unknown.
