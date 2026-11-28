# UCRT monetary, numeric and time component lifetimes

Eight pending library origins are reviewed through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` members `initmon.obj`, `initnum.obj` and
`inittime.obj`. All 2,789 bytes in `0x0055FC0C..0x005606F0` agree with the
locked Japanese TH20 v1.00a Steamless target, including complete initialization,
failed-query cleanup and component retirement paths. There are no omitted
alignment bytes or locally owned data/EH sections in these eight contributions.

## Complete bodies and cleanup identities

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x0055FC0C` | 254 | `__acrt_locale_free_monetary` |
| `0x0055FD0A` | 865 | `__acrt_locale_initialize_monetary` |
| `0x0056006B` | 105 | `__acrt_locale_free_numeric` |
| `0x005600D4` | 541 | `__acrt_locale_initialize_numeric` |
| `0x005602F1` | 37 | `free_crt_array_internal` |
| `0x00560316` | 636 | `initialize_lc_time` |
| `0x00560592` | 228 | `__acrt_locale_free_time` |
| `0x00560676` | 123 | `__acrt_locale_initialize_time` |

The monetary/numeric cleanup heads carried Ghidra FID-conflict labels. Full
member identity and all per-field comparisons resolve them: monetary cleanup
handles thirteen string pointers and numeric cleanup five. Each compares its
field against the same field of static `__acrt_lconv_c` at `0x005B2660` before
calling free_base. Monetary offsets are 12..36 and 56..76 in four-byte steps;
numeric offsets are 0, 4, 8, 48 and 52. They cover the eighteen pointer fields
of the original 80B lconv layout, preserving the intervening character fields.

Both helpers return for null lconv. Per-field checks compare pointer identity
with the corresponding static C pointer, rather than testing string contents.
Differing null fields still reach free_base(null). Neither helper clears fields
or frees the lconv structure itself. The already reviewed
[free-locale owner](CRT_LOCALE_REFCOUNT_BOUNDARY_REVIEW.md) supplies the outer
counter/static-object conditions and structure retirement.

## Monetary and numeric initialization

Monetary initialization allocates a zeroed 80B lconv and international counter
when either relevant category is non-C, plus a zeroed monetary counter when
needed. It accumulates all 21 locale-info query results with bitwise OR, then
uses the complete monetary destructor and original temporary frees on failure.
Failure returns 1. The C-monetary path copies the complete static lconv before
restoring the five existing numeric pointers. An all-C path selects the static
structure directly.

Numeric initialization first copies the complete existing lconv so monetary
fields survive. Its international/numeric counters use malloc and explicit
zero stores, unlike the monetary calloc paths. It accumulates five query
results. Allocation failures return 1; query failure cleans the numeric content
and temporaries, sets the saved result to `-1` at `0x0056021E`, then returns it.
The original failure values remain distinct despite the source's broad exit
comment. The C-numeric path restores the five static C numeric pointers.

Both initializers retain their inlined grouping normalization. Digits are
converted individually from ASCII to numeric bytes, semicolons are removed by
shifting the remaining bytes including NUL, and other bytes are preserved.
The loop revisits the character shifted into a removed semicolon's position.
Grouping remains inline in these selected owners.

New counters become one before publication. The commit paths decrement old
category/international counters and keep the exact conditional frees and
publication order. In particular, an old category-counter decrement is not
expanded into a new component-destructor call. Monetary and numeric paths also
retain their different old lconv/counter free order.

## Complete LC_TIME construction and content ownership

The 636B population helper copies the locale name into the field at +0x160,
then queries narrow/wide weekday and month names, AM/PM, date/time formats and
calendar type. Weekday indices rotate the OS Monday-first enumeration into
the runtime's Sunday-first array. Months remain in their original order.
Query results accumulate with OR; the final boolean result is in AL.

The locale-name copy result is stored without a separate check or contribution
to that accumulated query status. This original control flow is retained;
failure handling is not broadened based on the helper's general purpose.
The two shared providers are CRT's allocating locale-info shim at
`0x0055CF58` and locale-name copy at `0x00555DEF`. Their named dependencies
receive no body credit in this review.

The 37B array helper frees every element in the supplied range without clearing
the array. Time-content cleanup calls it for narrow and wide arrays of counts
7, 7, 12, 12 and 2, then retains all seven direct field frees: six format strings
and the copied locale name. This covers 87 string slots. It accepts null but
does not itself exclude static C time data or free the structure allocation.
Those responsibilities belong to the
[outer conditional retirement helper](CRT_LOCALE_REFCOUNT_BOUNDARY_REVIEW.md).

Time initialization selects static C data at `0x00599ED8` or allocates a zeroed
`0x164`-byte structure. Population failure destroys the partial content and
frees its block; allocation failure keeps the original free(null) path. Success
sets refcount +0xB0 to one and retains free(null) after detaching ownership.
It releases the old time reference before publishing the new pointer. No
immediate old-object destruction is added when that decrement reaches zero.

## Evidence and affected scope

Private `.analysis/origin-boundary/locale-components/` retains all three SDK
members, locations, bounded attested monetary/numeric/time listings and their
finishing tail queries, `review.py` and `reviewed.json`. The audit requires full
instruction coverage from the listing union and compares all eight whole code
sections, every ordinary byte, branch, HIGHLOW field and callee role. It checks
all thirteen/five lconv field identities, the ten array/seven direct time frees,
original structure size, reference initialization and unchecked copy-result
flow. No ledger boundary changes are needed.

Static C lconv/time structures are externally owned inputs. All referenced
local sections are selected code contributions, so no local literal, state or
EH contribution is left outside this scope. Installed source is
`ucrt/locale/{initmon,initnum,inittime}.cpp`.
Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
