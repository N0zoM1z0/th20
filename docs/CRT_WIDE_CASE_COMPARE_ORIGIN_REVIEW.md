# UCRT wide case comparison keeps WORD values and distinct lowering paths

Five complete SDK 10.0.26100.0 x86 contributions match the locked Japanese
TH20 Steamless target: 1,080B/384 instructions and twenty-six REL32/twelve
DIR32 roles. All five existing extents remain unchanged. The public APIs,
locale owners and unbounded ASCII helper are reviewed together with their
actual shared validator, classification and lowercase providers.

| Entry | Bytes | Instructions | Role |
| --- | ---: | ---: | --- |
| `0x0055DEC0` | 75 | 35 | `__ascii_wcsicmp` |
| `0x0055DF10` | 70 | 26 | `_wcsicmp` |
| `0x0055DF60` | 425 | 144 | `_wcsicmp_l` |
| `0x00565D40` | 73 | 29 | `_wcsnicmp` |
| `0x00565D90` | 437 | 150 | `_wcsnicmp_l` |

CodeView confirms cdecl int32 results and const WCHAR* inputs. The bounded
APIs take uint32 counts in UTF16 units, not byte counts; locale APIs add a
locale pointer. Complete arithmetic subtracts zero-extended WORD values,
retaining the full character difference. The bounded source's introductory
-1/0/+1 comment does not describe that result magnitude. No normalization
or signed-short truncation replaces the original subtraction.

## Public dispatch and zero-count validation

Both public entries first test the reviewed locale-changed DWORD. In the
unchanged case, null pointers go to the same physical 40B validator already
reviewed with [stricmp](CRT_STRICMP_ORIGIN_REVIEW.md). Its full ordinary bytes
and both errno/handler relocations agree with each wide member's definition.
It writes global EINVAL and returns 0x7FFFFFFF if the handler resumes.
There is no second physical validator entry or duplicate origin credit.

Valid pointers tail-transfer to the actual ASCII helper. A changed locale
calls the respective locale API with a null locale. The bounded public API
still rejects null pointers when count is zero. Its locale API also validates
left then right before returning zero; that zero-count return precedes locale
acquisition. The underlying ASCII bounded helper instead returns zero before
reading either input. No INT_MAX count restriction is added to these APIs.

The unbounded ASCII helper reads unsigned WORDs, folds only A..Z when raw
values differ and returns their int difference. It stops at a difference or
left NUL. The bounded helper has the same difference semantics plus count
termination; its complete 103B physical owner at `0x00565CD0` was already
reviewed with the [downlevel locale tables](CRT_DOWNLEVEL_LOCALE_TABLE_ORIGIN_REVIEW.md).
Its unchanged source section is reused without another entry or credit.

## Locale guards and asymmetric lowering

Both locale owners retain the established explicit/initial/PTD locale
selection and actual locale/multibyte refresh helpers. They set PTD
sync-disable bit 2 only when previously clear, record that obligation and
clear it on their ordinary result exits only when this call set it. A null
LC_CTYPE name at locinfo+0xA8 selects the actual ASCII helper after locale
acquisition, with the same guard restoration afterward.

For a named locale, the unbounded owner first compares raw WORDs. Equality
skips both lowercase operations. Otherwise it lowers the left WORD, compares
that with the original right WORD and lowers the right only if still unequal.
The bounded owner instead lowers both WORDs on every iteration, including raw
equality. Preserve that difference in provider-call order and conditionality.
Both stop on a nonzero result or mapped left NUL; bounded comparison also
stops after its requested number of units.

For values below 256, the inlined lowering tests the fixed wide UPPER bit
in the reviewed `_wctype` table and consults the locale byte-lowercase map
only when that bit is set. Larger values call the independently reviewed
212B `_towlower_l`, then zero-extend its AX result. The full shared 516B table,
EOF offset and conversion provider retain their
[existing classification evidence](CRT_WIDE_CLASSIFICATION_ORIGIN_REVIEW.md).
These are UTF16-unit operations; no surrogate-pair decoding is inserted.

## Complete boundaries and retained evidence

The two internal MOV EDI,EDI loop-alignment instructions remain within their
sections. All 31 linker INT3 bytes around the selected groups and reused
bounded helper are checked separately from code. No owned static data,
EH record, switch table or additional code padding belongs to the five new
owners. Three real external tail jumps are checked with their complete
relocation fields and independent helper/validator identities.

Private `.analysis/origin-boundary/wide-case-compare/` retains wcsicmp.obj,
provenance, complete locations, CodeView, both attested listings and full
ordinary-byte/relocation/CFG comparisons. It reuses the identical retained
wcsnicmp.obj in `downlevel-locale/`, plus existing narrow validation, locale
state and wide conversion/classification owners. Source is
`ucrt/string/{wcsicmp,wcsnicmp}.cpp` and the internal locale/case helpers.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected hashes remain unchanged. Exact replay scope is **zero
units**, with no new authored or maintained-source exact credit.
