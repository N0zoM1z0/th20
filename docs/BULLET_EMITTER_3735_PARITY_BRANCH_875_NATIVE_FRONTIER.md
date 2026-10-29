# CORE/RECON-587 — original odd-first shooting parity branch order recovered in entire 3,735B Bullet emitter

**Later CORE/RECON-605 whole original game-body correction:** The
3,735B Bullet emitter remains NONEXACT, but its actual original
[eight-value writable cancel-script lookup, independent per-use
BulletStyle indexing and correct native ShotMetadata/typed-radius
state](BULLET_EMITTER_3735_CANCEL_TABLE_AND_METADATA_928_FRONTIER.md)
have now been restored. A single real original `.data` table at
`0x005AEFF8` contains 32 exact bytes and contributes the formerly
missing original HIGHLOW field `+0xAFD`. The maintained source now
emits **3,742B/938 x86 instructions / 928 of 935 original mnemonic
heads aligned**, with all **60 native physical E8 targets in order**
and **69 DIR32** fields matching the original 45 code+24 switch
HIGHLOW *count only*. Dated 3,685B/930/911 scores below are
superseded; the complete parent field offsets, EH/SSE and two
switch labels remain NONEXACT. No original authored byte inflation,
no public-header or canonical-unit edit, no global cold replay.


**Later CORE/RECON-594 current whole native source:** The complete
3,735B original Bullet emitter remains **NONEXACT**, but original
floating-point source order has been further
[recovered from all six pi×2 SSE groups, sequential angle accumulations,
two speed locals and real metadata field re-reads](BULLET_EMITTER_3735_ORIGINAL_FLOAT_ORDER_911_FRONTIER.md).
The current maintained C++ generates **3,685B/930 x86 instructions,
911/935 original ordered mnemonic heads**, with **all 60/60 real
physical original E8 callee identities matching in ordinal order**.
Older historical 3,609B/914/831 and odd-first 875 checkpoint scores
below are superseded. Native E8 physical field sites, remaining
original SSE/stack/EH bytes and 13+11 jump tables still differ;
**no original parent-byte exact credit or global cold replay**.


Immutable Japanese TH20 v1.00a Steamless comparison target:
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The maintained entire 3,735B/935-instruction Bullet emitter boss at
`0x004818E0` now reconstructs the **original branch direction and source
order for both modes 0/1 and modes 9/10 parity-driven shot patterns**.
The previous full source was arithmetically plausible but used the
*reverse* odd/even conditional structure in both sites. The original
native loop directions were independently decoded, not read from
historical decompilation or a candidate's generated switch tables.

**Whole emitted candidate stays 3,609B/914 instructions, but actual
original mnemonic instruction alignment improves from 831/935 to
875/935.** Every **60/60 independently original native E8 physical
callee targets remains correct in original ordinal order**. The
original complete 3,735B/935 parent is still **NONEXACT**: E8 field
positions, stack lifetimes, original native compiler tables and the
remaining nonrelocated bytes do not all match. No original parent
body bytes are credited and this is not a full game link/runtime claim.

## Original immutable `E8`-independent x86 branch proof

The original ECL shooting pattern mode 0/1 at
`0x00481A83..0x00481ADA` loads the real signed 16-bit
`ShotParameters::count` at `ShotParameters+0x24`, masks the parity
bit then branches:

| Original native site | Actual instruction | Game/source meaning |
| --- | --- | --- |
| `0x00481A86` | `movsx eax, word ptr [edx+0x24]` | Load real signed `count` field |
| `0x00481A8A` | `and eax,1` | Test odd count |
| `0x00481A8D` | **`je 0x00481AAD`** | **Even count goes to SECOND branch**, odd count falls through first |
| `0x00481A8F` | `mov eax,[ebp+0x14]; add eax,1; cdq; sub eax,edx; sar eax,1` | First path uses signed `(column+1)/2` |
| `0x00481AAD` | `mov eax,[ebp+0x14]; cdq; sub eax,edx; sar eax,1` | Second path uses signed `column/2` and original `angle_step * 0.5` |

The previous source checked `if ((shot.count & 1) == 0)` with the
even branch first. Both paths produce the same intended angular values
for normal original game input, but the compiler emitted the **opposite
control-flow region order**. Natural C++ now checks
`if (shot.count & 1)` with the `(column+1)/2` path first, then the
even `(column/2 + half_step)` path. This is the real native source
branch order, not a fabricated branch, dummy variable or manual jump.

Modes 9/10 at original `0x00481D60..0x00481E5C` have exactly the
same *odd first* arrangement, this time using original signed
`ShotParameters::rows` at `ShotParameters+0x26`:

| Original native site | Actual instruction | Game/source meaning |
| --- | --- | --- |
| `0x00481D63` | `movsx eax, word ptr [edx+0x26]` | Load signed rows |
| `0x00481D67` | `and eax,1` | Test rows parity |
| `0x00481D6A` | **`je 0x00481DDE`** | **Even rows jump to second branch**, odd rows fall through |
| `0x00481D6C` | `mov eax,[ebp+0x18]; add eax,1; cdq; sub eax,edx; sar eax,1` | Odd-first uses signed `(row+1)/2`, original masked row-speed index `(row+1)&~1` |
| `0x00481DDE` | `mov eax,[ebp+0x18]; cdq; sub eax,edx; sar eax,1` | Even second uses signed `row/2`, adds native `angle_step * 0.5`, and uses `row&~1` for speed interpolation |

The maintained source now checks `if (shot.rows & 1)` with the real
odd path first, followed by the even path, preserving original
signed-half arithmetic and the separate `rows>1` interpolated-speed
guards. Nothing changes the input field widths, output format,
state-machine case IDs, natural C++ types, or original semantics.

## Entire pinned MSVC original instruction/codegen experiment

Four complete 3,735B-source alternatives were freshly compiled under
locked MSVC 19.44.35211 i386
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
Their whole emitted function extents, 914 instruction heads and 60
E8 calls remain the same; only actual native conditional order and
other branch/local lifetimes differ:

| Source condition order | Whole C++ bytes | x86 instructions | Original mnemonic heads aligned |
| --- | ---: | ---: | ---: |
| Old even-first in both modes | 3,609B | 914 | **831/935** |
| Odd-first only modes 0/1 | 3,609B | 914 | **842/935** |
| Odd-first only modes 9/10 | 3,609B | 914 | **864/935** |
| **Both original odd-first** | **3,609B** | **914** | **875/935** |

These are *whole-function* Capstone sequential comparisons of genuine
full-body native instructions, not sliced block counts. Independent
original physical E8 verification was rerun **after** promoting the
new source into maintained `src/BulletEmitter.cpp`:
`.analysis/core587-emitter-parity-maintained-60-E8-identity.json`.
It reconfirms **60 known original E8 callee target identities matched
by ordinal position, zero incorrect destinations, zero unmapped
aliases**, with no added code credit for the previously proven folded
physical 8B std::move, 16B Context getter or 24B BulletColor source.

Original source and whole compiler probe evidence:
`.analysis/core585-emitter-parity-branch-results.json`,
`.analysis/core586-emitter-parity-maintained-score.json`,
`.analysis/core586-emitter-main-parity-source-build.log`, and
`.analysis/core587-emitter-parity-60-native-target-proof.log`.
The earlier whole [60-E8 call identity audit](BULLET_EMITTER_60_ORIGINAL_E8_CALL_IDENTITY.md)
remains correct on physical original targets, but its historical
**831/935** instruction score is superseded by the current
**875/935** score.

## Scope, exactness and next original frontier

Only `src/BulletEmitter.cpp`, which has **zero configured existing
canonical native exact units**, was modified. All existing exact
sources, headers, canonical compiler profile receipts, source
manifests and original target bytes are untouched. The entire source
was recompiled as one native pinned C++ provider and independently
compared against all 935 immutable original native instructions.
**No global cold replay** of unrelated native units is appropriate or
was executed. The complete 3,735B parent still differs in 126 bytes
of *overall length*, 21 emitted instruction heads and multiple
original machine code fields, even though all 60 original E8
physical callee identities and order now match. The original 13+11
switch tables, EH/shared_ptr lifetimes and other stack/branch
instruction bytes remain open. Other large Player 555B/3,111B,
Animation VM 39,470B and Enemy ECL 41,967B roots also remain open.

Game-authored original strict exact coverage is **unchanged:
498 whole originals / 175,709 distinct native game bytes**;
1,184 existing canonical units, 1,183 source-present mappings and
243 existing compiled providers are untouched.
