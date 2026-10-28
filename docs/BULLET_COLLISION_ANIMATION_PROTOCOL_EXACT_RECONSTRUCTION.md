# CORE/EXACT-266 — seven complete 233-byte Animation and handle methods supporting the 2,018-byte Bullet collision boss

The immutable Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
is the independently attested native source. Seven **entire** original
Animation and AnimationHandle gameplay methods used in the 2,018-byte
`Bullet::process_collision` boss and 662-byte `Bullet::cancel` boss have
been recovered as ordinary natural C++20, compiled under the locked
MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` profile, and strictly compared to the whole original bodies.
No NOP padding, manual assembly, fake owner prefixes, partial functions
or fabricated relocated targets are involved.

| Complete native original method | Address | Bytes | Relocations | Canonical strict result |
| --- | --- | ---: | ---: | ---: |
| `Animation::set_collision_color_mode` | `0x004863C0` | **45** | 0 | **45/45** |
| `Animation::set_base_position` | `0x00470AF0` | **38** | 0 | **38/38** |
| `Animation::set_tint_channels` | `0x004864B0` | **62** | 0 | **62/62** |
| `cancel_animation_handle` (mode 1) | `0x00479040` | **22** | 1 | **22/22** |
| `cancel_animation_handle_mode2` | `0x00486310` | **22** | 1 | **22/22** |
| `cancel_animation_handle_mode3` | `0x00486350` | **22** | 1 | **22/22** |
| `interrupt_animation_mode3` | `0x00486370` | **22** | 1 | **22/22** |

**Seven entire original methods, 233 new game-authored native bytes and
four independently checked relocation sites, all strict exact.**
Original whole-body SHA-256 in table order:
`d28d3ede5fc207ceb7a727b2f8349b2d003178a9e31833c2240009a545174bad`,
`faa8e5bd186818a6bdb7a0b18b1f29b30947266a77598f4765ec2416664f885a`,
`62c70d6e7fdb9bd0d83c2158f4c3618b1adcf81bdcc6ed25ad3316f40bbd2c14`,
`4ccc17f2dce23770fc5888066065ee71c0fb22ba84a15b7a0d5c5ef254b1a524`,
`c1811bd479a8fd856edc5f54ce394ff32124a6a3b4a107671d59e9a76d7e39d1`,
`6310a36f7fd2185497cb28e62b1e5b7c5ca95985592336333e64b6dfd0bd40f5`,
`26d1362c74693d87b3aaf12977731af65e8d699874ff09c8b3327c253f86b0c5`.

## Actual Animation fields, flags and full protocol

The original 45B `Animation` setter at `0x004863C0` writes **the real
3-bit `AnimationFlags::color_mode` field** at Animation+`0x4A1` in
bit positions 2..4. MSVC naturally emits the native `0xE3` mask,
three-bit truncation and left shift. The maintained field was already
present in `src/Animation.hpp`; no artificial bitmask storage is added.

The original 38B `Animation::set_base_position` copies all three
four-byte float lanes to the genuine `AnimationBase::vector_2c` starting
at Animation+`0x2C`. It uses the existing real `Vector3` assignment
operator; it is **not** an Animation+0x5BC transformed screen position.

The original 62B `Animation::set_tint_channels` accepts four original
`uint8_t` arguments and writes their native color-channel order into
`AnimationBase::channels_494`: blue at +`0x494`, green at +`0x495`,
red at +`0x496`, alpha at +`0x497`. Both the native register/stack
widths and all four byte stores match the original PE. The function
is used in the Bullet collision fade animation path.

Four **independent fastcall** wrappers forward the authentic live object
through the original `__thiscall` ABI. Modes 1, 2 and 3 target the
same **actual `AnimationHandle::interrupt(int)` at `0x0044EF90`**, but
pass different exact integer operands; the original code therefore
contains **three distinct 22B entrypoints**, not three aliases of one
relocation. The separate fourth wrapper targets the real
`Animation::interrupt(int)` at **`0x004388F0`**, passing mode 3 on
an Animation pointer. All four source call relocation offsets are
`+0xD`, `REL32`, with their independently attested original addresses;
no separate consumer is renamed to a false callee merely because its
non-relocation bytes happen to match. The `AnimationHandle` wrappers
accept the already observed const-reference ABI used by the complete
662B original `Bullet::cancel`; the const bridge calls an existing
non-const member whose original body reads and forwards the handle.
No new `AnimationHandle` fields or owner facades are invented.

The source is one `src/BulletCollisionAnimationHelpers.cpp` translation
unit with three original narrow member declarations in the actual
`src/Animation.hpp`, and the four wrapper functions have genuine
source-level implementations. All seven functions reproduce the
original whole executable return paths and register/stack effects.

## Entire original 2,018-byte collision boss investigation (nonexact)

Independent native Ghidra/decompiler and Capstone inspection confirms
`Bullet::process_collision(int)` at `0x00484A20..0x00485201` is a
**2,018B / 532-instruction** whole game-owned root, native SHA-256
`7b565186781d77f6a0120ff031b59a849def7798460ffc5d91278ae873688ee3`.
It has **68 direct calls to 45 distinct original addresses** and is
called from both state-1 and state-2 handling in the already exact
211B Bullet step. This is a complete dynamic behavior path, not a
single inline collision predicate.

Original branches are grouped by Bullet flags bit 6 (scaled or native
geometry) and bit 4 (circle or rectangle). The real Player-owned
collision consumers `0x004F8CE0` (XY rectangle) and `0x004F8FF0`
(Player-centered circle) yield original result classes 0, 1 and 2.
The native zero case advances the correct Bullet Timer +`0x4C0` and
can arm a three-stage hit-effect phase. A result of one can set Bullet
state 3, interrupt the animation and handle, spawn an ANM hit effect
and publish genuine effect parameters. The result-two branch controls
graze interactions, animation opacity/scale feedback, repeated player
items/effects, original RNG branching and the three hit Timers. A
special damage collision path can restart from the same genuine hit
label rather than duplicating its side effects.

The seven complete Animation/handle methods now remove verified external
ABI and bitfield ambiguity for the later **full-parent C++20 draft**,
but **the 2,018-byte collision boss itself is not machine-code exact**
and has **zero parent code bytes admitted** here. Other unresolved
actual children include Player collision at `0x004F8CE0` and
`0x004F8FF0`, Player hit handling at `0x004F8B90`, player life/feedback
owners, ANM handle resolution and some effects. They must be
reconstructed with actual typed owners, not `void*` hacks in production.

## Actual scoped exact regression proof

Three narrow `Animation` member declarations in the shared
`src/Animation.hpp` alter the real include closure of **38 existing
source providers / 217 previously accepted strict units**. From
compiler receipts, **all 38/38 old source objects were rebuilt with
locked MSVC and all 217/217 old native units strictly replayed exact**,
including recently completed **1,846B Bullet physics**, **662B Bullet
cancel**, 781B wrap, 898B command3 and numerous old Animation roots.
The only changed existing relocation labels were compiler-private
`$SG` numbering for strings; every shift was accepted only when the
original relocation offset, type and independently fixed PE target
address remained exactly the same, and then the source was rerun
through the strict whole-unit comparator. No byte compare or external
relocation was relaxed.

The seven new whole functions also passed **7/7 exact in one new cold
object** in `.analysis/core266-bullet-collision-animation-canonical-replay.log`.
Together the entire affected-only batch is **224/224 strict native
units across 39 newly built source objects**. Focused old-source logs
are `.analysis/core266-animation-affected-replay-part-{0..3}.log` and
private symbol changes are in
`.analysis/core266-animation-sg-corrections.jsonl`. No unfiltered
whole-repository cold replay occurred. The original locked target hash
is unchanged. The 2,018B collision, 1,404B command11, 273B draw group,
3,735B single-shot emitter, 12,140B Bullet command sequencer and
41,967B Enemy opcode root remain independently nonexact.

## CORE/EXACT-273: both native Player collision selectors now whole exact

The earlier unfinished **777B rectangle** and **466B circle**
Player collision children are now each fully native exact. The original
466B circle uses real `PlayerCollisionBounds` radii, native 100.0f
multiplier from genuine 73B PlayerRecord clamp, 3.6f expansion and
2.5f/40.0f graze-margin floats, then the same FrontInf/state/Timer/hit
outcomes. See [whole Player circle and record evidence](PLAYER_COLLISION_CIRCLE_EXACT_RECONSTRUCTION.md).
The original 2,018B `Bullet::process_collision` parent is **not yet
exact**, regardless of its now-complete two main Player collision
children and seven exact native Animation/handle wrappers.

## CORE/EXACT-275 follow-on — real 51B resolver and 44B full-word test now exact

Two additional complete native caller dependencies of the still-open
2,018-byte `Bullet::process_collision` are now independently strict
exact: full **51-byte** `AnimationHandle::resolve` at `0x0044CED0`
with original native 0x005C0028/0x0044CD00 relocations, and the **44-byte**
fastcall `bullet_animation_handle_valid` at `0x00485A10` calling it.
The latter returns a **full int**, not the decompiler-inferred `bool`;
this restores its original 44B machine code without padding.
One new TU yields **2/2 new strict units / one cold object**, and no old
native source is impacted. See [complete resolver and handle test proof](BULLET_COLLISION_HANDLE_EXACT_RECONSTRUCTION.md).
