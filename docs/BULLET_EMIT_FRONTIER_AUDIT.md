# CORE/REVIEW-212 — Bullet single-shot boss dependencies and a corrected list operation

This audit was made directly against the original locked Japanese TH20 v1.00a
Steamless PE, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
not by assuming earlier reconstruction naming was right. Source probes were
compiled with the locked MSVC x86 toolchain; native function boundaries and
call sites were cross-checked with original disassembly and Ghidra.

## Original `BulletController::emit` boss at `0x004818E0`

The original complete **3,735-byte** function contains **935 x86 instructions**,
**60 direct calls** to 43 distinct targets and the primary switch over the
native shared shot command mode, including the two indirect branch sites.
It calls the genuine Animation file setup method `0x004383A0` at
`0x004822C5`, obtains/recycles an Animation through manager call
`0x0044C9B0` at `0x00482241`, and uses the true list operation
`0x0044A6B0` at `0x00481975`. This whole original root is still
**source/COFF nonexact**; the audited individual calls are not standalone
opcode functions or partial exact credit.

## Corrected `0x0044A6B0` list semantics (66 complete bytes)

The native function's first call `0x00411EE0` receives `this` as its receiver
and inserts the new link after the **head sentinel**; the second call
`0x00412DC0` sets the link's actual list owner. At +0x28..+0x3C, original
instructions compare `tail` at +0x14 to `this`, and write `tail=link`
**only on the empty-list path**. The algorithm is `IntrusiveList::prepend`,
not `append` (which inserts at the previous tail and updates it every time).
The existing generic natural source in `src/IntrusiveLink.hpp` does describe
`prepend` correctly. Explicit locked-compiler instantiation for `Bullet`
produces an entire 66-byte body with both independently anchored relocations,
but retains **five non-relocation byte differences**: 53/58 comparable
bytes match, in the final comparison's register/operand placement. Therefore
this callee itself remains nonexact and is not entered as a strict unit.

The previously admitted `Bullet::deactivate` at `0x0047DA40` wrongly
used `.append(&link)` while assigning the relocation field to `0x0044A6B0`.
It is now correctly `.prepend(&link)`, retaining the same verified destination.
The full **291/291-byte** original strict replay (including all thirteen
relocations) remains successful, with the two 54B/19B source siblings **3/3**.
Only the affected `src/BulletLifecycle.cpp` object was freshly compiled;
no whole-graph replay, and no new exact-function credit, results from this fix.

## Complete Animation script setup: native `0x004383A0` (338 bytes)

This is distinct from the previously accepted 84B
`AnimationFile::apply_template` at `0x00438B70`. Its native code checks the
real file script table at +0x54 and atomic state at +0x5C before zeroing the
entire 0x5E4 Animation on failure. On success it updates the actual script
index/owner IDs, distinct Animation flag bits, timers, pending callback,
Animation manager initialization and manager live count at +0xB8.

A natural diagnostic C++20 probe using the real 0x70-byte `AnimationFile`
and 0x5E4-byte `Animation`, and an explicitly **temporary unknown manager
prefix** only under `.analysis/`, reaches the **full 338-byte native function length** with
**306/306 non-relocation bytes**. The essential natural spelling is
`static_cast<bool>(stage)`: comparing `stage != 0` directly emits a different
316-byte path. This **is not a strict canonical match**: the real Renderer
owner's complete typed prefix up to +0xB8 and production global publication
remain unresolved, so the private placeholder MUST NOT be imported into
`src/`. No source mapping or exact credit was added for this boss.

## Animation allocation and manager reuse

The distinct complete 298B method `0x0044C9B0` is called by the original
3,735B emitter. It checks the manager's real free-list at +0x6000718,
selects a previously allocated Animation when available, detaches its
0x5E4 link, resets fields and real Animation nodes, or allocates a fresh
Animation through `0x00447800`. This requires the actual huge Renderer
owner, not an artificial one-field facade, before a production match can be
accepted.

The genuine **73-byte** `0x00447800` allocation path invokes native
operator new, then explicitly zeroes the complete 0x5E4 allocation before
calling the original Animation constructor. A current natural
`DiagnosticAllocator::allocate_object<Animation>` template instantiation
emitted **60 bytes**, omitting the pre-constructor clearing; it was
rejected, not passed off as exact or "corrected" with a special artificial
branch. Reconcile original constructor initialization and shared factory
semantics before changing the canonical allocator template.

Private diagnostics: `.analysis/core212-native-004383a0.asm`,
`.analysis/core212-native-0044c9b0.asm`,
`.analysis/core212-variant-atomic-bool.cpp`,
`build/core212-probes/atomic-bool.obj` and its locked compiler receipt,
`.analysis/core212-bullet-list-direction.cpp` and
`build/core212-probes/BulletListDirection.obj`,
`.analysis/core212-animation-allocate-probe.cpp`, and the 291B corrected
scope replay `.analysis/core212-bullet-lifecycle-semantic-correction-replay.log`.
These are exploratory evidence, not native accepted machine code for the
three still-open methods.

## CORE/LIB-254 follow-on: real 44B command-vector STL origins and full switch tables

The original 3,735B shot emitter has two physical jump tables: 13 entries
at `0x00482778` and 11 entries at `0x004827AC`, with original complete
3,840B code-plus-table/compiler contribution. Independent strict builds
also identify its three `0x0047C6C0` command index calls and one
`0x00486600` size call as **standard-library instantiations**, not
additional game-authored helpers. The original exact 33B index and 41B
size bodies are now modeled as real `std::pmr::vector<BulletCommand>`
template instantiations, **2/2 strict exact units in one new object**,
but deliberately excluded from authored exact functions/bytes.
The 3,735B gameplay source is still nonexact. See
[entire emitter table and STL ownership audit](BULLET_EMITTER_VECTOR_STL_ORIGIN_AUDIT.md).

## CORE/AUDIT-292 follow-on — entire 3,735B typed C++20 source now compiles

Later independent analysis confirms two original jump tables at
`0x00482778` (13 native destinations) and `0x004827AC` (11 destinations)
and the **3,832-byte original entire compiler contribution** (3,735B
function code, one NOP, 96B tables, excluding eight separate linker
alignment bytes). Complete C++20 emitter source, not just isolated shot
pattern branches, now compiles under `.analysis/core288-BulletEmitterFull.cpp`
and the native ownership-corrected
`.analysis/core290-BulletEmitterFull-RealMetadataLifetime.cpp`. The
first full build emits 3,629B code/911 instructions and **787/935 native
mnemonic positions aligned**; the corrected real one-time
`shared_ptr::get()` and moved-ownership version emits 3,516B code/890
instructions and also **787/935 aligned**, plus the correct **two
24-entry-total tables** (13+11). Eight more whole-body ownership variants
reach **789/935 aligned**, but all remain **nonexact**. Genuine 63B
original old-MSVC `std::shared_ptr<EtamaArgInf>` move assignment also
remains nonexact using the modern installed STL. No source or exact-byte
credit has been assigned to the 3,735B gameplay root.
See [whole emitter typed source and native switch-table frontier](BULLET_EMITTER_FULL_CXX_FRONTIER.md).
