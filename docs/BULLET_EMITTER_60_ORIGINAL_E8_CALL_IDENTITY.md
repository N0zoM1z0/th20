# CORE/RECON-583 — all 60 original Bullet emitter E8 callee identities now agree in native order; whole boss still NONEXACT

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


**Later CORE/RECON-587 original parity control-flow correction:** Both
native game shot-pattern parity checks in the 3,735B emitter use **odd
branch first**, with the even branch reached by original
`+0x1AD je +0x1CD` (count) and `+0x48A je +0x4FE` (rows).
Restoring that natural C++ branch ordering improves complete original
x86 mnemonic alignment **831/935 → 875/935**, while current C++
remains **3,609B/914 instructions**, still original call graph
**60/60 E8 physical callees matching in ordinal order**. [Immutable
original two-branch and complete native C++ proof](BULLET_EMITTER_3735_PARITY_BRANCH_875_NATIVE_FRONTIER.md).
Earlier scores and reversed branch source notes below are historical;
the entire 3,735B parent is still NONEXACT with no new authored
original bytes, global cold replay or linked game claim.


Target: immutable Japanese TH20 v1.00a Steamless game
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The complete original `BulletController::emit()` at
`0x004818E0..0x00482776` contains 3,735 bytes, 935 native i386
instructions and exactly 60 genuine `E8` direct calls. After
recovering the original legacy STL move protocol and merging two
separate error conditions into the original single Animation
interrupt branch, the entire maintained `src/BulletEmitter.cpp`
now generates exactly 60 real COFF E8 call fields whose **60
physical original callee destinations match the immutable game's
60 original E8 targets in the exact same ordinal order**.** This
is the first complete independently audited original game-call chain
for this large Bullet emitter boss, **not** an acceptance of the
entire original code body or a claim that generated relocation
field sites now match.

## Original complete call-identity proof, not a numeric E8 count

An independent original `.text` decoder walks the entire 3,735B
original physical method, decoding all 935 x86 instructions to its
actual native return. It recovers **every original E8** from the
immutable original opcode's signed 32-bit displacement, yielding the
**60 original native absolute destinations** and original site
addresses. The fresh pinned real C++ compiler object's COFF relocation
list provides the candidate's ordered `REL32` symbol names.

For each of the 60 positions, the candidate's actual decorated
COFF source symbol was independently resolved to the **physical
original native address** based on existing canonical original
manifests or separately original-PE-attested whole folded source
identities. The original PE targets are **not** inferred or solved
from compiled fields. The full ordinal-by-ordinal proof is preserved
in `.analysis/core583-emitter-maintained-60-whole-original-call-identity.json`.
It reports **60/60 known original physical callees agree, zero wrong
known targets, zero unresolved aliases**. Important independently
attested folded cases include:

- Original `0x0040C300` is one **16B physical code body** shared by
  the actual `Context::bullet_controller()`, `IntrusiveLink<Bullet>::node_value()`
  and other four-byte pointer getters. Actual existing `Context.obj`
  emits the same 16/16 original bytes; it is **one native address**, not
  separate authored exact credit for each source role.
- Original `0x0045D650` is the **24B** original `PackedColor`/`BulletColor`
  integer assignment, both typed C++ whole contributions identical
  to that native physical head. The second typed name gets **zero
  extra original authored byte credit**.
- Original `0x0040B280` is the physical **8B** noninlined legacy
  `std::move` helper, now rebuilt from a genuine typed source; the
  same 8B physical address already had a canonical folded
  `std::addressof` role, with **no duplicate native credit**.
- Original `0x005429EE` is the MSVC security-cookie checker already
  the independently original native target in **134 separately
  configured complete native canonical units**. Its checked
  original address resolves from the real compiler's
  `@__security_check_cookie@4` COFF role, not a guessed symbol target.
- The original **39,470B `Animation::update`** and other giant
  runtime owners are identified as physical *callees*, not newly
  reconstructed exact bodies. Matching their E8 identities in this
  caller does not prove their implementations.

Representative crucial original sites and physical destinations:

| Original E8 site | Original physical destination | Real typed C++ source role |
| --- | --- | --- |
| `0x00481989` | `0x0040B280` | Legacy noninlined old `std::move` of `shared_ptr<EtamaArgInf>&` |
| `0x0048199B` | `0x0047C530` | Independently whole **63B native-exact** legacy shared_ptr move assignment |
| `0x00481F45` | `0x00455FB0` | Game `geometry::norm_xy(a,b)`, not CRT `std::hypot` |
| `0x00481F66` | `0x00459280` | Game `scalar_math::arctangent(b,a)`, not CRT `std::atan2` |
| `0x00481FFA` | `0x0047A630` | Game `scalar_math::absolute(scalar_math::sine(...))` |
| `0x00482252` | `0x004299D0` | Actual `Animation::reset` after pool allocation |
| `0x00482297` | `0x004856C0` | Already whole-exact **18B** Bullet style type-to-script getter |
| `0x00482310` | `0x0040C300` | Context's selected BulletController pointer before child Animation file access |
| `0x00482390` and `0x00482481` | `0x0045D650` | Two genuinely typed physically folded 24B Bullet color assignments |
| `0x004825C4`, `0x004825EC`, `0x0048261F` | `0x0047C6C0` | Three independent opcode-1 `pmr::vector<BulletCommand>::operator[]` calls |
| `0x00482681` | `0x00429740` | `Vector3::operator-=` on the native first-command velocity adjustment |
| `0x004826AC` | `0x004388F0` | **One** common false-case `Animation::interrupt(2)` call |
| `0x004826C0` | `0x0042B5D0` | Still NONEXACT giant original Animation VM, invoked at correct original physical head |
| `0x0048276C` | `0x005429EE` | Original MSVC security-cookie checker |

The entire other 60-E8 original target table is in the private
JSON above, with unchanged original site addresses, original PE
callee destinations, candidate field offset, exact COFF symbol,
canonical/folded physical target and a per-ordinal match result.

## A real source-level common error-path and old STL lifetime fix

The original emitter handles an incoming `BulletCommand` vector at
`Bullet+0x98` through the authentic metadata owner and its indexed
`commands`. Original native branches **`0x004825A5 jae 0x00482698`**
(index out of bounds) and **`0x004825CD jne 0x00482698`**
(command opcode not 1) **both jump to the SAME original block**.
Only one `Animation::interrupt(2)` E8 at native
`0x004826AC` handles either condition. The prior C++ had nested
`if ... else interrupt(2)` and a separate outer `else interrupt(2)`,
so it emitted **two separate failure E8 calls**, contrary to the
original native control flow. Natural C++ now uses one short-circuit
condition:

```cpp
if (bullet->field_38 < metadata_source->commands.size() &&
    metadata_source->commands[bullet->field_38].opcode == 1) {
    // Real original opcode-1 path: two further independent indexed
    // event reads, both sign-extended from the 16-bit +0x10 field.
    ...
} else {
    bullet->animation->interrupt(2);
}
```

This naturally restores the one true common error-path E8, without
emitting a fake branch trampoline, hand-written code bytes or a
compiler-only dummy. The original successful opcode-1 path still
retains **three** `std::pmr::vector<BulletCommand>::operator[]` calls
and the two immutable native signed-16-bit `movsx` event-field reads
at `0x004825F1` and `0x00482624`.

The other original E8 previously missing came from the old original
STL operation on the by-value `std::shared_ptr<EtamaArgInf>` descriptor.
The independent full native original **63B move-assignment** and
**8B `std::move`** were recovered in
[`CORE/STL-577`](SHOT_SHARED_PTR_LEGACY_MOVE_63_EXACT_COMPILER_SUPPORT.md)
as an isolated typed MSVC compatibility implementation. The emitter's
real source now includes **type-specific declarations**, not a
second function definition or unsafe raw pointer cast, for these
two specialized old STL methods. This causes the emitter to generate
the **real separate `std::move` E8** before the original
move-assignment E8. The definitions remain in their separate,
**fully strict-exact** `src/ShotSharedPtrMoveLegacy.cpp` translation
unit, compiled with its distinct source-local `/GS- /sdl-` recipe.
Emitter's own pinned `/Od /GS /sdl` profile is unchanged. This is a
locked historical toolchain compatibility overlay, **not** a claim of
portable C++ standard-library customization/ODR safety or a
full-program linker selection proof.

## Honest entire original vs emitted C++ score

| Whole code / call measure | Before CORE/RECON-583 | Corrected maintained C++ | Immutable original |
| --- | ---: | ---: | ---: |
| Entire emitter game code bytes | 3,628B | **3,609B** | 3,735B |
| Decoded x86 instruction heads | 919 | **914** | 935 |
| Native mnemonic heads aligned in original order | 828 | **831** | 935 |
| E8 source call fields | 60 | **60** | 60 |
| Real original physical E8 targets aligned by ordinal | Not all (missing legacy move; duplicated fallback) | **60/60 correct** | 60 |

The source is **still NONEXACT**: the current 3,609B/914-instruction
whole native C++ object is **126B and 21 instructions short** of the
original complete 3,735B/935. Individual original E8 **field
positions and displacements** still differ, as do stack local
lifetimes, compiler EH/control-flow, nonrelocated instruction bytes
and original 13+11 switch-label/jump-table targets. The two
independently exact 63B and 8B library support children do not
reconcile those remaining original game bytes by themselves.
The original 12,140B Bullet command dispatcher is also separately
NONEXACT. No parent exact-body match row is added to the ledger.

## Focused build and reproducibility

Only `src/BulletEmitter.cpp` was changed for this checkpoint. No
public header, existing exact source, target executable, match unit,
existing canonical compiler recipe or original authored match range
was touched. The complete **modified source** was freshly compiled
with locked MSVC 19.44.35211 i386 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`; resulting ordinary COFF
`build/core582-probes/BulletEmitter.obj` provides every source E8
symbol for the original/native comparison. The separate previously
exact legacy STL library provider retains its already accepted
63/63B strict recipe and was not changed.

This source has **no previously accepted canonical exact units**
because the entire original 3,735B parent is not native exact.
Therefore no cold replay of the other 1,184 native strict units
was needed or run. Immutable target verification, source compilation,
full native E8 identity proof, conservative tracking validation,
progress checks, and `git diff --check` are the appropriate
**affected-only** validations.

Private reproducible evidence:

- `.analysis/core579-emitter-branch-legacy-results.json` — three full-source original branch/STL forwarding combinations.
- `.analysis/core582-emitter-current-main-source-score.json` — current whole 3,609B/914/831 C++ compiler output and 60 E8 count.
- `.analysis/core583-emitter-maintained-60-whole-original-call-identity.json` — complete independently original-PE-derived 60/60 call-by-call physical identity table.
- `.analysis/core583-emitter-60-native-call-identity.log` — strict visible original target alignment proof output.
- `docs/SHOT_SHARED_PTR_LEGACY_MOVE_63_EXACT_COMPILER_SUPPORT.md` — independent 63B/8B original library support strict source proof.

**Game-authored original exact coverage remains 498 whole functions /
175,709 disjoint native bytes**; original canonical strict units stay
**1,184**, source-present mappings **1,183** and MSVC provider
objects **243**. This checkpoint advances one of the most difficult
whole game bosses through its **complete original E8 call graph**,
not through prematurely declaring its whole original body identical
or promising a fully linked playable game.
