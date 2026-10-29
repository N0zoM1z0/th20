# CORE/RECON-557 — original 3,111B Player frame uses the exact 22-byte Timer POSTFIX increment ABI

Locked Japanese TH20 v1.00a Steamless original:
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**This is a source correction inside the entire 3,111-byte game-owned Player
main frame at `0x004F9C30`, not a newly exact original parent.** The
maintained whole source is `src/PlayerMainFrame.cpp`. The immutable
original body is **3,111B / 783 native i386 instructions**, SHA-256
`7f0bff5c2e175ff3d223c9e958fd908e39016b136fd1ff0eb0e1ce0cf6672467`.

## A mistaken but superficially equivalent original game call

The previous maintained Player source incremented the original
`Timer+0x2070` in the special-movement state using `++timer_2070`.
That selects the native **prefix** `Timer::operator++()` at
`0x00429400`, a separate **20-byte/ret** complete already-exact method.
The actual immutable original native Player main frame at
**`0x004F9CB9`** pushes the real ignored integer argument zero and
its direct **E8 at `0x004F9CBC`** invokes the distinct **22-byte
postfix** `Timer::operator++(int)` at **`0x00423540`**. Its native
`ret 4` consumes that original zero argument. Both exact Timer
methods ultimately call the same original `Timer::tick()`, but their
original ABI, physical original address, stack protocol, instruction
length and call target are **not interchangeable**. The native
original actually increments the same Player timer exactly once; there
is no justification for fabricating a second increment.

The **real corrected C++ source is now `timer_2070++;`**. Under locked
MSVC 19.44.35211 i386 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /EHsc` the complete new source emits the correct
`??ETimer@th20@@QAEXH@Z` COFF call, with **one** postfix and **zero**
wrong prefix calls. This compiler profile omits `/sdl` only for the
whole-source *nonexact* Player candidate; previous original native
analysis showed the original has no security cookie, whereas forcing
`/sdl` introduced a false cookie call. No canonical profile or header
has been changed.

The entire parent now compiles to **3,254B / 808 instruction heads**,
versus the original **3,111B / 783**. Ordered original mnemonic kinds
aligned improve from **730/783 to 733/783**; most important, the
actual postfix E8 original callee identity is restored. Both old and
new candidates emit **67 E8 + 37 DIR32** relocations, agreeing with
the original **67 E8 + 37 PE HIGHLOW** by *count*, not necessarily
original field site or destination. The separately original call census
`core557-player-parent-native-call-sequence.json` finds **60
identical known original physical callee heads in order**; several
unknown folded/source-only symbols cannot be resolved from a bare
COFF symbol alone. One decisive **remaining known mismatch** is
original 45B `EffectAnimationHandle::matches_value(0)` equality at
`0x00449430` versus the current source's 45B
`AnimationHandle::operator!=(0)` at `0x0047C650`.
They emit opposite boolean senses, are not linker-folded aliases,
and need a real type/receiver ABI correction. A reinterpret cast of
an existing four-byte `AnimationHandle` object to unrelated
`EffectAnimationHandle` would violate C++ object lifetime / type
rules: that shortcut is **not** adopted merely to match the native
call. Its correct original owning type must be reconstructed or a
sound representation established before exact admission.

Twenty private source variants also tested genuine `bool`, 32-bit
comparison and 8-bit focus assignments under the locked compiler.
None improved the complete 3,111B native instruction alignment, so
no code was committed solely to manipulate their stack temporaries.
Original immutable PE call-order and current actual compiled COFF
symbol checks live in ignored
`.analysis/core557-player-parent-native-call-sequence.json`;
new fresh whole-function compilation in
`.analysis/core557-player-main-timer-compile.log` and score in
`.analysis/core557-player-main-timer-verified-score.json`;
full bounded focus experiments in
`.analysis/core558-player-focus-original-type-probes.json`.

`src/PlayerMainFrame.cpp` still has **no canonical exact unit**, and
this is its only production source edit. No previously accepted source
or shared header, original PE byte, linker/manifest unit, match ledger
or exact-byte credit changes. There are **zero existing canonical
native units in the affected source** to cold replay. Running all
1,182 canonical units would neither validate the unresolved 3,111B
body nor be a relevant affected-only check. The entire original
555B Player movement function, 3,111B frame, Bullet 3,735B emitter
and Enemy ECL 41,967B dispatcher all remain **NONEXACT**. Authored
coverage remains **497 exact game functions / 175,691 distinct bytes**.
