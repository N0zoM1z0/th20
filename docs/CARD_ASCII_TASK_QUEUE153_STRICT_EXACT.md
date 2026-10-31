# CORE/RECON-1027 — complete original 153B ASCII/Card task enqueue, strict exact

Target: locked Japanese TH20 v1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original Card start Boss `0x00487C30` (1,896B /512 i386,
`dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410`)
issues a genuine direct E8 **`+0x330 -> 0x00470180`** to enqueue its
new `std::function<void()>` name-display task.

The native enqueue method is **153B/45-i386**, SHA-256
`49b7446465141dcc4380a69d175ece20eeeab2845c132c9f097fda95b1e50d32`.
Unlike the earlier guessed simple list `push_back`, this method has an
actual *game-owned lock scope*. It calls `process_locks.slot(18)` on the
real `LockRegistry` at `0x005C0240`; constructs a
`std::lock_guard<std::recursive_mutex>`, calls the authentic
`std::list<std::function<void()>>::push_back(std::function<void()>&&)`
for the true `AsciiInf::pending_tasks` member at **+0x1A234**; destroys
the guard; then destroys the **40-byte by-value `std::function`** stack
argument. MSVC's actual EH/SEH prologue, cookie check, unwinding and
`ret 0x28` are preserved, including both normal-path and exception-safe
ordering. The task's contents and original complete Card start producer
remain separately unresolved.

The natural maintained implementation is
[`src/CardAsciiTaskQueue153.cpp`](../src/CardAsciiTaskQueue153.cpp), using
real `std::lock_guard`, real `LockRegistry` and the existing `AsciiInf`
member. Its `NativeCardAsciiTaskQueueView` is a **borrowed receiver**,
not a fabricated new AsciiInf data owner or duplicate list. A previous
private no-lock experiment generated only **103B**, not the original
153B. Restoring the true tracked lock-18 scope (not a fake/inert local)
produced the **complete 153B**, 117/117 non-relocated bytes and exactly
the nine original relocation locations, types and physical destinations:

| Native source offset | Original role |
| --- | --- |
| DIR32 `+0x06/+0x15` | game EH handler `0x00568E75`, MSVC cookie `0x005B25C0` |
| DIR32 `+0x35` | real `LockRegistry` global `0x005C0240` |
| E8 `+0x39/+0x42` | lock 18 slot `0x0040C310`, `lock_guard` acquire `0x0040B730` |
| E8 `+0x5D/+0x69` | genuine list push-back `0x00470A20`, `lock_guard` release `0x0040B900` |
| E8 `+0x78/+0x8E` | `std::function` destruction `0x00414400`, cookie check `0x005429EE` |

[`verify-card-ascii-queue153-native.py`](../scripts/verify-card-ascii-queue153-native.py)
independently pins the original PE 153B function, all six true E8 targets,
all three real PE HIGHLOW, true instruction/function ending and the complete
original 1,896B Card start parent's physical call. The canonical unit
`card_ascii_task_queue_153` replays the whole relocated source with one
fresh pinned MSVC 19.44 x86 C++20 object and receipt:

```text
card_ascii_task_queue_153: exact (153/153 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This adds **one game-authored whole-exact head /153 native code bytes**.
Original STL lock_guard/list children are not credited again; the caller
**1,896B Card::start_spell remains SOURCE-PRESENT/NONEXACT** until its
actual task capture, std::function constructor, text task placement,
resource ownership and native exception path also close. No global cold
replay or header changes were made.

```sh
scripts/repo-python scripts/verify-card-ascii-queue153-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardAsciiTaskQueue153.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1028 — native 32B list helper now independently exact

The original `0x00470A20` task-list push-back invoked at `+0x5D` is
[now a separate whole 32B/15-i386 strict unit](CARD_ASCII_LIST_PUSH32_STRICT_EXACT.md)
replayed from this same canonical object. It remains library-origin
review/uncredited rather than a duplicate authored-game contribution.

## CORE/RECON-1030 — true Card producer now calls this exact queue

The [current source-present Card start Boss](CARD_START1896_TEXT_TASK_CONSTRUCTION_FRONTIER.md)
constructs a copyable PMR/Card/Animation callable in a real
`std::function<void()>` and directly passes it by value through the
shared borrowed [`NativeCardAsciiTaskQueueView`](../src/NativeCardAsciiTaskQueueView.hpp).
This 153B queue and its 32B STL caller remain whole strict exact;
Card start and its 102B callable constructor remain independently NONEXACT.
