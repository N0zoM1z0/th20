# TH20 reconstruction — current handoff

## Start here

The active task is to complete origin/boundary review before returning to native
matching. Reviewed groups now include import-library stubs, CRT forwarding/runtime
bodies, x86 integer helpers, startup policy/TLS leaves and lock ownership. See the
[import entry table](IMPORT_THUNK_ORIGIN_BOUNDARY_REVIEW.md),
[CRT chains and width findings](CRT_FORWARDING_ORIGIN_BOUNDARY_REVIEW.md),
[integer ABI evidence](CRT_INTEGER_ABI_ORIGIN_BOUNDARY_REVIEW.md),
[startup defaults](CRT_STARTUP_DEFAULT_ORIGIN_BOUNDARY_REVIEW.md),
[lock ownership](CRT_LOCK_OWNERSHIP_BOUNDARY_REVIEW.md),
[global retirement](CRT_GLOBAL_RETIREMENT_ORIGIN_REVIEW.md), and
[locale implementation](CRT_LOCALE_IMPLEMENTATION_ORIGIN_BOUNDARY_REVIEW.md). The combined
integer divide/remainder helpers return quotient in EDX:EAX and remainder in
EBX:ECX; preserve that compiler-helper ABI in later consumers.
This checkpoint changes no canonical native inputs and has **zero affected exact
replay units**; existing canonical products retain their captured hashes.

Read [AGENTS.md](../AGENTS.md), then the focused notes for the selected owner.
Use the **`gpt-6.1-sol:`** commit prefix. Keep native writes and heavy jobs serial,
at reduced scheduling priority. Use `scripts/repo-python` for all repository
Python and `scripts/ghidra.py` for attested Ghidra work; do not use REA or IDA.

## Target and authoritative status

The target is Japanese TH20 v1.00a Steamless, `resources/th20.exe`, 1,858,560B:

`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`

Registry/package identity is v1.00a; embedded title/replay strings say 1.00c
in this same file. See [target provenance](TARGET_PROVENANCE.md). Preserve the
Steam-original backup as provenance, without substituting it as the target.
A complete playable reconstruction has not been built, linked or validated.

Read live counts with:

```bash
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

`config/matches.csv` records authored exact credit; `match-units.toml` records
complete comparison units and bindings. Source presence and origin are separate
ledgers. The tracked README SVG is generated from them by `scripts/progress.py`.
Its denominator is the currently confirmed authored set, not the whole game.

## Latest native checkpoint — Player state frame

`src/PlayerStateFrame4043.cpp` contains the complete state owner at `0x004F7430`.
Its 4,043B body, one NOP and seven switch pointers form a **4,072B** contribution.
All 3,256 nonrelocation bytes match. Complete independent relocation bindings
remain open, so the parent is **source-present, NONEXACT**, with no canonical
unit. See [native ownership and compiler findings](PLAYER_STATE4043_NATIVE_FRONTIER.md).

`src/PlayerStateNativeAccessors.cpp` adds thirteen exact physical helper units.
The 68B Angle method remains under origin review. The 22B Player state setter
shares an existing FunctionChain physical head and receives no duplicate credit.
The power-consumption method produces a full integer result: using `bool`
changes two native opcode bytes. Feedback update returns `void`, while the
shot-controller update returns an integer. See
[the complete helper and return-ABI proof](PLAYER_STATE_NATIVE_ACCESSORS_STRICT_EXACT.md).

Nine declaration headers changed. The captured closure passed **1,146/1,146
existing units from 313 fresh providers**; the thirteen new units passed from
one additional provider. No old extent, relocation or profile was changed.
The complete parent also compiled and retained its private candidate's full
contribution and relocation roles. This establishes no parent exact credit.

Products are in `build/gpt61-player-state-canonical/`. Preserve both
`.analysis/player-state4043-session/` and `.analysis/player-state4043-abi/`:
attested queries, private source/header hypotheses, ABI negative controls,
complete comparisons, affected include closure and replay log are there.
Earlier Player canonical products remain intact.

## Next useful work

Continue origin/boundary review in bounded groups. All current Ghidra thunk
candidates have reviewed origins. Instruction-level references and complete
CRT startup objects resolve `0x00543B7E` and the folded zero defaults at
`0x00543B83`; function-level caller queries had missed their unowned startup
call sites. Use `xrefs_to` when an empty call graph conflicts with other evidence.

The false 66,925-byte span at `0x005419AC` is resolved: its 31-byte STL destructor
conditionally tail-transfers to the separately tracked nine-byte UCRT
`_unlock_locales` at `0x00551F10`. The lock and adjoining global retirement
protocols are now reviewed. All six
newly inventoried startup/exit callbacks have library/compiler origins. A single
private SDK-header probe emits the original 80-byte `std::locale` destructor at
`0x004F5600`; its object/receipt remain in `build/gpt61-origin-locale/`. The exit
controller retains its complete 29-byte cookie/EH handler and 36-byte metadata.
No canonical native input changed; exact replay scope remains zero.

The `_Locimp` lifetime, global publication and `_Locinfo` switch/restore methods
are reviewed, including `_Init`'s 8-byte cleanup / 5-byte alignment, 29-byte
handler and 44-byte EH section. A separate pinned SDK-header probe emits the
original 42-byte `_Yarn<char>::_Tidy`; its private object/receipt are retained
beside the locale probe. Source-present and canonical exact credit are unchanged.

Next review the remaining facet virtual methods bound by the observed `_Locimp`
vtable: `0x00484700` and `0x004FBD80`, plus the `_Facet_base` deleting entry at
`0x004F71B0`. The original RTTI, source declarations and table slots are captured
in the locale note/session. Other pending conversion helpers begin at
`0x00541D3B`; use independent archive symbols and full native control flow.
Generate current counts from the ledgers.

The following native frontiers remain available after review:

1. Resolve independent Player state-frame bindings, especially the zero Vector3
   at `0x00572664`. Its only known reference is in this same root; reading that
   field or finding twelve zero bytes does not independently bind its address.
   Existing scalar/global aliases and remaining member dependencies also need
   complete bindings before creating a canonical parent unit.
2. Recover the separate **663B death-entry owner at `0x004F8420`**. The existing
   attested `owner-callbacks.txt` under the Player session contains its native
   behavior. Preserve the ordered controller notifications, two option sweeps,
   animation-handle cleanup and timer resets. Bomb, Identifier32 damage-flag,
   shot and feedback implementations are other remaining state dependencies.
3. For another bounded frontier, use [the backlog](RE_OPEN_BOSS_BACKLOG.md).
   The [5,993B Animation Draw source decision](ANIMATION_DRAW_BOSS_5993_MODE45_MODE46_RETURN_FRONTIER.md#2026-11-26-native-width-preparation-and-one-zero-result-return)
   is current: candidate 5,969B, four cases account for the full 24B deficit.
   Two first-getter stores and four register reloads remain open. Reuse its
   failed controls and compiler-context evidence rather than repeating them.

The 3,111B Player main, 555B movement, Glyph compositor/text core, Card start,
827B polygon updater and 1,486B rotated projection are now whole exact. Use
[the evidence index](EVIDENCE_INDEX.md) to find their current proofs; historical
NONEXACT notes are superseded. [Source navigation](SOURCE_MAP.md),
[architecture](ARCHITECTURE.md) and [workflow](RE_WORKFLOW.md) have separate roles.

## Protected local products and cleanup boundary

Preserve the target, supplied `../game_exe/`, `.tools/`, game-specific Wine
state, `ghidra-project/`, Factory runtime directories and every canonical
object/receipt, including superseded canonical directories. Keep private native
source, attested exports and useful open-question controls under `.analysis/`.

Completed investigation snapshots, bulk reference-audit exports, old validation
logs and ledger baselines have been retired. Noncanonical compiled batteries,
portable host binaries and duplicate generated copies were removed. The private
Player state sessions remain; its corrected-ABI parent object is retained under
`build/gpt61-player-state-abi/`. Draw keeps the current and restored-order parent
objects, compiler/link calibration controls and debug metadata; the source
verifier's `build/core835-probe/` output is also retained. Other ordinary probe
objects can be rebuilt when needed. Historical scratch paths are not a retention
requirement; use canonical source/units and the focused findings for closed work.

For native changes, inspect all live Git dirt and run the preflight in AGENTS.
Derive affected providers from captured include closures and manifest
relationships. Replay only explicit source filters or individual units,
including full owned extents and relocations. Keep `config/claims.csv`
header-only. Never edit historical receipts to manufacture a pass.

## Earlier native investigation — 2026-11-27

The historical native-work instruction was: continue substantive TH20 reconstruction on both large boss functions and small leaf functions, do not avoid pre-existing dirty work, make multiple checkpoints after real progress (the current required prefix is `gpt-6.1-sol:`), use targeted rather than full cold replay, and reconstruct natural C/C++ rather than assembly or padding. The active large-function investigation is `AnimationPoolOwner::draw` at `0x00443880`; its current residual and compiler evidence are recorded in `ANIMATION_DRAW_BOSS_5993_MODE45_MODE46_RETURN_FRONTIER.md` and `ANIMATION_DRAW_BOSS_C2_DEBUG_TRACE.md`. The TH10-style C2 debugger has now reached the x64 `InvokeCompilerPassW` entry and observed typed in-memory IL arguments. The actual codegen/register-allocation entry is not yet identified, and no exactness claim is made. A separate StageResource leaf has since advanced: `StageResourceOwner::set_primary_rotation_flag` at `0x00477790` now uses a layout-preserving bitfield alias and strictly replays 45/45 bytes; its shared-header dependents passed targeted replay and compile smoke checks. The 2,884B particle-grid Update remains source-present/nonexact at 2,875B/767; its polar getter order is retained while one `float angle` is reused, reducing E8 offset delta from 883 to 440 (first 20: 84). The candidate frame is 0x194 versus native 0x19C; vector roles remain mapped from original call operands with a four-byte local displacement. C2 RVA `0x1d01a8` is argv setup (22 wide arguments), while RVA `0x1d1e20` is a six-record VCTIP instrumentation writer, not lowering. The bundled VCTIP server cannot run in this Wine prefix because Wine Mono is absent; the actual register-allocation/codegen path remains unidentified.

**2026-11-27 C2 worker/typed-IL continuation:** The VCTIP local consumer now
allows the real pinned compiler invocation to complete and capture the full
five-segment `-il` object (lengths `0x346DB/0x1E321/0x6B6C5/0x3AAF/0x760D1`).
C2 creates eight `_beginthreadex` workers; the generic worker entry candidate
is C2 RVA `0x36CB38`, which dispatches through a callback pointer at worker
context `+0x20`. The callback target is not yet decoded. Continue from
`ANIMATION_DRAW_BOSS_C2_DEBUG_TRACE.md`; do not label the worker trampoline as
register allocation or lowering. The large draw body remains 5,969B versus
5,993B native and NONEXACT.
