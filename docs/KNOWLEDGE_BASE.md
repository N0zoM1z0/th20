# Verified facts and open hypotheses

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
- User-requested play aid: death's immediate at RVA 0xF849D changes -1 to 0;
  original 0x4E1250 adds it to life stock +0xB8. Windows ASLR launch, readback
  and repeated attach pass; on-disk target hash is unchanged. Full gameplay
  hit/respawn validation and reconstruction runtime credit are not claimed.

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
