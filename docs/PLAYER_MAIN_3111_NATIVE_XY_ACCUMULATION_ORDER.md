# CORE/RECON-699 — original 3,111B Player main-frame motion accumulation order

**Whole original `Player::update_main_frame` at 0x004F9C30 is still NONEXACT**. The immutable Japanese TH20 v1.00a Steamless original has **3,111 bytes /783 x86 instructions**, target SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`. The maintained complete game owner is `src/PlayerMainFrame.cpp`. This correction is measured across that entire large parent and receives zero game-authored exact byte credit until the entire original method matches.

## Original source-order evidence from actual native machine code

The previous maintained C++ incorrectly computed the signed fixed-point portions of both real Player residual vector components into two separately named `stored_x` and `stored_y` locals, and only then combined them with `dx` and `dy`. This is not the dataflow observed in the original physical PE.

The original complete Player method at offsets:

- **+0x849..+0x863:** loads real `Player+0x20F0` *X* float into `xmm0`, multiplies the original file-backed `native_128` float, executes `cvttss2si edx,xmm0`, then **adds `[ebp-0xC]` and immediately stores the resulting `dx`**.
- **+0x866..+0x880:** only **after the X write** does it load `Player+0x20F4` *Y* float, multiply by the same independent 128.0f global reference, convert into `ecx`, **add `[ebp-0x10]` and immediately store `dy`**.
- **+0x883..+0x8B1:** only after *both original 32-bit motion accumulators are updated* does the method independently convert updated `dx` and `dy` back to floats, multiply each by the genuine `Player+0x20EC` movement scale, convert to signed 32-bit, and overwrite its original signed X/Y accumulator slot.

The repaired natural C++ follows this real original ordering: update `dx` with the X residual; then update `dy` with the Y residual; then separately multiply each updated integer by the movement scale. Both additions explicitly use unsigned 32-bit intermediate arithmetic before reinterpreting the stored signed value, preserving native wraparound rather than creating undefined signed C++ overflow. The field addresses, genuine `native_128` global, two distinct conversion lanes and scale evaluation are unchanged.

## Whole original vs locked compiler C++ diagnostic

| Full parent evidence | Previous source | New maintained source | Actual original |
| --- | ---: | ---: | ---: |
| Complete method body bytes | 3,093 | **3,077** | 3,111 |
| Whole method instruction count | 779 | **777** | 783 |
| Original mnemonic heads aligned in order | 764/783 | **766/783** | 783/783 |
| Identical operand displays among aligned heads (diagnostic) | 265 | **301** | — |
| Native original E8 / current COFF REL32 counts | 67 | **67** | 67 |
| Native PE HIGHLOW / current COFF DIR32 counts | 37 | **37** | 37 |
| Original ordinal physical call *role* identities | 67/67 | **67/67** | 67 |
| Complete original parent strict exact | NO | **NO** | original |

The 32-bit accumulator source evaluation now reproduces the original **float X → integer addition → store X → float Y → integer addition → store Y** machine-code kind order without two extraneous stored residual locals. The remaining original register choices, expression-grouping operations, four animation-script index arithmetic forms, final option iterator lifetimes and physical relocation sites still differ. Matching an instruction subset or total reference count is not native exactness. Importantly the called 555B `Player::apply_move_delta` remains an independent **NONEXACT** original child despite the original call role identity being verified.

## Bounded reproducible native evidence

- `.analysis/core698-player-motion-accumulator-order-probes.py/json`: ten actual whole C++ method builds, comparing both wrapping operand orders, staged temporaries, inline accumulator conversion and rejected interleaved X-scale-before-Y cases. All 67 E8/37 DIR32 counts persisted.
- `build/core699-probes/PlayerMainFrame.obj` and real locked MSVC x86 source/headers receipt: `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc`.
- `.analysis/core699-player-main-motion-order-whole-proof.json`: independently disassembled full immutable original and new maintained C++, original X/Y live-field order assertions and full instruction/mnemonic score.
- `.analysis/core699-player-main-67-callee-whole-proof.py/json`: rechecked **all 67** immutable original E8 physical callee roles against the actual new C++ COFF. Sixty already independently anchored, six original folded-compatible source identities (fully byte-attested, no double credit), one remaining distinct nonexact 555B child.

**Affected canonical replay scope: zero old native units.** Only noncanonical `src/PlayerMainFrame.cpp` changed; no public header, existing strict source/object, native match manifest, accepted unit or original PE was changed. Recompiled the entire affected original Player parent and checked its real 67 callee roles, **not** a full cold replay. Accepted authored coverage stays **504 whole original functions /179,611 nonoverlapping exact game bytes**. The 73B Animation factory and 3,735B Bullet emitter remain separately whole-native exact.
