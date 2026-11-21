# LaserController cancel-all — 238B strict-exact boss

The original `LaserController::cancel_all` at `0x004C9490` is restored in
`src/LaserCancelAll238.cpp` using the actual `IntrusiveList<Laser>`,
`IntrusiveIterator<Laser>`, `IntrusiveLink<Laser>` and `Laser` virtual
interface. It traverses the live list, skips lasers whose state is exactly 1,
invokes each remaining laser's native virtual `erase(mode, argument)` slot,
lets the iterator destructor repair observer links, and returns one.

The pinned i386 source candidate reproduces the complete 238-byte function,
including the original EH handler, security cookie, iterator initialization,
list begin/end, advance/differs/get, both node accesses, virtual dispatch,
iterator destruction and cookie check. The 12 relocation anchors are pinned
independently to the original executable. Iterator initialization's compiler
`__autoclassinit2` call is anchored to the shared native 8-byte clear helper at
`0x0040C080`, consistent with the other exact iterator consumers.

This is ordinary C++ using existing project types; no assembly, synthetic
padding, copied machine code, or post-return bytes are used. The neighboring
`LaserController::cancel_near` and `reset_all_lasers` remain independent
operations and retain their own match credit.
