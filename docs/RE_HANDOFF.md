# TH20 reconstruction — current agent handoff

**Last reconciled: 2026-10-29, CORE/RECON-704.** This file is a
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
| Source-present function mappings | **1,185**, all origins |
| Configured whole-native strict units | **1,187**, including library/compiler |
| Distinct canonical MSVC object + receipt providers | **245** |
| **Game-authored original whole-body exact** | **504 distinct functions / 179,611 disjoint original `.text` bytes** |
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
| `0x004818E0` Bullet emitter | **3,735B / 935 x86 full native exact**, [whole 3,832B code/NOP/two-switch-table strict source and 129 original relocated field proof](BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md); authentic 4.0f velocity scalar corrects earlier false 2.0f, isolated new source **1/1 strict cold replay**, zero overlapping compiler/table byte credit |
| `0x00539550` archive LZSS compressor | **1,036B / 315 x86**, [actual seven original accumulator writes and byte-exact original native encoder](ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md); prior 964B nonexact hypothesis **superseded** |
| `0x005391F0` archive LZSS decompressor | **706B**, [whole original archive/game provenance](GAME_OWNER_CONSTRUCTION_6057_EXACT_ORIGIN_AUDIT.md) |
| `0x0053B5C0` ECL runtime tick | **11,110B**, [whole strict original interpreter runtime](EXACT_ECL_TICK_RECONSTRUCTION.md); **not** the 41,967B Enemy opcode dispatcher |
| `0x00447800` Animation allocation factory | **73B/22 x86 complete strict exact**, [real game factory + coherent class tag and all 3 native physical E8 proof](ANIMATION_FACTORY_73_CLASS_TAG_STRICT_EXACT_RECONSTRUCTION.md); one normal C++ `class Animation` declaration in seven headers, one canonical `/sdl` explicit template definition, `extern template` in non-SDL 298B caller. **492/492 previous exact units and 117/117 affected cold objects preserved**, zero overlapping original compiler-helper credit. |
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
| 0x004F9C30 Player main frame | **3,111B, 783 x86** | Complete maintained [source](../src/PlayerMainFrame.cpp) now emits **3,114B / 783 x86, all 783/783 native mnemonic kinds in original order**. [Direct original PE proof](PLAYER_MAIN_NATIVE_SCRIPT_INDICES_AND_OPTION_LOOPS_3111.md) fixes a **real gameplay off-by-one**: original animation_scripts[1..4] at Player+0x22A0 +{4,8,12,16}, not previous [0..3], saves one begin/end result per 10/12-entry option group before iteration and uses native 8B history source-before-destination assignment. Previous [X-then-Y motion order](PLAYER_MAIN_3111_NATIVE_XY_ACCUMULATION_ORDER.md), [two focus DWORDs](PLAYER_MAIN_FOCUS_AND_HISTORY_NATIVE_LIFETIMES.md), [9x2 direction table](PLAYER_MAIN_FRAME_NATIVE_9X2_DIRECTION_TABLE.md), [signed speed](PLAYER_MAIN_FRAME_3111_INPUT_AND_SIGNED_SPEED_NATIVE_FRONTIER.md) and [typed 45B handle equality](PLAYER_ANIMATION_HANDLE_TYPED_EQUALITY_NATIVE_FRONTIER.md) remain. All 67 true E8 callee roles independently reconciled; 67 REL32/37 DIR32 by count only. Exact original byte/relocation field positions still differ, **NONEXACT**, zero parent byte credit. |
| `0x004FFA10` Player movement | **555B, 135 x86** | [Complete source](../src/PlayerMovement.cpp) emits **561B /136**, all original mnemonic kinds but one unwanted 6B SSE spill before `cvttss2si esi,xmm0`; not fixed by `/fp` changes or SSE intrinsics. [Full immutable PE history](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md). **NONEXACT**. |
| `0x0047DB70` Bullet drawing group | **273B** | [Complete source and extra SSE spill frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md); compiler currently emits ~283B. **NONEXACT**. |
| `0x004A4190` Enemy mesh | **1,649B** | [Whole C++ owner and original transient lifetime](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md); existing source is nonexact, do not forge an unused byte. |
| `0x0047DCF0` Bullet command dispatcher | **12,140B** | Distinct **NONEXACT** controller parent even though the 1,404B command-11 child is exact. [Source map](SOURCE_MAP.md). |
| `0x0048C010` Enemy ECL dispatcher | **41,967B** | Huge original VM/controller parent **NONEXACT**. [Dispatch layout / table analysis](CORE_ENEMY_DISPATCH_LAYOUT.md). |
| `0x0042B5D0` Animation VM update | **39,470B** | **NONEXACT** giant original parent; native-exact child parsers, loaders, reset and frame helpers cannot be counted as this body. [Animation owner map](SOURCE_MAP.md). |

**Near-term priority:** Bullet emitter remains fully strict exact at
3,735B / 3,832B full contribution, and the previously open 73B Animation
factory is now strict exact with all old 492 affected units protected.
Continue the 555B Player movement SSE spill and 3,111B Player main-frame
register/frame ABI; then the 12,140B Bullet command dispatcher,
39,470B Animation VM and 41,967B Enemy opcode parent. Do not infer exact giant parent bodies merely from
their exact children. All source/code work should be validated with
affected-only native replays, never automatic global cold replay.

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
