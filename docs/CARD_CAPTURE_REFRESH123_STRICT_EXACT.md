# Card capture/bomb flags — original 123B whole native C++ exact

At `0x00487BB0..0x00487C2A`, TH20 owns a complete 123-byte Card
state transition. Its only local state is the incoming `Card` receiver;
no synthetic stack fields or separately allocated view are needed.

The original first checks `Card::active` at `0x004887A0`. If active and
the real 35-byte `elapsed_4887d0` predicate says the Card Timer at
`+0x24` reached 60, the method clears `Card::bonus` at `+0x7C`, then
clears bits 1 and 5 of `spell_flags` at `+0x78` in **two distinct writes**.
Otherwise it asks `Card::context` at `+0xC0` for its real
`BombController` and sets bit 5 when the controller's original 42-byte
`active_478130` predicate is true. The inactive Card path does nothing.

`src/CardCaptureRefresh123.cpp` restores this behavior as a single
natural C++ member of a non-allocating receiver view. An early return
and a saved local `Card*` initially compiled to a longer 133-byte
function. Expressing the original positive `Card::active` branch without
a redundant pointer local naturally reproduces the **complete 123B
body**, all ordinary bytes, and all four original E8 physical fields:

| Site | Original target | Meaning |
| --- | --- | --- |
| `+0x0B` | `0x004887A0` | Card active flag |
| `+0x1A` | `0x004887D0` | 60-frame age threshold |
| `+0x56` | `0x00424010` | Context BombController getter |
| `+0x5D` | `0x00478130` | BombController active flag |

Pinned MSVC 19.44 x86 C++20 and the exact canonical relocation replay
match the full **123/123 bytes**. The 35-byte child has its own separate
whole-exact unit. The four real references are independently anchored to
the unchanged original binary, not inferred by solving caller bytes.
This verifies this Card subgraph; it does not claim the larger battle
controller or complete playable game is reconstructed.
