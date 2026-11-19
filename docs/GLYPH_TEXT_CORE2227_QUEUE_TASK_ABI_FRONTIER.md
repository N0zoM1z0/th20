**2026-11-19 CURRENT ADOPTED UPDATE:** The real `NativeGlyphRenderJob`
now remains visibly owned by a named rvalue reference that is actually moved
into the queued `std::function`. This captures the genuine pointer/lifetime
boundary without adding any extra call or unused local. The complete pinned
C++ function now occupies **2,308B/468 code instructions** (original
**2,316B contribution/470 code instructions+NOP**), and its authentic
`0x310` stack frame matches the original where the prior source used `0x30c`.
The native E8 role sequence is still **25/25**, with **17/25 exact sites**;
the sum of absolute E8 site deviations falls from **148 to 52**. All
**43/43 body data target roles** and **41/43 physical data sites** remain;
full-body ordinary-byte agreement improves from 1,626/1,936 to
**1,629/1,948**. All original 22 switch-case pointers and 17 alias groups
remain generated, and previously strict 132B/23B task children pass the
**2/2 source-scoped cold replay**. The parent is still **NONEXACT** and has
no new game byte credit. See
[`GLYPH_TEXT_CORE2227_RVALUE_QUEUE_LIFETIME_FRONTIER.md`](GLYPH_TEXT_CORE2227_RVALUE_QUEUE_LIFETIME_FRONTIER.md)
for the complete source/PE comparison and original queue ABI.

**CURRENT ADOPTED SOURCE UPDATE (2026-11-19).** The true completion
word at native stack `+0x2C` is declared `std::uint8_t*`, consistent with
the independently exact 360B upload, and forwarded by reference without
an integer/pointer alias. The maintained source uses a genuine
`std::addressof(canvas)` identity call (its folded native 8B code matches
**8/8**) and a named brace-constructed `NativeGlyphRenderJob` whose
destruction occurs after queue submission, in the actual original order.
The pixel-rectangle y-offset is incremented by six rather than assigned,
as in original `+0x797`. The caller `AsciiTextSubmit294.cpp` forwards its
original 32-bit input word as a pointer without modifying the native i386
stack ABI. Its natural 292B/104-i386 body remains NONEXACT by only the two
original NOPs.

The current whole MSVC x86 COFF contribution is **2,308B**: **2,220B
code /468 i386 instructions** and 22 generated switch pointers. The
original complete physical contribution is 2,316B (2,227B code, one
original NOP and 22 pointers). The first **17/25** original E8 positions
align, including the true `+0x7BC` reference helper and `+0x7E7` glyph
job constructor. **41/43** body data relocation positions align and
**1,629/1,948** comparable ordinary bytes match. All 25 original E8
callee roles and all 43 original body data destinations remain correct
and ordered; all 17 switch alias groups are retained. This improves
queue-construction and cleanup convergence without claiming parent
exactness. The `std::function` constructor and queue/cleanup sequence
remain the next native codegen frontier; candidate constructor is at
`+0x809` versus original `+0x80F`, a six-byte displacement after the
first 17 E8 positions have aligned.

The independent `scripts/verify-glyph-text-core2227-native.py` checks
the complete 2,308B contribution, all 25 call roles, all 43 data roles,
all 22 switch pointers, and the explicit 17 native alias groups. A
scoped one-object rebuild of only `src/GlyphTextCore2227.cpp` strictly
replayed **2/2** existing 132B/23B job units. The parent remains
SOURCE-PRESENT, NONEXACT, with zero parent-byte credit. No synthetic
call, unused local, false data, manual NOP, ASM or padding is used.

# Glyph Text 2,227B Boss: queue-task ownership and compiler-return frontier

The locked Japanese TH20 Steamless v1.00a executable (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains the full text rasterizer at `0x00415830`: **2,227B /470 i386 code**,
one original NOP, and 22 real font-switch pointers. The maintained
[`GlyphTextCore2227.cpp`](../src/GlyphTextCore2227.cpp) is SOURCE-PRESENT
**NONEXACT**. The earlier native-sized **2,316B whole contribution** was a prior frontier
with 15/25 physical E8 sites and 1,566/1,956 ordinary positional bytes; it is
superseded by the current 2,308B/17-site source frontier above. The established
[font dispatch](GLYPH_TEXT_CORE2227_SWITCH22_NATIVE_CONVERGENCE.md)
and [GDI color/offset semantics](GLYPH_TEXT_CORE2227_COLOR_AND_CANVAS_ABI_FRONTIER.md)
are not changed by the experiments below.

## Original task-construction protocol at +0x7BC..+0x842

The original's four consecutive calls are distinct and independently
identified from their physical E8 operands:

| Original E8 | Original destination | Native role |
| --- | --- | --- |
| `+0x7BC` | `0x0040B280` | 8B folded address/reference identity helper; actual `&canvas` local supplied |
| `+0x7E7` | `0x00413EC0` | Existing whole-exact 132B `NativeGlyphRenderJob` capture constructor |
| `+0x80F` | `0x00412F20` | 102B `std::function<void()>` producer for the captured task |
| `+0x824` | `0x004162F0` | Existing whole-exact 56B borrowed queue submission |

The original helper at `0x0040B280` is a complete eight-byte
`push ebp; mov ebp,esp; mov eax,[ebp+8]; pop ebp; ret` function. It is
folded among many library templates; **its exact C++ spelling is not
proven** by Ghidra's provisional symbol names. In this caller, source
code pushes the **address** of the local canvas pointer, receives that
address in `EAX`, then dereferences it immediately before passing the
canvas as a value to the 132B job constructor.

The native 132B constructor returns its object address in `EAX`; the
caller saves and copies that address in two real local words, sets EH
state 3, and forwards the address to the subsequent `std::function`
constructor. EH state then advances to 4 for the constructed
`std::function`; the original queue call borrows the lvalue. The source
must retain both destructors in native order: `std::function` at
`+0x833`, then glyph job at `+0x842`. A single-expression temporary that
is destroyed earlier does not preserve this lifetime contract.

The original job inputs also pass the `+0x2C` completion-byte pointer
word **by reference to the existing input slot**, not via a newly
allocated pointer local. Its pixel rectangle's initially zero
`field_b` is *incremented* by six if the extra-padding condition is
true (`mov/add/store`), rather than being assigned a literal six.
These are genuine source/ABI leads, but a natural, whole-native source
that preserves all lifetimes has not yet been established.

## Actual pinned-MSVC whole-body experiments

The current native-sized source was retained because proposed changes
trade site convergence for new whole-body differences. All candidates
were compiled as complete translation units using the locked MSVC
19.44 i386 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
profile; none were compared using truncated target-sized prefixes.

| Private source variation | Full COFF | Physical E8 sites aligned | Why not adopted |
| --- | ---: | ---: | --- |
| Maintained source | **2,316B** | **15/25** | Best validated natural whole contribution; still NONEXACT |
| Remove unused `glyph_mode`, use `field_b += 6`, borrow original `mode` slot, use `std::addressof(canvas)` and 64-bit representation return | 2,296B | 16/25 | Shorter code; reference/return source ownership unresolved |
| Same, named glyph task with brace construction | 2,296B | 17/25 | Still 20B shorter; `std::function` local lifetime differs in register/stack handling |
| Same, single-expression temporary task | 2,312B | 17/25 | Temporary lifetime does not match original two-object EH/destruction order |
| Same named task with two pointer/reference forwarding aliases | 2,320B | 17/25 | 4B longer and redundant aliases have no established source ownership |

These trials preserve the 22 genuine generated font pointers and 17
original table alias groups, but none is whole native exact. Replacing
EDX:EAX assembly of the native `SIZE` result with a C++20 `std::bit_cast`
adds another compiler helper; direct representation access removes the
non-native `__allshl` call but changes length and requires an ABI/aliasing
justification. `std::move(canvas)` by value alone is lowered to the
existing code and does not recover the original eight-byte helper.
The temporary probes, score script and whole COFF objects are retained
in ignored `.analysis/gptweb20-glyphtext-{task,addressof,task-lifetime,jobinit,jobpointer}/`
and `build/gptweb20-glyphtext-*` folders.

Next work should first reconcile the genuine input-slot/reference and
task-constructor-return lifetimes, then inspect the actual producer
symbol and cleanup order. Keep the independently exact 132B constructor,
23B destructor and 56B queue bridge unchanged, and run only the two
exact units owned by `src/GlyphTextCore2227.cpp` when its source changes.
No native source, canonical unit or tracking entry was changed by this
research note; its replay scope is zero.
