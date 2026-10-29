# CORE/EXACT-563 and CORE/RECON-563 — complete original Bullet style script getter and four recovered 3,735B emitter game calls

**Later CORE/RECON-583 complete E8 identity audit:** The real maintained
3,735B Bullet emitter parent now emits a C++ **3,609B / 914-instruction**
whole candidate, **831/935 original mnemonic kinds aligned**, and
all **60/60 immutable original PE physical E8 callee destinations
match in the original order**. The true anonymous-temporary
old `std::shared_ptr` move assignment and separate 8B `std::move`
are now referenced by the emitter source, and two original error
conditions share one actual `Animation::interrupt(2)` branch.
[Complete original 60-E8 ordinal callee proof](BULLET_EMITTER_60_ORIGINAL_E8_CALL_IDENTITY.md).
Older 3,628B/919 and 60-E8 *count-only* claims below are historical.
The original complete 3,735B/935 parent is **STILL NONEXACT**;
field sites, EH cleanup, switch tables and other code bytes differ,
with no parent exact-byte credit or global cold replay.


**Later CORE/RECON-571 current whole-boss status:** The complete
original 3,735-byte Bullet emitter remains **NONEXACT** but its real
maintained C++ was subsequently corrected for the original
`Context::bullet_controller()->file` child-Animation ownership path,
true game `geometry::norm_xy` and `scalar_math::arctangent` calls,
original `scalar_math::absolute(sine)` wave amplitude, additive
heading, and **`Vector3::operator-=` instead of +=**. The opcode-1
command now does **three independent original pmr::vector index
E8 calls and signed 16-bit `operand_10` reads**, rather than caching
one 32-bit value. [Complete original immutable PE gameplay evidence](BULLET_EMITTER_3735_COMMAND_AND_MATH_GAMEPLAY_CORRECTION.md).
Current full compiled C++ emits **3,628B/919 instructions with 828/935
original ordered mnemonics aligned**, and **60 candidate E8 vs 60
original E8 by count only**; original legacy STL move E8 and bytes
remain mismatched. Older 3,516B and 3,561B nonexact compiler
checkpoints below are historical, not current. No original parent
byte credit, public header edit or global cold replay in this pass.


Immutable original Japanese TH20 v1.00a Steamless executable:
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**One distinct original full 18-byte game function is newly strict
native exact**, and four previously missing original real game calls
are now present in the already-maintained **entire 3,735-byte Bullet
emitter boss**. The original physical color assignment at `0x0045D650`
is separately reproduced by a second type-safe source role and
**is not credited a second time**. The full emitter remains
**NONEXACT**: the last seven unconfirmed original call/stack/control-flow
relationships cannot be inferred from matching small children.

## Original 18-byte `type_to_script` — complete strict physical native unit

Native original `0x004856C0..0x004856D1`, **18 bytes / six i386
instructions**. Its true cdecl ABI accepts an integer `type`, scales
it by actual **0x158-byte** `BulletStyle` stride, and returns the
first 32-bit `BulletStyle::script` word from the real game BSS array
`bullet_styles[50]` at **`0x005C06A8`**. The original entire
`BulletController::emit()` has an independently decoded **real E8
at `0x00482297`** to this exact 18B physical function, and consumes
its returned ID before the separate already-exact 338B direct
`AnimationFile::load_script` call at `0x004822C5`.

`src/BulletStyle.cpp` now defines the natural typed
`std::int32_t type_to_script(std::int32_t type)` and declares it in
`BulletStyle.hpp`. Its complete ordinary MSVC 19.44.35211 i386 C++20
`/Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise` compiler body is
**18/18B** and retains exactly **one DIR32 COFF relocation**.
Independent immutable PE `.reloc` parsing gives the sole real
**HIGHLOW field at original `0x004856CC`**, targeting precisely
**`0x005C06A8`**. All **14 other original nonrelocated bytes**
are identical at their original positions. The pinned source object
was already a real canonical provider for `bullet_radius`; new
unit `bullet_type_to_script` uses that **same** native
`BulletStyle.obj` and canonical profile. Formal whole comparison
`compare-coff-function.py --unit bullet_type_to_script --json`
reports **`exact`, 18/18**, and the existing 18B `bullet_radius`
remains exact. The new physical body is disjoint from every previously
credited authored original native function, including both those
BulletStyle heads.

## Original 3,735B emitter: actual restored game calls and source roles

The original code for `0x004818E0..0x00482776` is **3,735B / 935
native i386 instructions**, with two attached independently checked
13-entry/11-entry switch tables and additional alignment in its
original compiler contribution. Its actual native direct E8 list
has **60 call fields**. Reexamining the original PE shows four
specific game method invocations absent from the previous natural
whole-source draft:

| Original emitter E8 | Immutable native destination | Recovered real C++ operation |
| --- | --- | --- |
| `0x00482252` | `0x004299D0`, full original **1,106B** | `bullet->animation->reset()` immediately after the already exact `0x0044C9B0` pool allocator and before writing user-data/callback fields |
| `0x00482297` | `0x004856C0`, newly exact **18B** | `type_to_script(shot.type)` passed to the separate 338B direct script loader rather than reading `style.script` in the emitter |
| `0x00482390` | `0x0045D650`, original **24B** | `bullet->color = 0xFFD08080u`, calling real typed Bullet word assignment instead of setting `.value` directly |
| `0x00482481` | `0x0045D650`, original **24B** | `bullet->color = style.colors[shot.color].words[4]` in native cancel-style case 6, retaining its real member call |

These original call-site addresses and absolute native targets were
**read directly from the immutable game executable's original E8
operands**, not solved from the candidate compiler object. The original
`0x00482241` pool allocator, `0x004822C5` script loader and all
other already independently accepted game-leaf addresses are
unchanged. Every corrected game statement uses genuine maintained
owner types (`Animation`, `Bullet`, `BulletStyle`, `BulletColor`), not
anonymous forged byte-storage, arbitrary `extern "C"` shims or
artificial assembly instructions.

### Exact 24B color assignment is physically linker-folded, not new credit

`Bullet::color` is a true **four-byte** `BulletColor` member at native
`Bullet+0x88`. It previously had a real constructor but no maintained
integer-assignment member, causing the whole emitter to write its
public `.value` field directly and emit **zero** calls for both
original physical assignments.

`Bullet.hpp` now declares and `Bullet.cpp` defines the natural typed
`std::uint32_t BulletColor::operator=(std::uint32_t input)` body,
assigning the genuine word and returning the input just as the
original native 24B code does. A freshly compiled **complete 24B
`BulletColor` contribution is byte-for-byte identical** to the
original existing physical `0x0045D650..0x0045D667` native method,
including its true `ret 4`; there are **zero relocation fields**.
This exact original physical address was **already** credited via
`PackedColor::operator=(uint32_t)` from
`src/EffectParameters.cpp`. These are independently legitimate
four-byte game field sources whose locked MSVC code is folded into
one native function. The new `BulletColor` source must therefore
receive **zero additional original authored bytes** and does **not**
create a second duplicate physical match-unit ledger row. This also
corrects the older mistaken 22B estimate: the entire physical
original **including three-byte `ret 4` is 24 bytes**.

### Full emitter's actual progress — not a falsely exact parent

| Whole original emitter measure | Previous maintained C++ | New maintained C++ | Immutable original |
| --- | ---: | ---: | ---: |
| Game method code bytes | 3,516B | **3,561B** | 3,735B |
| Decoded original/candidate instructions | 890 | **904** | 935 |
| Original instruction mnemonic kinds aligned in order | 792 | **809** | 935 |
| Direct E8 / compiler REL32 calls | 53 | **57** | 60 |

This is a **real improvement in source semantics and original target
identity**, not proof of the remaining byte relocation layout. The
emitter's 13 and 11 generated switch-label tables, 63B historical
`std::shared_ptr<EtamaArgInf>` move-assignment ABI, one original
0x40C300 handle getter and original vector/Animation return/lifetime
calls remain independently unresolved. The candidate emitter has no
canonical exact unit and gains **zero parent exact original bytes**.
The original complete method and separate 12,140B Bullet dispatcher
remain open bosses, as do Player 555B/3,111B, Enemy ECL 41,967B
and Animation VM 39,470B.

Original field proof (the new 18B head, full immutable PE HIGHLOW,
real 3,735B caller E8s, physical 24B color alias and no-overlap):
`.analysis/core563-emitter-type-script-original-pe-proof.json`.
Fresh 3,735B whole C++ comparison and 57-current-E8 evidence:
`.analysis/core560-emitter-e8-current.json`,
`.analysis/core561-emitter-call-sequence.json`,
`build/core562-probes/BulletEmitter.obj`.

## No full cold replay; all real public-header dependents protected

The source edits touch `src/Bullet.cpp`, `src/BulletStyle.cpp`,
`src/BulletEmitter.cpp` and the two **real shared headers**
`src/Bullet.hpp` and `src/BulletStyle.hpp`. The actual canonical
receipt closure was frozen **before editing those headers**:
**32 distinct original C++ source/object providers / 71 previous
whole native strict units**. Only these 32 original source
providers were freshly rebuilt, under their **existing pinned
per-source MSVC profiles**, along with the new 18B unit in the
already existing `BulletStyle.cpp` object.

The first strict pass exposed six MSVC-private source-string label
renumberings, **not** original game-code byte changes. An independent
source-vs-immutable-PE audit verified **all 72 entire native units /
24,481 original compared bytes**, including every unrelocated native
byte, original REL32/absolute field destination and each changed
compiler-owned string's **full exact original PE content**. The six
verified compiler-private renumberings are:

- Bullet cancel native `"bullet"` at `0x0056FD14`:
  `$SG183082` → `$SG183084`.
- BulletController constructor native `"initialize BulletInf\n"` at
  `0x0056FC68`: `$SG85550` → `$SG85552`.
- Four Dialogue constructor literal uses of the original `"text"`
  at `0x0056FE1C`: `$SG117951..954` → `$SG117953..956`.

Only these **six private COFF label spellings** changed in their
previous canonical manifests; the original native PE field offsets,
target addresses, bytes and actual payloads were not changed or
reinterpreted. A final fresh **32-source / 72/72 strict whole native
unit replay** passed, including prior 1,404B original command-11,
1,846B Bullet physics, 2,018B Bullet collisions, 898B command-3,
707B rectangle cancellation and all Dialogue/Enemy/Item source
consumers. This is **strictly affected-only**; no 1,183-unit global
cold replay.

Private frozen receipt dependency closure:
`.analysis/core562-preedit-bullet-style-owner-receipt-closure.json`;
new canonical original test:
`.analysis/core563-bullet-script-native-compare.json`;
full original byte/reloc/private-source-string proof:
`.analysis/core565-bullet-header-72unit-native-pe-audit.json`;
final scoped cold build and replay:
`.analysis/core565-bullet-headers-final-cold-build.log` and
`.analysis/core565-bullet-headers-final-replay.log`.

**Game-authored exact coverage rises from 497 complete original
functions / 175,691 disjoint bytes to 498 functions / 175,709 bytes.**
Canonical native units increase **1,182 → 1,183** and source-present
mapping rows **1,181 → 1,182**; actual pinned MSVC object providers
remain **242** because this whole 18B game function is implemented
in an already configured BulletStyle source. No physical original
color bytes were credited again, and the entire 3,735B emitter
remains NONEXACT. A linked executable or runtime-equivalent game is
not claimed.
