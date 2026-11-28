# UCRT lowio initialization, inherited handles and retirement

Four complete Windows SDK 10.0.26100.0 x86 `libucrt.lib` contributions from
`ioinit.obj` identify the locked target's lowio initialization and retirement.
All 492 instruction bytes, seven alignment bytes, 28B SEH table and 516B
loader-zero shared state agree. Three pending candidates are excluded as
library/compiler origins, and three omitted entries are recovered.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x0055982D` | 176 | initialize inherited file handles |
| `0x005598DD` | 176 | initialize standard handles |
| `0x0055998D` | 84 | recovered `__acrt_initialize_lowio` primary |
| `0x005599E1` | 3 | recovered compiler finally entry |
| `0x005599E4` | 9 | existing global index-lock unlock funclet |
| `0x005599ED` | 44 | recovered `__acrt_uninitialize_lowio` |

The six disjoint partitions fill `0x0055982D..0x00559A18`. Seven original INT3
bytes at `0x00559A19..0x00559A1F` separate retirement from the next owner.
Existing candidate extents remain unchanged.

## Inherited descriptor block

The first owner obtains STARTUPINFOW through the independently named
GetStartupInfoW import. Nonzero `cbReserved2` and nonnull `lpReserved2` permit
reading the block; the code does not validate its byte length. Its format is
a signed 32-bit count N, N attribute bytes, then N unaligned 32-bit OS handles.
The handle-array address uses the original N before any clamp.

The inherited count is signed-clamped to 8192, passed to the previously
reviewed ensure-fh owner, then reduced to `_nhandle` if necessary. Expansion's
return is ignored. The original negative-count behavior is retained without
adding a lower-bound check. The loop uses inequality against the count.

Each entry skips handles -1 and -2 and attributes lacking FOPEN/1. Pipe
attributes bypass GetFileType entirely, preserving the blocked-parent-pipe
case. Other handles require a nonzero GetFileType result. Accepted entries
copy only the raw handle to record +0x18 and attributes to +0x28; they do not
duplicate or close OS resources. The 64-record, 56B-stride array geometry
agrees with the [descriptor lifetime review](CRT_DESCRIPTOR_LIFETIME_ORIGIN_REVIEW.md).

## Standard handles and no-console fallback

Descriptors 0, 1 and 2 whose association is neither -1 nor -2 retain their
handle and gain FTEXT/0x80. Other entries first receive FOPEN|FTEXT/0x81,
then call GetStdHandle with -10, -11 or -12. A result that is neither null nor -1 must
also have a nonzero GetFileType result. Its low byte selects character-device
flag FDEV/0x40 or pipe flag FPIPE/8; other known types retain 0x81.

Failure assigns the no-console handle -2 and sets FDEV, leaving an open text
device. If the external `__piob` pointer at `0x005E531C` is nonnull, the
corresponding FILE descriptor at +0x10 also becomes -2. That pointer is an
external dependency here, without new ownership credit for its initializer.

The SDK's separate 34B `get_std_handle_id` has no complete target match. Its
switch is present inside the compared standard-handle owner; the unlocated
out-of-line section receives no separate ledger entry.

## Initialization lock, full finally boundary and shared state

Initialization holds global lowio index lock 7, invokes ensure-fh with zero,
then initializes inherited and standard handles only on successful expansion.
Its actual return is bool: false on expansion failure and true after setup.
The SDK source's nearby 0/-1 return comment does not describe that ABI.

The whole 96B section includes an 84B primary, a three-byte exception entry
`MOV BL,[EBP-0x19]`, and the existing 9B unlock funclet. Normal completion
calls the unlock directly. Ghidra omits the exception prefix; full pinned
decoding and the complete SDK section retain it. The 28B scope table at
`0x005AC520` has header `-2,0,-44,0` and record `-2,0,0x005599E1`, including
its original HIGHLOW relocation. This independently identifies the omitted
prefix as the exception entry.

The member's complete BSS definitions establish the 128-pointer `__pioinfo`
array at `0x005E5690` (512B) and adjacent `_nhandle` at `0x005E5890` (4B).
Both lie in the PE section's loader-zero tail. All 516 bytes, rather than
unrelated file bytes at those RVAs, are compared against SDK BSS zeros.
Code references and earlier expansion/destruction roles corroborate ownership.

The member's unreferenced 56B initialized `__badioinfo` section has no complete
target match. Its retention or elimination remains unresolved and receives
no target data ownership claim. The exploratory `fmode_initializer.obj` also
has no complete code match; the configured default mode remains open.

## Retirement and evidence

Retirement visits all 128 pointer slots. Each nonnull array goes to the
reviewed destructor and its slot becomes null. The function returns true,
ignores its terminating argument, does not reset `_nhandle`, and performs no
CloseHandle call. The destructor deletes critical sections and frees arrays,
as established in the linked descriptor review.

Private `.analysis/origin-boundary/lowio-initialization/` retains SDK members,
full-section search results, bounded attested `native.txt`, `review.py` and
`reviewed.json`. The audit covers every ordinary byte, REL32/DIR32 relocation,
PE HIGHLOW, direct branch/call, complete SEH closure and loader-zero extent.
The three import identities come from the target's PE import directory,
including shared GetFileType use in both initialization owners. Source is
`ucrt/lowio/ioinit.cpp` and `ucrt/inc/corecrt_internal_lowio.h`.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes are unchanged. Exact replay
scope is **zero units**; this adds no authored or maintained-source exact credit.
