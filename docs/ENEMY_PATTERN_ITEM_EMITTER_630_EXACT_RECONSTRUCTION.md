# CORE/EXACT-386 — entire original 630-byte EnemyPattern item emitter boss

Comparison original: immutable Japanese TH20 v1.00a Steamless
`resources/th20.exe`, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The whole game-owned `EnemyPattern::emit_items(const Vector3&)` at
`0x004A5350..0x004A55C5` is **630 native bytes / 178 original x86
instructions**, whole-original SHA-256
`0601284c4f569d9114a482d92e3b050bfaa27301881d304653d154eefb755fb6`.
The maintained C++ is `src/ItemSpawn.cpp`; complete native exact unit
`enemy_pattern_emit_items` is **630/630 bytes**, not a prefix match.

## Entire original gameplay scatter loop

The function constructs a live Vector3 output, draws an initial angle from
the real global `script_random` at `0x005BA4A8`, then scans fifteen of
the sixteen actual `EnemyPattern` item-count records. A nonzero duration,
real Timer less-than predicate and positive extra-count enable the
time-adjusted item count:

`count += extra_counts[i] -
 signed_low32(extra_counts[i] * timer.current) / signed(duration)`

The original multiplication retains 32-bit modular overflow; its native
signed `idiv` truncates toward zero. Each positive item count generates
elliptical polar XY from real radius fields, multiplies by a fresh uniform
random sample in [0.5,1], clears Z, adds the borrowed origin and calls
the genuine player's `ItemInf::spawn` with original kind, color, angle,
speed, delay, extra and sound. It advances the angle after *every*
spawn, including the last, with a new random sample and the
independently exact `normalize_angle` function. After all fifteen kinds,
it clears **all sixteen** stored counts, preserving extra counts, Timer,
radii, origin and bomb-kind state. Undefined native integer IDIV
overflow, exhausted pools and invalid resource lifetimes are not
claimed safe by byte identity.

## Natural two-byte machine-code closure, not fake NOP padding

The earlier complete whole source compiled to **628 bytes / 177
instructions**. Its sole missing native instruction was
`mov edx,esi` at original `+0xDC`. The prior expression multiplies
the Timer-derived value first, leaving MSVC to execute
`imul esi,dword ptr[eax]` and destroy an earlier live value.
The corrected real C++ expression evaluates the positive
`extra_counts[i]` *first*:
`extra_counts[i] * static_cast<std::uint32_t>(
 static_cast<std::int32_t>(timer))`.
Both spellings have the same 32-bit modular arithmetic, but with the
original operand order, pinned MSVC naturally preserves ESI and
emits `mov edx,esi; imul edx,dword ptr[eax]`. The entire
source now emits exactly **630 bytes / 178 original instructions**;
no inert spill variables, manual assembly, instruction padding,
synthetic return or truncated comparison were used.
Private experiments are in `.analysis/core385-item-imul-variants.py`;
the winning full compiled source is
`.analysis/core385-u32-source-first.cpp`.

## Independent original PE relocation proof

From the *unmodified* original PE, a fresh complete Capstone x86
decode found **18 original E8/REL32 call fields**; an independent
PE `.reloc` audit found **12 original HIGHLOW/DIR32 fields**.
All **30 original byte offsets, types, and actual native
callee/constant destinations** agree with the new 630-byte COFF
candidate. Twenty-eight targets were also corroborated from
separately accepted canonical native-relocation evidence; the two
remaining targets were read directly from immutable original PE
operands, not inferred from the candidate.

The original targets include global `script_random`
`0x005BA4A8`, true array index `0x00414580`,
`GameRandom::radians` and `::unit`, Timer methods,
`ellipse_polar` `0x00459190`, `ItemInf::spawn` `0x004C3C90`,
`normalize_angle` `0x00438540`, full 16-slot array
reset `0x004981F0`, compiler security-cookie check
`0x005429EE`, and native float constants. Their exact offsets and
symbols, original SHA and PE evidence are preserved in
`.analysis/core386-emit-independent-native-refs.json`.
The locked MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:strict /sdl /EHsc` profile emits
**510/510 nonrelocation bytes and 120/120 relocated bytes**.

## Focused replay, physical ownership and limits

Only the real `src/ItemSpawn.cpp` C++ expression changed, not
any shared header, class member, profile or other canonical source
provider. The preexisting exact
`ItemInf::spawn` **1,576 bytes** and
`EnemyPattern::drop` **239 bytes** share this source owner.
A filtered **single-source cold replay** passes **3/3
strict units in one object**:
**1,576/1,576, 239/239 and new 630/630**.
This complete Enemy item spawn/caller/emitter original chain
covers **2,445 nonoverlapping game-owned physical bytes**;
only the 630B emitter is newly admitted in this checkpoint.
Original authored provenance for the full item emitter already
existed in the ledger and was not double counted.
Focused full log: `.analysis/core386-item-spawn-replay.log`.
No all-repository cold replay, whole-game binary linkage claim
or assertion that the separate 41,967-byte Enemy ECL dispatcher
is exact.
