**CURRENT WHOLE-SOURCE UPDATE:** The maintained 1,896B Card start now has the original 20B Renderer file getter twice, the separate 16B text-file getter, the actual `"text"` literal, and the PMR display name lifetime through the end of the Card method. The tail script table is re-read from its true `0x005C6110` global seven times. Its whole source candidate is now **1,915B/495 i386 with all 62 original E8 and 26 PE HIGHLOW destination roles represented in exact original order**, but still NONEXACT. See [current source call/data proof](CARD_START1896_FULL_CALL_DATA_ROLES_FRONTIER.md). Earlier numeric source states below are historical.

**CORE/RECON-1160 / 1187 forwarding-leaf update:** the original 8B reference-forwarding primitive at `0x0040B280` remains `matching` from the `EclLoaderBuffer.cpp` owner. The original PMR string move (`0x0046A728`) now naturally calls it through an explicit out-of-line `std::move<polymorphic_allocator<char>&>` instantiation; the 108B PMR move constructor is whole exact. The Card `std::function` constructor (`0x00486839`) and `_Reset` helper (`0x00486A50`) are now both exact after CORE/RECON-1188 restored their real out-of-line `std::forward<NativeCardTextPayload>` calls; no synthetic wrapper or padding is used.

**New original dispatcher caller (CORE/RECON-1158):** the complete 552B shared Enemy opcode branch for 522/528/531/532/533 is now maintained in natural C++ and reaches this real `Card::start_spell` owner after its native rolling-XOR packet-name decode, mode adjustment and cached Context Card selection. This closes the caller source, not the 1,896B callee: the callee remains NONEXACT. See [the caller source frontier](ENEMY_41967_522_528_531_532_533_CARD_START_SOURCE_FRONTIER.md).

**Current CORE/RECON-1037 / 1188 update:** The actual Card text lambda body at `0x00486E80` has [whole 111/111 strict exact](CARD_TEXT_CALLBACK111_STRICT_EXACT.md), with the real `std::pmr::string::c_str` receiver at capture+4 and native layer 0x00FFFFFF. The 102B NativeCardTextPayload `std::function` constructor at `0x00486800` and 65B `_Reset` at `0x00486A30` are now whole exact. A separate 102B `std::function` constructor at `0x00486740` used by the callback path remains NONEXACT; the enclosing 1,896B Card start and 578B text renderer also remain NONEXACT.

# CORE/RECON-1030 — Card start 1,896B native text producer: real callable, PMR capture and locked task enqueue

The independent immutable target is Japanese TH20 Steamless v1.00a,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original game-authored `Card::start_spell` at `0x00487C30`
is **1,896B/512 x86 instructions**, with **62 original E8 and 26 PE
HIGHLOW**. Its immutable body is SHA-pinned at
`dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410`.
No parent source is yet canonically exact.

## Corrected native Card text task ownership

The earlier [CORE/RECON-1008](CARD_START1896_TYPED_NATIVE_FRONTIER.md)
source reconstructed the game's Card, Bonus, HUD, Bomb and effect stages,
but left the Card text queue behind a speculative opaque
`enqueue_card_name_display_task` function. That approach was **not** the
original task lifetime; its candidate was **1,732B/472 x86** with 60
REL32/16 DIR32 and omitted actual std::function transfer.

The updated maintained
[`CardStartSpell1896.cpp`](../src/CardStartSpell1896.cpp) now constructs
an actual `std::pmr::string` from `spell_name`, uses a genuine
[`NativeCardTextPayload`](../src/NativeCardTextPayload.hpp) of exactly
**36 bytes** (Card*, PMR string, Animation*), constructs a true
`std::function<void()>` from its moved callable, and passes the resulting
value **directly** to the borrowed
[`NativeCardAsciiTaskQueueView`](../src/NativeCardAsciiTaskQueueView.hpp).
Its original real queue method is separately fully source-exact at
[`0x00470180`, 153B](CARD_ASCII_TASK_QUEUE153_STRICT_EXACT.md):
the `std::recursive_mutex` lock-18, the actual AsciiInf pending-task list
and the 40-byte by-value function destructor are all preserved.
The original nested 32B STL list push method is also independently
[source exact](CARD_ASCII_LIST_PUSH32_STRICT_EXACT.md).

The actual compiler requires `std::function`'s captured functor to be
**copy constructible**. Merely providing a destructor and a move constructor
for `NativeCardTextPayload` failed with the pinned MSVC's C++ requirement
N4988 [func.wrap.func.con]/10.1. The retained header now declares a
normal **copy constructor** (`std::pmr::string` copied), alongside the
previous exact Card*/PMR string/Animation* ordinary and move constructors.
The original **111B native text callback** at `0x00486E80` is now whole
strict exact under CORE/RECON-1037; no fabricated body is used. Its native
path gets the name string, constructs an intermediate `std::function`, and
calls the separately substantial text-display path at `0x0044B020` (578B).
The separate 102B callback constructor at `0x00486740`, the text-render
Boss and Card parent retain their own distinct exactness frontiers.

A first correct high-level C++ candidate used a distinct `task` local
and passed `std::move(task)` into the queue. It compiled to
**1,880B/486 instructions** and 63 REL32/16 DIR32, introducing extra
std::function move/destroy calls not physically present in the original
Card parent. Removing the unnecessary transfer local and directly
constructing the **by-value queue parameter** uses C++17+ prvalue
elision to preserve the real resource ownership and produces the current
**1,750B/478 x86** candidate, with **61 REL32 and 16 DIR32**. This
retains the actual payload constructor, 93B generated std::function
construction, original 153B ASCII queue call and payload destructor
with real scope lifetime. The original E8 call targets at
`+0x30D` (payload constructor `0x00486B70`), `+0x325`
(std::function constructor `0x00486800`), `+0x330`
(ASCII queue `0x00470180`) and `+0x33F` (payload destructor
`0x0046ADE0`) are independently corroborated by original PE instructions.

## Exact compiler frontiers remaining, not guessed away

The generated original callable constructor at `0x00486800` is a
complete **102B** body with compiler EH/cookie and a real extra
9-byte `std::move` forwarding call before `_Reset`. The natural
MSVC 19.44 function-object template generated by the maintained source
is **93B**, while its own nested `_Reset` generated helper is **56B**
versus **65B** original at `0x00486A30` for the same independent
9-byte forwarding call. At this historical CORE/RECON-1030 checkpoint, the source-generated PMR
string move was **99B** versus native **108B** at `0x0046A710`. CORE/RECON-1187
has since closed that separate function with a whole 108/108 exact unit by
preserving the native out-of-line allocator `std::move<T&>` call. The 102B
callable constructor and 65B `_Reset` still have their own genuine 9-byte
compiler-lowering differences; they are not padded or aliased to hide them.

The 111B Card text callback is now whole exact. The original 102B NativeCardTextPayload `std::function` constructor and 65B
reset are now exact. The separate 102B callback constructor at `0x00486740`,
original EH frame/unwind, full effect/metadata owners and original whole-graph
control flow remain open.
The 1,896B Card start **remains SOURCE-PRESENT, NONEXACT**.
The checker
[`verify-card-start1896-native-frontier.py`](../scripts/verify-card-start1896-native-frontier.py)
independently verifies the original entire 1,896B/512 native body,
62 E8 and 26 PE HIGHLOW and separately reports only the *actual*
1,750B/478 source candidate with 61/16 roles. It awards **zero
additional whole-parent exact bytes**.

## Scoped regression and continuity

The actual changed include closure consists of **three existing
canonical objects**, not the full 1,470-unit repository: 4 accepted
payload/PMR units from `CardTextPayloadNative.cpp`, 1 accepted
PMR char constructor from the nonexact Card start source, and 2
accepted ASCII queue/list units from `CardAsciiTaskQueue153.cpp`.
All seven must remain whole exact under their original physical
ranges and independent relocation roles. The queue view header is
shared only between these relevant sources; no real AsciiInf/Card
class layout is altered and no build of the unaccepted full parent
is represented as a strict acceptance receipt.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/CardStartSpell1896.cpp build/gptweb-cont-1030/CardStartSpell1896.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-card-start1896-native-frontier.py \
  --candidate-object build/gptweb-cont-1030/CardStartSpell1896.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardTextPayloadNative.cpp \
  --source src/CardStartSpell1896.cpp \
  --source src/CardAsciiTaskQueue153.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1031 — native name getter now accepted beneath callback

The original 111B Card text callable's first E8 call targets a complete
[22B source-exact PMR name getter](CARD_TEXT_CAPTURE_CSTR22_STRICT_EXACT.md)
on the real 36B capture. The getter and its `c_str()` callee are
independently proved from the PE. The callable's own 111B body is now exact. Its separate 102B `std::function`
constructor at `0x00486740`, the 578B text draw Boss and Card start's 1,896B
parent remain separate unresolved code.

## CORE/RECON-1034 — source-generated 7B callable-test child accepted

The original 65B `_Reset` calls a genuine [whole-exact 7B
`std::_Test_callable<NativeCardTextPayload>`](CARD_TEXT_CALLABLE_TEST7_STRICT_EXACT.md)
at `0x00413910`. At the historical CORE/RECON-1034 checkpoint, the 65B
`_Reset` and 102B NativeCardTextPayload `std::function` constructor were
NONEXACT. CORE/RECON-1188 has since closed both whole functions with their
original `std::forward<T>` E8 calls. The separate 102B callback constructor
at `0x00486740` and 1,896B Card parent remain NONEXACT.


**Current CORE/RECON-1165/1168/1170 source update:** the primary/secondary spell-record lookups now remain inside the first `strcpy_s` argument, preserving native right-to-left argument evaluation. The reward product is retained in its own local before both Card fields are assigned and the initial bonus is clamped. The zero-position fallback now has an explicit local `Vector3` lifetime. The 12B script-table descriptor is corrected to `{file_id, script, group}` at offsets `+0/+4/+8`, and the stage/variant/controller/file/script locals are explicit. The whole natural-C++ candidate is now 1,915B/495 i386; all 62 original E8 callee roles and 26 PE data destination roles still match in order, but the original 1,896B parent remains NONEXACT (candidate 19B longer, 17 instruction heads fewer, 91/1,548 overlapping non-relocation bytes match).


**CORE/RECON-1187 update:** The original 108B `std::pmr::string` move
constructor at `0x0046A710` is now whole exact from the existing
`CardTextPayloadNative.cpp` owner. A natural C++ explicit instantiation of
`std::move<std::pmr::polymorphic_allocator<char>&>` with `__declspec(noinline)`
restores the original 8B forwarding E8 to `0x0040B280`; the candidate is
108/108 bytes with all five original REL32 target roles. The 64B payload move
remains exact. The separate 102B `std::function` constructor and 65B `_Reset`
are now whole exact under CORE/RECON-1188.


**CORE/RECON-1190 callback nested callable:** The independent 111B deferred
Card text callback constructs its own `std::function<void()>` for the 4B
`NativeCardTickCallback`. Its original 102B constructor at `0x00486740` and
90B `_Reset` at `0x004869D0` are now whole exact from the existing
`CardTextCallback111.cpp` owner. Both use the same 8B `std::forward<T&>` leaf
at `0x0040B280`; the constructor has two real PE HIGHLOW plus three E8, and
_Reset has five E8. These are separate generic STL boundaries from the
Card-start payload's 102B/65B pair; the 578B draw Boss and 1,896B parent remain
NONEXACT.


**CORE/RECON-1192 erased callable vtable:** The `NativeCardTickCallback`
`std::_Func_impl_no_alloc` concrete target now has its original six-method
vtable restored as whole exact natural-C++ units: Copy 47B, Move 104B, Do_call
26B, Target_type 16B, Delete_this 35B and Get 26B. Its 14B `std::invoke`
bridge is also exact. The `_Move` 104B body plus five compiler-generated
INT3 alignment bytes matches the original 109B comparison span; only 104B
function coverage is credited. The 34B callback operator and its 22B
AnimationHandle wrapper remain open; the 578B renderer and 1,896B Card parent
remain NONEXACT.
