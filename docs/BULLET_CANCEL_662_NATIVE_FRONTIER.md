# CORE/AUDIT-230 — the complete 662-byte Bullet cancellation boss remains open

**Source of truth:** immutable Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This document records an independent new inspection of the *entire* native
`0x0047C8F0..0x0047CB85` Bullet cancellation method, its actual downstream
protocols, and attempted whole-body natural C++ source. This is an **audit,
not a newly accepted exact source unit**.

## Original native function boundary and gameplay flow

The complete target is **662 bytes**, **199 x86 instructions**, **25 direct
calls to 21 distinct addresses** and four direct branch instructions.
Complete native interval SHA-256:
`d84cb64c727fb55c36bff760745ebc8ff3b815cd71a10f77199f6911bfbc82e1`.
The original 662B method is independently called by **six** game-owned
Bullet controller functions at `0x0047CB90`, `0x0047CC90`, `0x0047CF60`,
`0x0047D100`, `0x0047D240` and `0x0047DCF0`. Two of those callers are
already complete and exact (`cancel_all` 242B, `cancel_near` 320B), as is the
401B capped radial cancellation at `0x0047CF60`; none grants exactness to
their 662B child.

The complete native cancellation control flow:

1. Save the genuine Bullet `view_index` at +`0x51C` and select that view
   through the real animation process manager pointer at `0x005C0028`,
   method `0x004776A0`. Activate its live animation at `0x00477450` and
   send the actual `AnimationHandle` at +`0x5C` through native `0x00479040`.
2. Unless BulletFlags bit 9 is set, conditionally spawn a cancellation
   animation if the original signed `cancel_script` at +`0x34` is
   nonnegative. The real `Context::bullet_controller()` and its existing
   exact `animation_file()` accessor supply the owner. The original
   `AnimationFile::spawn` call is at `0x004790E0` and returns a typed
   `AnimationHandle` with a hidden result pointer. The caller then stores
   the handle by Bullet index +`0x28` using the actual `0x00486390`
   mapping operation.
3. Flags bits 11..12 determine additional game effects. Mode 1 retrieves
   the stored cancellation handle through `0x00485690` and invokes its
   native `0x00486350` wrapper. Mode 2 constructs genuine 56-byte
   `EffectParameters`, copies the position but zeros Z, carries the
   original packed color and creates a real effect through
   `Context::effect_info()` and native `0x0049DB70`.
4. When bit 9 is clear, request native positional sound effect `0x47`
   using the live Bullet position X, then call the whole 419-byte
   `Bullet::cancel_drops` at `0x0047D3D0` with actual position and mode.
5. Update the live position through the genuine game operators for
   `position += (velocity * float(default_timer_clock)) / 2.0f`,
   set state +`0x50` to 4, reset two separate native Bullet Timers
   (+`0x4D8` and +`0x4E8`) through `0x0047C5F0` with native 1.0f,
   assign zero to Timer +`0x4F8`, restore the original animation view
   and return integer zero through the locked security-cookie epilogue.

## Whole-body compiler probes, evidence and remaining mismatches

A complete natural C++20 trial was compiled against the real typed Bullet,
Animation, EffectParameters, ClockScalar and Context objects, with *private,
provisional external ABI declarations* for unowned animation manager and
nonexact helper methods. The locked MSVC 19.44 x86 profile uses `/Od /Ob0
/GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

The initial complete source emitted **656 bytes** versus the native
**662 bytes**, and 190 of the 199 native instruction mnemonics aligned in
sequence. Twelve explicit alternatives varied cancellation script/index
capture, hidden-return handle binding and vector-clock expression grouping.
Their **whole** emitted sizes were 640, 641, 646, 647, 655, 656, 661,
662, 667, 671, 676 and 680 bytes. The **662B candidate is *not* exact**:
it matches only **245/526 non-relocation bytes**, because its local frame,
result-pointer ABI and register allocation differ from original code. One
667B candidate matches 197/199 instruction mnemonics but still has a
mismatched stack frame and `Vector3` result temporaries. Equal size or
mnemonics do not qualify as native byte-for-byte reconstruction.

The outstanding source/ABI questions, rather than guessed answers, are the
true animation spawn hidden-result / index-mapping local-object lifetime,
the result passed to the native animation-handle update wrappers, the effect
creation return owner, and exact C++ evaluation order for two chained
`Vector3` temporary return objects and native 2.0f division. Use
independent native call/result evidence before changing maintained owner
storage. In particular, **do not import fake local Renderer layouts or
compiler-shaping declarations** from private probes, infer all relocation
anchors from a compared target field, or accept a partial native prefix.

The 3,735B original `BulletController::emit` at `0x004818E0` and 41,967B
Enemy opcode root at `0x0048C010` likewise remain open whole functions.

**Private scoped evidence** retained without adding canonical credit:
`.analysis/core227-native-BulletCancel.asm` (full native disassembly),
`.analysis/core230-BulletCancel-probe.cpp`,
`.analysis/core230-full-cancel-variants.py`, and
`build/core230-probes/*.obj` with per-compile receipts. No maintained
reconstruction source, tracking ledgers, or canonical matching inputs are
changed by this audit; thus **zero units require replay**, and no
unfiltered cold replay was executed.

## CORE/EXACT-232 follow-on — genuine 419B item-drop callee now exact

The entire original `Bullet::cancel_drops` at `0x0047D3D0` is now maintained
in `src/BulletDrops.cpp` as **419/419 canonical byte-exact**, with all
20 native relocations. Its actual original four-edge predicate at
`0x00485390` is also **136/136 exact** in `src/BulletScreenBounds.cpp`
(5 native relocations). The larger **662-byte** `Bullet::cancel` source
remains **nonexact**: restoring these two downstream complete functions
does not implicitly repair the boss's missing local/return-object ABI.
See [complete drops and bounds proof](BULLET_DROPS_AND_SCREEN_EXACT_RECONSTRUCTION.md).

## CORE/AUDIT-234 — native float Timer assignment dependencies

An additional independent complete PE disassembly identifies two original
functions called along the native 662-byte Bullet cancellation chain:

- `0x0047C5F0`, **33 bytes**, acts as a genuine 16-byte Timer member's
  float assignment wrapper: it loads the original float argument, passes it
  to native `0x004841F0` in the MSVC x86 `__thiscall` ABI and returns with
  `ret 4`. The exact original wrapper has 13 x86 instructions and SHA-256
  `evidence in .analysis/core234-native-47c5f0.asm`.
- `0x004841F0`, **103 bytes**, is the original float-set implementation.
  Only if `flags & 1` is clear does it invoke Timer reset at `0x00423F50`,
  set mode zero through `0x00423FE0`, and set the initialized bit.
  It then sets `current = trunc(float_value)`, writes the *untruncated*
  float to `current_fraction` at +8, and sets
  `previous = trunc(float_value - 1.0f)` using the independent original
  `0x0056C8CC` float constant. The original method must **not** be
  confused with the already accepted `Timer::set(int)` overload; its
  truncation/previous-value semantics differ for nonintegral input.

The actual native call graph includes two `0x0047C5F0` invocations from
`Bullet::cancel` at `0x0047CB34` and `0x0047CB50`. Other attested direct
callers include the 3,735-byte Bullet emitter `0x004818E0` and
`0x00484A20`, `0x00485B60`, `0x0049CAE0`, `0x004D3230`.
Complete native disassembly is saved under ignored
`.analysis/core234-native-47c5f0.asm` and
`.analysis/core234-native-4841f0.asm`. Both functions remain **nonexact**:
no made-up free function, fake Timer layout or incorrect `__fastcall`
stand-in is admitted to the maintained source. `Timer.hpp` alone currently
appears in **93** canonical source providers and **593** strict units, so
any real shared member declaration must be followed by its true affected
closure, not a claim based only on the two Bullet sites. No code changed
and no cold replay was needed for this audit.
