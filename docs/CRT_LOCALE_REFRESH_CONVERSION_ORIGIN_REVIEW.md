# UCRT locale refresh identities and conversion flag rules

Eight pending library origins are reviewed through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` members `locale_update.obj`,
`multibytetowidechar.obj` and `widechartomultibyte.obj`. All 632 code bytes,
complete branch/HIGHLOW sets and actual global/callee/import roles agree with
the locked Japanese TH20 v1.00a Steamless target. Ordinary bytes alone cannot
distinguish either pair of locale/multibyte refresh helpers.

## Complete entries and same-shaped refresh helpers

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x00558511` | 45 | `__acrt_update_locale_info` |
| `0x0055853E` | 49 | explicit locale-info refresh |
| `0x0055856F` | 45 | `__acrt_update_multibyte_info` |
| `0x0055859C` | 49 | explicit multibyte-info refresh |
| `0x0055DCF9` | 152 | `filter_mbtowcs_flags` |
| `0x0055DD91` | 42 | `__acrt_MultiByteToWideChar` |
| `0x0055DDBB` | 144 | `filter_wcstomb_flags` |
| `0x0055DE4B` | 106 | `__acrt_WideCharToMultiByte` |

The four refresh bodies fill `0x00558511..0x005585CC` (188B); the conversion
family fills `0x0055DCF9..0x0055DEB4` (444B). Both intervals and all eight SDK
contributions are complete, with no owned alignment or data section omitted.
Ledger sizes stay unchanged.

The 45B pair has identical ordinary bytes when relocation fields are masked,
as does the 49B pair. Locale roles use current data at `0x005E5664` and the
reviewed thread updater at `0x00560B88`. Multibyte roles use current data at
`0x005E596C` and updater `0x0055EE1E`. The global sync mask is shared at
`0x005B29F8`. Both actual pointer and updater roles reject swapping the names.
The general locator consequently reports two candidates for each refresh role;
that ambiguity is resolved through these dependencies.

Each void, cdecl helper compares the caller's pointer with current global data,
then tests PTD own-locale flags at +0x350 against the global mask. Only a
different pointer and zero mask intersection permit refresh. The explicit
versions compare the global pointer indexed by `state_index * 4`; they still
call the same no-argument thread updater and store its result through the
caller's pointer. They do not add index validation or a different updater ABI.
This completes the helper roles used by the
[legacy locale guard](CRT_LOCALE_INFO_COPY_ORIGIN_REVIEW.md).

## Exact numeric code-page flag cases

Let Z contain these original code-page IDs:

`42, 50220, 50221, 50222, 50225, 50227, 50229, 57002..57011, 65000`.

| Direction | Code-page set | Flags passed to the Win32 API |
| --- | --- | --- |
| multibyte to wide | Z | zero |
| multibyte to wide | 54936 or 65001 | input AND 8 |
| multibyte to wide | all other pages | input unchanged |
| wide to multibyte | Z, 54936 or 65001 | zero |
| wide to multibyte | all other pages | input AND `0xFFFFFF7F` |

These are the full original sparse branch trees, not a shared generic flag
mask. The wide direction removes bit 0x80 on every ordinary-page path; the
multibyte direction leaves ordinary-page flags intact. An isolated model of the
fully decoded filter branches enumerates all 65,536 sixteen-bit code-page IDs
and checks selected UINT32 boundary/flag values. It confirms the exact case
sets without invoking Win32 conversion or executing the game.

## Wrapper conventions and default-character outputs

The 42B CRT multibyte wrapper is cdecl with six arguments. It calls its local
filter, then the independently named MultiByteToWideChar stdcall import at
`0x0056C124`, forwarding the other arguments and integer result. The 106B
wide wrapper is cdecl with eight arguments and calls WideCharToMultiByte at
`0x0056C108` after its separate filter. PE import descriptors establish both
destinations; decorated SDK relocation names and native call sites establish
argument widths. Neither CRT wrapper pops its public arguments on return.

For code pages 65000/65001, the wide wrapper substitutes null for both
default-character pointers. If the caller supplied a used-default flag pointer,
it first clears the full BOOL/DWORD at that address, then passes null to the
Win32 API for that output. Other pages preserve both pointers. This rewrite
applies only to those two IDs, independently of the broader zero-flag set.
The original pre-call write is retained even if the conversion later fails.

The wrappers do not add locale lookup, errno handling or retry logic. Their
filters and calling conventions are the complete original adapter behavior.
The multibyte thread updater is now covered by the
[complete synchronization/publication review](CRT_MULTIBYTE_UPDATE_BOUNDARY_REVIEW.md),
including its corrected primary and complete SEH/return/abort ownership.

## Evidence and affected scope

Private `.analysis/origin-boundary/locale-refresh-conversion/` retains the three
SDK members, bounded attested `refresh-native.txt` and `conversion-native.txt`,
locations, `review.py` and `reviewed.json`. The audit checks eight whole code
sections, complete instruction coverage, all branches/HIGHLOW fields, explicit
same-shape negative cases and PE import roles. There is no locally owned data
or EH contribution outside the selected code sections.

`flag-model.py` and `flag-model.json` retain the bounded decoded-branch model
and exact numeric case lists. Refresh source is the installed
`ucrt/locale/locale_update.cpp`; conversion identity and implementation evidence
come from the complete SDK members, with prototypes and callers in the
installed internal headers/locale sources. Global pointer arrays and masks are
external dependencies. Only classification, focused evidence, handoff and
generated progress change. All 2,151 protected native input/product hashes
remain unchanged. Exact replay scope is **zero units**, with no new authored
or maintained-source exact credit.
