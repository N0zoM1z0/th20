# CORE/EXACT-301 — complete native Player draw callback (145 bytes)

The agreed Japanese TH20 v1.00a Steamless original, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains a **complete 145-byte / 43-instruction** game-owned Player draw
method at `0x004F8AF0..0x004F8B80`. The original complete interval has SHA-256
`6386222c009954ece0b6924f01e5f887d7ba078e078435fb595f482e85567caf`.
The independent Ghidra target-attested function/caller/callee read and direct
Capstone PE disassembly agree on the whole extent. The only observed native
caller is the separate 13-byte `0x004FEFB0` callback wrapper, separately
closed in CORE/EXACT-303 below.

The complete natural C++ implementation lives at `src/PlayerDraw.cpp` as
`std::int32_t Player::draw()`. It first checks the native `Player::state_value()`
(whose original callee is `0x00411700`) and immediately returns one for state
2. Otherwise, it selects draw layer 12 with the actual Player `view_index` at
`+0x14854`, copies the three lanes of `position_ref()` (`Player+0x614`) into
`animation.vector_5bc` (`Player+0x5E4`), writes **only the bottom two layer
bits** of animation flag byte `Player+0x4CB` to one, submits the embedded
`Player+0x28` Animation for rendering and calls the original Renderer draw
flush at `0x004455C0`. Both paths return one.

The narrow external ABI names `AnimationPoolOwner::flush_draws()` and
`Player::draw()` are inferred from this observable behavior; the 192-byte
Renderer flush implementation and its lifetime/startup linkage remain open.
No target executable, Renderer storage, synthetic services, padding, code
blobs or private database bytes were modified or imported into source.

## Independent native relocation evidence

The complete locked MSVC 19.44 x86 COFF output is **145/145 bytes exact**,
with all 113 nonrelocation bytes and all eight independently resolved
original relocation fields matching. The canonical unit is `player_draw` in
`config/match-units.toml`, using `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`, plus the manifest's C++20 option. Original native
references and complete original PE targets:

| Native field offset | Type | Independently observed original target |
| --- | --- | --- |
| `+0x0B` | REL32 | `0x00411700` Player state accessor |
| `+0x29` | DIR32 | `0x005C0028` current Renderer global |
| `+0x2E` | REL32 | `0x0044F3D0` Renderer layer selector |
| `+0x36` | REL32 | `0x00460850` Player position reference |
| `+0x74` | DIR32 | `0x005C0028` current Renderer global |
| `+0x79` | REL32 | `0x00443880` Renderer Animation submission |
| `+0x7F` | DIR32 | `0x005C0028` current Renderer global |
| `+0x84` | REL32 | `0x004455C0` Renderer draw flush |

The original PE `.reloc` table independently contains all three `HIGHLOW`
entries at `0x004F8B19`, `0x004F8B64`, and `0x004F8B6F`.
Original call displacements were read from the unmodified original function;
no comparison-field-derived relocation guesses were used. The canonical
result reports `exact`, 145 compared bytes, zero differences, with the
compiler and target hashes recorded in the object receipt.

## Focused downstream regression

Adding one real Player member declaration and one narrow external Renderer
method extends two shared include closures. Prior canonical compiler receipts
identify exactly **21 existing source providers** affected by
`src/Player.hpp` or `src/AnimationRuntimeOwner.hpp`. The new
`src/PlayerDraw.cpp` is one additional provider. Across five serialized,
low-priority cold replay batches, **57/57 strict native units across 22
providers** pass (56 previously accepted units and the one new draw root).
Private exact logs are `.analysis/core301-replay-batch0.log` through
`.analysis/core301-replay-batch4.log`; their immutable source lists and
header provenance are in `.analysis/core301-replay-sources.json`.

Two unrelated previously exact objects renumbered *only compiler-private*
string symbols due to the new header declarations: Bullet cancel's
`$SG183023` -> `$SG183024` (native `0x0056FD14` at original `+0xC0`),
and the Player constructor's `$SG82055` -> `$SG82056` (native
`0x00572BB8` at original `+0x2FC`). Each relocation's original offset,
type and independently established target are unchanged; only the manifest's
compiler-local symbol spelling was updated. All original code and data bytes
remained strict exact. No whole-graph cold replay was run.

This proof establishes one entire function's exact native codegen and
relocations, **not** whole-executable closure, finished Renderer
implementation, or runtime equivalence of the game.

## CORE/EXACT-303: complete 13-byte Player draw callback

Fresh target-attested Ghidra and independent complete-target byte decode
identify the entire original callback at `0x004FEFB0..0x004FEFBC`, SHA-256
`8b57d3c9efbbc40fd8ba3d0379dbb2ce0e6f0fe8fc936348bbb48e885f06f460`.
The full six-instruction body loads the pointer argument into `ECX` and
calls the independently exact `Player::draw` at `0x004F8AF0`; its native
`EAX` value is *left untouched* and forwarded to the original caller.
Ghidra's tentative `void` annotation is therefore not authoritative.

The complete natural C++ source is `src/PlayerDrawCallback.cpp` returning
`std::int32_t`; choosing an `int` return reflects the original code, whereas
an otherwise identical `void` wrapper adds a compiler NOP absent from the
native function. One independently observed native `REL32` call relocation
at `+0x07` targets `0x004F8AF0`. The strictly fresh locked-MSVC 19.44 x86
canonical `player_draw_callback` unit reports **13/13 exact bytes** and no
differences. Exactly **one** new object/provider and **one** strict unit
were cold rebuilt and tested; no existing exact source or shared header was
changed in this CORE/EXACT-303 revision. Callback registration and any
associated task lifetime remain unresolved.
