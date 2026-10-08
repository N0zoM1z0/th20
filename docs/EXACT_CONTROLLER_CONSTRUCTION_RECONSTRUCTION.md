# Actual Enemy Controller and Task construction

EXACT-074 reconstructs two complete constructor contributions: the 312-byte
EnemyController constructor at `4A2E80` and the 68-byte TaskInfo constructor at
`41FD20`. The Controller comparison also includes its five natural compiler
INT3 bytes, for 380 body /385 comparison bytes in total. Original native RTTI
identifies the Controller as `EnemyCtrlInf`; maintained names remain descriptive.

## Actual storage and construction order

The real x86 Controller remains 308 bytes, with the existing 16-byte TaskInfo
base, 164-byte EnemyData, PMR vector of PMR strings, scalar words, Timer, eight
AnimationFile pointers, loader pointer, six-pointer intrusive list, generation
identifier and player/context fields. No reference Services tail or arbitrary
padding is introduced. Existing type/offset assertions and original constructor
calls establish the real subobjects.

Task construction installs the original Task vtable, clears the four-byte flag
aggregate, sets both callback pointers to null and then sets bit 1. The earlier
implicit constructor initialized the final scalar value directly and emitted
53 bytes. A genuine aggregate flag word with the existing raw-word view and
explicit construction phases reproduces all 68 original bytes. The flag's
original declaration and meanings beyond the observed bit remain unknown.

Controller construction calls the real Task/Data/PMR vector/Timer/list/identifier
constructors in order. It initializes all scalar and pointer members, issues
the actual `initialize EnemyCtrlInf\n` diagnostic and advances the process enemy
generation using its default player index 0. The diagnostic is the existing
complete release-build no-op at `40C6B0`; the generation member was already
accepted independently. The native string is at `570404` and is matched by
complete source/COFF/native literal identity, not by solving a relocation field.

The independent native vtable at `5703F8` has three entries: scalar deleting
destructor `4A40A0` and inherited Task slots `421680`/`421760`. Its complete object
locator and TypeDescriptor identify `.?AVEnemyCtrlInf@@`. Only the complete
constructor contribution is accepted; the vtable/RTTI data and deleting
destructor are evidence, without new data or function byte credit.

The Controller's complete 29-byte EH handler and 36-byte FuncInfo replay the
common native records at `567600`/`5A91B8`: zero unwind state and nonthrowing
flag 5. The constructor's declared nonthrowing contract reproduces these
records. The per-source candidate profile is `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`; no executable-wide compiler profile is inferred.

## Semantic verification and exactness limits

The creation test now uses production Controller and Task constructors together
with the existing actual Data, Timer, identifier and generation implementations.
It checks callback/flag defaults, owned PMR/vector and sentinel state, all eight
animation pointers, scalar defaults and the constructor's generation update.
Guarded dirty placement construction verifies deterministic flags/pointers,
counter wrap from `FFFFFFFF` to player-0 generation 1 and boundary preservation.
Controller disposal, VM/startup, Session lookup, whole-list search and allocation
services remain explicit creation-test boundaries. Other loading/movement tests
retain their declared Controller fixtures and now link real Task construction.

Actual construction does not establish whole-game startup, Controller disposal
or the exact emission of every child. The production sentinel list has the
observed final state but its full constructor still emits 31 versus 40 native
bytes because the original assigns the tail twice. This discrepancy remains
recorded; redundant assignments are not added just to force the bytes. PMR
vector support emission is likewise separate from the exact caller contribution.

## Whole search, statistics and allocation findings

The original `find` at `498A80` is a complete 251-byte member, with identifier-0
early rejection, saved end iterator, intrusive observation and cleanup on both
found/missing paths. Native `499130` and `499210` are separate 219-byte list
statistics. They differ from the already accepted scalar count/capacity getters
at `478080`/`45BCF0` and must not replace those getters.

The first statistic excludes nodes according to the complete native predicate
at `49C050`: State flag word 0 bits 5, 0 or 4, or a positive Timer at Enemy
`310`. The second counts State flag word 1 bit 28 at Enemy `354`. Original
semantic names for these flags remain unknown. No partial reader/statistic
acceptance follows from these native observations.

Both statistics and the search pre-initialize an eight-byte result iterator
through the compiler-generated helper at `40C080` before `begin`. Natural
range-for, initializer-list/body/default-argument alternatives and a named
return object all retain the search's missing ten bytes. Unsupported default
constructor declarations and renamed operators were reverted. No explicit
clear, dummy default constructor or inert local is introduced. The class's
actual default/copy/value-initialization and compiler behavior remain open.

Microsoft documents pointer-member initialization under `/sdl` with a
user-defined default constructor; this is a compiler hypothesis, not proof of
the original source. The locked compiler's seven independent fixture variants
did not emit the helper, so the option alone does not explain this target.
See [Microsoft's SDL documentation](https://learn.microsoft.com/en-us/cpp/build/reference/sdl-enable-additional-security-checks?view=msvc-170).

The original Controller allocation member at `4A28C0` is 73 bytes. Both natural
`new T` and `new T()` factory probes emit 60 bytes, without the pre-construction
clear. The reference association containing allocation and construction remains
`reviewed-nonexact`; the exact constructor does not close its unmatched factory.
Original reference free/raw/Services adapters remain unimported. Whole readers,
Player/card/game owners, Controller searches/disposal, the 41 KB Enemy opcode
root and whole-game link/runtime remain open.

Private evidence includes `core074-audit.py`, `core074-defs.json`,
`core074-support.json`, the independent RTTI/native storage exports and all
failed SDL/search/factory probe sources and reports. Canonical replay snapshots
are stored compressed from the outset. Completed configuration and registration
writers must never be rerun.

## Verified checkpoint

The frozen graph strictly passes all 562 units across 103 fresh objects,
covering 98,392 disjoint comparison bytes. Origins remain 489 pending /9 library
/64 authored, with 16,948 authored bytes unchanged. All 6,945 reference reviews
remain terminal and 177 absorbed; the multi-target Controller association
remains nonexact. All 45 public tests pass, including the final guarded
construction checks. Protected cleanup retires 20 completed probe products,
preserves all 206 canonical hashes and verifies the current graph with existing
objects. No unchanged cold rebuild is required for documentation or cleanup.
