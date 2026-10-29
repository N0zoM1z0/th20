# CORE/ORIGIN-535 / CORE/EXACT-535 — ten complete Graphics, Player, Bullet, Item, Input, Progress and Archive owners, 6,057 bytes

Comparison executable: locked Japanese TH20 v1.00a Steamless
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Ten whole, distinct, native-strict-exact project-authored game/runtime
methods are newly origin-admitted, totaling 6,057 original code bytes
and 1,479 complete original x86 instructions.** They include major
941B Graphics and 794B Player constructors, 712B original PlayerRecord,
706B Archive LZSS decompression, 612B Progress metadata, 596B Item pool
and 556B Bullet initialization; this is not limited to trivial getter
leaves. All maintained natural C++ and exact canonical units already
existed. This checkpoint independently audits **authored source origin**
with the original game executable and its actual callers, rather than
claiming to have newly typed ten source functions.

## Whole original native game bodies and native consumers

| Original head | Complete body | Exact source role | Original caller evidence and confidence |
| --- | ---: | --- | --- |
| `0x004D8990` | **941B** | `Graphics::Graphics` — original Direct3D device/presentation, viewport, sprites and runtime flags | Original 43B startup/wrapper at `0x0040AA10` directly calls it, but original wrapper remains unnamed: **medium** |
| `0x004F46A0` | **794B** | `Player::Player` — actual full Player owner field and nested member initialization | Original 73B Player allocation wrapper `0x004F32B0` directly calls; custom gameplay storage: **high** |
| `0x00423050` | **712B** | `PlayerRecord::PlayerRecord` — actual game score, reward/power and history defaults | No incoming direct E8 found; possible constructed array/vector call path still unproven: **medium** |
| `0x005391F0` | **706B** | `archive_decompress` — original 8192-byte LZSS dictionary and game package decode | Original exact `ArchiveOwner::load_catalog` (`0x00539ED0`), exact `ArchiveOwner::read` (`0x0053A3C0`) and exact `ProgressSaveManager::parse` (`0x0050EB70`) call it: **high** |
| `0x0050E6E0` | **612B** | `ProgressMetadata::ProgressMetadata` — entire game-specific progress defaults and nested value lifetimes | Original `ProgressSnapshot` constructor at `0x0050E540` directly calls it: **high** |
| `0x004BC220` | **596B** | `ItemInf::initialize_pool` — real 512/1024 ordinary/special item slots and intrusive free lists | Original ItemInf initialization at `0x004C3C00` and three additional Item game controller routines call it: **high** |
| `0x0047BE00` | **556B** | `Bullet::Bullet` — real 0x528-byte Bullet object, indexed commands/Timer/Animation and list lifetimes | No incoming direct E8 in the original whole-function inventory; compiler vector construction is a possible explanation but not silently asserted: **medium** |
| `0x0050A4D0` | **475B** | `InputButtonState::update_replay` — real game input/replay state mutation | Two original runtime/control callers at `0x00507B70` and `0x00507F80` are still unnamed: **medium** |
| `0x00538C50` | **346B** | `Pbg::File::open` — original Win32/CP932 PBG archive file, append and read semantics | No incoming direct E8; real `Pbg::IFile` virtual interface and game package owner mean indirect calls possible, not proved: **medium** |
| `0x00471790` | **319B** | `ViewportState::ViewportState` — real game view/clip and D3D viewport initialization | Original unnamed 447B graphics helper at `0x004715C0` calls it: **medium** |

Four have **high** game-source provenance through original caller
families and bespoke storage. The other six deliberately retain
**medium** authored confidence, distinguishing unknown constructors,
virtual call paths, and unclassified original callers from a proven
absence of uses. This does **not** pretend that a custom `Pbg::File`
wrapper is standard C++ library/compiler output: the original method
implements project-specific CP932 file resolution and sequential
archive access over its real virtual IFile owner, unlike CRT/Win32
import thunks. Conversely, virtual/indirect invocation and original
runtime linkage remain unproven and are not upgraded to high confidence.

The original independent native direct E8 caller census for all ten
heads, including explicit zero-match cases, is preserved in
`.analysis/core532-owner-boss-original-direct-callers.json` and
`.analysis/core532-owner-boss-original-direct-callers.log`.
Source files are the already maintained `src/Graphics.cpp`,
`src/Player.cpp`, `src/PlayerRecord.cpp`, `src/ArchiveLzss.cpp`,
`src/ProgressStorage.cpp`, `src/Item.cpp`, `src/Bullet.cpp`,
`src/InputState.cpp` and `src/PbgFile.cpp`. No historical C++ name or
original translation-unit partition is claimed proven.

## Whole original PE and compiler relocation evidence

For each function we read the *entire game-authored body* from the
immutable locked PE, independently decoded its complete x86 instruction
heads through the physical return, and separately parsed the original
PE `.reloc` HIGHLOW directory. Original direct E8 targets were
recomputed from the **original executable's own opcode operands**,
not inferred from freshly compiled C++ candidate fields. Original
function intervals are pairwise disjoint and disjoint from all 465
previously accepted authored exact original intervals.

| Whole native function | Native game body | Full compared compiler span | Original E8 / PE HIGHLOW |
| --- | ---: | ---: | ---: |
| Graphics constructor | 941B | **946B** | 13 / 3 |
| Player constructor | 794B | **799B** | 30 / 4 |
| PlayerRecord constructor | 712B | 712B | 0 / 0 |
| Archive LZSS decode | 706B | 706B | 1 / 5 |
| Progress metadata constructor | 612B | 612B | 3 / 0 |
| Item pool initialisation | 596B | 596B | 18 / 1 |
| Bullet constructor | 556B | 556B | 18 / 0 |
| Input replay update | 475B | 475B | 7 / 0 |
| PBG File open | 346B | 346B | 2 / 3 |
| ViewportState constructor | 319B | 319B | 14 / 1 |

**All 106 original E8 locations and all 17 original HIGHLOW locations
and absolute targets (123/123 total fields) match the existing locked
MSVC COFF relocations**, including each symbol/base and ordinary
linker addend. Every remaining nonrelocated original byte agrees over
**6,067 compared bytes**. The **ten extra original compiler alignment
bytes** are attached to the 941B Graphics and 794B Player constructors:
they are compared exactly but are **not** credited again as authored
game-body bytes. No original code prefix was shortened, field hidden,
NP padding inserted or compiler flag changed.

Full original body/hash, original source fields, original absolute
E8 and HIGHLOW targets, original toolchain table/alignment contributions
and whole-source original physical no-overlap proof are in
`.analysis/core534-game-construction-ten-native-pe-audit.json`
and `.analysis/core534-game-construction-original-audit.log`.
These are independent original PE proofs, not a rewrite of the old
function inventory's 100% structural score.

## Focused cold compilation and strict native replay

Only the **nine actual existing source/object providers** above were
cold rebuilt with their **already registered, source-specific pinned
MSVC 19.44.35211 x86 profiles**. Some providers retain genuine
`/fp:strict`, native CP932 translation rules, `/GS` or `/GS-`; no
project-wide flag was imposed. The full source-scoped existing-object
native strict replay of all configured units in just those nine real
providers passed **119/119 complete original canonical native units**.
This includes other accepted player, Graphics, PBG file and
Item/intrusive-list functions whose code must remain exact. The ten
newly accepted bodies already had those exact source providers and
strict canonical unit receipts; the only newly proven claim is their
**independent project-authored origin**, not a new compile implementation.

Fresh complete strict and scope evidence:
`.analysis/core533-owner-boss-cold-build.log`,
`.analysis/core533-owner-boss-targeted-cold-build.json` and
`.analysis/core533-owner-boss-nine-provider-strict-replay.log`.
**No unfiltered or whole-repository cold replay** was run. No source,
shared-header, linker settings or original target bytes were changed.

**Game-authored original exact coverage increases from 465 functions /
161,762 bytes to 475 whole functions / 167,819 disjoint game-body
bytes.** Canonical native unit count **1,181**, source-present functions
**1,181** and unique MSVC source/object providers **241** do not
increase because these ten game-owned bodies already had full exact
source and receipts but were previously origin-pending.

The original 73B Animation factory remains separate and **NONEXACT**:
new private MSVC tests confirmed it first invokes an original 31B
clear-before-construct helper before the real Animation constructor,
whereas ordinary `new Animation` emits only 60B and explicit placement
new or `std::construct_at` still generates different calls. Changing
the real Animation constructor or forcing fabricated object layout just
to shape this small callee would endanger already exact source. The
3,735B Bullet emitter, 3,111B Player frame, 555B movement, 39,470B
Animation VM and 41,967B Enemy ECL dispatcher also remain **separate
NONEXACT whole game bosses**. Exactness of any of the ten game-owned
constructor/codec/viewport helpers does not prove those parents,
a complete original game link, or playable runtime.
