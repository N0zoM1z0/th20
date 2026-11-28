# UCRT application policies, WinRT wrappers and random-provider lookup

Eight pending origins are now library exclusions through complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` contributions. The five optional API wrappers,
two policy consumers and shared secure-process guard match all 487 instruction
bytes and one trailing INT3 in the locked Japanese TH20 v1.00a Steamless target.
Their absent-API contracts differ and their policy caches have distinct owners.

## Complete bodies and API identities

| Entry | Bytes | SDK role |
| --- | ---: | --- |
| `0x00557F83` | 79 | `__acrt_AppPolicyGetProcessTerminationMethodInternal` |
| `0x00557FD2` | 79 | `__acrt_AppPolicyGetThreadInitializationTypeInternal` |
| `0x005582BA` | 74 | `__acrt_RoInitialize` |
| `0x00558304` | 61 | `__acrt_RoUninitialize` |
| `0x00558341` | 78 | `__acrt_RtlGenRandom` |
| `0x0055845C` | 58 | `__acrt_get_begin_thread_init_policy` |
| `0x00558496` | 39 | `__acrt_get_process_end_policy` |
| `0x0055E11B` | 19 | `__acrt_is_secure_process` |

The random wrapper's whole SDK section is 79B, including the original INT3 at
`0x0055838F`. Its abort call remains inside the reviewed body. Every other
selected body ends at the complete contribution's return. All ordinary bytes,
local branches, external call roles and HIGHLOW fields agree.

All five wrappers inline the fast path of the established
[raw API cache protocol](CRT_WINAPI_THUNK_CACHE_ORIGIN_REVIEW.md). A zero cache
enters the shared slow resolver; `-1` skips lookup and selects the wrapper's
absence path; a real pointer enters a CFG-checked call. Full API-name literals,
candidate arrays, IDs and slots identify each wrapper:

| API export | Function ID | Slot | Candidate module IDs |
| --- | ---: | --- | --- |
| `AppPolicyGetProcessTerminationMethod` | 26 | `0x005E6068` | `[21]` |
| `AppPolicyGetThreadInitializationType` | 27 | `0x005E606C` | `[21]` |
| `RoInitialize` | 24 | `0x005E6060` | `[11]` |
| `RoUninitialize` | 25 | `0x005E6064` | `[11]` |
| `SystemFunction036` | 31 | `0x005E607C` | `[14,17]` |

The previously compared complete module table names ID 21 as
`api-ms-win-appmodel-runtime-l1-1-2`, ID 11 as `api-ms-win-core-winrt-l1-1-0`, and
IDs 14/17 as `api-ms-win-security-systemfunctions-l1-1-0` and `advapi32`.
These are full candidate ranges: first/end pointers and every array element
agree, including one-past-array addresses adjacent to API-name strings.
The public random wrapper resolves the export named `SystemFunction036`.

The diagnostic-policy SDK wrapper is a useful negative candidate: its control
structure resembles the process-policy wrapper, but its function ID is 28
instead of native ID 26. No address is assigned to it from shape alone.

## Absence contracts and calling conventions

Both policy queries pass the output pointer and effective-thread-token pseudo
handle `-6` to the resolved API. The installed `processthreadsapi.h` definition
independently establishes that constant. Missing APIs return `0xC0000225`, named
`STATUS_NOT_FOUND` in the installed `ntstatus.h`; there is no local write to the
output pointer. These wrappers return LONG in EAX and pop their one public
argument with `RET 4`.

RoInitialize forwards the initialization type and returns the API's HRESULT;
when absent, it returns S_OK/zero without invoking a replacement. RoUninitialize
has a void interface and returns immediately when absent. Its residual EAX is
not a status result. The random wrapper forwards buffer and byte count, returns
the API's BOOLEAN in AL with `RET 8`, or calls the independently established
abort at `0x00547B43`. No recoverable missing-provider return is added.

## Policy consumers, cache state and secure-process guard

The two policy consumers initialize their local Windows policy value to zero.
They call the secure-process guard before querying; a true result skips the
query. They ignore the query's returned status and translate the local policy
value, so an absent API retains the original default.

Begin-thread policy owns one zero-filled 4B cache at `0x005E5660`. Zero means
unresolved. Windows policy value 1 becomes CRT policy 2/RoInitialize; any other
value becomes 1/none. XCHG publishes that final nonzero value and subsequent
calls return it directly. Failed lookup and secure-process defaults are cached
as well. This is a numeric policy cache, separate from the raw function-pointer
table at `0x005E6000` and callback slot at `0x005E565C`.

Process-end policy has no cache. Windows value 1 becomes CRT policy
0/TerminateProcess; every other value becomes 1/ExitProcess. The installed
`corecrt_internal.h` enums independently name both CRT policy encodings.

The complete 19B secure-process guard reads FS:[0x18], follows TEB+0x30 to PEB,
PEB+0x10 to process parameters, then reads Flags at +0x08 and shifts bit 31 into
the result. It has no API lookup or import dependency. The exact SDK member and
`peb_access.cpp` identify this guard; the adjacent application-verifier helper
receives no credit from this review.

## Evidence and affected scope

Private `.analysis/origin-boundary/optional-api-wrappers/` retains bounded
attested policy, WinRT/random and secure-process listings, member locations,
`review.py` and `reviewed.json`. The policy-consumer instructions reuse the
attested `thunk-cache/lifetime-native.txt` under the same target identity.
The audit checks eight whole code sections, complete branches/HIGHLOW sets,
all five full name/candidate pairs (144B), the 4B policy cache, and the existing
whole 128B function table. Shared slow-resolver/module evidence is unchanged.

Members are preserved `winapi_thunks.obj` and newly extracted `win_policies.obj`
and `peb_access.obj`; the report records their hashes. Corresponding installed
source is `ucrt/internal/{winapi_thunks,win_policies,peb_access}.cpp`.
Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
