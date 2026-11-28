# UCRT locale wrappers, compatibility callback and direct Win32 forwarding

Eighteen pending origins are now library/compiler exclusions, with one recovered
3B SEH entry. Seventeen complete Windows SDK 10.0.26100.0 x86 `libucrt.lib`
`winapi_thunks.obj` code contributions agree with all 814 original bytes in the
locked Japanese TH20 v1.00a Steamless target. The shared callback state and full
28B scope table establish the compatibility owner's complete boundaries.

## Entries and complete ownership

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x00557BE6` | 34 | stdcall locale callback adapter |
| `0x00557C08` | 100 | guarded enumeration primary partition |
| `0x00557C6C` | 3 | recovered SEH finally entry |
| `0x00557C6F` | 12 | shared unlock funclet |
| `0x00558021` | 31 | `__acrt_AreFileApisANSI` |
| `0x00558040` | 93 | `__acrt_CompareStringEx` |
| `0x0055809D` | 84 | `__acrt_EnumSystemLocalesEx` |
| `0x005580F1` | 12 | `__acrt_FlsAlloc` |
| `0x005580FD` | 12 | `__acrt_FlsFree` |
| `0x00558109` | 13 | `__acrt_FlsGetValue2` |
| `0x00558116` | 12 | `__acrt_FlsGetValue` |
| `0x00558122` | 12 | `__acrt_FlsSetValue` |
| `0x0055812E` | 63 | `__acrt_GetLocaleInfoEx` |
| `0x0055816D` | 60 | `__acrt_GetUserDefaultLocaleName` |
| `0x005581A9` | 12 | `__acrt_InitializeCriticalSectionEx` |
| `0x005581B5` | 56 | `__acrt_IsValidLocaleName` |
| `0x005581ED` | 63 | `__acrt_LCIDToLocaleName` |
| `0x0055822C` | 93 | `__acrt_LCMapStringEx` |
| `0x00558289` | 49 | `__acrt_LocaleNameToLCID` |

The first four partitions fill `0x00557BE6..0x00557C7A` without gaps or padding.
The three guarded-call partitions constitute one complete 115B contribution.
The other fifteen bodies fill `0x00558021..0x005582B9`, also contiguously.
Every original ordinary byte, HIGHLOW field, branch and external tail is kept.

## Same-shaped wrappers require real API identities

CompareStringEx and LCMapStringEx have identical 93B ordinary bytes after
relocation fields are masked. Their independently identified
[cache getters](CRT_WINAPI_THUNK_CACHE_ORIGIN_REVIEW.md) distinguish them:
`0x00557CA5` is CompareStringEx and `0x00557DFD` is LCMapStringEx. Their fallback
IAT slots independently name CompareStringW at `0x0056C0C8` and LCMapStringW at
`0x0056C0C4`. Swapping those roles fails both checks despite byte-shape agreement.

Both wrappers forward all nine arguments to a CFG-checked resolved pointer.
Fallback converts the locale name with zero flags, then supplies the six legacy
arguments. The version/reserved/parameter arguments have no legacy counterpart.
Both return with `RET 36`. The five 12B direct forwarding bodies also have the
same ordinary bytes; PE import descriptors distinguish their FlsAlloc, FlsFree,
FlsGetValue, FlsSetValue and InitializeCriticalSectionEx destinations.

GetLocaleInfoEx falls back through locale-name conversion to GetLocaleInfoW.
GetUserDefaultLocaleName combines GetUserDefaultLCID with the selected
LCIDToLocaleName wrapper and zero flags. IsValidLocaleName converts with zero
flags and calls IsValidLocale with `LCID_INSTALLED` (1). The LCID/name wrappers
call the cdecl downlevel helpers at `0x005625C9` and `0x00562647`, dropping their
flags on fallback. Those two callee bodies remain the next review scope; the
SDK's named dependencies identify their roles without granting body credit.

AreFileApisANSI returns TRUE when unavailable. FlsGetValue2 reads function slot
3 at `0x005E600C` and tail-jumps directly through EAX. It performs no local
lookup, sentinel check or CFG check. The SDK source explicitly requires a prior
capability check; preserve that caller responsibility when reconstructing it.

## Enumeration fallback and complete SEH cleanup

EnumSystemLocalesEx normally forwards its four arguments to the CFG-checked
resolved API. Its compatibility path supplies lock ID 4 and the callback to the
115B guarded owner. The owner acquires the established CRT lock, publishes the
callback at `0x005E565C`, and calls EnumSystemLocalesW with `LCID_INSTALLED`.
The 34B stdcall adapter reads that callback, CFG-checks it, and passes the locale
string with flags and parameter both zero. The fallback does not forward the
Ex wrapper's flags, parameter or reserved pointer.

On normal completion the owner clears the callback slot, retains the BOOL
result and calls the 12B unlock funclet. Its exception cleanup begins three
bytes earlier: `MOV ESI,[EBP-0x1C]` at `0x00557C6C`, then fallthrough to the same
unlock code. Clearing the callback occurs before this finally region and is
not repeated by the exception cleanup. No exception-catching branch is added.

The full scope table at `0x005AC500` has the original `-2,0,-44,0` header and
`-2,0,0x00557C6C` record. Its HIGHLOW pointer independently retains the missed
3B entry. Ghidra lists the primary and unlock bodies but omits those three bytes
and their data reference; pinned decoding and the complete object/table
comparison cover them. These are compiler partitions sharing the parent's
frame, rather than independent ordinary C functions.

The 4B callback state follows the separately reviewed 23 module handles exactly:
their end sentinel is `0x005E565C`. The cache retirement loop's comparison with
that address does not make this callback slot a twenty-fourth module handle.

## Evidence and validation scope

Private `.analysis/origin-boundary/locale-wrappers/` retains bounded attested
`native.txt`, `enum-native.txt` and `references.txt`, SDK member diagnostics,
`review.py` and `reviewed.json`. It reuses the preserved
`thunk-cache/winapi_thunks.obj` with the same object hash and previously reviewed
getter placements. The audit checks seventeen whole code sections, all branches,
ordinary bytes and HIGHLOW sets, actual getter/import roles, the complete 28B
scope table and 4B callback slot, plus the existing full 128B function table.
Same-shaped wrapper substitutions are explicit negative cases. Installed source
is `ucrt/internal/winapi_thunks.cpp`.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
