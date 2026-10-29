# CORE/EXACT-520 — exact original 338B Animation script-loader boss and 21B VM-forward wrapper

Immutable comparison PE: Japanese TH20 v1.00a Steamless
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Two complete, independently disjoint game-authored original physical
functions are now strict native exact: `0x004383A0` (338/338B,
93 complete x86 instructions) and `0x00435500` (21/21B,
9 complete instructions).** These add **359 newly exact original
game-body bytes** and two canonical native units. They do not make
the separate 39,470B Animation VM at `0x0042B5D0` exact, nor claim
that the entire Bullet emitter or game runtime now links.

## Correcting a wrong large-boss original call target

Independent original native E8 xrefs show that the entire 3,735-byte
`BulletController::emit()` calls physical **`0x004383A0` at
`0x004822C5`** to load a new Animation file script. The preceding
maintained emitter draft instead called the **32-byte**
`AnimationFile::bind_animation(Animation*,int)` wrapper at
**`0x00438380`**, itself forwarding into the distinct **194-byte**
`AnimationFile::bind_animation(Animation*,int,Animation*)` at
`0x004382B0`. This was a real original caller/behavior mismatch,
not a cosmetic naming issue. The original `0x004383A0` method is
neither wrapper and must not be silently folded into them.

The emitter's natural maintained source `src/BulletEmitter.cpp` now calls
a separately typed **`AnimationFile::load_script(Animation*,int)`**
method declared on the actual `src/AnimationFile.hpp`, implemented in
`src/AnimationFileScriptLoad.cpp`. This restores the authentic
original call target without a fake trampoline, arbitrary C++ cast,
assembly shim, partial original prefix or duplicate game-body credit.
The descriptive modern name does not assert historical source spelling.

## Recovered complete real 338-byte script-loading behavior

The original x86 loader first examines the real file's script-pointer
array at `AnimationFile+0x54`. If the indexed pointer is null, it
zeroes the **entire 0x5E4-byte real Animation object** through the
native CRT `memset`. Otherwise it obtains the actual `std::atomic`
state at `AnimationFile+0x5C` through the native **21-byte**
`std::atomic<uint32_t>` implicit-load wrapper at `0x004292C0`.
This state is converted to a boolean before short-circuiting into
the zeroing branch. That real C++ conversion, `if (scripts[index] ==
nullptr || stage)`, emits the original six-byte-boolean-control-flow
instruction sequence; a superficially equivalent explicit unsigned
comparison eliminated the original local and shortened the function.

The loaded-script path uses true, already modeled Animation fields:

- `AnimationBase+0x440` writes the 16-bit script index and the two
  game file-id words at Animation+`0x18`/`0x1C`.
- Mode byte at Animation+`0x4A0` first clears its **high two bits**,
  then sets low-two-bit mode to **2** in a separate byte operation.
  At the end, the low mode **2** transitions to mode **1**.
- The script index and current frame are published at Animation+
  `0x24` and `0x28`.
- Real Timers at `0x4D8` and `0x4C8` are reset to zero through two
  original integer-assignment member calls.
- The observed Animation flag bit at `0x49A` is cleared; the
  real entry callback slot at `0x5DC` is set to null.
- The actual Renderer owner receives the Animation instance through
  the separate **21-byte** VM-forward wrapper; its original writable
  script counter at Renderer+`0xB8` is incremented using **two independent
  global pool pointer loads**, as in the original assembly. The full
  Renderer layout remains opaque; only this independently observed
  32-bit slot is accessed, not a fabricated padded owner struct.

Original MSVC `/Od` code reads the mode byte using an **8-bit** `mov
DL,[ECX+0x4A0]` followed by `and dl,0x3f`; treating it as a generic
`std::uint8_t &= 0x3F` expression promoted to a 32-bit zero-extended
load and emitted **339 bytes instead of 338**. The semantically
accurate actual bitfield assignment
`animation->base.flags.bits_08.other_6_7 = false;`
uses the existing typed `AnimationModeBits`, restores precisely the
native byte load and lands on the **entire 338-byte, 93-instruction
original**. This is native field semantics, not compiler padding.

## Complete 21-byte Renderer VM forwarding wrapper

The new `src/AnimationPoolUpdate.cpp` implements
`std::int32_t AnimationPoolOwner::update_animation(Animation*)`, the
original physical wrapper `0x00435500..0x00435514`. It passes the
real Animation pointer to `Animation::update()` at **`0x0042B5D0`**
with thiscall/stack argument cleanup and preserves the native integer
return in EAX. The first draft used `void` and emitted an extra
`nop` after the VM call, producing **22 bytes**; the correct integer
return ABI emits the full original **21/21**. The 39,470-byte child VM
is a **separate unfinished original function**, so exactness of this
21B caller is not evidence of its implementation.

## Independently anchored original E8 and PE HIGHLOW proof

The original PE was decoded through each entire return (338B/93 heads
and 21B/9 heads). Its native E8 fields and *actual original* PE
`.reloc` HIGHLOW fields were read independently of the compiler object.
The 338B loader contains exactly **five** original E8 calls:

| Original field | Original destination | Role |
| --- | --- | --- |
| `0x004383BF` | `0x004292C0` | atomic implicit value conversion |
| `0x004383E5` | `0x00544760` | CRT complete `memset` |
| `0x00438461` | `0x00423520` | first Timer integer assignment |
| `0x00438471` | `0x00423520` | second Timer integer assignment |
| `0x004384A2` | `0x00435500` | genuine 21B Renderer VM forwarder |

Its exactly **three** original PE HIGHLOW fields at
`0x0043849D`, `0x004384A7`, `0x004384B6` all independently target
real writable Renderer pool pointer **`0x005C0028`**. The additional
whole 21B wrapper has a single original native E8 field at
`0x0043550B` targeting the genuine unfinished Animation VM
`0x0042B5D0`, and **zero original PE HIGHLOW** fields.
All **9/9 independently original field positions, types and native
destinations** match the actual new MSVC COFF relocation identities
and ordinary addends; all remaining **306/306 and 17/17** nonrelocated
original bytes match at their original positions. Full original body
SHA-256 values: **338B** `a96d39d3c73a43b417f761b62ea12473f64d02c3d7e5316d7a90632f12897cd0`;
**21B** `9b8404a1b636b48b5c320a4e39c4f7f0d26b56176db5a25a7211f34c1dfa813d`.

Pinned compiler: MSVC 19.44.35211 i386 C++20
`/Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise` for these two new
independent native source objects. Full strict canonical commands
`compare-coff-function.py --unit animation_file_load_script_whole --json`
and `--unit animation_pool_vm_forward --json` both return **exact**,
not merely structural-exact. Scoped replay: **2/2 new canonical
units**, two new canonical COFF providers. Independent original code
and relocation proof is preserved in
`.analysis/core520-animation-native-original-relocation-proof.json`,
with fresh compiler receipts and strict compare output in
`.analysis/core520-script-canonical-compare.json`,
`.analysis/core520-pool-canonical-compare.json`, and the two-object
`.analysis/core520-two-animation-units-scoped-replay.log`.

## Source-header regression and pending large bosses

Public `src/AnimationFile.hpp` and `src/AnimationRuntimeOwner.hpp`
now carry the two real original method ABIs. Existing canonical
compiler receipts were inspected **before** these edits to freeze
the actual dependent closure: **61 source/object providers and 266
old whole native strict units**. Every one of these 61 real compiler
providers was cold rebuilt under its own existing pinned flags,
and every one of the **266/266 original native units strictly
replayed exact** after the changes. These include whole Animation
reset/motion/operand routines, 1,404B Bullet command-11, Player
1,518B option rebuilding, HUD/Dialogue, Enemy and original resource
constructors. **No unfiltered global cold replay was run.**

Twelve MSVC-private source-string `$SG` labels changed numerically
because of the real public declaration edits. For each one, the
full original PE field and destination, the complete original string
payload and actual new compiler source symbol were independently
verified; only the private label spelling in its existing canonical
manifest was updated, not the original relocation offset or target.
This includes the original Bullet `"bullet"`, Dialogue `"text"`,
Enemy/Front/Player initializers and original diagnostic literals.
Complete original-byte audit, list of the twelve independently
resolved labels and focused replay are in
`.analysis/core520-animation-header-266unit-byte-audit.json`,
`.analysis/core520-scoped-animation-header-build.log` and
`.analysis/core520-animation-header-266unit-scoped-replay.log`.

**Authoritative game-authored exact count: 452 / 153,901B before, now
454 / 154,260 original disjoint bytes. Source-present and canonical
strict units both increase from 1,178 to 1,180, unique pinned
MSVC source/object providers from 238 to 240.** The original
3,735B Bullet emitter now calls the correct 338B loader but remains
**NONEXACT** (the real compiler still differs in shared_ptr move ABI,
branch layout and two switch tables). The **39,470B Animation VM,
12,140B Bullet controller dispatcher, 555B Player movement and
3,111B Player main-frame** also remain separate open whole functions.
This checkpoint does not prove a full game link, original global
compiler flags, or playable-game runtime.
