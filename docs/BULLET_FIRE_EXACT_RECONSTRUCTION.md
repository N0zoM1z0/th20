# CORE/EXACT-210 — whole native BulletController firing boss

The canonical original is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
A fresh read of the *complete* original `0x00481780..0x004818D2`
found **339 bytes / 103 native x86 instructions** (SHA-256 of the native
interval `8a6b1ca5d2c7a03d98fa63cc6698a3f5ef058ae64f761354de7770b59b39b38d`).
Natural maintained C++20 is in `src/BulletFire.cpp` and the original-sized
owner protocol is declared on the existing `BulletController` in `src/Bullet.hpp`.
The original identifier spelling is not recovered, but the complete
body, MSVC calling convention and native relocation values are exact.

## Independent behavioral and ABI audit

- The controller's real `context` at +0x286DA0 yields the current Player;
  native `Context::player` precedes the exact newly restored
  `Player::direction_to(params.position)` at `0x004FF350`. The direction
  result is passed as a **float** to every shot, not recomputed for each row.
- ShotParameters are 40 bytes. The native compares **signed 16-bit** `rows`
  at +0x26 in the outer loop, then signed 16-bit `count` at +0x24 in
  the inner loop; both loop indices are native signed 32-bit integers.
- Each shot calls the *actual 3,735-byte* `BulletController::emit` at
  `0x004818E0`, transferring a **by-value `std::shared_ptr<EtamaArgInf>`**
  copied from the caller's owning metadata. Its original native copy and
  destructor support are preserved, not erased or flattened.
- Original control flow must test **nonzero** emission status before
  distinguishing result `1` (stop both loops early) from `-1`
  (continue the inner iteration). A superficially equivalent `switch`
  was **not** emitted byte-identically by the locked compiler.
- After the loops or early stop, metadata `sound` at +0x3c is read; if
  nonnegative, `process_sound` at `0x005BA830` receives the sound ID and
  the exact `params.position.x` as a float for positional playback.
  The shared pointer argument is destructed on function exit/unwind.

The complete eleven original relocation destinations are independently
corroborated from the native call and object flow: SEH handler
`0x0056915D`, security cookie `0x005B25C0`, Context Player accessor
`0x0040FF90`, Player direction `0x004FF350`, shared-pointer copy
`0x0047B850`, real Bullet emission `0x004818E0`, shared-pointer getter
`0x0040C300` twice, SoundInf singleton `0x005BA830`, positional request
`0x00426EB0`, and shared-pointer destructor `0x0047C300`.
No relocations were inferred by solving the target field being compared.

## Strict original comparison and affected-only scope

The locked MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` compile of `src/BulletFire.cpp` emits **339/339 identical
canonical bytes after all 11 native relocations are replayed**. The
initial unaccepted probes, including a 322-byte alternative `switch`,
were retained privately only as diagnostic counterexamples, not as source.

Adding member declarations to shared `Bullet.hpp` changes its actual
compiler include closure: **six** existing cold object providers and
**35** old exact units. All 35 were freshly rebuilt and strictly compared
successfully. The compiler renumbered its own diagnostic string-local
symbols (one in the Bullet controller ctor from `$SG79803` to `$SG79812`,
four in the Dialogue ctor from `$SG117739..117742` to
`$SG117748..117751`). Original native target data addresses and
relocation fields stayed unchanged; only the manifest symbol names were
corrected. **Total: 36/36 strict units, seven cold objects.** No unfiltered
whole-graph cold replay ran. Logs: `.analysis/core210-bullet-fire-replay.log`
and `.analysis/core210-bullet-header-affected-replay.log`.

Crucially, the downstream **3,735-byte native Bullet single-shot emission
function `0x004818E0`** remains to be reconstructed; this source only declares
its ABI and calls its original native address. The original complete
**41,967-byte `EnemyState::execute_opcode`** that invokes `BulletController::fire`
through opcode 601 is also still nonexact. These large functions remain
first-class reconstruction targets rather than being treated as completed
by this admission.
