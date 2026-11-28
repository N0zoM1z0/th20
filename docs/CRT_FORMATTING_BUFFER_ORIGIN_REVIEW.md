# UCRT formatting buffer ownership and growth

Five complete contributions from Windows SDK 10.0.26100.0 x86
`libucrt.lib(output.obj)` identify pending library origins in the locked
Japanese TH20 Steamless target:

| Entry | Complete bytes | Operation |
| --- | ---: | --- |
| `0x0054894E` | 24 | `formatting_buffer::count<char>` |
| `0x00548966` | 128 | `formatting_buffer::ensure_buffer_is_big_enough<char>` |
| `0x00548C79` | 30 | `formatting_buffer::scratch_data<char>` |
| `0x0054948E` | 26 | `formatting_buffer` destructor |
| `0x005494A8` | 36 | internal-free-policy `__crt_unique_heap_ptr<char>` move assignment |

All 244B/95 instructions agree with the complete members and bounded attested
listings. The six REL32 fields name the actual count, move-assignment,
malloc_base and free_base providers. There are no HIGHLOW fields, local data
tables, EH metadata or padding bytes in these five complete sections. Every
instruction is reachable from its owning main entry, and all existing ledger
extents remain unchanged.

## One physical buffer supplies two logical halves

The native formatting-buffer layout has 1,024 inline bytes at offset zero,
the dynamic allocation's byte size at `+0x400`, and its owning pointer at
`+0x404`, forming a 0x408B object. The installed
`corecrt_internal_stdio_output.h` defines that same field order and types.

Count chooses 512 characters when the dynamic pointer is null. Otherwise it
returns the unsigned stored byte size shifted right by one. Scratch-data
calls this complete count provider, chooses the inline or dynamic base from
the saved owning pointer, and adds that count. The original pointer-valued
return starts at the second half of the physical allocation.

These methods use ECX for this. Count returns the full 32-bit size; scratch
returns a char pointer. Growth returns its boolean in AL and removes its
two stack arguments with RET 8. The original widths and cleanup remain intact.

## Growth validates the doubled byte size before allocating

The request is a character count. Values above 0x7FFFFFFF return false after
writing ENOMEM (12) to the supplied cached PTD host at `+0x18` and setting
its valid byte at `+0x1C`. These are the original local cached-errno writes;
the deferred publication protocol is described by the installed
`corecrt_internal_ptd_propagation.h`.

For a valid request, the required physical size is count times two. A null
dynamic pointer and requirement at most 1,024B succeed using inline storage.
Any requirement within the stored dynamic size also succeeds immediately.
Once dynamic storage exists, smaller requests continue using that storage.

A larger request allocates the complete doubled size through the previously
reviewed malloc_base at `0x005584C0`. Allocation failure keeps the old pointer
and size and returns false. Success moves the new pointer into the owning
member, then publishes the new byte size. Growth allocates fresh storage and
discards the previous buffer contents. The local temporary cleanup still
calls free_base on null after a successful transfer, and on allocation
failure; all of those original calls remain in the complete owner.

## Transfer frees the old allocation before publishing the new pointer

The complete move assignment at `0x005494A8` calls free_base on the old
destination pointer, clears that destination slot, reads the source pointer,
publishes it to the destination and clears the source. It returns the
destination object by reference in EAX and removes its one stack argument
with RET 4. The source read follows destination clearing, so a self move
leaves the owner null. There is no separate self-alias branch in this body.

The formatting-buffer destructor also calls free_base unconditionally on
the `+0x404` pointer and clears that slot. It leaves the size field untouched.
The real null handling remains in the independently reviewed 58B free_base
at `0x00557BA0`; the caller's unconditional release is preserved.

## Evidence and affected scope

Private `.analysis/origin-boundary/format-buffer/` retains the full archive
member and provenance, scoped locator results, three attested listings,
complete comparison, source roles, independent heap-provider evidence and
original ledger rows. The installed formatting-buffer and
`vcruntime/internal_shared.h` definitions corroborate the physical halves,
overflow guard, move ordering and release behavior.

The wide-character variants, constructor and generic data/scratch-count
helpers are not assigned from incomplete or generic shapes. The attempted
copy/concatenation members in `string-copy/` likewise have no complete match;
those retained negative results identify the next work without adding credit.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass; all 2,151 protected native input/product hashes
are unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
