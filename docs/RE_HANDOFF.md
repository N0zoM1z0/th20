# TH20 reconstruction — current agent handoff

**Last reconciled: 2026-10-29, CORE/RECON-750.** This file is a
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
| Source-present function mappings | **1,201**, all origins |
| Configured whole-native strict units | **1,203**, including library/compiler |
| Distinct canonical MSVC object + receipt providers | **245** |
| **Game-authored original whole-body exact** | **556 distinct functions / 186,645 disjoint original `.text` bytes** |
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
| Game PBG/Fog/geometry/PlayerShot/Session/Graphics whole methods | **Nine complete original game-native functions /1,686 newly accepted disjoint exact bytes**, [native source, original PE HIGHLOW, 31 E8 and actual original callers proof](GAME_FOG_GEOMETRY_PLAYER_PBG_SESSION_1686_ORIGIN.md). Typed original Player damage-to-shot chain **55B -> 38B -> 246B** completed, true 1,074B original Fog boss calls two separate 226B operations, 313/324B exact polygons call 229B normalization, 346B exact PBG File opens call 248B CP932 path converter, 941B Graphics ctor calls 204B flags, real 16B compiler dynamic initializer calls 214B Session ctor without extra helper credit. All **8 relevant MSVC source objects /121/121 old exact units scoped cold rebuilt**, including fixed stale Fog/geometry receipts, never full replay. |
| Game Animation, ECL, Item and Player complete native child methods | **Seven whole-game original functions /1,283 distinct strict exact original bytes**: [243B Animation child-list begin, 241B recursive find, 217B layer, 182B ECL async spawn, 147B Item spawn-many, 133B PlayerFeedback constructor, 120B ScriptStack local](GAME_PLAYER_ANIMATION_ECL_SEVEN_ORIGINAL_1283_EXACT_ORIGIN.md). Newly attested original PE **30 E8/13 HIGHLOW**, real previously exact 967B Enemy animation, 878B RenderMesh, 11,110B ECL Runtime, 419B Bullet cancel, 794B Player constructor and ten ECL arguments caller chains. False earlier assumption that the ECL interpolation setter was Animation::set_layer **rejected** from physical E8. Only **7 bounded source cold objects /66/66 exact units** replayed, original giant parents remain NONEXACT. |
| Laser parameters and controller protocol | **Ten complete originally game-owned Laser function bodies / 936 disjoint native strict exact bytes**, [four LaserType0/1/2/3 parameter construction and destruction pairs plus real context selection and lookup](LASER_PARAMETERS_936_ORIGINAL_GAME_EXACT_ORIGIN.md). Independently decoded ten original bodies, **17 E8/3 true PE HIGHLOW**, physical 12,140B Bullet command case-27 and 41,967B Enemy opcode dispatch callers; exact 1,738B Dialogue constructor independently calls Laser controller lookup. One affected source cold replay **12/12 strict**, but the previously game-credited 179B controller constructor and 263B reset function are **not** counted again. Both original giant dispatchers remain NONEXACT. |
| Enemy and ECL original lifecycle | **4 complete game-authored, strictly exact functions / 762 disjoint original bytes**, [original EnemyController::create 155B, Enemy::initialize 222B, EnemyState::advance_scripts 168B and EclManager::tick 217B](ENEMY_ECL_LIFECYCLE_762_ORIGINAL_GAME_EXACT_ORIGIN.md). Independently decoded original **29 E8 /4 PE HIGHLOW** sites, original 12,140B (NONEXACT) dispatcher to Enemy creation, original 1,371B exact Enemy::defeat to ECL Manager, and both original ECL Manager calls to the separately exact 11,110B Runtime. Targeted-only receipt refresh for two existing original ECL native objects, zero broad replay or duplicate original code credit. |
| ECL native typed arguments and tagged ScriptStack | **Twelve distinct complete game-authored whole original native methods, 2,073 disjoint strict exact bytes**, [complete original ECL argument and custom ScriptStack provenance](ECL_ARGUMENT_TAGGED_STACK_2073_ORIGINAL_GAME_EXACT_ORIGIN.md). Independently verified original **31 E8/9 PE HIGHLOW** fields, 185 physical original calls from the already exact 11,110B interpreter into the 15-method ECL argument/stack protocol, and 12 from the separately exact 923B call_into. The three prior exact siblings and both giant original full parents are **not recounted**; affected-only two-source cold replay **12/12 and 3/3 strict**, no full cold replay. |
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
| 0x004F9C30 Player main frame | **3,111B, 783 x86** | Complete maintained [source](../src/PlayerMainFrame.cpp) now emits **3,114B / 783 x86, all 783/783 native mnemonic kinds in original order**. [Direct original PE proof](PLAYER_MAIN_NATIVE_SCRIPT_INDICES_AND_OPTION_LOOPS_3111.md) fixes a **real gameplay off-by-one**: original animation_scripts[1..4] at Player+0x22A0 +{4,8,12,16}, not previous [0..3], saves one begin/end result per 10/12-entry option group before iteration and uses native 8B history source-before-destination assignment. Previous [X-then-Y motion order](PLAYER_MAIN_3111_NATIVE_XY_ACCUMULATION_ORDER.md), [two focus DWORDs](PLAYER_MAIN_FOCUS_AND_HISTORY_NATIVE_LIFETIMES.md), [9x2 direction table](PLAYER_MAIN_FRAME_NATIVE_9X2_DIRECTION_TABLE.md), [signed speed](PLAYER_MAIN_FRAME_3111_INPUT_AND_SIGNED_SPEED_NATIVE_FRONTIER.md) and [typed 45B handle equality](PLAYER_ANIMATION_HANDLE_TYPED_EQUALITY_NATIVE_FRONTIER.md) remain. All 67 true E8 callee roles independently reconciled; 67 REL32/37 DIR32 by count only. Exact original byte/relocation field positions still differ, **NONEXACT**, zero parent byte credit. Additional [independent whole native semantic operand proof](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md): **164/164 nonrelocated ordinary immediates and 67/67 positive nonstack game member displacements identical**; exactly seven original/candidate ADD register encoding length differences sum to **+3B**, but many other original stack registers/relocation fields still differ. Four complete MSVC /fp-/sdl variants confirm profile invariance. [Complete original 9×2 direction .rdata and 37/37 actual main HIGHLOW source roles](PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md) now have real new src/PlayerDirectionTable.cpp with **72/72 exact original data bytes**, genuine C++ symbols on both whole-frame table references, 34 original globals and 7-byte effect literal independently attested. The 72 bytes are game DATA, not added to .text exact function credit. |
| `0x004FFA10` Player movement | **555B, 135 x86** | [Complete source](../src/PlayerMovement.cpp) emits **561B /136**, all original mnemonic kinds but one unwanted 6B SSE spill before `cvttss2si esi,xmm0`; not fixed by `/fp` changes or SSE intrinsics. [Full immutable PE history](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md). **NONEXACT**. [Independent original native 128 denominator identity](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md) now uses the real `native_128` symbol at original `0x0056CD98` for both trailing world coordinate divisions, rather than compiler-private `__real@43000000`; all 561 code bytes and 27 field locations are unchanged, only two COFF symbol names improved, still **NONEXACT**. |
| `0x0047DB70` Bullet drawing group | **273B** | [Complete source and extra SSE spill frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md); compiler currently emits ~283B. **NONEXACT**. |
| `0x004A4190` Enemy mesh | **1,649B** | [Whole C++ owner and original transient lifetime](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md); existing source is nonexact, do not forge an unused byte. |
| Original Bullet 12,140B direct-call source coverage | [Independent complete original 210-E8 source-role audit](BULLET_12140_E8_203_7_SOURCE_CLOSURE.md): currently **203/210 original E8 call occurrences bind canonical strict native heads**. Exactly seven E8 physical targets are not yet canonical: original **37B game animation link/resource cleanup**, three original **21B Animation+0x499 flag setters** for 0/1/2, original **22B Animation interrupt(2)** wrapper and two compiler helpers **14B security-cookie /31B __allshl**. Those five true game candidates total **122B**, but NONE is credited until a complete natural exact C++ source exists. Original three switch tables remain 53/53 PE HIGHLOW; **entire 12,140B parent still source-absent NONEXACT**. |
| 0x0047DCF0 Bullet::run_extended_commands | **12,140B / 2,490 original x86** | New [independently original 34+8+11 nested-switch full-case CFG](BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md) corrects the older [primary-only 34-case frontier](BULLET_12140_ORIGINAL_34_CASE_DISPATCHER_FRONTIER.md). Entire real PE has **53 original post-RET switch-table HIGHLOW** across 212B, 38 body HIGHLOW, 210 E8; **2,387/2,490 native instructions and 204/210 E8 are case-reachable**, remaining six native E8 belong to actual command prelude/security epilogue, zero unresolved nested indirect branches. Main cases 5/14/28 share default; nested 8-way command 4 and 11-way command 9 sprite/style are authentic integer selectors (Ghidra float-case decompiler types were wrong). Two independently strict large parents 3,735B emitter and 1,846B Bullet physics physically E8-call this genuine Bullet method. **No complete maintained C++ body yet, source-absent, NONEXACT and zero exact body credit.** Independent [three whole exact native Vector3 interpolation setter roles and physical folded-compatible 35B Motion alias](BULLET_VECTOR3_INTERPOLATION_95_EXACT_FOLDED_ALIAS.md) add **95 original disjoint game code bytes** through three original PE call sites, with only **two** new Interpolation.cpp canonical strict units; actual source now 43/43 exact. Giant original 12,140B remains NONEXACT. [Native PMR vector copy/dtor helpers](BULLET_COMMAND_PMR_VECTOR_121_20_LIBRARY_EXACT.md) now have 121B/20B strict original STL template code (two added exact canonical units in existing same native source, 4/4 scoped replay). These are library origin and do not add game-authored code credit; original 470B/32B deeper helpers and entire 12,140B game dispatcher remain NONEXACT. [Original PMR Bullet STL C++17 helper recovery](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md): genuine 200B capacity reserve, 196B EH-aware uninitialized copy and 73B memmove are now completely **469B whole native exact**, alongside previous 121B copy and20B dtor. Existing one source owner C++17 **7/7 strict**. Original 470B counted-range still **NONEXACT**: original actual E8 at 0x0047A99F invokes the exact std::is_constant_evaluated 7B code, absent from 458B C++17/current STL implementation; no fabricated call. Library originals are excluded from game-authored exact bytes. [Original seven exact Bullet Vector3/Float interpolation tangent, Timer-reset and mode methods](BULLET_199_INTERPOLATION_TANGENT_TIMER_EXACT.md) add **199 distinct original game code bytes**, with genuine complete 12,140B Bullet E8 receivers +0x420/+0x474. Shared Interpolation.hpp/Interpolation.cpp updated naturally and 114 affected native source objects /542 old units strict exact preserved, including 25 independently original-PE-proven string renames. Entire 12,140B parent still source-absent NONEXACT. [CORE/EXACT-749 original Bullet shared_ptr ownership](BULLET_SHARED_PTR_LEGACY_CTOR_100_LIBRARY_EXACT.md) adds a whole original 46B shared_ptr<EtamaArgInf> move constructor and whole original 54B _Ptr_base move helper, with real PE Bullet 0x0047F935 -> constructor -> helper E8 chain and separate exact 63B move assignment as caller. Single actual shared_ptr legacy source 3/3 strict; **100B library-origin, no added authored code**, original giant 12,140B remains NONEXACT. |
| 0x0048C010 Enemy ECL dispatcher | **41,967B /8,896 original x86** | [Independent original 704-byte opcode compression and 174 actual PE HIGHLOW code pointers](ENEMY_41967_NATIVE_LASER_OPCODE_CASE_GRAPH.md). Physical opcodes **702/703/711/713** map to selectors 154/155/163/165 and true LaserType0/1/2/3 original ctor/dtor branches, with 153/176/141/137 bounded native x86 heads and genuine original E8 destinations. Their ten separate Laser game classes/controller functions are already **936B whole native strict exact**, but the enclosing entire Enemy Boss remains source-absent **NONEXACT** and gets no code credit; [prior historical layout](CORE_ENEMY_DISPATCH_LAYOUT.md) retains dated host-probe context. |
| `0x0042B5D0` Animation VM update | **39,470B** | **NONEXACT** giant original parent; native-exact child parsers, loaders, reset and frame helpers cannot be counted as this body. [Animation owner map](SOURCE_MAP.md). |

**Near-term priority:** Bullet emitter remains fully strict exact at
3,735B / 3,832B full contribution, and the previously open 73B Animation
factory is now strict exact with all old 492 affected units protected.
Continue the 555B Player movement SSE spill and 3,111B Player main-frame
register/frame ABI; then the original 12,140B source-absent Bullet 34-command sequencer,
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
