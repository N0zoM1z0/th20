# UCRT double decomposition helper and complete boundary

The complete 270B/83-instruction owner at `0x005523A0` is `__decomp`,
not the public frexp entry. Section 17 of both SDK 10.0.26100.0 x86
frexp.obj and ldexp.obj has a unique full ordinary-byte location there.
The one REL32 calls the independently reviewed `__allshl` at `0x005432F0`;
there are no HIGHLOW fields, static data references, EH or jump tables.
The existing extent remains unchanged. Three preceding and two following
INT3 bytes separate it from the neighboring candidates, including the
already reviewed sptype at `0x005524B0`.

Both members' CodeView signatures establish cdecl `double(double, int32*)`.
The double arrives on the stack and returns through ST(0); the pointer
receives a full int32 exponent. All 83 instructions are present in the
attested Ghidra listing and reachable in the complete local control flow.

## Normalization retains the original operations

The first UCOMISD compares the input with zero, then LAHF/TEST/parity
branches distinguish equality from unordered. The equality path writes an
exponent of zero and returns positive zero, including for negative zero.
No control word or MXCSR mode is installed. In particular, the original
SSE comparisons remain sensitive to the caller's denormal and exception
settings; do not replace them with a mode-independent bit-only zero test.

For a finite normal value, the helper extracts the biased exponent and
subtracts 1022. It retains the sign and fraction bits while replacing the
exponent with 1022, giving a signed fraction with magnitude in [0.5, 1).
It spills the resulting double and loads ST(0) for the return.

A nonzero subnormal reaching the normalization path uses BSR on the high
20 fraction bits or the low word to obtain the highest set position k.
It calls the reviewed register-ABI left-shift helper with the 64-bit
fraction in EDX:EAX and shift count 52-k in CL. Clearing the shifted hidden
bit, restoring the sign selected by the original floating comparison and
installing exponent 1022 yields the fraction; the output exponent is
k-1073. The common exit stores that exponent and returns the spilled double.

There is no infinity/NaN classification or matherr path here. Such inputs
pass through the nonzero-exponent branch: the output exponent is 1025 and
the sign/fraction payload is placed under exponent 1022. The initial
UCOMISD retains its original signaling-NaN exception behavior. The helper
does not validate the output pointer or change errno.

## Evidence and useful negative searches

Private `.analysis/origin-boundary/frexp-ldexp/` retains complete member
locations, both CodeView signatures, the attested listing, full comparison,
relocation/CFG checks and original ledger rows. It reuses the frexp member
already retained in `math-special-round/`; the new ldexp member retains its
archive provenance. No native reconstruction input changes, all 2,151
protected hashes agree, and exact replay scope is **zero units**.

The same full-contribution search finds no complete ordinary-byte location
for these members' public frexp/ldexp bodies, set_exp, dtou64 or u64tod.
The separately retained `fpexcept-tail/` search likewise finds none for
this SDK member's except2, fperrraise, fperrraise_with, errcode, get_fname,
handle_qnan2, raise_excf or strtox should_round_up helper. These negatives
avoid repeating the same member scans; they confer no reviewed credit on
an unlocated implementation. Continue from a retained caller or another
independent member rather than assigning those names to nearby candidates.
