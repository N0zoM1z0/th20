# CORE/RECON-999 — four whole original Card finish helpers, source-native exact

Target: immutable Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

A new source owner [`CardSpellNativeLeaves.cpp`](../src/CardSpellNativeLeaves.cpp)
contains four distinct original methods invoked by the entire native
**602B /172-i386** Card::finish_spell Boss at `0x004878B0` (SHA-256
`17601f659a19106028345e6ea7349827979a354946d8f728d56cd3a12b08003f`).
The original parent remains a separate **NONEXACT** source-absent body at
this checkpoint. No parent exact credit is inferred from its children.

## Four complete physical functions and independently original parent calls

| Native entry | Original bytes / x86 | Source role / PE E8 in Card finish | Origin |
| --- | --- | --- | --- |
| `0x004883A0` | **32B/12** | UI dirty bit at `+0x3344`, E8 `+0x1F` | Authored game; +32B |
| `0x00488510` | **61B/18** | Capture-record counter at `+0xC0/+0xC4`, saturated at 99999; E8 `+0x142/+0x179` | Authored game; +61B |
| `0x00488700` | **19B/9** | Record group selection by `+0x8A460`; E8 `+0x14D/+0x1A3/+0x1D4` | Origin unproven, zero authored credit |
| `0x00486E10` | **23B/9** | `0xE0`-stride record subscript, E8 `+0x133/+0x16A/+0x1B7/+0x1E8` | Likely generic index, origin unproven, zero authored credit |

The compiler consumes honest non-owning source views in
[`NativeCardSpellViews.hpp`](../src/NativeCardSpellViews.hpp), without inventing
prefix data, altering the actual Card layout or duplicating already mapped
physical heads. All four native bodies have **zero original E8 and zero PE
HIGHLOW in their own byte extents**. The original parent has 26 E8 and
13 PE HIGHLOW. All nine actual parent call sites to these four physical
functions are proved directly from the independently attested PE, not from
candidate addresses.

The verified native 61B counter is sensitive to C++ expression structure:
an early `auto* values = this+0xC0` source experiment produced **62B**, one
extra stack-local slot and different instructions. Directly indexing the
real underlying native word span **twice** with ordinary C++ evaluation
produced exactly 61/61B, including the original signed `< 99999` branch.
This is real observed member access, not an inert source-shaping local.

[`verify-card-spell-finish-leaves-native.py`](../scripts/verify-card-spell-finish-leaves-native.py)
checks immutable original whole-body SHA-256 for all four functions,
independent native x86 through true `ret` / `ret 4` and full original parent
E8 destinations, and complete compiled objects. With pinned MSVC 19.44
x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`,
one single new source object passed all four original canonical comparisons:

```text
card_finished_ui_mark_32: exact (32/32 bytes)
card_spell_capture_counter_61: exact (61/61 bytes)
card_record_archive_second_19: exact (19/19 bytes)
card_spell_record_at_23: exact (23/23 bytes)
Exact replay: 4/4 units, 1 cold objects
```

**Four new strict whole native units /135 original physical `.text` bytes**,
but just **two newly credited authored game heads /93 original bytes**.
The 19B/23B source is conservative `origin=unknown/review`, not counted
as authored code. No source work or state change to the full parent,
Session, Context, animation handles, score or 1,896B Card start Boss is
claimed here. No project-wide cold replay ran.

```bash
scripts/repo-python scripts/verify-card-spell-finish-leaves-native.py \
  --candidate-object build/core999-canonical/CardSpellNativeLeaves.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardSpellNativeLeaves.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
