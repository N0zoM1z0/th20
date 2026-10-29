# CORE/RECON-724 — genuine shared Player float 128: recover two original physical relocation identities in entire 555B movement source

**Player::apply_move_delta remains NONEXACT: original 555B/135 i386; maintained full MSVC source 561B/136 i386.** The original Player movement's last two world-coordinate divisions use the **same, existing game-owned native global float at physical address `0x0056CD98`** as the two previous maximum-Y bound calculations. The maintained source previously expressed these two denominators as `128.0f`, which made MSVC emit its unnamed private floating literal `__real@43000000`, rather than the independently original-attested `native_128` game symbol. Replacing only these two expressions with the already genuinely declared `native_128` preserves all game values and compiled machine code while restoring their original global data owner.

Locked Japanese TH20 v1.00a Steamless target: SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## Native independently original physical data provenance

The complete immutable original physical game method at `0x004FFA10` performs its float Y bound using the file-backed native constant float at `0x0056CD98` (actual binary bytes `00 00 00 43`, IEEE 754 value `128.0f`). The two trailing original `DIVSS` instructions at native function offsets **`+0x1DA` (world X)** and **`+0x205` (world Y)** both read `0x0056CD98` as a real PE HIGHLOW relocation. These are separate native original address fields for the **same** original game constant, not inferred from another program's compiler symbols.

Furthermore, **nine other independent, previously complete original native-exact Player methods' relocation fields** already identify that same physical original target as `?native_128@th20@@3MB`, including accepted Player initial motion/speed settings and `IntPoint::to_vector3` conversion. The maintained 3,111B Player main frame already uses the same original `native_128` for actual signed fixedpoint accumulation. Its original value is not an independent anonymous source constant for these final two divides.

## Native whole-method compiler proof and precise effect of the edit

A clean private pinned MSVC i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc` source probe changed exactly the two original full source expressions, followed by a fresh actual production full-source compile of `src/PlayerMovement.cpp`. Both actual COFF outputs were independently decoded:

| Entire body audit | Before source correction | Updated maintained source |
| --- | --- | --- |
| Full compiled native code | **561B /136 x86** | **561B /136 x86** |
| All native code bytes (including original real relocation field placeholder bytes) | Original nonexact candidate | **Identical to pre-edit, 561/561 code bytes** |
| Total original-source COFF relocation fields | 17 REL32 /10 DIR32 | **17 REL32 /10 DIR32** |
| World X denominator, COFF immediate offset `+0x1E4` | Private literal `__real@43000000` | **`?native_128@th20@@3MB`** |
| World Y denominator, COFF immediate offset `+0x20F` | Private literal `__real@43000000` | **`?native_128@th20@@3MB`** |
| Every other COFF relocation source symbol and every physical field offset/type | Original candidate | **Identical** |
| Complete original target native exact | **NO** | **NO** |

This repairs a **real file-backed global symbol/identity** in a game-owned medium-sized full function, without inventing separate magic constant storage, changing behavior or falsely claiming more native code coverage. The C++ implementation continues to perform both floating-clock motion updates, playfield clamps and 128-division world coordinate projection.

The remaining blocker is unaffected: the original computes `cvttss2si esi,xmm0` after the second upper Y bound multiplication, whereas MSVC still emits an extra six-byte `movss [ebp-0x30],xmm0` before `cvttss2si esi,[ebp-0x30]`. The whole 555B parent is **NONEXACT**, and its original 17 E8/10 PE HIGHLOW source roles still require full offset/byte proof before strict acceptance. Do not add artificial compiler-local reads, volatile or assembly to hide the spill.

Reproducible evidence:

- `.analysis/core723-player-movement-real-constant.cpp` — private same-game source probe with only these two typed native-global denominators.
- `build/core723-probes/PlayerMovement.obj` — MSVC compiled private complete function and actual 27-field COFF relocation table.
- `build/core720-probes/PlayerMovement-precise_nosdl.obj` — pre-edit complete-function COFF reference.
- `build/core724-probes/PlayerMovement.obj` — new maintained actual source whole native MSVC compilation.
- `.analysis/core724-player-movement-real-128-native-relocation-proof.json` — asserts 561/561 raw C++ bytes equal, the *only* two changed symbol identities at original typed relocation fields, native immutable `0x0056CD98` and nine separate accepted original game native relocation sites.

**Affected canonical strict native source units: zero.** The only edited file is the noncanonical whole game-owned `src/PlayerMovement.cpp`, previously absent from all 1,187 canonical match-unit providers. Full Player movement alone was compiled and structurally compared; original PE, shared headers, accepted strict receipts and game exact ledger were unchanged. No global cold replay was run. Accepted game-authored coverage remains **537 complete functions /184,665 disjoint original native code bytes**.
