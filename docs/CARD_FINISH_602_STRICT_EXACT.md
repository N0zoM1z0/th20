# CORE/RECON-1002 — Card::finish_spell: whole 602B native exact, including both 113-record capture paths

Original binary: immutable Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Game-authored `th20::Card::finish_spell` at **0x004878B0..0x00487B09** is now
**entire 602B /172-i386 strict exact** under pinned MSVC 19.44 x86 C++20.
The canonical source is [`CardFinishSpell602.cpp`](../src/CardFinishSpell602.cpp).
This supersedes the NONEXACT 577B source frontier described by
[CORE/RECON-1000](CARD_FINISH_602_TYPED_SOURCE_AND_41_23_EXACT.md); the
restored source, not merely its 7 accepted Card/HUD children, is now exact.

## Physical native evidence, not inferred from source

[`verify-card-finish602-native.py`](../scripts/verify-card-finish602-native.py)
SHA-attests the entire original 602B code and disassembles through its
actual terminal `ret` (172 instructions). Native SHA-256:
`17601f659a19106028345e6ea7349827979a354946d8f728d56cd3a12b08003f`.
The verifier checks **all 26 original physical direct E8 call positions** and
all **13 actual PE HIGHLOW fields**, their instruction boundaries, and the
whole original code, independently from the compiled relocation fields.
The original operations include 3 information-handle cancellations, 2
retire calls, HUD animation clear, score and capture-result publication,
2 record storage updates, a true **113-record** completion traversal,
achievement 40, and the distinct sound choices. Other existing canonical
leaves remain separately exact, without duplicated original bytes.

## The recovered source-level branching and local identity

The first original native bit0 guard is an early exit on inactive Card.
After clearing animation/UI state, the `spell_flags` bit1 success branch
**executes the capture path first**, and the failure path is the later
`else`. Reversing this source ordering in early trials changed the physical
branch layout although the gameplay branches appeared logically equivalent.
The original calls both persistent record-group accessors and the real
0xE0-stride record-index functions. The card's `spell_index` is intentionally
read into **two separate native local snapshots** before their respective
record calls. The 113-record scan evaluates the two-element 32-bit capture
counter array independently, and repeats the second lookup only if the first
counter is zero, as in the original control flow.

The last previously unexplained 30 non-relocation byte differences were
**not** arbitrary compiler noise. They were caused by a wrong C++ local
ownership hypothesis in the earlier 602B/172-instruction compiler experiment:
separate `capture_kind` and `completed` locals made the frame 0x34 instead
of the original 0x30, shifting a sequence of real native EBP-relative
slots. The actual native **EBP-8 word is reused**: first it stores the
0/1 capture kind passed to both capped-record increment calls, then it is
reset to zero and becomes the signed completed-record count while an
independent loop index lives at EBP-0xC. In the maintained semantic C++
source a single real `int32_t capture_progress` local reproduces exactly
this native lifetime; it performs meaningful distinct state work on both
sides of the reset. No `volatile`, artificial NOP, unused local, filler,
manual assembly or target-byte editing was used.

Independent MSVC compiler trials, all full functions:

| Trial | Whole function | Actual difference |
| --- | ---: | --- |
| Old maintained semantics | 577B | Failure-first branch and missing array-index source roles |
| Correct success-first CFG | 578B | Original scan/index locals still absent |
| Independent `spell_index` snapshots | 590B | Index store sites restored; scan offsets still wrong |
| 2-element native array access, cached record | 611B | Extra record temporary; one unnecessary stack slot |
| 2-element native array access, fresh record E8 | 602B/172 | All 39 fields align, but 30 stack-slot bytes differ because counters were separate locals |
| **One reused actual capture/counter local** | **602B/172** | **All 446/446 ordinary code bytes and 39/39 independently original relocations exact** |

An alternative explicit nested C++ scope introduced a real extra compiler
NOP, proving that lexical braces alone do not reconcile source-level local
reuse. The accepted solution is a real local whose meaning changes after
its completion-of-capture work, as corroborated by the exact native stack
storage and original entry/exit semantics.

## Canonical strict acceptance and scope

The new `card_finish_spell_602` unit in
[`config/match-units.toml`](../config/match-units.toml) enumerates **all
39 genuine relocation fields with source symbols, original relocation types,
and independently established physical original destinations**. The target
comparison never derives an unknown call target from the source object.
One new pinned compiler object and fresh receipt are verified and replayed:

```text
card_finish_spell_602: exact (602/602 bytes)
Exact replay: 1/1 units, 1 cold objects
PASS native Card finish: 602B/172 i386, 26 true E8 and 13 PE HIGHLOW
```

This adds **one newly credited game-authored function /602 original `.text`
bytes**; its previously exact children and folded generic helpers retain
one physical credit each. No shared header, canonical old provider, full
cold replay, full runtime or pre-existing accepted unit has changed. The
**1,896B Card::start_spell** and still nonexact 39,470B Animation VM remain
separate open game Bosses. A native-exact function is not a whole linked or
playable game.

```bash
scripts/repo-python scripts/verify-card-finish602-native.py \
  --helper-object build/core1000-canonical/CardFinishStatusHelpers.obj \
  --parent-object build/core1002-canonical/CardFinishSpell602.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardFinishSpell602.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
