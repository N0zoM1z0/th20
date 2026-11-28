# UCRT binary-to-decimal digits and shared big-integer division

The complete SDK 10.0.26100.0 x86 cfout.obj identifies two pending library
origins in the locked Japanese TH20 Steamless target:

| Entry | Complete contribution | Operation |
| --- | ---: | --- |
| `0x0054E9F0` | 1,239B | shared big-integer division |
| `0x0056281D` | 5,326B | `___acrt_fltout`, including its inlined digit generator |

The full 6,565B comprises 6,564B/1,893 instructions and the original final
INT3 at `0x00563CEA`. Both existing ledger extents remain unchanged. All
49 REL32 and 16 DIR32/HIGHLOW fields have independently bound roles; full
control-flow traversal reaches every instruction. Complete owned data is
2,528B, with four inter-literal alignment bytes. Divide ends immediately
before the next independent entry at `0x0054EEC7`; there is no alignment
gap there. There is no local EH table.

## Floating environment, zero and special values

Fltout receives the double by value, unsigned precision, precision-style
enum, 12B strflt pointer, buffer and count through its cdecl interface. It
publishes the integer sign (`'-'` or space) and supplied mantissa pointer.
It first saves the 8B floating environment. If the saved control's low five
exception-mask bits are not all set, feholdexcept runs and the environment
is restored before normal return. The finite path also saves the original
control word, masks `_MCW_EM`/`0x8001F` during conversion, then restores
those control bits before the optional environment restoration.

Zero testing includes exponent-zero denormals when `_DN_FLUSH`/`0x1000000`
is set. This path sets decpt to zero and copies `"0"`. Nonfinite values set
decpt to one and copy the original `1#INF`, `1#QNAN`, `1#SNAN` or `1#IND`
spelling. Infinity returns trailing/zero; zero and the three NaN forms
return no_trailing/one. Each strcpy_s error reaches the real nonreturning
invoke_watson. No replacement validation or failure result is introduced.

The zero literal's two-byte content has 140 aligned occurrences. Its address
`0x0056CF60` is bound through the separate attested prefix helper's one-byte
append at `0x004EC63C`, before comparing fltout's field. The other four full
literal contributions are individually unique at `0x0059D870`, `0x0059D878`,
`0x0059D880` and `0x0059D888`; their complete 28B including zero and their
four intervening zero bytes are retained.

## Exact fractions and the complete power tables

The finite path clears the sign and adds the extra requested rounding digit
using unsigned precision+1. It expands the IEEE mantissa and handles the
denormal exponent adjustment separately. The initial decimal exponent is
ceil(log10(value)); INT_MIN/INT_MAX conversion results retain the original
fallback to zero. The precise log10 helper receives and returns the double
in XMM0; ceil receives its stack double and returns through ST0. These are
distinct call contracts. The positive/negative binary-exponent and exact-power-of-two
branches build the original numerator/denominator fraction, then multiply
the denominator by 10^k or numerator by 10^-k.

Big integers contain a 32-bit used count and 115 little-endian 32-bit limbs:
the data capacity is 460B and the object is 464B. Default construction clears
the used count; it does not initialize the unused array. The inlined shifts,
single-limb and full multiplication retain their capacity limits, carry
propagation and overflow resets. The generator retains the original handling
of their Boolean results rather than adding error branches.

The three independently located complete table contributions are:

| Address | Bytes | Contents |
| --- | ---: | --- |
| `0x00597D78` | 2,312 | 578 packed limbs |
| `0x00598680` | 152 | 38 four-byte unpack indices |
| `0x00598718` | 36 | nine small powers, 10^1 through 10^9 |

Every unpack index has a 16-bit limb offset, an 8-bit omitted-zero count
and an 8-bit stored-limb count. Reassembling all 38 records reproduces
10^10 through 10^380 and consumes every packed limb exactly once. Both
inlined large-power loops retain chunks capped at 38, low-zero filling,
full multiplication and the remaining small-power multiplication. Negative
source addends -1, -2 and -4 address the proper index components; they are
not adjusted to hide differences.

## Trial correction and nine-digit chunks

The initial division follows numerator multiplication by ten. A trial digit
of ten increments k, emits one and multiplies the denominator by ten; zero
decrements k without emitting; other values emit the actual digit. The
corrected k is published to decpt. Fixed style adds nonnegative k to the
required digit count only when the incremented precision is at most INT_MAX;
scientific style keeps the supplied count. The subsequent endpoint reserves
the terminator. The trial digit precedes endpoint calculation, as in source.

Each remaining iteration multiplies the numerator by 10^9, divides and
decomposes the quotient into nine decimal digits in reverse order. Digits
outside the endpoint are skipped, but a skipped nonzero digit sets a sticky
flag. After NUL termination, no_trailing requires both a zero remainder
according to its used count and no skipped nonzero digit. The original
algorithm continues beyond merely significant digits, allowing exact large
integer output. It does not perform the later decimal rounding itself.

## Shared division keeps its full quotient and remainder contract

The 1,239B owner takes a mutable numerator and const denominator by cdecl
reference. It returns a uint64 quotient in EDX:EAX and updates the numerator
to the remainder. Zero numerator or zero denominator returns zero without
new validation. The denominator-one path explicitly returns the low 32-bit
limb and clears the numerator. Single-limb division keeps its separate
32-bit and multi-limb paths; the latter can retain used=1 for zero remainder.

The multi-limb path rejects smaller numerators, normalizes the high divisor
limbs, estimates and corrects each quotient limb, subtracts the product and
adds the denominator back if the estimate was one too large. It then clears
unused high limbs and trims the remainder. All nine real calls retain the
reviewed memcpy_s and custom 64-bit arithmetic/shift ABIs, including the
EBX:ECX remainder output of aulldvrm.

## Evidence and affected scope

Private `.analysis/origin-boundary/fp-fltout/` retains the bounded attested
listings, complete comparison and table checks, independent provider
signatures, archive provenance and original rows. It reuses cfout.obj in
`fp-dispatch/`; installed `convert/cfout.cpp`, the full big-integer header
and floating declarations corroborate the layouts and algorithms. Existing
classifier, memcpy_s, memory, cookie and integer-helper evidence is reused.

Fegetenv, feholdexcept and fesetenv now have their
[complete environment review](CRT_FENV_ENVIRONMENT_ORIGIN_REVIEW.md), including
the original mask/readback asymmetry. The precise SSE2 log10 and ceil retain
complete independent archive identity anchors for the calls here. Their own
boundary/data/protocol work remains pending. Next reconcile those math-provider
shared tails and inferred boundaries.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
