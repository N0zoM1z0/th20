# CORE/EXACT-417 — entire original 1,081-byte Player option frame boss and 70-byte fixed-point presentation ABI

Immutable comparison target: user-approved Japanese TH20 v1.00a Steamless
`resources/th20.exe`, full SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The previously open **whole 1,081-byte** native game routine at
`0x004FA860` is now reconstructed as the real maintained
`Player::update_option_frame(PlayerOption*)`, including **all 325
original x86 instructions**, complete EH/security-cookie protocol,
both option animation handles, focus changes, signed timer gates,
original integer interpolation and per-option callback/position
ownership. Its separate original 70-byte fixed-to-presentation
conversion callee at `0x004FEE00` is also whole strictly exact.

| Whole original native routine | Original physical entry | Strict whole bytes | Native x86 instructions | Original PE E8 / HIGHLOW fields |
| --- | --- | ---: | ---: | ---: |
| `Player::update_option_frame(PlayerOption*)` | `0x004FA860` | **1,081/1,081** | **325/325** | **39 / 1** |
| `IntPoint::to_vector3(Vector3&) const` | `0x004FEE00` | **70/70** | **20/20** | **0 / 2** |

Exactly **two new physically distinct game-owned functions and
1,151 original machine-code bytes** are admitted; none of their
boundaries overlap older accepted original functions. Their
complete immutable original SHA-256 intervals respectively are
`15d55387bfaae29de1e11979d1289b4199b12bcee5b8c07e2651f2bf28c531dd`
and
`dad21b8e411d0065213fa0c2e64c2b1dbbae93520718d9ac9cdd2e38552785bd`.

## Independent native caller and concrete typed ownership

**Updated identity (CORE/RECON-432):** The old tentative name
`Player::frame_changed` at `0x004F9C30` was wrong.
A completely different **25B exact canonical**
`Player::frame_changed()` already exists at
`0x004C0CE0`. The enclosing 3,111B body is
currently an unnamed, independently nonexact
Player main-frame routine. See its
[full native 783-instruction call-graph audit](PLAYER_MAIN_FRAME_3111_NATIVE_FRONTIER.md).


The **3,111-byte** original *unnamed Player main-frame routine* at
`0x004F9C30` calls the option-frame routine at **two separate
original call sites**, once per source-array traversal. Its
real receiver is `Player*` in ECX and its single stack argument
is a concrete `PlayerOption*`, a 300-byte object: native
`ret 4` preserves the original `__thiscall` ABI. The
maintained complete parent body lives in
`src/PlayerOptionFrame.cpp` and its true class declaration
is `src/Player.hpp`.

The option-frame method constructs a genuine `Vector3`
presentation position and returns immediately for disabled
options. A change in focused/unfocused state retires the
appropriate existing AnimationHandles, selects the true
script-table bases `PlayerShotData +0xA8` / `+0x88`,
asks the actual WeaponStoneInfo variant selector to choose
the script, spawns the corresponding native ANM handle and
interrupts the real animation state at event zero. It
updates the real `PlayerOption` focus byte at `+0x104`.

The native main branch checks **bit 1** of the Player
`entity_flags` at `+0x14` and of the option flags word
at `+0x100` with actual `shr 1; and 1`. It selects
one of the two real IntPoint offsets at option `+0x80`,
updates the current fixed position at `+0x70`, and
conditionally invokes the option's two callbacks.
The original callbacks have the **option object in ECX**
and no stack arguments. A special-entity branch
instead uses the live Player fixed position, and at
the native signed frame threshold 30 deactivates the
option and retires both animation handles.

The interpolation branch constructs a real `IntPoint`
temporary; when the Player frame counter at `+0x20E4`
is at least 30, it evaluates the genuine chained
low-32-bit operation

`diff = ((fixed_position - previous_fixed_position)
         * signed(frame_counter)) / 100`

as original **whole aggregate returns**, followed by
the true two-coordinate nonzero predicate. It adds
the resulting IntPoint to the saved fixed position or
copies the target on zero. An active hold/delay counter
instead decrements and copies the fixed position.
Finally, the method converts the saved IntPoint to a
real 3-component Vector3, forwards the result to both
animation handle positions and records the previous
presentation position in the option.

These are full native gameplay branch/field/call semantics,
not mere matching instruction mnemonics. The enclosing
3,111-byte `Player::frame_changed` **remains a separately
unclosed, nonexact function**; its exact option-frame
callee is not a claim that the entire frame root or linked
game executable is complete.

## The decisive four-byte member-function pointer ABI

The original native callback call sites have exactly two
real loads of the live option receiver followed by
`mov eax,[option+0x120]; call eax` for one branch,
and `mov edx,[option+0x11C]; call edx` for the other.
They use **ECX as the thiscall receiver**, including
the original post-call compiler NOP.

The earlier complete C++ frame source, using raw
integer callback fields and reinterpret-cast free-function
pointers, emitted **1,091 bytes / 327 instructions**:
two superfluous 5-byte local callback pointer spills.
All **325 original mnemonic kinds** already aligned in
order, but those extra real bytes prevented whole
native exactness. **Retyping the actual original option
fields as**

`void (PlayerOption::*field_11c)();`
and
`void (PlayerOption::*field_120)();`

**recovers genuine one-word MSVC single-inheritance member
function pointers**. Their sizeof values are statically
asserted to be exactly four bytes on the pinned MSVC i386
target, preserving the actual option layout, field offsets,
constructor and both enclosing Player option arrays.
Natural calls `(option->*option->field_11c)()` and
`(option->*option->field_120)()` then emit precisely
the two original direct register calls, eliminating
both unobserved spills. The full maintained method
naturally emits **1,081/1,081 exact original bytes**,
including all 40 external relocated fields, with no
manual assembly, artificial locals, forced NOP padding,
or shortened original byte range.

Earlier alternatives using `__fastcall`, `__thiscall`
or `__cdecl` **free-function pointers** were compiled
and rejected: they retained extra stores or wrong
stack argument cleanup. The retained ABI is grounded
by the original callback state/receiver instructions,
not chosen by byte length alone.

## Original IntPoint conversion and five independently exact coordinate callees

The 70-byte native `IntPoint::to_vector3` performs the real
signed `cvtsi2ss` of both 32-bit fixed-coordinate lanes,
divides them each by the same original float
`128.0f` at **`0x0056CD98`**, and writes Z as zero
without touching unrelated output storage. Its two
original PE `HIGHLOW` fields are at `+0x12` and
`+0x29`, both independently targeting that float.
It has **no original E8 calls** and returns with
the original `ret 4`. Its real source is added
beside the existing whole-exact fixed-coordinate
`IntPoint::assign_scaled` in `src/PlayerFixedPoint.cpp`,
which retains its original canonical owner and MSVC
profile.

The 1,081-byte frame uses all five independently exact
`IntPoint` whole functions admitted in CORE/EXACT-410:
49-byte scalar inequality, 45-byte multiplication,
48-byte subtraction, 45-byte signed division and
65-byte by-value `operator+=`. Their complete
physical game-original bytes are *not* re-credited here.

## Independent original PE E8 and HIGHLOW reference proof

The original immutable 1,081-byte PE interval was
independently decoded into **all 325 native x86
instructions**. Direct original E8 instruction operands
provide exactly **39 REL32 fields**, and the immutable
PE `.reloc` section provides **one DIR32/HIGHLOW**
field at `+0x0A` targeting the genuine security cookie
`0x005B25C0`. All **40 original field offsets/types and
independently original targets** match the current
MSVC COFF object exactly. The 70-byte method's separate
two HIGHLOW fields at `+0x12`/`+0x29` also match the
actual original PE and real native float source.

Original independent references include real Player
`player(0)`, focus predicate, animation handle retirement,
AnimationFile script spawn, WeaponStone script variant,
`IntPoint::operator+/-/*//+=`, scalar inequality,
two AnimationHandle position stores and native security
check. The original executable additionally contains
an actual **folded code address `0x0041CAF0`**:
the candidate emits the true `Context::player_record()`
accessor symbol while the earlier canonical inventory
also classified the identical physical 17-byte code
as `FloatInterpolation::duration_value`. The current
reference targets the *one* immutable native address;
neither same-bytes source spelling receives an
additional duplicate physical-function claim here.

The complete audit
`.analysis/core416-player-boss-independent-refs.json`
records **all 42 original E8/HIGHLOW fields across
both bodies**, their physical original destinations,
COFF symbol identities, genuine addends and independently
prior exact function-body annotations. This audit was
made from the immutable PE **before** native exact
admission; no address was guessed by reading the
candidate object's displacement.

The exact whole game boss compares **921/921
nonrelocation bytes plus 160/160 original relocation
bytes**, and the 70-byte conversion compares **62/62
nonrelocation plus 8/8 relocated original bytes**,
using the unchanged strict oracle and pinned MSVC
19.44.35211 i386 C++20 source profiles.

## Strictly actual affected-only cold replay

**Before any public header changes**, old compiler receipts
were independently collected for all three modified
native interface headers `src/Player.hpp`,
`src/PlayerStorage.hpp` and `src/Rectangle.hpp`.
The union of their old include closures is **31 existing
source providers with 105 old strict native units**.
Two newly exact native routines add **one new
source provider** (`src/PlayerOptionFrame.cpp`)
and one extra exact method in the preexisting
`src/PlayerFixedPoint.cpp` provider, so the entire
real affected set is **107/107 strict native units
across precisely 32 freshly cold-built source
objects**. The seven serial reduced-priority batches
are **5 + 37 + 12 + 7 + 11 + 26 + 9**.
There was **no unfiltered full cold replay**.

In particular, complete older native original
**1,518-byte Player option animation rebuild**,
**966-byte Player initial reset**, **2,018-byte
Bullet collision**, and the
`PlayerOption` constructor (`440B body,
445B including independently original CC alignment`)
and `PlayerShotPool` ctor (`81B body, 86B including
original CC alignment`) still pass the strict
oracle. The changed callback field type does
not silently damage their original ABIs.

Six MSVC compiler-private `$SG` symbols
renumbered in original Player/Dialogue/Ascii
constructors after the shared header edits.
All were accepted only after independently
checking their immutable native original string
destination, relocation offset/type and complete
nonrelocation bytes, followed by a fresh unchanged
strict compare. Their real original destination
addresses, private old/new symbol spellings and
offsets are in
`.analysis/core417-reconciled-private-symbols.json`.
Actual preedit receipt closure:
`.analysis/core416-option-frame-preedit-closure.json`;
complete scoped replay batches:
`.analysis/core417-option-frame-replay-batch0.log`
through `batch6.log`.

These exact original native functions are
not a claim about invalid resource safety,
whole-game executable linkage, or the still-open
3,111-byte parent Player frame controller and
41,967-byte Enemy ECL dispatcher.


## Subsequent CORE/EXACT-420 Player frame mode and secondary-option closure

The still-open complete 3,111-byte enclosing Player frame
caller additionally uses three whole game-owned methods
now strict exact: **23B** `movement_mode`
at `0x004FF870`, **75B** `set_movement_mode`
at `0x004FFF10`, and **90B**
`set_secondary_option_field_fc` at `0x004FB340`.
These are independent original native source bodies
with all **three original PE E8 references** attested.
The two-bit movement setter's native 75B code relies
on returning the genuine bit-field assignment
expression, and the secondary delay setter iterates
12 real 300-byte options. They do **not** alter or
recredit the already exact 1,081-byte per-option frame.
The actual previous two-header receipt closure passed
**84/84 native strict units across 28 cold objects**,
without any global full replay. The 3,111-byte
enclosing Player frame remains separately open.
See the [three Player mode and secondary-option whole
native proofs](PLAYER_MOVEMENT_MODE_188_EXACT_RECONSTRUCTION.md).
