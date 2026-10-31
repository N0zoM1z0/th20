# CORE/RECON-1028 — original 32B task-list push-back strict exact, with real ASCII enqueue caller

Locked target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x00470A20` is a **complete 32B/15-i386**
`std::list<std::function<void()>>::push_back(std::function<void()>&&)`
with SHA-256 `e61e3cf7c7d9061fe6e5eb45caee8ed3e9a4be730ba4c5cd694fff99e6fad884`.
It forwards the actual list head pointer and rvalue task pointer into
its original E8 `+0x14 -> 0x004682E0`, then returns with `ret 4`.
There are no original PE HIGHLOW fields in this body.

Its parent is not speculative: the original **153B/45-i386
AsciiInf::enqueue** at `0x00470180` (already source-exact under
[CORE/RECON-1027](CARD_ASCII_TASK_QUEUE153_STRICT_EXACT.md)) calls
this exact physical head at **E8 `+0x5D`**, as independently confirmed
from the immutable PE. The natural `pending_tasks.push_back(std::move(task))`
statement in [`CardAsciiTaskQueue153.cpp`](../src/CardAsciiTaskQueue153.cpp)
instantiates precisely that complete native STL method. The parent retains
the native lock-18 guard, exceptional unlock, function destruction and
full original 153B byte extent without requiring a new source owner or ABI.

[`verify-card-ascii-list-push32-native.py`](../scripts/verify-card-ascii-list-push32-native.py)
SHA-pins the original 32B body, its 15 original instructions through
`ret 4`, the genuine call target `0x004682E0`, the absence of PE HIGHLOW
and the original 153B caller's physical `+0x5D` E8.

Replaying just that already scoped source with locked MSVC 19.44 i386
C++20 keeps **both the parent and the newly accepted STL helper** exact:

```text
card_ascii_task_queue_153: exact (153/153 bytes)
card_ascii_list_push_back_32: exact (32/32 bytes)
Exact replay: 2/2 units, 1 cold objects
```

This is **one additional physical strict unit /32 original bytes**.
Its original class template/compiler ownership is not proven as authored
game code, so it is `origin=unknown/review`, with **zero new credited
game-authored heads or bytes**. Neither this 32B helper nor the 153B
parent closes the 1,896B Card start's still nonexact lambda/EH producer.
No project-wide cold replay was run.

```sh
scripts/repo-python scripts/verify-card-ascii-list-push32-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardAsciiTaskQueue153.cpp
```
