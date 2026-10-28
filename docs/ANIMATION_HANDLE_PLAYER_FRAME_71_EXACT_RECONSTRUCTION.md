# CORE/EXACT-439 — whole original 45B AnimationHandle validity and 26B position forwarding

The immutable comparison original is Japanese TH20 v1.00a Steamless,
whole executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Two distinct complete original game-owned `AnimationHandle` members
are now **strictly original-byte exact** in the existing canonical
`src/AnimationHandle.cpp` provider:

| Native member | Original entry | Complete strict bytes | Original i386 instruction heads | Original E8 / HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `AnimationHandle::is_valid()` | `0x0047A340` | **45/45** | **15** | **1 / 0** |
| `AnimationHandle::set_position_forward(const Vector3&)` | `0x004645E0` | **26/26** | **12** | **1 / 0** |

The two disjoint original PE functions total **71 unique
game-authored native bytes**. Their complete original native
SHA-256 digests are
`f70a65fe03b7ad94ee0225ff6025135444c675031761c4d1840d388c094a7e04`
and
`2325af27c27373c3b3b6fed3d0e3c67095e8b6c3201cfc0f2f5da2cd2a7f32cc`.

## Actual game object behavior and full x86/COFF references

The original 45B validity member takes a real four-byte
`AnimationHandle` receiver in ECX, calls its genuine native
`resolve()` at `0x0044CED0`, and returns whether the resolved
`Animation*` is nonnull. Importantly `resolve()` can clear
a stale handle; this member does not simply test the four-byte
integer value. Natural C++ `return resolve() != nullptr;`
generates the whole original code. A tested ternary with an
extra bool local instead produced a 45B function whose
nonrelocated bytes **did not** match, and was rejected.

The original 26B position-forwarding member receives the live
`Vector3&` on stack, forwards it through the actual
`AnimationHandle::set_position` at `0x004502C0`
using the proper `__thiscall` receiver, and returns with the
original `ret 4`. It is a physically separate native wrapper
from that callee and is not double-credited.

The entire immutable original functions were decoded from the
PE before canonical admission: **15 + 12 instructions**,
one direct original E8 displacement each and **no** PE
`.reloc` HIGHLOW fields. Independently native-recovered fields:

| Source original field | Type | Independently original target | Earlier full exact callee |
| --- | --- | --- | --- |
| `0x0047A340 +0x0D` | E8/REL32 | `0x0044CED0` | `bullet_collision_handle_resolve` (51B) |
| `0x004645E0 +0x0F` | E8/REL32 | `0x004502C0` | `animation_handle_set_position` (35B) |

Both original PE field locations/types and independently observed
physical targets agree with the actual MSVC COFF symbol and
zero addend. Each original entire body is strict exact,
**45/45 + 26/26**, without padding, assembly, manual machine
bytes, shorter prefixes or a guessed target.
Full immutable native proof:
`.analysis/core439-animation-handle-original-pe-proof.json`.

Both original physical methods are called by the separately
still-nonexact **3,111B / 783-instruction Player main-frame**
at `0x004F9C30`: validity is checked twice, and position
forwarding once. That parent has **67 native direct E8 calls**
and **37 original PE HIGHLOW** fields. At CORE/EXACT-436
time 59/67 call sites had exact original callee bodies;
these two whole methods close another three sites, giving
**62/67**, with five still unclosed. This does not
prove or credit any native bytes of the 3,111B parent.

## Genuine AnimationHandle.hpp include-graph validation: 473/473

Only the preexisting four-byte `AnimationHandle` type's
two member declarations in `src/AnimationHandle.hpp`
and their natural C++ definitions in
`src/AnimationHandle.cpp` were added. Its original
native storage layout, existing method signatures,
locked MSVC profile, and original canonical owner
`build/core163-canonical/AnimationHandle.obj`
were not changed.

**Before editing the shared header**, prior real compiler
receipts were independently enumerated. The complete
`AnimationHandle.hpp` include closure contains exactly
**106 existing source providers / 471 earlier strict
native units**. Both new methods join the already
existing single AnimationHandle source/object; thus the
entire actual changed-header affected set is
**473/473 strict native units across 106 freshly cold-built
source objects**. No unfiltered whole-repository
cold replay was run. It was replayed in **22 serial,
low-priority batches**, scoped solely to the actual
receipt-proven providers, with per-batch strict counts

`67+42+26+6+13+6+16+7+10+36+16+24+19+26+38+36+20+8+14+21+18+4 = 473`.

The complete source closure and actual results are in
`.analysis/core438-animation-handle-preedit-closure.json`,
`.analysis/core439-animation-handle-replay-groups.json` and
`.analysis/core439-animation-handle-replay-batch0.log`
through `batch21.log`.

The existing entire **2,018B Bullet collision**,
**1,846B Bullet physics**, **1,081B Player option-frame**,
and associated original gameplay/Animation/Enemy/Effect
functions remained fully strict exact under that closure.

The shared header caused some MSVC compiler-private `$SG`
symbol IDs to renumber in diagnostic-heavy owners, including
Item, Player, Sound, RenderMesh, Dialogue and other existing
exact methods. **Only private symbol spellings** were updated
after checking their **same independently original PE string
target**, relocation offset/type and complete nonrelocation
bytes. The source-specific replays then passed with the
unchanged strict oracle. Individual prior/new IDs,
original PE destination and byte-field offsets are recorded
in `.analysis/core439-reconciled-private-symbols.json`;
these changes do **not** relax acceptance or generate additional
native exact credit.

The two 71B methods are independent whole original game-owned
bodies, not proof of linked whole-game runtime equivalence.
