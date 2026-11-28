# UCRT narrow locale adapters: counts, flags and sort-key bytes

Three pending library origins are reviewed through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` members `getstringtypea.obj` and
`lcmapstringa.obj`. All 820 code bytes match the locked Japanese TH20 v1.00a
Steamless target, including full branch/HIGHLOW/callee/import roles. Query
versus fill flags, actual versus queried counts and byte versus wide outputs
remain distinct. The old source headers describe optional ANSI API selection;
these actual bodies use wide classification/mapping after conversion.

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x0055D108` | 254 | `__acrt_GetStringTypeA` |
| `0x0055D206` | 493 | internal `__acrt_LCMapStringA_stat` |
| `0x0055D3F3` | 73 | `__acrt_LCMapStringA` |

These three whole contributions fill `0x0055D108..0x0055D43B`. Their ledger
boundaries stay unchanged, with no omitted owned data, EH or alignment.
Both public adapters are cdecl: seven arguments for classification, nine for
mapping. Classification returns the full Win32 BOOL value; mapping returns an
integer count rather than a narrowed boolean.

## Guard, conversion flags and actual classification count

The classification adapter constructs the reviewed legacy locale guard.
Code page zero selects the guarded locale's code page. Its initial size query
passes flags 9 (`MB_PRECOMPOSED | MB_ERR_INVALID_CHARS`) when the error argument
is nonzero, otherwise 1 (`MB_PRECOMPOSED`). The actual fill always passes 1.
These are inputs to the
[reviewed code-page-specific conversion filter](CRT_LOCALE_REFRESH_CONVERSION_ORIGIN_REVIEW.md),
not unconditional flags delivered to Win32 for every code page.

A zero size query or allocation/conversion failure returns false through the
original cleanup. Before filling, classification clears the entire UTF-16
payload. It then passes the second conversion's **actual** count to
GetStringTypeW at independently named IAT slot `0x0056C194`, together with the
caller's info type and WORD output array. It retains the raw BOOL result,
releases the temporary, restores the guard's own-locale bit and checks the GS
cookie. There is no ANSI GetStringTypeA fallback in this body.

## Mapping source bounds and retained query capacities

The public mapping wrapper constructs the legacy guard, passes its effective
locale to the internal function, forwards the other eight arguments and
restores the guard afterward. The internal function only bounds the source
when its byte count is positive. It calls `__strncnt` at `0x00552590`; an early
null changes the count to length plus one, while an unterminated bounded input
keeps the bounded length. Zero and negative counts pass through unchanged.

Code page zero selects the supplied effective locale's code page. The size
query again uses flags 1 or 9 according to the error argument; fill always
uses 1. Unlike classification, the input temporary is not explicitly cleared.
The second conversion is tested for zero, but subsequent LCMapStringEx calls
use the original queried input extent. They do not substitute its actual
conversion return count.

LCMapStringEx first queries output capacity. Its complete nine-argument
stdcall adapter at `0x0055822C` is already reviewed through the
[WinAPI wrapper proof](CRT_LOCALE_WINAPI_WRAPPER_ORIGIN_REVIEW.md).
All three reserved arguments remain zero.

## Sort-key bytes and ordinary wide mapping

When map flags contain `LCMAP_SORTKEY`/0x400, the queried result is a byte count.
A zero destination count returns that size without filling. For nonzero
destination count, a signed comparison rejects insufficient capacity; otherwise
the original narrow destination is passed directly to LCMapStringEx as its
sort-key byte buffer. No second wide temporary or wide-to-multibyte conversion
is used on this path.

Ordinary mapping treats the query result as a UTF-16 count and allocates the
second temporary accordingly. After mapping succeeds, reverse conversion uses
that original queried output count, rather than the second mapping call's
return value. A zero destination count requests required narrow bytes with a
null destination; otherwise conversion writes the supplied buffer/capacity.
Flags and both default-character pointers are zero. The output temporary is
released before the input temporary on all applicable exits, preserving the
original zero-result failure branches and integer result.

## Complete temporary ownership and rejected release variants

All three temporary-allocation sites preserve doubled UTF-16 payload sizes,
the eight-byte malloca header and the original addition-overflow branch.
The 1024B threshold includes the header: 508 UTF-16 elements fit the stack
path, while 509 require heap allocation. Stack and heap headers carry 0xCCCC
and 0xDDDD respectively. Allocation failure and all release/GS exits remain
inside the compared contributions.

Both SDK members contain a 32B freea candidate. Both are rejected at the actual
shared `0x0054273F` release target: they add a two-byte hotpatch prefix and call
free_base directly. The retained independently reviewed 30B owner calls the
`_free` forwarding function instead. Reuse its existing allocation evidence;
do not rename, resize or rebuild that shared owner from these losing variants.
The 130B legacy guard is likewise reused from the
[complete locale-info review](CRT_LOCALE_INFO_COPY_ORIGIN_REVIEW.md).

## Evidence and affected scope

Private `.analysis/origin-boundary/narrow-locale-adapters/` retains both SDK
members, locations, the bounded attested 324-instruction listing, `review.py`
and `reviewed.json`. The audit compares three whole sections, complete control
flow and all relocation roles, the PE import name and both rejected freea
definitions. Installed implementation sources are `ucrt/locale/GetStringTypeA.cpp`
and `ucrt/locale/LCMapStringA.cpp`. The bounded string counter is now covered
by the [complete counter/wide-adapter review](CRT_WIDE_COUNT_ADAPTER_ORIGIN_REVIEW.md).
The stack probe and memset remain separate pending bodies; their call roles
confer no body credit.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
