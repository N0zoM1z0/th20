# CORE/RECON-750 — entire 12,140-byte Bullet command Boss: 203/210 canonical call roles, seven remaining native children

**The entire original TH20 Bullet::run_extended_commands game function remains source-absent and NONEXACT.** This audit re-reads all 12,140 original executable bytes, all 2,490 original i386 instructions, all 210 real E8 direct calls and all three physical PE HIGHLOW switch tables, then joins actual native E8 destinations to the **current**, separately source-present canonical strict graph. It does not credit the nonexact giant parent with any game-authored code bytes.

Original locked Japanese TH20 v1.00a Steamless PE, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Entire original command Boss source-role coverage

| Whole original binary property | Fresh independent physical result |
| --- | --- |
| Original Bullet method | 0x0047DCF0, **12,140B, 2,490 original x86 instruction heads**, actual final RET |
| All physical original E8 calls | **210 / 210** individually decoded from signed 32-bit original native operands |
| Current native E8s targeting a configured strict canonical complete-method head | **203 / 210** (call occurrences, not 203 unique methods) |
| Physical original E8 sites still without a canonical whole-function source | **7 / 210**, seven distinct physical original target heads |
| Remaining original game-specific candidate children | **5 original method heads, 122B physical original code**; not yet accepted exact |
| Remaining compiler-runtime children | **2 original heads, 45B**, __security_check_cookie and __allshl; not game-authored |
| Original direct switch tables | Primary 34 entries, command-4 nested 8 entries, command-9 nested 11 entries |
| Real original PE HIGHLOW table fields | **53/53**, all destinations actual instruction boundaries within the same 12,140B code |
| Real original PE HIGHLOW fields inside 12,140B body | **38/38** |
| Original giant command Boss exact status | **NONEXACT, zero 12,140B parent credit** |

These numbers use original actual physical E8 call sites, not decompiler names or an assumption that a C++ declaration proves byte exactness. All currently configured native strict unit target heads are matched by actual original 32-bit destination values. Some previously source-present whole methods have multiple legitimate type-compatible aliases; a call counts **once** regardless of alias spelling. The graph currently has 1,203 canonical strict units and 1,201 source-present functions, covering library as well as game code; do not call all 203 E8 destinations game-authored.

The source-bound direct-call coverage has improved over the dated 188/210 canonical-role count in the earlier single-table native Boss research through the genuinely accepted seven new 199B Vector3/Float interpolation methods, exact 121B/20B Bullet command PMR vector library methods, 200B/196B/73B C++17 vector helpers and 46B/54B shared_ptr move code. The STL helpers are source-present but excluded from original game-authored byte credit. The remaining original function still has its separate source-absent body and must not be considered linker-complete.

## Exactly seven real original E8 gaps, no guessed game methods

| Original E8 site in entire Bullet Boss | Actual original target | Whole original native size | Original physical role |
| --- | --- | ---: | --- |
| 0x0047F3CC | **0x0044FCD0** | 37B | Game-specific Animation resource/link cleanup; uses real game global at 0x005C0028, E8-calls 0x0044FCA0, clears original link |
| 0x004807C1 | **0x0045E590** | 21B | Animation+0x499 byte value **0** |
| 0x004807B0 | **0x0045E5B0** | 21B | Animation+0x499 byte value **1** |
| 0x00480793 | **0x004865D0** | 21B | Animation+0x499 byte value **2** |
| 0x0047F671 | **0x00486330** | 22B | On actual Animation receiver, calls genuine Animation::interrupt(2) at 0x004388F0 |
| 0x00480C50 | **0x005429EE** | 14B | Compiler security-cookie check, not game-authored |
| 0x0047DDEC | **0x005432F0** | 31B | Compiler signed 64-bit shift helper __allshl, not game-authored |

All seven original target extents were independently disassembled to their real ends and have distinct physical start addresses. The three 21B setters are complete different original functions; the original x86 byte stores to Animation+0x499 with *literal* 0, 1 and 2, respectively. No semantic name beyond the observed original flag-byte operation is assumed; the byte lives within real AnimationBase::flags in the currently maintained class. They must be implemented as natural typed game methods before gaining any authored exact byte credit.

The 22B original helper genuinely pushes integer 2 and calls the independently previously whole-exact Animation::interrupt original 0x004388F0 at native E8 **0x0048633C**. The 37B original cleanup invokes the actual 0x0044FCA0 game helper at native E8 **0x0044FCE3**. Both observed targets and original root callers are independently decoded from the immutable original game binary. Neither is yet source-present/canonical. The two compiler helpers are **not** original game-authored logic even though they occur in the game executable; their whole original bodies are not silently credited as completed source.

The five game-specific candidates total **37 + 21 + 21 + 21 + 22 = 122 native bytes**, but none is counted exact yet. They are a concrete next native-source implementation target. Calling them original gameplay methods based on the observed byte writes does **not** establish a complete correct class name or historical whole-program linker ICF identity.

## Three independently original switch tables remain protected

The complete native main method has one primary indirect x86 dispatch at 0x0047DE4D with opcode index 0..33, one nested 8-way dispatch at 0x0047E8FF with integer selector 0..7, and one nested 11-way dispatch at 0x0047F48A with integer selector 0..10. Their original physical pointer tables are at:

- **0x00480C5C**, 34 actual 32-bit HIGHLOW pointers, 32 distinct native instruction targets; main IDs 5, 14 and 28 share a real no-op/tail entry.
- **0x00480CE4**, 8 actual HIGHLOW pointers, seven distinct native targets.
- **0x00480D04**, 11 actual HIGHLOW pointers, eleven distinct native targets.

The 53 words are contiguous in the actual PE from **0x00480C5C through 0x00480D2F**, and every physical field is present in its real original IMAGE_REL_BASED_HIGHLOW directory. The separate entire original 12,140B function body has another 38 such fields. This is complete original compiler/dispatch support, **not** a 212-byte extra original game function or a replacement for source-level 34-case C++.

## Reproducible exact native owner proof and scope

- **scripts/verify-bullet-command-call-coverage.py** — newly tracked self-contained locked-PE audit. Re-decodes all 12,140B/2,490 original i386 instructions and 210 E8s, reads the 1,203 current canonical source-unit physical heads, checks exactly 203 mapped and seven unmapped E8s, all seven original whole native child ends, three literal Animation flag values and actual nested interrupt/cleanup E8 destinations. Independently parses the original PE .reloc directory, all 53 native switch-table pointers and 38 body HIGHLOW fields.
- [Entire three-switch original native case CFG](BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md) — original 34+8+11 branch topology, 2,387 case-reachable native instructions and 204 original E8 in case branches plus six common setup/exit calls.
- [Real original 199B game interpolation children, complete 114-object closure](BULLET_199_INTERPOLATION_TANGENT_TIMER_EXACT.md) — natural C++ type/member source, seven whole strict units.
- [C++17 Bullet command PMR STL original helpers, 610B](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md) — five genuine original native STL helper bodies, **excluded** from game-authored byte totals.
- [Real original shared_ptr move constructor/helper, 100B](BULLET_SHARED_PTR_LEGACY_CTOR_100_LIBRARY_EXACT.md) — genuine whole original 46B/54B STM standard-library members, same original Bullet direct-call chain, **excluded** from game-authored byte totals.

The new original Boss audit changes no game logic source or exact unit. Original whole game-authored accepted coverage remains **556 complete original functions /186,645 disjoint game code bytes**. Source-present remains **1,201**, canonical strict units **1,203**. Original 12,140B command Boss is still NONEXACT; its 210 E8 source-role coverage is not whole-byte equality, no full cold replay was run and no game playability claim is made.
