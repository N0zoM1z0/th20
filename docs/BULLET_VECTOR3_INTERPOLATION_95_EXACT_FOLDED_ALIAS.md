# CORE/EXACT-730 — three original Bullet Vector3 interpolation setters, 95 distinct game-exact native bytes

**Three physical original TH20 game functions used by the whole 12,140B Bullet command Boss are now independently established as full native strict exact, totaling 95 disjoint game-owned code bytes.** Only **two NEW strict canonical units** are necessary: the original 35-byte set_start target was already a whole exact Motion::set_position physical native unit whose genuinely distinct typed VectorInterpolation::set_start source emits the same entire 35 machine-code bytes. This is a correct original-code identity/fold-compatible alias, not two credits for one physical function.

Original Japanese TH20 v1.00a Steamless target: resources/th20.exe, immutable SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Immutable whole native methods, real source types and physical callers

| Game-authored original physical method role | Native original head | Whole code | Existing/new strictly exact canonical binding |
| --- | --- | ---: | --- |
| VectorInterpolation::set_start / fold-compatible Motion::set_position | 0x004393F0 | **35B / 15 x86** | Existing motion_set_position, real original 35/35 |
| Interpolation<Vector3>::set_end | 0x00438A90 | **38B / 16 x86** | **NEW vector3_interpolation_set_end, 38/38** |
| Interpolation<Vector3>::set_duration | 0x00438E70 | **22B / 10 x86** | **NEW vector3_interpolation_set_duration, 22/22** |
| **Three distinct original physical code intervals** | | **95B** | **Two new canonical units; one existing exact** |

All three original code intervals were freshly read and decoded through their complete original RET/RET4 instructions, and all three original bodies are **byte-for-byte identical** to the real pinned MSVC i386 generated whole-method COMDAT bodies. All three have zero original PE HIGHLOW and zero direct E8 fields inside their own bodies, with the original 35/38/22 byte lengths. Their physical code intervals are mutually disjoint and overlap none of the **546** already credited original game-function intervals.

The original original 12,140-byte / 2,490-x86 Bullet::run_extended_commands command root physically calls all three with the **same genuine Bullet+0x420 receiver**, the real 84-byte VectorInterpolation owner, and the corresponding original command/position arguments:

- **0x00480386 to 0x004393F0:** native Bullet+0x420 Vector3 interpolation start value receives actual Bullet+0x64 position. The original 35B body assigns three 32-bit components to offsets +0,+4,+8.
- **0x004803C5 to 0x00438A90:** same native receiver, and a real command vector argument, assigning all three 32-bit components at interpolation offsets +0xC,+0x10,+0x14.
- **0x0048042F to 0x00438E70:** same receiver, genuine duration integer argument, writing interpolation duration at **+0x4C**, consistent with the separately asserted real VectorInterpolation layout.

These are original PE relative E8 destinations read from whole actual native code, not a claim that the enclosing 12,140B command root is strictly exact. That much larger parent still has no complete maintained C++ function and is **NONEXACT**.

## Independently type-correct original 35B shared-head alias, no duplicate credit

The existing maintained real Motion::set_position(const Vector3&) implementation in src/Motion.cpp naturally produces the complete original **35/35B physical code at 0x004393F0**, already accepted as canonical unit motion_set_position.

The independently maintained generic C++ template in src/Interpolation.cpp also naturally compiles **Interpolation<Vector3>::set_start(const Vector3&)** to the **same complete 35 original native bytes** with no relocation fields. The symbol names are genuinely different and typed, while the original 35B code is physically identical. Importantly, the original separately already exact **637B Bullet::advance_command8** at 0x004827E0 physically E8-calls this original head at **0x0048293F**, and its own freshly built real COFF relocation at the exact same native field names the correct VectorInterpolation::set_start typed template symbol. Additional original exact Motion/Enemy callers physically use the same head.

This is strong fold-compatible game source provenance and dataflow evidence. It does **not** establish historical linker ICF settings, nor entitle a second source alias to another full physical native code interval. **The one existing motion_set_position canonical unit is retained; no duplicate vector3_interpolation_set_start unit was added.** The 35B original body is now newly accepted once as a game-owned function, while the typed interpolation alias is separately documented.

Likewise, the real Interpolation<IntegerTriple>::set_end(const IntegerTriple&) C++ template happens to emit the **same 38-byte complete machine-code body** as Interpolation<Vector3>::set_end. The original Bullet+0x420 receiver proves the Vector3 source role for the 0x004803C5 site, but no second 38B physical code credit is claimed for an alternative folded-compatible template spelling.

## The real existing C++ source and strictly bounded native replay

These methods required no new invented C++ code and no changes to the already natural interpolation algorithm. The maintained real src/Interpolation.cpp has typed set_start, set_end and set_duration definitions on the actual templated Interpolation<T> with a genuine explicit Vector3 instantiation; src/Interpolation.hpp already declares these methods. The original game object layout has correct start, end and duration offsets and is compiled under existing pinned MSVC 19.44 i386 profile:

    /nologo /c /std:c++20 /Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise

Two newly tracked strict match units use the **existing single native Interpolation.cpp/Interpolation.obj canonical source provider**, without changing any C++ source, header, compiler profile, existing function mapping, or original physical relocation target:

- vector3_interpolation_set_end: 0x00438A90, 38B, 0 original relocations.
- vector3_interpolation_set_duration: 0x00438E70, 22B, 0 original relocations.

**Only this source provider was freshly cold rebuilt and replayed: 43/43 complete strict native units, one object**, preserving all 41 existing exact interpolation units. The separately older exact Motion.cpp provider had its stale receipt handled by a **13/13 native strict source-only cold replay**, and the genuine 637B Bullet Command 8 typed caller had its stale receipt handled by a **1/1 strict source-only cold replay**. No global/unfiltered cold replay or whole-project linking was done.

Private reproducible original PE/source evidence:
- .analysis/core730-bullet-vector-interpolation-original-native-proof.py/json — independent complete three 35/38/22B original native bodies, pure C++ compilation, genuine Bullet+0x420 original caller E8 sites, typed 637B Bullet command-8 native/COFF alias, original 35B Motion/VectorInterpolation code equality, IntegerTriple alternative folded-compatible source, complete physical nonoverlap.
- Existing complete canonical motion_set_position 35/35, new vector3_interpolation_set_end 38/38 and new vector3_interpolation_set_duration 22/22.
- Prior [34+8+11 Bullet original three-switch native CFG](BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md) — actual game owner/source analysis, not yet whole original native exact.

## Conservative accounting and status

The physical original game code admission adds exactly **three** distinct whole authored original functions, **35+38+22 = 95 new game bytes**, to the previous **546 / 186,351** baseline, yielding **549 whole game-authored native exact functions / 186,446 disjoint original .text bytes**. The canonical strict-unit graph increases by only **two** new strict units (1,187 -> 1,189) because the 35B physical head already had a canonical exact unit, even though its game-authored origin remained uncredited.

The 3,111B Player main, 555B Player movement, 12,140B Bullet command sequencer and 41,967B Enemy opcode root remain original source-present/non-source-present as previously tracked and **NONEXACT**. The complete original 72B Player direction .rdata game data, reconstructed separately, is **not** included in game-authored .text byte totals.
