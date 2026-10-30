# CORE/RECON-908 — original 20B polygon group destructor: real virtual-table ABI versus `novtable`

The locked Japanese TH20 Steamless 1.00a target is SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This report describes a **bounded, source-only nonexact frontier**, not a new
strict unit, and preserves the previously accepted
[entire 113B game constructor and 49B MSVC scalar-deleting wrapper](ANIMATION_POLYGON_GROUP_CTOR_113_DELETE_49_STRICT_EXACT.md).

## Original executable facts

[`scripts/verify-animation-polygon-group-ctor113-native.py`](../scripts/verify-animation-polygon-group-ctor113-native.py)
reads only the immutable PE `.text` and `.reloc`. The physical original
`0x0045C2A0` ordinary destructor is **20B /10 complete x86 instructions**,
with exactly one E8 at original instruction `+0x0A → 0x00446BA0` (the actual
`AnimationCallback` base destructor), no HIGHLOW, and a final `ret`.
The already exact **49B** original scalar-deleting wrapper at `0x0045F5A0`
physically E8-calls this **separate 20B** head. The original derived
vtable at `0x0056EE50` points to the 49B wrapper, exact 140B update and
exact 233B draw. The genuine **113B** original derived constructor writes
that vtable into the object via original PE HIGHLOW field `+0x18 → 0x0056EE50`.

## Compiler behavior from 30 isolated full-body probes

Five natural/ABI declaration variants were each compiled under six pinned
MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise` profile variants:
normal, `/GR-`, `/vd0`, `/vd1`, `/vd2`, and no `/sdl`. All source snapshots
and logs remain in the ignored private
`.analysis/gptweb-group20-experiments/` and their separate probe objects in
`build/gptweb-probe/Dtor20_*.obj`.

| C++ type/definition | 20B destructor candidate | 113B constructor candidate |
| --- | --- | --- |
| Actual polymorphic derived class, `~Derived() = default` | 29B, **NONEXACT** | **113B structural exact** |
| `final` polymorphic derived class | 29B, NONEXACT | 113B structural exact |
| User-provided empty destructor body | 29B, NONEXACT | 113B structural exact |
| `noexcept` destructor | 29B, NONEXACT | 113B structural exact |
| `__declspec(novtable)` on the derived class | **20B, structurally exact** | **104B, NONEXACT** |

The 29B ordinary derived destructor naturally writes its derived vptr before
calling the original base destructor, adding nine nonoriginal bytes. The
`novtable` declaration suppresses precisely that write, yielding the original
20/20B body; **but the same annotation also suppresses the true derived
vtable write in the constructor**, reducing its formerly exact 113B body to
104B and breaking the known original virtual dispatch. This is a genuine
class-definition contradiction under the tested source/profile combination,
not permission to compile two conflicting class definitions or manually
write a private vptr. `/vd` and RTTI flags do not resolve it.

The untouched maintained class continues to reproduce the exact **113B
original constructor, 49B scalar wrapper, 140B update and 233B draw** in a
single ODR-consistent source owner, with a separate 156B exact factory.
The 20B destructor remains **NONEXACT**. An original COMDAT alias, another
legitimate source owner or a different native compiler lowering is possible
but has **not** been independently demonstrated. No dummy locals, handwritten
vtable assignment, machine-byte patch, invented native credit or whole-project
cold replay were used in these experiments.

Next: identify the physical class/destructor ownership from original
RTTI/vtable/reference users rather than promoting an isolated 20B
`novtable` match whose shared 113B parent regresses.
