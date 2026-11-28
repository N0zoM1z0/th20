# UCRT fclose cleanup, stream reset and complete exceptional unlock

Four complete SDK 10.0.26100.0 x86 contributions match the locked Japanese
TH20 Steamless target: 400B/164 instructions, sixteen REL32/two DIR32 roles,
a full 28B scope table and four following zero alignment bytes. Five existing
entry extents remain unchanged. A missing six-byte exception prefix completes
the original 151B locked owner.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x005643F3` | 137 | `_fclose_internal` primary |
| `0x0056447C` | 6 | recovered compiler stream/result restore |
| `0x00564482` | 8 | compiler unlock |
| `0x0056448A` | 142 | `_fclose_nolock_internal` |
| `0x00564518` | 48 | public `fclose` |
| `0x005665F1` | 59 | `__acrt_stdio_free_stream` |

The first five entries partition the complete contiguous 341B fclose region.
The reset helper is a separate complete 59B stream.obj section. No code
alignment, extra static state or jump table belongs to these contributions.
The original two flag-read NOPs remain code. CodeView confirms cdecl int32
returns for the three fclose functions and void for reset. Internal close
functions take FILE* plus cached-host reference; reset takes the complete
four-byte stream wrapper by value. The existing stream layout remains 56B.

## Locked entry and cached errors

Both internal close functions reject null FILE before accessing its fields.
They mark cached errno valid at host+0x1C, store EINVAL/22 at +0x18 and call
the reviewed internal invalid-parameter handler with five null arguments and
the same host. A returning handler leads to EOF/-1. These owners do not clear
doserrno or immediately commit the cached errno globally.

The locked owner reads string-backed bit 0x1000 first. A string-backed stream
goes directly to the reset helper and returns EOF, without taking the FILE
lock, flushing or closing a descriptor. Otherwise it saves an initial zero
result, calls the reviewed FILE lock, then activates try state zero and calls
the nolock owner. After an ordinary return it saves that full int result,
sets try state -2 and calls the eight-byte unlock. It does not replace a
negative result with a bool or infer success from the stream's reset flags.

Public fclose constructs the existing 40B cached PTD host with null locale,
passes it to the locked owner, saves EAX in ESI, destroys the host and returns
the saved result. This retains the existing deferred error propagation.

## Nolock cleanup and error precedence

The nolock owner starts with EOF. Only allocated bit 0x2000 selects flush,
free_buffer, fileno and `_close_internal`, in that order. Flush failure does
not suppress buffer release or descriptor close. The flush result remains
the result unless descriptor close returns a signed-negative value, which
forces EOF. A successful descriptor close does not overwrite an earlier
flush failure with success.

Only a nonnegative descriptor-close result permits freeing a nonnull tmpfname
through the reviewed free_base, then clearing its pointer. A negative result
skips that free. Both paths subsequently call reset, which clears tmpfname
along with the other fields. Thus the failure path clears the pointer without
freeing that allocation in this owner. Keep that original sequence rather
than moving the free into unconditional cleanup.

A nonnull unallocated stream skips flush/buffer/descriptor/name operations,
but still resets and returns EOF. Null validation returns before reset.
There is no extra string-backed shortcut in the nolock owner.

The 59B reset helper clears ptr/base/cnt, stores descriptor -1 and clears
charbuf/bufsiz/tmpfname, then atomically exchanges the whole flags DWORD
at +0x0C with zero. The allocation bit is released only after those stores.
It retains the lock at +0x20 and the stream object/table slot; this is not
heap-object deletion. There is no added null check, buffer free or lock call.

## Full exception prefix and scope table

The recovered instructions at `0x0056447C` load ESI from parent EBP-0x20 and
EDI from EBP-0x1C, then fall into the existing unlock. Normal completion calls
`0x00564482` directly. The exceptional path restores both saved values before
unlocking and propagates the exception; it does not turn it into a close
result. Lock acquisition occurs before try activation.

The full scope table at `0x005AC6A0` has header `-2,0,-48,0` and record
`-2,0,0x0056447C`. Its unique location follows from the complete source header
and independently located parent callback offset 137, before comparing the
code's metadata field. The table's one HIGHLOW and four following zeros are
checked. Ghidra omits the six-byte prefix from its function listing; bounded
pinned decoding and the complete object/native comparison cover both
instructions without changing the database.

## Relocation identity and evidence

The source's public fclose and fclose_nolock sections have identical complete
ordinary bytes and the same 48B masked location. Their middle call names the
locked 151B owner versus the 142B nolock owner. The actual target calls the
independently located locked owner, establishing fclose and rejecting a
second nolock entry. No duplicate entry or origin credit is added.

Private `.analysis/origin-boundary/stdio-fclose/` retains complete comparisons,
attested listings, CodeView/wrapper layout, supplemental decode and the scope
search. It reuses fclose.obj and full locations in `stdio-closeall/`, plus
reviewed flush/free_buffer, fileno, allocation, lock, SEH4 and cached-host roles.
Its new stream.obj supplies the full reset helper. The 163B `_close_internal`
at `0x005664AE` now has its
[complete descriptor/handle/error/EH review](CRT_LOWIO_CLOSE_ORIGIN_REVIEW.md).
Source is `ucrt/stdio/{fclose,stream}.cpp` and the stdio/PTD propagation headers.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected hashes remain unchanged. Exact replay scope is **zero
units**, with no new authored or maintained-source exact credit.
