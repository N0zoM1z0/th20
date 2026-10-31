# CORE/RECON-1006 — whole-exact BombController active-state predicate from 1,896B Card start

Target: Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The **complete original 42B/14-i386** body at `0x00478130` (SHA-256
`2b2d4d3752de62d8d422963622a2fc921cf81e7ac441baede296ed98e6fc1517`)
checks whether the real `BombController` state word at owner `+0x18` equals
one, returning a true native one-byte `bool` via `movzx eax,byte ptr
[ebp-4]`. The independently pinned **1,896B Card::start_spell** original
calls this exact original head via its actual E8 at `+0x1D6`.

The maintained source [`CardStartBombActive42.cpp`](../src/CardStartBombActive42.cpp)
uses the actual existing `BombController::active_state` field (verified
native offset `+0x18`) through a borrowed typed receiver view. This
**does not change** `BombController`'s public data, its vtable, inheritance
or any previous canonical source owner. Read-only proof
[`verify-card-bomb-active42-native.py`](../scripts/verify-card-bomb-active42-native.py)
checks both immutable complete native bodies, true E8 destination, original
`ret`, actual state-word load, and absence of PE HIGHLOW fields.

Pinned MSVC 19.44 x86 C++20 emits **42/42 exact bytes** with the
proper `__thiscall` and full `bool` return, independently from Ghidra's
provisional fastcall inference. One-source localized replay:

```text
card_start_bomb_active_42: exact (42/42 bytes)
Exact replay: 1/1 units, 1 cold objects
```

Credit: **one newly matched game-authored head /42 native `.text` bytes**.
The source-absent 1,896B Card start parent remains **NONEXACT**; its
existing Card state and HUD helper matches are not duplicated, and no
whole-game linkage or gameplay completion is claimed.

```sh
scripts/repo-python scripts/verify-card-bomb-active42-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardStartBombActive42.cpp
```
