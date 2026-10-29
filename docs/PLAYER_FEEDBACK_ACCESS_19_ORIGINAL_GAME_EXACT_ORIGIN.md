# CORE/ORIGIN-676 — original 19B PlayerFeedback accessor: full game-owned source and strict exact

**One independent, previously existing 19-byte strict native unit is now admitted as a game-authored physical original function.** This is an origin review of a function already implemented and strictly matched, not a source change or a second physical byte credit for a folded helper.

## Original native owner and genuine complete callers

Original target: Japanese TH20 v1.00a Steamless `resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

- The entire native `0x004AAA60..0x004AAA72` body is **19 bytes, 9 instructions**. Its actual `__thiscall` receiver is saved to `[ebp-4]`, returned through `eax` as **`this + 0x2244`**, followed by an ordinary `ret`, with **zero native E8 and zero original PE HIGHLOW fields**.
- The exact complete original **1,371B game-owned `Enemy::defeat`** at `0x004A5640` physically calls this same original head **three separate times**, at `0x004A58C5`, `0x004A5955` and `0x004A597B`. These are native original E8 targets extracted independently from the entire original game boss, not guessed from C++ names. The real Enemy gameplay uses the returned PlayerFeedback field to record hits and compute reward multipliers.
- Independently, the exact complete original **794B Player constructor** at `0x004F46A0` constructs the same member by loading the Player receiver, **adding 0x2244 at `0x004F4941`**, then calling the actual `PlayerFeedback` constructor at **`0x004F4947 → 0x004F4580`**. This independently establishes the storage owner and subobject lifetime; it is not an arbitrary convenience pointer.
- `src/Player.hpp` independently asserts `offsetof(Player, feedback) == 0x2244` under native x86; `src/Player.cpp` has the naturally typed, maintained `PlayerFeedback* Player::feedback_value() { return &feedback; }` member body. No fabricated wrapper or reinterpret cast is used.

These combined facts support **authored, high-confidence original gameplay project ownership**, rather than a CRT/STL helper or an unproven generic folded alias. The function head occupies a unique, nonoverlapping 19-byte range in the original `.text` inventory.

## Strict existing canonical unit and bookkeeping

Canonical `player_feedback_access`, symbol
`?feedback_value@Player@th20@@QAEPAUPlayerFeedback@2@XZ`,
actual pinned MSVC x86 `build/core180-canonical/Player.obj`, locked profile
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The unmodified strict comparator again reported:

- `player_feedback_access: exact (19/19 bytes)`
- `enemy_defeat: exact (1371/1371 bytes)`
- `player_construct: exact (794/794 coverage bytes; 799/799 compared bytes)`

The new admission changes only `function-origins.csv`, the corresponding inventoried function status/owner in `functions.csv`, adds **one** nonoverlapping row to `matches.csv`, and refreshes the generated progress snapshot. Source, native target, compiler profiles, previously exact unit manifests and native object receipts are unchanged. There are **zero changed native source providers** to replay cold. These three actual existing unit receipts were compared strictly in the affected call/owner chain; no global cold replay was run.

Independent reproducible original caller/constructor/whole-leaf evidence:
`.analysis/core676-player-feedback-original-native-origin.py/json`.

**Disjoint game-authored exact coverage:** 499 complete original functions / 179,444 bytes → **500 / 179,463 bytes**. No extra code bytes are credited for the 1,371B Enemy boss or 794B Player constructor; both were previously counted exact, and the new 19B leaf is a distinct original interval. This does not establish whole-game linkability or additional Player main-frame exactness.
