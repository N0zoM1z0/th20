# CORE/RECON-789 — complete original 192-byte Animation draw-queue flush semantic source (NONEXACT)

> **Historical NONEXACT frontier, superseded by CORE/RECON-790:** the real 192-byte flush is now strict exact with genuine natural D3D9 argument materialization, full 55/55 native instructions and four independently original-PE-proven fields. See [complete exact proof](ANIMATION_DRAW_QUEUE_FLUSH_192_STRICT_EXACT_RECONSTRUCTION.md). Counts and mismatches below describe only the dated earlier source.

Locked Japanese TH20 v1.00a Steamless original SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint reconstructs **the complete behavior of the original
192-byte /55-i386-instruction custom game function at `0x004455C0`** in
maintained natural `AnimationPoolOwner::flush_draws()` C++. It is a key
batch/graphics-state barrier on the separately **5,993-byte Animation draw
Boss**, and is directly called from the separately strict-exact three
92-byte D3D9 `Graphics` cache transitions and previously exact 145-byte
Player draw orchestration. **The current source is NONEXACT** and receives
**zero original matched game-code credit**: 192B code size and 55 native
instruction kinds alone are not whole-byte equality.

## Independent complete original native mechanism

The immutable original entire `0x004455C0..0x0044567F` method stores ECX
as one real renderer-owner pointer and first tests a nonzero 32-bit
queued-primitive count at native owner offset **`0x06000E70`**. If the
count is zero, the native method returns without touching the D3D9 device
or batch buffers. On the nonzero path:

1. Get the **real** `Graphics::get_device()` from original global
   `process_graphics` at **`0x005C4D40`**, and invoke the actual D3D9
   vtable slot **`+0x164`, `SetFVF(0x144)`**. The FVF is exactly the
   D3D9 combination `D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1`.
2. Get the device *again*, not a fabricated cached global. Invoke the
   original D3D9 vtable slot **`+0x14C`, `DrawPrimitiveUP`**, with primitive
   topology **`D3DPT_TRIANGLELIST`** (native value 4), original number
   of primitives **two per queued entry**, actual active draw-stream pointer
   at owner+**`0x07C00E78`**, and genuine vertex stride **28 bytes**.
   The existing `SpriteTexturedVertex` native typed layout asserts that
   `sizeof(SpriteTexturedVertex)==28`.
3. Restore the active draw-stream pointer from owner+**`0x07C00E74`**
   into +`0x07C00E78`, zero the queue count at +`0x06000E70`, and
   increment the original draw-batch counter at renderer owner+`0xC4`.

These very large field offsets are real x86 operands; the maintained
source uses byte-offset views of the existing opaque `AnimationPoolOwner`,
**not** an invented 130-MiB padded public Renderer class. The true
D3D9 `graphics_api::Device` and shared `Graphics` owner already exist.
The original function never uses an invented fallback branch or fake ABI
trampoline.

The native return closes the **entire 192B/55-instruction** boundary.
Exactly **four** original executable relocation positions are independently
attested. The real PE32 `.reloc` section contains the two
`IMAGE_REL_BASED_HIGHLOW` fields at original **`0x004455DA`** and
**`0x00445601`**, both pointing to actual `process_graphics` at
`0x005C4D40`. The original E8 at **`0x004455DE`** and **`0x00445605`**
physically call the actual `0x00412730` `Graphics::get_device()` shape,
which is folded with another preexisting accepted tiny value getter;
**no duplicate 17B original function byte credit** is awarded here.
Indirect virtual D3D9 calls are not counted as original direct E8.

## Natural whole-method C++ and precise still-open compiler gap

An isolated pinned MSVC 19.44.35211 x86 compile of
`src/AnimationDrawFlush.cpp`, `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc`, creates **192 C++ bytes /55 disassembled x86 instructions
with four genuine COFF field types and offsets**, matching the *number*
of original native instructions and full physical method length. This is
not accepted strict exact: the candidate still has **23 nonrelocation byte
differences**, concentrated around the different evaluation order of the
D3D9 virtual `DrawPrimitiveUP` function-pointer expression and its two
natural temporary arguments. The original loads the virtual function
pointer **before** calculating/storing the active stream and doubled
primitive count; the pinned C++ source currently calculates the two natural
arguments **before** reading the virtual function pointer. Both orders
preserve intended submission semantics in this context, but produce
observable different native register and stack operand bytes. The genuine
physical global/E8 reference roles do not resolve this codegen gap.

The scoped hypothesis work explored direct inline operands, named
primitive count, named vertex stream, both declaration orders and typed
`SpriteTexturedVertex` stride. Their compiled whole-function sizes ranged
**179..192 bytes**, but no candidate passed whole native byte equality.
Those private, unaccepted probes live in ignored
`.analysis/core786-*`, `.analysis/core787-*`, `.analysis/core788-*` and
`build/core786-probe/..build/core789-probe/`. No source claim was inferred
from the old Ghidra function pseudocode.

The expanded independent original PE test
`scripts/repo-python scripts/verify-animation-draw-boss-native.py`
reads all 55 original flush instruction heads, two actual PE HIGHLOW
fields and two signed original E8 destinations, checks the true
SetFVF/DrawPrimitiveUP slots and exact primitive/stream/count fields.
It also continues to attest the **entire** original 5,993B draw Boss,
both original switch tables (49+31) and all seven previously strict game
children (four Animation accessors and three Graphics transitions).

**No prior canonical compiler input was modified.** This checkpoint adds
only a new, noncanonical full-source file, one source-present/author-origin
ledger mapping and original-PE validator evidence. Therefore the required
cold replay scope is **zero**, with no all-graph replay. The separate
Graphics original **92/92 +92/92 +92/92B strict** methods retain their
protected receipts and original native identity.

Source-present mappings increase **1,221 →1,222**, but strict game-authored
whole-original coverage stays **576 complete functions /188,433 disjoint
.text bytes**, with **1,223 strict canonical units /251 object providers**.
Both `0x004455C0` 192B batch flush and `0x00443880` 5,993B draw parent
remain **NONEXACT** and no whole-game linkage/playability is asserted.
