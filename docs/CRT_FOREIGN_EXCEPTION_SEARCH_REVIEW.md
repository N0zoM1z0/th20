# VCRuntime foreign-exception search

The complete MSVC 14.44.35207 x86 `libvcruntime.lib(frame.obj)` contribution
at `0x00546EFD` identifies one pending library origin in the locked Japanese
TH20 Steamless target. All 309 instruction bytes and the final INT3 at
`0x00547032` agree. The existing 309B instruction extent is unchanged.
This section owns no local data or EH table.

## Translator eligibility is narrower than ellipsis eligibility

STATUS_BREAKPOINT, code 0x80000003, returns before consulting VCRT PTD.
Other exceptions first test the translator at PTD+8. A literal null pointer
skips translation without calling EncodePointer. A nonnull pointer is also
rejected when it equals the independently named EncodePointer(null) result.
The body does not decode other translator pointer values.

Managed exception codes 0xE0434F4D and 0xE0434352 bypass the translator as
well. They still proceed to the later ellipsis search. Eligible exceptions
call the complete CallSETranslator owner with the original frame, context,
FuncInfo, depth and marker. A nonzero result returns immediately. A normal
translator return reports zero and continues searching, as established in
the [control-transfer review](CRT_CATCH_TRANSLATOR_TRANSFER_REVIEW.md).

## Only nonstandard ellipsis catches foreign exceptions

Before searching try blocks, the original verification aborts for a zero
try-block count. The complete GetRangeOfTrysToCheck supplies the iterator
range. Each copied 20B try entry is eligible only when
`tryLow <= currentState <= tryHigh`.

For an eligible try, the helper examines only its last 16B HandlerType.
The TypeDescriptor must be null or have an empty name, denoting ellipsis,
and catch-adjective mask 0x40 must be clear. Installed `ehdata_values.h`
defines that mask as HT_IsStdDotDot: standard C++ catch(...) catches only
C++ exceptions. A typed handler or flagged standard ellipsis is skipped.

An eligible catch enters the complete CatchIt owner with null conversion,
IsRethrow true and recursive false, retaining the original marker and depth.
If CatchIt returns after rethrow, this helper advances to the next try;
it does not claim that the exception was handled. There is no return value
and no local exception normalization beyond the translator protocol.

## Evidence and affected scope

Private `.analysis/origin-boundary/foreign-exception/` retains `review.py`,
`reviewed.json` and the original ledger row. It reuses the full frame member
and bounded attested `foreign-native.txt` in `type-info/`, plus the complete
catch-entry and translator proofs. All 111 listed instructions, branches,
REL32/DIR32 roles and HIGHLOW fields agree, with no omitted instructions.
EncodePointer is checked independently through the PE import directory.
Installed `frame.cpp`, `ehdata.h` and `ehdata_values.h` corroborate the
translator exclusions, range traversal and ellipsis flag contract.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new authored or maintained-source
exact credit.
