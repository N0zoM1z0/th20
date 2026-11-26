# Exact 1,896-byte Card spell start

`Card::start_spell` at `0x00487C30` now strictly replays its complete
**1,896B / 512-instruction** body, including all **62 REL32 calls** and
**26 HIGHLOW/DIR32 fields**. Its complete **66B exception-code contribution**
and **52B exception metadata** also match. This adds one authored exact
function and 1,896 original game bytes.

The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The root body SHA-256 is
`dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410`.
The maintained source is [CardStartSpell1896.cpp](../src/CardStartSpell1896.cpp),
compiled with locked MSVC 19.44.35211 and
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

## Source findings

The previous source already had all call and data roles, but its freshly
rebuilt root was 1,915B / 495 instructions. Named locals and a field-based
script descriptor obscured several native expression boundaries:

- Construct the text payload as the temporary argument of `std::function`,
  then enqueue that function directly. The payload constructor's returned
  pointer feeds forwarding construction; cleanup follows enqueue immediately.
  The PMR display name survives through the later effect/script operations.
- Keep the first primary record lookup inside `strcpy_s`'s first argument.
  Its archive getter precedes the outer argument pushes, while the record
  lookup follows them. Use a separate named primary receiver for the later
  attempt update, preserving the native receiver storage and evaluation.
- Chain effect-file, selected-boss and animation-variable lookups directly.
  The zero-position branch uses list assignment, `position = {0,0,0}`.
  A named `Vector3` moves into the compiler's protected local region;
  an explicit `Vector3(...)` temporary instead copies through constructor EAX.
  List assignment recovers the native temporary slot and three memory loads.
- Compute the reward as one multiplication expression. MSVC retains the first
  getter's result in ESI across the mode getter. Preserve the native
  `initial_bonus >= 1000000000` branch and 999999999 replacement.
- Represent each script descriptor as three indexed `int32_t` words: file id,
  script, then flag group. The original retains constant-index arithmetic
  that a three-field struct removes. Keep one selected-variant local, the
  seven live global reads, and the optional descriptor's direct stage input.
  Pass its group word directly to the flag setter rather than introducing
  another named local.

The final frame is `0x114`, with `this` at `[ebp-0x30]`, saved ESI and the
capture temporary at `[ebp-0x120]`. All 62 physical call positions match.
The shared Card layout and handle array are unchanged: the original also
contains the constant-index handle arithmetic.

The source controls distinguish these effects. Temporary capture alone gives
1,891B / 500 instructions;
turning both primary receivers into expressions gives 1,897B. The chained
lookup candidate reaches 1,837B with its first 43 calls aligned. Indexed
script descriptors plus list-assigned position reach 1,906B / 514 with
56 calls aligned. Removing the extra group local yields the complete
1,896B / 512 match. These are compiler observations, not alternative
accepted implementations.

## Complete exception ownership and independent anchors

| Native head | Complete extent | Canonical unit |
| --- | ---: | --- |
| `0x00487C30` | 1,896B root | `card_start_spell_1896` |
| `0x00569230` | 8B PMR-name cleanup | `card_start_eh_name_cleanup_8` |
| `0x00569238` | 16B payload cleanup, including five INT3 bytes | `card_start_eh_payload_cleanup_16` |
| `0x00569248` | 42B cookie-checking handler | `card_start_eh_handler_42` |

The two-state map begins at `0x005AA6A4`; FuncInfo begins at `0x005AA6B4`.
Its complete 52B contribution has three DIR32 fields: two cleanup actions
and the map pointer. State zero destroys the display name; state one first
destroys the capture. All metadata bytes and all three physical HIGHLOW
positions agree with the generated contribution.

The complete 66B exception-code sequence has a unique `.text` match with
all COFF relocation fields masked. This independently anchors both cleanup
heads and the handler, without deriving its address from the root field.
Filling those cleanup targets into the 52B generated metadata and masking
only its map self-pointer gives a unique `.rdata` match at `0x005AA6A4`.
FuncInfo is then the independently located contribution plus 16. External
cleanup, cookie and frame-handler roles use the established PMR, payload
and CRT identities. Literal bindings inspect actual `text` and `effect`
bytes. No compared relocation field is solved to manufacture a match.

## Verification and next work

Only `src/CardStartSpell1896.cpp` changed in the native graph. Its four
previously accepted helpers and four new root/EH units pass **8/8 complete
canonical comparisons** from one fresh object. No shared header changed;
other providers retain their existing evidence. The old `core1009-canonical`
object and receipt are preserved; the current provider is
`build/gpt61-card-start-canonical/CardStartSpell1896.obj`.

```sh
nice -n15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardStartSpell1896.cpp --existing-objects
nice -n15 scripts/repo-python scripts/verify-card-start1896-native-frontier.py \
  --candidate-object build/gpt61-card-start-canonical/CardStartSpell1896.obj
```

The focused checker also verifies the complete metadata and independent
anchors. Private controls reject an inverted same-size pause branch, the
old 1,891B contribution, and malformed EH state count, cleanup symbol and
map symbol. The native decompilation came through attested `scripts/ghidra.py`.
The maintained source, unit configuration and canonical products reproduce the
complete comparison.

The adjacent [602B Card finish](CARD_FINISH_602_STRICT_EXACT.md) was already
exact. The ASCII text render/submit frontiers remain open. This checkpoint
establishes the spell-start unit and its owned extents; a complete game build
remains open.
