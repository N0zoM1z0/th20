# CORE/EXACT-231 — complete 388-byte Bullet std::function-filtered cancel boss

Immutable original: Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The whole native `0x0047D240..0x0047D3C3` function is **388 bytes**
(**116 native x86 instructions**, interval SHA-256
`b7df85761f117b261143370ecb99e2dcc11edf6533e7bdf0bb6c5c4297513dec`).
The complete real typed original operation now lives as one natural C++20
`BulletController::cancel_near_if(const Vector3&, float,
std::function<std::int32_t(const Vector3&)>)` in
`src/BulletFilteredCancellation.cpp`. The inferred original C++ name is
not claimed as recovered; source behavior, ABI, whole code and independently
anchored original target relocations are checked against the immutable PE.

## The actual 40-byte callback-owner ABI, not a raw function pointer

Original native callee `0x00449630` is the MSVC `std::_Func_class` call
wrapper: it tests that the callable holds a nonempty target, dispatches
through the stored virtual implementation and returns a **full EAX integer**
result. The whole caller's original signature cleans **48 bytes** via
`ret 0x30`: 4-byte position reference, 4-byte radius, and **40-byte**
by-value `std::function<std::int32_t(const Vector3&)>` argument.
It destroys the actual standard-library function owner through native
`0x00414400` even on the ordinary exit, with original SEH state tracking.
This independently establishes value ownership and callback lifetime.
The actual original native callers at `0x00535D00`, `0x00535E20`,
`0x00536280`, `0x005371A0`, `0x005372C0`, and `0x00537730` attest this
method is game-owned, not a compiler-generated STL function.

The function iterates the real `BulletController::active` intrusive list
using exact `active_list()` at Controller +`0x286D64` and the original
iterator construction/advance/end/deref/destruction. It skips Bullet
states other than **1 or 2** and skips any Bullet whose +`0x18` field is
nonzero. Both the original native **122-byte exact** squared XY radial
distance predicate `bullet_distance_within(position,center,size.x/2+radius)`
at `0x00485A60` **and** the true incoming `std::function` callback are
short-circuit tested. Only when both are true does the caller clear the
actual Bullet flags bits 11..12, invoke genuine `Bullet::cancel(0)` at
`0x0047C8F0`, increment real Controller `cancel_counter` at +`0x286D88`
and increment its separately returned count.

The first natural `continue` after each predicate compiled to **398B**,
whereas the original has a common branch to the next iterator advancement.
A single natural short-circuit `if (distance && predicate)` compiled to
the original **388B**, matching **320/320 non-relocation bytes** and all
**17 independently identified original relocation offsets/types/targets**,
including two original frame/EH anchors, actual `std::_Func_class::operator()`
at `0x00449630`, `std::function` destructor `0x00414400`, real Bullet cancel
`0x0047C8F0`, iterator lifetime and original security check. No copied
machine instructions, arbitrary padding, compiler-only dummy locals, or
partial-function credit was introduced. Exact native SHA-256 and
Ghidra/Capstone evidence come from the locked original PE, not from
solving target values in the comparison manifest.

## Strict affected-only regression scope

Including authentic `<functional>` and the original typed member declaration
in shared `src/Bullet.hpp` affects **14 existing exact cold source objects,
51 previously exact functions**. All 51 were freshly compiled with locked
MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
and strictly replayed; **all remained exact**. The compiler's private
BulletController diagnostic `$SG79893` became `$SG85490`, and four Dialogue
literals `$SG117829..117832` became `$SG117835..117838` because of the
expanded standard-library include. Only those private COFF symbol names in
the manifest changed: actual native relocation types/offsets/data target
addresses and compared bytes remained unchanged. This checkpoint totals
**52/52 strict native units across 15 freshly compiled objects** (51 old +
new 388B). No unfiltered whole-graph cold replay or comparator relaxation.

Focused logs: `.analysis/core231-filtered-cancel-native-replay.log` and
`.analysis/core231-bullet-full-include-closure-replay.log`; rejected and
accepted full-function private prototypes remain in `.analysis/core231-*.cpp`.

The original **662-byte** `Bullet::cancel` body at `0x0047C8F0` remains
source/COFF nonexact despite now having another exact whole-function caller.
The 3,735-byte Bullet emitter `0x004818E0`, original 41,967-byte Enemy ECL
root `0x0048C010`, actual `std::function` producer lambdas and full-game
link/runtime proof are not claimed by this checkpoint.
