# CORE/RECON-904/905 — independent original 113B polygon group constructor and 78B array constructor frontier

> **CORE/RECON-906 correction:** The original 78B three-segment `std::array` constructor is now [whole canonical strict exact](ANIMATION_POLYGON_SEGMENT_ARRAY_78_STRICT_EXACT.md). Its own five following original INT3 bytes are included in 83/83 full contribution comparison. The 113B group ctor and 75B Vector2 array ctor remain NONEXACT. Historical 78B constructor tests below describe the previous checkpoint.

The original 113B/30-i386 group method at `0x0045F340` is invoked by the
now whole-exact [156B C++17 allocation factory](ANIMATION_POLYGON_GROUP_FACTORY_156_NATIVE_EXACT.md).
It is **not yet accepted as a canonical strict unit**. Its source and ABI
were re-examined from the immutable Japanese TH20 1.00a Steamless PE, not
from the previous flat-byte record hypothesis alone.

The original 113B group construction does the following in native order:

1. `AnimationCallback::AnimationCallback(Animation*)` at `0x00446B60`
   (original E8 `+0x0E`), establishing an 8B polymorphic base containing
   vptr plus an actual `Animation*` receiver.
2. Stores the **genuine original derived vtable `0x0056EE50`** via native
   HIGHLOW `+0x18`. Its first three virtual targets are original
   `0x0045F5A0` scalar deleting destructor, already exact
   `0x0045F5E0` update, and already exact `0x0045F9B0` group draw.
3. Constructs three `0x3D4` polygon segments with original 78B helper
   `0x0045F2B0`, native E8 `+0x22`.
4. Zeroes float control `+0xB84` using `xorps`/`movss`, invokes Timer
   default ctor `0x00422D90` at `+0x3E`, clears `+0xB98`, invokes
   Vector3 default ctor `0x00422E10` at `+0x59`, sets byte `+0xBA8=1`.
5. Returns the real object pointer with `ret 4`.

A **natural C++20 polymorphic `NativePolygonMotionGroup : AnimationCallback`**
constructor with real member initializer order and the used
`Animation*` base argument produces **113B /30 x86**, **93/93 original
nonrelocation bytes**, and all **five** native relocation field offsets,
kinds and independently verified original targets, **when compiled without
`/EHsc`**. With `/EHsc` it produces an unrelated **169B EH prologue**.
This is a genuine source and compiler-profile lead, not proof of a
coherent linked owner or permission to admit the function.

**Critical incompatible-header frontier:** The accepted 156B C++17 `/sdl`
scalar factory currently uses a single canonical 0xBAC class with a native
pointer field at `+4`. An alternative purely inherited `AnimationCallback`
base eliminates the original C++17 factory's automatic zero-initialization
call: the same factory then compiles **143B** instead of its accepted **156B**,
although the 113B constructor becomes structurally exact. Restoring the
factory using a *dummy direct pointer purely to shape codegen* would be
unjustified: the original `+0xB98` word is initialized to zero and assigned
from a configuration argument, but no independent pointer semantics have
been established. A brute-force native x86 search finds the `+0xB98`
displacement at only these two stores. No extra field/union or fake
constructor-only type is admitted to production sources merely to make two
independent probes both appear exact.

The complete typed inheritance hypothesis, changed-source Git diff,
source snapshots and pinned MSVC objects are preserved privately at
`.analysis/gptweb-constructor-113-frontier/` and
`build/gptweb-probe/` for re-examination. The three actual previously
accepted native source/header files were **restored only after this
preservation and verification**, without discarding any user-authored work
or rewriting accepted local commits. The new 113B C++ source remains
private (not a competing public class definition), and its compiler
result is **diagnostic structural exact, NOT canonical strict exact**.

The original 78B `0x0045F2B0` array ctor has an EH registration, two
HIGHLOW fields for EH/cookie, one original **DIR32 reference to the
newly exact 60B segment ctor `0x0045F3C0`**, and a native E8 to
`0x0040BC20` to construct three actual `0x3D4` records. Simple
`std::array<T,3>` candidate sources so far emit only 28B, 36B or 41B,
not 78B. The original **75B `std::array<Vector2,61>` constructor at
`0x0045F260`** also remains unresolved: current C++20 codegen emits
33B (an EH/array helper protocol difference), and no exact unit is
accepted for that native head. By contrast, 75B color-word array
ctor and 60B segment ctor are now independently whole strict exact.

[`scripts/verify-animation-polygon-segment-construction-native.py`](../scripts/verify-animation-polygon-segment-construction-native.py)
provides original-only immutable complete function extents, native E8
site/targets, HIGHLOW references and the original group vtable. Next
progress should reconcile the **two truly open 75B/78B array constructors
and the factory/derived-class ABI in one genuine coherent source owner**,
with local strict replay of affected providers only. Do not infer parent
exactness from already exact children, invent padding or rewrite the
156B previously accepted factory to force the 113B method.
