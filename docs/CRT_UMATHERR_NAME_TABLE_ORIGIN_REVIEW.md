# UCRT umatherr name lookup, callback result and control-word order

The complete 255B/84-instruction entry at `0x00554210` is `__umatherr`
from SDK 10.0.26100.0 x86 fpexcept.obj in the locked Japanese TH20 Steamless
target. Its full 29-record name table, all 29 string contributions and all
seven REL32/31 DIR32 roles are reviewed. The existing instruction extent
remains unchanged; there is no owned EH or embedded jump table.

CodeView establishes a cdecl double return with six arguments: int32 type,
unsigned int32 opcode, three doubles (arg1, arg2, result), and unsigned int32
saved control word. The reviewed except1 caller supplies zero for arg2;
umatherr itself preserves its caller-supplied second argument.

## All 29 records and literal contributions remain owned

The complete 232B table is independently located at `0x00599490` by its
29 ordinary opcode keys before reading its name pointers. Every eight-byte
record contains a 32-bit opcode and pointer. All 29 pointer fields have the
expected HIGHLOW roles and point to complete matching strings. The 151B of
strings include their terminators; 49 following zero alignment bytes are
also checked. The table ends immediately before the string pool.

The code scans records in their original nonnumeric order and stops at the
first matching opcode. It checks the resulting name pointer even though all
current table entries are nonnull. No matching entry leaves the local name
null and selects the original fallback. There is no extra function entry for
the inlined get_fname loop.

Selected bindings connect the already reviewed math callers:

| Opcode | Name |
| --- | --- |
| 5 | sqrt |
| 11, 12 | floor, ceil |
| 13, 14, 15, 16 | acos, asin, atan, atan2 |
| 20, 26, 27, 29 | exp, log, log10, pow |
| 30, 32 | sin, tan |

Private evidence retains every record, including hyperbolic, decomposition,
Bessel and nextafter names. Names with other local copies retain their
actual table-selected instances and complete contents.

## Control restoration precedes callback and errno processing

The no-name path restores the supplied raw control word through ctrlfp with
mask `0xFFFF`. It then sets errno 33 for type 1, errno 34 for types 2/3, and
loads the original result into ST(0). Other types have no errno fallback here.

With a name, the function initializes the full 32B exception record from the
name, original type, both argument doubles and result double. It restores
the raw control word before invoking the already reviewed user-matherr bridge.
The bridge supplies the guarded callback behavior and integer handled result.
There is no subsequent control-word restore in umatherr, so callback control
changes remain in effect on its return path.

A nonzero handled result suppresses errno fallback. Otherwise the function
uses the original type retained in ESI to select the same 33/34 cases; a
callback's edits to the record type do not change this selection. Every
callback path loads the record's possibly modified retval into ST(0), including
the unhandled path. Keep that double-return contract and writeback order.

## Evidence and affected scope

Private `.analysis/origin-boundary/umatherr/` retains the full attested listing,
unique table/code locations, complete comparisons, all name records and original
rows. It reuses fpexcept.obj in `math-error/`, the CodeView signature in
`math-special-round/`, and the reviewed ctrlfp, errno and callback providers.
The matching tran implementation source is absent from the installed snapshot;
archive/native bodies and the established record/caller contracts supply the
implementation evidence. Fifteen original INT3 bytes before the function and
one after it are retained, up to the reviewed aligned_free entry.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
