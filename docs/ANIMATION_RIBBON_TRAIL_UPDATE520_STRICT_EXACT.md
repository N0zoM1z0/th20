# CORE/RECON-937 — original 520B/149-i386 64-point ribbon update Boss whole strict exact

Locked target Japanese TH20 v1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0045DF80` is a **520B/149-i386 polymorphic Update Boss**,
pointed to by the original `0x0056ED1C` vtable and using the same
0x320-byte group as the independently exact
[103B constructor](ANIMATION_RIBBON_TRAIL_GROUP_CTOR103_STRICT_EXACT.md).

## Original PE proof, independent of candidate source

[`scripts/verify-animation-ribbon-trail-update520-native.py`](../scripts/verify-animation-ribbon-trail-update520-native.py)
fully verifies all 149 native instructions through `ret`, every one of
**15 original E8 instruction sites AND destinations**, all **5 original
PE HIGHLOW locations AND targets**, original 0x58-byte stack frame,
64-frame gate, data constants and the real vtable's second virtual slot.

| Original native role | Physical evidence |
| --- | --- |
| Timer gate at receiver `+0x30C` | E8 `+0x019 -> 0x00423560` (`less_than(64)`), `+0x032 -> 0x0045D030` (change gate), `+0x048 -> 0x0040FF90` (current frame), and `+0x1FD -> 0x00423540` (`Timer++`) |
| Color alpha fade | Three separate E8 `+0x07D/+0x09E/+0x0CB -> 0x00414580` access actual four-byte cells at `+0x208`, clamp alpha under 16 to zero or subtract 16 |
| New polar vertex | RNG E8 `+0x0DB -> 0x00429830`, real HIGHLOW `0x005BA4C4` mutable RNG plus `5.0f` `0x0056EDD4` and `4.0f` `0x0056C8E0`; E8 `+0x11D -> 0x0045D670` index and `+0x13F -> 0x00439330` polar conversion |
| Cumulative geometry | E8 `+0x160/+0x180 -> 0x0045D670` indices, `+0x187 -> 0x00439960` original **Vector2::operator+=** with by-value returned temporary and natural compiler `nop` |
| Angle and return | E8 `+0x192 -> 0x004297D0` random radians, divide by physical `5.0f`, E8 `+0x1D2 -> 0x00438600` add angles; real original return1 on complete 64-frame expiration and return0 after Timer advancement |

The exact original E8 fields not otherwise shown in the table and all
HIGHLOW fields are exhaustively enumerated/checked by the script,
without trusting Ghidra semantic names or the COFF candidate.

## Natural C++ and full original-bound oracle

[`src/AnimationRibbonTrailGroupUpdate520.cpp`](../src/AnimationRibbonTrailGroupUpdate520.cpp)
reconstructs the complete original control flow in one normal C++20
`NativeRibbonTrailGroup::update()` using actual 64 `Vector2` points,
64 four-byte color records, Angle state and Timer. Typed alpha field
access naturally emits the original byte-offset `+3`; a separate
`Vector2*` local is required to evaluate the destination before the
polar call. The trailing `if/else` layout is meaningful: the original
exits with 1 on expired lifetime, otherwise increments Timer and returns
0. This restores the original distinct branch, rather than inserting
a synthetic NOP or copying machine instructions.

Initial natural source using raw `unsigned char[3]` indexing and a
single source-level early return generated **531B/150-i386**; a typed
alpha field reduced it to 512B and an explicit vertex pointer to
518B. Reconstructing the actual final `if/else` lifetime and Timer
control flow yielded exactly **520B/149-i386**. Pinned MSVC 19.44 x86
C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
reproduces all **20 original relocation fields/targets**, including
440/440 nonrelocated bytes, and the canonical replay confirms:

```text
animation_ribbon_trail_update_520: exact (520/520 bytes)
animation_ribbon_trail_group_ctor_103: exact (103/103 bytes)
animation_ribbon_trail_scalar_delete_49: exact (49/49 bytes)
Exact replay: 3/3 units, 2 cold objects
```

This adds **one new game-authored exact head /520 physical original
`.text` bytes**. The 49B deleting-wrapper is not double-credited.
The 165B trail draw, 340B/382B configuration and 156B allocation factory
are distinct original functions and must be independently validated.
No global replay, full-game linkage or playable game is claimed.

```bash
scripts/repo-python scripts/verify-animation-ribbon-trail-update520-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonTrailGroupUpdate520.cpp --source src/AnimationRibbonTrailGroupCtor103.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
