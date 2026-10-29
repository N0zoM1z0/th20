# CORE/RECON-753 — native exact whole 282-byte Animation subtree retirement plus 43/37-byte handle chain

Original locked Japanese TH20 v1.00a Steamless: SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint closes **three entire, separate original game functions,
362/362 unique original .text bytes** from one coherent live Animation pool
retirement protocol. These are not replaced by a stub, thunk or original-code
prefix: all original executable instructions, including their real end RET,
and all independently verified PE relocation destinations are preserved.

| Original native start | Entire original bytes | Maintained source | Role |
| --- | ---: | --- | --- |
| `0x0044FB80` | **282** | `AnimationPoolOwner::mark_animation_tree_for_retirement(Animation*)` | Null guard, mark `Animation+0x570`, traverse actual `child_links[1]` intrusive iterator, recursively mark all descendant animations, safely destroy iterator on all normal paths |
| `0x0044FCA0` | **43** | `AnimationPoolOwner::retire_handle(uint32_t)` | Resolve actual handle through native `0x0044CD00`, forward the returned `Animation*` into the 282B recursive method |
| `0x0044FCD0` | **37** | `AnimationHandle::retire()` | Read actual `AnimationHandle::value`, call genuine `current_animation_pool` at original `0x005C0028` and real `0x0044FCA0`, then clear handle value to zero |

## Original native code/ABI evidence independently rechecked

Original executable disassembly confirms the 282-byte function starts with
SEH stack registration and security cookie, then `if (!animation) return;`,
sets the 32-bit field at `Animation+0x570`, calls the true
`AnimationChildLinks::operator[](1)` twice and tests the native list head,
constructs an `IntrusiveIterator<Animation>` and runs the original iterator
`advance/differs/get/node_access` protocol. Its actual recursive E8 at
function offset `+0xE8` lands back on `0x0044FB80`; a genuine iterator
destructor and security cookie epilogue complete the 282B function. The
original pointer owner of the recursion is the same `AnimationPoolOwner`
receiver as the 43B wrapper; no new owner allocation/storage was invented.

The first natural C++ branch form (`if (animation) { ... }`) compiled to
**281 bytes**, one byte short, due to a near conditional jump. Replacing it
with the equivalent natural early-return form (`if (!animation) return;`)
recovered the **original `jne` followed by the five-byte unconditional
`jmp`**, and all **282/282 bytes**, apart from genuine relocation operands,
then matched. This was a compiler-control-flow reconstruction from original
instruction evidence, not an ad hoc instruction patch.

For the 282B body **16 real relocation fields** were independently checked:
two original PE32 `IMAGE_REL_BASED_HIGHLOW` fields (actual
`0x0056863D` SEH handler, `0x005B25C0` compiler cookie) and fourteen
original native `E8` call targets (`0x004494B0`, `0x0040FF90`,
`0x0040C080`, `0x0044B9F0`, `0x00412540`, `0x00411C30`,
`0x00411BB0`, `0x0040C300`, `0x0040F160`, `0x0044FB80`,
`0x00411B00`, `0x005429EE` with genuine repeated destinations). The 43B
wrapper adds two real E8 `REL32` fields (resolve at `0x0044CD00`, recurse
at `0x0044FB80`). The 37B handle adds one true PE HIGHLOW (global
`0x005C0028`) and one genuine E8 call (`0x0044FCA0`). The manifest keeps
every one of these **20/20** field offsets/types/symbol identities/physical
original targets. No relocation was ignored or guessed from Ghidra alone.

## Narrow native build closure and strict proof

Pinned MSVC 19.44.35211, x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`. One new C++ translation unit,
`src/AnimationHandleRetire.cpp`, has **3/3 whole native canonical
functions exact** from its freshly compiled `build/core753-canonical`
object and receipt. The sole existing public-header modification is two
method declarations on `AnimationPoolOwner` in
`src/AnimationRuntimeOwner.hpp` (no object field/layout changes).

Actual preedit receipt include-closure contains exactly **15 old canonical
source/object providers and 31 previously exact strict native units**.
These, together with the **one new provider / three units**, were all
cold-compiled and exact-verified: **16 source objects /34 of 34 strict
native functions exact**, including the original 3,735B Bullet emitter,
1,518B Player option rebuild and 662B Bullet cancellation. No global or
unfiltered cold replay was run. The private reproducible verification script
and JSON evidence are in `.analysis/core753-scope-replay.py` and
`.analysis/core753-private-string-proofs.json` (intentionally not Git-tracked
source assets).

Exactly **two private MSVC `$SG` numeric symbol relabelings** arose from
the legitimate header declaration changes. Only the compiler-private
symbols were reconciled in `config/match-units.toml`:

- In complete old 662B `Bullet::cancel`, `$SG183133` became `$SG183137`:
  original PE HIGHLOW at original game code `0x0047C9B0` still points to
  native `0x0056FD14`, whose full original 7 bytes are `bullet` plus NUL,
  equal to the new real COFF private .rdata string.
- In complete old 298B `AnimationPoolOwner::allocate_animation`,
  `$SG79268` became `$SG79272`, after independently verifying identical
  nonrelocation original code bytes, unchanged real PE relocation and
  physical original absolute target, plus the **entire NUL-terminated
  compiler .rdata string equals the original immutable PE**.

For both, original source function bytes, literal values, immutable game
strings, relocation field offsets/types and absolute target addresses are
unchanged; the new string names are compiler-private bookkeeping only.
All 34 unchanged/new native units subsequently passed whole strict replay.

## Boundary of this milestone

The genuine original 12,140B /2,490-instruction `Bullet::run_extended_commands`
parent at `0x0047DCF0` now has **208/210 original E8 direct call sites
landing on source-present canonical whole-function heads**, versus 203/210
before the two focused batches. The only two outstanding original E8 target
heads are compiler-runtime helpers `__security_check_cookie` (14B at
`0x005429EE`) and `__allshl` (31B at `0x005432F0`); neither is extra authored
gameplay code. Original three dispatch tables still contain 34/8/11 genuine
original code pointers and 53 PE HIGHLOW fields; original parent has another
38 HIGHLOW fields. **The parent itself remains source-absent, NONEXACT and
not proven linked or playable.** Its complete 12,140B source-level dispatch
reconstruction is a serious separate task; 208/210 call-role coverage is
not 208/210 parent byte accuracy.

Original game-authored whole-function coverage for these two batches moved
from 556 distinct original functions /186,645 disjoint .text bytes to
**563 /187,092**. The second batch alone adds exactly **362 bytes** in three
complete functions. No original compiler/runtime or STL library method is
miscounted as gameplay code.
