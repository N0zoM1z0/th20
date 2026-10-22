# ECL wire-header extents and exact instruction resolution

CORE/EXACT-126 accepts the complete 54-byte `EclLoader::instruction` at
`0x0053E8E0`. The complete 876-byte `append` at `0x0053FE60` remains nonexact.
The earlier [buffer protocol](ECL_BUFFER_RECONSTRUCTION.md) still describes
borrowing, ordering, failures and recursive includes. Current totals belong in
[the handoff](RE_HANDOFF.md) and [generated progress](PROGRESS.md).
The later [registration and insertion review](ECL_BUFFER_REGISTRATION_EXACT_RECONSTRUCTION.md)
closes the complete registration root and its reviewed supporting units.

## Native boundaries and wire storage

The locked PE and attested Ghidra listing agree on all 19 instruction heads in
instruction resolution and all 276 heads in registration. Their complete extents
end with `ret 8` and `ret 4`, respectively. Neither has missing listing heads,
associated switch tables or direct branches outside the reviewed interval.
No comparison extent is shortened.

The following inter-entry intervals contain ten and four `0xCC` bytes:
`0x0053E916..0x0053E91F` and `0x005401CC..0x005401CF`. The next independently
listed entries start at `0x0053E920` and `0x005401D0`. The fresh instruction
function occupies its complete 54-byte COFF section; it supplies no subsequent
fill contribution. Those inter-entry bytes receive no credit in this batch.

Registration consumes magic at +0, unsigned version at +4, unsigned include size
at +6 and unsigned subroutine count at +0x10. The offset table starts after the
complete 36-byte fixed file header and the variable include block. Its include
callback independently receives the byte immediately after that fixed header.
The remaining fixed-header bytes stay opaque. Maintained `EclFilePrefix` now
represents the complete wire extent, including the unknown bytes +0x12..+0x23;
these are file bytes, not invented object padding.

Instruction resolution skips a complete 16-byte subroutine prefix before adding
the signed byte offset. A local opaque `EclSubroutinePrefix` represents that
extent without assigning names or meanings to unreviewed fields. It is a wire
view, not an assertion about an original C++ owner or RTTI name.

## Compiler observation and strict acceptance

With the locked MSVC x86 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc profile, byte indexing emits `MOV 1; SHL 4` for the subroutine skip.
Addressing the next complete prefix emits the native `MOV 16; SHL 0`. This
accounts for the two previously documented structural differences in the whole
54-byte method. The source retains the actual record table reference and performs
the final signed displacement in bytes, after crossing the prefix.

The single REL32 at +0x1C targets the record-index helper `0x0053B590`. Its
independent anchor already occurs in accepted `ecl_loader_subroutine_index`;
the native helper's complete producer/consumer and eight-byte record-stride
evidence predates this comparison. No compared relocation field is solved to
obtain its destination. A fresh production build and the canonical comparator
pass every byte and this relocation in unit `ecl_loader_instruction`.

The same complete-prefix representation reduces the whole registration output
from 878 to 876 bytes. Six structural bytes at offsets 485, 486, 487, 488, 490 and
492 still disagree in the subroutine-buffer address calculation. Reversing the
addition operands preserves those differences; a buffer-subscript hypothesis
produces 901 bytes and is rejected. Neither attempt receives exact credit.
There are no shaping locals, byte arrays containing target code, assembly or
source-profile branches.

## Independent origin review

Both complete roots are classified as application-authored, separately from
their exact status. Registration implements the native SCPT/version-one format,
Spt file-header diagnostic routes at `0x00576AD8` and `0x00576AFC`, borrowed
subroutine-name/header publication, stable lexical insertion and recursive
game-script includes. These are custom serialization and resource semantics,
rather than a generic compiler or standard-library implementation.

Instruction resolution consumes those custom records and their fixed subroutine
prefix. Its independently maintained native VM consumer at `0x005403D0` and name
selection at `0x00540340` corroborate that domain. The generic vector indexing,
array indexing, iterator machinery and CRT calls remain separate dependencies;
they acquire no authored credit from these two reviews. Original source names
and translation-unit placement are not inferred.

## Semantics, reproduction and protected products

The existing O2/UBSan buffer and actual VM/Manager/Stack tests continue to exercise
the production methods. The buffer fixture additionally checks a negative offset
which lands at the subroutine prefix and a positive four-byte offset. These
distinguish byte displacement from accidentally scaling by the new prefix type.
The unchecked valid-buffer domain and original failure/publication semantics
remain unchanged. Complete game resource ownership and startup remain open.

Reproduce the new unit with `scripts/repo-python scripts/build.py --unit
ecl_loader_instruction`, followed by `scripts/repo-python
scripts/compare-coff-function.py --unit ecl_loader_instruction --json`.
The canonical object and sibling receipt are
`build/core126-canonical/EclLoaderBuffer.obj` and
`build/core126-canonical/EclLoaderBuffer.receipt.json`.
Those checkpoint products are superseded by CORE/EXACT-127; their original
input/receipt closure is archived, and current paths come from match-units.toml.

The original 160 canonical objects do not include EclLoaderBuffer.cpp. Their
original immutable receipts therefore remain valid under the reviewed
[freshness policy](ORACLES.md). Only this newly admitted translation unit needs
fresh MSVC compilation. Private boundary, compiler and native evidence is under
`.analysis/core126-*`; raw decompiler text is not maintained source.

The frozen graph passes all 828 strict units across 161 objects and 160,975
disjoint comparison bytes. All 80 public tests pass in 332.833 seconds.
Target, tracking, reference, build and progress gates pass. Retirement removes
ten superseded probe products (437,842 bytes) after preserving their original
input closures and receipts in a 228,477-byte archive. All 322 canonical product
hashes remain unchanged; all 828 units strictly replay after cleanup without
another compiler invocation.
