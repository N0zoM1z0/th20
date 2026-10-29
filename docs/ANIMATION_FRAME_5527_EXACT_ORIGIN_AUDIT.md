# CORE/ORIGIN-507 / CORE/EXACT-507 — 17 complete original Animation game functions, 5,527 bytes

Immutable comparison executable: Japanese TH20 v1.00a Steamless,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**17 whole game-authored original Animation functions / 5,527 nonoverlapping
body bytes are now formally admitted to the authored exact ledger.** This is
an **origin audit** of real maintained sources and existing, initially
origin-pending native strict units, rather than a claim of 17 newly authored
source functions. The vast **39,470-byte original Animation VM dispatcher**
at `0x0042B5D0` remains an independently **nonexact parent**; its calls into
these children do not grant any bytes of the dispatcher itself.

## Complete original bodies and real game roles

| Original entry | Whole body | Game-owned method |
| --- | ---: | --- |
| `0x004299D0` | **1,106 B** | `Animation::reset` — real field reset, native Timers, interpolation lifecycle |
| `0x00435520` | **931 B** | `Animation::update_motion` — actual motion, rotations, scroll and clock dependencies |
| `0x004358D0` | **944 B** | `Animation::update_interpolations` — twelve typed Animation channels |
| `0x00437EB0` | **835 B** | `Animation::float_value` — actual VM animation operand evaluation |
| `0x00437D00` | **301 B** | `Animation::integer_value` — VM integer operands and game RNG |
| `0x00437310` | **244 B** | `Animation::float_argument` — original variable binding |
| `0x00437220` | **165 B** | `Animation::integer_argument` — original variable binding |
| `0x004382B0` | **194 B** | `AnimationFile::bind_animation` — parent linkage/template application |
| `0x00437770` | **196 B** | `Animation::rotation_sum` — recursive parent rotation |
| `0x00437840` | **226 B** | `Animation::transform_direction` — inherited rotation/scale |
| `0x004374B0` | **67 B** | `Animation::slowdown` — parent frame-rate inheritance |
| `0x004458E0` | **93 B** | `Animation::inherited_scale_y` — recursive Y scale |
| `0x00445940` | **93 B** | `Animation::inherited_scale_x` — recursive X scale |
| `0x004459A0` | **45 B** | `Animation::height` — inherited dimension |
| `0x004459D0` | **45 B** | `Animation::width` — inherited dimension |
| `0x0044CB60` | **17 B** | `Animation::position_ref` — real game-owned position field |
| `0x0044FA10` | **25 B** | `Animation::set_packed_color` — actual game-published color |

Original game-ownership is supported by independently parsed original E8
call sites, not simply names in old notes. Most decisively, original
`Animation::update`/VM (`0x0042B5D0`, **39,470 bytes**) calls the full
**931-byte** motion update, full **944-byte** interpolation update,
**13** original integer-argument sites, **22** float-argument sites,
**117** integer-value sites and **156** float-value sites. These are
independent original decoded call instructions. The actual `Animation::reset`
is invoked from the genuine **12,140-byte** Bullet controller dispatcher,
**3,735-byte** Bullet emitter and other real animation-pool creation
consumers. Game-exact `EnemyState::update_movements` (**1,675 bytes**)
reads original Animation X/Y scales and position. Game-exact
`ItemInf::spawn` and other game participants call packed-color setters.
The original 3,111-byte Player main frame invokes the real parent
Animation binding four times. These relationships tie each member to real
Animation/Player/Bullet/Enemy gameplay ownership, not STL/CRT templates.

The original source spelling, authored translation-unit partition,
linker fold identity of unrelated getters, whole-game linkage, runtime,
state validity in untested input domains and external toolchain globals
remain separate questions. Generic `std`/PMR compiler helpers in the
same source object are **not** upgraded to game-authored status. The
pre-existing Array/Pool constructors, compiler allocation and string
helpers remain in their previously reviewed or excluded origin states.

## Strict native whole-body evidence and independent relocations

Each of the actual source providers `src/Animation.cpp`,
`src/AnimationUpdates.cpp` and `src/AnimationOperands.cpp` was freshly
cold-built **once** under its existing pinned MSVC 19.44.35211 x86 source
profile. The relevant retained 50 strict units then passed **50/50**
complete canonical original-byte replay using only an explicit three-source
filter, without an unfiltered whole-graph cold replay. All **17/17** newly
origin-admitted whole game bodies therefore already had an exact canonical
unit; 33 other units in these same three objects were also preserved
(e.g. class-lifetime contributions and separate library/compiler bodies).
No native source, public header, compiler flags or manifest entries
changed in this checkpoint.

An independent original-target parser separately decoded the complete
**5,527 native body bytes / 1,475 original i386 instructions**, plus
attached original compiler contributions where the canonical unit's
`compare_size` exceeds the game body. In particular, integer/float
argument and value interpreters carry genuine switch-table and related
compiler bytes: the actual **5,944 compared bytes** exceed the game
body coverage by **417 bytes**. These attached bytes are fully compared
but are not credited again as authored body bytes.

Across all 17 original entries, the independent native x86 decoder
recovered **93 original E8 direct calls** and the immutable original
PE `.reloc` parser recovered **140 HIGHLOW absolute fields** (including
real attached table pointers). Every original field position and type
matched the pinned COFF relocation and its existing independently
identified manifest symbol/base plus compiler addend. Every remaining
non-relocated native byte also agreed with original `.text`, with no
shortened extent, ignored instruction, patch or candidate-derived
relocation destination. Actual original full hashes, original native
call targets, original `.reloc` sites and compiler candidates are in
`.analysis/core507-animation-native-original-audit.json` and
`.analysis/core507-animation-native-callers.json`. Complete filtered
replay is in `.analysis/core507-animation-50unit-replay.log`.

**Authored coverage:** previous **420 functions / 138,279 original game-body
bytes** becomes **437 functions / 143,806 distinct original game-body
bytes**. Strict canonical unit count remains **1,177** and unique
canonical compiled object/receipt providers remain **237**, because
all 17 functions were already native strict units but their original
game-authored provenance was still withheld. All game-origin entries in
this checkpoint have high confidence based on original code consumers,
exact owner state and independent native full-function evidence.

## Next whole-function frontiers

The original enclosing Animation VM `0x0042B5D0` is still nonexact and
contains additional native script interpreter operations; reconstructing
its entire control flow and the true scheduler/ANM lifetime is distinct
work. Player `0x004F9C30` (3,111B), Player movement `0x004FFA10`
(555B), Bullet command-11 `0x00481200` (1,404B), Bullet emitter
`0x004818E0` (3,735B) and the 41,967B Enemy dispatcher also
remain open. No child/caller or exact-origin credit closes these parents.
