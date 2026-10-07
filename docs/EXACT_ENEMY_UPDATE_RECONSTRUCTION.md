# Whole Enemy movement update and its actual owners

EXACT-061 reconstructs the complete 1,675-byte Enemy movement update and fourteen
related owner/interface functions. The batch adds 4,205 instruction bytes and
ten compiler alignment bytes. The frozen graph contains 442 whole units,
84 cold objects and 84,017 disjoint comparison bytes. New origins remain pending;
the conservative authored total stays 64 functions / 16,948 bytes.

## Complete contributions

| Address | Body bytes | Compared bytes | Operation |
| --- | ---: | ---: | --- |
| 004A7710 | 1675 | 1675 | Whole EnemyState movement update |
| 004D8990 | 941 | 946 | Complete Graphics construction |
| 004D88C0 | 204 | 204 | Graphics flag construction |
| 00471790 | 319 | 319 | Complete viewport construction |
| 004B9C10 | 473 | 478 | Complete configuration construction |
| 00448A30 | 186 | 186 | AnimationFile construction |
| 00423320 | 133 | 133 | Context construction |
| 00477B80 | 38 | 38 | Motion position assignment from Vector3 |
| 0049BEA0 | 46 | 46 | Orbit mode predicate |
| 004AB2B0 | 46 | 46 | Elliptic mode predicate |
| 0047A540 | 26 | 26 | Motion parameter +20 assignment |
| 0047A520 | 26 | 26 | Motion parameter +24 assignment |
| 004AAD90 | 32 | 32 | Enemy parent lookup through its list owner |
| 0047A2C0 | 25 | 25 | Enemy combined-position reference |
| 0047A630 | 35 | 35 | Float-to-double CRT absolute-value wrapper |

Each comparison includes its entire COFF contribution. Graphics and
Configuration have five trailing INT3 bytes each; those bytes also replay.
No dispatcher case, prefix or shortened comparison receives credit.

## Movement, following and animation order

The first operation snapshots combined Motion +110 into +C8. Flag word +2D0
bit 3 then copies the parent's combined position into record zero's Motion.
The parent comes from Enemy's +3E4 link owner and that list's node value. It is
not a spawn-position fallback. Initialization establishes the required movement
and animation records; no invented null/empty-container recovery is added.

Each actual 388-byte movement record follows the same ordered protocol:

1. Sample nonzero +AC angle duration only outside orbit/elliptic modes, normalize
   the angle and assign it. Skipped angle interpolation does not advance.
2. Sample nonzero +D8 speed duration, then nonzero +104 two-parameter duration.
   The +144 interpolation is retained by this operation.
3. Sample the current-first position interpolation when its duration is nonzero
   and write the sampled-minus-current displacement; otherwise update velocity.
4. Update position. Flag word +2CC bit 10 then adds viewport zero's final vector,
   even when the record's own Motion updates were frozen.

The existing complete composition/bounds body runs after all records. Flag
word +2CC bit 4 enables animation selection from displacement X: below -0.03,
above +0.03, or the middle direction. Previous directions -1, 0 and 1 select
the native transition offsets; other previous values retain transition zero.

A direction change resolves the previous animation, constructs a zero position
and looks up the file **before** retiring the previous handle. A successful
lookup supplies the retained position. Spawn receives a null expected-stem
pointer, base script + transition, that position, zero rotation, base layer +7
and zero flags. The returned four-byte handle is stored before direction changes.
Independent callee 450CB0 compares the optional name against the file's PMR stem;
the first spawn argument is a character pointer, not an integer group identifier.

The final lookup refreshes extent X from animation height and extent Y from
animation width. A failed lookup clears the handle while retaining old extents.
These calls widen float to double, invoke CRT `fabs` at 550230 and narrow to
float. The earlier comparison-based geometry absolute value at 445680 is a
different operation: it retains negative zero and NaN sign. The shared
ScalarMath wrapper preserves the native signed-zero/NaN behavior here.

Horizontal departure is checked before vertical departure. The comparisons
are strict, with horizontal limits +/-192 and vertical limits 0/448, adjusted
by half the corresponding extent. Departure clears word +2D0 bit 6. A previously
entered entity returns -1 unless the corresponding word +2C8 axis exception is
set. An inside result sets the entered flag and bit 6. Ordered comparisons
preserve the native NaN behavior and the horizontal branch's priority.

## Full owners and initialization

The native 40AA10 startup independently identifies Graphics base 5C4D40 and
0xDE8 storage. Its separate constructor establishes six ViewportState values at
+278, stride 0x16C; viewport construction establishes final_vector at +144.
Thus the movement offset at 5C50FC belongs to the real enclosing global. The
maintained declaration does not invent a separate global array lifetime.
The production global definition, startup wrapper and destruction remain open.

Graphics contains actual RECT/DIDEVCAPS records, two 64-byte matrices, a
viewport, three 56-byte D3D presentation records, display mode, typed resource
pointers, five independent animation pointers, an AnimationHandle, Configuration,
six viewports, D3DCAPS9, snapshot storage and two actual Worker values. Native
builds use the pinned Windows SDK records directly; explicit portable API records
serve the owned host tests. Native size/offset assertions cover the full owner.
Names for unresolved scalar roles retain offsets; original source spelling and
roles of secondary presentation records remain unknown.

Matrix construction leaves all sixteen floats intact. This is distinct from
the existing zeroing Matrix4. Viewport construction calls seven individual
Vector3 constructors, initializes both actual viewport records, calls two
individual Vector2 constructors at +11C/+124 and constructs a three-element
Vector2 array at +12C, followed by the final vector and FogValue. The two boundary
Vector2 values are cleared; treating them as four uninitialized float lanes was
a rejected private hypothesis.

Graphics retains matrix elements, device capabilities, +DB0 and version size
+DC0 during construction. Configuration constructs two real InputBindings
values, initializes its low option bits and scalar fields, and preserves implicit
alignment bytes +77/+A5..A7 and high option bits. GraphicsFlags independently
clears its low fields, sets bits 7/11 and retains bits 14..31. There is no blanket
constructor clearing, packed reference transport or explicit padding member.

AnimationFile is 0x70 bytes: two actual PMR strings, byte/template/descriptor
pointers, counts and a real atomic uint32 value at +5C. Its nested standard
atomic constructor chain independently replays in full. Context has twelve
independent pointer slots and is 0x30 bytes. EnemyController's complete 0x134
declaration includes its real TaskInfo base, EnemyData, PMR vector, timers,
eight file pointers, EclLoader, list and Identifier32. That controller's
constructor, destructor and file-selection body are still undefined.

The 38-byte position-only Motion assignment has independent Bomb consumers at
477DAE/479FF1 on their +28 Motion owners, as well as the Enemy use. The maintained
overload changes only position and returns its receiver. Its source name and
return-reference spelling are reconstruction choices; machine protocol and
storage behavior are independently established. Shared Vector3 copy/move
contracts are unchanged.

## Compiler, replay and verification boundary

EnemyMovementUpdate.cpp uses the strict-FP/GS/SDL recipe; precise FP folded the
two constant bound divisions and did not reproduce the complete body. Other
owners retain their manifest recipes. These are local compiler recipes, not a
claim about original translation-unit partition or executable-wide flags.
The actual nonthrowing Graphics/Configuration constructors reproduce complete
29-byte EH handlers and 36-byte flags-5 FuncInfo records independently.

All caller relocations use separately exported native definitions, established
shared owner methods, decoded readonly float values, complete array construction
and global startup evidence. Fourteen complete supporting alias/library/EH
contributions also replay without overlapping function/byte credit. Structural
diagnostic destinations are not used as solved anchors. The first strict replay
exposed the wrong absolute-value dependency; its independently exported callee
led to the semantic correction above.

Owned C++20/O2/UBSan tests execute the maintained complete movement, actual
Motion/list/Enemy construction, animation extents, Graphics/viewport/configuration
construction and shared interpolation. They cover following, snapshots, frozen
offsets, orbit/elliptic angle retention, interpolation order, all direction
transitions, file-before-retirement order, missing handles, retained extents,
strict limits, horizontal priority, negative zero and NaN. Dirty storage tests
check retained matrices/caps/scalars/option bits and implicit configuration gaps.

Unresolved ECL base lifetimes, controller lifetime/file selection, renderer
lookup/retirement, animation spawn and allocator/global startup use explicitly
bounded **test fixtures**. Unexpected ECL virtual/stack operations abort. These
fixtures neither implement production bodies nor establish whole-game runtime.
Native handle/file wrappers and their complete callees establish the caller ABI;
accepting the movement function does not accept those dependency implementations.

The complete 41,967-byte Enemy opcode dispatcher and its full tables remain the
next core priority. No partial opcode credit or playable-game claim is made.
