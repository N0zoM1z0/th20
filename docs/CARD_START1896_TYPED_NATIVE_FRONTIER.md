**Current milestone (CORE/RECON-1030):** The original 1,896B Card start now [constructs a real copyable PMR/Card/Animation callable and directly passes a std::function prvalue to the native-exact 153B ASCII queue](CARD_START1896_TEXT_TASK_CONSTRUCTION_FRONTIER.md). The older 1,732B/472-instruction statistics below remain dated evidence; current parent source compiles to 1,750B/478 instructions with 61 REL32/16 DIR32, still NONEXACT.

# CORE/RECON-1008 — Card::start_spell 1,896B native original and maintainable C++20 gameplay source frontier

The locked target is Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The complete native **1,896B /512 x86** `Card::start_spell` Boss at
`0x00487C30..0x00488397` (SHA-256
`dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410`)
is independently established by the real executable. Its actual `ret 16`,
**62 E8 calls** and **26 PE HIGHLOW** fields are checked in
[`verify-card-start1896-native-frontier.py`](../scripts/verify-card-start1896-native-frontier.py).
The presence of exact children never establishes source or matching status
of this original full function. It remains **NONEXACT**.

## Source recovery and real owner boundaries

A real maintained implementation candidate now exists as
[`Card::start_spell`](../src/CardStartSpell1896.cpp), using the true
`Card` class (0xC8 bytes), real `Timer`, three `info_handles` and one
`effect_handle`, actual `BombController`, `Context`, `EffectInfo`,
`EnemyController`, `AnimationFile`, `AsciiInf`, and borrowed Card HUD and
persistent record interfaces. It follows every major original game state:

- Resets the Card timer, stores the spell index and bounded 64-byte name,
  updates active/capture flags, clears native flag7 and branches on the
  original paused play-state condition
- For non-paused play, writes the name to the two distinct persistent
  **0xE0-stride spell record tables** and calls the already exact 61B
  saturated-at-99,999 attempted-card counter for the proper session kind
- Starts the two actual HUD animations at event 2, clears the bit5 Bomb
  marker and reads the independently accepted **42B Bomb+0x18 active-state
  predicate** before selecting bit5, publishes the frame marker and clears
  bit6, then creates the three independent Card information animations
- Constructs an ordinary PMR string for the spell name and the actual
  **36-byte Card*/PMR string/Animation* capture**. Its real original
  56B constructor, 23B destructor and underlying 167B PMR copy are
  accepted separately. Lifetime is scoped to this text submission sequence
- Starts the actual sound 0x21 and Card effect animation, samples the
  selected boss's real native position (or zero when no enemy exists),
  positions the effect and writes the duration into two child Animation
  variables (child indices 4 and 5) and the Card's own duration state
- Evaluates the native **five-level bonus** table, preserves low 32-bit
  multiplication and clamps the displayed initial bonus to 999,999,999;
  creates a second effect animation independently
- Chooses native stage/variant script descriptors using the genuine
  `0x34` per-stage and `0x0C` per-option byte strides, including the
  special 0x58..0x5C Card index range; conditionally creates the associated
  animation, updates Card flag bit9 through its independently exact 42B
  setter, and visits the stage's optional third script entry

The still unresolved interfaces are named distinctly, not silently
substituted with invented base objects or taken from a historical
decompiler signature. The original `0x005C6110` table shape is observed
only as 0x34/0x0C strides. Its full data owner is **unproven**. The task's
**102B std::function wrapper**, asynchronous ASCII queue, associated
copy/move/EH state, and graphics/sound owner lifetimes are open: a
provisional enqueue boundary in the candidate models intent, **not** a
native-exact implementation of those helper instructions. The original
bonus metadata's complete resource ownership requires further review.

## Native comparison: source present, still NONEXACT

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` compiles the maintained full-route
C++ source to a **1,732B /472-instruction** contribution with
**60 REL32 and 16 DIR32 fields**. The original is **1,896B /512
instructions** with **62 actual E8 and 26 PE HIGHLOW**. This is a real
functional reconstruction and compiler-reproducing experiment, but it
has **not** closed EH, the dispatching text job nor every native branch.
No canonical exact unit has been admitted for this Boss. It contributes
**zero additional accepted game-authored heads/bytes**; it must never be
compared to a shortened 1,732B original prefix.

[`verify-card-start1896-native-frontier.py`](../scripts/verify-card-start1896-native-frontier.py)
separately pins original target code and the distinct source candidate
extent. It checks the exact original E8 to native bit7-clear, Bomb active,
text capture construct/destruct, and Card bit9 setter. A compiled source
probe is retained in ignored `build/gptweb-nextcard/`, while the clean
source remains committed under `src/`. Real full game linking, frame
execution, local text task allocation and the Card start Boss are not
claimed completed. A source-level staging/ABI change will require its
own focused build and replay; no project-wide cold replay was run.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/CardStartSpell1896.cpp build/gptweb-nextcard/CardStartSpell1896.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-card-start1896-native-frontier.py \
  --candidate-object build/gptweb-nextcard/CardStartSpell1896.obj
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1009 — the real PMR spell-name constructor is now whole exact

The maintained 1,896B Card start source naturally instantiates the complete
[128B original `std::pmr::string(const char*)` constructor](CARD_START_PMR_STRING_CHAR128_STRICT_EXACT.md)
that the original parent calls at `+0x2D3`. Its entire 4 E8/2 PE HIGHLOW
code is independently source-exact in a separate unit; the parent itself
remains NONEXACT and no game-authored credit is added by this STL helper.

## CORE/RECON-1027 update — Card ASCII enqueue callee now whole exact

The original `0x00470180` task enqueue invoked by `Card::start_spell`
at `+0x330` now has a [full 153/153 native-exact implementation](CARD_ASCII_TASK_QUEUE153_STRICT_EXACT.md)
using the real process recursive lock 18 and AsciiInf's borrowed
`pending_tasks` list. This resolves the queue *consumer*, not the
remaining text lambda producer or Card start parent EH. The 1,896B
Card start parent is still NONEXACT; previously described missing
callee code is superseded only for this 153B subproblem.
