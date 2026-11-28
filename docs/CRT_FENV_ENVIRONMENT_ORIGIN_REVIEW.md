# UCRT floating environment packing, restoration and readback

Seven complete SDK 10.0.26100.0 x86 contributions identify pending library
origins in the locked Japanese TH20 Steamless target. Their 1,279B/465
instructions, all eight REL32/three DIR32 fields and 51 original INT3 bytes
are reconciled. All existing extents remain unchanged, with no local data
or EH table. The review preserves the original feholdexcept mask/readback
asymmetry described below.

| Entry | Bytes | Archive symbol |
| --- | ---: | --- |
| `0x00559A30` | 57 | `___acrt_fenv_expand_round_control` |
| `0x00559C80` | 172 | `___acrt_fenv_get_status` |
| `0x00559D30` | 578 | `___acrt_fenv_set_control` |
| `0x00559F80` | 265 | `___acrt_fenv_set_status` |
| `0x00565F50` | 29 | `_fegetenv` |
| `0x00565F70` | 84 | `_fesetenv` |
| `0x00565FD0` | 94 | `_feholdexcept` |

The first four bodies come from the retained `_fenvutils.obj`; the other
three have their own archive members. Full control-flow traversal covers
every instruction. The 51 INT3 bytes occupy the checked gaps after expand,
the previously reviewed control getter, the new status getter/control setter
and the three API owners. The status setter ends immediately before the
already reviewed iswctype at `0x0055A089`, with no gap there.

## Two packed words preserve separate x87 and SSE state

Fenv_t contains two 32-bit words: control at offset zero and status at four.
CodeView procedure/enum records independently establish cdecl, unsigned
long32 control/status enum types and void return for both setters. Get_status
and expand return their 32-bit enum in EAX; the public APIs return int32.
The existing control getter at `0x00559AA0` supplies the other saved word.

The status getter uses FNSTSW without clearing status. It normalizes the
six hardware exception bits as follows, for both x87 and MXCSR:

| Hardware low-six bit | Meaning | Abstract bit |
| --- | --- | --- |
| `0x01` | invalid | `0x10` |
| `0x02` | denormal | `0x20` |
| `0x04` | divide by zero | `0x08` |
| `0x08` | overflow | `0x04` |
| `0x10` | underflow | `0x02` |
| `0x20` | inexact | `0x01` |

For normalized x87 X and SSE S, its full EAX result is
`(X << 16) | (S << 24) | (X | S)`. The low bits are a union, not a substitute
for the separate high fields. STMXCSR and both setters' MXCSR accesses retain
the signed ISA-level >=1 gate at the independently reviewed `0x005E5288`.
The native setters also use unconditional XMM initialization before that gate.

Set_status takes X from input bits 16..21 and S from 24..29. It converts
them back, uses FNSTENV/FLDENV to replace only the x87 status low six bits,
and replaces only MXCSR status bits 0..5. It preserves the other saved bits.
This direct environment restoration is distinct from the previously reviewed
91B set_statfp owner, which induces flags through arithmetic operations.

## Control restoration uses the high mask and rounding fields

Set_control extracts x87 masks from bits 16..21 and rounding from 22..23;
SSE masks come from 24..29 and rounding from 30..31. The low-word precision
encoding maps 0 to x87 `0x300`, `0x1000` to `0x200`, and the other `0x3000`
masked values to zero. Input infinity bit `0x4000` maps to hardware `0x1000`.
The complete FNSTENV/FLDENV merge changes only x87 control mask `0x1F3F`.

Input denormal mode bits `0xC00` map 0/`0x400`/`0x800`/`0xC00` to MXCSR
0/`0x8040`/`0x40`/`0x8000`. The SSE merge replaces bits 6..15, retaining
the six status bits and upper reserved bits. Both original mask permutations
and all four rounding mappings remain intact.

The separate expand helper duplicates the common exception masks and
rounding mode into both high banks. Its complete unsigned 32-bit result is
`v | ((v & 0x3F) << 16) | ((v & 0x3F) << 24) |
((v & 0x300) << 14) | ((v & 0x300) << 22)`. It keeps the original low word.

## APIs mutate, then validate the complete saved words

Fegetenv reads control first, status second, stores both to the supplied
pointer and returns zero. It has no added null validation. Fesetenv calls
the void control setter, then the void status setter, then fegetenv into
a local 8B object. It returns zero only when both full words equal the
request. A failed read or mismatch returns one after the original writes;
there is no rollback.

Feholdexcept first snapshots into its local object and copies both words
to the output. It ORs only `0x1F` into the local control's low word and calls
fesetenv. Failure returns one; only success reaches the real clearfp at
`0x00561F90`, whose old-status result is discarded before returning zero.
All original failure branches remain, including the fegetenv result check.

The following is an inference from the complete instructions, under ISA>=1
and normal completion of the hardware state operations. Consider a canonical
53-bit/nearest snapshot with both units' divide-by-zero mask clear:

| Stage | Packed control |
| --- | --- |
| original snapshot | `0x37371037` |
| feholdexcept's local request | `0x3737103F` |
| readback after setters | `0x37371037` |

The setters read the unchanged high banks, so the low-word OR does not change
the two actual masks. Readback differs from the request: fesetenv returns
one and feholdexcept skips clearfp. The low union can also conceal an
individual unit's unmasked exception when the other unit masks it. Preserve
the real low/high fields and return paths; do not infer successful masking
from the API name or replace the OR with expansion. This was checked by
bounded bit-field calculation, without a hardware execution experiment.

## Evidence and affected scope

Private `.analysis/origin-boundary/fenv-environment/` retains complete
signatures, attested listings, all relocation/CFG checks, CodeView type
records and the separately labelled mask inference. It reuses `_fenvutils.obj`
in `fp-dispatch/` and the three API members/listing in `fp-fltout/`. The
installed public fenv.h corroborates fenv_t, API types and exception constants;
the corresponding tran implementation files are absent from the installed
source snapshot. Complete archive/native bodies supply their implementation
evidence. The 26B status-from-mask helper has no complete ordinary-byte
location and receives no credit.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit. Next reconcile the retained precise-log10 and ceil contributions,
including their shared tails and provisional Ghidra boundaries.
