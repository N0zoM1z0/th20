# CORE/ORIGIN-679 — complete original 23B AnimationHandle default construction is game-owned strict exact

**One already canonical native 23-byte exact function is newly origin-reviewed as game-authored.** This class is the real four-byte game AnimationHandle identifier, not a generic compiler/CRT/STL owner. Its original class name and precise compiler-linker folding history remain source-inferred, so no duplicate physical function is claimed.

## Immutable original game method and 54 independently observed calls

Target: original Japanese TH20 v1.00a Steamless executable `resources/th20.exe`, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

- Full original method **`0x00425CC0..0x00425CD6`, 23 bytes and 10 x86 instructions**. It preserves a `__thiscall` receiver in `[ebp-4]`, performs the only game-state modification `mov dword ptr [eax], 0` on the receiver's four-byte identifier, returns the actual receiver and exits without external E8 or PE HIGHLOW fields. Its real source owner is `src/AnimationHandle.cpp` and `AnimationHandle.hpp`, which expose one four-byte game-specific wrapper and the natural zero-initializing C++ default ctor, not compiler-patched code.
- An independent scan of **every currently configured canonical original function body** (not their source names) found **54 direct E8 calls into this *one* physical head across 22 distinct already-strict original native owners**. This is substantially more than one arbitrary caller.
- At least seven independently **game-owned full original constructors** prove the real storage roles: the complete **794B Player ctor** calls the native method at `0x004F4728` and `0x004F4736` for Player+0x60C and +0x610; the **498B Animation ctor** at `0x00448B40` calls it at `0x00448B79` for Animation+0x4C0; the **556B Bullet ctor** calls it at `0x0047BEE0` and `0x0047BF36`; the **765B EnemyState ctor** calls three times; the **941B Graphics ctor** calls once; **883B FrontInf** calls thirteen times; and **1,738B Dialogue** calls eight times. All seven original game-owned constructor bodies independently pass native canonical strict exact.
- Other exact native callers include Card, Bomb, Item, PlayerOption and PlayerShot construction, EffectInfo spawn, and EffectAnimationHandle construction. The game-owned specialized handle is actively used for resolving sprites, forwarding position, interruption and effect lifetimes across numerous original gameplay owners. This original identifier-state operation belongs to the authored game object model, although the compiler emits the method body from the source-level constructor.

These true PE E8 destinations and body roots were freshly decoded from the **immutable original executable**, independent of the historical prose notes. Counts include all physical call sites, not invented alternate native heads.

## Original byte-acceptance and nonoverlapping accounting

Previously configured pinned unit: `animation_handle_construct`, built from `src/AnimationHandle.cpp`, and strictly verified again:

`animation_handle_construct: exact (23/23 bytes)`

Independent game constructors separately strictly rechecked: `player_construct` **794/794B** (799B with compiler contribution), `animation_ctor` **498/498B** (503B complete), `bullet_ctor` **556/556B**, `enemy_state_ctor` **765/765B**, `graphics_ctor` **941/941B** (946B complete), `front_ctor` **883/883B**, and `dialogue_ctor` **1,738/1,738B**. They are independent original dataflow proof, not newly credited constructor bytes.

Private reproducible evidence: `.analysis/core679-animation-handle-default-ctor-original-owner.py/json` — every canonical source-owner original E8, the full 23-byte original, exact original-body hash, seven strongly identified gameplay constructors and their real physical call sites.

**Only origin tracking is changed**, from unknown review to authored high-confidence for this single distinct physical original method, with its preexisting canonical strict unit admitted to the exact authored ledger. No source/header or native object was edited; no cold replay beyond the already accepted independently rechecked eight original units, no global cold replay, no original target edit. Exact authored status becomes **502 complete whole original game functions / 179,518 disjoint native code bytes** from prior **501 / 179,495**. The separate 3,111B Player main-frame, 555B Player movement, 273B Bullet drawing group and 73B Animation factory remain NONEXACT.
