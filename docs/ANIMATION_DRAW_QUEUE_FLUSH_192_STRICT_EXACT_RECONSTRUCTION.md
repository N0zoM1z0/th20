# CORE/RECON-790 — original whole 192-byte Animation draw submission queue flush is strict exact

**The complete original function at `0x004455C0` is now strict exact:
192/192 original .text bytes, 55/55 x86 instruction heads and all four
independently original-PE-proven relocation fields.** The original is the
locked Japanese TH20 v1.00a Steamless binary, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The maintained natural game C++ is `src/AnimationDrawFlush.cpp` as
`AnimationPoolOwner::flush_draws()`, under its pre-existing ABI. The
previous complete 192B/55-instruction but 23-byte-different candidate
was genuinely NONEXACT and remains historical evidence under
[CORE/RECON-789](ANIMATION_DRAW_QUEUE_FLUSH_192_NATIVE_SOURCE_FRONTIER.md).

## Original full native behavior and externally verified relocation roles

The native owner has the original queued count at +`0x06000E70`, current
stream pointer at +`0x07C00E78`, stream reset pointer at +`0x07C00E74`
and draw batch counter at +`0xC4`. If the count is zero, no graphics
submission occurs. On the nonzero branch, the function obtains the actual
`Graphics::get_device()` from the shared `process_graphics` owner, calls
the real D3D9 `SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)` with
native FVF `0x144`, obtains the device again (not an unproven local singleton),
then calls the true `IDirect3DDevice9::DrawPrimitiveUP` vtable slot at
`+0x14C`. It supplies native `D3DPT_TRIANGLELIST` (4), **two primitives
per queued item**, the genuine current draw-stream pointer, and the real
28-byte `SpriteTexturedVertex` stride. It then resets the stream pointer,
zeros the queue count and increments the real draw-batch counter. Its whole
original 192-byte function ends at original `ret` at `0x0044567F`.

The original executable independently attests all **four** x86 relocation
fields, not taken from the compiled C++ target bytes:

| Original field | Type | Physical original destination |
| --- | --- | --- |
| `0x004455DA` (`+0x1A`) | original PE HIGHLOW | `0x005C4D40`, real `process_graphics` |
| `0x004455DF` (`+0x1F`) | original E8 `REL32` | `0x00412730`, compatible genuine `Graphics::get_device()` getter |
| `0x00445601` (`+0x41`) | original PE HIGHLOW | `0x005C4D40`, second real Graphics access |
| `0x00445606` (`+0x46`) | original E8 `REL32` | `0x00412730`, second native device getter |

The real D3D9 device's two `call [ebp-...]` virtual calls do **not** have
statically relocated E8 targets. The 17B `0x00412730` physical function
has previously identified compatible folded value-getter bodies, so no
additional separate game bytes are claimed for a duplicate code alias.

## Solving the compiler evaluation-order frontier naturally

Original `0x0044560D..0x00445648` loads the native D3D9 virtual
`DrawPrimitiveUP` function-pointer before computing and storing the
stream pointer and doubled primitive count as local argument values. The
CORE/RECON-789 natural source first assigned those two locals, then
invoked the method. Under pinned MSVC this emitted 192B/55 i386 but
**23 genuine nonrelocated byte differences** inside the call setup.

A bounded family of explicitly meaningful C++ argument-materialization
hypotheses was compiled under the original pinned compiler. The original
codegen follows the natural expression:

```cpp
std::uint32_t primitive_count;
void* stream;
draw_device->DrawPrimitiveUP(
    D3DPT_TRIANGLELIST,
    (primitive_count = queued_count * 2),
    (stream = current_stream),
    sizeof(SpriteTexturedVertex));
```

The maintained file uses actual native field accesses for `queued_count`
and `current_stream`, not invented memory. Both named temporaries hold the
real arguments to a real SDK call and are not inert/compiler-only reads.
MSVC x86 evaluates the function pointer first, then the two relevant
argument expressions and spills them in exactly the original order.
The result is the **entire original 192B /55 x86, zero nonrelocated
byte differences**, no hand-assembled code, no NOPs, no artificial branch,
no function-prefix comparison, no target/COFF edits. Unlike the prior
historical candidate, this one has the full original virtual-call
register and stack operand values.

The three previously exact 92B Graphics `Fog`/`Z-write` cache transitions
all still invoke this same full game method at its original physical head
`0x004455C0`, and the already exact Player draw orchestration also uses
it. Together with the separate original **5,993B /1,501-instruction**
Animation draw Boss, these establish the custom game batching semantics
and original owner. The Boss parent itself remains **SOURCE-ABSENT
and NONEXACT**; this accepted child does not establish that large
function's byte identity or game playability.

## Scoped strict replay and accounting

Pinned MSVC 19.44.35211 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` compiles one new canonical translation unit
`src/AnimationDrawFlush.cpp` to
`build/core790-canonical/AnimationDrawFlush.obj`, with a strict compiler
receipt and one new unit `animation_draw_queue_flush_192`. Independent
readback of the original locked PE confirms all four physical call/data
fields and entire x86 function; then the canonical comparator verifies:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawFlush.cpp
    scripts/repo-python scripts/verify-animation-draw-boss-native.py

**Strict complete unit: 192/192 bytes exact, 55/55 instruction heads,
4/4 original relocations.** No existing canonical source/header,
profile, old object or protected receipt changed; actual affected replay
scope is **one new source/object/whole unit, zero old units**. An
all-repository cold replay was neither necessary nor performed. The
previous nonexact private probes remain preserved in `.analysis/core786-*`
through `core790-*`, not copied into the accepted source or repository.

At this accepted checkpoint, total original game authored strict exact
coverage grows **576 →577 complete distinct physical functions** and
**188,433 →188,625 original disjoint code bytes**. Source-present
mappings stay **1,222** (already authored but NONEXACT in CORE/RECON-789),
canonical units **1,223 →1,224**, distinct canonical object/receipt
providers **251 →252**. Neither the original 5,993B Animation draw Boss
nor the separate 12,140B Bullet command, 41,967B Enemy ECL and 39,470B
Animation VM are now whole exact.
