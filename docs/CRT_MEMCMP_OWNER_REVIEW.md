# CRT memcmp and its complete residual table

The installed MSVC 14.44.35207 x86 `libvcruntime.lib(memcmp.obj)` identifies
the pending library origin `_memcmp` at `0x00544D77` in the locked Japanese
TH20 Steamless target. The existing 4,929B instruction extent is correct.
The complete contribution is **5,060B**: 4,929B/1,727 instructions, a 3B
NOP at `0x005460B8`, and the 128B internal table at
`0x005460BB..0x0054613A`. All ordinary bytes and all 33 DIR32/HIGHLOW fields
agree, including every table entry. The next candidate begins at `0x00546140`.

## Scalar comparison and normalized result

This cdecl implementation preserves EBP/EBX/ESI/EDI. Zero count returns zero
before loading either buffer. Counts one through four have separate direct
paths that join the complete shared result/return owner. Larger inputs use
ESI/EDX for the two pointers, EBX = 1 and EDI = -1.

Each 32B iteration compares eight consecutive dwords. Equal dwords skip
their byte-resolution paths. An unequal dword is resolved in increasing
byte order with unsigned-byte loads. The first nonzero left-minus-right
byte difference is normalized with the original conditional moves to
**-1 or +1**; equality returns zero. The integer value of a little-endian
dword does not decide lexicographic order. The shared final-byte result
and common register-restoring epilogue remain inside the same function.

After a fully equal 32B block, both pointers advance by 32 and the original
count stack slot is reduced by 32. Another full block repeats the loop.
For the residual count below 32, both pointers advance to the residual end
and dispatch through the complete table using that count as the index.

## All 32 residual entries belong to this owner

The table contains one pointer for each residual count 0–31. Case zero at
`0x00545520` clears ECX and reaches the shared result. Cases one, two and
three begin at `0x00545888`, `0x00545BF3` and `0x00545F66`. They read the
last one, two or three bytes with the original byte/word logic.

Cases at least four start with a dword at end-minus-count. An equal dword
continues at case count-minus-four. Unequal dwords resolve their individual
bytes in order before returning. These four interleaved chains account for
all table entries and the large unrolled tail. Every one of the 1,727
instructions is reachable from the main entry when the table edges are
included. No case is another function or an omitted external tail.

The sole table-reference relocation is at function offset `0x444`; the
remaining 32 are its entries at offsets `0x1344..0x13C0`. All are bound to
COFF labels in the same complete section, with their original addends.
This owner has no external calls, runtime state references or local EH
metadata. Its boundary therefore does not depend on the preceding CPU-state
proof. The object's separate cmpBYTE/WORD/DWORD/result helpers and
unaligned_memcmp section have no complete target locations and receive no
additional credit.

## Evidence and affected scope

Private `.analysis/origin-boundary/memory-compare/` retains the full member,
archive provenance, locator results, attested full listing, all 32 target
roles, complete comparison, reachability result and original ledger row.
The retained 5,060B comparison includes the original NOP and all table bytes;
the ledger keeps its existing instruction extent of 4,929B. No historical
receipt or reconstruction source changes.

Tracking/progress checks pass. All 2,151 protected native input/product hashes
remain unchanged. Exact replay scope is **zero units**, with no new authored
or maintained-source exact credit.
