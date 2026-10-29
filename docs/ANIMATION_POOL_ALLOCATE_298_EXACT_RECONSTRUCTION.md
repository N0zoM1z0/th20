# CORE/EXACT-525 — complete original 298-byte Animation pool allocation/reuse boss, native strict exact

Immutable Japanese TH20 v1.00a Steamless original executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Entire original game-owned physical `0x0044C9B0..0x0044CAD9` now
reconstructed and strict native exact: 298/298 bytes, 78/78 original
i386 instructions, 14 original E8 direct call fields and two native PE
HIGHLOW absolute fields, all independently corroborated.** This is a
*complete original real C++ method*, not a cropped body, hand-authored
assembly, artificial local, NOP patch or merely an exact leaf.

The original complete 3,735B `BulletController::emit` has a direct native
E8 at `0x00482241` calling this 298B `AnimationPoolOwner::allocate_animation()`
owner; it also calls the separately whole-exact 338B direct AnimationFile
script loader and 21B VM-forward wrapper. The entire Bullet emitter
is **still NONEXACT**: do not credit its original instructions because
the allocator and loader children are now exact.

## Entire original allocation and recycling path

The original Renderer/Animation owner is large and remains only partly
identified. We do **not** declare a fake full Renderer prefix, pad a
96-MiB array, invent its class hierarchy or claim original renderer
startup. The original native x86 independently proves that the real
intrusive Animation free-list is at **Renderer+`0x06000718`**. The
maintained source, `src/AnimationPoolAllocate.cpp`, uses the real
existing `IntrusiveList<Animation>` and a localized, documented
byte offset to that genuine member, pending a complete Renderer
class reconstruction.

The original function checks that genuine free-list **twice** through
the native `IntrusiveList<Animation>::front()` call. If it contains a
node, it retrieves the real `Animation*` directly through the typed
`IntrusiveLink::node_value()`. The original x86 then:

- Detaches the **real `PooledAnimation::free_link` at +`0x5E4`**,
  reusing one existing 0x600-byte PooledAnimation slot rather than
  constructing a new Animation.
- Restores the **original Animation index at Animation+`0x4C4`** from
  the PooledAnimation index word at +`0x5FC`. The prior private source
  hypothesis wrongly stored this word in `AnimationHandle` at
  +`0x4C0`, a *different* field and an important gameplay error.
- Marks the pool slot **active = 1** at +`0x5F8`, then executes the
  real original whole-exact **1,106B `Animation::reset`** and real
  **32B `clear_pending_fields`**.
- Clears real `parent_558` and `parent_55c`, reinitializes the actual
  Animation link at +`0x4EC`, and reinitializes both typed child links
  through the real `AnimationChildLinks::operator[](0/1)`.
- Returns this same recycled Animation.

If the free list is empty, the method instead asks the actual
`DiagnosticAllocator` to create a new Animation with the authentic
original source-label literal. It resets the Animation, clears pending
callbacks, initializes the **index at +`0x4C4` to `0xFFFF`**, and
returns the newly allocated object. The distinct **73B native
`DiagnosticAllocator::allocate_object<Animation>` at `0x00447800`
is not independently exact yet**: this full original method can be
strictly equivalent while the freshly called allocator template
remains a separate native-link/frontier concern.

The original source-label constant at PE `0x0056E5BC` is the complete
null-terminated debug annotation
`D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\sprtlib.cpp:2888 SprtInf`.
Both its original full bytes and the actual new compiler-local
`$SG` literal payload were independently checked before mapping the
native original PE absolute reference, not inferred from one another.
This label is historical game provenance and does not establish the
original modern C++ symbol/class name.

## Why the exact codegen needed genuine ownership corrections

The earlier candidate used a valid but non-original intermediate
`IntrusiveLink<Animation>*` local after the second `front()` call.
Under the pinned `/Od` MSVC i386 compiler, this caused an extra
`mov [ebp-0x10],eax` and an unnecessary stack frame slot. In the
**actual original** the second `front()` return value goes **directly**
into the typed `node_value()` receiver. Modeling the true original
expression-lifetime relationship eliminated the artificial C++ local
and recovered the original stack layout and native call sequence.

Separately, the original has two physically real source code roles at
`0x0040FF90`: a 17B `Timer::operator int` getter and the
`IntrusiveList<Animation>::front()` read of its `next` pointer at
+4. The generic `front()` template in the existing shared header
currently calls another getter and compiles to 19B on its own. The
pool source therefore provides a **real typed explicit specialization**
for `IntrusiveList<Animation>::front()` returning its actual `next`
member, so the complete specialized 17-byte native source matches
the same immutable original physical 17B head at `0x0040FF90`.
This is a semantic member operation, not a hard-coded timer function
call or artificial native trampoline, and **zero additional native
original bytes** are credited for the folded source role.

The same source object independently emits the complete real generic
`IntrusiveLink<Animation>::node_value()` **16/16B** folded with the
original `0x0040C300`, `detach()` **55/55B** at `0x00411CE0`, and
`initialize(Animation*)` **61/61B** at `0x0044A670`.
Their ordinary original E8 relocations were compared separately
where necessary; these are **four existing physical original helper
bodies**, not newly claimed extra game functions.

## Immutable native PE reference proof

The original game PE was decoded from the entire 298B native function
through the physical return, producing 78 x86 instruction heads.
**14 genuine E8 direct calls** were recovered from native original
`E8` opcode operands, and **two native HIGHLOW** fields were read
separately from the immutable PE's actual `.reloc` blocks. The
latter are precisely the original debug label at `0x0056E5BC`
and the actual `DiagnosticAllocator* process_allocator` global at
`0x005B8894`.

All **16 original reference offsets, field kinds and absolute original
destinations** agree with the real pinned compiler COFF relocation
names and natural addends: front at `0x0040FF90` (twice),
`node_value` at `0x0040C300`, detach at `0x00411CE0`, reset at
`0x004299D0` (twice), pending-field clear at `0x00429E30` (twice),
node initializer at `0x0044A670` (three times), child array indexing
at `0x004494B0` (twice), and native allocation at `0x00447800`.
**Every one of the remaining 234 nonrelocated original bytes is
identical**. None of these original destinations was chosen by solving
it backwards from a candidate relocation field.

Private independent full original PE and physical helper evidence:
`.analysis/core525-pool-native-full-original-relocation-proof.json`
and `.analysis/core525-pool-original-anchor-proof.log`. Probe history
and semantic fixes:
`.analysis/core522-pool-variants-results.json`,
`.analysis/core523-pool-source-evaluation-results.json`, and the
folded-helper `.analysis/core524-*` compiler probes.

## Native strict canonical acceptance and scoped validation

The maintained **entire 298B original source** is
`src/AnimationPoolAllocate.cpp`; it does not modify any previously
accepted shared header or source file. New strict unit
`animation_pool_allocate_whole` uses real
`build/core525-canonical/AnimationPoolAllocate.obj` and existing
locked MSVC 19.44.35211 x86 C++20 profile
`/nologo /c /std:c++20 /Od /Ob0 /GS- /Gy /Zl /arch:SSE2
/fp:precise`. Its official whole canonical
`compare-coff-function.py --unit animation_pool_allocate_whole --json`
reports **`exact` (298/298 bytes, 16/16 original anchored fields)**.
The sole affected fresh canonical source/object provider and
**one complete new original unit** were cold built and **1/1
strictly replayed exact** using `--existing-objects --source
src/AnimationPoolAllocate.cpp`. Private canonical compiler/receipt,
full JSON and replay evidence are in
`.analysis/core525-pool-canonical-compile.log`,
`.analysis/core525-pool-canonical-strict-compare.json`, and
`.analysis/core525-pool-one-unit-scoped-replay.log`.

**No full cold replay** and no old unit rebuild were needed, since no
old source or header compiler input changed. Game exact coverage grows
from **454 / 154,260B** to **455 / 154,558 distinct original bytes**;
canonical units/source-present functions grow **1,180 -> 1,181** and
unique native compiled object providers **240 -> 241**. The
39,470B Animation VM, 3,735B emitter, 3,111B Player main frame and
555B movement still remain open. The exact 298B pool boss does not
prove a complete renderer implementation, final linker ICF choices
or playable game runtime.
