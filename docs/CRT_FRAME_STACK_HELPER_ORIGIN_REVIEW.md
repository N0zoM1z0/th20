# CRT frame setup, cookie teardown and aligned stack probes

Eight complete `libcmt.lib` contributions from the installed MSVC
14.44.35207 library context identify nine pending library origins in the
locked Japanese TH20 Steamless target. All 350 instruction bytes, five
INT3 bytes, relocation roles and shared tails agree. Existing extents remain
unchanged; the entries have custom register/stack contracts rather than
ordinary C call interfaces.

| Entry | Bytes | Archive role |
| --- | ---: | --- |
| `0x00542C40` | 43 | `__chkstk` / `__alloca_probe`, one physical head |
| `0x005435ED` | 20 | `__EH_epilog3` |
| `0x00543601` | 15 | `__EH_epilog3_GS` |
| `0x00543610` | 51 | `__EH_prolog3` |
| `0x00543643` | 54 | `__EH_prolog3_GS` |
| `0x00543679` | 54 | `__EH_prolog3_catch` |
| `0x005439E0` | 22 | `__alloca_probe_16` |
| `0x005439F6` | 22 | `__alloca_probe_8` |
| `0x00543C40` | 69 | `__SEH_prolog4` |

## EH frames and equal-sized variants

The C++ prologs receive the handler thunk in EAX, a local-allocation count N
at entry ESP+4 and their own return address at ESP. They replace the count
slot with saved EBP and establish EBP at entry ESP+4. Each saves EBX/ESI/EDI,
pushes the cookie XOR EBP, relocates the helper return address, initializes
the state at EBP-4 to -1, then links FS:[0] to EBP-12. The handler and saved
previous FS link occupy EBP-8 and EBP-12. After helper return, ESP is
EBP-28-N; EAX is scratch. These are compiler-runtime frame builders.

The 51B ordinary variant uses a 12B EH registration node without a local GS
cookie. Both 54B variants add one store, with distinct meaning:

- GS stores the encoded cookie at EBP-16; N includes that cookie slot.
- Catch stores the final ESP at EBP-16 for the 16B catch registration node;
  N includes its saved-ESP field, and no extra local GS cookie is introduced.

The actual stores are `MOV [EBP-16],EAX` versus `MOV [EBP-16],ESP`. Equal
length does not establish interchangeable frame layout. Cookie initialization
precedes publication of the exception node in all three complete sections.

The ordinary epilog restores FS:[0], saves the helper return in ECX,
discards the EH cookie, restores EDI/ESI/EBX and EBP, and returns with ESP
pointing to the reconstructed function's caller return address. Its own
instructions preserve EAX. It does not check the discarded EH cookie on
normal return. The 15B GS epilog first loads EBP-16, XORs EBP and invokes
the independently identified fastcall cookie checker at `0x005429EE`, then
jumps to the whole ordinary epilog. This preserves the distinction between
normal GS checking and per-function EH cookie checks during unwinding.

## Rejected aligned-epilog substring

The SDK `ehprolg3a.obj` has a 12B `__EH_epilog3_GS_align` whose ordinary
bytes match the interior of the 15B GS epilog at `0x00543604`. That aligned
entry expects the cookie already in ECX and a distinct EBX-based parameter
frame. Its required tail, `__EH_epilog3_align`, is a complete 22B routine
that restores the aligned and unaligned stack bases separately.

The candidate actually jumps to the 20B ordinary epilog at `0x005435ED`.
That target does not match the required 22B tail. The complete aligned-tail
search also has no location. Therefore the 12B substring receives no aligned
identity or overlapping entry. The unlocated catch-GS and other aligned
prologs/epilogs remain uncredited.

## Full SEH4 registration

The 69B SEH4 prolog receives local byte count at entry ESP+8 and the scope
table pointer at ESP+4. It installs the actual `__except_handler4` address
`0x00546620`, preserves previous FS:[0] and establishes EBP at entry ESP+8.
Its registration record is:

| Offset from EBP | Stored value |
| --- | --- |
| -16 | previous FS:[0] |
| -12 | exception handler |
| -8 | scope pointer XOR global cookie |
| -4 | initial state -2 |

The helper also stores its final parent ESP at EBP-24 and pushes the
cookie XOR EBP beneath the saved nonvolatiles. It moves its return address
before replacing the original scope/state slots, then publishes FS:[0]
at EBP-16. After return ESP is EBP-32-N. This agrees with the complete
scope-table owners reviewed for locks, lowio, signal and onexit. The handler
is a named external dependency here; its body receives no credit.

## Probing and alignment change the caller's stack

`chkstk.obj` exports `__chkstk` and `__alloca_probe` at offset zero in the
same complete 43B section. There is one physical entry. The requested byte
count arrives in EAX. After preserving ECX, the probe subtracts the count
from its entry stack address. Subtraction wrap clamps the desired bottom
to zero. It rounds the current stack page downward to a 4,096B boundary,
then descends one page at a time with a read-only `TEST [EAX],EAX` until
the requested bottom is in the probed page.

The final path restores ECX, exchanges ESP with the computed bottom, copies
the helper's return address to that new stack and returns there. This both
probes and allocates the caller's frame; a Boolean result or a normal C
return stub would lose the ABI. The five original INT3 bytes after the
section at `0x00542C6B..0x00542C6F` are retained before the next owner.

The complete 44B `alloca16.obj` section comprises two 22B entry paths. The
second export lacks a COFF function type, but its symbol value is exactly
22 and the shipped source independently names the 8-byte entry there.
Each computes the misalignment of the caller's proposed new ESP, using
mask 15 or 7, adds it to EAX, saturates the request to 0xFFFFFFFF if that
addition carries, restores ECX and tail-jumps to the independently located
43B probe. The resulting caller ESP is aligned to 16 or 8 bytes. The source's
occasional “bit” wording does not change the byte masks or native behavior.

## Evidence and affected scope

Private `.analysis/origin-boundary/frame-prologues/` retains complete
`ehprolg3.obj`, `sehprolg4.obj`, `chkstk.obj`, `alloca16.obj` and the rejected
`ehprolg3a.obj` context. Bounded attested listings, whole-section searches,
relocation details, `review.py`, `reviewed.json` and original ledger rows
cover all eight owned sections, nine disjoint entries, full control flow,
every REL32/DIR32 field and PE HIGHLOW. There is no locally owned data or EH
metadata in these shared helper sections. The external cookie and handler
roles are checked separately from ordinary byte agreement.

The source corroboration is the installed `crt/src/i386/ehprolg3.c`,
`ehprolg3a.c`, `chkstk.asm` and `alloca16.asm`. A corresponding SEH4 source
file is absent from that installed source tree; its complete archive section,
relocations, native instructions and reviewed caller/table protocols provide
the evidence. All four selected members came from `libcmt.lib`, rather than
the installed `libvcruntime.lib`. This comparison does not globally identify
the game's compiler or link settings.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**; no authored or maintained-source exact credit is added.
