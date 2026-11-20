# `LaserController::cancel_near()` — exact reconstruction

The native method at `0x004CAAD0` is a 288-byte thiscall member. The
maintained natural C++ source now reproduces the complete native function
under the scoped MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` profile.

## Native behavior and ordering

1. Initialize the accumulated cancellation count to zero before copying the
   supplied `Vector3` into `LaserController::cancel_position` at `+0x30`.
2. Construct the eight-byte intrusive iterator using the compiler-generated
   autoclass initialization, obtain `active.begin()` and the null end marker,
   then traverse with the native `advance()` / `differs()` protocol.
3. Read the current `IntrusiveLink<Laser>` through the iterator. Use
   `node_access()` for the state test and repeat `node_access()` for dispatch;
   do not cache a `Laser*` across the two native reads.
4. Skip state 1. For every other state, dispatch the real virtual slot `+0x30`
   (`Laser::cancel_circle(center, radius, mode, argument)`) and add its signed
   result to the accumulator.
5. Destroy the iterator through its native scope cleanup, restore the SEH chain
   and security cookie, then return the accumulated count.

## Exactness receipt

The complete COFF contribution is 288 bytes. All 240 non-relocation bytes
match, and all 12 original relocation fields (48 bytes) resolve to their
native destinations, including the EH handler, security cookie, intrusive
iterator/list helpers, node accessors and virtual dispatch call site. The
canonical `laser_cancel_near` unit is scoped to this source/object and replays
independently. The source owner is established; original authored/source origin
remains unknown and is not inferred from byte equality.


The `LaserCurveInf` vtable's circle-cancel slot at `+0x30` points to the
15-byte `Laser::cancel_circle()` base default at `0x004CAAC0`, which returns
zero. The Line, Beam and Infinite vtables point to separate segment-aware
handlers at `0x004CB060`, `0x004CA830` and `0x004CABF0`; these larger concrete
handlers remain separate reconstruction boundaries. See
[the exact base-default receipt](LASER_BASE_CANCEL_CIRCLE_DEFAULT_EXACT.md).


The Line Laser implementation reached by this loop is the 1,165-byte
`LaserLineInf::cancel_circle()` handler at `0x004CB060`; its current natural
source candidate and concrete `0x18F8` owner layout are documented separately
in [the Line Laser cancellation reconstruction](LASER_LINE_CANCEL_CIRCLE_RECONSTRUCTION.md).
