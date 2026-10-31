# CORE/RECON-1003 — five whole original Card start leaves, 225 game-authored bytes

Target: the locked Japanese TH20 v1.00a Steamless binary, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original **1,896-byte /512-instruction `Card::start_spell` Boss** at
`0x00487C30` is still a separate source-absent/NONEXACT game function.
[`verify-card-start-five-native.py`](../scripts/verify-card-start-five-native.py)
reads that entire original PE body independently (SHA-256
`dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410`),
checks 62 physical E8 call instructions and 26 original PE HIGHLOW sites,
and proves the specific parent calls listed below. Exactness of these five
children does **not** establish source or strict credit for the 1,896B parent.

## Independently complete original bodies and roles

| Original head | Whole body | Original role and genuine callsites |
| --- | ---: | --- |
| `0x004888C0` | **29B /12 x86** | Card+0x78 clears capture effect bit7; parent E8 `+0xAB` |
| `0x00488960` | **42B /16 x86** | Card+0x78 sets native bit9 from input low bit, preserving every other bit; parent E8 `+0x68D` |
| `0x00488590` | **61B /18 x86** | Saturated 99,999 attempt-counter update in persistent spell-record+0xC8, index 0/1; parent E8 `+0x14B/+0x1AA` |
| `0x004888E0` | **22B /11 x86** | Borrowed HUD Animation receives VM event **2** via already exact 34B `0x00477450`; 71B HUD caller E8 `+0x20/+0x3D` |
| `0x00488A60` | **71B /24 x86** | Actual two HUD animation pointers at +0x88 are processed in order with two folded 22B index calls at `0x00414580` and two 22B event-2 calls; parent E8 `+0x1B6` |

Original bodies are SHA-attested, checked to the actual final `ret` or
`ret 4`, and have **zero original in-body PE HIGHLOW**. The 22B event-2
wrapper is followed by *ten* genuine `INT3` alignment bytes outside its
original code extent; the 22B function is not expanded into a false 32B
code body. No new unit takes duplicate physical credit for the existing
34B VM setter or folded 22B array indexing target.

## Natural compiler source and ABI corrections

[`CardStartNativeLeaves.cpp`](../src/CardStartNativeLeaves.cpp) contains all
five bodies. It uses the actual `Card` fields and the retained non-owning
[`NativeCardStartFlagsView`](../src/NativeCardStartFlagsView.hpp),
[`NativeCardFinishViews`](../src/NativeCardFinishViews.hpp),
[`NativeCardHudAnimationView`](../src/NativeCardHudAnimationView.hpp), and
[`NativeCardSpellViews`](../src/NativeCardSpellViews.hpp). All views refer to
observed existing native storage; no new inherited object, vtable or padded
prefix owner was introduced.

The 42B bit9 setter particularly checks an old source hypothesis: manually
expanding a word-wide read-modify-write OR/AND emits **42B but only 23/42
matching bytes** because MSVC evaluates the existing word before the input.
A real four-byte `uint32_t` **bitfield view of bit9** naturally computes the
incoming masked bit first, then updates the existing native word, exactly
matching **42/42B**. The capture record counter similarly retains direct
original indexing at `+0xC8` on both branches, not a fabricated cache or
filler local. The two HUD array reads are intentionally performed separately,
matching both real original compiler-generated calls and stack temporaries.

## Scoped accepted replay (no full cold replay)

Pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` confirms **all five functions are whole strict
exact**, with genuine relocated destinations. Two shared native view headers
and the previous HUD source were updated coherently. The current receipt
include closure identified exactly **four existing canonical objects /ten
already exact units** as affected; those four were recompiled once, preserving
all ten old unit comparisons. One new provider contains the five new units:

```text
card_start_flags_clear_29: exact (29/29 bytes)
card_start_bit9_42: exact (42/42 bytes)
card_start_attempt_counter_61: exact (61/61 bytes)
card_start_vm_start_22: exact (22/22 bytes)
card_start_hud_start_71: exact (71/71 bytes)
Exact replay: 15/15 units, 5 cold objects
```

These are five newly recognized game-specific physical heads and add **five
complete game-authored functions /225 original `.text` bytes**, counted once.
The source spelling of the original UI class and the full permanent record
owner are still unknown; the byte-exact ABI is established only for their
observed narrow receiver interfaces. The original 602B Card finish Boss is
separately **whole exact**; the original **1,896B Card start Boss is not**.
Whole-game linkage/playability and the 39,470B Animation VM remain open.

```sh
scripts/repo-python scripts/verify-card-start-five-native.py \
  --candidate-object build/core1003-canonical/CardStartNativeLeaves.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardSpellNativeLeaves.cpp \
  --source src/CardFinishStatusHelpers.cpp \
  --source src/CardHudSpellCleanup71.cpp \
  --source src/CardFinishSpell602.cpp \
  --source src/CardStartNativeLeaves.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1006 — original 42B Bomb predicate accepted separately

The same original Card start uses a genuine BombController active-state
predicate at `0x00478130`, native E8 `+0x1D6`. Its [independent whole
42B strict match](CARD_START_BOMB_ACTIVE42_STRICT_EXACT.md) adds one game
head/+42B and **does not** make the 1,896B Card parent exact.

## CORE/RECON-1007 — typed original Card text payload accepted

The previously unowned original start text capture now has a [natural 36B
Card*/PMR string/Animation* owner and three whole strict-exact helpers](CARD_TEXT_PAYLOAD_56_23_167_STRICT_EXACT.md), including the real 167B PMR
string copy with compiler EH metadata. The original full 1,896B parent
remains separate and NONEXACT, and the helper ownership is uncredited.
