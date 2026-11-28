# UCRT downlevel locale tables and preserved Konkani lookup failure

Five pending origins are now library exclusions through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` contributions: four bodies in
`lcidtoname_downlevel.obj` and the ASCII comparator in `wcsnicmp.obj`. All 423
instruction bytes, one trailing INT3, both 228-record tables and 389 complete
literal sections agree with the locked Japanese TH20 v1.00a Steamless target.
The reverse table contains an original ordering defect that must be preserved.

## Complete entries and tables

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x00562532` | 67 | `GetTableIndexFromLcid` |
| `0x00562575` | 84 | `GetTableIndexFromLocaleName` |
| `0x005625C9` | 125 | `__acrt_DownlevelLCIDToLocaleName` |
| `0x00562647` | 44 | `__acrt_DownlevelLocaleNameToLCID` |
| `0x00565CD0` | 103 | `__ascii_wcsnicmp` |

The first four whole contributions fill `0x00562532..0x00562672`, including the
INT3 at `0x00562646`. The 125B conversion body retains its terminal nonreturning
failure call. The comparator's complete 103B contribution includes the nine-byte
loop NOP at `0x00565CE7`. No extent is shortened to omit an error path or padding.

The forward table at `0x0059B800` and reverse table at `0x0059C920` are each
1,824B: 228 records of two 32-bit fields. The forward records pair LCIDs with
UTF-16 names; reverse records pair names with forward-table indices. All 456
pointer fields, record values and complete referenced string sections agree
with the SDK member. The 389 literal sections total 4,504B, giving 8,152B of
complete data. The reverse indices form a permutation of `0..227`, with each
name agreeing case-insensitively with its corresponding forward record.

## Lookup behavior and original ordering defect

The LCID search starts with bounds 0 and 227, compares through signed subtraction
and returns the middle index or `-1`. The name search uses the same bounds and
calls the selected ASCII comparator with a limit of 85 UTF-16 code units.
The comparator loads unsigned words, folds only ASCII A-Z when values differ,
and returns their integer difference. It stops on mismatch, NUL or exhausted
count; zero count returns zero before reading either string. There is no locale
lookup or separate argument validation in this helper.

The forward LCIDs are strictly ascending. The reverse names are not fully
ascending under that comparator: zero-based records 128, 129 and 130 are `kok`,
`kok-in` and `ko-kr`. Both Konkani names belong after `ko-kr` in ASCII order.
The same inversion occurs in the installed SDK source and object; it is not a
Ghidra decoding or relocation discrepancy.

A finite model of the completely compared binary-search algorithm over all 228
original records finds every stored name except `kok` and `kok-in` (forward
indices 63 and 137). Their wrapper therefore returns zero under that algorithm.
This is an inference from the full code/table evidence, rather than a runtime
game test. Sorting a private control copy makes every stored name reachable,
confirming that the failed sortedness assumption changes behavior. Keep the
original order when reconstructing these tables.

## Conversion validation, output and failure paths

LCID-to-name rejects zero, `LOCALE_USER_DEFAULT` (`0x400`) and
`LOCALE_SYSTEM_DEFAULT` (`0x800`), null output with a positive count, negative
counts and absent LCIDs. For a found name it calls wcsnlen with limit 85.
Count zero queries the required size without copying; a positive count must
exceed the name length. Successful output returns length plus the NUL. The
invariant locale record has the empty string and therefore requires one unit.

The secure copy is at `0x00548100`; a nonzero result enters the original inline
five-zero-argument call to `__invoke_watson` at `0x005480CC`. That branch does
not return an ordinary conversion failure. The length helper is at
`0x00548430`. These named SDK dependencies receive no body credit here.

Name-to-LCID rejects null input, an absent name or an index outside `0..227`,
otherwise returning the forward record's LCID. Its normal callers and the
LCID-to-name caller are the already reviewed
[locale API fallback wrappers](CRT_LOCALE_WINAPI_WRAPPER_ORIGIN_REVIEW.md).
The downlevel helpers take cdecl arguments without the Ex APIs' flags.

## Evidence and affected scope

Private `.analysis/origin-boundary/downlevel-locale/` retains both SDK members,
bounded attested `native.txt` and `compare-native.txt`, locations, `review.py`
and `reviewed.json`. The audit compares all five whole code contributions,
complete branch and HIGHLOW sets, both whole tables and every full literal.
It checks table/index correspondence, records the ordering inversion and retains
the exhaustive finite search result with its sorted-copy control. Installed
source is `ucrt/locale/lcidtoname_downlevel.cpp` and `ucrt/string/wcsnicmp.cpp`.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
