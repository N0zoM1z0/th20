# CORE/EXACT-227 — complete native 320-byte Bullet spatial cancellation boss

Immutable native input: Japanese TH20 v1.00a Steamless PE,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The exact original `0x0047D100..0x0047D23F` comprises **320 bytes,
95 native x86 instructions** and **14 original relocations** (interval
SHA-256 `84591a35d82201b5dcd270de506721a33e9bf573a5c7af28c2591a9329f6507c`).
The real original Player caller `0x004F7430` and the independently recovered
full BulletController and Bullet layouts confirm that this is a game-owned
spatial cancellation operation, not a compiler/library template.
Its original C++ spelling remains inferred.

The maintained entire natural `BulletController::cancel_near(const Vector3&,
float,int)` is in `src/BulletSpatialCancellation.cpp`. It iterates the
**real** BulletController active intrusive list at +`0x286D64`, using the
native `IntrusiveIterator<Bullet>` constructor, `begin`, `end`, `get`,
`node_value`, `differs`, `advance`, destructor and full exception/security
cookie epilogue. It skips states other than **1 or 2** and tests each
Bullet's actual `position` at +`0x64` against the native geometry predicate
at `0x00485A60`, passing the **actual Bullet `size.x` at +`0x7C` divided by
the original 2.0f constant at `0x0056C8D0` plus the caller radius**.
On a hit it passes the original mode to the **662-byte** native
`Bullet::cancel(int)` at `0x0047C8F0`, increments the Controller's real
`cancel_counter` at +`0x286D88`, and increments a separate local return
count. No pointer-wrapper facade, byte-copying, partial opcode body or
skipped iterator cleanup is used.

## Original ABI and compiler convergence

An initial natural prototype declared the `0x00485A60` distance predicate
as returning `bool`. MSVC then inserted a `movzx` to widen AL; however the
**original native caller directly tests complete EAX**. Using a real
`std::int32_t`-returning external ABI removes that widening. Its original
return type is supported by the whole native call and branch behavior;
Ghidra's independently inferred `bool` return was not taken on trust.
The second mismatch was the compiler's branch order when states 1/2 were
expressed as a positive compound `if`. The natural equivalent
`if (bullet->state != 2 && bullet->state != 1) continue;` precisely matches
native branches and iterator advance. The final complete C++20 code compiles
to the **entire original 320 bytes** with **264/264 matching non-relocation
bytes** and all **14** original relocation offsets/types/destinations
strictly replayed, including native SEH handler `0x0056863D`, cookie,
full typed iterator protocol, original 2.0f float object, original real
geometry callee `0x00485A60`, native Bullet individual cancel callee
`0x0047C8F0` and security check.

The locked MSVC 19.44 x86 profile was `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` (C++20). Complete unit replay returned
**320/320 bytes exact** in `build/core227-canonical/BulletSpatialCancellation.obj`.
The shared `src/Bullet.hpp` adds only the real member declaration; the
compiler-receipt-derived affected closure has **thirteen** source objects,
**49 old accepted units and this new unit**. All **50/50 complete strict
functions across thirteen freshly built objects** passed, including the
entire 832B Bullet boundary boss, 242B cancel-all boss, 339B Bullet fire,
81B draw orchestrator, 291B retirement and all four bounce methods.
Compiler-private Bullet constructor `$SG79856` shifted to `$SG79860` and
four Dialogue literals `$SG117792..117795` shifted to
`$SG117796..117799`; original data relocation targets and bytes were
unchanged. No unfiltered whole-repository cold replay was used.

Focused proof logs: `.analysis/core227-bullet-spatial-cancel-native-replay.log`
and `.analysis/core227-bullet-full-include-closure-replay.log`; independent
native full-interval audit at `.analysis/core227-native-0047d100.asm`.

The original **122-byte** geometry predicate `0x00485A60` and **662-byte**
individual Bullet cancel `0x0047C8F0` are still independent **nonexact**
source/COFF frontiers, as are the **3,735-byte** Bullet single-shot emitter
and **41,967-byte** Enemy opcode root. Their correct call ABI does not grant
byte-credit for the entire callee, nor does this prove a complete runnable
link or original Renderer startup.

## CORE/EXACT-228 follow-on — called distance routine now exact

The original **122B** `bullet_distance_within` at `0x00485A60` has now
been independently reconstructed as a separate complete native exact unit,
including its **full-EAX integer return** and five original relocations.
`src/BulletSpatialCancellation.cpp` now includes the maintained typed
`BulletDistance.hpp` instead of a private forward declaration. The original
complete **320/320B** caller still matches in a fresh affected-only replay
with the new 122B callee, **2/2 strict units, two cold objects**.
The earlier nonexact distance-callee status in the historical checkpoint
above is superseded by this verified admission, not by conjecture. See
[exact Bullet distance](BULLET_DISTANCE_EXACT_RECONSTRUCTION.md).
