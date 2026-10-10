# EXACT-046: shared easing and interpolation evaluation

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

A single native protocol batch reconstructs the shared easing dispatch, all
eight generic interpolation update bodies, two evaluations that leave time
unchanged, and their direct arithmetic dependencies. It adds 32 complete units:
13,822 code bytes and 13,952 complete comparison bytes. The maintained code
uses the existing real interpolation, timer, angle and component values.

## Substantive native bodies

| Operation | Native entry | Code bytes | Complete comparison bytes |
| --- | --- | ---: | ---: |
| Shared easing dispatch | 0x00454EF0 | 4,154 | 4,284 |
| Integer interpolation update/sample | 0x00429E90 | 639 | 639 |
| Float interpolation update/sample | 0x0042A110 | 649 | 649 |
| IntegerTriple interpolation update/sample | 0x0042A3A0 | 1,489 | 1,489 |
| Vector2 interpolation update/sample | 0x0042A980 | 1,022 | 1,022 |
| Vector3 interpolation update/sample | 0x0042AD80 | 1,129 | 1,129 |
| Angle interpolation update/sample | 0x0042B1F0 | 923 | 923 |
| Fog interpolation update/sample | 0x00473590 | 1,074 | 1,074 |
| Byte interpolation update/sample | 0x00513710 | 670 | 670 |
| Float evaluation without advancing time | 0x00511CF0 | 477 | 477 |
| Byte evaluation without advancing time | 0x00511AF0 | 499 | 499 |

Five physical stop heads add 108 bytes, five factor heads add 424 bytes,
and the no-argument timer increment wrapper adds 20 bytes. Ten constructor/
arithmetic members add 545 bytes. Shared scalar heads cover float, integer
and Angle layouts; shared three-component heads cover Vector3 and
IntegerTriple layouts. Equivalent template emissions bind to those same
independently observed destinations and receive no duplicate coverage units.

## Independent flow, storage and ABI evidence

Wrapper-attested Ghidra disassembly and locked-PE decoding reconcile complete
instructions, direct branches, returns, call targets and member offsets for
all 32 units. Unreachable return/else jumps omitted from Ghidra's AddressSets
are independently decoded and accounted for. There are no shortened prefixes.
All complete comparison extents are disjoint from the existing units.

The easing contribution includes a two-byte alignment NOP and a 32-entry table
at 0x00455F2C. Each entry reaches an audited instruction boundary. Native modes
0, 7, 8 and 17 share the linear/default block; explicit source labels preserve
this actual dispatch range. The table and its semantic case bindings were read
before assigning compiler labels. Relocation anchors come from native callees,
existing canonical heads, constant objects and this dispatch audit; solved
structural diagnostic fields do not supply canonical destinations.

The generic value layout remains five typed values followed by Timer, signed
duration and signed mode, with the existing 32/44/64/84/164-byte sizes. All
eight source instantiations share one update implementation. Aggregate returns
use the observed hidden result pointers. IntegerTriple addition/subtraction
receive the other twelve-byte value by value; Angle, Vector2, Vector3 and Fog
arithmetic use their independently observed member ABIs.
IntegerTriple's coordinate constructor takes the last component first and
stores arguments in reverse field order. That order is independently established
by its full constructor and arithmetic callers. The ordinal field names retain
uncertain original channel roles and source spelling.

## Recovered behavior

Positive durations advance time before sampling. Reaching duration clamps the
timer, sets duration to zero and returns the terminal endpoint. Early returns
leave the stored current value unchanged. Duration zero returns end, except
modes 7 and 17 return start. Negative durations evaluate without advancing.

Mode 7 adds end to start on each active evaluation. Mode 17 adds the current
end tangent to start before increasing that tangent by end. Mode 8 uses four
Hermite basis coefficients, calculated before value arithmetic. The ordinary
path calculates the factor before subtracting, scaling and adding values.
These active temporaries and the value snapshot in the incremental paths
preserve the independently observed evaluation and mutation order.

Easing includes quadratic/cubic/quartic input, output and paired curves,
constant zero/one, four sine variants and five calibrated quadratic back curves
with mirrored variants. Zero duration returns one before mode dispatch;
otherwise elapsed/duration is not clamped. Back curves retain the original
float endpoint normalization, with shifts 0.25, 0.30, 0.35, 0.38 and 0.40.
The shared expression is expanded within the dispatch, preserving repeated
float operations without introducing a new runtime helper ABI or simplifying
rounding-sensitive terms.

Byte results truncate to int32 before retaining the low byte, including negative
back-curve values. Signed scalar and IntegerTriple additions/subtractions use
explicit modulo-2^32 arithmetic rather than C++ signed overflow. IntegerTriple
scaling truncates each component separately; Hermite interpolation therefore
retains those per-value conversion boundaries. Angle arithmetic normalizes
each constructed result; ordinary Angle interpolation follows the observed
one-turn difference. Fog arithmetic keeps its existing per-operation packing.

Only float/byte evaluate-without-advance entries are independently bound.
Other generic evaluation emissions are unbound and receive no source mapping
or exact credit. Native Enemy's distinct current-first, per-axis interpolation
owner remains a separate protocol.

## Compiler and validation

Existing per-source profiles remain unchanged: Interpolation, Timer,
IntegerTriple and Vector2 use precise float evaluation; Angle retains strict
float evaluation. Easing uses its own strict profile. There are no assembly,
padding arrays, inert locals, profile-selected bodies or replacement owners.
The recorded local profiles do not establish the original global build recipe.

All 291 units across 60 cold comparison objects strictly replay with zero
differences over 34,844 disjoint complete comparison bytes. All prior units
were rebuilt after the shared declarations changed. Public C++20/UBSan checks
cover an independent double-precision curve oracle, reduced back polynomials,
all modes, ratios outside [0,1], zero duration, scale invariance, all eight
update families, guarded storage, unchanged early-return current values,
positive/zero/negative durations, four clock rates, evaluation without time
mutation, integer/byte wrapping, negative byte truncation, per-component
Hermite truncation, packed fog consistency and circular Angle interpolation.

Floating-to-int conversions require a finite, int32-representable truncation.
Portable checks do not establish exceptional CRT inputs, floating-control
startup, full enclosing owners, original resources, linkage or playable runtime.
Original names and origins remain pending. Source mappings rise to 291,
with 230 pending origins and four previously classified library comparisons;
authored exact credit remains 57 functions / 4,074 bytes. The completed
reference review remains 6,945 bodies and 113 grammar files.
