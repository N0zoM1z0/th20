# UCRT format length and character-width mappings

Two complete Windows SDK 10.0.26100.0 x86 `libucrt.lib(output.obj)`
contributions identify pending library origins in the locked Japanese TH20
Steamless target: the 49B `is_wide_character_specifier<char>` at
`0x00548A1A` and `to_integer_size` at `0x00549ECD`. Both existing 49B
instruction extents are correct. The latter's full 84B contribution also
owns a 3B NOP and two internal tables totaling 32B.

The combined complete scope is 133B: 98B/47 instructions, 3B NOP and all
32 table bytes. Every ordinary byte, table field and original addend agrees.
The seven DIR32/HIGHLOW fields are internal to to_integer_size; the character
width helper has none. Both use cdecl, have no calls or local EH metadata,
and retain all branches and returning paths.

## Integer sizes use the x86 widths

To_integer_size compares the 32-bit length value with eleven using unsigned
JA. Values zero through eleven index twelve selector bytes at `0x00549F15`.
Those bytes select one of five code pointers at `0x00549F01`, whose targets
return 4, 1, 2, 8 or zero. All five pointer targets are instruction heads in
the same complete owner.

| Length modifiers | Returned byte size |
| --- | ---: |
| none, l, z, t, I, I32 | 4 |
| hh | 1 |
| h | 2 |
| ll, j, I64 | 8 |
| L, w, T and other values | 0 |

L (enum value eight) reaches zero through its explicit selector. The w/T
values and all unsigned values above eleven take the direct default branch;
negative underlying enum values therefore also return zero. Shared epilogues
remain part of the owner. The original 3B NOP at `0x00549EFE` separates the
49B code body from the first table. The full second table ends at
`0x00549F20`, immediately before the next inventoried function.

## Narrow format strings retain their own character-width policy

For the char instantiation, l and w force a wide result; h and T force a
narrow result. With other modifiers, lowercase c/s select narrow and other
format bytes select wide. This is the helper's original predicate, including
values beyond the ordinary C/S alternatives a caller may supply.

The 64-bit options argument remains in the stack ABI even though this narrow
instantiation does not read it: the char argument is at frame `+0x10` and the
32-bit length argument at `+0x14`. Boolean results use AL. Its actual 24
instructions are the full 49B owner, with the original NOP/prologue and two
shared return sequences. The unlocated 78B wchar_t instantiation is separate.

## Evidence and affected scope

Private `.analysis/origin-boundary/format-types/` retains scoped locator
results, the attested listing, complete comparison, all selector values and
results, reachability proof and original rows. It reuses the complete member
and archive provenance in `format-buffer/`. Installed
`corecrt_internal_stdio_output.h` supplies the same length enum and complete
mapping definitions; the finite table review covers every selector and the
default branch. Every instruction is reachable when all five table edges
are included.

Only classification, evidence, handoff and generated progress change. No
existing instruction extent or native reconstruction input changes.
Tracking/progress checks pass; all 2,151 protected hashes are unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
