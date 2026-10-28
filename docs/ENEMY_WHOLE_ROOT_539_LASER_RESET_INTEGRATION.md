# Whole Enemy dispatcher: opcode 539 / genuine LaserController (CORE183)

CORE183 advances the **same complete 41,967-byte** `EnemyState::execute_opcode`
root at `0x0048C010`, **not** a separate extracted fake function or isolated
opcase. Original executable is Japanese TH20 1.00a Steamless PE32, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The full Enemy root **remains machine-code nonexact**. The already accepted
263-byte LaserController function has its own independent canonical credit;
**no opcode-539 caller bytes** have been registered as exact functions.

## Native case boundary independently decoded

The actual opcode 539 code is **30 consecutive bytes / 7 instructions** at
`0049579E..004957BB` (end-exclusive `004957BC`), with SHA-256
`a5864dab8c4c7cf5b834b999ef8f69fcee8b078ecafe5184edbefb577f7f278c`.
Each original operation was independently read from the unchanged PE:

```asm
0049579E mov  ecx, [ebp-0x3F4]        ; EnemyState*
004957A4 mov  ecx, [ecx+0x2EC]        ; real Context*
004957AA call 0041CA90               ; Context::laser_controller (slot +0x14)
004957AF mov  ecx, eax
004957B1 call 004D2430               ; exact 263B reset_all_lasers
004957B6 nop
004957B7 jmp  004963DF               ; root's shared common exit
```

There are **no** ECL integer/float operand or destination reads, no
zero-argument value conversion, no state-1 Laser filtering, no return-value
transfer and no global/controller fallback. The getter runs once using the
state's live `Context` receiver. The already accepted full callee performs
actual `Timer::operator=(0)` at `Laser+0x6AC`, clears `+0x6CC`, and makes a
true 34-slot beam vtable `erase(1,0)` call. See
[CORE/EXACT-182](ENEMY_OPCODE_539_LASER_RESET_EXACT_RECONSTRUCTION.md).

## The original complete switch candidate and actual owner semantics

The private candidate `.analysis/core183-enemy-dispatch-candidate.cpp` retains
the **entire preceding CORE181 root switch** and adds the natural source case:

```cpp
case 539:
    state.context->laser_controller()->reset_all_lasers();
    break;
```

This is executed through the single existing root entrypoint in
`.analysis/core183-dispatch-host.cpp`, not a substitute Laser service, raw
blob, memcpy trampoline or separately claimed caller. The host uses actual
maintained `Enemy`, `EnemyState`, `Context`, `LaserController`, `Laser`,
`IntrusiveList<Laser>`, `IntrusiveIterator<Laser>` and `Timer` types. Only
the still-unreconstructed **four concrete beam virtual implementations**
and native resource retirement are test-only fixture boundaries, not
invented production implementations.

`.analysis/core183-laser-reset-host-cases.inc` supplies **192 new complete
root-entry scenarios**: empty/single/three-beam lists, all four iterator
mutation actions (keep / detach current / detach pending / throw), two
Context owner choices, on-callback context retargeting, and four Timer flag
words. It verifies both real typed controller images, all nonselected
beam images, unchanged controller counts, no operand reads, correct
per-beam Timer/field mutation before the virtual call, normal/EH observer
cleanup and precise one-time dynamic Context selection. In particular:
**32** virtual-erase exceptions, **208** actual `erase(1,0)` invocations,
**64** retargeting callbacks. All four native beam vtables have 34 slots;
the fixture's concrete virtuals are intentionally an unresolved leaf boundary.

## Focused execution and verification

The CORE183 recipe and full test log are saved as
`.analysis/core183-dispatch-host-recipe.json` and
`.analysis/core183-dispatch-host.log`. `g++-13` compiled the host with all
**80 actual production translation units** at C++20 `-O2 -Wall -Wextra
-Werror -fsanitize=undefined -fno-sanitize-recover=all`, dead-section
elimination and pthreads. The **prior 38,241/38,241** whole-root scenarios,
including all original opcode 548/549/551/554 cases, still pass; the 192 new
539 cases also pass. **Total 38,433/38,433**. The host is a semantic
whole-root experiment, not an x86 native whole-function exact build.

`.analysis/core183-native-539-audit.json` preserves all seven original
instruction bytes and native SHA; `.analysis/core183-enemy-whole-root-proof.json`
retains SHA-256 for **107** build inputs/fixture/source paths, the complete
host executable/log, predecessor audit and compiler-exact callee receipt.
Proof SHA-256:
`4662940ccf86444eb74092363914cdccdf6274d221809d82632aba4f5105d955`.
The CORE181 candidate and host identities are unchanged. Among the 97
previously recorded CORE181 files, the only changed input is the legitimate
`src/LaserParameters.cpp` from CORE/EXACT-182; the separately tracked
LaserParameters header is pinned in CORE183 as well.

**No MSVC cold build and no full cold replay were run in CORE183.** No
maintained `src/` file changed. All **164/164 current canonical object
receipts**, including the two recently cold-built CORE182 providers, were
re-attested for original source/include and object hashes, without
recompilation; the 263/263 native Laser callee remains exact.

The complete private draft now covers **123 effective opcode values and
94 primary opcode heads**, but numerous other opcode paths, complete
resources, native exception ownership and the 41,967-byte whole-root
machine-code identity remain unresolved. Explicitly **zero** bytes of new
whole-root opcode-case coverage enter the exact-function ledger. Current
accepted authored exactness stays **218 functions / 57,271 bytes**.
