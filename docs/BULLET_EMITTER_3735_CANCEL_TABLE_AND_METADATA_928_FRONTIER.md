# CORE/RECON-605 — original Bullet cancel-script data table, typed palette lookups and true game-state fields in the whole 3,735B emitter

**Later CORE/RECON-615 current whole native source:** The original
Bullet emitter's **two real `&0x0000FFFE` 6B masks** and direct
`Player::position_ref()` return-reference passing are now restored
in [the full C++ game method](BULLET_EMITTER_3735_NATIVE_ROW_MASK_AND_PLAYER_DIRECT_ABI.md).
Whole candidate **3,736B/936 instructions**, immutable native original
3,735B/935; correct **60/60 original E8 physical callee identities**
in order and original/candidate whole code+table span **3,832B** each,
but **49 source E8 physical sites +1B** after a real extra C++ NOP
at method +0x112, along with other original stack/EH/switch-byte
mismatches. Old 3,742B/938 score below is historical. This original
parent remains **NONEXACT**, no authored byte credit or full cold
replay.


Target: immutable Japanese TH20 v1.00a Steamless
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The complete original `BulletController::emit()` physical game boss
at `0x004818E0` remains NONEXACT.** The original body comprises
**3,735B / 935 i386 instructions**, followed by genuine compiler
alignment and two jump tables (13 plus 11 entries) in its **3,832B
whole original contribution**. We recovered a previously missing,
**real original 32-byte writable cancel-script table**, eliminated a
wrongly cached `BulletStyle&`, fixed two actual `ShotMetadata` field
offsets and a missing zero, and recovered original float-radius
assignment order. These are observable game-behavior corrections, not
compiler padding or changes to unrelated class layouts.

The pinned MSVC 19.44.35211 full-source candidate now emits
**3,742B / 938 x86 instructions**, with **928/935 original mnemonic
heads aligned in native order**, **60/60 actual original physical
E8 callees in the same ordinal order**, and **69 COFF DIR32 fields**
matching the original whole contribution's **69 genuine PE HIGHLOW
fields by count**. It is not enough: the E8/DIR32 **field offsets**,
EH/stack/SSE bytes and original switch-label destinations remain
unverified. No part of the 3,735B parent enters authored-exact credit.

## The original eight-word `case 1` cancel-script lookup was missing

The original x86 at **emitter-relative `+0xAFA`** has a real `mov`
reading `dword ptr [eax*4 + 0x005AEFF8]`, with `eax` holding the
32-bit `ShotParameters.color` value. The **HIGHLOW field inside that
instruction begins at `+0xAFD`**. Parsing the locked executable's
actual PE `.reloc` section independently confirms the original
absolute destination **`0x005AEFF8`**, not a guessed table symbol.

That target is in the original `.data` section. Directly reading the
original 32 bytes as eight little-endian signed 32-bit values yields:

| Color index | Original script ID |
| --- | ---: |
| 0 | 6 |
| 1 | 10 |
| 2 | 14 |
| 3 | 18 |
| 4 | 22 |
| 5 | 26 |
| 6 | 30 |
| 7 | 36 |

The next original data beginning at **`0x005AF018`** is a distinct
packed-color palette, not an extension of this eight-entry table.
The original entire eight-word byte sequence has SHA-256
`04debfc344669250b4d3753fe8b38e399299d880ee6af2ce6dace7964a8b4698`.

The previously maintained `case 1` wrote
`bullet->cancel_script = int(shot.color)`: that was an actual logic
error (e.g. index 0 must select script **6**, not script 0). Natural
typed maintained C++ now defines **exactly eight original data words**
in its one changed source provider:

```cpp
std::int32_t bullet_cancel_scripts_by_color[8] = {
    6, 10, 14, 18, 22, 26, 30, 36
};
// In the real case 1 of the cancel-style switch:
bullet->cancel_script = bullet_cancel_scripts_by_color[shot.color];
```

Fresh MSVC emits a **single writable 32-byte `.data` section** with
`?bullet_cancel_scripts_by_color@th20@@3PAHA` at offset zero.
Independent PE versus COFF section-content comparison confirms
**all 32/32 original native data bytes identical**. The full emitter
C++ now has a real DIR32 for that symbol; the former candidate had
no equivalent field. The true original text's **45 PE HIGHLOW**
fields plus **24 additional original switch-label HIGHLOW** fields
make **69**, whereas the former candidate had **68 COFF DIR32**
fields. With this genuinely sourced table, it emits **69**, matching
the complete original reloc *count*. The precise offsets still
require further whole-native work; this is not a claim of complete
relocation equality or original data linkage address.

## Original `BulletStyle` indexing is not one cached C++ reference

The old code cached `BulletStyle& style = bullet_styles[shot.type]`
and reused that reference through child script, color/cancel,
render-group and bullet-size paths. The original x86 instead
**recomputes the native stride `0x158`** from the current shot type
for each independent style access. Real original `imul` instructions
are visible at method offsets `+0xA44`, `+0xA90`, `+0xAB9`, `+0xC35`,
and the original actual BulletStyle array begins at `0x005C06A8`.
Removing the cached reference restores those real independent loads,
source-evaluation order and global absolute references. It is not
an artificial style-index side effect.

There is a distinct original type owner **inside cancel mode 6**.
The two original `movsx` instructions at **`+0xB48` and `+0xB74`**
read a **signed 16-bit Bullet+`0x4C` type**, *not* a freshly loaded
32-bit `ShotParameters.type`, before indexing the style's five-word
color record. The original separately uses the full 32-bit
`ShotParameters.color` index (`+0xB55/+0xB81`, stride `0x14`).
The maintained C++ therefore uses
`bullet_styles[static_cast<std::int16_t>(bullet->field_4c)]`
for these **two** palette source reads, but retains
`bullet_styles[shot.type]` for the other independent style uses.
This matches the actual original field widths rather than using a
32-bit cast everywhere merely because it yields a shorter candidate.

## Two genuine metadata offset bugs and an omitted state reset

The original emitter writes the real Bullet state in this order:

- At `+0xC47..+0xC50`, original
  **`Bullet+0x40 = ShotMetadata+0x40`**. Maintained source now uses
  `bullet->field_40 = metadata_source->alternate_sound`; it formerly
  read the *different* `ShotMetadata+0x44` field.
- At `+0xCA1`, original writes **`Bullet+0x3C = 0`**. This real
  original initialization was completely omitted in the previous
  C++ source; the maintained method now clears `bullet->field_3c`.
- At `+0xCAB..+0xCB1`, original writes the **full 32-bit**
  **`Bullet+0x38 = ShotMetadata+0x44`**. The older source incorrectly
  read **signed byte** `ShotMetadata+0x48` and assigned it to this
  game command index. Maintained C++ now reads `field_44`.

These original member addresses and widths were independently decoded
from native i386 load/store operands and do **not** require changing
`ShotMetadata.hpp` or `Bullet.hpp`. The source also removes a second
unnecessary 32-bit switch-mode temporary: original dispatch reads
`static_cast<std::uint16_t>(metadata_source->field_38)` directly,
whereas older C++ introduced a named intermediate plus a compiler
switch-local copy.

## Radius calculation: real x87 return stored once, then Y and X

After its native `bullet_radius` E8, the original method uses x87
`fstp` to store one float radius at original stack `[EBP-0x54]`,
then separately `movss` copies it to **Bullet+`0x80` (Y)** at
`+0xC71/+0xC76`, and finally to **Bullet+`0x7C` (X)** at
`+0xC81/+0xC86`. Earlier C++ used X first and copied X to Y via
integer `mov` rather than retaining the original float value.
The current natural source uses:

```cpp
float native_radius = bullet_radius(static_cast<int>(shot.type));
bullet->size.y = native_radius;
bullet->size.x = native_radius;
```

This models the actual original one-value/two-typed-float-store
lifetime, rather than adding a meaningless local to force machine
padding.

## Whole-function compiler experiments and immutable original proof

Complete ordinary C++20 i386 source variants (not isolated snippets)
under the pinned `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` show:

| Entire original Bullet emitter source candidate | C++ bytes | x86 heads | Ordered original mnemonic heads | DIR32 fields |
| --- | ---: | ---: | ---: | ---: |
| Before this checkpoint | 3,685 | 930 | 911/935 | 62 |
| True metadata+`0x40/+0x44`, `Bullet+0x3C` clear and one stored radius | 3,711 | 933 | 918/935 | 62 |
| Uncached independent style loads, direct original 16-bit switch | 3,727 | **935** | 925/935 | 68 |
| Signed 16-bit actual Bullet type for two cancel-color lookups | 3,736 | 937 | 927/935 | 68 |
| Also original eight-value writable cancel script table | **3,742** | **938** | **928/935** | **69** |

In all final candidates, E8 count remains **60**. Independent
original whole native E8 call comparison on the **fresh maintained
`src/BulletEmitter.cpp` object** reconfirms **60/60 actual original
physical callee targets in the same ordinal order, zero incorrect,
zero unresolved**. This is a physical *callee identity* proof only;
compiled E8 offsets are still not those in the original game.

The independently parsed original `.reloc` field/array proof reads
true locked PE `.data` and original switch-table relocations, verifies
actual original x86 signed type loads, then independently reads the
compiled candidate `.data` section and COFF symbol payload. It does
not manufacture linker target addresses from C++ candidate fields.
The original entire 3,735B/935-instruction body remains separately
available for comparison. Detailed ignored private reproducible
artifacts:

- `.analysis/core596-emitter-real-metadata-radius-probes.json` — whole-body metadata/state/radius variants.
- `.analysis/core598-emitter-style-lifetime-results.json` — direct original style index and switch-source lifetime variants.
- `.analysis/core599-emitter-case6-native-bullet-type-results.json` — real signed 16-bit stored Bullet type variants.
- `.analysis/core601-emitter-original-color-map-variants.json` — eight full emitters with writable/const original table types.
- `.analysis/core602-emitter-928-mismatch-regions.json` — still unmatched actual native x86 opcode regions.
- `.analysis/core605-emitter-maintained-original-color-pe-proof.json` — original `.data` 32B and independently real 45+24 PE HIGHLOW plus 69 COFF DIR32 proof, **from maintained source object**.
- `.analysis/core605-emitter-maintained-60-E8-identity.json` — all original E8 physical callee identities from the **maintained** source, 60/60 matching.
- `build/core604-probes/BulletEmitter-maintained.obj` — fresh complete C++ object and compiler receipt under pinned local flags.

## Affected-only validation and remaining big game bosses

**Only `src/BulletEmitter.cpp` is modified** in production. Its added
original data array is private to this game source's translation unit,
so there is no shared-header ABI change, no change to previously exact
source units, and no need to fabricate a complete Bullet class or
`ShotMetadata` layout. The entire modified source was freshly cold
compiled; it has **zero previously accepted canonical exact original
units**. Running 1,184 other units through a global cold replay
would not validate the still-NONEXACT parent and was not performed.
Immutable PE verification, whole-source C++ compilation, original
physical E8/DIR32 audits, match-ledger validation, Markdown-link
checks and Git diff checks are the appropriate scoped evidence.

The complete original **3,735B Bullet emitter remains NONEXACT**;
its candidate is actually **seven bytes and three net instructions
longer** now, even though original field identity/number and real
gameplay have improved. The unproven original E8 offsets,
switch-table branch addresses, MSVC EH/SEH and SSE stack-lifetime
bytes are the next hard frontier. Also open independently are
12,140B Bullet dispatch, 41,967B Enemy ECL dispatch, 39,470B
Animation VM and 3,111B Player frame/555B movement.

Accepted original *game-authored* exact coverage remains **498 whole
functions / 175,709 disjoint game bytes**, with **1,184 configured
canonical strict native units, 1,183 source-present functions and
243 MSVC object providers**. Neither the new eight-word original
*data* table nor the still-NONEXACT 3,735B parent is falsely
counted as an additional exact original game function.
