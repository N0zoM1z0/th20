# CORE/EXACT-229 — complete 401-byte capped Bullet radial cancellation boss

This checkpoint reconstructs the **entire 401-byte original** function
`0x0047CF60..0x0047D0F0` (120 native instructions, original interval
SHA-256 `8326d829980bcad5a3266f49236d86488a52edfaf3cf459edaf8a153fe2bc9eb`)
from the immutable Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The source is maintained as the complete native game-owned method
`BulletController::cancel_near_limited(const Vector3&, float, int, int, uint32_t)`
in `src/BulletLimitedCancellation.cpp`. The original name remains inferred;
the full member ABI, field identities, code and original call boundaries are
independently checked against native instructions, not assumed from notes.

The method traverses the real BulletController +`0x286D64` active list using
its independently exact `active_list()` accessor and real
`IntrusiveIterator<Bullet>` lifetime. It skips Bullet states other than
**1 or 2** and any Bullet whose actual +`0x18` field is nonzero. Eligible
Bullets are filtered by the original **122-byte fully exact**
`bullet_distance_within()` predicate (`0x00485A60`) with live Bullet
position and `size.x / 2.0f + caller_radius`. On a true predicate, the
method assigns the low two caller effect bits to the real Bullet flags' bits
**11..12**, calls original `Bullet::cancel(mode)` at `0x0047C8F0`,
decrements the caller's signed maximum count, increments the Controller's
real `cancel_counter` +`0x286D88`, and increments the returned total. The
limit reaching zero or less exits early through a separate original
iterator destructor, while other cases use the normal iteration destructor.
Both exception/unwind and security-cookie paths are native complete.

## Newly established original flag layout

A first natural implementation used a mask-and-OR expression for the two
cancel effect bits; it produced **406 bytes** rather than the original
401. Combining the two edge branches into a positive guarded block closed
the length to 401 but still differed in register assignments. Independent
original x86 instructions show MSVC's **direct two-bit field assignment**:
its `AND 3`, shift left 11, old word AND `0xFFFFE7FF`, OR and write are
emitted in a specific original register order. Defining the real typed
`BulletFlags::fields.effect_mode` as a **2-bit field after 11 lower bits**
reproduces the entire MSVC instruction and register allocation sequence.
The existing raw `BulletFlags::bits` interface remains available as an
exact same-size union. This is a real game-data layout discovery, not
artificial compiler byte shaping or a manually inserted opcode. The final
natural expression `bullet->flags.fields.effect_mode = effects` matches the
complete source/native instruction ordering.

Locked MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` produces **337/337 native non-relocation bytes** and all **sixteen
independently anchored original relocations**, covering the entire 401B body.
Complete strict canonical replay verifies **401/401 original bytes**,
including original SEH frame/cookie and two destructor branches. Focused
individual log: `.analysis/core229-bullet-capped-native-replay.log`.

Adding the authentic bitfield and the game Controller method declaration to
shared `Bullet.hpp` affects **13 existing source objects/50 exact old units**
(including the already exact 832B Bullet boundary boss, 339B firing boss,
320B radial cancellation and 242B cancel-all). Each was freshly rebuilt and
strict-compared, and all **50/50 prior exact units remain exact**. With the
new function this checkpoint has **51/51 strict units over 14 cold objects**.
The compiler-private BulletController diagnostic string symbol moved from
`$SG79860` to `$SG79893`, and four Dialogue local strings from
`$SG117796..117799` to `$SG117829..117832`; original relocation types,
positions, native data destinations and compared bytes remain unchanged.
Only these private COFF symbols in the manifest were updated; **no**
comparator relaxation or whole-repository cold replay occurred.
Complete affected-only log:
`.analysis/core229-bullet-full-include-closure-replay.log`.

The original **662-byte** `Bullet::cancel` target at `0x0047C8F0` is
still not exact; nor are the genuine 3,735B single-shot Bullet emission
function at `0x004818E0` or 41,967B Enemy opcode root `0x0048C010`.
A full exact 401B caller is not evidence that those downstream complete
functions have been reconstructed or that the game can now link and run.
