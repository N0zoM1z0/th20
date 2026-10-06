# Verified facts and open hypotheses

## REF-004 — 2026-10-06

- Individually reviewed: all 64 explicit archive definitions in eight files;
  eighteen native cases deferred, forty-six source API/test/report helpers.
  Total decisions: 190; 6,518 indexed bodies and 103 parser-gap files pending.
- Independent target: filename primitive 0x456270 sums pointer/count bytes
  modulo 256. Native caller 0x53A3C0 performs strlen, table selection and crypt
  parameter pushes. File-backed eight twelve-byte records at 0x5AE000 match
  reference constants; aggregate-return selector is a new reference API.
- Compiler-observed: natural shared archive_name_sum reproduces all 71 bytes
  with original cdecl ABI and no relocations. Portable cases verify explicit
  counts, embedded zeros, high bytes, wrap and zero length. Full cold replay:
  32/32 units, nine objects, 1,848 bytes; authored: 25 functions, 1,549 bytes.
- Independent target: crypt 0x4100E0 has six cdecl arguments, signed 32-bit
  arithmetic and allocator copy of min(size,limit). Reference vector/64-bit
  arithmetic and invalid-parameter guards are not its native ownership/ABI.
- Independent target: LZSS 0x5391F0 has optional output/allocation owner and
  persistent dictionary 0x5C6B38. Bit-byte fetch precedes exhaustion checking;
  source safe indexing and expansion/final-size exceptions differ. Valid
  MSB/ring/overlap semantics do not establish malformed-input equivalence.
- Independent target: ArcMngr fields at +0/+4/+8/+12 own records/count/names/
  stream; records stride sixteen with an extra end sentinel. Native lookup
  returns pointer/null and uses CRT comparison 0x555750 with global-state
  alternate path. Reference vectors, view-length ASCII comparison and index
  exceptions are individually deferred replacements.
- Independent target: file wrapper 0x410AA0 has name,size-out,loose-mode ABI,
  fixed lock-2/EH and raw buffers. Two strrchr calls corroborate the path quirk
  and explicit loose selection; source optional-vector interface omits size-out.
- Recipe observed: four unmodified archive production/verifier TUs compile
  after supplying CMake-required SHA string macros. Source tests/extraction
  validators do not run the original EXE; reports are not inherited or summed.
- Unknown: complete native archive allocator/stream/deleting lifetime, codec
  ABI/failure paths, locked global initialization and whole-game linkage/runtime.

Private evidence: .analysis/ref004-* and reference-functions/exact-replay-008.log.

## REF-003 — 2026-10-06

- Individually reviewed: all 67 explicit runtime_core bodies across nine files;
  126 total indexed decisions, 6,582 pending. One WINAPI annotation parser gap
  manually reconciled, 103 gap files still pending. File and body hash gates
  prevent silently carrying decisions to different reference revisions.
- Independently observed: original registry has 22 x86 recursive mutexes of
  48 bytes, 22 depth bytes at +0x420 and enabled byte at +0x436. Natural enable
  and disable fully replay 21 bytes each. Original accessors are unchecked;
  reference array.at bounds checks prevent direct accessor absorption.
- Independently file-backed: vtable 0x56C920 and RTTI debug_memory_resource
  establish a custom four-slot PMR receiver. Natural defaulted construction,
  destruction and always-true equality replay 31/29/15 bytes. Shared std base
  helper anchors at 0x40BDA0/0x40E5E0 are independently checked; shared empty
  emission does not establish unique owners for those helper addresses.
- Independently file-backed: vtable 0x56D4C0 has three slots and TaskInf RTTI.
  TaskInfo restores the 20-byte destructor and separate 20-byte virtual
  forwarding/53-byte nullable node operations in each direction. Default
  flags=2/null-node semantics are represented but native construction is open.
- Independently observed/corroborated: Worker 0x40B780 calls the jthread
  constructor at 0x40B810 and atomic<bool>(false) at 0x40B710. Their separately
  queried chains and installed MSVC headers establish library identities.
  Natural maintained construction fully replays 44 bytes with both calls,
  initializes +0..+12 and preserves tail padding without explicit padding.
- Compiler-observed: cold 31/31 canonical units across eight objects compare
  1,777 complete bytes. Authored exactness: 24 functions, 1,478 bytes; eleven
  new native contributions add 327 bytes. No prefix slicing or solved-field
  canonical anchors were used. Vtable/RTTI data emission is not claimed exact.
- Origin remains pending for three exact empty/defaulted PMR/TaskInfo lifetime
  contributions: custom RTTI establishes class identity, without distinguishing
  authored code from compiler synthesis. Their 80 bytes receive no authored
  credit; this checkpoint adds eight authored contributions totaling 247 bytes.
- Portable UBSan checks: registry toggles preserve adjacent storage; TaskInfo
  null/one/two-node operations mask only disable bits and preserve callback/data
  state without invoking callbacks. Linux mutex layout is not x86 evidence.
- Recorded semantic mismatch: reference finish_log throws on failed CP932
  conversion, whereas native 0x453220 calls MessageBoxW without checking that
  return. Native graphics 0x4D9E30 logs before closing Worker member +0xD90;
  free Worker-only composition omits the enclosing receiver and diagnostic.
- Unknown/pending: PMR allocation/deallocation, Worker close/detach/join and
  destructor, native allocator deleting flags/global lock lifetime, native
  variadic logging/failure paths and whole-program linkage/runtime. Reference
  isolated CPU fixtures share source PMR/thread state and omit these paths.

Private evidence: .analysis/ref003-*, reference-functions/exact-replay-007.log
and compiler receipts under build/. Maintained public credit links identify
Oracatt/Touhou20 as the review reference and N0zoM1z0/th095 as workflow origin.

## REF-002 — 2026-10-06

- Review coverage: 6,708 explicit nongenerated definitions in 916 C/C++ files;
  104 parser-gap files still require manual reconciliation. Fifty-nine bodies
  have individual hash-bound outcomes; remaining bodies are unreviewed.
- Compiler-observed: natural Timer two-bit assignment matches all 38 bytes.
  Add/tick match 295/324 bytes with separately established receiver helpers,
  default slot 0x5AEFE0, float 1.0 storage 0x5AEFE4, and threshold constants
  0x56E72C/0x56E730. Only the observed default pointer slot is declared.
- Semantically checked: tick's near-one/null path advances integer and float
  independently; strict 0.99/1.01 endpoints scale. Receiver float helpers
  match 16/35 bytes, but their enclosing owner/origin remains unknown.
- Independently observed: dispatch stack argument/caller cleanup/EAX result
  establishes cdecl int32(void*) callbacks. Link consumers establish the five
  pointer slots. Eleven clean FunctionChain members replay all 443 bytes.
- Shared pointer-store addresses 0x412DA0/0x412DC0 have multiple receiver views;
  exact credit counts each original address once and does not prove a unique
  class owner. Iterator/allocator/List base/EH protocols remain deferred with
  individual notes in reference-function-reviews.csv.
- Cold replay: twenty complete units, four objects, 1,450 bytes; authored
  exactness is sixteen functions, 1,231 bytes. Library and unknown-origin
  comparisons remain outside authored credit.
- User-requested play aid: initial stock-only mode changed death immediate
  RVA 0xF849D from -1 to 0. The user then requested no hit effects: hit entry
  0x4F86F0 now returns immediately. Its three collision callers pass ECX with
  no stack arguments and ignore its return, then produce their own result.
  Normal death code is restored when upgrading the earlier in-memory patch.
  No file-oracle changes or reconstruction runtime credit follow.

## REF-001 — 2026-10-06

- Observed: reference commit 011aa029d1dac51578107bc98a0006bd750e453c uses
  the same target hash. Its v1.00c label matches embedded title/replay strings;
  registry/package v1.00a is separate evidence, not a different binary.
- Audited: all 10,822 tracked files; 648,476 matching byte-bearing disassembly
  rows; 401 stale JSON hash references. All 55 review groups have dispositions
  accounting for every file. See `REFERENCE_REVIEW.md` and the audit manifests.
- Independently observed: 153 retained-source diagnostic sites in 124 functions
  pass target-string, attested Ghidra-reference and Capstone-immediate checks.
  Two ownerless reference sites are deferred, with no credit.
- Compiler-observed: natural C++20 /Od bodies fully replay four complete COFF
  functions with explicit independently reviewed relocation anchors.
- Corroborated library origin: RNG step/invocation match installed MSVC
  minstd_rand machinery. These and the reviewed __aullshr helper are excluded
  from authored totals, regardless of successful component replay.
- Accepted authored exactness: Timer::reset and Timer::set, 131 bytes total.
  Timer::set_mode retains three differing bytes and has no exact credit.
- Semantically checked: reset preserves flags; mode replaces only bits 1..2;
  set initializes only when required and preserves modulo-32 previous values.
  Independent portable tests pass with undefined-behavior sanitization.
- Unknown: full Timer clock/rounding behavior, enclosing 28-byte RNG ownership,
  remaining origin/boundary review, global compiler flags and whole-program
  compile/link/runtime. Reference reports do not resolve these unknowns.

Public repository: https://github.com/N0zoM1z0/th20. Maintained text and commit
messages are English; new subjects use `gpt-6.1-sol: <description>`.

## BOOT-001 — 2026-10-06

- Observed: selected file SHA-256/MD5/size, PE32/x86, image base, entry,
  six section hashes and linker 14.44 are pinned in `config/target.toml`.
- Corroborated: immutable THCRAP registry exactly identifies selected
  Steamless v1.00a, Steam-original backup and original v1.00a `custom.exe`.
  Official release/store sources establish release identity and Japanese
  language, without providing executable checksums.
- User decision: use existing Steamless as exact oracle, retain backup as
  provenance. Non-Steam retail has a different registered whole-file hash.
- Observed: five non-code raw sections compare identical between selected
  file and backup; backup `.text` is encrypted and has `.bind`. No new
  transformation or patch was applied.
- Ghidra-observed: 6,928 provisional candidates. No origin, boundary, authored
  source or exact unit is accepted by auto-analysis.
- Compiler-observed: installed candidate emits ordinary x86 COFF with
  `_MSC_FULL_VER=194435211`; linker emits PE32/i386. Win32/legacy DirectX
  headers/libraries and console/D3DX smoke run under isolated Wine.
- Inferred/corroborated: companion Rich-header build 35211 suggests game
  compiler 19.44.35211. Game lacks its own Rich header, so the exact compiler
  build remains unproved. Mixed library builds 33140/35207/35211 in custom
  are not a license to assume the game's complete library provenance.
- Unknown: game optimization/inlining/security/EH/RTTI/floating-point/runtime
  flags, original SDK/CRT versions, translation-unit partitioning, original
  function ownership and whole-game runtime status.

Durable new facts require target-local addresses, commands/input hashes and
independent evidence references. Private experiment logs remain `.analysis/`.
