# CORE/RECON-594 — recover original floating-point evaluation, branch order and speed lifetimes in the entire 3,735B Bullet emitter

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


Immutable source of truth: Japanese TH20 v1.00a Steamless
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The complete original game-owned `BulletController::emit()` at
`0x004818E0` is still NONEXACT.** Its entire original 3,735B code body
has 935 physical i386 instructions and 60 independently original E8
calls. This checkpoint restores a substantial fraction of the
**remaining original floating-point evaluation order** in the
maintained full `src/BulletEmitter.cpp`. The pinned locked MSVC i386
whole-source compiler candidate now emits **3,685B / 930 x86
instructions, 911/935 original instruction mnemonic kinds aligned in
order, with all 60 original physical E8 callee destinations still
matching by exact call ordinal**. This is a major native whole-boss
codegen improvement over prior **3,609B / 914 / 831**, but **not**
a 3,735/3,735-byte match, not a whole-program game link, and
not new game-authored exact byte credit.

## Why the previous C++ branch order was wrong

Previous source used two short-circuit parity branches with the *even*
case written first, then the *odd* case. The actual original native
game has **odd branches as the fall-through body**:

- Original method `+0x1AA` tests `shot.count & 1`, and original `je`
  at `+0x1AD` skips odd-body instructions to the separate **even**
  body at `+0x1CD`. Thus original shot modes **0/1** first compute
  `float((column+1)/2) * angle_step` (odd), and only then the
  even computation `float(column/2)*angle_step + angle_step*half`.
- Original method `+0x487` tests `shot.rows & 1` and `je`
  at `+0x48A` jumps past the full odd-body to the **even**
  speed/angle branch at `+0x4FE`. Original modes **9/10** first
  compute `((row+1)/2)` and the corresponding original stepped
  speed, not the even branch first.

Both source variants are usually arithmetically equivalent, but
under the original MSVC `/Od`, the branch-first source shape changes
the **whole physical switch-case code layout**. The fresh complete
source comparison isolated these two changes: original ordered
instruction mnemonic alignment improved **831 → 842** from odd-first
mode 0/1, **831 → 864** from odd-first mode 9/10, and **831 →
875/935** when both genuine source orderings are restored together.
No original compiler bytes, target fields or switch labels were
patched manually.

## Original angle accumulation uses distinct float steps and pi-times-two first

The earlier draft combined many original shot-angle calculations into
a single long floating expression. The actual original game's x86
makes the source-visible evaluation order explicit:

- Modes **2/3**: native `+0x28B` adds the column/(count) fraction to
  the *current* `heading` and writes it back; only then does native
  `+0x295..+0x2AA` compute `row*angle_step + shot.angle + heading`.
  The old C++ computed row and shot angle before the fraction.
- Modes **4/5**: original `+0x2D3` computes the independent
  `pi/count` component and adds it to heading; original
  `+0x2EE..+0x316` computes and adds the column/(count) fraction;
  only then original `+0x31B..+0x330` computes the row/shot angle.
  The old source grouped the three operands in the reverse
  cumulative evaluation order.
- Mode **7**: original `+0x3A3..+0x3CB` computes and adds the
  column fraction to heading first, followed by row/shot angle
  operations at `+0x3D0..+0x3E5`. The old expression combined
  row and shot angle first and then added the column fraction.

These are all **ordinary natural C++ scalar operations**, no
synthetic local or fabricated side effect. Although algebraically
associative over real numbers, IEEE single-precision floating point
can round differently depending on order. Reproducing original
steps is therefore required for **both byte-exact compilation and
original gameplay semantics**.

Moreover, each of the **six** real angle-pattern expressions at
original method-relative offsets `+0x268`, `+0x2EE`, `+0x3A3`,
`+0x458`, `+0x5CD` and `+0x6AD` uses the **same original SSE order**:

```asm
movss xmm1, dword ptr [0x0056E0F0] ; native pi
mulss xmm1, dword ptr [0x0056C8D0] ; native two
mulss xmm0, xmm1                   ; float(column) * (pi*two)
```

The former source instead had `(float(column) * native_pi) * native_two`
left-associativity, which generated two consecutive `mulss xmm0`
instructions, changed original operand evaluation and IEEE rounding.
The current typed source consistently uses
`float(column) * (native_pi * native_two)` in **all six real original
modes**. On the native-source candidate where all other corrections
are held constant, each independently grouped pattern contributes
one additional original matched instruction, and six such grouping
changes improve alignment **905 → 911** while preserving all 60
native game calls.

## Two real speed locals and two original unsigned metadata reads

The actual original method code at `+0x169` stores an incoming
computed base speed in local `[ebp-0x38]`, reloads it from that stack
slot at `+0x16E`, and stores a **separate mutable current-pattern
speed** local `[ebp-0x2C]` at `+0x173`, before initializing the
Bullet initial speed field. The previous C++ reused one source local
for both, losing two real original /Od stack instructions. The
maintained source now preserves both roles naturally:

```cpp
float base_speed;
if (shot.rows > 1)
    base_speed = /* original stepped-speed calculation */;
else
    base_speed = shot.speed;
float speed = base_speed;
bullet->field_24 = speed;
```

This is not a fake byte-preservation variable: a distinct **base
velocity** and a **mutable pattern velocity** have direct original
stack evidence and different lifetimes as later modes change speed.

The original also does **not** reuse the switch's widened
`metadata_source->field_38` local for later mode tests. Native
`+0x223` reloads the actual metadata owner, `+0x226` uses
`movzx word ptr [edx+0x38]` and `+0x22A` tests for zero. Later,
`+0x596..+0x59D` makes another real owner load and unsigned
16-bit `movzx` to test for **mode 9**. The maintained source now
uses two distinct typed source expressions
`static_cast<uint16_t>(metadata_source->field_38) == 0` and `== 9`,
instead of `mode == 0/9` on the earlier cached switch variable.
This restores real original member reads and signedness without
changing the physical ShotMetadata layout or other ECL opcodes.

## Independent immutable PE and entire source experiments

The original locked `.text` has been read afresh and **all 935
complete instruction heads** decoded to the native physical method
end. The independent verification checks the actual odd-first
parity `je` targets, all **six exact real pi×2 SSE instruction
triples** with original absolute data addresses, each separate
mode 2/4/7 `addss` accumulation site, original two speed-local
stack copy instructions and the two native unsigned metadata
`movzx` member reloads.

Each source variation was a **whole 3,735B game function** C++
compile, not a standalone expression snippet, cropped prefix or
an isolated fake compiler provider. The private scoreboard includes:

| Whole maintained source variation | Candidate bytes | Candidate x86 instructions | Ordered original mnemonics |
| --- | ---: | ---: | ---: |
| Before this checkpoint, correct original 60 E8 targets | 3,609 | 914 | **831 /935** |
| Odd shot count first, modes 0/1 only | 3,609 | 914 | **842 /935** |
| Odd shot rows first, modes 9/10 only | 3,609 | 914 | **864 /935** |
| Both original parity branch orderings | 3,609 | 914 | **875 /935** |
| Original sequential modes 2/3 and 4/5 | 3,627 | 917 | **892 /935** |
| Two speed float locals plus unsigned mode re-reads | 3,655 | 923 | **899 /935** |
| Also original mode 7 sequential heading | 3,661 | 924 | **905 /935** |
| Also all six original inner `(pi*two)` groupings | **3,685** | **930** | **911 /935** |

The fully maintained source under the original pinned Microsoft
Visual C++ 19.44.35211 i386 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` emits **3,685B / 930
complete method instructions**. Independent original PE call decoding
and **entire ordered COFF relocation identity comparison** after
this exact source update prove that **all 60 original E8 physical
callee targets still match in native order**, zero wrong and zero
unmapped. This includes the genuine separately canonical exact
63B old-STL shared_ptr move assignment, physically folded 8B
`std::move`, two 24B folded BulletColor assignments, Context getter,
all gameplay maths, actual Bullet command indexed access and the
original MSVC cookie checker. No duplicate game body is credited
for these already accepted physical original nodes.

Private experiment/proof evidence:

- `.analysis/core585-emitter-native-parity-branch-results.json` — four entire-source odd-first parity combinations.
- `.analysis/core587-emitter-evaluation-order-results.json` — mode-2/3, mode-4/5 and scalar evaluation-order trials.
- `.analysis/core588-emitter-metadata-and-math-results.json` — actual C++ original ECL metadata re-read and selective grouping trials.
- `.analysis/core589-emitter-initial-speed-mode-results.json` — real speed-local lifetime and unsigned mode variants.
- `.analysis/core591-mode7-native-math-evaluation-results.json` — original mode-7 and selective pi grouping trials.
- `.analysis/core592-pi-product-group-results.json` — all six original SSE groupings and multiple combinations.
- `.analysis/core593-emitter-native-fp-order-score.json` — final fresh maintained whole-boss compilation.
- `.analysis/core594-emitter-original-native-floating-order-proof.json` — original immutable PE whole-code/byte instruction evidence.
- `.analysis/core594-emitter-fp-order-60-whole-original-call-identity.json` — complete 60 original physical target ordinal proof from the newly maintained source.

## Remaining whole-boss work and affected-only validation

The result is **close by size but still NONEXACT**. Original physical
method has **3,735B / 935 instructions**; current C++ has **3,685B /
930 instructions**, so the current candidate is **50 bytes and five
net instruction heads short**. The original **E8 destination identity
and order are proved**, but original E8 **instruction offsets,
nonrelocated bytes, SSE register allocation, branch displacements,
stack local placement, EH lifetimes and 13+11 jump-table labels**
still differ. A candidate which matches all 60 call destinations is
not automatically byte-identical. We do not count any of the
3,735B game-body bytes as newly exact until every instruction,
relocation and linker contribution is verified.

**Only `src/BulletEmitter.cpp` changed.** It is still a noncanonical
source frontier with **zero previously accepted original native
exact units**. No public/shared header, other accepted source,
compiler profile, target bytes, original match ledger entry or
canonical unit manifest was touched. The entire affected source was
cold compiled and its original PE/call graph independently audited;
there are zero existing strict units in its own source to replay.
Running an unfiltered 1,184-unit repository cold replay would not
validate this still-nonexact parent and was deliberately avoided.

Game-authored exact coverage remains **498 functions / 175,709
nonoverlapping original bytes**. The existing exact canonical graph
remains **1,184 native units, 1,183 source-present function mappings,
243 compiled providers**. The separate 555B Player movement and
3,111B Player frame, 12,140B Bullet command dispatcher, 41,967B
Enemy ECL dispatcher and 39,470B Animation VM all remain independent
unfinished original game bosses; exact original gameplay/runtime
linkage is not implied.
