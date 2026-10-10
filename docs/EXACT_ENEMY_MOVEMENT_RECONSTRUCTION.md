# Enemy movement composition and nonthrowing construction

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-061 follow-up: the previously pending whole movement update and its
Graphics/viewport/configuration/Context/AnimationFile owners now strictly replay.
See [whole movement update evidence](EXACT_ENEMY_UPDATE_RECONSTRUCTION.md).
This document records the historical EXACT-059 boundary.

EXACT-059 adds nine complete functions: 1,285 instruction bytes and ten compiler
alignment bytes. All 417 units / 78 cold objects / 76,932 disjoint comparison
bytes strictly replay. New origins remain pending; authored totals remain
64 functions / 16,948 instruction bytes. This batch closes a shared protocol
used throughout the Enemy movement opcodes; the entire 41 KB opcode dispatcher
remains pending and its cases receive no separate exact credit.

## Complete contributions

| Address | Instruction bytes | Compared bytes | Operation |
| --- | ---: | ---: | --- |
| 004A7DA0 | 844 | 844 | EnemyState movement composition and bounds |
| 00499390 | 17 | 17 | Motion Y getter |
| 0049C7E0 | 26 | 26 | Motion Y setter |
| 0047A560 | 78 | 83 | Nonthrowing normalized angle assignment |
| 0047A5C0 | 26 | 26 | Motion speed assignment |
| 0047A500 | 26 | 26 | Select linear mode |
| 0047A4C0 | 29 | 29 | Select orbit mode |
| 0049C470 | 29 | 29 | Select elliptic mode |
| 004A33C0 | 210 | 215 | Nonthrowing Enemy construction |

The maintained bodies use existing EnemyState752, Enemy0x428, Motion72,
EnemyMovement388 and actual PMR vector storage. No packing overrides, alternate
exact source, artificial locals or copied decompiler bodies are used.
EnemyState.cpp retains its existing precise-FP/GS/SDL recipe. Enemy.cpp and
MotionConfiguration.cpp use the same recipe plus EHsc. These are local matching
recipes, not evidence of a globally recovered game build configuration or
original translation-unit partition.

Motion X accessors independently reproduce complete native bodies 4292E0/16
and 4292A0/25. These physical heads already belong to the accepted ClockScalar
getter/setter comparisons; logical Motion aliases do not add overlapping units,
mapped functions or duplicate bytes.

## Composition and bounds

The complete 219-instruction body sums all record positions into a local Vector3,
subtracts the previous combined position, writes that displacement to the
combined Motion's vector and invokes its accepted position update. State flag
word +2CC bit 1 enables rectangular bounds. X and Y independently clamp against
the center minus/plus half width or height; Z is untouched by the bounds.

When bounds are enabled, the resulting combined position is copied, positions
of all records after record zero are subtracted, and record zero receives the
remainder. This preserves the other components while making their sum equal to
the bounded result. Redistribution occurs even if no coordinate needed a clamp.
The native operation requires a nonempty vector in this branch. Initialization
establishes record zero; no invented empty-container recovery is added.

Position update retains its existing motion-mode, frozen and floor-to-hundredths
behavior. Freezing the combined Motion skips that update, but composition still
records displacement and the following bounds/redistribution still execute.
Composition does not advance individual movement interpolation timers or their
velocity updates. The ordered float comparisons do not clamp a NaN coordinate.

Native calls and actual record stride independently establish PMR unchecked
begin/end at 414F30/414F70 and indexed access at 48BD10, whose complete body
multiplies the index by 388. Existing accepted vector arithmetic, Motion methods,
security cookie/check and the established 2.0f constant provide the remaining
anchors. Every relocation is replayed from these definitions; structural
comparison's solved diagnostic destinations are not used as anchor evidence.

Two rejected complete probes are retained privately: evaluating the lower-bound
arithmetic before the getter emitted 870 bytes; caching a separate first-record
reference emitted 850. The accepted source keeps getter-first comparisons and
directly accesses record zero through its actual container reference. It emits
the entire 844-byte contribution. No prefix, branch fragment or shortened
comparison was accepted.

## Native nonthrowing contracts

The original angle setter registers handler 567600; Enemy construction registers
567750. Ghidra's inferred function ownership does not contain these thunk heads,
so the independently attested PE supplies their complete 29-byte decode.
Both point to the previously independently audited 36-byte FuncInfo at 5A91B8:

`magic=19930522; maxState=0; unwindMap=0; tryBlocks=0; tryMap=0; ipCount=0; ipMap=0; exceptionSpec=0; flags=5`.

The natural `noexcept` compiler experiment produces identical complete metadata
and handlers, including their distinct frame-cookie offsets. This closes the
previous 168/native210 Enemy constructor gap without changing child constructor
or destructor contracts. Each EH-bearing COFF function contributes five trailing
INT3 alignment bytes; native padding matches all five. Manifests compare complete
83/215-byte contributions while retaining 78/210 instruction-byte sizes.
Both handlers and both metadata contributions also pass complete canonical
replay as supporting evidence, without extra function/byte credit.

Enemy construction invokes its real EclManager base, stores its derived vptr,
zeroes flags, constructs a controller link pointing to the Enemy, State, spawn
parameters, child sentinel/list and detached parent link, constructs the empty
callback and clears player index and Context. Independent Enemy destruction's
vptr store corroborates the table at 5703CC; its six native slots include the
accepted dispatcher wrapper. Full vtable/RTTI reconstruction is not claimed.
Native base/list/std::function definitions and existing child body evidence
establish constructor call identities. The list constructor remains a documented
natural nonexact child implementation; accepting the enclosing call does not
promote its body or establish whole-game linkage.

## Verification and next core work

Owned C++20/O2/UBSan tests execute actual composition with multiple independent
components, both bound sides, repeated redistribution, preserved nonfirst
records/timers, frozen combined state and NaN coordinates. They check mode
selection preserves all high flag bits, X signed zero, independent Y/Z/speed
storage, normalized angle assignment and declared nonthrowing contracts.
The existing counting-resource tests still verify complete State ownership release.
Enemy construction's machine body and EH are audited, but its production base,
destructor/resolvers and full linkage remain undefined; public tests do not
substitute a constructed whole Enemy or claim native allocation-failure behavior.

The next movement root is 4A7710/1,675 bytes. Its entire body is now reviewed:
previous-motion snapshot, conditional position lookup, scalar/vector/
position interpolation, velocity/position updates, global offset, composition,
direction-dependent animation replacement, animation-derived extents and
off-screen retirement flags. It calls actual animation resolution, loader/context
and global-motion owners that remain unimplemented. The 4A8260/1,258-byte body
is the animation update, not the movement update; its complete twenty-byte switch
table and real animation lifetime also remain pending.

The complete Enemy dispatcher remains 48C010/41,967 instruction bytes with both
native tables. Its 49 movement opcode indices are reviewed together with this
protocol. The original missing-argument comparison uses double -999999.0, and
argument evaluation order, mirrored angle handling, interpolation contracts,
shared temporary lifetimes and actual parent/controller interfaces must be
preserved when reconstructing the whole root. No partial switch or defaulted
unrecovered case is presented as exact source.
