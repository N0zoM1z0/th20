# CORE/EXACT-211 — Bullet retirement, context binding and free-list owner

This checkpoint reconstructs **three whole original game functions**, both
small owner protocols and a substantial complete **291-byte** Bullet teardown,
used by the genuine **3,735-byte** single-shot `BulletController::emit` boss.
The original immutable target is the Japanese TH20 v1.00a Steamless PE,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Addresses, sizes, branch shapes and calls were independently rechecked against
original executable bytes and Ghidra; earlier notes were not treated as proof.

| Original entry | Whole function | Relocations | Exact comparison |
| --- | --- | ---: | ---: |
| `0x0047DA40` | `Bullet::deactivate` — complete active-bullet retirement | 13 | 291/291 B |
| `0x00486570` | `Bullet::select_context` — actual context publication | 2 | 54/54 B |
| `0x00485900` | `BulletController::free_list` — real free-list reference | 0 | 19/19 B |

The functions live **together** in the maintained natural
`src/BulletLifecycle.cpp`, with declarations added to the existing typed
`src/Bullet.hpp`. Complete normal compiler codegen has all **15** original
relocations replayed and all **364** bytes identical.

## Nontrivial 291-byte Bullet retirement

The native `Bullet::deactivate` first tests the actual +0x50 state and
**returns immediately** on zero; a straightforward wrapping `if(state != 0)`
was *not* compiler-identical to the original jump shape. Active retirement
then detaches the **real `IntrusiveLink<Bullet>`**, resolves the Bullet's
actual +0x520 Context and its genuine BulletController owner, and prepends
the Bullet's link to `BulletController::free` at +0x286D4C. It sets state to
zero, assigns integer zero to **five distinct native Timers** at
+0x4F8, +0x508, +0x4A0, +0x4B0 and +0x4C0, clears the actual +0x54 and
+0x2C fields, and clears flags bits 0, 8, 9 and 6 **in native order**.
The Bullet's actual `AnimationHandle` at +0x5C is retired. Its Animation
pointer is sent to the real, externally owned animation pool from pointer
global `0x005C0028`, using the original call at `0x0044C2F0`.
Finally it calls the **actual** `std::shared_ptr<EtamaArgInf>::reset()` on
`Bullet::metadata` at +0x98; using an invented no-argument reset function
produced a shorter **281-byte** alternative and was explicitly rejected.

The animation pool's complete class layout, original C++ spelling, global
initialization and physical linker definition are **not** recovered.
`AnimationPoolOwner` in this narrow source is an explicitly provisional
external ABI declaration, *not* a claim that the full manager has been
reconstructed. All thirteen native callee/global targets are anchored from
the original locked PE, including the genuine metadata reset at
`0x004862B0` and original list/handle/Timer operations.

`Bullet::select_context` writes original view index +0x51C and real Context
pointer +0x520 through the actual Session at `0x005BA568` and Session context
accessor `0x0040BBC0`. The exact 19B `BulletController::free_list` exposes
the typed intrusive-list reference at +0x286D4C. These are *not* duplicate
bytes from the existing Controller context binding at `0x00486530`.

## CORE/REVIEW-212 correction: prepend, not append

The original exact caller `0x0047DA40` invokes complete original `0x0044A6B0`.
Independent disassembly now establishes this callee is **head insertion**:
its first call inserts after the list sentinel at `this+0`, it assigns the
link's owner, and it updates `tail` only if it previously pointed to the
sentinel (the empty-list case). The former canonical source used
`free_list().append(&link)` with relocation target `0x0044A6B0`, which
replayed bytes but described the **wrong semantics**. The maintained caller
now uses `free_list().prepend(&link)`; its correct COFF relocation symbol
maps to the *same independently verified* native address. The whole 291B
caller, its thirteen relocations and its 54B/19B sibling units have freshly
passed 3/3 strict replay after the correction. The 66B generic prepend callee
itself remains nonexact (53/58 non-relocation bytes match) and is **not**
newly credited. See [emitter frontier audit](BULLET_EMIT_FRONTIER_AUDIT.md).

## Full boss boundary audit and verification scope

Fresh original PE Capstone disassembly of the **entire original 3,735B**
`BulletController::emit` at `0x004818E0` gives **935 instructions**, **60
direct calls to 43 distinct addresses**, **42 direct conditional/unconditional
jumps** and **2 indirect jumps**. Its locked complete native interval SHA-256
is `54c8c60dc8ca5aaf6a97e094db9447150152849e904741f1f110455b002e051d`.
It calls the new context binder at `0x004819AD` and full Bullet deactivate
at `0x00482716` on its late retirement path. The complete native boss
**remains nonexact**; no partial prefix, handler or switch branch is counted
as a reconstructed standalone function. Private native instruction transcript
and audit are kept at `.analysis/core211-native-bullet-emit.asm` (or
`.analysis/core211-bullet-lifecycle-audit.json`).

The shared `Bullet.hpp` include closure has exactly **six** existing object
providers and **35** old exact units. All 35 were freshly cold-compiled and
strictly rechecked. MSVC-private diagnostic string symbol renumbering moved
one Bullet constructor `$SG79812` to `$SG79816` and four Dialogue constructor
strings `$SG117748..117751` to `$SG117752..117755`; all original relocation
targets and bytes remained fixed. Only the private symbol spellings in the
manifest changed. **38/38 complete strict units, seven affected cold objects**
passed (3 new + 35 old), with no unfiltered whole-graph cold replay.
Logs: `.analysis/core211-bullet-lifecycle-replay.log`,
`.analysis/core211-bullet-header-affected-replay.log`.

The original large **3,735-byte single-shot emitter**, even larger animation
update/retirement dependencies and the **41,967-byte Enemy opcode root**
remain substantive open targets. Full-game linking, actual original global
publication and whole runtime validation are not claimed by a scoped exact
object replay.
