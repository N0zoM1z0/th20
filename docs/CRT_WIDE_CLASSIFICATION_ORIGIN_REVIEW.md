# UCRT wide classification, case mapping and the full ctype table

Five pending library origins are reviewed through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` contributions. All 412 code bytes, the full
516B wide classification table and its four-byte pointer slot agree with the
locked Japanese TH20 v1.00a Steamless target. The table has 258 WORD entries:
EOF, U+0000..U+00FF and a real final U+0100 entry, rather than two padding bytes.

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x0054A476` | 34 | `__acrt_locale_get_ctype_array_value` |
| `0x005521A6` | 36 | `__pctype_func` |
| `0x0055A089` | 105 | `iswctype` |
| `0x00563E25` | 25 | `__acrt_GetStringTypeW` |
| `0x005653D9` | 212 | `_towlower_l` |

All five code sections are complete, with unchanged ledger extents and no
owned alignment or EH table. Required PTD, locale refresh, the legacy guard
and wide mapping adapters retain their existing reviewed owners.

## Lowercase compatibility paths and WEOF

The real wint_t input is a WORD in its cdecl stack slot. WEOF/0xFFFF returns
before constructing the guard or reading the supplied locale. Other input
constructs the reviewed legacy guard and reads its effective code page.

For UTF-8/65001, only values below 128 use the fast path. Other code pages
permit values below 256. The fast path first tests the immutable wide table's
UPPER bit at index `c + 1`; only then does it fetch the locale's narrow lower
map byte at `locinfo + 0x94`. It returns that byte as wint_t. This preserves
the original narrow-code-page interpretation for U+0080..U+00FF in non-UTF-8
locales rather than substituting a generic Unicode case fold.

For a non-UTF-8 value at least 256, a null LC_CTYPE locale name returns the
input unchanged. Remaining paths call the reviewed `__acrt_LCMapStringW` at
`0x0056665E` with LOWERCASE/0x100, one UTF-16 input unit and one output unit.
Mapping failure returns the input; success returns the mapped WORD. The
original zero extensions and conditional PTD own-locale restoration remain.

## Classification widths and dynamic narrow table access

`iswctype` takes WORD character/mask values and returns an integer bitmask.
WEOF returns zero. Values below 256 use the current `_pwctype` pointer at
`0x005B2774` and preserve the full table-word AND mask result. Other values
zero a WORD output, classify one UTF-16 unit through GetStringTypeW with
CT_CTYPE1, then return that word AND mask. API failure returns zero. There is
no locale guard or added errno path in this owner.

The complete 25B cdecl CRT adapter forwards all four arguments to the named
GetStringTypeW stdcall import at `0x0056C194`. The import pops its arguments;
the CRT adapter retains its caller-cleaned public arguments and raw BOOL
result. The wrapper's installed C++ implementation is absent; its full SDK
body, prototype and PE import provide the implementation/identity evidence.

The 34B narrow array helper accepts signed character and integer mask inputs.
An unsigned comparison of `c + 1` against 256 permits EOF/-1 and bytes 0..255.
It returns the selected WORD AND mask; other values return zero without
reading the array. It does not normalize the result to bool or call an
invalid-parameter handler.

The 36B pctype getter obtains required PTD, copies its locale pointer from
+0x4C, conditionally refreshes that slot through `__acrt_update_locale_info`
and returns the effective locale's narrow ctype pointer. It has no arguments
and does not return the fixed wide table.

## Complete shared table and rejected getter candidates

The 516B `_wctype` section at `0x00599140` matches the independent `ctype.obj`
definition and has a unique full-byte location in the target's data sections.
Its final U+0100 WORD is 0x0101 (UPPER plus C1_ALPHA). All entries and source
comments through that final character are retained. The four-byte `_pwctype`
section at `0x005B2774` contains `_wctype + 2`, skipping the EOF entry, with
its complete HIGHLOW relocation. Together they cover all 520 data bytes.

The SDK's six-byte `__pwctype_func` shape has eleven native candidates.
Every candidate loads a different global slot, so all eleven are rejected.
No getter origin is inferred from the shared load/return spelling. Other
narrow/upper-case SDK candidates likewise remain pending where complete
byte matches are absent.

## Evidence and affected scope

Private `.analysis/origin-boundary/case-conversion/` retains `towlower.obj`,
`ctype.obj`, `iswctype.obj`, `_wctype.obj` and `getstringtypew.obj`, complete
attested listings, `review.py` and `reviewed.json`. The audit covers all five
whole code contributions, both complete data sections, every branch/relocation,
independent whole-table location, PE import and rejected getter roles.
Installed sources are `ucrt/convert/{towlower,iswctype,_wctype}.cpp`,
`ucrt/locale/ctype.cpp`, `corecrt_internal.h` and the public `ctype.h`.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
