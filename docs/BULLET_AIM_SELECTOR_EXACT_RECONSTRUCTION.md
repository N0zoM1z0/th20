# CORE/EXACT-294 — complete native 434-byte Bullet aim direction selector

The original Japanese TH20 v1.00a Steamless PE is the immutable source of
truth, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
A previously unclassified **434-byte complete game function** at
`0x00485740..0x004858F1` is now reconstructed as the normal C++20
`th20::select_bullet_aim(view_index, fixed_angle, position,
direction_code, deviation)` with actual game-typed `Vector3`, `Player`,
`EnemyController`, `Enemy`, `GameRandom` and geometry methods.

**Whole canonical strict result: 434/434 original bytes, 109/109 original
x86 instruction kinds and order, 346/346 non-relocation bytes, and all
22 original relocation fields matched.** Original function SHA-256:
`46030fba1f1d7e81891603a8dc0c5b3cd61edae630c1dc6862e2dcf770195bc5`.
No partial prefix, assembled game bytes, artificial padding, fake owner
prefix or dummy locals were admitted. Native symbol spelling is inferred;
its complete original semantics, code extent, ABI and original targets
were independently corroborated against full native Capstone disassembly
and the original Ghidra decompilation.

## Whole direction-selection gameplay protocol

Native direction codes are floating-point sentinel values, **not** integer
enum indices. Seven real immutable original-PE float anchors are separately
read from the original `.rdata` section:

| Original native address | Real float | Meaning / use |
| --- | ---: | --- |
| `0x0056FD80` | -999990.0f | Default/fixed-direction lower sentinel and optional deviation reset |
| `0x0056FD54` | 999990.0f | Start player aiming band |
| `0x0056FD58` | 1999990.0f | End player aiming band |
| `0x0056FD5C` | 2999990.0f | Start player aiming with random angular deviation |
| `0x0056FD60` | 3999990.0f | End player-deviation band / start random-fixed band |
| `0x0056FD64` | 4999990.0f | End random-fixed band / start selected-Enemy aiming |
| `0x0056E0F0` | 3.141592741f | Actual native `pi` substituted when deviation is at/below sentinel |

The full native method returns a float through its actual 32-bit x87 `ST0`
return ABI. If the deviation is no greater than the sentinel, it first
uses original `pi`. The complete selector then evaluates the actual
floating-point conditions, respecting the original comparisons and
NaN behavior:

- At or below the lower direction sentinel: return the incoming fixed
  direction unchanged.
- From 999990 inclusive to 1999990 exclusive: compute the **actual**
  `player(view_index)->direction_to(position) + deviation`.
- From 2999990 inclusive to 3999990 exclusive: compute that player
  direction plus `process_bullet_random.signed_unit() * deviation`.
- From 3999990 inclusive to 4999990 exclusive: use
  `process_bullet_random.signed_unit() * deviation + fixed_angle`.
- From 4999990 onward: use the original
  `geometry::direction_xy(position,
  enemy_controller(view_index)->selected(0)->position_ref())`.
- Other in-range selector values retain the incoming literal floating
  direction. The actual source is a nested conditional expression, not
  a copied switch/array of original branch bytes.

The **109** native instructions include distinct nested result
publication paths and original x87-to-SSE materialization. A first
full C++20 candidate with a plausible nested `if` tree emitted **413B
and only 53/109 native instruction kinds in order**. The original
MSVC `/Od` codegen is instead recovered by expressing the same gameplay
as meaningful chained `?:` conditionals with default-angle case first.
That whole natural function emits exactly **434B**, the full native
109-instruction sequence and all intermediate SSE result copies, with
no inert local introduced to force byte equality.

## Independently verified 22 native call/data relocation sites

The complete original PE was disassembled as 109 x86 instructions. Every
candidate COFF relocation offset was independently matched to its
**native original instruction operand**: 7 distinct original data
constants (some referenced twice), two original process global random
uses at `0x005BA4A8`, and original exact callee address identities:
`player(view_index)` `0x00460830`, `Player::direction_to` `0x004FF350`,
`GameRandom::signed_unit` `0x004298E0`, `enemy_controller(view_index)`
`0x00478060`, `EnemyController::selected` `0x00485660`,
`Enemy::position_ref` `0x0047A2C0`, and
`geometry::direction_xy` `0x0047A2E0`.
Each relocated original DWORD and any REL32 displacement were validated
*from the original disassembly*, not copied from the comparison solver.
Original exact offsets, COFF relocation types and fixed native targets
are bound in `[units.bullet_aim_selector]` of
`config/match-units.toml`. The independent private evidence is
`.analysis/core294-bullet-aim-original-native-22-relocations.json` and
`.analysis/core294-bullet-aim-attestation.log`.

The locked MSVC 19.44 x86 build profile is
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` at reduced scheduling priority. Fresh canonical strict replay
in `.analysis/core294-bullet-aim-canonical-replay.log`:
**`bullet_aim_selector: exact (434/434 bytes)`**.

## Scoped regression and remaining original large functions

This batch adds only one new source `src/BulletAimSelector.cpp`, its
previously nonexistent isolated header `src/BulletAimSelector.hpp`,
tracking and English documentation. **No previous exact source,
shared header, compile profile, native data or existing manifest unit
changes**, hence the actual existing source-include receipt closure is
**zero old source objects / zero old exact units**. Exactly **one newly
introduced complete native unit** was compiled and strictly replayed
(1/1 in one fresh object). No unfiltered full cold replay occurred.

The complete 1,404B Bullet command 11, 273B group drawing, 3,735B
shot emitter, 12,140B Bullet command root and 41,967B Enemy opcode
root remain independently nonexact. This exact original aim mode boss
is a real dependency, not claimed proof for any of those entire parents
or whole-game runtime/linker completeness.
