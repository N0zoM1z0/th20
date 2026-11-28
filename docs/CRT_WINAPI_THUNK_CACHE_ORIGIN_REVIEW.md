# UCRT late-bound API cache and locale capability identity

Eighteen complete entries belong to the UCRT late-bound API cache. Seventeen
pending origins are now library/exclude; the existing library head at
`0x00558390` receives a corrected semantic role. Complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` member `winapi_thunks.obj` contributions match
979 instruction bytes, one trailing INT3 byte and 1,934 bytes across all 52
referenced data sections in the locked Japanese TH20 v1.00a Steamless target.

## Complete entries and data ownership

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x00557C7B` | 42 | `try_get_AreFileApisANSI` |
| `0x00557CA5` | 43 | `try_get_CompareStringEx` |
| `0x00557CD0` | 43 | `try_get_EnumSystemLocalesEx` |
| `0x00557CFB` | 43 | `try_get_GetDateFormatEx` |
| `0x00557D26` | 43 | `try_get_GetLocaleInfoEx` |
| `0x00557D51` | 43 | `try_get_GetTimeFormatEx` |
| `0x00557D7C` | 43 | `try_get_GetUserDefaultLocaleName` |
| `0x00557DA7` | 43 | `try_get_IsValidLocaleName` |
| `0x00557DD2` | 43 | `try_get_LCIDToLocaleName` |
| `0x00557DFD` | 43 | `try_get_LCMapStringEx` |
| `0x00557E28` | 43 | `try_get_LocaleNameToLCID` |
| `0x00557E53` | 204 | `try_get_function_slow` |
| `0x00557F20` | 99 | `try_load_library_from_system_directory` |
| `0x00558390` | 11 | `__acrt_can_use_vista_locale_apis` |
| `0x0055839B` | 55 | `__acrt_eagerly_load_locale_apis` |
| `0x005583D2` | 35 | `__acrt_initialize_winapi_thunks` |
| `0x005583F5` | 49 | `__acrt_tls2_supported` |
| `0x00558426` | 54 | `__acrt_uninitialize_winapi_thunks` |

The slow resolver's complete object contribution is 205B, including the INT3
at `0x00557F1F`. Its terminal abort path is retained. Every selected body has
full original instruction coverage and complete ordinary-byte/HIGHLOW agreement.

The full referenced data set includes the 32-entry function-pointer array at
`0x005E6000` (128B), 23 module handles at `0x005E5600` (92B), the 23-pointer
module-name table, every complete referenced module/API string and candidate
module-ID array, plus both UTF-16 loader-prefix literals. Array sizes, pointer
fields and all literal bytes agree. The module handles are zero-filled virtual
data; the function-pointer section also begins with zero entries in the image.

## Correcting the 11B helper's identity

The previous lifetime review assigned `0x00558390` to `__acrt_thread_attach`
because its eleven ordinary bytes matched that SDK contribution. That assignment
was wrong: the generic CALL/TEST/SETNZ/RET shape also implements several API
capability predicates. There was no independent thread-attach caller binding.

The actual callee at `0x00557CA5` is a complete CompareStringEx accessor. It
reads function slot `0x005E6004`, passes ID 1, references the full
`CompareStringEx` string at `0x00599D1C`, and uses candidate module IDs `[8,18]`
(the string API set and kernel32). These independent roles agree with
`__acrt_can_use_vista_locale_apis`, whose complete SDK relocation names that
accessor. They reject both thread attach and the same-shaped xstate predicate.

The old private lifetime object/report remain as failed-hypothesis evidence.
`reviewed.json` here records the rejected role and a negative check: the old
thread-attach contribution still agrees in ordinary bytes, but its callee role
does not agree with the fully identified accessor. No maintained source or
canonical manifest binding used the mistaken name/address. The library origin
and lack of authored/exact credit remain unchanged; only the semantic ledger
label and affected evidence are corrected.

## Raw cache states, loading and protection

Fast accessors distinguish raw zero (not attempted), raw pointer (resolved) and
`-1` (failed lookup). Zero enters the slow resolver; `-1` returns null without
another lookup. These are raw pointers/sentinels, separate from the
[cookie-encoded initialization slots](CRT_UCRT_LIFETIME_CALLBACK_ORIGIN_REVIEW.md).

The slow path visits candidate module IDs and uses the matching module cache.
A failed load publishes `-1`. A successful load exchanges its handle into the
slot; if another thread already published a handle, the duplicate reference is
released through FreeLibrary. GetProcAddress supplies the function candidate.
These operations are inline in the selected 204B body; unmatched standalone
helper sections are not assigned addresses from their names alone.

Publishing a function uses CRT lock 14, changes the complete 128B function table
to PAGE_READWRITE (4), exchanges the pointer or `-1`, restores PAGE_READONLY (2),
then unlocks. Either failed protection transition calls abort. The initializer
applies read-only protection to the image-zeroed table and returns its success
in AL.

The loader first uses LoadLibraryExW flag `0x800`. Only error 87 permits retry
with zero flags, and that fallback excludes `api-ms-` and `ext-ms-` prefixes.
Both complete sixteen-byte prefix literals and both LoadLibraryExW import
sites agree with the original. PE import descriptors independently establish
LoadLibraryExW, GetLastError, GetProcAddress, FreeLibrary and VirtualProtect.
The source is `ucrt/internal/winapi_thunks.cpp`.

## Lifecycle, eager locale lookup and TLS2

The original paired UCRT table independently binds initialization to
`0x005583D2` and retirement to `0x00558426`. Normal retirement visits all 23
module slots, calls FreeLibrary only for real nonnull/non-sentinel handles and
clears nonzero slots. Terminating mode skips this work and returns true in AL.
The separate function-pointer array is not cleared by this callback.

The 55B eager-locale owner resolves all eleven listed APIs in original order,
using ten CALLs and a final getter tail JMP; it does not invoke the APIs. The
49B TLS2 predicate performs the same cache protocol for ID 3/FlsGetValue2,
including its full name and candidate array. Boolean results use AL; getter
results are pointers in EAX. Locale wrapper/fallback bodies remain the next
review scope, including their real call conventions and distinct callees.

## Evidence and affected scope

Private `.analysis/origin-boundary/thunk-cache/` retains the SDK member, bounded
`lookup-native.txt` and `lifetime-native.txt`, locations, `review.py` and
`reviewed.json`. The audit checks all selected complete code and referenced data
sections, local branch targets, external tails, complete HIGHLOW sets, API IDs,
cache offsets, candidate modules, imports and original lifecycle-table roles.
It rejects the earlier wrong semantic assignment despite ordinary-byte
agreement. Existing historical receipts are unchanged.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
