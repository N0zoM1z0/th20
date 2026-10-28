# CORE/EXACT-209 — original Player spatial reference and direction

Target is the locked Japanese TH20 v1.00a Steamless executable (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
The two complete original functions are now maintained in `src/PlayerDirection.cpp`
using `Player`'s real `Vector3 position` at offset +0x614, alongside the
previously established full Player layout in `src/Player.hpp`. Names are
inferred, but original instruction boundaries, complete bytes and immediate
relocation identities are independently checked against the locked native PE.

| Original entry | Whole size | Native behavior | Strict canonical replay |
| --- | ---: | --- | --- |
| `0x00460850` | 19 B | Return reference to the actual Player+0x614 position | 19/19 |
| `0x004FF350` | 157 B | Compute XY position difference to target; if both components equal the original float zero, return native float pi / two, else invoke original scalar `atan2f` wrapper | 157/157 |

The direction method emits all **seven** original relocations: two calls to
`0x00460850`, two reads of the original zero at `0x0056E0E8`, pi at
`0x0056E0F0`, two at `0x0056C8D0`, and the scalar arctangent wrapper at
`0x00459280`. These original target destinations are fixed from independent
native call and literal-object inspection; they were not computed from a
compared field. Both source functions share a single MSVC x86 `/Od /Ob0` object,
`build/core208-canonical/PlayerDirection.obj`, freshly built before strict
comparison. Native Ghidra read of both complete functions independently
corroborated the offset and operand order. The 339-byte original
`BulletController` firing caller at `0x00481780` invokes the direction method
at `0x004817CA`; the firing method and the full 41,967-byte Enemy opcode boss
are not exact as a result of these two leaf admissions.

A change to the shared `Player.hpp` required rebuilding the five existing
source-object providers that include it, totaling **30** old exact units.
The locked compiler assigned the Player constructor's local diagnostic string
symbol `$SG82001` in place of `$SG81998`. Its relocation position/type and
original independent data destination (`0x00572BB8`) remained unchanged.
The manifest's *symbol spelling only* was updated. All original bytes and
relocation values were then compared afresh without relaxed checks:
**30/30 old units + 2/2 new units, six cold objects, all exact**.
Private bounded logs: `.analysis/core209-direction-scope-replay.log` and
`.analysis/core209-player-header-affected-replay.log`; original PE intervals,
relocations and floating constants in
`.analysis/core208-player-direction-original-audit.json`.
No unfiltered cold replay was run; source/include closures determined the scope.
