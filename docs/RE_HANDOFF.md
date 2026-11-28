# TH20 reconstruction — current handoff

## Start here

The active task is to complete origin/boundary review before returning to native
matching. The [evidence index](EVIDENCE_INDEX.md) links the reviewed import, CRT,
startup, lock, locale, facet, conversion and stream-lifetime groups. The latest
review covers [x87 state and MXCSR recovery ownership](CRT_FLOAT_STATE_ORIGIN_BOUNDARY_REVIEW.md).
Five existing candidates and three recovered partitions account for complete
floating-state contributions, including the DAZ setter's previously unlisted
SEH filter/handler and full scope table. This classification-only checkpoint
changes no native graph;
exact replay scope is **zero units**, and all 2,151 protected hashes are unchanged.

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

## Latest native correction — math-adapter bindings

`GraphicsCameraTanAdapter35.cpp` now calls `std::tan(double)` at `0x00439850`.
`ScalarMath.cpp` binds `arccosine` at `0x00439760` to `_acos`/`0x0054FEB0` and
`arctangent_single` at `0x00439790` to `_atan`/`0x0054FF00`. The old ordinary
bytes could not distinguish their incorrect external names. Full independent
CRT sections now establish the identities, and fresh complete canonical replay
passes: **84/84 affected units from 31 fresh providers**. The Animation VM's
runtime contributions agree before/after the three expected call-name
substitutions; the VM remains NONEXACT. All three wrapper origins remain
unknown/review. The existing true square-root wrapper and two-argument atan2
retain their bindings.

Preserve `build/gpt61-origin-tangent-canonical/`, the before/after VM objects in
`build/gpt61-origin-tangent-{before,after}/`, and
`.analysis/origin-boundary/{x87,tangent-binding}/`. The latter holds captured
include closures, old product hashes, the 84-unit replay log, consumer comparison
and the old wrong-symbol source/object negative case. Do not overwrite old
receipts. The two public camera verifiers read current manifest object paths.

## Retained native frontier — Player state frame

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
candidates have reviewed origins. Use `xrefs_to` when an empty function-level
call graph conflicts with original startup references. Preserve external tails:
the corrected 31-byte `_Lockit` destructor at `0x005419AC` conditionally transfers
to the separate nine-byte `_unlock_locales` at `0x00551F10`.

Keep the private evidence in `.analysis/origin-boundary/` and the pinned SDK
probes/receipts in `build/gpt61-origin-locale/`: `Locale.obj` emits the original
80-byte destructor, `Yarn.obj` the 42-byte cleanup, and `Facet.obj` eight complete
virtual/lifetime contributions. Reuse those results for unchanged inputs.

The allocation review resolves the false 3,046-byte span at `0x00542E42`:
the full aligned-new parent is 52 bytes, and its shared 28-byte bad-array throw
helper at `0x00543A0C` is now separately inventoried. Both allocation parents'
failure edges, two throw-helper INT3 bytes and all ten shared type records are
retained. One natural pinned-header probe emits the original 36-byte bad-array
default constructor; preserve `build/gpt61-origin-allocation/BadArray.obj`, its
receipt and `.analysis/origin-boundary/allocation/` alongside the earlier probes.

The remaining malloc/aligned-delete heads and complete new-handler state owner
are now reviewed. The 317-byte shared code section includes 57 INT3 bytes and
two EH-only three-byte prefixes at `0x0055290B`/`0x00552979`; the complete SEH
section is 60 bytes. Both prefixes fall through to existing nine-byte unlock
entries. The missed legacy overload at `0x00552990` passes the security-cookie
value to the setter; preserve that operand. Private `reviewed-handler.json`
captures the complete text, codecs, wrappers and scope-table comparisons.

The four oversized spans beginning at `0x0054FEB0`, `0x0054FF00`, `0x0054FFB0`
and `0x00550130` are now resolved as acos/atan/sin/floor entries and independent
fallbacks. The complete eight code sections and five literal sections are
retained in `.analysis/origin-boundary/disjoint/`. Atan's five-byte instruction
at `0x0055A8F6` remains inside the full 139-byte default body. Floor's earlier
64-byte compatibility dispatcher at `0x005500F0` is separately inventoried.

The SSE groups beginning at `0x0055A2E0`, `0x0055A920` and `0x0055B240` are
also reviewed through complete Pentium4 sections, both trailing NOPs and all
14,880 bytes of local/shared tables. The six-byte stack-input heads fall through
to the separately owned kernels. Intrinsic adapters consume ST(0) and create the
stack argument view; kernels need that view as well as XMM0/XMM7. Reuse
`disjoint/reviewed-sse.json` and its original listing for unchanged inputs.

The common x87 support and tangent group are now reviewed. The false 755-byte
span at `0x0055B518` is a six-byte head, followed by a separate 564-byte shared
kernel, fourteen alignment bytes and independent common helpers. Reuse
`x87/reviewed.json`, including all 5,929 constant/table bytes. The shared
one-/two-argument math error entries at `0x005640B7`/`0x005640A0`, `_87except`,
mask/raise/errno handlers and four encoded-callback methods are also reviewed.
Preserve `math-error/` with its complete 2,231B code contributions, 40 constant
bytes and original callback references. The four x87 state helpers and MXCSR
setter are now reviewed: internal control/status words return with sign
extension, and the DAZ trial owns a complete SEH filter/recovery path. Preserve
`fp-state/`, including all five code sections, extended literals, initialized
cache and 28B scope table. Four nonoverlapping partitions retain all 222B of the
setter owner. Next inspect the actual public
control/status owners using the retained `ieee87.obj`; several helper sections
had no full ordinary-byte location and must not be assigned guessed addresses.
Underlying heap entries at `0x005584C0`, `0x00554310` and `0x00554330` remain
another bounded allocation frontier. Reuse established runtime bindings.
Use independent archive symbols and complete original control flow, including
nonreturning paths and owned EH. Generate current counts from the ledgers.

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
