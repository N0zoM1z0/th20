# Verified facts and open hypotheses

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
