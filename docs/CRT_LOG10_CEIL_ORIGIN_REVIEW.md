# UCRT ceil boundaries and x87 log10 entries

The provisional 1,523B ceil span at `0x00566320` is a 32B public entry with
external fallback edges. Complete SDK 10.0.26100.0 x86 contributions recover
four omitted heads and identify seven disjoint library entries in the locked
Japanese TH20 Steamless target. No intervening CRT function belongs to ceil.

| Entry | Bytes | Archive symbol | Contribution |
| --- | ---: | --- | --- |
| `0x005662E0` | 64 | `__ceil_no_sse41` | ceil_pentium4.obj, offset 0 |
| `0x00566320` | 32 | `_ceil` | same, offset 64 |
| `0x00566340` | 221 | `__ceil_pentium4` | same, offset 96 |
| `0x00566710` | 59 | `__CIlog10` | log10_impl.obj, offset 0 |
| `0x0056674B` | 20 | `__CIlog10_default` | same, offset 59 |
| `0x0056675F` | 193 | `__log10_default` | same, offset 79 |
| `0x00566820` | 243 | `__ceil_default` | ceil.obj, complete code section |

The three complete code contributions total 832B/229 instructions. All
18 REL32 and 17 DIR32/HIGHLOW roles agree, as do the full 98B of scoped
constants and literals. Full control-flow traversal reaches every instruction,
including the distinct intrinsic heads and shared internal call at `0x00566768`.
Four entries were absent from the ledger; the two other existing extents remain
unchanged. There is no locally owned EH or embedded jump table.

## Ceil selects three complete implementations

The public entry compares the ISA level at `0x005E5288` with two using an
unsigned condition. The fast path retains ROUNDSD immediate `0xA`, stores the
double into the caller's argument slot and returns it through x87 ST(0).
Its backward edge reaches the recovered 64B compatibility dispatcher.

That dispatcher first tests the independently known math-enable slot
`0x005E59AC`, then checks `(MXCSR & 0x7F80) == 0x1F80` and
`(CW & 0x7F) == 0x7F`. LEA releases its temporary stack storage without
destroying the flags used by the following conditional jump. It tail-transfers
to the complete 243B default body or 221B SSE2 body.

The SSE2 body retains its exponent/sign classification, variable bit shifts,
large/already-integral returns, negative-zero result for small negative input,
and positive-side increment/comparison. Small positive values use the input
copy established by `MOVAPD XMM3,XMM0` at `0x005663CC`; its comparison is at
`0x00566401`. The original NaN path calls libm_error_support with code `0x3EC`
and returns through ST(0). All 72B of its local constants at `0x005A2750`,
including the final negative-zero double, remain compared.

The default body saves the old raw control word through the reviewed ctrlfp,
installs `0x1B3F` with mask `0xFFFF` and retains special-input classification.
Classification codes 1/2/3 restore the old word and return the original input;
the other special path preserves the original input-plus-one operation and
except1 call. Finite input passes through the real frnd helper, retains the
rounded/input comparison and old precision-mask test, and either reports
through except1 or restores control before returning the rounded value.
The pooled full 1.0 double at `0x0056C468` is independently bound by the
already reviewed floor contribution's same external constant symbol.

## X87 intrinsic and stack-input paths share one algorithm

The 59B CI dispatcher accepts the argument in ST(0). It retains the same
math-enable/control tests and a tail transfer to the independently located
complete CIlog10_pentium4 provider. The adjacent 20B default adapter stores
the argument with FST, calls checkTOS_withFB and calls into the default body
at offset +9. The ordinary 193B default entry instead prepares EDX from its
stack double and calls fload_withFB. Their saved-stack and flags/EAX contracts
are the ones established by the reviewed x87 common helpers.

The shared algorithm retains FLDLG2/FXCH/FYL2X, conditional installation of
the default control word, and both fast/math exits. Special values preserve
the sign/exponent/mantissa tests, quiet-NaN conversion, indefinite value for
negative-domain input and negative infinity for zero. Original EAX error
values 1/2, EDX function code `0x1B`, the fastflag branches and the real
one-argument error handler remain intact.

The complete 8B log-name contribution is unique at `0x005A27A0`. The full
10B negative-infinity literal at `0x005A30EA` is independently located through
87tran.obj's complete 90B provider signature and symbol offset ten. That
provider's exponential metadata remains outside this code review. Existing
full indefinite/control-word/common-exit evidence is reused. The fourteen
original INT3 bytes at `0x00566702..0x0056670F` are checked before the recovered
CI head; both reviewed default bodies end directly before their next entries.

## Precise SSE2 log10 remains pending

The separate precise owner at `0x00566030` retains its complete 688B ordinary
signature, including the 675B instruction extent and two original alignment
LEAs totaling 13B at `0x005662D3`. Its 256B private constant section has two
complete aligned candidates, `0x005A2650` and `0x005A2FE0`, also shared by the
retained Pentium4 object's signature. No independent bank assignment is
established here, so this owner keeps its pending origin and unchanged extent.
The two complete 1,040B log10 table signatures are also retained for that work.

## Evidence and affected scope

Private `.analysis/origin-boundary/log10-ceil/` retains the complete section
comparisons, independent locations, archive provenance, full control-flow
checks and original rows. Bounded attested listings cover the existing code;
Capstone supplements the unlisted 79B CI/adapter prefix without modifying the
Ghidra project. The members in `fp-fltout/` and prior disjoint/x87 evidence
are reused. Libm_error_support and CIlog10_pentium4 have full independent
archive identity anchors for the calls here; their own remaining code/data
review receives no credit from those anchors.

Only classification, boundaries, evidence, handoff and generated progress
change. Tracking/progress checks pass and all 2,151 protected hashes remain
unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
