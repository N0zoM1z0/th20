# ScreenInf allocator, constructor and shutdown — three whole native boundaries

The existing 37B default-priority wrapper, 81B ScreenInf factory and
637B ten-mode initializer now connect to the actual native allocation and
lifetime protocol. This change closes three more complete C++ functions
from the same original owner rather than treating the factory as an
opaque `new` operation.

| Native address | Original body | Source boundary | Exact behavior |
| --- | ---: | --- | --- |
| `0x00422D40` | **67B** | `ScreenAllocate67.cpp` | 0x44-byte `operator new`, null branch, actual zero-memory helper `0x0040C080`, direct constructor call `0x004233B0` |
| `0x004233B0` | **187B** | `ScreenInfConstruction187.cpp` | TaskInfo base, real derived vtable, eight scalar zero stores, Timer constructor, view zero and original diagnostic |
| `0x00425070` | **29B** | `ScreenShutdown29.cpp` | real process allocator, generic virtual-destructor release `0x0041F7C0`, nulls the incoming local and returns zero |

## Natural C++ and exact code generation

`NativeScreenInf` is the observed `0x44`-byte owner with the real
16-byte `TaskInfo` base and Timer at `+0x30`. Its 187-byte constructor
naturally emits the original TaskInfo call, derived-vtable pointer at
`0x0056D744`, Timer call at `0x00422D90`, and diagnostic string at
`0x0056D750`. The complete COFF contribution is 192B: the 187B body
followed by the original five `INT3` alignment bytes. All seven physical
relocation fields are independently replayed; the body and alignment are
not conflated in authored byte credit.

The 67-byte allocation helper uses the original `operator new(0x44)`,
the true thiscall zero-memory wrapper `0x0040C080`, and a typed
non-allocating constructor receiver view for the original direct
`0x004233B0` call. A real positive-allocation branch followed by the
null result branch reproduces the original control flow. No placement-new
helper call, extra allocation, manual object bytes, assembly or padding is
introduced. Its three E8 fields are at `+0x0C`, `+0x22` and `+0x2A`.

The 29-byte shutdown bridge is not a Screen-specific destructor
implementation. It calls the existing generic virtual-destruction and
allocator release helper at `0x0041F7C0`; that helper invokes vtable slot
zero and then releases storage under the real allocator lock. The
shutdown callback's final local pointer assignment models the original explicit
zeroing of its stack argument at `[ebp+8]` and emits the exact seven bytes
without inert code.

## Exact replay

All three functions have independent match units. The constructor compares
its entire 192-byte contribution (187B body plus five original alignment
bytes), including four DIR32 and three REL32 relocations. The allocator
compares 67/67 bytes and all three REL32 calls. Shutdown compares 29/29
bytes, including its process-global DIR32 and virtual-release REL32.
The original 37B wrapper, 81B factory and 637B initializer remain separate
whole-exact units; this work does not double count any parent or child.

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/ScreenInfConstruction187.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/ScreenAllocate67.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/ScreenShutdown29.cpp
```
