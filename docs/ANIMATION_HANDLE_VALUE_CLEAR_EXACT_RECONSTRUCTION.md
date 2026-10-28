# CORE/EXACT-335 — entire 20-byte AnimationHandle value-clear ABI and parent-call correction

Locked original: Japanese TH20 v1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete 20-byte i386 routine at native `0x0049DA50..0x0049DA63`
(original whole-body SHA-256
`a068869c343013a89039a5c55be7cdb6c83ff8952b8a0522ce59771b0170b434`)
receives a pointer to the real four-byte `AnimationHandle` value in `ECX`
and stores exactly one zero dword to its member at offset zero. There are
**nine original x86 instructions and no static relocations**.

The complete natural C++20 source is the `__fastcall` reference helper
`th20::clear_animation_handle_value(AnimationHandle&)`, now in the existing
`src/BulletCollisionAnimationHelpers.cpp` owner alongside real
`AnimationHandle` cancellation/interrupt bridges. The original source
spelling is *not established*: a no-stack-argument `__thiscall` member and
an ECX-reference `__fastcall` free helper share this physical calling
convention. The maintained name describes only independently observed
receiver semantics and the one original store. No fabricated handle,
manual assembly or padded bytes were introduced to resolve the ambiguity.

The original 1,518-byte `Player::rebuild_option_animations` calls the same
physical routine at original caller offset **`+0x20D`** after passing an
option's `AnimationHandle` to its mode-1 cancellation function. The previous
maintained parent wrote `handle.value = 0` inline, preserving the scalar
side effect but **omitting the native call**. The maintained full boss now
calls `clear_animation_handle_value(option->handle_e0)` instead.
Recompiling the entire nonexact parent with its separately observed
8-byte stack alignment and `/GS-` i386 profile yields **1,587 bytes / 420
instructions, with 390/418 ordered original instruction kinds**, rather
than 1,586 bytes / 418 instructions and 387/418 aligned kinds in the
immediately previous candidate. This is a real ABI/behavioral correction,
not an exactness claim for the full 1,518-byte parent.

The 20-byte method itself passed **20/20 canonical strict original bytes**
with the pinned MSVC 19.44.35211 x86 C++20 owner profile. The only changed
existing canonical source is `src/BulletCollisionAnimationHelpers.cpp`, so
precisely **8/8 strict native units in one freshly rebuilt source object**
were checked; all seven earlier Animation/handle helpers remained strictly
exact. The parent is source-present but nonexact and was recompiled as one
isolated locked full-body probe, not added to canonical `matches.csv`.
Private evidence: `.analysis/core334-AnimationHandleClear.cpp`,
`.analysis/core335-handle-clear-replay.log`, and
`.analysis/core335-maintained-parent-check.txt`. No shared-header edits,
no unrelated cold replay and no whole-graph build occurred.


## Subsequent CORE/EXACT-369 whole-parent closure

The *separate* complete **1,518-byte** Player option rebuild boss at
0x004FACA0 is now independently **1,518/1,518 native strict exact**,
with all 418 original instructions and 60 independently attested
E8/HIGHLOW references. Any earlier reference in this historical
checkpoint to that parent as still nonexact/open is **superseded**.
This proof's own helper or original function is not double counted.
Read the [new entire Player option rebuild exact proof](PLAYER_OPTION_REBUILD_1518_EXACT_RECONSTRUCTION.md).
