# UCRT decimal digit rounding and strflt-to-string

Three complete Windows SDK 10.0.26100.0 x86 `_fptostr.obj` contributions
identify pending library origins in the locked Japanese TH20 Steamless target:

| Entry | Complete bytes | Operation |
| --- | ---: | --- |
| `0x00562673` | 35 | remaining-digit check |
| `0x00562696` | 142 | decimal rounding decision |
| `0x00562724` | 249 | strflt-to-string conversion |

The complete contiguous 426B/197-instruction interval agrees with the archive
member and attested listing. All eight REL32 fields name the actual helpers,
fegetround, invalid-parameter and memmove providers. HIGHLOW sets are empty;
there are no local data, padding or EH tables. Full control-flow traversal
covers every instruction, with all existing extents unchanged.

## Validation order and the leading overflow digit

The converter first validates the buffer and a nonzero count. It clears the
first byte, then requires count strictly greater than max(digits,0)+1, and
finally validates the strflt pointer. Errors retain their original ordering,
cached EINVAL/22 or ERANGE/34 and call to the complete internal invalid-
parameter provider. The supplied cached PTD host is the seventh cdecl argument.

The 12B strflt has sign at offset zero, decpt at four and mantissa pointer at
eight. Conversion leaves the mantissa pointer and digit data unchanged. It
places an ASCII zero overflow placeholder in the output, copies the requested
positive digit count and pads with ASCII zero after the input terminator.
The mantissa cursor advances only for copied input bytes. The output receives
a NUL before rounding begins.

## Decimal rounding checks generated and ungenerated trailing digits

The remaining-digit helper returns true immediately for the trailing enum
value zero. Otherwise it skips ASCII zero digits and returns whether the
next byte is non-NUL. Thus a no_trailing result from the generator does not
discard nonzero digits still present in its generated string.

Legacy mode rounds when the current signed char is at least ASCII 5.
Standard mode uses the complete fegetround provider. Nearest handles greater
or less than five first, then tests the remaining string and generator flag
for an exact tie. With no preceding mantissa digit it rounds down; otherwise
the preceding digit's parity selects the even result.

Upward/downward call the remaining-digit helper at the current cursor and
combine its result with the integer sign field's comparison to minus. Other
rounding modes return false. This complete decimal predicate is separate from
the [hexadecimal nibble predicate](CRT_FP_DISPATCH_FORMATTING_ORIGIN_REVIEW.md),
whose directed-rounding test uses only the next nibble. Both retain their own
full implementations and common fegetround provider.

## Carry propagation updates decpt without changing mantissa ownership

A negative requested digit count skips rounding. Otherwise, when the
predicate returns true, conversion walks backward over output nines, changes
each to zero and increments the first earlier digit. Carry into the leading
placeholder makes it one and increments strflt.decpt. Without that carry,
the real memmove removes the unused placeholder with strlen+1 bytes, retaining
the terminator. The original cdecl status result is zero on success; the
helpers return booleans in AL.

## Evidence and affected scope

Private `.analysis/origin-boundary/fp-strflt/` retains scoped locations, the
attested full listing, complete comparison, call/ABI checks and original rows.
It reuses the full `_fptostr.obj` member and archive provenance in
`fp-dispatch/`. Installed `convert/_fptostr.cpp` provides the complete source,
including validation order, decimal tie handling and unchanged mantissa.
The existing full fegetround, invalid-parameter and memmove proofs are reused.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass; all 2,151 protected native input/product hashes
are unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit. The separate 5,326B fltout contribution remains
pending under its own complete scope.
