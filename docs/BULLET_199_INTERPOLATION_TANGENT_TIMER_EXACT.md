# CORE/EXACT-746 — seven complete Bullet interpolation game methods, 199 native-exact bytes

**Seven previously missing complete TH20 game methods have now been restored in the actual shared Interpolation<T> source class, totaling 199 distinct original native code bytes.** All seven are directly called by the original 12,140-byte Bullet::run_extended_commands game Boss, which itself remains source-absent and NONEXACT.

Original Japanese TH20 v1.00a Steamless target: resources/th20.exe, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Real whole game functions

| Original typed method | Original physical head | Whole strict original bytes | Actual parent Bullet E8 |
| --- | --- | ---: | --- |
| Interpolation<Vector3>::set_tangent_start | 0x00439480 | **38/38**, 16 x86 | 0x004803E7 |
| Interpolation<Vector3>::set_tangent_end | 0x00438B20 | **38/38**, 16 x86 | 0x00480408 |
| Interpolation<float>::set_tangent_start | 0x00439460 | **24/24**, 11 x86 | 0x00480873 |
| Interpolation<float>::set_tangent_end | 0x00438B00 | **24/24**, 11 x86 | 0x004808A3 |
| Interpolation<Vector3>::reset_timer | 0x004396A0 | **25/25**, 12 x86 | 0x0048046C |
| Interpolation<float>::reset_timer | 0x004395B0 | **25/25**, 12 x86 | 0x00480903 |
| Interpolation<Vector3>::set_mode | 0x004394F0 | **25/25**, 11 x86 | 0x0048045B |
| **Seven separate original native code intervals** | | **199/199** | **Seven genuine original E8** |

Each complete original native function was disassembled through its genuine RET and strictly compared with the complete pinned MSVC i386 C++ output. The five tangent/mode setters have zero original relocations. Each 25-byte timer-reset method has exactly one REL32 field at +0x10, physically E8-calling independently exact Timer::operator=(int32_t) at 0x00423520. No duplicate physical code ranges are credited.

## Native game object ownership, not decompiler guesses

The original entire 12,140B Bullet command processor constructs its receiver from **Bullet+0x420** for genuine Interpolation<Vector3> and **Bullet+0x474** for Interpolation<float>:

- Vector3 tangent_start and tangent_end are original member offsets +0x18 and +0x24; mode is at +0x50 and Timer at +0x3C.
- Float tangent_start and tangent_end are at original +0x08 and +0x0C; Timer is at +0x14.

The natural C++ code now declares set_tangent_start, set_tangent_end and reset_timer in src/Interpolation.hpp and implements the same three generic typed methods in the existing src/Interpolation.cpp owner. The already genuine set_mode implementation remains shared. All member sizes and offsets remain unchanged. No fake wrapper, assembly, volatile, binary patch, invented pointer cast or duplicate source owner was introduced.

## The complete shared-header compiler dependency closure was protected

Changing these genuine public template declarations affects a real include closure. Before editing, the repository dependency analysis identified **114 actually affected canonical native source/object providers, containing 542 previously accepted strict original functions**. It did not run an unfiltered full-project replay of all 245 canonical objects.

All **114** affected objects were cold rebuilt serially under their actual pinned MSVC profiles. All **542/542** previously accepted native original whole functions still pass strict replay. The newly expanded Interpolation.cpp itself has **50/50 strict units**, its 43 prior units plus all seven new methods.

### Exactly 25 compiler-private original string symbol adjustments

The first scoped cold pass identified 15 existing providers with private MSVC dollar-SG source-string numeric-label changes. None showed a whole-function native code-byte regression.

Before changing the manifest, every one of **25 changed private string labels** across **17 previously strict units** was independently checked against the immutable original PE:

1. The entire nonrelocated original function bytes still match actual native MSVC output.
2. Actual COFF relocation offset and type are exactly the old accepted ones.
3. The original PE relocation directory still has the same genuine HIGHLOW field, with exactly the old independently anchored absolute target.
4. The new real COFF string's full NUL-terminated raw bytes equal the original PE string bytes at that same physical address.
5. All other original relocation symbols and targets are unchanged.

Only these independently original-PE-backed 25 private label names were updated in config/match-units.toml. All 15 affected providers were then separately cold rebuilt and retested strict exact. Original game bytes, field addresses/types/targets and all other function code were not changed to force a match.

The separate source-present but NONEXACT original 3,111-byte Player main was also recompiled. Its entire 3,114-byte/783-instruction candidate and its 67 REL32/37 DIR32 source field locations remained identical; only the private effect string label was renumbered. This **does not** make the 3,111B parent byte-exact.

## Reproducible native proof and bounded validation

- src/Interpolation.hpp and src/Interpolation.cpp — real maintained typed methods, unchanged class layout and original interpolation algorithms.
- scripts/verify-bullet-interpolation.py — tracked verifier reading the original immutable 12,140B Bullet parent, seven real E8 physical destinations and typed member receivers, the full seven original PE method bodies and their strict native receipts. Run through scripts/repo-python.
- .analysis/core740-Interpolation.hpp and core740-Interpolation.cpp — private natural template probes, full 38/38, 38/38, 24/24, 24/24, 25/25, 25/25 and 25/25 original bodies proven before public-header changes.
- .analysis/core741-interpolation-header-closure-before-edit.json — actual 114 object/542 old exact unit include closure and original compiled object hashes.
- .analysis/core741-scoped-interpolation-header-replay.py and its logs — all 114 dependent source objects individually rebuilt, never a global/unfiltered cold replay.
- .analysis/core743-interpolation-private-string-proof.py/json and its original-field-preserving manifest update — independent 25 original PE HIGHLOW/NUL string proofs, followed by 15 repaired native source replays.
- .analysis/core744-interpolation-closure-114-whole-exact.py/json — final **114/114** actual native object receipts and **542/542** previous strict function preservation, alongside the seven new exact units in the same owner.
- .analysis/core745-register-seven-original-Bullet-interpolators.py — original whole function and real typed source/relocation registration.
- Current canonical source-scoped Interpolation.cpp replay — **50/50 exact**, one native source object.

## Conservative original-code accounting

**Seven game-authored original complete functions add exactly 199 disjoint code bytes.** Authored exact coverage advances **549 functions /186,446 native bytes to 556 /186,645**. Canonical strict units rise **1,194 to 1,201** and source-present mappings **1,192 to 1,199**. All 542 existing functions in the actual changed-header closure were protected.

The full **12,140B Bullet command Boss**, separate 3,111B Player main frame and 555B Player movement remain **NONEXACT**. The separately recovered 72B Player movement table is read-only game data, not extra authored code. No full-game link/playability or unfiltered whole-project cold replay is claimed.
