# CORE/EXACT-347 — entire native 332-byte Player bullet-graze feedback boss

The user-approved Japanese TH20 v1.00a Steamless original is immutable,
whole-file SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its *complete game-owned* `Player::record_bullet_graze` at
`0x004F8B90..0x004F8CDB` is **332 original bytes / 105 original i386
instructions**. The complete native interval SHA-256 is
`daaa17e5829c58846d3ef079592757a572e03ded5e36d82a3af165cde1f44a31`.
The entire function now has **strict canonical exact** C++20 source in
`src/PlayerGrazeFeedback.cpp`. Its original real caller includes the
separately exact 2,018-byte `Bullet::process_collision` at `0x00484A20`,
not a synthetic harness or a shortened prefix.

## Original, independently decoded behavior

In native order, the method:

1. Obtains the real `PlayerRecord` from its live `Context`, increments
   its actual `field_e4` using the native `PlayerRecord::add_field_e4(1)`
   call at `0x004FE8D0` (whose separate implementation clamps the result
   through the original `std::clamp<int>`); it does not bypass that setter.
2. Constructs an actual `EffectParameters` value, copies the three floats
   of the incoming original `Vector3`, assigns the input packed color with
   the native `PackedColor` operator, then sets the **fourth byte / Alpha**
   of that four-byte value to `0xFF`. The color write is a real byte alias,
   using `std::uint8_t*` byte-pointer arithmetic by three bytes, not a
   non-native array-index multiply or a fabricated color object.
3. Obtains the real `EffectInfo` from `Context`, advances the global
   original `GameRandom` state at `0x005BA4A8`, takes the **unsigned** result
   modulo four, and submits the original effect through
   `EffectInfo::queue_effect(style,4,effect,0)` at `0x0049DC60`.
   The effect queue's separate implementation and runtime lifetime are
   **not** newly claimed strict exact here.
4. Gets original `WeaponStoneInfo(0)`, observes the live StoneEnemy
   controller's byte at `+0xB0` and selects damage amount **1500 or 1000**
   in the native branch order, then calls `WeaponStoneInfo::record_damage`
   with the actual input location and kind 13.
5. Queries the real `EnemyController(0)` predicate at `0x0049BE20` and
   chooses **50 or 10** reward. Stores the actual chosen reward before
   the separately native `player_record(0)` lookup, then invokes its real
   `add_field_44` member, preserving side effect and signed argument ABI.
6. Requests effect **42** from the original global Sound system at
   `0x005BA830`, passing the actual X coordinate as `float`, and returns
   with the full native `ret 8`. The original stack security cookie is
   preserved, including the final native check at `0x005429EE`.

The three previously private, unverified ABI hypotheses were **not simply
accepted from old documents**. The original callee contexts and whole
original x86 calls were re-examined for `PlayerRecord::add_field_e4`,
`EffectInfo::queue_effect` and `EnemyController::graze_reward_active`.
The maintained headers now expose narrow native member interfaces without
fabricated object storage or changing any original class layout. The
separate callee bodies are independent future work; the whole 332-byte
caller's actual code is the function accepted here.

## Complete original relocation proof

A fresh, independent decode of the **unmodified original PE** found **17
native `E8 / REL32` calls** plus **three `HIGHLOW / DIR32` fields** in the
original `.reloc` table. All **20 original offsets, types, and targets**
match the canonical MSVC COFF function's real relocations, including:

| Original call/field offset | Original target | Native relationship |
| --- | --- | --- |
| `+0x07` DIR32 | `0x005B25C0` | compiler `__security_cookie` |
| `+0x2A` REL32 | `0x004FE8D0` | actual PlayerRecord `field_e4` increment |
| `+0x6D` DIR32 | `0x005BA4A8` | original bullet random state |
| `+0x72` REL32 | `0x00423EE0` | original GameRandom advance |
| `+0x92` REL32 | `0x0049DC60` | actual EffectInfo queue operation |
| `+0xE7` REL32 | `0x0049BE20` | EnemyController graze reward predicate |
| `+0x132` DIR32 | `0x005BA830` | original SoundInf global |
| `+0x142` REL32 | `0x005429EE` | compiler security-cookie check |

All twenty original reference field offsets/targets and compiler symbols
are retained in the ignored source of truth
`.analysis/core346-graze-native-independent-refs.json`, created from
original E8 operands and PE `.reloc` **before** writing the canonical
manifest. The other 12 references are in the same independently decoded
list. The entire 332-byte function has **252 nonrelocation bytes and 80
relocated bytes**, all accepted by strict whole-function replay.

## Natural C++ statement ownership, not inserted padding

A previous 332-byte private candidate matched only 100/105 original
instruction kinds. Revisiting the original MSVC `/Od` side effects
resolved the root causes naturally:

- Modifying Alpha via actual byte-pointer addition, rather than an indexed
  byte array expression, removes two unobserved register/multiply
  instructions while preserving the true original `byte ptr` write.
- The selected **reward amount is saved before the native PlayerRecord
  lookup**, preserving both its value and original evaluation order.
- Three real, side-effecting operations (record increment, effect enqueue,
  and reward update) each occur in their own natural C++ lexical scope.
  With the locked compiler, these scopes naturally emit the original
  three one-byte NOPs at `+0x2E`, `+0x96`, and `+0x121`.

No arbitrary NOP, inline assembly, synthetic return, compiler-only dead
local, fake memory layout or shortened native comparison was used.
The ordinary maintained function compiles to **332/332 exact original
bytes, all 105 original x86 instructions, and all 20 independently attested
original relocations**. The canonical unit `player_record_bullet_graze` uses
locked MSVC 19.44.35211 i386 `/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` and has a fresh object/receipt.

## Actual affected-only replay

Three real member interfaces were added to `src/PlayerRecord.hpp`,
`src/ItemResourceOwners.hpp` and `src/EnemyController.hpp`, without
changing object sizes or offsets. The **previous canonical compiler
receipt include closures** identified **41 existing source providers with
306 existing exact units**; the newly maintained 332-byte whole method adds
one source provider/unit. Exactly **307/307 strict units in 42 freshly
rebuilt objects** passed nine serialized, low-priority batches of
**19+39+21+22+37+47+27+66+29** units. This includes the previously exact
2,018-byte Bullet collision and the large Player/Enemy/Item roots.
There was **no whole-graph cold replay**.

Twenty-two *MSVC compiler-private* `$SG` label identities in eighteen
old units renumbered in the fresh header closure. Every change retained
the original independently observed native string address, original
relocation offset/type and nonrelocation bytes and was re-accepted by
the unchanged strict whole-function comparator. Private audit:
`.analysis/core347-reconciled-private-symbols.json`.
Private scope source map: `.analysis/core347-graze-affected-preedit.json`
and `.analysis/core347-graze-replay-groups.json`; strict results:
`.analysis/core347-graze-replay-batch0.log` through `batch8.log`.

The original game's whole linker startup, GameRandom/EffectInfo runtime
lifetimes, and other large Player/Bullet/Enemy roots remain independent
open tasks. This proof accepts **one entire native function**, not
whole-game behavioral equivalence.

## CORE/EXACT-348 later callee closure

The independent whole **87-byte** `PlayerRecord::add_field_e4` callee
at `0x004FE8D0` is now also **strict native exact**. The entire game-owned
332-byte caller and the separate graze counter are credited at their two
nonoverlapping original boundaries. See the
[complete original counter proof](PLAYER_GRAZE_COUNTER_ADD_EXACT_RECONSTRUCTION.md).
The original EffectInfo queue operation and EnemyController predicate remain
separately open; the graze caller's exact status does not close them.

## Later CORE/EXACT-352 callee acceptance

The separate complete **143-byte** EffectInfo scheduled request queue at
`0x0049DC60` is now also strict native exact, with its real `void`
return ABI, original 1024/72-byte queue shape, and corrected policy and
delay request fields. The earlier description of this callee as unaccepted
is superseded. Read the independent
[143-byte queue proof](EFFECT_REQUEST_QUEUE_143_EXACT_RECONSTRUCTION.md).
The 332-byte Player graze caller was recompiled with the corrected `void`
relocation symbol and remains 332/332 strict exact.
