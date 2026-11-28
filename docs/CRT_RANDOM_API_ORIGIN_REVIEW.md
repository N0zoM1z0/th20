# UCRT rand state and rand_s error/output order

Two complete SDK 10.0.26100.0 x86 libucrt.lib contributions identify library
origins in the locked Japanese TH20 Steamless target. The 105B/36-instruction
scope retains all six REL32 calls, full local control flow and six adjacent
INT3 bytes. Neither existing extent changes; neither owner has static data,
HIGHLOW fields, EH metadata or an embedded jump table.

| Entry | Bytes | Instructions | Symbol | Member |
| --- | ---: | ---: | --- | --- |
| `0x0055020D` | 33 | 8 | `_rand` | rand.obj |
| `0x00552355` | 72 | 28 | `_rand_s` | rand_s.obj |

CodeView and installed stdlib.h agree: rand is cdecl int32 with no arguments;
rand_s is cdecl int32 with one unsigned-int32 pointer. They return in EAX.
The reviewed STL random-device caller independently selects the rand_s entry.

## Rand updates the original per-thread word

Rand calls the already reviewed required UCRT PTD getter at `0x005579C2`.
It reads the uint32 state at PTD+0x18, multiplies it by 214013, adds 2531011
and stores the low 32-bit result back to the same word. The return is the
updated state shifted right by sixteen and masked with 0x7FFF. Installed
rand.cpp and the PTD declaration identify this field as `_rand_state`;
the earlier reviewed constructor at `0x00557748` initializes it to one.
There is no new global random-state cell or independently reviewed srand
entry in this scope. The current 18B SDK srand contribution has no complete
ordinary-byte location.

## Rand_s preserves callback and provider failure behavior

A null output pointer first sets errno to 22, then calls the reviewed
returning invalid-parameter wrapper. If the handler resumes, the function
returns the immediate value 22; it does not reread errno or call the provider.

For nonnull output, the original AND-to-zero clears the full four-byte word
before passing its address and byte count four to the reviewed stdcall
RtlGenRandom bridge at `0x00558341`. A nonzero AL means success and returns
zero. This bridge already owns the SystemFunction036 lookup and the
nonreturning missing-provider abort; rand_s adds no fallback generator.

A zero AL sets errno to 12, calls the errno getter again and returns the
then-current value through that pointer. Preserve both getter calls. It
does not clear the output again after provider failure, so the earlier
zero store does not guarantee zero after a provider has written the buffer.
There is no PTD random-state update on any rand_s path.

## Evidence and affected scope

Private `.analysis/origin-boundary/random-api/` retains archive provenance,
complete member locations, CodeView signatures, attested instructions,
full comparisons, all relocation roles and original rows. The source files
are `ucrt/stdlib/rand.cpp`, `rand_s.cpp`, `ucrt/inc/corecrt_internal.h` and
`ucrt/internal/per_thread_data.cpp`. The complete PTD, errno, returning
invalid-parameter and random-provider reviews supply the external identities.
Two INT3 bytes follow rand; one precedes rand_s and three follow it. The
latter gap is also retained by the adjacent decomp review, without another
physical entry or duplicate credit.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
