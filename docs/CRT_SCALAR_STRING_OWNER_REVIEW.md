# UCRT scalar string comparison and length

The installed Windows SDK 10.0.26100.0 x86 `libucrt.lib` identifies three
pending library origins in the locked Japanese TH20 Steamless target:

| Entry | Symbol | Full section | Decoded instruction bytes |
| --- | --- | --- | --- |
| `0x0054FD10` | `_strcmp` | 140B | 137B / 55 instructions |
| `0x0054FDA0` | `_strncmp` | 120B | 117B / 45 instructions |
| `0x0054FE20` | `_strlen` | 139B | 139B / 46 instructions |

All 399B of the three complete members agree. Strcmp and strncmp each include
three internal INT3 bytes, retained in their existing ledger extents. Each
section has zero relocations, matching the empty PE HIGHLOW sets. There are
no calls, data tables, ISA-state references or local EH metadata. All three
use the original cdecl argument/return protocol.

## Strcmp resolves unsigned bytes in order

Strcmp aligns the first pointer with byte/word head handling, then reads
four bytes from that pointer at a time. The second string is checked one
byte at a time against the loaded value, with a zero check after each equal
byte. The first differing unsigned byte decides the result. The original
`SBB EAX,EAX; OR EAX,1` sequence produces -1 or +1, while equal termination
returns zero. The byte/word heads and all shared return paths remain inside
the full owner.

The source's internal alignment emits an unreachable 2B jump at
`0x0054FD53`, three INT3 bytes at `0x0054FD55..0x0054FD57` and an unreachable
`MOV EDI,EDI` at `0x0054FD5E`. These bytes match the archive and remain
compared despite their omission from Ghidra's instruction listing.

## Strncmp keeps the original count and page protocol

Strncmp saves EBX/ESI and returns equal before any buffer read for count zero.
It retains the first-minus-second pointer delta in ECX and aligns the second
pointer to four bytes through the scalar head. Before each dword load, the
first address must satisfy `(address & 0xFFF) <= 0xFFC`; otherwise it returns
to byte comparison. The second dword's address is already aligned.

Unequal dwords also return to byte comparison so the earliest differing byte
and the original remaining count decide the result. After equal dwords,
`SUB count,4; JBE` returns zero when the requested count is exhausted; the
remaining loop uses the original 0xFEFEFEFF/0x80808080 zero-byte test.

This sequence can load a full dword with fewer than four requested bytes
remaining. The page check and subsequent count control are original behavior;
the body is not replaced by a new byte-only tail. Results remain normalized
to -1, zero or +1. The complete owner includes its unreachable alignment
jump at `0x0054FE0B` and three INT3 bytes at `0x0054FE0D..0x0054FE0F`.

## Strlen preserves its dword detector and all four exits

Strlen scans initial bytes until the pointer is four-byte aligned, then
uses the original 0x7EFEFEFF addition and 0x81010100 candidate mask. A
candidate dword is reloaded and checked in byte order. A high-byte 0x80
false positive resumes the scan. Each of the four real zero-byte exits
subtracts the original string pointer to produce the unsigned length.

The installed `string/i386/strlen.asm` explicitly contains the five-byte
`ADD EAX,0` alignment instruction. It and the following original alignment
LEAs match and remain in the complete 139B section. The original source is
used as evidence; no assembly or artificial padding is added to maintained
reconstruction source.

## Complete coverage and affected scope

Private `.analysis/origin-boundary/string-length-compare/` retains the full
archive members and provenance, unique complete locations, bounded attested
listing, comparison, decoded listing omissions and original rows. The
installed SDK's i386 strcmp/strncmp/strlen assembly corroborates the exact
branches, masks, count protocol and internal alignment.

The full scope is the 416B interval `0x0054FD10..0x0054FEAF`, ending before
the independently reviewed acos. It contains 393 decoded instruction bytes,
six internal INT3 bytes and seventeen following alignment INT3 bytes across
the three members. Ghidra lists 143 instructions; bounded decoding retains
all 146, including the three unreachable alignment instructions. Every other
instruction is reachable from its own main entry. No existing extent changes.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass; all 2,151 protected native input/product hashes
are unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
