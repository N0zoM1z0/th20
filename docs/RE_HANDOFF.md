# TH20 native reconstruction — current working handoff

> Current workflow: follow the **Highest priority** section in `AGENTS.md`.
> Prefer affected exact comparisons and useful Markdown knowledge. Ordinary
> notes do not require full CI, native replay or document-hash/pin refreshes.
> Older broad validation instructions apply only when their impact is relevant.


**Reconciled 2026-11-11.** This is the short, current entry point for
the next agent, **not** the 100KB chronological checkpoint log.
Read [AGENTS.md](../AGENTS.md) first, then this page, the
[open Boss backlog](RE_OPEN_BOSS_BACKLOG.md), the
[native evidence index](EVIDENCE_INDEX.md), and the live
[game-authored exact ledger](../config/matches.csv) and
[strict unit graph](../config/match-units.toml). Earlier versions
of this handoff are preserved in Git history and dated detailed proofs;
old status labels are **historical observations**, not current facts.

## Locked target and current accepted coverage

| Property | Verified state at this checkpoint |
| --- | --- |
| Executable | `resources/th20.exe` — Japanese Steamless TH20 v1.00a, **1,858,560 bytes** |
| Immutable SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Embedded labels | Title/replay strings say **1.00c inside this same locked v1.00a file**; do not change targets based on the embedded label |
| Ghidra provisional candidates | **6,928 Ghidra candidates plus one original-only recovered 2,884B head** (not all Ghidra candidates have independent boundaries) |
| Accepted source-tracked units | **1,583 whole strict units**; `functions.csv` has **1,585** nonempty source-file rows |
| Canonical build providers | **437 pinned MSVC object + receipt pairs**; all currently protected |
| Credited *game-authored* whole-native exact | **774 distinct original function heads /265,580 `.text` bytes** |
| Whole game compiles, links or plays | **No** — native matching and standalone source coverage are different milestones |

Those figures are a **dated snapshot**, not a counter to increment
manually. `config/matches.csv` counts only independently proven
original game-authored exact function heads, while
`config/match-units.toml` also accepts separate compiler/STL code
and compared native data boundaries. Recompute the current status:

```sh
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

## Important recent *whole exact* Bosses — do not reclassify as open

- **Both Renderer Animation list-update Bosses now WHOLE STRICT EXACT:**
  `0x00449870` **508B/152-i386** and `0x00449B20` **511B/153-i386**,
  each with all 30 original E8 and five PE HIGHLOW fields, all native
  physical targets and complete **508/508 +511/511 relocated bytes**.
  The original `/sdl` ten-byte list preclear is naturally emitted by the
  one consistent `class IntrusiveList<Animation>` explicit specialization;
  the generic list type is unchanged. **82/82** earlier canonical units
  passed fresh cold replay in **22 affected objects**. [Whole native/ABI
  proof](ANIMATION_RENDERER_LIST_508_511_STRICT_EXACT.md). +1,019
  distinct game-authored bytes; no child was credited twice.
  The separately original [40B list constructor and 42B reset](ANIMATION_RENDERER_LIST_HELPERS_40_42_NATIVE_FRONTIER.md)
  are still NONEXACT; a new single-object double-tail hypothesis
  yields 40B/16 i386 and 34/36 ordinary bytes, with two register-direction
  bytes unresolved and no duplicate credit.


- Original D3D9 **alpha-fringe texture finalizer** `0x00451910`:
  **2,745B/759-i386 WHOLE STRICT EXACT**. Canonical native code
  covers **2,745/2,745** actual original machine-code bytes; the
  *complete* **2,798/2,798** COFF contribution also compares
  the real following **53B** alignment/jump/mapping tables and
  all **25** physical relocation roles (17 E8 +8 HIGHLOW).
  Only the 2,745B *code* is credited; the table is never counted as
  a second function. [Independent complete proof](ANIMATION_TEXTURE_FINALIZER2745_STRICT_EXACT.md).
- D3D9 texture upload **562B**, surface RECT copy **439B**, and
  random-color surface effect **581B** are **all separately exact**.
  [Uploader](ANIMATION_TEXTURE_UPLOAD562_STRICT_EXACT.md),
  [surface copy](ANIMATION_SURFACE_BLIT439_STRICT_EXACT.md),
  [surface effect](ANIMATION_SURFACE_EFFECT581_STRICT_EXACT.md).
- AnimationFile native loader **1,022B**, Renderer preload **269B**,
  find/wait **182B**, animation handle restart **118B** and
  file-table index **40B** are each independently exact.
  [Loader](ANIMATION_FILE_LOAD1022_STRICT_EXACT.md),
  [preload](ANIMATION_FILE_PRELOAD269_STRICT_EXACT.md),
  [find/wait](ANIMATION_FILE_FIND_OR_LOAD182_STRICT_EXACT.md),
  [handle restart](ANIMATION_HANDLE_REFRESH_118_29_STRICT_EXACT.md),
  [file table](ANIMATION_FILE_BY_INDEX40_STRICT_EXACT.md).
- Four original **139B/183B/183B/187B** texel alpha/RGB neighbor
  functions were *already exact* under historical REF-042.
  Their original game ownership was subsequently established at
  **medium confidence** by four physical E8 per format in the
  2,745B finalizer. The **692B attribution correction did NOT
  create new strict units**. [Original ancestry proof](ANIMATION_TEXEL_FOUR_GAME_ORIGIN_692_STRICT_EXACT.md).
- **InputDevice keyboard/DirectInput/XInput polling `0x00421B00`
  (3,490B/747-i386)** is also [WHOLE STRICT EXACT](INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md),
  not source-present/NONEXACT as a few historical `InputState.hpp`
  and source comments once claimed. Canonical unit: `input_device_poll`.
- **Particle-grid virtual event** `0x0045D060`: **51B/18-i386 WHOLE STRICT
  EXACT**, backed by the genuine 16B aggregate Timer layout and the already
  accepted folded 26B forwarding callee (never recredited). Original vtable
  slot4, sole E8, and the true 172B constructor's Timer call are all
  independently attested. [Complete native proof](ANIMATION_PARTICLE_GRID_EVENT51_AGGREGATE_TIMER_STRICT_EXACT.md).
- **Renderer Unicode formatted sprite text** `0x0044AC20`:
  **417B/114-i386 WHOLE STRICT EXACT**, with original lock-9 format and
  by-value callback dispatch. [Independent full-code/relocation proof](ANIMATION_RENDERER_FORMATTED_TEXT_417_STRICT_EXACT.md).
- Other very large already accepted native bodies include **11,110B
  ECL tick**, **3,735B Bullet emitter**, **3,159B quad submit**,
  **4,347B Mode8 draw**, **2,769B Mode6 draw** and
  **827B polygon dynamics**. Do not rely on dated documents saying
  these exact functions are `SOURCE-ABSENT` or `NONEXACT`.
  [Complete proof catalog](EVIDENCE_INDEX.md).

## High-priority unfinished work

**Attack large Bosses and small callees together.** The detailed
[open-function backlog](RE_OPEN_BOSS_BACKLOG.md) records actual
source files, native extents, unresolved compiler/ABI issues and
links to original PE evidence. The immediate priorities are:

1. **5,993B Animation Draw:** Latest maintained whole-function
   [mode35/45 native-site convergence](ANIMATION_DRAW_BOSS_5993_MODE35_MODE45_SITE_CONVERGENCE.md) retains the entire
   **5,993B/1,501-i386** and 49+31 original jump-pointer tables,
   with **113/123 E8 sites** and **26/32 in-body HIGHLOW sites** aligned
   (previously 86/123 and 23/32). Original call/data roles remain 123/32;
   **4,801/5,376** ordinary bytes match. The first inherited-scale x87
   return spill and mode45 float lifetime still differ: **NONEXACT**.
   **2,245B glyph mask compositor** (GDI bitmap/PMR growth),
   **2,227B Unicode glyph text core**, and **1,896B Card start**.
   These are all source-present but remain **NONEXACT**.
2. **336B ANM per-group parser**: now source-present, 336B/83 i386
   but **278/280 ordinary bytes**, with two outstanding stack/frame
   differences. Its 1,022B loader parent is already exact.
4. **586B centered Unicode Renderer text Boss:** `0x0044ADD0` now has
   [full natural C++20 source](ANIMATION_RENDERER_CENTERED_TEXT_586_NATIVE_FRONTIER.md)
   (594B/140-instruction compiler body versus original 586B/140,
   11 E8 and nine PE HIGHLOW). Only its float-width SSE temporaries
   remain NONEXACT. Both it and the separately [whole-exact 417B](ANIMATION_RENDERER_FORMATTED_TEXT_417_STRICT_EXACT.md)
   use one borrowed Renderer owner; the 417B consumer was rebuilt and
   remains strict exact. No credit is claimed for the 586B sibling.
4. Source-absent **12,140B Bullet command dispatcher**, **41,967B
   Enemy ECL opcode dispatcher** and **39,470B Animation VM**.
   Their independently exact descendants do not make these
   parents exact. The backlog also covers Player/particle/mesh
   frontiers and smaller exact-leaf opportunities. The 2,884B particle
   Update now has an independently verified **integer stage owner at
   +0x15E8**; all eight exact consumers survived a focused six-object
   replay; its nine handle and four stage array accesses now use genuine
   typed `std::array` indexing. The full 2,884B virtual Update has since
   been promoted to [maintained source](ANIMATION_PARTICLE_GRID_UPDATE_2884_TYPED_OWNER_SOURCE_FRONTIER.md),
   with four real Session→EffectInfo→AnimationFile→spawn protocols and the
   genuine 25B/19B animation accessors. The pinned candidate remains
   2,924B/760 i386, **NONEXACT**; its separately accepted 26B selector,
   83B spawn, 92B Stop and now independently strict **51B Event** sibling
   retain exact credit only for themselves. The new aggregate Timer owner
   preserves all eight exact group-dependent units after six scoped builds.
   A further [whole-code ESI/polar evaluation improvement](ANIMATION_PARTICLE_GRID_UPDATE_2884_ESI_POLAR_LIFETIME_CONVERGENCE.md)
   restored the native ESI lifetime and six exact E8 sites, reducing the
   nonexact 2,884B parent candidate from 2,969B to 2,924B while preserving
   all 99 native E8 roles and 25 PE HIGHLOW role destinations.

## Scoped compiler receipt integrity

The full 2,884B particle Update translation unit was moved from the
`probes/` tree to `src/` and is still NONEXACT. This touched no prior
canonical object's real compiler include closure. The receipt verifier
in [`scripts/project.py`](../scripts/project.py) now permits unrelated
source moves/additions while still SHA-checking the owned source, each
captured include, the pinned compiler, profile, target identity and whole
COFF object. It also rejects newly introduced source/header basenames
that might shadow a captured include. The focused regression
[`scripts/test-scoped-build-receipt.py`](../scripts/test-scoped-build-receipt.py)
uses only a disposable 26B exact object and covers **3 accepted /6 rejected**
scenarios (header/source/object/profile/target tampering rejected); native
`compare-coff-function.py --unit` continues verifying complete original
relocated bytes. This prevents unrelated source work from triggering a
whole-graph cold replay.

## Workflow and verification boundary

- **Every** code/metadata change starts from the live `git status`;
  staged, dirty and untracked work belongs to the active agent.
  Preserve unfinished work under `.analysis/` with its unresolved
  question if it cannot yet be admitted to maintained source.
- Read original PE SHA, whole native boundaries and physical
  E8/HIGHLOW **independently** before accepting source exactness.
  Keep actual ABI, C++ ownership, EH, vtable, COM and original
  data/code separation. No fake padding, copied machine bytes,
  assembly, inert locals, truncated function or duplicated game credit.
- For **native source, shared headers or exact-manifest changes**:
  identify actual affected providers and replay **only those sources**
  using `scripts/repo-python scripts/replay-exact-units.py --source
  src/Relevant.cpp`. Keep compiler work serialized at low priority;
  **never run an unfiltered full cold replay**.
- For **docs and regenerable-artifact cleanup with unchanged native
  graph**: **zero affected native units and zero cold replay**.
  Validate protected hashes, Markdown relative links and
  `git diff --check` instead.
- Commit meaningful checkpoints promptly and make multiple commits
  when warranted, always **`gpt-web: ...`**. Maintain English source
  comments, docs and commit messages.

## Storage and current maintenance

Keep the locked target/provenance, reference inputs, pinned tools, Ghidra project,
current source and ledgers, canonical manifest objects/receipts, and useful native
knowledge. Retain unresolved source drafts. The 417B formatted-text private draft is now
superseded by the maintained exact source, but remains as ignored investigation history. Historical snapshots,
comparison logs, cleanup reports and noncanonical objects are disposable unless
a specific open question needs a difficult-to-reproduce compiler context.
Document references do not confer retention. See [the workflow](RE_WORKFLOW.md).

Ghidra/JDK/Wine already use Factory. `.tools/msvc` is the locked 19.44 compiler
and SDK; `.tools/wine` is TH20's isolated mutable prefix. Factory's 14.10/v141
compiler is not interchangeable. See [shared tools](SHARED_TOOLS.md).

Current maintenance reduced the local tool payload to desktop x86 after testing
with surplus components temporarily unavailable. Native source, headers, profiles,
ledgers and target are unchanged: **zero affected canonical providers**. Six
representative providers were freshly compiled to private objects and all 18
complete units passed strict comparison; canonical objects/receipts were preserved.
Win32/DirectX, resource compilation and desktop CRT runtime checks also passed.
See [shared tools](SHARED_TOOLS.md) for retained components and the debug UCRT
runtime dependency. Resume reconstruction from the open Boss backlog.
