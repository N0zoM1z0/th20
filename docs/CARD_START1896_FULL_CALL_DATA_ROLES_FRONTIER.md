# Card Start 1,896B Boss — recover all 62 native calls and 26 data owner roles

The independent original is `resources/th20.exe`, TH20 Japanese Steamless
v1.00a, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The real game `Card::start_spell` begins at `0x00487C30` and has a complete
**1,896B /512 i386** body, SHA-256
`dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410`.
It has **62 original physical E8 calls and 26 PE HIGHLOW fields**, with
`ret 0x10` at its native ending. This parent is **SOURCE-PRESENT,
NONEXACT**; restoring a source call graph does not admit the original
body's bytes.

## Genuine resource owners and call sequence

The previous C++ source cached the `AsciiInf::animation_file` field and
used it for **all three** info animation spawns. The actual original
calls its already-exact **20B** renderer file getter `0x00437950` at
E8 `+0x213` and `+0x293`, and the independently observed **16B** shared
text file getter `0x00470670` at `+0x249`. The middle spawn also passes
original literal `"text"` from physical data `0x0056FE1C` rather than
`nullptr`. Each of the three getters is followed by its own genuine
57B `AnimationFile::spawn` call at `+0x22D`, `+0x277` and `+0x2AD`.
The original input receiver for all three and the queued text submission
is the process Card/ASCII renderer pointer at **`0x005C0698`**. The
maintained code now borrows that actual owner through
[`NativeCardRendererFileView.hpp`](../src/NativeCardRendererFileView.hpp),
whose pre-existing exact `current_file_437950()` method lives in
`CardHudResult1522.cpp`; `AsciiInf::text_animation_file()` has the actual
shared getter's ABI and ignores its receiver. No fake new file owner,
new allocation, duplicated 20B method body, or duplicate exact byte
credit was introduced.

The original creates the PMR display name before the text payload but
**destroys it after all sound/effect/script operations** (E8 `+0x746 ->
0x00449240`), with the payload's own destructor at `+0x33F` before the
sound. The original also checks whether the boss exists and reads its
position first, only constructing the zero `Vector3` on the alternate
path. Its bonus calls `Session::clamped_field_1f4` at `+0x4F3` before
`Session::mode` at `+0x4FF`. All of these observable branch, evaluation,
and object-lifetime orders now match the natural C++20 source.

## Recovered native script-table reads

The table global **`0x005C6110`** is not a fixed cached entry: the original
loads its pointer **seven times** at source-relevant offsets
`+0x5B2/+0x5E8/+0x625/+0x671/+0x699/+0x6CA/+0x702`.
These are four accesses of the selected 12B descriptor (`file_id`
condition, `file_id` lookup, `script` lookup and `group` flag
publication) plus three accesses of the optional third descriptor.
The actual stage stride is **0x34**, descriptor stride **0x0C** and
native descriptor-array base **+0x64**. The current source expresses
those same real typed accesses at every native use using a local source
macro `CARD_SCRIPT_ENTRY`. The macro avoids an unrelated C++ helper E8
and does **not** cache a mutable global pointer. The old `spell_script_entry`
helper was called twice in the source but not once in the original PE.

## Whole-COFF results, not a shortened prefix

Pinned MSVC 19.44 x86 C++20 (`/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`) produced:

| Evidence | Previous maintained source | Current source | Original PE |
| --- | ---: | ---: | ---: |
| Complete native parent / candidate function | 1,750B | **1,848B** | 1,896B |
| i386 instructions | 478 | **490** | 512 |
| Physical E8 / compiler REL32 | 61 | **62** | 62 |
| PE HIGHLOW / compiler DIR32 | 16 | **26** | 26 |
| Original E8 **callee roles in order** | incomplete | **62/62** | 62/62 |
| Original data destination **roles in order** | incomplete | **26/26** | 26/26 |
| E8 **opcode positions** identical | not exact | **0/62** | 62/62 |

The current parent remains 48 bytes and 22 i386 instructions short,
with differing stack locals, source call placement, and compiler/EH
cleanup. It matches only **90/1,496** ordinary positional bytes
when masking the exact 88 real COFF relocation fields. All role
claims compare the original SHA-pinned physical PE E8 destinations
and HIGHLOW values to the actual generated COFF **symbol names**;
they are not inferred from candidate displacements. The full source
and immutable 62/26 census are checked by
[`scripts/verify-card-start1896-native-frontier.py`](../scripts/verify-card-start1896-native-frontier.py).
Do **not** record 1,896B whole exact or a new authored game byte here.

## Strict bounded regression

Only the affected `CardStartSpell1896.cpp` source was cold rebuilt; its
accepted **128B PMR string constructor and 7B callable helper** remain
**2/2 strict exact**. The previously original-exact 1,522B HUD result
Boss and its distinct 20B file getter remain **2/2 strict exact** under
their original unmodified translation unit. This was explicitly checked
after briefly testing a shared-header include in the HUD source: the
additional include changed generated `$SG` labels but not code; we kept
the original accepted HUD source unchanged rather than changing its
canonical relocation manifest. The new Card Start source uses an
ODR-compatible narrow declaration for the existing renderer getter.

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardStartSpell1896.cpp
scripts/repo-python scripts/compare-coff-function.py \
  --unit card_hud_spell_result_boss_1522
scripts/repo-python scripts/compare-coff-function.py \
  --unit card_hud_renderer_file_getter_20
scripts/repo-python scripts/verify-card-start1896-native-frontier.py \
  --candidate-object build/core1009-canonical/CardStartSpell1896.obj
scripts/repo-python scripts/validate-tracking.py --require-target
```

No full-graph cold replay was used. The next substantial Card Start
frontier is the remaining 48B of EH, bonus, stack-local and handle
creation lowering; the 102B text `std::function` constructor is still
independently nonexact. Existing Card text/queue and HUD children
remain distinct original physical code owners, never double-credited.
