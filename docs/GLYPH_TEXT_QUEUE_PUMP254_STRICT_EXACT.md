# CORE/RECON-1075 — complete original 254B glyph-render task dispatcher, whole strict exact

Immutable target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire original TH20-owned **`0x00416140`** is a
**254B/74-instruction i386** game-render queue dispatcher, native
whole-body SHA-256
`ef9966b4d7958ec50e93ea140df2f52ba3109e6ecf5a9caf0ecd1376510e0899`.
This is the previously missing gameplay executor linking the exact
56B glyph task submission wrapper and the exact 360B D3D9 glyph
texture-upload callback. Its original native code is independently
physical and not reconstructed by renaming a folded `std::list`
function.

## Actual native task-list and two recursive locks

The original global object at **`0x005B66E0`** is a genuine
**12-byte native i386 `std::pmr::list<std::function<void()>>`**. Its
`+0x00` allocator resource, `+0x04` sentinel/node slot and `+0x08`
live node count are part of the same object. The dispatcher genuinely
calls the original folded 17B `std::list::size()` `0x00412730`,
reads the count at `+0x08` and **skips work only when the count is
zero**. Using the more conventional `!std::list::empty()` expression
in the candidate compiles a different path, not the original.

When a task exists, original code acquires actual game recursive lock
slots **`0x12` then `0x13`**; constructs a local **40-byte
`std::function<void()>`** in its default state; **copy-assigns** from
the *front* of the actual native PMR queue; takes the *begin* iterator
and calls `erase(begin())` to remove that list node; then **invokes
the copied task** while holding the two native locks. The task is
destroyed, then locks `0x13` and `0x12` are released in reverse order.
This is the complete native exception-safe scope; it is not a
`pop_front()` shortcut, and source does not invent detached worker
threads, extra queue races, an async scheduler or a callback lifetime
not observed in the executable.

The maintained real C++20 body in
[`src/GlyphTextQueuePump254.cpp`](../src/GlyphTextQueuePump254.cpp)
and the borrowed 12B queue declaration
[`NativeGlyphTaskQueue.hpp`](../src/NativeGlyphTaskQueue.hpp) implement
this exact original sequence using standard `std::pmr::list` and
`std::lock_guard<std::recursive_mutex>`. It is an actual game-owned
nonempty queue executor, not a fake empty wrapper around the already
strict generic library routines. The previous generic PMR-list
insertion source (151B `_Emplace` and 158B node ctor, still NONEXACT)
creates nodes for the **same physical native queue protocol**; its
118B guard and 11 accepted PMR list children are separate code.

## Whole original call/PE relocation graph

The immutable original 254B method contains **exactly 15 genuine E8
and eight PE HIGHLOW** fields. They are independently pinned by
[`verify-glyph-text-queue-pump254-native.py`](../scripts/verify-glyph-text-queue-pump254-native.py):

| Original E8 site | Native original destination and meaning |
| --- | --- |
| `+0x2D` | `0x00412730` previously exact folded 17B list size getter |
| `+0x41/+0x5D` | `0x0040C310` lock-registry slot 0x12 /0x13 |
| `+0x4A/+0x66` | `0x0040B730` native recursive lock_guard construction |
| `+0x72` | `0x00414150` 23B `std::function<void()>` default constructor |
| `+0x80` | `0x00415600` 22B PMR list front getter |
| `+0x89` | `0x00414540` 60B `std::function` copy-assignment |
| `+0x98` | `0x004150B0` 63B list begin iterator constructor |
| `+0xAF` | `0x00415550` 93B native list erase |
| `+0xB8` | `0x00414740` previously exact 59B `std::function` invocation |
| `+0xC4` | `0x00414400` previously exact 20B function destructor |
| `+0xD0/+0xDF` | `0x0040B900` two lock_guard destructors in reverse order |
| `+0xF5` | `0x005429EE` actual native security-cookie check |

The eight physical original HIGHLOW fields are: `+0x06` SEH handler
`0x00567E2D`, `+0x15` cookie `0x005B25C0`, and four actual
references `+0x29/+0x7C/+0x94/+0xAB` to the **same PMR list
object at `0x005B66E0`**, plus two references `+0x3D/+0x59` to
original lock registry `0x005C0240`. The two D3D/GDI tasks that
flow through the queue are not counted as part of this 254B source.

Original whole code, 74 decoded instructions, all 15 physical E8
and eight independent PE HIGHLOW roles are SHA-attested **before**
comparing the generated object. Pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
then compiles the natural dispatcher to **254B/74 instructions**,
with **162/162 comparable native bytes**, all 23 real original
relocation positions and authentic destinations. A controlled
source-only probe matrix confirmed the contrast:

| Meaningful source formulation | Generated complete native method |
| --- | ---: |
| True `queue.size()!=0`, `task=queue.front()`, `erase(queue.begin())` | **254B/74 i386, WHOLE EXACT** |
| Change only count predicate to `!queue.empty()` | **257B/75 i386, NONEXACT** |
| Copy-construct instead of default+copy-assign task | **245B/71 i386, NONEXACT** |
| Use `pop_front()` instead of `erase(begin())` | **225B/62 i386, NONEXACT** |
| Create an extra named iterator/local in the loop | **265B/77 i386, NONEXACT** |

The original native execution order and resource ownership, rather
than code padding, recovered the exact size. The canonical source
is the unique game-owned function at this physical address:

```text
glyph_text_queue_pump_254: exact (254/254 bytes)
Exact replay: 1/1 unit, 1 cold object
```

This credits **one newly distinct game-authored original head /
254 executable `.text` bytes**. The existing folded list-size getter,
independently exact 59B callback, 20B function destructor, native
lock wrappers, and any future exact natural generic `front/begin/erase`
source bodies are **not re-credited as game-authored code**. The
151B/158B original queue insertion nodes and the 2,227B GDI text
producer remain separate SOURCE-PRESENT/NONEXACT frontiers. This
finished task pump does not establish whole-game linkage or runtime
playability. No full-project cold replay was used.

```sh
scripts/repo-python scripts/verify-glyph-text-queue-pump254-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueuePump254.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
