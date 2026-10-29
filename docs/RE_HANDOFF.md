# TH20 reconstruction — current agent handoff

**Last reconciled: 2026-10-29, CORE/DOC-CLEANUP-628.** This file is a
**current-state/next-work guide**, not a chronological checkpoint log. The
previous 813-line handoff, with its historical exact counters and repeated
Bullet emitter milestones, remains in Git at
`git show 3e0f343:docs/RE_HANDOFF.md`. Use
[the evidence index](EVIDENCE_INDEX.md) for individual original PE audits.
**Do not apply dated NONEXACT or compiler-score claims over newer whole-native
exact admissions.** The ledgers and live native receipts, not prose, decide
what is accepted.

## Immutable target and accepted status

| Fact | Verified current value |
| --- | --- |
| Game | Japanese TH20 v1.00a, user-selected **Steamless** PE |
| Game target | `resources/th20.exe`, **1,858,560 bytes** |
| SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Provisional function heads | **6,928**; unresolved boundaries are *not* exact |
| Source-present function mappings | **1,183**, all origins |
| Configured whole-native strict units | **1,184**, including library/compiler |
| Distinct canonical MSVC object + receipt providers | **243** |
| **Game-authored original whole-body exact** | **498 distinct functions / 175,709 disjoint original `.text` bytes** |
| Whole-program link / playable game | **Not yet available** |

These counts are a dated snapshot. Run `scripts/repo-python
scripts/report-reconstruction-status.py --summary` for the live graph. The
percentage of *confirmed authored* functions in `docs/PROGRESS.md` is **not**
a percentage of the entire original TH20 executable reconstructed. Registry
and package version 1.00a versus embedded title/replay string 1.00c are
both true of this exact [locked target](TARGET_PROVENANCE.md).

### Closed original bodies — do not reopen based on old frontier notes

| Original native owner | Strict accepted whole body / evidence |
| --- | --- |
| `0x00421B00` InputDevice polling | **3,490B / 747 x86**, [complete DirectInput/XInput source and PE proof](INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md) |
| `0x00481200` Bullet command-11 | **1,404B / 357 x86**, [full original command state and canonical replay](BULLET_COMMAND11_1404_EXACT_RECONSTRUCTION.md) |
| `0x00539550` archive LZSS compressor | **1,036B / 315 x86**, [actual seven original accumulator writes and byte-exact original native encoder](ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md); prior 964B nonexact hypothesis **superseded** |
| `0x005391F0` archive LZSS decompressor | **706B**, [whole original archive/game provenance](GAME_OWNER_CONSTRUCTION_6057_EXACT_ORIGIN_AUDIT.md) |
| `0x0053B5C0` ECL runtime tick | **11,110B**, [whole strict original interpreter runtime](EXACT_ECL_TICK_RECONSTRUCTION.md); **not** the 41,967B Enemy opcode dispatcher |
| `0x0044C9B0` Animation pool allocator | **298B**, [true game-owned pool allocation and recycled slot ABI](ANIMATION_POOL_ALLOCATE_298_EXACT_RECONSTRUCTION.md) |
| `0x004383A0` Animation direct script load | **338B**, plus 21B VM-forward helper, [whole native caller ABI](ANIMATION_DIRECT_SCRIPT_359_EXACT_RECONSTRUCTION.md) |
| Real geometry | **19 whole methods, 13,360B**, [complete original rectangles, circles, polygons and intersections](GEOMETRY_ORIGIN_13360_EXACT_RECONSTRUCTION.md) |
| Real game owner constructors/codec/graphics | **10 whole methods, 6,057B**, including 941B Graphics and 794B Player; [native project-origin audit](GAME_OWNER_CONSTRUCTION_6057_EXACT_ORIGIN_AUDIT.md) |
| ECL/Bullet/Animation methods | **21 whole methods, 6,836B**, including ECL operand parser and four Animation child recursions; [original user call graph](ECL_BULLET_ANIMATION_6836_EXACT_ORIGIN_AUDIT.md) |
| Enemy/Motion and interpolation | **7,204B** [Enemy/Motion](ENEMY_MOTION_7204_EXACT_ORIGIN_AUDIT.md) and **8,571B** [interpolation](INTERPOLATION_BOSSES_8571_EXACT_ORIGIN_AUDIT.md), complete independently PE-verified original game-owned bodies |

The 63-byte original `std::shared_ptr<EtamaArgInf>` move assignment is
[whole-native 63/63 exact](SHOT_SHARED_PTR_LEGACY_MOVE_63_EXACT_COMPILER_SUPPORT.md),
but it is **library-origin, excluded from game-authored byte credit**. The
folded 8B `std::move`, 16B Context getter and 24B BulletColor/PackedColor
assignments do **not** create separate physical-original byte credit.
A call from an unresolved giant parent to an exact child does **not** mean
that entire parent is reconstructed.

## Open complete-game bosses — active source and actual blockers

| Original head | Real whole original | Current evidence / most useful next work |
| --- | --- | --- |
| `0x004818E0` Bullet emitter | **3,735B, 935 x86** | [Full native source](../src/BulletEmitter.cpp) now emits **3,735B/935 x86**, plus exact-size original post-function NOP and 13+11 switch tables for a **3,832B whole contribution**. [Independent original PE/COFF audit](BULLET_EMITTER_3735_COMPLETE_CODE_RELOCATION_FRONTIER.md): **3,316/3,316 nonrelocated bytes identical**, **129/129 physical E8/DIR32 field offsets/types**, all **60/60 native E8 callee destinations independently verified**. Original-absent internal NOP eliminated through real Timer if-initializer; mode-11/12 float argument order recovered. **69 absolute target identities and whole new strict replay still outstanding; NONEXACT, no authored byte credit yet.** |
| `0x004F9C30` Player main frame | **3,111B, 783 x86** | [Complete typed C++](../src/PlayerMainFrame.cpp) emits **3,254B /808**, **733/783** native mnemonics aligned. Native 67 E8/37 HIGHLOW and candidate 67/37 agree by count **only**. Correct two Context EnemyController getter calls, separate sprite floats, real 22B Timer **postfix**; original 45B effect-handle equality vs source inequality still unresolved. [Current ABI proof](PLAYER_MAIN_TIMER_POSTFIX_3111_NATIVE_ABI.md). **NONEXACT**. |
| `0x004FFA10` Player movement | **555B, 135 x86** | [Complete source](../src/PlayerMovement.cpp) emits **561B /136**, all original mnemonic kinds but one unwanted 6B SSE spill before `cvttss2si esi,xmm0`; not fixed by `/fp` changes or SSE intrinsics. [Full immutable PE history](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md). **NONEXACT**. |
| `0x0047DB70` Bullet drawing group | **273B** | [Complete source and extra SSE spill frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md); compiler currently emits ~283B. **NONEXACT**. |
| `0x004A4190` Enemy mesh | **1,649B** | [Whole C++ owner and original transient lifetime](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md); existing source is nonexact, do not forge an unused byte. |
| `0x0047DCF0` Bullet command dispatcher | **12,140B** | Distinct **NONEXACT** controller parent even though the 1,404B command-11 child is exact. [Source map](SOURCE_MAP.md). |
| `0x0048C010` Enemy ECL dispatcher | **41,967B** | Huge original VM/controller parent **NONEXACT**. [Dispatch layout / table analysis](CORE_ENEMY_DISPATCH_LAYOUT.md). |
| `0x0042B5D0` Animation VM update | **39,470B** | **NONEXACT** giant original parent; native-exact child parsers, loaders, reset and frame helpers cannot be counted as this body. [Animation owner map](SOURCE_MAP.md). |
| `0x00447800` Animation factory | **73B** | Original clear-before-construct path differs from ordinary `new Animation`; earlier natural placement/new tests unsuccessful. Do not alter otherwise exact Animation constructor or introduce fake zeroing. [Allocation history](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md). |

**Near-term priority:** independently anchor all 69 absolute relocations
of the entire Bullet emitter, add its 3,832B canonical unit, and perform
**only that new owner's** complete strict native replay. The 60 original
E8 callees are already independently checked. Do not grant 3,735B authored
credit until replay accepts the complete relocation-resolved contribution.
Next continue the Player 555B spill and 3,111B main-frame ABI; do not
abandon giant parents.

## Evidence and source ownership discipline

1. Distinguish **source-present**, **original project/library provenance**,
   **canonical whole-native strict exact**, **linked runtime**, and actual
   gameplay equivalence. `config/functions.csv`,
   `config/function-origins.csv`, `config/matches.csv` and
   `config/match-units.toml` serve different purposes. One original
   physical function head gets one body credit despite folded aliases.
2. Source/PE acceptance requires the **entire original instruction and
   compiler-alignment extent**, PE E8 and genuine `.reloc` HIGHLOW sites,
   independently anchored absolute original targets, matching COFF fields
   and actual locked MSVC **strict replay**. A mnemonic alignment score,
   equal E8/DIR32 **counts**, or byte-identical nonrelocated text alone is
   **not** an exact parent.
3. Old proof documents often include their **dated** counters or then-current
   NONEXACT status. Follow [current handoff](RE_HANDOFF.md) and
   [evidence index](EVIDENCE_INDEX.md); preserve old proofs as dated
   experimental evidence, do not globally replace historical facts.
4. All production C++ and docs use English. No fake ABI aliases, copied
   original code, byte patch, padding/assembly, unverified data table,
   artificial `volatile` or undefined pointer cast to make numbers match.
   Distinct toolchain/library compatibility code must be clearly classified.

## Verification — bounded to changed inputs

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/progress.py --check
```

- **Native changes:** rebuild and strictly compare only the changed canonical
  units or the actual pre-edit include/receipt source closure. Example:
  `scripts/repo-python scripts/build.py --unit NAME` and
  `scripts/repo-python scripts/replay-exact-units.py --existing-objects --source src/X.cpp`.
  Never unfiltered/full-graph cold replay; don't claim source-present bosses
  exact without a canonical unit. `src/BulletEmitter.cpp` currently has
  **zero** previously strict units, so its full pinned C++/PE comparison is
  the relevant test until whole-exact.
- **Docs and ignored-cache cleanup only:** no native compiler input changes,
  **zero native units to replay**. Check target and protected object hashes,
  live ledger/progress when needed, Markdown links, `git diff --check`.
  Tooling changes warrant targeted Python/control-plane tests, **not** an
  automatic game-wide cold build. [Workflow](RE_WORKFLOW.md).
- **Dirty tree is our work**: inspect every tracked/untracked change, own
  unfinished code/evidence, and retain original hypotheses under ignored
  `.analysis/` when needed. Commit stable progress with `gpt-web: ...`.

## Storage and protected artifacts

`resources/th20.exe` and its SHA, `ghidra-project/`, `_reference/`, the
installed `.tools/msvc` / Wine / D3DX, pinned `.venv`, **all 243 canonical
`.obj` and `.receipt.json` pairs** and independent PE/source proofs must
survive cleanup. Historical `.analysis/*.json.gz` snapshots are explicitly
cited and may contain the **only** original frozen ABI state; do not purge
them, even if they are old. Older source variants and unique native audit
proofs remain in `.analysis/` and Git history.

Only retired **reproducible noncanonical `build/*-probes` objects/receipts**
are suitable for the guarded storage cleanup. Use the dry-run-first
`scripts/repo-python scripts/prune-generated-artifacts.py`, then an explicit
new `--inventory .analysis/NAME.json --apply`; preserve active Bullet/Player,
Mesh, and other open-boss probes. **Never overwrite old cleanup inventories,
`git clean -fdx`, delete the full `build/`/`.analysis/`, remove the
compiler/toolchain, or delete original PE and native proofs.** See
[latest retirement audit](ARTIFACT_RETIREMENT_CORE628.md) and
[protected storage workflow](RE_WORKFLOW.md).
