# Animation byte-endpoint interpolation: whole 86-byte native exact

The Japanese TH20 v1.00a Steamless binary has a complete 86-byte game method
at `0x00438C60` (SHA-256 `80bd4aa64313c0266df68b27b8a3bbafba99cbe805a6b64577b862fa97c70dea`).
The receiver is an Animation: the method addresses its integer interpolation
member at `Animation+0x134`, promotes two independent unsigned byte arguments
to signed 32-bit endpoint values, and calls the previously exact
`Interpolation<int>::begin` at `0x00439550` with duration and curve mode.

The natural C++ implementation is `NativeAnimationFadeConfig86::interpolate_channel_438c60`
in `src/AnimationFadeConfig86.cpp`, a non-owning Animation view with no extra
storage. The actual 86-byte pinned MSVC x86 compiler output matches all
74 nonrelocated native bytes and the **three original relocations**:

| Original field | Role |
| --- | --- |
| `+0x07` DIR32 | Security cookie `0x005B25C0` |
| `+0x41` REL32 | Integer interpolation begin `0x00439550` |
| `+0x4C` REL32 | Security cookie check `0x005429EE` |

The original finishes with `ret 0x10`; no instruction or padding is supplied
manually. Ghidra's actual callers include the 39,470B Animation VM at
`0x0042B5D0` and original Polygon/Ribbon/Trail group configuration methods.

A focused `replay-exact-units.py --source src/AnimationFadeConfig86.cpp` rebuild
and full canonical COFF/PE relocation comparison is the acceptance gate. The
native head is counted once, separately from its already-exact interpolation
callee and exact caller methods. Existing nominal caller views are reconciled
through the same canonical callee in the following caller-scope step.
