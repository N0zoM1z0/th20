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

The current parser finds 6,706 definitions: 4,193 reconstruction candidates,
2,439 test/oracle bodies, 39 tooling/support bodies and 35 historical bridge
bodies. These role hints need review. The parser reports gaps in 103 files;
manual reconciliation remains required, and this inventory is not asserted
to be a complete compiler AST. Private gap ranges are recorded rather than
silently omitted. Tree-sitter 0.25.2 and its C++ grammar 0.23.4 are pinned in
the analysis environment. Export annotation `API` and scheduler CPU-oracle
`__cdecl` annotations are blanked only in their individually reconciled files.
Flat inline-assembly statements are blanked only in the manually reconciled
platform-services CPU oracle. Offsets and hashes use the original bytes; reference source is never edited.

`reference-function-reviews.csv` binds every decision to its exact body hash.
`report-reference-functions.py` validates those bindings, counts explicit
terminal decisions separately from intermediate work, and reports untouched
bodies as pending. No scan, compile or module status grants review credit.
The first 408 native-core/export/scheduler/runtime/archive/input/platform-service/
tool/test bodies have explicit decisions. The remaining 6,298 indexed bodies
are pending. The separate
`reference-parse-gap-reviews.csv` binds manual reconciliation to the file hash
and parser-gap count: six of 103 files are reconciled, leaving 97 pending.

## REF-007: platform services' 43 definitions reviewed

All ten C++ source/header files are read in full, with individual decisions for
43 actual definitions: two absorbed exact components, fourteen native cases
deferred with specific differences and twenty-seven support helpers. The
README, CMake recipe, CPU-validation report and top-level extract_evidence.py
are also reviewed. That Python helper has no function definitions: its hash
guard is useful, but hardcoded paths and prefix extents are diagnostic only.
Total decisions: 408; 6,298 definitions and 97 parser-gap files remain pending.

| Target | Complete bytes | Maintained function | Authored credit |
| --- | ---: | --- | --- |
| 0x0041FB10 | 309 | InputBindings constructor | 309 |
| 0x0041FC50 | 85 | InputBindingSlots constructor | Origin pending |
| 0x004B9B80 | 137 | ConfigurationFlags constructor | Origin pending |

Three 16-byte signed binding records recover the original receiver ABI,
member-default construction and twenty-four assignments. Native signed loads
and disabled -1 bindings independently corroborate the int16 fields. The
zeroing member constructor is independently queried before anchoring three
REL32 calls. Flags initialize nine one-bit members individually and preserve
bits 9..31. Native configuration construction and six independent graphics
option consumers corroborate storage and named bits. The complete 176-byte
configuration owner is still deferred. Default-slot and flag constructors
might be compiler-generated contributions and receive no authored credit.

Cold complete replay passes 40/40 units, eleven objects, 3,188 full bytes.
Authored exact: 31 functions, 2,667 bytes; source-present mappings: 40.
Portable checks cover all signed defaults, standalone slot zeroing and retained
high flag bits in preinitialized storage. Four unmodified reference production
TUs compile serially; this does not accept their native protocols.

The CPU oracle's five flat inline-assembly statements caused two phantom
bodies and hid the actual enclosing original_conversion function. Narrow
parse-view normalization recovers that owner and removes both phantoms; all
365 prior reviewed IDs/body hashes remain unchanged. Regression verifies
original body/file hashes and offsets. Two remaining WINAPI annotation gaps
are manually reconciled; the reference files remain untouched.

Deferred native clock code uses fixed globals, lock-5 tracked guards and a
special compiler conversion ABI. Its full unsigned-conversion helper includes
feature-dispatched AVX512VL code; testing only SSE2 is not complete equivalence.
Native rounding returns an integer status through separate CRT helpers, while
the reference uses a bool adapter. Writer lock-2/EH, 522-byte buffer clearing,
uninitialized write count, raw allocator/file ownership and returned save status
are not recovered by the source RAII/vector/void replacements. Initialization
uses one retained 4096-WCHAR scratch buffer and writes system-option results to
adjacent globals; no system-setting mutation was executed during this review.

The reference's missing-%s argument comment is contradicted by native pushes:
0x4DC473..476 supplies the filename, and caller 0x41E8E5 supplies th20.cfg.
The source instead logs a joined path. Source path initialization also appends
a log entry where the native path calls a verified no-op, changing normal-path
behavior. Truncated-file rejection and eager zero initialization differ too.

The retained 66,270-check CPU report includes fourteen source-only decode
checks, leaving 66,256 native fixture checks. It maps the target without normal
entry/TLS startup, manufactures lock/global/IAT state and forces SSE2. NaN/
subnormal offsets, feature-dispatch variants, real files/path initialization and
cross-thread scheduling are outside that evidence. Reports and source-only
Windows service tests were read, not rerun or credited as native exactness.

Private evidence: `.analysis/ref007-*` and fresh compiler receipts.

## REF-006: input's 84 definitions reviewed

Every definition in all seven input source/header/test files now has an
individual hash-bound decision: five absorbed exact components, twenty-eight
native cases deferred with specific differences and fifty-one support helpers.
Both parser-gap files are manually reconciled: nine WINAPI callback annotations
and two CALLBACK annotations; all actual bodies are present in the index.
Total review decisions: 365; 6,342 definitions and 98 parser-gap files pending.

| Target | Complete bytes | Maintained function | Relocations |
| --- | ---: | --- | --- |
| 0x00421720 | 50 | InputDevice::reset_header | None |
| 0x00421AB0 | 31 | InputDevice::initialize_keyboard | None |
| 0x00421AD0 | 40 | InputDevice::initialize_xinput | None |
| 0x00420510 | 105 | map_input_byte | None |
| 0x004228B0 | 583 | InputButtonState::update | Eleven REL32 calls |

The original Device entries are thiscall members, while the reference exposes
free functions. Maintained members restore the original receiver, parameter
widths and callee stack cleanup. Reset affects only the first sixteen bytes;
keyboard/XInput initialization preserves other header fields and all history.
The byte-mapping helper retains separate conditional OR and return expressions,
including the second byte read after the store and disabled negative bindings.

ButtonState is 704 bytes; Device is 980 bytes on x86, with state/raw/tail at
+0x10/+0x2D0/+0x3D0. Native constructor, poll and frame consumers corroborate
retained storage rather than arbitrary padding. Update walks a real array of
32 counters using progressive remaining-input and output-bit cursors. Unsigned
wrap, threshold-eight held mask, first repeat at frame 26 and eight/twelve-frame
recurrences remain intact. Retained arrays and suppression/device-kind words
are preserved. The independently queried callee 0x414580 implements receiver
plus index*4 with RET4; installed MSVC std::array indexing matches its contract.
Canonical relocation anchors use that separate observation, not solved fields.

Cold complete replay passes 37/37 units, ten objects, 2,657 full bytes.
Authored exact: 30 functions, 2,358 bytes. Portable checks exercise frame cadence,
bit31, releases, wrap, retained state, partial-header initialization and negative/
high-bit byte bindings. All three unmodified input production TUs compile in
serial diagnostics; compilation alone grants no native acceptance.

Deferred entries preserve specific ABI/ownership differences. Native polling,
legacy polling, startup sampling, shutdown, rebuild, XInput enumeration and
whole-frame sampling produce results that the reference drops as void. Device
DirectInput initialization has a Device receiver; reference moves it to
Controller. Native Controller owns 0x2EF8 bytes, TaskInf/RTTI/EH and fixed globals;
reference appends a context pointer and introduces Host virtual dispatch.
Native enumeration callbacks ignore userdata and use singleton/device globals;
reference uses injected userdata. WMI deliberately differs in BSTR allocation
and VariantClear behavior. Keyboard-clear failure and invalid mapping/selection
exceptions are changed policies. Native bit mapping's wide x86 shift domain
still needs a defined natural C++ explanation before exact acceptance.

The upstream 44,271 CPU comparisons are reviewed retained evidence, not a fresh
run. The oracle maps the target and initializes original locks but bypasses
ordinary entry/TLS startup, fixtures OS/COM observations, excludes vptr/context
from Controller comparison, and checks empty COM shutdown. Live discovery,
original allocator/teardown and concurrent reconfiguration remain unverified.
Support adapters and fixtures are individually reviewed without game credit.

Private evidence: `.analysis/ref006-input-*.asm`, `ref006-input-*.decomp`,
`ref006-input-compile.log`, `ref006-exact-replay.log` and compiler receipts.

## REF-005: tools and root/scheduler tests reviewed

All 39 tooling/support definitions, 37 root test definitions and 15 scheduler
CPU-oracle definitions now have individual support-reviewed decisions. These
91 reviews cover binary/PE/ECL readers, serialization and reporting, CLI output
guards, indexed asset extraction, synthetic parser fixtures, target mapping,
floating-point preparation and scheduler state normalization. They grant no
native exact credit. Native core's indexed production bodies were already
reviewed; the next coherent production family is input, with 84 definitions.

The scheduler oracle's forward declarations were incorrectly parsed as one
extra `shutdown_callback` body swallowing the following `World` class. Narrow
annotation normalization removes that unreviewed phantom and its three parser
errors; all 190 prior review IDs and original body hashes remain unchanged.
A synthetic regression checks real definitions, preserved offsets and original
hashes. Two further gaps are manually reconciled: CLI Windows/POSIX conditional
entry declarations share one body; root CPU-test inline x87 instructions are
inside already indexed functions. Neither omits another implementation.

The portable binary-parser CTest passes, including 928 ECL bit mutations, but
its stricter error policies are tool contracts. CPU tests map the original
without ordinary entry/TLS startup and prepare a fixed FP environment; x87
control-word restoration does not restore the full floating-point stack/status.
Scheduler tests manufacture nodes and callbacks, disable source dispatch locking
and normalize address-like state words. Owned-node allocation is source-only.
These tests do not establish native allocation, renderer shutdown, cross-thread
locking, exception unwinding or complete raw-byte equivalence.

Production source, profiles and relocation anchors are unchanged. The existing
32 complete exact units remain the last cold replay checkpoint; no new exact
claim is added by this review batch. Private evidence: `.analysis/ref005-*`.

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
forty complete units, 3,188 bytes, eleven independently rebuilt objects.
Authored credit is thirty-one functions, 2,667 bytes. RNG is excluded as STL;
the two shared float-view functions, three empty/defaulted lifetime
contributions and two configuration initializer contributions remain under origin review and are not added to authored totals.
Exact names do not establish an enclosing clock or
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

## Scheduler: all 35 indexed implementation bodies reviewed

Every definition in scheduler.cpp and scheduler.hpp has an individual
body-hash-bound outcome: eleven absorbed exact, eighteen reviewed nonexact,
and six integration/support helpers. Tests and callers in other files still
need their own review; this is not a module-wide completion claim.

| Maintained contribution | Original entry | Complete bytes |
| --- | --- | ---: |
| Link constructor | 0x00411970 | 64 |
| Link::insert_after | 0x00411EE0 | 76 |
| Link::insert_before | 0x00411F30 | 76 |
| Node::set_callback | 0x00412D50 | 42 |
| Node::set_userdata | 0x00412D10 | 22 |
| Node::set_owned | 0x00412D30 | 26 |
| Node::enable | 0x00412D80 | 26 |
| Node::disable | 0x004127F0 | 26 |
| Node::set_before_insert | 0x00412DC0 | 22 |
| Node::set_shutdown_callback | 0x00412DA0 | 22 |
| Node::clear_callbacks | 0x00411B80 | 41 |

All eleven pass complete canonical replay with no relocations: 443 authored
bytes. Target node construction and link consumers independently establish
five Link pointer slots and 20/44-byte x86 Link/Node storage. Dispatch's
indirect calls pass userdata on the stack, clean four bytes in the caller,
and inspect EAX, establishing cdecl int32(void*) callback ABI. The /Gd profile
states that calling convention explicitly. Portable tests check flag masking,
callback clearing without invocation, link initialization, neighbor insertion
and null-end branches.

The pointer stores at 0x00412DA0/0x00412DC0 also serve equivalent Link
observer/owner accessors. Each original address receives credit once; shared
emission does not establish a unique Node owner. List/Iterator allocation,
construction and destruction are not inferred from matching setters.

Deferred cases have individual reasons in reference-function-reviews.csv.
Examples include Iterator construction's two original stack arguments versus
one reference argument; Node/Iterator FS/EH registration missing from free
initializers; the List/base constructor's two tail stores; allocator/debug
owner indirection; merged update/draw APIs with extra Environment/bool
arguments; original separate accessor calls; and shutdown's missing renderer
flush at 0x004D9E30. These are current direct-absorption limits, not proofs that
future natural reconstruction is impossible. No padding, inert stores or
invented signatures were added to force them.

Private independent evidence is in .analysis/ref002-scheduler-{leaves,links,
dispatch,remaining}.* and exact-replay-004.log. Reference TU compilation is
only diagnostic; no behavior claim is inherited from its passing tests.

## REF-003: runtime_core's 67 explicit definitions reviewed

All nine nongenerated runtime_core source/header/include files were read.
Their 52 candidate and 15 test/oracle definitions each have a body-hash-bound
decision: nine absorbed reference bodies, twenty-four deferred native cases
and thirty-four integration/test helpers. Those nine absorbed bodies restore
eleven distinct original contributions; wrappers/helpers are counted once per
original address. No other module is marked reviewed by this checkpoint.

| Maintained contribution | Original entry | Complete bytes |
| --- | --- | ---: |
| LockRegistry::enable / disable | 0x0041CCC0 / 0x0041CA30 | 21 / 21 |
| DebugMemoryResource constructor / destructor | 0x00418DB0 / 0x00418E90 | 31 / 29 |
| DebugMemoryResource::do_is_equal | 0x0041C9F0 | 15 |
| TaskInfo::~TaskInfo | 0x0041FDF0 | 20 |
| TaskInfo virtual enable / disable | 0x00421680 / 0x00421760 | 20 / 20 |
| TaskInfo enable / disable helpers | 0x004216A0 / 0x00421780 | 53 / 53 |
| Worker constructor | 0x0040B780 | 44 |

Cold canonical replay passes every byte and relocation of these eleven units,
327 new compared bytes, of which 247 receive authored credit. Existing units remain exact. The complete replay is
31/31 units across eight freshly built objects; comparison includes all 1,777
bytes, with 1,478 authored bytes. Partial PMR/Worker declarations do not close
allocation or thread lifetimes, and no whole-program linkage is claimed.

Custom RTTI establishes the PMR/TaskInfo class identity, but does not identify
whether their empty/defaulted constructor/destructor contributions were
authored or synthesized by the compiler. Those three full exact functions stay
under origin review and receive no authored credit; their units remain replayable.

Independent constructor disassembly establishes 22 recursive mutexes of 48
bytes, followed by 22 depth bytes and the enable byte at +0x436. Portable tests
check that toggling changes only that byte and restores the object state;
Linux mutex storage is not used as proof of the x86 representation.

Raw file-backed RTTI and vtables independently establish debug_memory_resource
at 0x0056C920 with four PMR slots, and TaskInf at 0x0056D4C0 with three slots.
The PMR equality override always returns true; installed standard new/delete
resources use identity equality, corroborating a custom implementation. Natural
defaulted custom construction/destruction call the original shared std base
helpers and install the observed custom vtable. Matching these function bodies
does not establish complete matching vtable/RTTI data or deleting destructors.

TaskInfo restores virtual forwarding plus separate two-node helpers rather
than merging both into each virtual body. Portable tests cover null, one and
two nodes, masking only the disabled flag, preserving callback/data state and
never invoking callbacks. Worker construction follows independently checked
jthread and atomic<bool> constructor chains: twelve-byte thread state at +0,
false at +12, preserved tail padding. Installed MSVC headers corroborate those
library identities before canonical anchors are accepted.

Each deferred case records its own evidence and follow-up. Specific differences
include reference array.at bounds checks versus unchecked native indexing;
lazy lock singleton versus fixed native global storage; native allocator
receiver/deleting flags versus free factories; raw allocation's two native
arguments and new-handler failure path; merged va_list logging versus two
complete cdecl variadic entries; and a conversion-failure exception absent
from the original finish-log body. The reference worker synchronization helper
is not the complete graphics member at 0x004D9E30: that native body logs a
diagnostic and closes its Worker subobject at +0xD90.

Program-entry bridges and injected renderer lambdas are recorded as reference
integration support, not duplicate native implementations. The isolated CPU
oracle resolves selected imports/heap state and redirects the mapped original
PMR default global to a source resource. It checks limited constructor, lock,
string, allocation and source-created-thread cases. It omits allocation
failure/new-handler, original variadic formatting, MessageBox and original game
entry. Its report is not inherited as our runtime acceptance. Source-only
tests and every explicit fixture lambda are reviewed separately.

Manual reconciliation of cpu_compare.cpp's sole parse gap identifies WINAPI
on line 10 as the annotation error. Full reading accounts for all five explicit
bodies and the separately indexed included worker fixtures. The hash/count
binding is checked publicly; no completeness claim follows for the other 103
files with parser gaps.

Private independent evidence: .analysis/ref003-runtime{,-extra}.asm,
ref003-{resource,task}-vtable.json, ref003-worker-{construct,library}-anchors.asm,
ref003-pmr-base-anchors.asm and reference-functions/exact-replay-007.log.

## REF-004: archive's 64 explicit definitions reviewed

All eight nongenerated archive source/header files were read, including both
test drivers and the extraction verifier. Every indexed definition receives
an individual decision: eighteen native cases deferred with specific ABI or
behavior differences, and forty-six source API, integration, fixture or report
helpers. No archive file has an outstanding parser gap. Total explicit reviews
are 190; 6,518 indexed bodies and 103 parser-gap files remain pending elsewhere.

Independent full target disassembly covers the crypt primitive, filename sum,
LZSS, header/catalog parsing, aligned name advancement, lookup, member reads,
manager close/open/size and full file-selection wrapper. It establishes:

- 0x00456270 only sums a caller-counted byte sequence modulo 256 and returns
  a byte. The parameter-table lookup happens inside 0x0053A3C0, after strlen
  and this sum. Eight twelve-byte records at 0x005AE000 independently match
  the reference's key/step/block/limit values. An aggregate-return parameter
  selector is a reference API, not the native sum contribution.
- 0x004100E0 is a six-argument cdecl in-place crypt routine. It uses signed
  32-bit lengths and an allocator-owned copy of min(size, limit), whereas the
  reference uses vectors, signed 64-bit arithmetic and additional rejection
  conditions. Odd-byte/short-quarter-block tail and permutation/key behavior
  are corroborated, without accepting the new ownership or failure contract.
- Native 0x005391F0 accepts input/length/optional-output/allocation-size, can
  allocate through the original owner and returns a pointer. Dictionary
  0x005C6B38 persists and each stream cursor starts at one. Its bit reader
  fetches before the exhaustion check; the reference checks before indexing.
  Reference expansion/final-size exceptions and vector return are additional
  policies. Literal, thirteen-bit ring address and length-plus-three behavior
  agree on valid streams; malformed-input equivalence is not claimed.
- Native ArcMngr is sixteen bytes: records +0, count +4, names +8 and stream
  +12. Parse uses stream virtual calls and allocates count+1 sixteen-byte
  records, with a final stored-end sentinel. Close logs and separately releases
  names, records and stream. Reference vector/unique_ptr/path/error storage
  and injected/embedded dictionary are different lifetime/receiver designs.
- Native lookup returns a record pointer or null and calls CRT comparison
  0x00555750. That helper has an ASCII fast path and a global-state-dependent
  alternate path. Reference explicit-length ASCII views and throwing index
  results cannot represent its complete native contract.
- The full file-selection entry 0x00410AA0 owns lock-2/EH, a size-output
  argument, raw buffers and explicit loose-file mode. Its two strrchr calls
  preserve the observed backslash/slash quirk; an absent archive member does
  not select filesystem fallback. A standalone view-return basename helper
  is not the whole original entry.

Maintained ArchiveCrypt recovers the counted filename sum with its original
two-argument cdecl ABI and one shared natural body. All 71 bytes replay exactly,
with no relocations. The reference selector row records this accepted subpart
while leaving its broader aggregate-return API nonexact. Tests cover explicit
lengths, embedded zeros, high bytes, wrap, zero length and the sum of all 256
byte values. This adds one authored function; cold replay is now 32/32 units,
nine objects, 1,848 compared bytes. Authored exactness: 25 functions, 1,549 bytes.

The source tests, dictionary-borrowing lambdas, manager tests and extraction
verifier are individually classified as support. Their checks compare valid
decoded resources to external extraction or exercise source-defined rejection
and lifecycle behavior; none executes the original game. Duplicate-index
comparison and first-match unique-member tests have different scopes and are
not summed. Old report totals are not imported as fresh acceptance.

All four selected unmodified archive production/verifier TUs compile in serial
diagnostic probes. The verifier recipe now supplies the source SHA string macros
from its actual CMake contract; missing build definitions are not algorithm
failures. Conservative receipt checks still retry after any source changes.
This compilation result is not linkage, native runtime or direct ABI acceptance.

Private evidence: .analysis/ref004-archive-target.asm, ref004-name-compare.asm,
ref004-crypt-table.json, reference-functions/exact-replay-008.log and serial
reference compiler receipts/logs. Original bytes and reference source stay private.

## Compiler diagnostics and remaining work

`compile-reference-probes.py` compiles unmodified reference translation units
serially through the locked wrapper. Its profile and all compiler/header/source
identities are recorded privately. These probes discover ABI/emission/build
issues; successful compilation is not semantic acceptance, and failed recipes
do not reject all functions in a file. Build dependencies and test-specific
macros are reconciled before interpreting compiler errors.

Initial scheduler/archive/runtime probes found the runtime CMake dependency on
the scheduler include directory and archive-verifier hash macros. The diagnostic
recipe now supplies the scheduler include. Cached probes verify the object,
receipt, all source fingerprints and included headers; stale entries and failed
compilations are retried rather than being accepted by source hash alone. The standalone verifier needs its
declared CMake definitions; that build issue carries no algorithm conclusion.

Next: review platform_services' 44 definitions and every
remaining implementation. Deferred scheduler/runtime/archive/input owner/ABI recovery
is recorded separately.
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
