# Enemy opcode 551: genuine FogValue packing in the complete-root host (CORE176)

The comparison target remains Japanese TH20 v1.00a Steamless PE32, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The production `EnemyState::execute_opcode` at **0x0048C010** remains an
unimplemented, **41,967-byte** whole root. This batch advances its single
private, complete-root semantic source candidate; a native case is **not** a
standalone function and receives zero partial exactness credit.

## Full original native case and five operand reads

The complete native opcode 551 primary interval is **0x00495C1F through
0x00495D20 (end exclusive)**: **257 bytes, 58 instructions** (the last one
jumps to the whole dispatcher's shared exit at 0x4963DF). The actual
original instruction bytes, case SHA-256, and nine direct call sites are
recorded in ignored private `.analysis/core176-enemy-551-native-audit.json`.
The native trace constructs an actual four-byte `AnimationHandle` temporary,
then calls `EnemyState::integer_argument` at indices **0, 1, 2** in that exact
order. It assigns the third integer into the temporary through the genuine
native handle word assignment at `0x0045D650`. This use of a handle-shaped
four-byte value is observed; it does not establish that the word refers to a
live renderer animation.

It then reads floats in **4, 3** order, and interprets the third integer's
four little-endian bytes as unsigned blue, green, red and alpha values. Each
byte is converted separately to a float and passed with the two sampled
floats to the real six-float `FogValue` constructor at `0x004718D0`.
`FogValue` has already been source-reconstructed as a complete **28-byte**
value with blue/green/red/alpha floats and a packed color word. The host
executes the **production** handle/assignment and FogValue constructor/packer,
not duplicate guessed C++ semantics.

The last original call at `0x0049C5B0` receives integer operands 0 and 1 and
a borrowed pointer to that completed FogValue. Crucially, the original
program loads a process pointer at **0x005C069C** only **after all five
operand evaluations and fog construction**. The pointer's complete Stage/
Background/global owner and the real 45-byte wrapper/130-byte subcall are
*not* yet accepted. The private host therefore captures only the original
transfer boundary as an **opaque identity**, rather than inventing a production
facade or calling these unresolved functions. This is an explicit limitation.

## Full 41KB root regression, not a case fragment

The previous CORE175 full host passes **37,479** cases. CORE176 adds **170**
whole-root caller checks: **160** combinations of ten four-channel color
words, four integer IDs, two near/far distance patterns and two late-global
retarget options, plus **ten** exception-injection cases covering all five
operand reads and both retargeting states. All **37,649/37,649** cases pass in
a freshly compiled **79-translation-unit** `g++-13 -O2 -Wall -Wextra -Werror
-fsanitize=undefined -fno-sanitize-recover=all` host, with all earlier
movement, drop, rank, HUD, visibility, screen, sound, Game and Bullet paths
still running in the **same whole-root executable**.

Each successful test validates complete read order `i0,i1,i2,f4,f3`, the two
raw near/far float words (including signed zero, infinity and a NaN payload),
all four independent channel floats, unchanged input EnemyState image, and
exact preservation of the packed color. The callback may switch the opaque
global pointer while reading the last float operand, and the subsequent
transfer must use the **new** pointer. Failure at *any* operand stage
prevents the boundary call, leaving the entire state unchanged.

The ignored private reproducibility proof
`.analysis/core176-enemy-whole-host-proof.json` includes SHA-256 of all
**94** source/fixture/native-input paths, the executable and result log;
the original **CORE175** private candidate/host/log hashes also remain
unchanged. All **164** current authenticated pinned-MSVC canonical object
receipts were rechecked and remain valid. This stage changes **zero**
production code, ledger mappings, strict units, or exactness claims. The
private whole-root draft now covers **120 effective opcode values / 91
original primary heads**, with **212 independently accepted complete authored
functions / 56,622 native bytes** and **998 whole strict units** unchanged.

## Remaining major work

Correct native byte-exact emission of the 41,967-byte dispatcher still needs
its full 174-head primary routing, four nested rank tables, shared exits,
compiler-owned EH/data and true native subsystem owners. For this specific
path the original 0x005C069C global and 0x49C5B0/0x4776C0 fog interpolation
interfaces remain unclosed; the earlier FogValue leaf exactness does not prove
these owners. Other high-priority native paths include 539, 548/549, 555 and
unrecovered original Screen/Renderer/Stage resource lifecycles. No original
Win32/game startup, playability or overall percent exactness is claimed.
