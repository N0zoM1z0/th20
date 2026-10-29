# CORE/AUDIT-292 — complete C++20 shot-emitter root trials and real 3,832-byte MSVC contribution

**Later CORE/RECON-571 current whole-boss status:** The complete
original 3,735-byte Bullet emitter remains **NONEXACT** but its real
maintained C++ was subsequently corrected for the original
`Context::bullet_controller()->file` child-Animation ownership path,
true game `geometry::norm_xy` and `scalar_math::arctangent` calls,
original `scalar_math::absolute(sine)` wave amplitude, additive
heading, and **`Vector3::operator-=` instead of +=**. The opcode-1
command now does **three independent original pmr::vector index
E8 calls and signed 16-bit `operand_10` reads**, rather than caching
one 32-bit value. [Complete original immutable PE gameplay evidence](BULLET_EMITTER_3735_COMMAND_AND_MATH_GAMEPLAY_CORRECTION.md).
Current full compiled C++ emits **3,628B/919 instructions with 828/935
original ordered mnemonics aligned**, and **60 candidate E8 vs 60
original E8 by count only**; original legacy STL move E8 and bytes
remain mismatched. Older 3,516B and 3,561B nonexact compiler
checkpoints below are historical, not current. No original parent
byte credit, public header edit or global cold replay in this pass.


**Later CORE/EXACT-563 entire-parent correction:** The maintained
3,735B Bullet emitter now restores **four actual original game E8 calls**:
`0x00482252 -> 0x004299D0` (Animation reset),
`0x00482297 -> 0x004856C0` (newly whole-exact **18B** BulletStyle
`type_to_script`), and both `0x00482390`/`0x00482481 -> 0x0045D650`
(typed BulletColor word assignments, physically folded with the
already exact 24B PackedColor body, **zero duplicate byte credit**).
The full C++ source currently emits **3,561B / 904 instructions**
with **809/935 original mnemonic heads** aligned and 57/60 native
original direct E8 calls represented, versus the older checkpoint's
3,516B/890/792/53. **The entire 3,735B Bullet emitter remains
NONEXACT**; original switch tables, STL move-ownership and other
callees remain open. Only 32 original header-dependent compiler
sources and 72 strict units were freshly replayed, 72/72 exact;
no whole global cold replay. [Full immutable original E8,
source/canonical 18B and physical folded alias proof](BULLET_EMITTER_REAL_CALLS_18_EXACT_RECONSTRUCTION.md).


**Historical CORE/AUDIT-292 private-source checkpoint, superseded by
[CORE/RECON-514](BULLET_EMITTER_3735_MAINTAINED_SOURCE_FRONTIER.md).**
The complete original 3,735B Bullet emitter is now a real whole typed
`src/BulletEmitter.cpp` in the maintained game-source graph, not only
private `.analysis` experiments. Independent native 60 E8/43 unique
call targets and 13+11 original jump-table cases were rechecked; the
original `rows > 1` speed-branch shape was repaired and the current
native candidate emits 3,516B / 890 x86 instructions with 792/935
original opcode kinds aligned. It remains **NONEXACT**, with no newly
accepted original function bytes. The authentic 298B allocator ABI was
added to the real production header; 38 actual affected source objects
and **91/91 original strict units** were cold rebuilt and replayed,
without a global replay. The older full source tests below are retained
as historical evidence, not current source-presence status.


Native source of truth: immutable Japanese TH20 v1.00a Steamless PE,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This audit pursues the **whole 3,735-byte, 935-instruction**
`BulletController::emit(const ShotParameters&, std::shared_ptr<EtamaArgInf>,
int column, int row, float player_direction)` at `0x004818E0`, rather
than an individual shot pattern, child method or decompiler prefix.
It is called by the already strictly exact 339B `BulletController::fire`.
**The entire emitter remains nonexact**, and none of these probes earns
an authored exact mapping or partial native byte credit.

## Original function/exception unwinding and switch-table contribution

The original source-method contribution comprises **3,735 actual x86 code
bytes**, an original **one-byte NOP at `0x00482777`**, the original
**13-entry 52-byte switch table at `0x00482778`**, and the original
**11-entry 44-byte switch table at `0x004827AC`**. Thus the C++ compiler's
whole code-and-table contribution is **3,832 bytes**. The subsequent
**eight `CC` linker-alignment bytes** at `0x004827D8..0x004827DF`
are separate: the full native executable span up to the next method
is **3,840 bytes**, not 3,735 or 3,832. Original whole code SHA-256:
`54c8c60dc8ca5aaf6a97e094db9447150152849e904741f1f110455b002e051d`.
Original full code+table/linker-alignment SHA-256:
`69955b759b7c702bb8a2ae4f379ebcb365e54bb2bdacd616bc658853c3b9e615`.
This exact scope distinction is mandatory for eventual acceptance.

The original method has **935 decoded x86 instructions, 60 direct calls,
43 distinct immediate callee addresses, two genuinely indirect switch
branches, and compiler-managed C++ exception/security-cookie unwinding**
for its by-value `std::shared_ptr`. The independently verified table
labels, 13 and 11 original targets, and two native table checksums are
in [Bullet emitter vector STL origin and switch table audit](BULLET_EMITTER_VECTOR_STL_ORIGIN_AUDIT.md).

## First complete compiling typed owner and both switch bodies

A **whole-function, 200-plus-line C++20 private source draft** now exists at
`.analysis/core288-BulletEmitterFull.cpp`. It compiles under the locked
MSVC 19.44 x86 profile `/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`. Unlike previous descriptive-only
research it supplies all of the following full-method paths in one
translation unit: initial free-list selection and detachment, active-list
head insertion, metadata ownership transfer and context selection;
per-shot speed/angle initialization; **all 13 first shot pattern cases**;
true Bullet 0x528 layout and 16B native Timer operations; the full
0x158-byte existing `BulletStyle` mapping and actual color/style
selection; real resource pointer and Animation allocation/binding;
**all 11 native cancel-type/style cases**; current command-vector
inspection through real `std::pmr::vector<BulletCommand>`; native
Animation/command update, distance check and early Bullet retirement;
full by-value shared_ptr cleanup and native exception-handler shape.

The draft emits an **entire 3,728-byte `.text$mn` contribution**:
**3,629 bytes of compiled method code**, a generated **three-byte
alignment NOP**, then **exactly 96 bytes of compiler jump-table data**.
It has **911 decoded method instructions** and **787/935 ordered native
instruction mnemonics aligned** with the entire original game method,
with 123 COFF relocations (99 ordinary code fields plus **24 switch-table
fields**). Neither the 3,629-byte body nor its two tables matches the
original exact content; the apparently close **3,728B versus 3,735B**
figures would be an invalid comparison because the former includes
96B of table data and the latter does not. Original complete compiler
contribution is **3,832B**, not 3,735B.

## Independently corrected metadata ownership and shot pattern semantics

Original native disassembly at method offsets `+0x09A..+0x0BF` proves
the game **first queries the incoming shared_ptr once** through the
real folded 16B `.get()` target `0x0040C300`, retains the resulting
`ShotMetadata*`, then moves the owning shared_ptr into the Bullet
at `+0x98`. The first draft incorrectly accessed
`bullet->metadata->` repeatedly, introducing extra getter calls.
The typed revision `.analysis/core290-BulletEmitterFull-RealMetadataLifetime.cpp`
preserves the native one-time metadata pointer plus move, removes an
extra pre-switch Bullet-speed store, and uses the original
`ShotParameters::count` parity (offset `+0x24`) for the first pattern
branch rather than mistakenly using `rows` at `+0x26`.
All changed expressions correspond to real native gameplay and owner
semantics; none is filler or a dummy stack local.

The revised entire function emits **3,516B method code** and two native
24-pointer/96-byte tables, **3,612B total**, **890 instructions**,
**787/935 ordered original instruction kinds aligned**, and 116 COFF
relocations (92 code + 24 table). The shrink is real: correcting
ownership removes several spurious standard-library getter calls.
Thus restoring semantic correctness did **not** make this emitter
byte-exact; length or instruction-count proximity is not sufficient.

Further independent *whole-body* variations of the actual
`std::shared_ptr` move protocol appear in
`.analysis/core292-emitter-move-ownership.py` and
`.analysis/core292-emitter-ownership-results.txt`.
Eight complete variants were freshly compiled. Named shared_ptr
reference alternatives emit 3,527B code; explicit temporary
construction/swap variants emit 3,551–3,589B code. The strongest
current ordered-mnemonic alignment is **789/935**, but none has the
original relocation shape or 3,832B full contribution.

## Original 63-byte shared_ptr move assignment is not yet exact

Native original `0x0047C530` is a complete **63B** standard-library
`std::shared_ptr<EtamaArgInf>` move-assignment operation. Its x86 path
calls an actual `std::move` operation at `0x0040B280`, constructs a
shared_ptr move temporary at `0x0047B820`, swaps at `0x00486690`, and
retires the temporary at `0x0047C300`. A direct explicit instantiation
of the **current** locked MSVC standard-library template emits
**54B**, without the original extra `std::move` call. An independent
private user-defined specialization of that move assignment emits
**87B with an additional stack cookie/exception path**, also nonexact.
Both incompatible whole-code trials remain private in
`.analysis/core289-ShotSharedPtrMove.cpp` and
`.analysis/core291-ShotSharedPtrLegacyMove.cpp`; neither is admitted,
renamed to a game method, nor counted in authored bytes. The old STL
implementation's physical call sequence and source/compiler version
need separate corroboration rather than a forced inline call or fake
function body.

Both original compiler tables are generated in the private full
function's COFF contribution with **24 actual DIR32 code-label
relocations**, independently confirmed as **13 first-mode cases plus 11
second-mode cases**. Their *contents and original absolute branch
destinations remain nonexact*. The already admitted 33B and 41B
`std::pmr::vector<BulletCommand>` methods remain genuine library-origin
complete functions, **excluded from authored game coverage**.

## Remaining whole-method barriers and validation scope

Original external manager methods `AnimationPoolOwner::allocate_animation`
(298B at `0x0044C9B0`) and `AnimationFile` script binding
(338B at `0x004383A0`) remain nonexact; the manager's giant native
allocation owner layout is not faked in `src/`. The private draft uses
only real existing types plus a narrowly provisional external
allocation declaration in `.analysis/core288-AnimationRuntimeOwner.hpp`.
No private declaration or nonexact C++ draft was copied into the
maintained source graph. The complete original 66B Bullet intrusive-list
`prepend` callee at `0x0044A6B0` was rechecked with 14+18 naturally
equivalent boolean/control-flow variants; the strongest private
result remains **56/58 non-relocation bytes** with two genuine compare
operand-orientation differences. No fake assembly/pointer cast or exact
manifest entry is accepted for it.

**No maintained C++ source, shared header, canonical profile, native
function ledger or original target bytes change in this checkpoint**.
Only this English evidence and navigation records change, so the
actual affected native replay scope is **zero exact units**, and no
unfiltered cold replay is run. The complete exact 2,018B Bullet
collision boss, 1,846B Bullet physics boss and 339B firing orchestrator
remain protected and counted once. All remaining original large roots,
including this 3,735B emitter, 1,404B command11, 273B group draw,
12,140B command sequencer and 41,967B Enemy opcode, remain nonexact
until their own **whole native functions** replay with all original
relocations.
