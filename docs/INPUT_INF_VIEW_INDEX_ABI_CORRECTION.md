# CORE/EXACT-508 — correct the native InputInf logical-to-process-view signed index ABI

Target: the original user-selected Japanese TH20 v1.00a Steamless executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The previously described `InputInf+0x2E30` two-pointer view layout was
wrong.** Two native 4-byte words at `+0x2E30` are **signed process-view
indices**, not `InputButtonState*`. The original 26-byte physical member
at `0x00498FB0` returns one signed `std::int32_t` selector. Its exact
original 26 bytes and 10 instructions remain unchanged; this correction
neither adds a new physical unit nor credits duplicate game bytes.

## Independent original caller evidence

The complete original 26-byte getter reads the receiver in ECX, uses the
signed stack index at `[EBP+8]`, loads
`[ECX + index*4 + 0x2E30]` and returns the raw 32-bit result in EAX
with `ret 4`. This alone could encode either an index or a pointer; the
older origin review inferred a pointer without checking enough consumers.

Three **independent native original E8 callers** supply the decisive data:

| Original game-owned enclosing routine | Original call instruction | Result use |
| --- | --- | --- |
| Player state root `0x004F7430` (4,043B) | `0x004F746B` | Saves the selection for the active Player state, not an `InputButtonState*` receiver |
| Player main-frame root `0x004F9C30` (3,111B) | `0x004F9C6D` | Tests result as **signed nonnegative**, then indexes the live 4-byte pointer array at `0x005B889C + index*4` before calling the 25B exact `InputButtonState::replay_current_bits` |
| Additional player control root `0x00505A30` (853B) | `0x00505A5F` | Independently repeats the signed `index >= 0`, `process_input_views[index] != nullptr` and `replay_current_bits` protocol |

The native `InputInf::start` independently publishes four actual
`InputButtonState*` process pointers into the distinct global array
`process_input_views[4]` at `0x005B889C`. That **global array** is where
the original `InputButtonState*` values live; it is not the two-word
`InputInf+0x2E30` selector. The independently strict-exact 261B InputInf
constructor only proves that it zeros both selector words, not that they
have pointer type. The original user/producer identities therefore prove
`std::int32_t view_indices_2e30[2]` and an integer-returning getter.

The maintained C++ now uses exactly the corrected ABI:

- `InputInf::view_indices_2e30[2]`, preserving both original 4-byte words
  and their original class layout/constructor initialization.
- `std::int32_t InputInf::for_view(std::int32_t logical_index)`, with
  native compiler symbol `?for_view@InputInf@th20@@QAEHH@Z`.
- The genuine 3,111-byte Player main-frame source calls this method
  once and tests the returned signed view index before dereferencing
  `process_input_views[view_index]`.

Independently original-attested raw 26 bytes are
`55 8B EC 51 89 4D FC 8B 45 08 8B 4D FC 8B 84 81 30 2E 00 00 8B E5 5D C2 04 00`.
The corrected locked MSVC object emits **all 26/26 original bytes with
zero relocations**, even though the source-level decorated return type
changed. The original exact `input_inf_for_view` unit's symbol was
updated; physical address, compiler profile, original-byte extent and
zero-relocation manifest are unchanged. Do not infer the original source
identifier from the modern descriptive `for_view` name.

## Narrow cold rebuild and exact regression

The other concurrent source change adds a complete typed Player main-frame
C++ frontier and its method declaration to `Player.hpp`. Before editing,
existing canonical compiler receipts identified the actual original
`Player.hpp` include closure as **25 providers / 72 exact units**,
and `InputInf.hpp` as **8 providers / 17 units**. They were disjoint:
**33 unique source/object providers, 89 canonical full original units**.
All 33 were serialized and cold built under their *existing* locked
compiler profiles. Each complete original body and the original
relocation field targets were independently checked against the
new objects before replaying **89/89 strict exact whole functions**.

The only affected private compiler symbol renumbering was the genuine
Player constructor diagnostic string at native `0x004F499C`, pointing to
original `0x00572BB8` (`initialize PlayerInf\n`). Its compiler-local
label moved from `$SG82283` to `$SG82284` while the complete original
message, original relocation field, nonrelocated original bytes and
original PE target remained identical. The manifest changes **only**
that private spelling; it does not rewrite original anchors or invent
comparison destinations. The complete 3,490B native InputDevice polling
boss and prior Player option/animation functions remain strict exact.

Reproducible ignored evidence is retained in
`.analysis/core508-player-main-preedit-receipt-closure.json`,
`.analysis/core508-input-view-preedit-receipt-closure.json`,
`.analysis/core508-pre-reconcile-89unit-proof.json`,
`.analysis/core508-source-scoped-cold-build.log`, and
`.analysis/core508-player-input-89unit-strict-replay.log`.
No unfiltered whole-repository cold replay was run.

The still **NONEXACT** enclosing Player main-frame source is analyzed
separately in [CORE/RECON-508](PLAYER_MAIN_FRAME_3111_TYPED_SOURCE_FRONTIER.md).
This ABI correction proves actual runtime data shape and preserves old
strict native code, but does not prove a linked or playable full game.
