# CRT math exception dispatch and encoded user callbacks

Eleven pending entries are library code in the shared x87 math-error protocol.
Their 2,177 instruction bytes belong to ten complete SDK contributions totaling
2,231 bytes, including six alignment bytes and 48 embedded switch-table bytes.
No source or canonical unit changes in this review; affected exact replay scope
is **zero units**.

The target is the locked Japanese TH20 v1.00a Steamless executable. Independent
symbols and complete sections come from Windows SDK 10.0.26100.0 x86
`libucrt.lib`: `genexcep.obj`, `87except.obj`, `fpexcept.obj` and `matherr.obj`.
The private `.analysis/origin-boundary/math-error/` directory retains extracted
members, attested Ghidra listings, caller references, `review.py` and
`reviewed.json`. All reviewed code decodes contiguously and appears in the
attested listings. Full ordinary bytes, HIGHLOW sets, local branches, embedded
table destinations and shared relocation roles agree with those objects.

## Reviewed entries and owned extents

| Entry | Instruction bytes | Archive symbol | Complete contribution |
| --- | ---: | --- | --- |
| `0x005640A0` | 23 | `__startTwoArgErrorHandling` | shared 83B `genexcep.obj` section |
| `0x005640B7` | 60 | `__startOneArgErrorHandling` | remainder of that same section |
| `0x00564100` | 277 | `__87except` | 312B, including 3B NOP and 32B switch table |
| `0x00553B40` | 809 | `__handle_exc` | 809B |
| `0x00553E70` | 35 | `__raise_exc` | 35B |
| `0x00553EA0` | 785 | `__raise_exc_ex` | 804B, including 3B NOP and 16B switch table |
| `0x005541D0` | 49 | `__set_errno_from_matherr` | 49B |
| `0x00555910` | 29 | `___acrt_has_user_matherr` | 29B |
| `0x00555930` | 15 | `___acrt_initialize_user_matherr` | 15B |
| `0x00555940` | 57 | `___acrt_invoke_user_matherr` | 57B |
| `0x00555980` | 38 | `___setusermatherr` | 38B |

The ledger's 277B and 785B instruction extents remain valid. Their owned tables
must also be retained in a future complete source comparison. `_87except` has
eight HIGHLOW case pointers at `0x00564218..0x00564237`; its `0F 1F 00` NOP
occupies `0x00564215..0x00564217`. `_raise_exc_ex` has four HIGHLOW case pointers
at `0x005541B4..0x005541C3`, preceded by the same three-byte NOP at
`0x005541B1`. Every case target is an instruction start inside its own body.
No table word is treated as an extra function or omitted from the review.

## One shared x87-to-C error bridge

The two assembly entries are partitions of one section. The 23B two-argument
prefix saves EAX as the error type and copies the second double argument from
`[EBP+0x18]`/`[EBP+0x1C]` into its local record, then jumps to the shared
continuation at `0x005640C0`. The single-argument prefix occupies nine bytes
before falling into that same continuation. Its 60B ledger extent owns the
continuation once; the two-argument entry does not acquire a duplicate tail.

The continuation stores ST(0) as the double result, ECX as the function-name
pointer, and the first double from `[EBP+0x10]`/`[EBP+0x14]`. It passes EDX,
the 32B local exception record and the saved control-word address to `_87except`
at `0x00564100`. It then reloads the possibly changed result and restores the
saved x87 control word when it differs from `0x27F`. The one-argument entry
does not initialize the unused second-argument slot. A reconstruction must
retain this register/stack contract rather than invent a normal cdecl prototype
or initialize fields solely to shape the compiler.

The earlier [common x87 exits](CRT_X87_CONTROL_TANGENT_ORIGIN_REVIEW.md) already
identify these two destinations. Ghidra's reference query lists eight calls to
the one-argument entry, but misses the original call to the two-argument entry
at `0x0055B88E`; the retained common-object comparison and original operand
establish that call independently. An empty reference list is not an absence
of callers.

## Handling masks, raising exceptions and errno

`_87except` maps the exception type through its eight-entry table, asks
`_handle_exc` to process the result under the saved control word, and invokes
`_raise_exc` if handling remains necessary. For operation IDs `0x10`, `0x16`
and `0x1D`, it includes the second double in the floating exception record.
It applies `_ctrlfp` to the resulting saved word before processing the user
callback/errno path. Type 8 bypasses the user callback. An installed callback
can suppress the errno fallback by returning nonzero.

The full 809B `_handle_exc` preserves the original mask checks, directed
overflow result selection, denormal shifting and guard/round/sticky decisions,
including the current rounding-mode query. It writes the adjusted double and
updates floating status through `_set_statfp` at `0x0055DC10`; its final integer
result is nonzero when no pending bits remain unhandled.

The 35B `_raise_exc` forwards six arguments plus a zero width selector to the
785B `_raise_exc_ex`. The latter builds the floating exception record, calls
`_clrfp`, and invokes the original `RaiseException` import through `0x0056C158`.
The PE import descriptor independently names `KERNEL32.dll!RaiseException`.
The post-call path is real: it reads the handler-modified record, updates the
saved control word through the four-entry rounding table and precision branches,
and copies either a float or double result back according to the width selector.
Treating the OS call as unconditionally nonreturning would lose this behavior.

The 49B errno helper sets 33 for type 1 and 34 for types 2/3, leaving the other
types alone. Both original calls target `_errno` at `0x005516C1`. Other external
floating-state/decomposition helpers remain separately pending; their roles and
addresses are recorded in `reviewed.json`, without claiming their bodies here.

Four complete constant contributions also agree: double zero (8B) at
`0x0056CD50`, the 16B sign mask at `0x00597070`, positive infinity (8B) at
`0x005989C0`, and maximum finite double (8B) at `0x005989C8`. The first two are
in `fpexcept.obj`; `copysign.obj` independently names the latter two. All forty
bytes and their absence of HIGHLOW fields were checked.

## Encoded callback state and startup evidence

All four matherr state methods use the same original four-byte slot at
`0x005E55D4`. `matherr.obj` gives it one four-byte BSS contribution, and the PE
places it in the zero-filled virtual tail of `.data`. The initializer stores
its already encoded argument directly. The shipped UCRT
`internal/initialization.cpp` computes encoded null before calling this
initializer; its raw zero-filled image value is not the later initialized
null representation. The subsequent
[UCRT lifetime review](CRT_UCRT_LIFETIME_CALLBACK_ORIGIN_REVIEW.md) resolves the
empty Ghidra reference result: the unlisted `initialize_pointers` body contains
an original CALL at `0x0055390A` to this initializer, passing the security cookie
as encoded null. Complete archive/table roles and original-byte decoding retain
that native caller independently of Ghidra's incomplete instruction inventory.

The setter encodes a callback with the security-cookie rotation/XOR and stores
it. The presence check decodes the same slot and returns a boolean in AL. The
invoker likewise decodes it, returns integer zero when absent, or checks the
target through the guard pointer at `0x0056C37C` and returns the callback result.
This pointer is the [already reviewed CRT guard slot](CRT_FORWARDING_ORIGIN_BOUNDARY_REVIEW.md).

Original startup provides a second role check: `0x005433FC` pushes the folded
default `_matherr` at `0x00543B83`, then `0x00543401` calls the 38B setter at
`0x00555980`. This is conditional on the preceding user-override test; it is
not an unconditional registration claim. The complete `exe_winmain.obj`
startup evidence is retained in the
[startup-default review](CRT_STARTUP_DEFAULT_ORIGIN_BOUNDARY_REVIEW.md) and
`.analysis/origin-boundary/startup-default-context.txt`.

The eleven origins are library/high-confidence/exclude. This review changes
only their rows in the two classification ledgers, evidence, handoff and generated
progress. All 2,151 protected native input/product hashes in
`protected-hashes-tangent.json` remain unchanged. There is no new authored or
maintained-source exact credit.
