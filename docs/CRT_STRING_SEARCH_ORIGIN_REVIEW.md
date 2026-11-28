# CRT first/last character search owners

Four complete MSVC 14.44.35207 x86 `libvcruntime.lib` members identify pending
library origins in the locked Japanese TH20 Steamless target:

| Entry | Symbol | Complete instruction extent |
| --- | --- | --- |
| `0x005448C0` | `_strrchr` | 311B / 116 instructions |
| `0x00546140` | `_strchr` | 299B / 122 instructions |
| `0x0054628E` | `_wcschr` | 154B / 60 instructions |
| `0x00546328` | `_wcsrchr` | 162B / 62 instructions |

All existing extents remain unchanged. The complete 926B/360-instruction
union agrees with the members and bounded attested listings. Each member has
one DIR32 field naming `___isa_available` at `0x005E5288`, independently
established by the complete CPU initializer/data proof in
[the memory-dispatch review](CRT_MEMMOVE_CPU_DISPATCH_REVIEW.md).
All four HIGHLOW sets agree. These owners have no calls, local tables or EH
metadata, and every instruction is reachable from its owning main entry.

## Narrow first occurrence and shared entry

Strchr compares the ISA level with one using an unsigned branch. Its SSE2
path expands the low byte of the search integer, aligns the first load down
to 16 bytes and masks positions before the original string. It combines
character and zero-byte masks, then uses BSF to select the first event.
The final byte comparison distinguishes a character match from termination;
searching for zero returns the terminating zero's address.

The scalar path aligns forward by bytes, preserving EBX and then EDI/ESI as
needed. Its 0x7EFEFEFF dword test checks both the target byte and termination.
Candidate bytes are resolved in order, including the high-byte 0x80 false
positive case. Every pointer-return and null-return tail remains in the
complete function.

The member's public `___from_strstr_to_strchr` label is at `0x005461AE`,
inside the scalar owner. It expects the search byte already prepared in EAX
and enters before EBX is saved. It retains that register/stack protocol as
an internal alternate entry; it adds no second physical function or byte credit.

## Narrow last occurrence has three ISA paths

Strrchr uses unsigned comparisons: below one selects the scalar path, exactly
one selects SSE2, and above one selects the STTNI path. SSE2 masks the initial
aligned block's prefix and carries the previous last-match pointer. At the
first block containing zero, it restricts the character mask through that
first terminator and selects the last surviving match with BSR. This retains
the zero-search result at the terminator itself.

The higher-ISA nonzero path scans a scalar alignment head, then uses
PCMPISTRI immediate 0x40 to update the last match until zero is detected.
Its separate zero-search path uses aligned SSE2 zero masks and BSF. The
scalar fallback finds the terminator with REPNE SCASB, then searches backward
including that terminator. Its original STD and final CLD remain paired
across both returning branches. All paths restore EDI and the frame.

## Wide first occurrence checks each prospective page crossing

Wcschr uses a signed ISA-level comparison with one. The scalar path walks
16-bit values and returns the selected pointer or null, including the
terminator when the search value is zero. The SSE2 path expands the 16-bit
search value, compares eight characters with both it and zero, and uses the
first mask bit to select the result.

Each vector attempt first requires `(address & 0xFFF) <= 0xFF0`. Near the
page end it checks one 16-bit character and retries. The original two-byte
versus sixteen-byte increments and shared final comparison remain intact.

## Wide last occurrence uses the original character alignment rule

Wcsrchr uses a signed ISA-level comparison with two. Below that threshold it
finds the terminator and searches backward through the first character.
The higher-ISA path saves the last match in ESI and checks single characters
until `((address + 1) & 0xE) == 0`. This preserves the original handling of
both even and odd addresses before vector loads.

For nonzero searches, PCMPISTRI immediate 0x41 selects the highest matching
word index and updates ESI until termination. Zero search instead builds
the range pattern 0xFFFF0001 and uses immediate 0x15 to locate the first
terminating word. Both indices scale by two, and the common epilogue restores
EDI/ESI/EBP. The ISA thresholds and scalar branches remain distinct from
the narrow implementations.

## Evidence and affected scope

Private `.analysis/origin-boundary/string-search/` retains the four complete
members, archive provenance, attested listings, full byte/relocation checks,
instruction reachability and original ledger rows. Installed x86 strchr,
strrchr, wcschr and wcsrchr sources corroborate the scalar and wide protocols.
The retained 173B memchr member has no full ordinary-byte match and receives
no origin credit here.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass; all 2,151 protected native input/product hashes
are unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
