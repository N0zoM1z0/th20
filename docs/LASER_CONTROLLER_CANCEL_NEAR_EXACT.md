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
