# Whole progress-file serialization protocol

CORE-090 refines the complete SaveManager writer at 50F6B0. The maintained
contribution is 1198 bytes, matching the native extent, with 46 structural
instruction differences. It remains whole nonexact. No new exact unit,
authored origin, reference absorption or compared-byte coverage is claimed.

## Integer iteration and source ownership

The native writer uses one-word range values and free aggregate-return begin/end
helpers. A shared four-byte cursor provides construction, prefix increment,
member inequality and dereference. Independent Game calls at 5085B5/508915 and
their complete loop consumers corroborate this protocol separately from the
writer's compared relocations. Finite std::views::iota had the right values but
different helper ownership and calling conventions.

ProgressRanges.hpp declares the actual one-word cursor and the two observed
finite domains. Eight complete compiler contributions strictly replay as
support: constructor 4142A0/24 bytes, increment 461860/27, inequality 449460/47,
dereference 40C300/16, two begin wrappers sharing 461510/18, and end wrappers
50AE60/18 and 50AE80/18. Constructor relocations use the independently reviewed
constructor identity. These are support only; the folded begin wrappers do not
add duplicate coverage or extra exact units.

The original type names and the kind of the range tags remain unknown. The enum
tags are a maintained source inference implementing the full-width value ABI,
zero selection and observed bounds 2/9. Only these finite domains are verified;
the general cursor overflow domain and original source spelling remain open.

## Storage, checksum evaluation and cleanup

The complete native score.cpp diagnostic identifies the staging allocation as
char. Source now uses that allocation type and a separate read-only byte view
for the actual codec payload. Checksum calls evaluate the real Profile, fallback
and Metadata slots, and compound assignments recompute their destinations.
The complete disk header is viewed at the current Snapshot buffer slot.

Writer buffer releases each have one null guard. The allocator macro already
supplies that guard. The independently observed double guards in the parser and
SaveManager destructor are retained. On success the compressed buffer is
released before string/path destruction, and staging is released afterward.
On open failure both buffers are released before automatic string/path cleanup.
This is observable lifetime ordering, with one shared production body.

## Remaining compiler emission

The first remaining writer difference is the payload index. Native emits
MOV44/SHL0; ordinary indexed byte pointers emit MOV1/IMUL44, followed by different
register choices. The complete extent stays 1198 bytes. Pointer addition instead
produces a shorter 1193-byte writer and does not explain the original protocol.

Batch probes cover literal/enum/sizeof indices, signed/unsigned/ptrdiff casts,
reversed subscripts, sizeof division, removal of /sdl, /permissive and
/std:c++latest. None resolves the difference. Indexed parser probes produce
825/native824 bytes; the maintained parser remains 813/native824. No inert
index local, invented array owner, fake return, assembly, truncated comparison
or solved relocation is introduced. Compiler/source-expression identity remains
open; equal extent alone does not establish exactness.

Five complete filesystem/string SDK contributions agree structurally. Their
remaining SDK/EH relocation closure is still separate from canonical exactness.
The private whole-function audit records every unresolved relocation.

## Verification and evidence

The O2/UBSan integration check executes the real writer, both codec directions,
parser, checksums, default initialization, threads, allocator, file and log
bodies. A non-CR Profile is omitted from the actual compressed/encrypted packet;
its selectors, checksum and complete bytes remain unchanged through writing and
parsing. The other seventeen slots, fallback and Metadata round-trip correctly.
Existing complete-packet, reload, failure and short-write checks remain active.
Startup, resource-reader, OS and valid-input secure-CRT boundaries are explicit
fixtures. Native disk/game execution and allocation/CRT failure domains remain
open.

Ignored proofs include core090-protocol-audit.json, the bounded range/SDK native
exports, core090-literal-diagnostics.json, core090-addition-diagnostics.json,
core090-final-frozen-source.json and exact090-canonical-results.json.gz. Retired
probe receipts retain original SHA-bound inputs and negative results. Completed
replay and cleanup writers must never rerun; historical experiments require
restoring their entire original input set.

The frozen graph strictly replays623 units across125 fresh objects and122227
disjoint bytes. All59 public tests pass in178.205 seconds. Exact/source/origin
counts stay unchanged. Two protected cleanup passes retire32 probe products;
post-cleanup623/623 replay reuses125 objects. Original receipts, negative
diagnostics and the historical source version remain archived.
