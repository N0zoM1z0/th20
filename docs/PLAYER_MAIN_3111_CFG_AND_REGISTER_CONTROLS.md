# Control flow and registers in the Player main frame

Every internal branch in the current Player main frame targets the same
instruction ordinal as the original; all EBP/ESP memory operands also agree. Its remaining ordinary
instruction differences are confined to EAX/ECX/EDX-family register encodings.
The complete method is still **NONEXACT: 3,114B/783 instructions versus
3,111B/783 native instructions**. No source or shared header was changed.

The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The fresh `PlayerMainFrame.cpp` object uses locked MSVC 19.44.35211 x86 with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc`.

## Complete-function constraints

| Check against the whole original method | Fresh result |
| --- | ---: |
| Instruction mnemonics in ordinal order | 783/783 |
| Internal direct jump targets, compared as instruction ordinals | 106/106 |
| EBP/ESP-relative operands: base, index, scale, displacement and width | 327/327 |
| Ordinary nonrelocated immediate values | 174/174 |
| Direct-call roles, using independent canonical/folded/known-source anchors | 67/67 |
| Physical data-reference roles and field positions within paired instructions | 37/37 |
| Ordinary instructions with different actual bytes | 327 |

The 174-immediate comparison includes ten zero values in instructions whose
memory addresses contain DIR32 fields. The earlier 164-value audit excluded
those entire instructions. Relative branch displacements are checked through
their actual destination ordinals; they are not treated as ordinary constants.

All ordinary mismatches use different EAX/ECX/EDX-family registers, including
two CL/AL differences. Other register classes, nonrelocated operands and
instruction encodings agree under that explicitly limited classification.
The seven accumulator ADD encoding differences documented in
[the earlier audit](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md)
still account for the net three-byte size increase. Actual register values
and relocation positions must match before exact acceptance.

The first ordinary mismatch is at native +0x1A2, immediately after the
ignored `Timer::equals(8)` call: original `mov eax,[ebp-4]`, candidate
`mov edx,[ebp-4]`. The next ADD therefore uses a longer generic-register
encoding. The whole frame allocation remains `0x108` in both bodies.

The 37 data roles were independently rechecked with the existing direction
table checker: 34 established global references, two table references and
the actual seven-byte `effect` literal. The old data probe was absent, so
only the 72B table source was rebuilt for this check. The 555B movement
callee remains nonexact and is bound as a known physical source owner;
its call identity does not establish its exactness.

## Bounded source and ABI controls

| Private control | Complete main-frame result |
| --- | --- |
| Explicit void discard or pointer receiver | Same 3,114B code and relocation field layout |
| Inline or constexpr comparison definitions visible in the translation unit | Same 3,114B code and relocation field layout |
| Predicate compared with `false` or zero | Same 3,114B code and relocation field layout |
| Operator declarations/calls with the same if-initializer grouping | Same 3,114B code; only eight comparison symbol names change |
| Separate discarded operator-expression statement | 3,115B/784, adding an unwanted NOP |
| Predicate compared with `true` | 3,115B/783, different comparison encoding |
| Byte-return predicate declarations | Main still 3,114B; invalid native callee bodies |

Where compiler-local `$SG` labels changed, the real literal payload and all
other relocation properties were compared. The inline and constexpr bool
definitions also reproduce both complete 46B native comparison callees.
The byte-return hypothesis emits 40B callees despite preserving the main
caller's code. It is rejected against the complete native 46B bodies; the
validated public Timer ABI remains unchanged.

Earlier comma, statement grouping, receiver-local and float/profile controls
are retained in `.analysis/core705-player-native-timer-lifetime-results.json`
and the linked earlier audit. Reuse them instead of repeating those trials.

## Evidence and next work

Current sources, receipts, complete listings and control results are under
`.analysis/player-main3111-session/` and `build/gpt61-player-main-probe/`.
The useful entry points are `audit.py`, `whole-audit.txt`, `whole-audit.json`,
`control-equivalence.txt` and `data-roles-proof.txt`. All native extents were
read from the locked PE; no original or analyzer bytes were modified.

**Canonical replay scope is zero.** There is no main-frame exact unit and
no change to accepted executable inputs. Existing Timer/Player accessor
objects and receipts are preserved. The next related game-owned scope is
the unresolved 555B `Player::apply_move_delta` at `0x004FFA10`; retain these
main-frame constraints while investigating that independent child.
