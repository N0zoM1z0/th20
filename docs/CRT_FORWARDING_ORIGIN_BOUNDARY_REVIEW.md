# CRT forwarding chains and complete runtime boundaries

Fifteen pending candidates (445 body bytes) are now classified as library code
and excluded from authored coverage. The review uses the locked Japanese TH20
v1.00a Steamless target, MSVC 14.44.35207 CRT archives and Windows SDK
10.0.26100.0 x86 `libucrt.lib`. The source graph and exact unit graph are unchanged.

## Reviewed entries

| Entry | Body bytes | Library operation | Archive member |
| --- | ---: | --- | --- |
| 0x00543320 | 124 | `__ftoi2` | `ftol2.obj` |
| 0x00543310 | 5 | `__ftol2_sse_excpt` | `ftol2.obj` |
| 0x0054A540 | 5 | `_free` | `free.obj` |
| 0x00557BA0 | 58 | `__free_base` | `free_base.obj` |
| 0x00547B43 | 67 | `_abort` | `abort.obj` |
| 0x00553567 | 5 | `__initialize_narrow_environment` | `environment_initialization.obj` |
| 0x00553148 | 44 | `??$common_get_or_create_environment_nolock@_W@@YAPAPA_WXZ` | `environment_initialization.obj` |
| 0x00553174 | 90 | `??$common_initialize_environment_nolock@D@@YAHXZ` | `environment_initialization.obj` |
| 0x005429FC | 5 | `??3@YAXPAX@Z` | `delete_scalar.obj` |
| 0x00542A0A | 5 | `??_V@YAXPAX@Z` | `delete_array.obj` |
| 0x00542036 | 5 | `?uncaught_exceptions@std@@YAHXZ` | `uncaught_exceptions.obj` |
| 0x005463D0 | 16 | `___uncaught_exceptions` | `ptd-match.obj` |
| 0x0055727C | 6 | `@_guard_check_icall@4` | `ucrt-checkcfg.obj` |
| 0x005419CB | 5 | `___std_init_once_link_alternate_names_and_abort@0` | `xonce2.obj` |
| 0x00553511 | 5 | `___dcrt_get_or_create_wide_environment_nolock` | `environment_initialization.obj` |

`ptd-match.obj` is the privately extracted VCRuntime `uncaught_exceptions.obj`;
`uncaught_exceptions.obj` in the table is the separate STL member. The private
`ucrt-checkcfg.obj` is UCRT's `checkcfg.obj`, not the similarly named MSVC member.
The alternate `_ftol2_sse` entry in the installed object also forwards to
`_ftoi2`; the reviewed physical address does not identify every folded alias.

## Physical chains and independent roles

The complete deallocation chain is:

```
00542A0A  operator delete[] -> 005429FC
005429FC  operator delete   -> 0054A540
0054A540  free              -> 00557BA0
00557BA0  _free_base        -> HeapFree; on failure map GetLastError into errno
```

The existing canonical manifest already independently anchors the scalar/array
delete and `free` call roles. The three extracted library objects carry those
same public symbols and REL32 destination symbols. This distinguishes three
five-byte physical wrappers even though their unrelocated opcodes are identical.
The UCRT implementation preserves its null check, process heap and failure path.
Its complete object contribution is 64 bytes: 58 bytes of instructions followed
by six original INT3 bytes. The reviewed candidate remains the full 58-byte body.

`0x00542036` forwards STL `std::uncaught_exceptions` to the 16-byte VCRuntime
`__uncaught_exceptions` at `0x005463D0`. The latter returns zero for absent thread
storage or the `_ProcessingThrow` count at +0x18. The VCRuntime object gives the
callee symbol `__vcrt_getptd_noinit`; a byte-pattern search located that member,
and its symbol table and shipped source confirmed the role. The absent-storage
path returns zero without allocating thread storage.

`0x005419CB` jumps to UCRT `abort`. Its sole reported caller,
`0x004F5510`, calls the original imported `InitOnceComplete` and takes this path
only on failure. That agrees with the STL
`__std_init_once_link_alternate_names_and_abort@0` object and the inline once
completion protocol. The 67-byte abort body retains the SIGABRT handler check,
report-fault flag, fast-fail feature test and final `_exit(3)` call. Its complete
68-byte archive contribution includes one original trailing INT3 byte; no return
is invented for the nonreturning terminal call.

The floating conversion wrapper targets the complete 124-byte `_ftoi2` body.
Both the ISA-selected `FISTTP` path and the x87 exponent/sign/range paths remain
inside the reviewed extent. Its object names the ISA variable and NaN constant;
this is the CRT conversion routine, independently of its automatic Ghidra name.

`0x00553511` forwards to the 44-byte wide-environment getter/creator, while
`0x00553567` forwards to the 90-byte narrow-environment initializer. The former
checks existing wide and narrow tables before initialization/cloning; the latter
initializes multibyte support, obtains and splits the OS environment, publishes
both environment pointers and releases temporary storage. The object symbols and
shipped `environment_initialization.cpp` distinguish the wide getter, narrow
initializer and separate initial-environment getter. The native wide getenv
caller at `0x00564257` reads 16-bit characters and calls `0x00553511`. The getter calls the separate 85-byte wide initializer at
`0x005531CE`; its lack of a multibyte-initialization call distinguishes it from
the 90-byte narrow initializer. Cross-function relocation roles consistently
identify `0x005E55AC` as the wide table and `0x005E55A8` as the narrow table.
Ordinary-byte identity alone would have incorrectly assigned the char template
to the wide getter.

`0x0055727C` is UCRT's six-byte `_guard_check_icall` jump through `0x0056C37C`.
The UCRT object references `__guard_check_icall_fptr`. The native slot contains
`0x005435EA`, whose complete listing is `RET 0`; both the jump operand and pointer
slot have original HIGHLOW relocations. The installed MSVC archive's similarly
named function is seven bytes (`MOV EAX,[pointer]; JMP EAX`), whereas UCRT's is
six bytes (`JMP [pointer]`). The latter agrees with this target. The original
load-config record is only 64 bytes and has no GuardCF pointer field; this review
does not infer that CFG enforcement is enabled from the helper's presence.

## Evidence and limits

The private `.analysis/origin-boundary/` directory retains full attested listings
and body metadata in `local-thunks.txt` / `local-thunk-bodies.txt`, caller queries
in `local-thunk-callers.txt`, and the once-completion caller in
`abort-alias-caller.txt`. `environment-width.txt` supplies the width-sensitive
consumer and initializer evidence. `runtime-corroboration.json` identifies
archive members,
complete object extents, symbols, relocation roles and byte diagnostics.
`runtime-relocation-roles.json` records the consistent cross-function bindings
observed for this origin investigation; these are not canonical exact anchors.
`extract-runtime.py`, `runtime-corroboration.py` and
`record-runtime-review.py` retain the bounded investigation commands.

All fifteen complete native bodies decode contiguously to their ledger ends;
every listing byte agrees with the locked target. All ordinary bytes of the
corresponding complete archive contributions agree, including the observed
seven alignment bytes. Original DIR32 fields have PE HIGHLOW entries; REL32
symbol roles and native chains are inspected separately. These archive
comparisons support origin and boundary review. They are not fresh compilations
of maintained source and confer no canonical exact credit.

The zero-return origin uncertainty from this checkpoint is now resolved by
[complete startup callers and locale records](CRT_STARTUP_DEFAULT_ORIGIN_BOUNDARY_REVIEW.md).
The later review classifies both `0x00543B7E` and `0x00543B83`; a function-level
caller query had omitted calls in startup instructions without an owning
Ghidra function.

Only the fifteen selected rows in each classification ledger and the associated
notes/progress change. Tracking, generated progress and protected native input /
canonical-product hashes pass. The exact replay scope is **zero units**.
