# CORE/RECON-1118 — original 875B Card periodic-update Boss and 32B HUD leaf whole strict exact

The original is the selected Japanese TH20 Steamless v1.00a executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This result covers **two distinct game-authored original heads**, never a
prefix or inferred continuation, plus the already accepted 23B bit-8 getter.

## 875B parent — complete native machine code, not just a call graph

`0x00486F60..0x004872CA`, complete SHA-256
`580adb8f5e4f41c29033e2654b23f480e7f8f4dde927bbfb8f3f4f15b4ed986d`,
has **875 actual bytes, 262 i386 instructions, 28 original E8 and 8
physical PE HIGHLOW fields**. It is the real Card per-frame update; the
original 13B callback bridge `0x004885D0` calls it at `0x004885D6`.

The maintained [`CardTickBoss875.cpp`](../src/CardTickBoss875.cpp) now
implements all of the original gameplay transitions using the already
established real `Card` layout (+`0x78` flags, +`0x7C` bonus, +`0x80`
initial bonus, +`0x84` duration, +`0x8C` frames, +`0xAC` position,
+`0xC0` context):

- Returns one without modifying state for an inactive Card. On an active
  Card, advances `frames`, checks Timer thresholds of **60, 300 and 120**,
  clears HUD flag0 when bit9 is clear, updates a signed decaying bonus
  with the native divide-then-round-to-ten arithmetic, and increments
  the Card Timer using the real `Timer::operator++(int)`.
- Uses the original two **independent 23B bit-8 getter E8** calls for
  the top/bottom visibility hysteresis: original data are **96**, **128**
  and **448** float objects. It preserves the distinct direct bit8 reads
  in the other state branch, the paired Player position lookups, three
  child AnimationHandle event `3` or event `2` calls and the corresponding
  bit2 flag transition. The grouped conditions retain the original
  short-circuit event evaluation order.
- Samples the real selected Enemy only when present and moves the Card
  `Vector3` towards its position using the original `Vector3::operator-`,
  `operator*` and `operator+=`. It passes the new position to the real
  effect AnimationHandle and clears bit5 if the original Bomb state is no
  longer active. The interpolation factor is the real pooled float
  `0.05f` at native `0x0056FE5C`, not a substituted approximation.

The source is a non-owning `NativeCardTickView` interpreting the real
`Card*` receiver. It does **not** add a vtable, invent padding fields,
create a second Card storage type, or modify the shared `Card.hpp` ABI.
`Context::player()` and `Context::enemy_controller()` compile to the
existing folded original 17B getters, and the real 42B Bomb predicate
is still shared with the exact Card Start work. Their aliases are
explicitly validated by original E8 destinations, not re-credited.

### Real MSVC source experiments that closed the body

Pinned MSVC 19.44 x86 C++20 `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` was tested with multiple genuine C++ source
forms (scoped probes under ignored `.analysis/`). Results:

| Real source experiment | Full source bytes / instructions | E8 physical positions | Whole strict result |
| --- | --- | --- | --- |
| Initial typed Card reference and early exit | 894B / 267 | 0/28 | NONEXACT |
| Direct borrowed receiver and outer active branch | 882B / 263 | 5/28 | NONEXACT |
| Correct original bit2 `>>2 &1` test, live external factor | 885B / 264 | 23/28 | NONEXACT |
| Original literal `0.05f` scalar, real bit2 test | **875B / 262** | **28/28** | **875/875B EXACT** |

The last transformation removes a genuine extra 10B/two-instruction
float local spill, reproducing the native `push`, then `movss` from the
pooled literal and `movss` to the outgoing stack argument. No dummy
variables, inline assembler, fabricated NOPs or special linker behavior
were used. The source's **all 28 E8 opcode offsets and targets and all
8 PE HIGHLOW offsets and destinations** match the native. The entire
original **731/731 nonrelocation bytes** agree. The locked comparator
therefore accepts **875/875 whole function bytes** from the real source
and exact canonical MSVC object.

## Distinct 32B Card HUD flag0 reset

The original complete `0x00487B90..0x00487BAF` body has SHA-256
`d0c5dc0bf24d68834a4e0f5ad9ac71b6c73523bd993d8359032fd0211a54c3aa`.
It is called by the 875B parent's **E8 `+0x05C`** when 60 frames have
elapsed and Card bit9 is clear. Its original 12 i386 instructions
read, clear and write **HUD receiver +`0x3344` bit0**. Source
[`CardTickUiClear32.cpp`](../src/CardTickUiClear32.cpp) accesses exactly
that borrowed field with a natural `std::uint32_t` read-modify-write;
no fake prefix-padded HUD struct is allocated. Both original and compiled
bodies are **32/32B identical**, with no E8 or PE HIGHLOW fields.

## Whole native receipts, tracked credit and scope

[`scripts/verify-card-tick-boss875-and-ui32-native.py`](../scripts/verify-card-tick-boss875-and-ui32-native.py)
independently pins both original SHA-256 bodies, their terminal `ret`,
all 28 E8 targets, all 8 physical HIGHLOW values, the true literal
floats, 13B original callback wrapper, the actual compiler symbols,
and the strict receipt. The separately accepted original 23B Card bit-8
getter has 2 original physical E8 uses here and is rechecked but not
credited twice. A shared new tiny header
[`NativeCardTickViews.hpp`](../src/NativeCardTickViews.hpp) holds these
real borrowed interfaces, with the old getter recompiled unchanged.

Only the **three affected source units** were cold built:

```text
CardFlag8Getter23.cpp: exact (23/23 bytes)
CardTickBoss875.cpp: exact (875/875 bytes)
CardTickUiClear32.cpp: exact (32/32 bytes)
Exact replay: 3/3 units, 3 cold objects
```

Reproduction:

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardTickBoss875.cpp \
  --source src/CardTickUiClear32.cpp \
  --source src/CardFlag8Getter23.cpp
scripts/repo-python scripts/verify-card-tick-boss875-and-ui32-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

**Two new distinct authored original heads, 907 new native `.text`
bytes (875+32)**. These remain separate from the previously credited
23B bit getter and the ongoing **1,896B Card Start** and **6,073B
battle-controller** original NONEXACT Bosses. Whole-game binary linking
and runtime playability have not been established; no full-graph cold
replay was performed.
