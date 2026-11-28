# CRT startup defaults, folded zero returns and callback storage

Thirteen pending candidates, totaling 196 body bytes, are now classified as CRT
library code. This includes the last pending Ghidra thunk and its shared
three-byte zero-return destination. The locked target is Japanese TH20 v1.00a
Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Body bytes | Library operation |
| --- | ---: | --- |
| 0x00543A29 | 4 | `__get_startup_argv_mode` |
| 0x00543B7E | 5 | `___scrt_initialize_mta` |
| 0x00543B83 | 3 | `folded CRT zero defaults` |
| 0x00543B86 | 66 | `___scrt_is_managed_app` |
| 0x00543BC8 | 12 | `___scrt_set_unhandled_exception_filter` |
| 0x00543D1D | 6 | `__get_startup_file_mode` |
| 0x00543D23 | 12 | `?__scrt_initialize_type_info@@YAXXZ` |
| 0x00543D2F | 3 | `__should_initialize_environment` |
| 0x00543D32 | 32 | `__initialize_default_precision` |
| 0x00543D53 | 29 | `___scrt_initialize_default_local_stdio_options` |
| 0x00543D70 | 12 | `___scrt_is_user_matherr_present` |
| 0x00543D7C | 6 | `___scrt_get_dyn_tls_init_callback` |
| 0x00543D82 | 6 | `___scrt_get_dyn_tls_dtor_callback` |

## Resolving the zero-return origin

The earlier function-level caller query reported no callers for `0x00543B7E`
and `0x00543B83`. A fresh instruction-level `xrefs_to` query instead identifies
calls in `0x0054339C..0x00543460`. Ghidra has no containing function at the two
startup callback entries `0x0054339C` and `0x0054344F`; its function-call graph
therefore omitted these real calls. For origin work, an empty `callers` result
must be checked against instruction and data references when ownership is
incomplete.

The complete installed `exe_winmain.obj` contributions for pre-C initialization
(171B), post-PGO initialization (8B) and pre-C++ initialization (18B) agree with
the full original ranges after excluding only their recorded relocation fields.
Their original instruction order and object relocation symbols identify these
uses of the same zero-return address:

| Original reference | CRT role at `0x00543B83` |
| --- | --- |
| CALL at `0x005433AF` | `_get_startup_commit_mode` |
| Pointer operand at `0x005433FC` | default `_matherr` callback |
| CALL at `0x00543416` | `_get_startup_thread_locale_mode` |
| CALL at `0x00543430` | `__scrt_initialize_winrt` |
| CALL at `0x00543454` | `_get_startup_new_mode` |
| JMP at `0x00543B7E` | default MTA stub |
| Data at `0x005996C8` and `0x005996D4` | locale-category no-op initializer |

The last two pointers are in twelve-byte `LC_ALL` and `LC_COLLATE` records.
Their original UTF-16 category names, null/C-locale pointers and callback slots
agree with UCRT `wsetlocale.cpp` and its `__lc_category` object. The complete
`no_op_initialize` contribution is the same three-byte `XOR EAX,EAX; RET` body.
The startup defaults and `_matherr` also independently have that complete body
in their respective library objects. This establishes the shared library roles
rather than identifying one unique original function name or prototype.

The five-byte `__scrt_initialize_mta` wrapper is separately bounded. Its CRT
object calls `__scrt_exe_initialize_mta` and carries an alternatename directive
to `__scrt_stub_for_initialize_mta`. The native startup calls that wrapper at
`0x00543435`, and its complete jump targets the common zero default. Keep both
physical heads while recording their distinct roles.

## Other startup leaves and complete extents

The native startup supplies independent roles for the unexpanded-argv policy
(value 1), text-file policy (`_O_TEXT`, 0x4000), environment policy (true in AL),
per-module type_info SList initialization and the matherr override test. The
29-byte stdio initializer ORs printf options with 0x24 and scanf options with
0x2 through the real getters, retaining their high words.

The default precision routine calls
`_controlfp_s(nullptr, _PC_53, _MCW_PC)` and retains its fastfail(7) error branch.
The native instructions occupy 32 bytes; the full CRT object contribution is
33 bytes including the original INT3 at `0x00543D52`. The main-startup object
used as caller evidence likewise contains 382 code bytes and one original INT3
at `0x005435DF`. Both full contributions were compared, rather than comparing
a target-sized prefix. Main startup is caller evidence here and receives no
new ledger classification or exact credit.

The two TLS accessors return **addresses of callback slots**, at `0x005E59A0`
for initialization and `0x005E599C` for destruction. The main-startup object's
relocation symbols and native consumers distinguish those pointer-to-pointer
results from loaded callbacks. The managed-image predicate checks the current
module's MZ/PE/PE32 headers, directory count and COM descriptor RVA. The filter
setter passes the CRT exception-filter address to the imported
`SetUnhandledExceptionFilter`. Original import descriptors corroborate these
SDK roles, including `GetModuleHandleW` and `InitializeSListHead`.

## Evidence and verification

The original full listings and body metadata are retained in
`.analysis/origin-boundary/startup-leaves.txt` and `startup-leaf-bodies.txt`.
`default-return-references.txt` and `startup-default-context.txt` retain the
references and previously unowned startup instructions. All thirteen reviewed
bodies decode contiguously to their original ledger ends, with no omitted
local code or owned switch table. The precision routine's terminal error call
and the MTA wrapper's tail jump remain explicit external edges.

Private `startup-defaults/whole-comparisons.json` records the complete CRT
contributions, original relocation roles and object hashes. All ordinary bytes
agree. DIR32 operands have original PE HIGHLOW relocations. The zero body has
no relocations; the wrapper has one REL32 edge. Source under the installed
MSVC CRT and UCRT trees corroborates the policies and alias directive. These
library-object diagnostics establish origin evidence, with no fresh source
compilation or canonical exact admission.

Tracking, generated progress and protected native input/product hashes pass.
Only thirteen rows in each classification ledger, review notes and generated
progress change. The exact replay scope is **zero units**. All 41 currently
inventoried Ghidra thunks now have reviewed origins; the rest of the provisional
function inventory remains a separate unfinished review.
