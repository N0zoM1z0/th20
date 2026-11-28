# UCRT floating-output owner and complete cached-locale updater

Two complete Windows SDK 10.0.26100.0 x86 `libucrt.lib(output.obj)`
contributions identify pending library origins in the locked Japanese TH20
Steamless target: the 439B/174-instruction char `type_case_a` at
`0x00549F94` and the 91B/38-instruction `update_locale_slow` at
`0x0054A360`. All 530B/212 instructions and thirteen REL32 fields agree.
Both existing extents remain unchanged, with empty HIGHLOW sets and no local
data, padding or EH table. Every instruction is reachable from its own entry.

## Precision and storage remain one protocol

The selected nonpositional char body uses ECX for this and sets the signed
flag at `+0x1C`. Negative precision becomes thirteen for a/A and six for the
other floating formats. Explicit zero precision becomes one for g/G.

Its formatting buffer begins at this `+0x3C`. It requests capacity for
precision plus 349 characters through the complete char growth provider.
On failure it retains the available buffer and caps precision at count minus
349, then continues. The previously reviewed
[buffer owner](CRT_FORMATTING_BUFFER_ORIGIN_REVIEW.md) supplies both equal
logical halves and preserves allocation failure correctly.

The body selects inline/dynamic output storage, publishes the narrow-string
pointer at `+0x30`, consumes eight bytes from the varargs cursor at `+0x10`
and copies the double into a local eight-byte value. It passes that value,
both buffer pointers/capacities, format, precision, complete 64-bit options,
rounding argument one and cached PTD host to the real fp formatter. Its
status return is ignored; postprocessing follows whenever that call returns.

## Locale-dependent postprocessing and final output state

Alternate form with zero precision calls the complete decimal-point inserter.
Nonalternate g/G calls the complete trailing-zero cropper. Each path checks
the host's locale-status byte at `+0x14` and calls update_locale_slow only
when that byte is zero, then supplies the locale-pointer pair at host `+0xC`.
The two helpers retain their [full locale/copy proof](CRT_DECIMAL_OUTPUT_ORIGIN_REVIEW.md).

A leading minus sets the negative flag and advances the stored narrow-string
pointer past the sign. A leading i/I/n/N clears the leading-zero flag and
changes the stored format byte at `+0x2D` to s, preserving special-value
prefix/padding handling. The original inline length loop publishes the
remaining string length at `+0x34`. Every normal return yields true in AL;
the complete thiscall body has no false-return branch.

Four complete char stream/string, standard/format-validation contributions
have identical bytes and relocation roles at this physical head. They are
retained as compatible full aliases with one canonical origin row. The
positional and wchar_t variants have no complete matches here.

## The locale updater uses complete independent providers

The updater calls the already reviewed required PTD reader at `0x00547EA3`.
It copies PTD locinfo from `+0x4C` into host `+0xC` and multibyte info from
`+0x48` into host `+0x10`. The original explicit locale and multibyte refresh
providers at `0x0055853E` and `0x0055859C` receive those fields, the PTD and
the host's state index at `+4`.

Finally it tests PTD `+0x350` bit 0x2. If clear, it sets that bit and marks
host locale status as two; the already-set branch leaves the status byte
untouched. The complete register/frame return sequence remains in this
thiscall void owner. The target uses the previously reviewed 29B PTD-reader
contribution rather than the unmatched 92B definition carried by output.obj.

## Same-name COMDAT variants resolve the old 89B/91B question

Output.obj provides a full 91B target match. The separately extracted cvt.obj
provides an 89B update_locale_slow with the same decorated name. Both section
auxiliary records specify SelectAny (selection two). Their first 87 raw
bytes and three relocation roles are identical. Only the epilogue differs:

| Contribution | Final frame return sequence |
| --- | --- |
| output.obj, target 91B | MOV ESP,EBP; POP EBP; RET |
| cvt.obj, 89B alternative | LEAVE; RET |

The complete 91B definition supplies this target's comparison owner. The
89B alternative remains a useful negative and is not shortened into a pass.
The earlier cached-locale header probe still emitted no object; no retry or
historical receipt change is needed to establish these archive observations.

## Evidence and affected scope

Private `.analysis/origin-boundary/format-floating-owner/` retains the full
cvt member/provenance, scoped locations, attested listings, complete two-owner
comparison, aliases, both COMDAT variants and original rows. It reuses output.obj
and the complete buffer/decimal/provider proofs. Installed
`corecrt_internal_stdio_output.h` and `corecrt_internal_ptd_propagation.h`
corroborate the same arguments, field order and branches.

The parent's fp-format call was independently identified by cvt.obj's complete
unique 384B ordinary-byte signature at `0x00558F7C`. The subsequent
[complete dispatch/formatting review](CRT_FP_DISPATCH_FORMATTING_ORIGIN_REVIEW.md)
now covers its seven call roles, all direct layout/rounding owners and the
special-value table. The two separate digit-generation providers remain
pending with their own full identity evidence retained.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass; all 2,151 protected native input/product hashes
are unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
