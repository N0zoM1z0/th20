# CORE/EXACT-256 — exact 255-byte Vector2 geometry chain and complete 1,404-byte Bullet command11 boss frontier

The immutable Japanese TH20 v1.00a Steamless PE is the source of truth,
whole-file SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Independent disassembly/decompilation and locked-MSVC x86 codegen now
establish **three complete native Bullet geometry methods**, not only
extracted basic blocks of the parent.

| Entire original method | Native start | Native bytes | Original relocations | Strict canonical replay |
| --- | --- | ---: | ---: | ---: |
| `th20::cross_components(const Vector2&, const Vector2&)` | `0x00480D30` | **50** | 0 | **50/50** |
| `th20::dot_components(const Vector2&, const Vector2&)` | `0x00480D70` | **50** | 0 | **50/50** |
| `th20::normalize_vector2(Vector2&, const Vector2&)` | `0x0043E910` | **155** | 3 | **155/155** |

Total **255 entire original game-owned bytes**, all three original
relocation offsets/types/targets, two new source providers: `src/BulletRayMath.cpp` for the 50B
products and `src/BulletCommand11Geometry.cpp` for 155B normalization;
separate narrow headers do not alter older exact source inputs. Both 50B functions return the original
MSVC x87 `float` via ST0 after normal C++20 scalar evaluation and the
native stack result local; they use the real existing `Vector2` x/y
member layout, **not** a fabricated byte-array argument.

Original whole-interval SHA-256 values, in table order:
`ec06860850a5738e04f27b1cf73cfc113e5e94b4f9970c048872e97135aa2e7e`,
`98db99c0c1f9e2ac024aad66ba6631a330a51749fba6cac5ceb670eb2616f7c5`,
`ebc6623dad35a9e70638648612f5017cde9857f2553949a489d8910251301d80`.

## Original 155B conditional normalization semantics

The actual `normalize_vector2` calculates the two-lane squared magnitude,
passes it through already reconstructed `scalar_math::square_root` at
`0x00446B30`, converts to the original x87-returned float and invokes
`geometry::absolute` at `0x00445680`. The native constant at
**`0x0056E1A0`** is **0.01f** (`0x3C23D70A`). If absolute magnitude
is less than that epsilon, it copies **both** input lanes to output.
Otherwise it divides input X and Y independently by the original
magnitude. The same input and output pointer may alias, as observed at
all four native command11 call sites. Complete original relocations:
`+0x2F REL32 -> 0x00446B30`,
`+0x45 REL32 -> 0x00445680`, and
`+0x53 DIR32 -> 0x0056E1A0`. All 143 non-relocation bytes plus these
three original relocated words match in canonical replay.

The source is ordinary C++20 using the already maintained
`scalar_math::square_root`, `geometry::absolute` and actual 8-byte
`Vector2`. Independent original math and MSVC codegen corroborate these
C++ contracts. The names are inferred but all complete original native
return paths/branches and addresses are fixed. Locked compiler profile:
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc`, invoked with reduced scheduling priority.
Canonical evidence:
`.analysis/core257-integrated-command11-geometry-replay.log`:
**3/3 complete strict native units, two cold objects**. No previously
accepted source/header, native relocation or compilation profile changed;
there are **zero older replay-affected units** and **no unfiltered cold
replay**.

## Independent complete 1,404-byte command11 boss investigation

The entire original game-authored `Bullet` command-11 method at
**`0x00481200..0x0048177B`** is **1,404 bytes / 357 x86 instructions**,
whole native SHA-256
`48a4da455a231997829ed66a57a9604d32988b2d8eb604749a935da80f94f546`.
It is a direct original callee of the **1,846-byte** Bullet physics
update boss `0x00485B60` and remains a separate **nonexact complete
parent**, despite its three now exact geometry children. Its original
behavior decrements the genuine `commands.at(11).timer`, checks the
original nonzero command count, then tests sprite-extent-adjusted
out-of-screen state through already exact `bullet_wrap_outside`
(`0x004854D0`) and original typed `Animation::sprite_data`.

Within the outer branch it constructs two *real 8-byte Vector2 values*,
a normalized direction computed from the current Bullet Angle, and
two separate arrays of four floats each. Four original corner vectors
are derived from the independently verified gamefield **-384/+384** and
**-448/+448** constants with sprite extents and the 2.0f divisor.
Each corner is normalized by the entire newly exact 155B method;
its **four cross and four dot products** now have their genuine complete
50B callees. The original compiler stores their x87 ST0 float results
in parallel 4-element arrays. Two distinct native loops choose the
furthest forward projection in the crossing-negative and crossing-positive
sets; native sentinel values are **-999.0f** at `0x0056FD7C`, terminal
threshold **-998.0f** at `0x0056FD78`, and zero at `0x0056E0E8`.
When either best candidate fails the threshold, the original clears
Bullet command flag `0x100` and returns one. Its other final path
calls `Timer::at_most(0)` and conditionally clears the same flag.

A full-length and all-branch natural C++ candidate, retained only
privately as `.analysis/core255-BulletCommand11.cpp`, compiled to
**1,399B**. Correctly modeling the two *independent four-float arrays*
and natural `if/return` Timer result control flow (rather than a single
8-float array and a cached bool local) produced another complete candidate
of **1,398B with 351/357 original instruction mnemonics aligned** at
`.analysis/core255-BulletCommand11-splitarrays.cpp`. **Neither is
native-exact**: the original `polar` XY direction argument evaluation
pushes a float before the native Angle x87 getter and forwards ST0
directly, whereas the candidate spills/reloads two float temporaries.
There are also two actual original float stores at native offsets
`+0x105..+0x11E` into local frame slots -0x78/-0x7C containing 384.0f
and 448.0f whose source-level ownership is not yet explained.
Their early stores were checked against the *whole* original disassembly,
not fabricated as useless padding. Importing a fake local solely to
force matching bytes would violate the exactness rules. The current
production source deliberately **does not admit the 1,404B parent**,
no provisional code is placed under `src/`, and **zero** of its parent
bytes are credited.

The original **1,846B** Bullet physics, **2,018B** collision,
**3,735B** single-shot emitter, **12,140B** Bullet update and
**41,967B** Enemy opcode dispatcher remain nonexact. The full
command11-specific native disassembly and whole-function compiler trials
stay under ignored `.analysis/core255-*` and `build/core255-probes/`.
