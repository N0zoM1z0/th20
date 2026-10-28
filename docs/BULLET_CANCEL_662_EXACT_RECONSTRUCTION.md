# CORE/EXACT-250 — full 662-byte native Bullet cancellation boss

The immutable target is Japanese TH20 v1.00a Steamless, original executable
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete original `0x0047C8F0..0x0047CB85` is **662 bytes**, **199 x86
instructions** and **34 independent native relocation anchors**. Its
interval SHA-256 is
`d84cb64c727fb55c36bff760745ebc8ff3b815cd71a10f77199f6911bfbc82e1`.
Maintained natural C++20 lives at `src/BulletCancel.cpp` as the entire
`Bullet::cancel(int)` method, not a switch arm, prefix, embedded byte array
or fabricated assembler. Original source spelling remains inferred.

## Original typed animation, effect, drop and Timer protocol

The source preserves the current Bullet view at +`0x51C`, selects it via
native `AnimationPoolOwner::select_view` at `0x004776A0` using the actual
global manager pointer `0x005C0028`, activates the live Animation via
`0x00477450`, and passes the real `AnimationHandle` via the native fastcall
**mode-1** wrapper at `0x00479040`. Under the original bit-9-clear branch,
a nonnegative `cancel_script` causes a true `Context::bullet_controller()`
and `BulletController::animation_file()` lookup followed by real
`AnimationFile::spawn` (`0x004790E0`) and a hidden-result `AnimationHandle`.
The caller reads **the returned object through EAX**, stores it in the
Controller's actual handle index map (`0x00486390`), and selects extra
handle/effect handling based on BulletFlags bits **11..12**.

Mode 1 loads the mapped handle through actual `0x00485690` and forwards it
through the **distinct mode-3** fastcall wrapper at `0x00486350`. Independent
Ghidra analysis confirms that `0x00479040` and `0x00486350` call the same
native low-level `0x0044EF90` with differing arguments **1** and **3**:
collapsing them to one source function would be semantically wrong even
when a structural byte comparison accepted the caller. Mode 2 constructs
real 56-byte `EffectParameters`, copies the three-lane Bullet position,
zeros Z, retains packed color, and calls actual
`EffectInfo::spawn_effect` (`0x0049DB70`) using its correct hidden
AnimationHandle-return ABI. The original unused effect result is discarded.

The bit-9-clear path then requests native positional SoundInf effect
**0x47** using Bullet X through `0x00426EB0` and calls the independently
exact full **419-byte** `Bullet::cancel_drops(position,mode)` at
`0x0047D3D0`. The function advances all three position lanes through
actual native `Vector3::operator*(float)`, `Vector3::operator/(float)` and
`Vector3::operator+=` with `float(default_timer_clock)` and literal
**2.0f** (original `0x0056C8D0`). It sets state 4 at Bullet+`0x50`,
assigns **1.0f** to two separate real 16-byte Timer members at
+`0x4D8` and +`0x4E8` through the already exact native
`Timer::operator=(float)` (`0x0047C5F0`), sets Timer+`0x4F8` to integer
zero, restores the original process animation view and returns zero
through the real native security-cookie epilogue.

## Resolving the complete compiler differences

Prior private whole-function attempts emitted **640–680 bytes**; one
662-byte early candidate was **not** exact (only 245/526 comparable bytes).
A later complete source produced **676 bytes** with all 199 instruction
mnemonics aligned but a redundant SSE scalar spill for an external
`const float` divisor. Using the original C++ literal **`2.0f`** emits the
correct `__real@40000000` relocation and removes the unwanted spill,
reducing the source to **663 bytes**. The last byte and pervasive
four-byte stack-local shifts originated in the hidden result of
`AnimationFile::spawn`, and an unnecessary named local for the unused
EffectInfo return. Accessing `spawn(...).value` directly follows the
original `mov ecx,[eax]`, and discarding the unused effect return
produces the identical original local frame with the meaningful
handle/index value-copy protocol. The final source emits **662/662 native
bytes**, **199/199 original instructions** and **526/526 comparable bytes**.

All **34** relocation offsets, COFF types, actual native destinations and
original method/data identities are independently corroborated from the
locked original Ghidra/Capstone observations, including the two distinct
handle wrappers and the real native Timer, SoundInf and BulletDrops
functions. The canonical manifest does not infer these solely from target
fields and includes no exemptions. Locked MSVC 19.44 x86 C++20 profile:
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
Original whole-body strict replay: **662/662 bytes**, in
`.analysis/core250-bullet-cancel-canonical-replay.log`.

Four production headers receive only true narrow member declarations:
`Animation::activate_display`, `AnimationPoolOwner::select_view`,
`EffectInfo::spawn_effect`, and
`BulletController::store_cancel_handle/get_cancel_handle`. Their
independent native implementations remain external; no fake giant Renderer
layout or invented source implementation is introduced.

The actual historical MSVC include-receipt closure for these headers
contains **52 preexisting source providers / 250 previously accepted
exact units**. All were freshly compiled and **250/250 complete strict
native units replayed byte-exact**. Local compiler-private `$SG` diagnostic
string symbol numbers moved in a few owners; corrections were permitted
only for a `$SG` name after confirming **unchanged relocation offsets,
COFF types and independently fixed native target data addresses**, then
the source-specific strict replay passed again. With the new root:
**251/251 exact affected units across 53 freshly compiled objects**.
No unfiltered whole-repository cold replay ran. Proof logs:
`.analysis/core250-bullet-cancel-affected-replay-part-{0..4}.log`,
`.analysis/core250-bullet-cancel-sg-corrections.jsonl`, and private full
source/ABI trials `.analysis/core249-*` and `.analysis/core250-*`.

Earlier `BULLET_CANCEL_662_NATIVE_FRONTIER.md` nonexact reports were correct
for their dated candidates but are now superseded by this exact whole-body
admission. The original **273-byte** single Bullet draw, **3,735-byte**
`BulletController::emit`, **12,140-byte** Bullet update, and **41,967-byte**
Enemy opcode root remain separate open whole-function reconstruction goals.
A strict local source/codegen proof is not a full game link/runtime claim.
