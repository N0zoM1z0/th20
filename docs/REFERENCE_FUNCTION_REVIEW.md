# REF-002: exhaustive implementation review in progress

The user requires a function-by-function review of every existing reference
implementation. REF-001's repository scan and module dispositions do not meet
that requirement. This work stays active until each implementation has an
explicit outcome. Easily recoverable exact functions are absorbed immediately;
difficult cases receive specific evidence and remaining work, then the review
continues. No default module-wide rejection or completion is permitted.

## Coverage and decisions

`reference-function-index.csv` inventories explicit C/C++ definitions, defaulted
definitions and lambdas. Deleted declarations and generated Ghidra exports are
excluded from implementation counts. `reference-source-files.csv` includes all
916 nongenerated C/C++ source/header/include files, including files with no
function bodies. Names, address hints and role hints are discovery metadata;
they are not accepted mappings or semantic conclusions.

The current parser finds 6,708 definitions: 4,193 reconstruction candidates,
2,441 test/oracle bodies, 39 tooling/support bodies and 35 historical bridge
bodies. These role hints need review. The parser reports gaps in 104 files;
manual reconciliation remains required, and this inventory is not asserted
to be a complete compiler AST. Private gap ranges are recorded rather than
silently omitted. Tree-sitter 0.25.2 and its C++ grammar 0.23.4 are pinned in
the analysis environment. Export annotation `API` is blanked for parsing only;
reference source bytes are never edited.

`reference-function-reviews.csv` binds every decision to its exact body hash.
`report-reference-functions.py` validates those bindings, counts explicit
terminal decisions separately from intermediate work, and reports untouched
bodies as pending. No scan, compile or module status grants review credit.
The first 24 native-core/export bodies have explicit decisions. The remaining
implementations and parse gaps are still pending.

## Native core: accepted components

The original target, retained reference bodies and our maintained C++ have
been checked individually. Validation-only free functions and export adapters
are distinguished from the original ECX receiver ABI.

| Target | Complete bytes | Maintained function | Exact replay | Authored credit |
| --- | ---: | --- | --- | --- |
| 0x00423FE0 | 38 | Timer::set_mode | Passed | 38 |
| 0x004530F0 | 295 | Timer::add | Passed, eight relocations | 295 |
| 0x004533B0 | 324 | Timer::tick | Passed, ten relocations | 324 |
| 0x004292E0 | 16 | ClockScalar::operator float | Passed | Origin pending |
| 0x00452F50 | 35 | ClockScalar::operator* | Passed | Origin pending |

Existing Random and Timer reset/set units still pass. Current cold replay is
nine complete units, 1,007 bytes, three independently rebuilt objects.
Authored Timer credit is five functions, 788 bytes. RNG is excluded as STL;
the two shared float-view functions remain under origin review and are not
added to authored totals. Exact names do not establish an enclosing clock or
interpolation type.

### Mode representation

Both orders of the raw masked-word expression were investigated: they differed
from the full target by three or seventeen register/instruction bytes. A
natural two-bit field assignment emits all 38 bytes exactly. The maintained
Timer has shared raw-word/bit-field union views of its observed four-byte flag
storage: bit 0 initialized, bits 1..2 mode, and the other 29 flags preserved.
This uses the MSVC x86 representation, with GCC's supported union view used
by portable state-invariant tests. It adds no padding or alternate body.

### Clock protocol and independent anchors

Add and tick initialize lazily, conditionally clear nonzero modes, select the
default clock slot, and save the previous integer. Add accumulates a scaled
delta and truncates. Tick's near-one/null paths increment the integer
independently of its float value; other rates accumulate then truncate.

The reference supplies a rate pointer as an extra parameter and replaces the
original float receiver calls with intrinsics. Maintained members restore the
target ABI, repeated float reads and actual helper calls. Scalar conversion
and multiplication are independently checked as complete 16/35-byte target
bodies, including x87 float returns and SSE multiplication.

Before canonical relocation comparison, independent Ghidra xrefs/disassembly
and raw file-backed data establish the default slot at 0x005AEFE0, initially
pointing to the 1.0f storage at 0x005AEFE4. Only the observed default slot is
declared; Timer add/tick clamp the selected mode to zero. This does not invent
four valid pointers from adjacent unrelated storage. Constants at 0x0056E72C
and 0x0056E730 encode 0.99f/1.01f; independently referenced 0x0056C8CC is 1.0f.
These anchors were inspected before the structural diagnostic reported any
solved destinations. Reset/mode anchors already have independent full units.

Portable tests cover initialization, flag preservation, interval endpoints,
null/default clocks, fractional accumulation, independent integer/float
values, and integer wrap. Float-to-integer tests use finite representable
inputs. Locked target-identical x86 emission also preserves CVTTSS2SI hardware
behavior; no broader portable invalid-conversion contract is asserted.

The 0x00423520 forwarding entry is independently inspected (26 bytes, 174
callers). Its enclosing declaration/origin remains a follow-up, rather than
inventing a constructor or return contract to gain another match.

## Compiler diagnostics and remaining work

`compile-reference-probes.py` compiles unmodified reference translation units
serially through the locked wrapper. Its profile and all compiler/header/source
identities are recorded privately. These probes discover ABI/emission/build
issues; successful compilation is not semantic acceptance, and failed recipes
do not reject all functions in a file. Build dependencies and test-specific
macros are reconciled before interpreting compiler errors.

Initial scheduler/archive/runtime probes found the runtime CMake dependency on
the scheduler include directory and archive-verifier hash macros. The diagnostic
recipe now supplies the scheduler include. The standalone verifier needs its
declared CMake definitions; that build issue carries no algorithm conclusion.

Next: individually review the scheduler's constructors, links, iterator repair,
callback mutation and dispatch entries, then runtime and archive ownership.
Continue through every indexed implementation; investigate and record hard
cases without stalling or marking untouched bodies as reviewed.

```bash
scripts/repo-python scripts/index-reference-functions.py --check
scripts/repo-python scripts/report-reference-functions.py
scripts/repo-python scripts/compile-reference-probes.py --resume
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/ci.py
```

Private evidence: `.analysis/ref002-*`, `.analysis/reference-functions/` and
object receipts under `build/`. No upstream implementation text, raw target
bytes or decompiler output is distributed.
