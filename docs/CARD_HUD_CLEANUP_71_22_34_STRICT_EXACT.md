**Current status update (CORE/RECON-1002):** The previously NONEXACT 602B Card finish parent is now [whole strict exact](CARD_FINISH_602_STRICT_EXACT.md). The children below keep their independent 71B/22B/34B exact identity and are not credited twice.

# CORE/RECON-1001 — complete native 71B HUD two-animation cleanup and 22B/34B VM bridge chain

Locked target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

This checkpoint reconstructs the genuine original Card finish HUD subchain,
not just small standalone functions. The entire original **602B Card::finish_spell**
at `0x004878B0` physically calls the **71B** HUD cleanup at E8 `+0x8E`.
The HUD method in turn calls two original 22B event-3 bridges through two
folded 22B `std::array` index calls, and each bridge calls a complete 34B
Animation VM-event setter. All are whole physical heads with actual original
call identities, not inferred matches from neighbouring game functions.

## Complete original PE control flow and source

| Physical native head | Whole instructions | Original complete call graph | Replayed original size |
| --- | ---: | --- | ---: |
| `0x00488AB0` Card HUD cleanup Boss | 71B /24 i386 | `+0x19/+0x36` to folded `std::array::operator[]` at `0x00414580`; `+0x20/+0x3D` to the 22B bridge | 71/71B |
| `0x00488900` finish event-3 wrapper | 22B /11 i386 | `+0x0C` to the original 34B VM setter `0x00477450` | 22/22B |
| `0x00477450` Animation VM-event setter | 34B /13 i386 | writes native Animation word `+0x438`; `+0x16` to the original **still NONEXACT** 39,470B Animation VM update `0x0042B5D0` | 34/34B |

[`verify-card-hud-cleanup-native.py`](../scripts/verify-card-hud-cleanup-native.py)
reads the immutable target PE, pins the entire native SHA-256 of all three
bodies, checks exact 24/11/13 instruction boundaries through the real
`ret`/`ret 4`, validates all six native original E8 fields and their
**physical** original destinations, confirms zero original PE HIGHLOW and
real `INT3` outside the function ends, and proves the genuine original
602B parent call. The candidate is compared only after the independent PE
census; original target fields are never solved from candidate relocations.

The single natural maintained C++ source
[`src/CardHudSpellCleanup71.cpp`](../src/CardHudSpellCleanup71.cpp)
uses the actual borrowed two-Animation array at HUD owner `+0x88`. It
reads element zero and one separately and invokes the true event-3 forwarding
bridge; the bridge forwards three to the true `Animation+0x438` event word
and invokes the existing real `Animation::update` method. The original
HUD source performs two distinct array-base evaluations. A first shared
`auto& handles` local in a private probe generated 59B instead of the
original 71B; preserving two **actual distinct array accesses** generated
the exact full 71B original, including every compiler local slot and original
physical field position. The repeated expressions perform required actual
reads, not inert padding or code-shaping side effects.

Importantly, the private source experiment initially declared a derived
`NativeHudAnimationView : Animation` without independent inheritance proof.
That hypothesis was **rejected**: the maintained `NativeHudAnimationView` is
now strictly a *non-owning view*, containing no data or invented superclass.
Its VM method casts only the observed borrowed receiver back to genuine
`Animation*` for the already declared `update()` call. This preserves the
full original 34B and avoids fabricating the native RTTI/vtable or class
construction. The 22B index helper at `0x00414580` was already mapped
under a different type and is **not** credited twice.

## Strict PE/COFF acceptance

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` builds one actual source provider:

```text
card_hud_animation_vm_event_34: exact (34/34 bytes)
card_hud_finish_event_bridge_22: exact (22/22 bytes)
card_hud_spell_cleanup_71: exact (71/71 bytes)
Exact replay: 3/3 units, 1 cold objects
```

All three are specific game-authored methods; each head has unique original
code bytes and each is credited once: **+3 authored game heads /127 native
`.text` bytes**. The earlier 32B/61B/19B/23B Card record leaves and the
41B/23B Card state leaves remain separate accepted physical methods; no
shared array or VM-update callee is counted again. The **602B Card finish
Boss itself remains SOURCE-PRESENT / NONEXACT**, currently 577B compiled
candidate, and its original 26 E8/13 HIGHLOW checks are unaffected.
The 1,896B Card start Boss and whole-game linkage remain unfinished.

```bash
scripts/repo-python scripts/verify-card-hud-cleanup-native.py \
  --candidate-object build/core1001-canonical/CardHudSpellCleanup71.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardHudSpellCleanup71.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

No full-graph cold replay was run.
