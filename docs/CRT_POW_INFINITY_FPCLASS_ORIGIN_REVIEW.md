# UCRT power infinity handling and full floating classification

The complete 499B `_powhlp` at `0x00566ED0` and 193B `_fpclass` at
`0x005670D0` match SDK 10.0.26100.0 x86 powhlp.obj/ieeemisc.obj in the locked
Japanese TH20 Steamless target. All 692B/217 instructions, four REL32/twelve
DIR32 roles and 72B of full constant sections are reviewed. Both existing
extents remain unchanged. Thirteen/fifteen following INT3 bytes agree;
there is no owned EH, switch table or additional code tail.

CodeView establishes cdecl int32 returns. The classifier takes one double;
the power helper takes two doubles and a double* output. Every ordinary
power-helper exit returns zero. Selected special-value paths store a double;
the other finite-input paths retain the output unchanged. Do not infer that
zero means the helper wrote a result, or replace it with a double/ST0 return.

## Ordered infinity tests and parity-dependent signs

The power helper first clears the base's sign with the complete 16B mask,
then tests the exponent's two raw DWORDs for exact positive/negative infinity.
Its original COMISD comparisons retain these selections:

| Input path | Stored result |
| --- | --- |
| exponent +infinity | +infinity if abs(base) > 1; +zero if < 1; otherwise 1 |
| exponent -infinity | +zero if abs(base) > 1; +infinity if < 1; otherwise 1 |
| base +infinity, remaining exponent | +infinity for ordered positive; +zero for ordered negative; otherwise 1 |
| base -infinity, remaining exponent | infinity for ordered positive; zero for ordered negative; negative sign only for odd integer exponent; otherwise 1 |

The otherwise branches include unordered comparisons; they do not introduce
NaN propagation or an errno callback. Original COMISD, UCOMISD, XORPS sign
selection and signed-zero stores remain distinct.

For a negative-infinite base, exponent class mask 0x90 rejects both denormal
classes from integer-parity testing. Otherwise the code calls the reviewed
23B frnd, stores its ST0 result as a double and compares it with the original
exponent. Equality selects another frnd on half the exponent: equal means
even/type 2, unequal means odd/type 1. Noninteger/unordered selects type zero.
The full UCOMISD/LAHF/TEST parity sequence is retained. Frnd uses the caller's
current x87 rounding mode; this owner installs no replacement control word
and does not restore floating status flags changed by its operations.

The standalone 149B `_d_inttype` source section has no complete ordinary-byte
location. Its parity logic is inlined in the full 499B contribution; no extra
function entry is assigned to an interior suffix.

## Full integer classification result

The classifier inspects raw exponent bits first. An all-ones exponent calls
the independently reviewed 114B sptype: positive infinity maps to 0x200,
negative infinity to 4, quiet NaN to 2 and the remaining signaling-NaN path
to 1. It does not return the sptype enum unchanged.

For zero exponent with nonzero mantissa, the sign selects negative denormal
0x10 or positive denormal 0x80. The other finite paths preserve the original
UCOMISD-with-zero test and select signed zeros 0x20/0x40 or signed normals
8/0x100. These ten full int flags agree with the installed float.h constants.
Neither the return type nor any result mask is narrowed to bool. Sign bits,
full mantissa tests and exact zero are retained independently of the earlier
infinity/NaN classification.

## Complete constants and evidence

All seven referenced constant sections are compared, including both lanes of
each 16B mask:

| Linked address | Bytes | Definition |
| --- | ---: | --- |
| `0x0056C468` | 8 | 1.0 |
| `0x0056CD50` | 8 | +zero |
| `0x00597050` | 16 | double-lane absolute mask |
| `0x00597070` | 16 | double-lane sign mask |
| `0x005989C0` | 8 | named d_inf |
| `0x005989D0` | 8 | named d_mzero |
| `0x005A3140` | 8 | 0.5 |

Shared one/zero/sign-mask/infinity roles reuse prior floor/math-exception
proofs. copysign.obj independently supplies the complete named infinity and
negative-zero definitions. All seven patterns have multiple aligned image
occurrences. Newly observed pooled placements remain linked observations;
their ordinary values alone do not select independent canonical addresses.

Private `.analysis/origin-boundary/tail-566ed0/` retains both original members,
provenance, unique whole code locations, CodeView, both attested listings,
complete CFG/field comparisons, full data and the rejected standalone helper.
It reuses copysign.obj in `math-error/` and the existing sptype/frnd owners in
[the special/rounding review](CRT_MATH_SPECIAL_ROUND_ORIGIN_REVIEW.md).
The other nine ieeemisc code sections have no complete ordinary-byte locations;
their negative results remain in `misc-locations.json`. Revisit them only with
new caller/compiler evidence.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected hashes remain unchanged. Exact replay scope is **zero
units**, with no new authored or maintained-source exact credit.
