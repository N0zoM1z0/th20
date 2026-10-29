# CORE/RECON-571 — restore original cross-controller child Animation, native ellipse mathematics and signed-16 Bullet command state in the entire 3,735B emitter

Target: immutable Japanese TH20 v1.00a Steamless `resources/th20.exe`,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The original whole game-owned `BulletController::emit()` at
`0x004818E0..0x00482776` remains NONEXACT**: 3,735B / 935 complete
original x86 instructions. This checkpoint recovers additional
**real gameplay branches, cross-owner file selection, native math
calls, vector arithmetic and signed ECL command semantics** in its
complete maintained `src/BulletEmitter.cpp` source. No original parent
bytes are credited by making a closer but still different compiler
candidate. The actual real original [298B Animation allocation and
338B script-load children](ANIMATION_POOL_ALLOCATE_298_EXACT_RECONSTRUCTION.md)
remain independently exact; their parent emitter does not inherit
that equivalence.

## Immutable original branch/callee proof and repaired natural C++

All original native call sites below were independently decoded from
the immutable 3,735-byte original game's actual `E8` operands; the
*original* direct-callee head, not a candidate-derived target, is
listed. Each repaired source expression is genuine typed C++ and
uses established real methods; none introduces byte-patch or
artificial NOPs.

| Original direct E8 | Original physical callee | Entire emitter game behavior corrected |
| --- | --- | --- |
| `0x00481F45` | `0x00455FB0` | Ellipse speed uses native `geometry::norm_xy(a,b)`, **not** the CRT `std::hypot(a,b)` |
| `0x00481F66` | `0x00459280` | Ellipse heading uses original `scalar_math::arctangent(b,a)`, **not** `std::atan2` |
| `0x00481FFA` | `0x0047A630` | After original `scalar_math::sine` at `0x00481FF2`, run native `scalar_math::absolute`: negative half-wave changes game speed; previously missing |
| `0x00482310` | `0x0040C300` | Retrieve **`context->bullet_controller()`** then load **that controller's** `file` for the child sprite, rather than `this->file` |
| `0x004825C4` | `0x0047C6C0` | First `std::pmr::vector<BulletCommand>::operator[]` for opcode |
| `0x004825EC` | `0x0047C6C0` | Independently index the same command for first **signed-16 operand** comparison |
| `0x0048261F` | `0x0047C6C0` | Independently index a **third time** for the signed-16 Animation event argument |
| `0x00482681` | `0x00429740` | Original `Vector3::operator-=`, not `+=`, during the first-command two-velocity-step position adjustment |

### Cross-Context ownership is not a no-op accessor

The original at `0x00482307..0x0048231B` loads the *current
BulletController* at `+0x286DA0` (`Context*`), passes that pointer
as the native E8 receiver to `0x0040C300`, and then reads the
returned **other BulletController+`0x286D8C`** `AnimationFile*`.
`Context::bullet_controller()` is already a real maintained typed
method returning `primary_owner`, Context+0; its complete compiler
body in the unchanged real `build/core163-canonical/Context.obj`
is independently **16/16 bytes identical** to original physical
`0x0040C300`. That native 16B getter body was already counted
through another existing linker-folded exact source role, and
receives **zero extra authored original bytes** here. By contrast,
the earlier emitter used the emitter's implicit `this->file`, which
omitted this real E8 call and could select a different controller's
resource in multi-view gameplay. The *main* emitter's separate
`file->load_script` before this child still uses the emitter's
own file; only the original child-spawn path uses the Context owner.

### Original ellipse/sine semantics are not generic CRT math

The original ellipse branch has `E8` to actual `scalar_math::cosine`,
`sine`, `geometry::norm_xy` and the custom two-argument
`scalar_math::arctangent` in that order, not `std::hypot` and
`std::atan2`. The original next waveform mode performs an actual
`scalar_math::sine` call **followed directly** by a distinct
`scalar_math::absolute` call before subtracting the scaled magnitude
from original 1.0f. The old missing absolute-value operation changed
the sign and speed for the negative sine half-cycle. Also, original
`+0x1FDD` executes `addss xmm0,[ebp-0x24]`, preserving the prior
heading rather than overwriting it. The maintained C++ now uses
`heading += circle_angle + shot.angle`, keeping that original state
operand. The exact original mathematical wrappers had already been
accepted as independent physical native functions; **no new game
body credit** is given for calling them correctly from this still
nonexact root.

### Native BulletCommand opcode-1 is three independent indexed accesses

From `0x004825C4` through `0x0048263E`, original code performs **three
separate E8 calls** to the real `std::pmr::vector<BulletCommand>::operator[]`
physical `0x0047C6C0`: the first reads the **32-bit opcode at
command+`0x20`**, the second reads the event field at command+`0x10`
for comparison, and the third reads the event field again to prepare
`Animation::interrupt(event+7)`. The last two original reads are
specifically **`movsx ..., word ptr [eax+0x10]`** at original
`0x004825F1` and `0x00482624`, with **signed 16-bit** game command
interpretation for opcode 1. The maintained C++ previously cached
one `const BulletCommand&` and read the full 32-bit `operand_10` for
both decisions. Caching removed one genuine native E8 and reading
32 bits misinterpreted negative 16-bit event IDs. The source now
uses three independent real vector indexing expressions and explicit
`static_cast<std::int16_t>(...operand_10)` for this opcode. Other
BulletCommand opcodes have different 32-bit field interpretations,
so we **did not** change the public 32-byte `BulletCommand` layout,
break its other already-exact native units, or invent a packed struct.

Finally, original E8 at **`0x00482681`** calls native
`Vector3::operator-=(const Vector3&)` after computing
`velocity*2.0f`. The original source's `position += velocity*2`
was an actual direction sign bug; using `-=` restores the
real native game motion and its whole exact existing 85B Vector3
callee at `0x00429740`.

## Entire 3,735B compiler progress, not a strict-parent claim

| Complete emitter measure | Previous maintained C++ | Corrected C++ | Original native |
| --- | ---: | ---: | ---: |
| Whole method code | 3,561B | **3,628B** | 3,735B |
| Decoded x86 instruction heads | 904 | **919** | 935 |
| Original instruction mnemonics aligned in order | 809 | **828** | 935 |
| Source whole-method E8 call fields | 57 | **60** | 60 |

The **60/60 E8 figure is a count, not an E8 identity or byte-exact
result**. One old original STL `std::move` helper at real native
**`0x00481989 -> 0x0040B280`** is still absent from current compiler
emission, even though independent opcode-1 vector index now restores
an E8 elsewhere. Native original `0x0048199B` also calls a **63B
legacy `std::shared_ptr<EtamaArgInf>` move-assignment implementation**
whose ordinary modern C++ template body remains different. The
the original `0x004826C0` Animation VM call, old EH/shared-owner lifetime,
24-switch-label tables, register/stack lifetimes and additional
nonrelocated bytes remain unproved. Neither matched E8 counts nor
increased opcode alignment mean original machine equivalence.

The complete original game PE audit checks all **935 original x86
instructions**, **60 original E8 field heads**, original cross-Context
load/member offsets, custom math targets, both original signed-16
`MOVSX` instructions, original `Vector3::operator-=` and native
heading addition. The fresh entire C++ compiler source emits
**3,628B / 919 instructions** with exactly **three genuine
`std::pmr::vector<BulletCommand>::operator[]`** COFF fields and two
native-equivalent signed-16 MOVSX loads; all corrected custom game
calls are emitted as actual REL32 COFF fields. Reproducible private
proof and compiler experiments:

- `.analysis/core566-emitter-real-call-restoration-results.json` — nine entire-source native call/math/context variants.
- `.analysis/core567-emitter-maintained-native-score.json` — initial complete parent with real math and subtract branch.
- `.analysis/core569-emitter-three-index-sign-extension-results.json` — five complete opcode-1 signedness/indexing variants.
- `.analysis/core570-bullet-emitter-maintained-score.json` — formal current full-source compiler code/instruction/E8 count.
- `.analysis/core571-emitter-native-five-gameplay-proofs.json` — immutable entire original PE game call, field type, physical folded getter and C++ evidence.
- `.analysis/core570-bullet-emitter-maintained-build.log` — pinned source compilation of this one actual modified unit.

## Focused change scope and honest remaining bosses

**Only `src/BulletEmitter.cpp` was changed.** No shared headers,
existing original strict-exact source files, existing canonical
manifests, unit recipes or original target bytes are modified. The
entire current source was freshly compiled with the locked MSVC
19.44.35211 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` candidate flags, and the whole original
3,735B/935-instruction native body was independently decoded for
all corrected game E8 calls. `src/BulletEmitter.cpp` has **zero
previously configured canonical exact units** (the parent remains
NONEXACT), so there are no affected old native strict units to
cold replay; no unfiltered 1,183-unit full cold replay was run.

The original **3,735B Bullet emitter**, separate **12,140B Bullet
command dispatcher**, **555B Player movement**, **3,111B Player main
frame**, **41,967B Enemy ECL opcode dispatcher** and **39,470B
Animation VM** remain unfinished whole game bosses. Authored exact
coverage is therefore **unchanged: 498 whole original game functions /
175,709 disjoint original native bytes**, 1,183 configured strict
canonical units and 242 unique real compiled source/object providers.
A byte-exact game runtime or final linked original PE is not claimed.
