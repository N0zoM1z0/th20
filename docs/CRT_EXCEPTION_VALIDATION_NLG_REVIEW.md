# CRT image validation, SSE2 exception repair and NLG markers

Nine complete installed CRT code contributions establish nine pending
origins and three recovered entries in the locked Japanese TH20 Steamless
target. All 518 instruction bytes, 39 INT3 bytes and 44B of SEH/NLG data
agree. The original 186B readonly-image owner is partitioned without losing
or duplicating bytes; every other existing extent remains unchanged.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x005435EA` | 3 | fastcall guard-check nop |
| `0x0054769C` | 48 | context-record validator |
| `0x00547B10` | 12 | NLG Notify1 |
| `0x00547B20` | 31 | NLG Notify and shared Go/dispatch tail |
| `0x00547B40` | 3 | NLG Call/Return2 |
| `0x005671A0` | 67 | FindPESection |
| `0x005671F0` | 137 | IsNonwritableInCurrentImage primary |
| `0x00567279` | 19 | recovered AV filter |
| `0x0056728C` | 3 | recovered exception entry |
| `0x0056728F` | 27 | recovered failure continuation |
| `0x005672B0` | 49 | ValidateImageBase |
| `0x0056746F` | 119 | default SSE2 exception filter |

The providers are libcmt.lib's `pesect.obj`/`x86_exception_filter.obj` and
libvcruntime.lib's `jbcxrval.obj`/`exsup.obj` in the installed MSVC 14.44.35207
context. The legacy EH3 validator member has no complete location here.

## PE section arithmetic and readonly-image semantics

ValidateImageBase checks MZ, the PE signature at base+e_lfanew and PE32
optional-header magic 0x10B, returning a normalized BOOL. It adds no bounds
check for e_lfanew, header lengths or the complete image. PE32+ is not accepted.

FindPESection obtains NumberOfSections and SizeOfOptionalHeader from the PE
file header, then scans 40B section headers in their original order. It
returns the first section satisfying unsigned
`VirtualAddress <= rva < VirtualAddress + VirtualSize`. The upper-bound
addition remains unchecked. It neither substitutes SizeOfRawData nor sorts
sections or checks SizeOfImage.

IsNonwritableInCurrentImage uses the linker ImageBase, independently confirmed
as `0x00400000` by the locked PE header. It validates that base, subtracts it
from the target address using the native 32-bit arithmetic, then finds a
section. Success is exactly the absence of IMAGE_SCN_MEM_WRITE in that
section's Characteristics. The function does not dereference the target
itself or query current page protections. This is the slot check used by
the previously reviewed SEH4 destruction-callback gate.

The original 186B owner contains 137B primary, a 19B exception filter, a 3B
exception entry and a 27B failure continuation. Ordinary failures and AV
recovery share the zero-result continuation, which restores FS:[0], saved
registers and the frame. The filter accepts only STATUS_ACCESS_VIOLATION,
0xC0000005; other exceptions continue search. The complete 28B SEH table at
`0x005AC720` has header `-2,0,-40,0` and record
`-2,0x00567279,0x0056728C`. Its two original relocated targets establish
the entries omitted by Ghidra. Whole-section comparison and pinned decoding
retain all 22 missing instruction bytes. The four disjoint partitions cover
the same full 186B interval exactly once.

## Context stack bounds and the real guard nop

The 48B context validator first compares the current guard-check pointer
at `0x0056C37C` with the real fastcall nop at `0x005435EA`. If equal it
returns before reading the context. Otherwise it reads the TEB through
FS:[0x18], obtains CONTEXT.Esp at +0xC4 and checks the inclusive range
`StackLimit <= Esp <= StackBase`. The TIB fields are +8 and +4. A value
outside those bounds executes fastfail 13; there is no added null check.

The nop is the full three-byte `RET 0` contribution. Thirty-six ordinary
byte candidates exist, but the complete context validator's named relocation
selects this one. The on-disk guard pointer also contains that address, with
its original HIGHLOW. This is the initial image state; the function still
retains its conditional validation branch. The separate weak 10B
ReadNoFence/ReadPointerNoFence candidates at `0x0040B2A0` have no reviewed
caller role and receive no origin claim from this member.

## SSE2 aggregate exception codes

The default filter returns its input unchanged when `__isa_available < 1`,
or when the code is neither STATUS_FLOAT_MULTIPLE_FAULTS/0xC00002B4 nor
STATUS_FLOAT_MULTIPLE_TRAPS/0xC00002B5. Otherwise it reads MXCSR without
changing it and considers exception flags that are both set and unmasked.
The native fixed priority is:

| First active condition | Returned status |
| --- | --- |
| invalid operation | 0xC0000090 |
| divide by zero | 0xC000008E |
| denormal | 0xC0000090, invalid operation |
| overflow | 0xC0000091 |
| underflow | 0xC0000093 |
| precision/inexact | 0xC000008F |
| none | original aggregate code |

The code XORs MXCSR with 0x3F and tests paired mask/status bits. In
particular, denormal maps to invalid operation rather than the denormal
operand status. The ISA cell at `0x005E5288` remains a named external
dependency without new ownership credit for its initializer.

## NLG shared record, tail and debugger markers

The complete writable record at `0x005B2640` is four DWORDs: signature
0x19930520, destination, code and frame pointer. The last three start at zero;
all sixteen bytes match the independent exsup data contribution.

Notify loads its code from the stack. Notify1 uses ECX and jumps directly
to Go at Notify+11/`0x00547B2B`. That shared tail stores ECX at record+8,
EAX destination at +4 and EBP frame at +12, preserving the original
registers through the native push/pop sequence. Both paths retain RET 4.
The Dispatch/Dispatch2 aliases at Notify+23 are debugger marker addresses
inside the same complete owner, without extra physical entries.

NLG Call is exactly `CALL EAX; RET`; the final RET is also Return2's marker.
Its callback target belongs to the caller. The record writes and markers
are the complete observed notification mechanism; no logging or additional
callback is introduced. These roles close the named NLG dependencies of
the reviewed SEH4 finally and handler-transfer paths.

## Complete extents and affected scope

The three PE contributions include 13, 6 and 15 following INT3 bytes. The
two NLG notification heads have four and one following INT3 bytes. All 39
alignment bytes are compared along with the nine whole code sections.
The complete 28B SEH and 16B NLG sections form the 44B owned data scope.

Private `.analysis/origin-boundary/exception-validation/` retains the full
members, bounded attested listings, complete search/relocation results,
`review.py`, `reviewed.json` and original ledger rows. Every ordinary byte,
branch/call, REL32/DIR32 and PE HIGHLOW is checked, including Notify1's
branch into its canonical tail owner. Source corroboration is the installed
`vcruntime/{pesect,jbcxrval}.c`, `vcruntime/x86_exception_filter.cpp` and
the NLG record layout in `i386/exsup.inc`; the full exsup artifact and native
instructions provide the notification body evidence.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**; no authored or maintained-source exact credit is added.
