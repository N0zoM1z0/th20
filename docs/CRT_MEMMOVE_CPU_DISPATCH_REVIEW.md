# CRT memory copy/fill and CPU dispatch state

Three complete x86 library contributions identify pending origins in the locked
Japanese TH20 Steamless target: `libcmt.lib(cpu_disp.obj)` supplies the 794B
`___isa_available_init` at `0x005436C1`, and `libvcruntime.lib(memmove.obj)`
supplies the 1,396B `_memmove` at `0x00543E20`. The same VCRuntime archive's
`memset.obj` supplies the 346B `_memset` at `0x00544760`. All existing extents
remain unchanged. The full comparisons include ordinary bytes, relocation roles,
source addends and every corresponding PE HIGHLOW field.

## Independent CPU state provider

The initializer's complete 239-instruction body establishes the state used by
memmove. Its sole imported call names `IsProcessorFeaturePresent` through the
PE import table at `0x0056C17C`, with feature argument 10. The original early
return remains when that test fails. Before the test, it sets the x86 enabled
bit and resets the ISA level; all returning paths produce integer zero.

The remaining body preserves the Intel vendor/model checks, CPUID maximum-leaf
guards, leaf 7 subleaf checks, XGETBV OS-state checks and newer leaf 0x24
processing. Atom model checks set favor bit 0. CPUID leaf 7 EBX bit 9 sets
favor bit 1. SSE2, SSE4.2, AVX, AVX2, AVX-512 and AVX10 updates retain their
original prerequisites and complete inverted-feature mask writes. The two
globals consumed by memmove are not inferred from memmove's own fields:

| Complete provider section | Address | Contents before initialization |
| --- | --- | --- |
| 12B initialized data | `0x005B2610` | 64-bit `___isa_inverted = -1`, then `___isa_enabled = 1` at `0x005B2618` |
| 12B loader-zero BSS | `0x005E5284` | `___avx10_version`, `___isa_available` at `0x005E5288`, then `___favor` at `0x005E528C` |

All 42 initializer DIR32 fields agree with those complete provider sections
or the independently named import. The BSS comparison uses loader-zero
virtual bytes rather than unrelated raw file bytes. This also corroborates
the ISA-level slot used by preceding floating/string reviews.

## Complete overlap and copy protocol

Memmove preserves ESI/EDI, takes three cdecl stack arguments and returns the
original destination pointer in EAX. Its unsigned overlap decision uses the
original 32-bit source-plus-count operation: copy forward when destination is
at or below source, or at/above source end; otherwise copy backward. The
zero-count path reaches the scalar return without a buffer access.

Forward sizes below 32B use scalar loops. Sizes 32–127B test enabled bit 1
for SSE2, otherwise use destination-aligned dword copying. At least 128B
first tests favor bit 1 for REP MOVSB. Otherwise equal source/destination
alignment modulo 16 and SSE2 select the aligned XMM owner. Its head adjustment,
128B/32B loops and scalar tail are all retained.

The alternate Atom path tests favor bit 0 and the original four-byte
alignment conditions. Its destination head, PALIGNR 12/8/4 software pipelines
and tail remain inside the same owner. There is no separate SSSE3 feature
test in this body. The installed `i386/memmove.asm` selects `MEM_MOVE` and
includes the shared `i386/memcpy.asm`; that source corroborates the complete
protocol and labels without introducing maintained assembly.

Backward copying starts at the two buffer ends. Small copies use decreasing
dword/byte loops. Larger SSE2 copies align the destination end, then load
each entire 128B or 32B block before storing it. The scalar large path sets
DF for REP MOVSD and clears it before the trailing-byte dispatch and return.
No backward branch or shared return is split out as another function.

## Internal tables and original unreachable bytes

The full physical memmove span is `0x00543E20..0x00544393`: **1,361B/417
decoded instructions**, **32B of tables**, and **3B INT3** at
`0x0054426D..0x0054426F`. Instruction bytes include the original alignment
instructions and unreachable jump. The two four-entry tables are
`TrailingUpVec` at `0x00544084` and `TrailingDownVec` at `0x00544130`.
Every table pointer resolves to the corresponding internal instruction head;
the 17 DIR32 fields include both tables and all state/table references.

Ghidra lists 404 instructions. Bounded decoding accounts for thirteen more:
the original 7B `ByteCopyUp` jump at `0x0054407C` and twelve alignment
instructions. Its table reference retains source addend 16, which points to
`0x00544094`, beyond the four-entry table. There is no entry-reachable path
to that instruction. A traversal from memmove's entry, including every
internal table edge, leaves exactly those thirteen instructions unreachable.
They remain compared in the full contribution; neither that jump nor its
operand is repaired or discarded. The complete owner has no local EH table.

## Memset's thresholds, tail and register preservation

The complete 346B/89-instruction memset agrees with its archive member and
bounded attested listing. All three DIR32/HIGHLOW fields use the already
established ISA-enabled and favor slots. It owns no table, EH metadata or
INT3 padding. Original alignment instructions remain in its full extent.

This cdecl body saves EDI in EDX without a stack frame, reads only the low
byte of the integer value argument and expands it with multiplication by
0x01010101. Zero count returns before any destination store. Every return
restores EDI and supplies the original destination pointer in EAX.

Unlike memmove's below-32B scalar threshold, memset uses scalar copying for
**at most 32B**. Sizes 33–127B try SSE2. At least 128B first tests favor bit 1
for REP STOSB, then falls back to the SSE2 test or scalar owner. Scalar
copying consumes count modulo four in bytes, an optional dword, then eight
bytes per loop; those steps use count bits rather than destination alignment.

The large SSE2 path stores a first unaligned 16B block, aligns the following
destination upward and derives the remaining count from the original end.
The 128B loop retains its actual `TEST count,0xFFFFFF00` continuation mask;
the shared 32B loop handles the remaining range. A nonempty trailing range
uses two 16B stores ending at the original buffer end, overlapping already
written bytes. All branches, the shared tail and every return remain in the
complete contribution.

## Evidence and validation scope

Private `.analysis/origin-boundary/memory-copy/` retains the archive provider,
provenance, full attested CPU listing, comparison, traversal and original
ledger rows. The full memmove member and attested listing are retained in
`catch-build/`. Both members come from the installed MSVC 14.44.35207 x86
archives. Both memmove state symbols and every memmove relocation are bound
through the complete independent provider, not a masked ordinary-byte match
alone. The initializer's complete 794B and memmove's complete 1,396B retain
their original boundaries, including all data and alignment.
Private `memory-set/` additionally retains the full memset member/provenance,
attested listing, complete comparison and original ledger row. Its relocation
bindings reuse the CPU provider through its original object hash and locked
target identity, with no new CPU-state inference from the memset fields.

Only origin/boundary classification, evidence, handoff and generated progress
change. All 2,151 protected native input/product hashes are unchanged. Exact
replay scope is **zero units**; these archive identities add no authored or
maintained-source exact credit.
