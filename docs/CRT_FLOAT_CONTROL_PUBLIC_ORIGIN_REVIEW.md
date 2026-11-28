# CRT public floating control, clearing and bit conversion

Five pending entries are library code in the public x87/SSE control protocol.
All 1,736 bytes of their complete contributions agree with Windows SDK
10.0.26100.0 x86 `libucrt.lib`, including all ordinary bytes and original
relocation roles. The locked target remains Japanese TH20 v1.00a Steamless.
Existing boundaries are complete; none is shortened or extended here.

| Entry | Bytes | Archive symbol / role | Member |
| --- | ---: | --- | --- |
| `0x00557210` | 108 | `__controlfp_s`, checked public control API | `contrlfp.obj` |
| `0x00561EC0` | 199 | `___hw_cw_sse2`, abstract flags to MXCSR | `ieee87.obj` |
| `0x00561F90` | 281 | `__clearfp`, public combined status clear | `ieee87.obj` |
| `0x005620B0` | 906 | `__control87`, public combined control owner | `ieee87.obj` |
| `0x00562440` | 242 | `__hw_cw`, abstract flags to x87 control word | `ieee87.obj` |

## Hardware words and public flag encoding

The two integer converters map public exception masks into different hardware
positions. The installed SDK `ucrt/float.h` names these public constants; the
complete native instruction sequences implement the following mapping:

| Public mask | Public bit | x87 control bit | MXCSR control bit |
| --- | ---: | ---: | ---: |
| Invalid | `0x10` | `0x01` | `0x0080` |
| Denormal operand | `0x80000` | `0x02` | `0x0100` |
| Divide by zero | `0x08` | `0x04` | `0x0200` |
| Overflow | `0x04` | `0x08` | `0x0400` |
| Underflow | `0x02` | `0x10` | `0x0800` |
| Inexact | `0x01` | `0x20` | `0x1000` |

Public rounding bits `0x300` map to x87 `0xC00` or MXCSR `0x6000`. Public x87
precision values 64/53/24 use `0`, `0x10000`, `0x20000`, whereas the hardware
fields use `0x300`, `0x200`, `0`. Preserve this reversed encoding. The x87
converter also handles infinity control. The MXCSR converter maps all four
denormal policies: save both, flush both, flush operands only, or flush results
only, using DAZ `0x40` and FTZ `0x8000`. Neither converter itself loads floating
state.

`_clearfp` obtains and clears x87 status, then conditionally obtains and clears
MXCSR status when the original ISA variable is at least one. It translates the
old status bits and returns their OR in public encoding. Its x87-only fallback
is retained. This is distinct from the 19B internal `_clrfp`, which returns a
raw sign-extended status word and does not touch MXCSR; see
[raw state and DAZ recovery ownership](CRT_FLOAT_STATE_ORIGIN_BOUNDARY_REVIEW.md).

## Combined control and actual post-update state

The complete 906B `_control87` reads x87 control, converts it to public flags,
merges the requested mask and value, and uses `_hw_cw` when a write is needed.
After FLDCW it reads back the hardware word. Its ISA-disabled return remains
inside the complete body.

The SSE path performs its abstract conversion inline, reads MXCSR with
STMXCSR, and merges only the applicable public mask bits. A changed value goes
through `_hw_cw_sse2` and the independently reviewed MXCSR setter at
`0x0055DAE0`. Crucially, the caller **reads MXCSR again** after this setter.
The setter can reject DAZ and retry without it; reporting the requested value
instead of the resulting hardware state would change the public result.

The owner combines the two abstract results and sets `_EM_AMBIGUOUS`
(`0x80000000`) when they differ under the common `0x8031F` mask. Precision,
infinity and denormal-flush controls have their bank-specific handling; the
ambiguity check is not a comparison of every raw x87/MXCSR bit.

This whole owner also explains several earlier failed standalone searches:
the native path and its matching SDK contribution inline abstract-control and
MXCSR-read operations. The reviewed code calls the two real converters and
the real setter, with no separate getter call. `ieee-locations.json` records
the full-contribution search results; no address is assigned to unmatched
helper sections from their names alone.

## Checked API and startup contract

The full 108B `_controlfp_s` first removes denormal exception-mask control
(`0x80000`) from its effective mask. It checks unsupported bits in
`new_value & effective_mask`, rather than rejecting every bit outside the mask.
For a valid request it calls `_control87`, optionally stores current state,
and returns zero. A null output pointer is supported: the control update still
takes place.

For an invalid request it optionally obtains current state through
`_control87(0,0)`, sets errno to 22, calls `_invalid_parameter_noinfo` at
`0x005480BC`, and retains the path returning 22 if that handler returns. The
three `_control87` call sites and the `_errno` call at `0x005516C1` all agree
with their independent SDK relocation roles.

The already reviewed default-precision startup owner supplies independent caller
evidence: its original E8 at `0x00543D3E` calls this API at `0x00557210` with a
null output and the 53-bit precision request. The complete archive and original
caller evidence remain in the
[startup-default review](CRT_STARTUP_DEFAULT_ORIGIN_BOUNDARY_REVIEW.md).

## Evidence and affected scope

Private evidence is under `.analysis/origin-boundary/fp-state/`:
`public-native.txt`, its bounded `public-tail.txt` completion,
`secure-native.txt`, the two archive members, `locate-ieee.py`,
`review-ieee.py` and `reviewed-ieee.json`. All five complete bodies decode
contiguously to their returns, with every byte covered by attested Ghidra
listings. The audit checks every local branch target, full ordinary bytes,
complete HIGHLOW sets, internal cross-owner relocations and the independent
startup/MXCSR-setter bindings.

The diagnostic object dump displays some reused local labels in unrelated
sections, splitting valid instructions into misleading fragments. Those display
breaks are not boundaries: the audit uses each symbol's actual section index,
full raw contributions, original listings and pinned contiguous decoding.

Only the five rows in each classification ledger, these notes, handoff and
generated progress change. All 2,151 protected native input/product hashes are
unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
