# CORE/RECON-785 — three complete original Graphics render-state cache methods (276B) from the 5,993B draw Boss

> **Subsequent CORE/RECON-790:** original `0x004455C0` flush callee is now separate whole-native strict exact **192/192B**, not the earlier NONEXACT source described below. [Exact source and original PE proof](ANIMATION_DRAW_QUEUE_FLUSH_192_STRICT_EXACT_RECONSTRUCTION.md). Other date-specific totals remain historical.

> **Subsequent CORE/RECON-789:** The separate 192B `AnimationPoolOwner::flush_draws` callee now has complete maintained typed game semantics and original-PE relocation proof but remains **NONEXACT** (192B/55 x86 yet 23 nonrelocation byte differences). See [the source frontier](ANIMATION_DRAW_QUEUE_FLUSH_192_NATIVE_SOURCE_FRONTIER.md). Earlier exact 92B Graphics method proofs remain valid.

The selected, immutable original Japanese TH20 v1.00a Steamless PE is fixed
by SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint closes **three separate complete original game-authored
92-byte/30-x86 Graphics render-state transitions, totaling 276 disjoint
original .text bytes**. Each is a genuine caller target of the independently
audited original 5,993-byte `AnimationPoolOwner::draw(Animation*)` Boss.
The main parent **remains source-absent and NONEXACT**, even though its own
123-call census and its 49+31 original HIGHLOW switch tables are now known.

## Original game behavior and physical call evidence

| Original physical head | Complete native body | Original Graphics field and D3D9 transition | Original 5,993B Boss call occurrences |
| --- | --- | --- | ---: |
| `0x004DDAC0` | **92B /30 x86**, return included | If `Graphics+0xDB8` is not 1, flush pending Animation draws, publish `render_value=1`, call `IDirect3DDevice9::SetRenderState(D3DRS_FOGENABLE,1)` | **2** |
| `0x004DDA60` | **92B /30 x86**, return included | If `Graphics+0xDB8` is not 0, flush pending Animation draws, publish `render_value=0`, call `SetRenderState(D3DRS_FOGENABLE,0)` | **2** |
| `0x004DDF80` | **92B /30 x86**, return included | If `Graphics+0xDBC` is not 0, flush pending Animation draws, publish `field_dbc=0`, call `SetRenderState(D3DRS_ZWRITEENABLE,0)` | **1** |

`Graphics` is the existing original game-owner class defined by its prior
native object construction and authentic x86 layout. These source methods
use its real `graphics_api::Device` D3D9 interface, not a simulated vtable
or a fake device. The original object reads `Graphics+0x08` for the native
D3D9 device and dispatches its virtual `SetRenderState` through true
vtable offset **`+0xE4`**. The render-state numeric constants are the genuine
SDK `D3DRS_FOGENABLE=0x1C` and `D3DRS_ZWRITEENABLE=0x0E`, not speculative
codes inferred from high-level decompilation. The guarded caches are
`Graphics::render_value` at `+0xDB8` and `Graphics::field_dbc` at `+0xDBC`.
Both offsets have native MSVC x86 compile-time assertions.

Each original full function has exactly **two** ordinary source relocation
fields, independently verified from unmodified original PE:

- At function **`+0x17`**, a real original PE
  `IMAGE_REL_BASED_HIGHLOW` location points to the genuine global
  `current_animation_pool` at **`0x005C0028`**.
- At function **`+0x1C`**, the immediate displacement of the true original
  `E8` at `+0x1B` resolves to **`0x004455C0`**, the separately original
  Animation draw-queue flush method. Source calls
  `current_animation_pool->flush_draws()` before updating the cached device
  state. There is no claim that this separate 192B callee is now exact.

The additional indirect D3D9 vtable call is not an E8 COFF relocation and
must not be claimed as a static direct call to a particular address.
Both direct original fields, all other x86 bytes, the real return and the
entire 92B method boundaries are verified without truncation.

## Recover the original compiler control flow, not an arbitrary instruction patch

A first normal C++20 implementation used a guarded early return with a
fallthrough `return 0;`. Pinned MSVC emitted **90B /29 x86** for each
method, missing a genuine original short two-byte `jmp` near its end.
A bounded set of **12 ordinary equivalent source-level return forms** was
compiled in isolation under the authentic pinned compiler profile. Writing
the intended cache fast-path as an explicit `if (...) { ... } else {
return 0; }` keeps the original compiler's short explicit return-join
branch. It produces the **entire original 92B /30-instruction sequence with
zero nonrelocated byte differences** in all three methods, no artificial
NOP/assembler/volatile, no shortened compare range and no semantic changes.
The rejected probes remain private under `.analysis/core784-*` and
`build/core784-probe/`; they are not accepted source.

Maintained typed C++ lives in one new `src/GraphicsDrawRenderStates.cpp`,
including all three full natural source bodies. Pinned MSVC
19.44.35211 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
creates one new `build/core785-canonical/GraphicsDrawRenderStates.obj` and
strict receipt. Its three new units (`graphics_draw_fog_enable_92`,
`graphics_draw_fog_disable_92`, `graphics_draw_depth_write_disable_92`)
pass **3/3 complete native code and all actual relocation identities**:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/GraphicsDrawRenderStates.cpp
    scripts/repo-python scripts/verify-animation-draw-boss-native.py

The independently immutable original-PE verifier reads all three 92B
originals and checks exactly 30 instruction heads, real PE HIGHLOW global,
actual E8 site/target, original Graphics field write, real indirect D3D9
vtable slot and numerical render-state argument. It also still checks the
**entire** 5,993B draw parent: 123 direct E8, 49+31 original PE jump
entries, 32 original in-body HIGHLOW and its real 3B post-body alignment.
No Ghidra guessed function name or source relocation field is an oracle
for independently deriving original reference destinations.

**Affected existing canonical providers/strict units: zero.** This batch
adds only one new source/object/receipt with three new 92B exact functions.
No previously accepted shared `Graphics.hpp`/`GraphicsApi.hpp` or other
canonical input was edited. A full or unfiltered cold replay was not run.

Game-authored strict original whole-function coverage advances
**573 →576** and nonoverlapping native .text bytes **188,157 →188,433**;
source-present methods **1,218 →1,221**, strict canonical units
**1,220 →1,223**, distinct object/receipt providers **250 →251**.
The separate 5,993B draw Boss, 12,140B Bullet command processor, 41,967B
Enemy ECL dispatcher, 39,470B Animation VM, 3,111B Player main and
273B Bullet single-group draw remain **NONEXACT**. Original graphics
state helper exactness is not whole-program linkage or gameplay playability.
