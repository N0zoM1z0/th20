# TH20 reconstruction — current handoff

## Start here

The active task is to complete origin/boundary review before returning to native
matching. The [evidence index](EVIDENCE_INDEX.md) links the reviewed import, CRT,
startup, lock, locale, facet, conversion and stream-lifetime groups. The latest
review covers [UCRT libm error records and full switch ownership](CRT_LIBM_ERROR_SUPPORT_ORIGIN_REVIEW.md).
The full 660B contribution includes 539B/143 instructions, one NOP and both
60B tables, with both REL32 fields and all 37 DIR32 roles. Void cdecl/32B record types,
all selectors, guarded callbacks and distinct errno/underflow/default paths
remain intact. Linked literal/BSS instances are retained as observations,
separate from independent canonical source-unit anchors.
This classification-only checkpoint changes no native graph;
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

Continue origin/boundary review in bounded groups. Use instruction/data
references when Ghidra's function graph omits original callers; the pointer
initializer and recovered heap callbacks are retained examples. Keep complete
shared owners, tails, alignment and owned metadata in each reviewed scope.

The current proof is in `.analysis/origin-boundary/libm-error/`: complete
code/tables, attested listing and full CodeView error/record/void metadata.
It reuses libm_error.obj in `log10-ceil/`; the separate 43B setter remains
unlocated. The two BSS cells are observed zero in the image, without a
reviewed runtime writer.
Next review the precise log10/CI Pentium4 pair's remaining data and protocol
scope. `log10-ceil/` retains complete 688B/656B code identities, two full
1,040B tables and both identical 256B constant banks at `0x005A2650` and
`0x005A2FE0`. The precise contribution contains 675B code and two LEAs/13B
alignment. Keep observed linked bank instances separate from any future
independent canonical binding; the earlier origin review is still pending.
The existing ceil/x87 review and supplemental 79B intrinsic prefix remain
in the same directory. If the pair needs further evidence, the real sptype,
except1 and frnd providers at `0x005524B0`/`0x00553A00`/`0x00564240` are
separately pending bounded math scopes.
`fenv-environment/` retains complete types/state/packing and mask inference;
the 26B status-from-mask helper has no full ordinary location. `fp-fltout/`,
`fp-strflt/` and `fp-dispatch/` retain full fraction/carry/format evidence.
`format-parse-integer/` retains the complete no-whitespace parser/source proof;
`format-buffer/`, `format-types/` and `format-decimal/` retain the reviewed
capacity/transfer, length tables and decimal insertion/cropping protocols.
Keep unlocated wide parser variants and generic jump helpers separate from
those owners. The char width helper still takes
the original unused 64-bit options argument.

The [evidence index](EVIDENCE_INDEX.md) links the completed string/memory,
purecall and exception owner groups to their focused notes and private proofs.
Preserve `bad-exception/` and `build/gpt61-origin-exception-copy/` for natural
header variants and the rejected scalar-alias hypothesis. Ghidra listing
omissions remain recorded with the complete bounded decoded supplements.

The cached-locale probe in `cached-locale/` emitted no object: installed SDK
source omits FFS/state-isolation private headers and conflicts on __p__fmode
under the attempted build configuration. Keep both failed logs and inputs;
do not repeat that compile until those inputs are resolved. The target's 91B
updater now has a complete output.obj match; the 89B cvt.obj alternative
remains retained rather than replacing the target extent.

The runtime reporter's banner, unknown-program text, library caption and
abort message are absent in both ASCII and UTF-16. Larger SDK reporter
sections have no complete match; the already reviewed abort follows the
release path with no debug-only message call. Do not keep searching nearby
code for that reporter without a new retained caller or string reference.

Continue with a bounded unresolved CRT owner, using archive members and
actual callers before relying on a familiar Ghidra name. The frame owner
closure is retained through the focused notes and private reports; keep
unlocated weak forwarding/type-info helpers separate from those complete
physical owners. The bad_exception proof independently binds TypeDescriptor
`0x005B4030`, ThrowInfo `0x005AC1FC` and its real constructor/destructor
callbacks. Base exception and bad_exception deleting implementations have
different target entries despite identical optimized archive shapes.

The retained 173B memchr member has no complete ordinary-byte match. The five
attempted copy/concatenation archive members in `string-copy/` contain six
function shapes without complete matches. Reuse those negatives rather than
assigning familiar names or repeating the same scans without new evidence.
The same-shaped bad_alloc constructor at `0x00540D24` retains its previous
class identity.
The 14B secchk signature independently locates the cookie check at
`0x005429EE`; its own failure-owner review remains pending. std type-info
name/hash/list-cleanup, application verifier and termination query remain
pending.

Unlocated VCRT thread/critical-cleanup wrappers, translator setters and
ReadNoFence lookalikes at `0x0040B2A0` remain unassigned. The similarly named
winapi_thunks.obj module-handle candidates and downlevel weak FLS accessors
receive no credit from their ordinary matches in other CRT groups. The SDK
beginthread body remains unlocated; its endthread lookalikes actually call
invoke_watson.

The SDK's unreferenced 56B badioinfo data and separate
34B standard-ID helper have no complete target match; neither receives
ownership credit. The fmode initializer also has no complete location yet.
The aligned/catch-GS frame variants remain unlocated; their ordinary substrings
do not receive overlapping physical credit.

The [evidence index](EVIDENCE_INDEX.md) links closed CRT groups and their
focused findings. Preserve `.analysis/origin-boundary/` and all useful SDK
probes/receipts under `build/gpt61-origin-locale/` and
`build/gpt61-origin-allocation/`: Locale, Yarn, Facet and BadArray retain natural
compiler evidence. The math correction's fresh products and negative controls
are listed above. Closed-review history and byte partitions belong in those
focused notes, rather than a cumulative handoff log.

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
