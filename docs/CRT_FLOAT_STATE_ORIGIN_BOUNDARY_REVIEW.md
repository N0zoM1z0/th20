# CRT x87 state and MXCSR recovery ownership

Five existing candidates and three recovered entry partitions belong to the
CRT floating-state protocol. Complete Windows SDK 10.0.26100.0 x86
`libucrt.lib` member `fpctrl.obj` agrees with all 394 code bytes, two 12B
extended-literal contributions, the 4B DAZ cache and the full 28B SEH scope
table in the locked Japanese TH20 v1.00a Steamless executable.

The review corrects the false 222B convex span at `0x0055DAE0`. Its full source
owner remains 222B, partitioned between normal execution and compiler SEH code.
These partitions are not independent C functions or separate source-exact
claims. Future source comparison must retain this entire owner and its scope
metadata.

| Entry | Bytes | Role / archive symbol | Origin |
| --- | ---: | --- | --- |
| `0x0055DAE0` | 118 | `___set_fpsr_sse2`, primary partition | library |
| `0x0055DB56` | 30 | SEH filter, object label `$LN16` | compiler |
| `0x0055DB74` | 46 | SEH recovery entry, object label `$LN11` | compiler |
| `0x0055DBA2` | 28 | normal continuation and frame unlink | library |
| `0x0055DBC0` | 19 | `__clrfp` | library |
| `0x0055DBE0` | 44 | `__ctrlfp` | library |
| `0x0055DC10` | 91 | `__set_statfp` | library |
| `0x0055DC70` | 18 | `__statfp` | library |

## Raw x87 words and real exception effects

The four x87 helpers are the physical callees identified by the
[math exception protocol](CRT_MATH_EXCEPTION_ORIGIN_BOUNDARY_REVIEW.md).
`_clrfp` saves the old status with FNSTSW, executes FNCLEX, and returns the old
word **sign-extended** to EAX. `_statfp` uses the waiting FSTSW form and also
sign-extends the result. Neither reads or clears MXCSR.

`_ctrlfp` obtains the old control word with waiting FSTCW, merges the selected
low-sixteen-bit mask/new-value fields, loads the new word with FLDCW, then
returns the **old** word with MOVSX. This internal interface cannot be replaced
with a public `_controlfp` call that translates abstract flags or reports a
different word. Preserve the return width and the waiting/nonwaiting forms.

The 91B `_set_statfp` induces flags through real x87 operations. Its bit tests
select integer conversion of a large extended value, narrowing large/tiny
extended values to double, division by zero, or narrowing pi. The FWAIT sites
and original exception masks remain consequential: an unmasked exception can
be observed. A direct status-bit assignment would lose those effects.
The full `_over` and `_under` contributions at `0x0059A9D8` and `0x0059A9E4`
are twelve bytes each, including their trailing two bytes. Both complete
sections agree, not just the ten-byte extended payloads. Some disassemblers
combine FWAIT with the following instruction while others list it separately;
the audit compares original bytes and complete coverage across that difference.

## Complete DAZ trial and exception recovery

The MXCSR setter gates execution on the original `___isa_available` at
`0x005E5288` being at least one. If argument bit `0x40` (DAZ) is requested and
the cache at `0x005B29FC` is nonzero, it tries LDMXCSR inside its SEH region.
The complete initialized cache is four bytes with original value one.

The filter at `0x0055DB56` returns one for `0xC0000005` or `0xC000001D`, and
zero for other exception codes. The recovery entry at `0x0055DB74` restores
the saved ESP, writes zero to the DAZ cache, clears argument bit `0x40`, retries
LDMXCSR, and restores the exception chain before returning. The separate normal
continuation at `0x0055DBA2` clears that bit before loading MXCSR; its frame
unlink at `+0xA` also handles the ISA-disabled path. All primary branches,
filter returns, recovery instructions and shared exits remain accounted for.

The full scope table at `0x005AC5E0` has header words
`FFFFFFFE, 0, FFFFFFD8, 0` and one record `FFFFFFFE, filter, handler`.
Its two HIGHLOW fields at `+0x14` and `+0x18` point to the recovered filter and
handler, respectively. The primary prologue independently references this
table, `_except_handler4` at `0x00546620`, and the original security cookie.
These links establish the exception-only entries, even though Ghidra reports
no containing functions there.

Ghidra's parent body contains 146 addresses across the 222B convex span: the
118B primary portion and 28B normal continuation. The missing 76 bytes are
the 30B filter and 46B recovery entry. Pinned Capstone decodes those original
bytes, and the complete archive section independently matches them. The ledger
now inventories all four nonoverlapping partitions; the `$seh_filter`,
`$seh_handler` and `$normal_continuation` suffixes are maintained descriptive
labels. No new C ABI or original identifier is inferred for these fragments.

## Evidence and affected scope

Private evidence is under `.analysis/origin-boundary/fp-state/`: `native.txt`,
`mxcsr-native.txt`, `owner-bodies.txt`, the SDK object, `review.py` and
`reviewed.json`. The audit checks all five whole code contributions, all data
and scope bytes, ordinary-byte agreement, complete HIGHLOW sets, internal branch
targets and both SEH entry pointers. It reuses the independently captured
math-error caller roles and verifies all 2,151 protected hashes unchanged.

Other SSE helper sections in `fpctrl.obj` gave no full ordinary-byte location
in the original `.text` during the bounded search (`locations.json`). This
does not establish their absence: inspect the actual public control/status
owners and their compiler/inlining context next, using `ieee87.obj`. No origin
or address was assigned to those unmatched sections.

Only classification, evidence, handoff and generated progress change. The
native source graph and canonical products are unchanged, so exact replay scope
is **zero units**. No authored or maintained-source exact credit is added.
