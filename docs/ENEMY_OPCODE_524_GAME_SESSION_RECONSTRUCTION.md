# Enemy opcode 524: native GameController / PlayerTable level propagation (CORE/EXACT-172)

The only comparison target is Japanese TH20 v1.00a Steamless PE32, original
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete **41,967-byte** Enemy opcode dispatcher at `0x0048C010` remains
**unimplemented and nonexact**. This batch independently reconstructs two of
its actual full native dependencies, not copied fragments of the main root.

## Original native opcode 524 and genuine global ownership

The opcode head is `0x00495727`. The complete native sequence reads
`EnemyState::integer_argument(0)` through `0x004AB080`, caches its *full*
32-bit result, then reads the published GameController pointer at **0x005BA828**
and calls `0x0049C940` with the cached argument. The pointer at 0x005BA828 is
the separately established GameInf owner publication from the native
factory at `0x004BEC70`, not the neighboring Session table or a fabricated
Stage service. The root then writes the original argument to
`EnemyState::field_280` and resets `EnemyState::field_284` to **zero**, in
that order. There is no extra operand read and no null owner guard in this
native interval. The original Game startup/allocator remains separate work.

The native code inside `0x0049C940` reveals its second genuine owner:
`ECX = 0x005BA5F0`. Independent Session storage and startup evidence give
`session` at **0x005BA568**, with `Session::table` at **+0x88**; thus the
native pointer is exactly the existing `session.table`. Its outgoing call
`0x0049C970` writes the signed input at `PlayerTable+0x1FC` and clamps the
stored value to **0 through 999**. Afterwards `0x0049C940` writes the
**unchanged** input word at `GameController+0x34`, the existing typed
`GameController::field_34`. The two values intentionally differ for negatives,
values above 999, and high-bit words. They cannot be merged into one facade
or one clamped Game field.

## Complete pinned-compiler function matches

| Original native entry | Maintained real member | Complete native bytes | Independently mapped relocations |
| --- | --- | ---: | ---: |
| `0x0049C970` | `PlayerTable::set_field_1fc(int32_t)` | **78/78** | 1 |
| `0x0049C940` | `GameController::set_field_34(uint32_t)` | **36/36** | 2 |

The first body naturally stores the parameter, then evaluates
`field_1fc = std::clamp(field_1fc, 0, 999)`, using the pre-existing exact
`std::clamp<int>` target at `0x00471170`. Three other plausible forms were
examined: clamping the incoming value directly, using an explicit reference,
or preserving a local reference. They emitted **60**, **75**, and **84**
bytes rather than the exact 78-byte original. The second native body is the
natural `session.table.set_field_1fc(static_cast<int32_t>(value)); field_34 =
value;`, using the genuine process Session global relocation at `0x005BA568`
with a **+0x88** COFF addend and the independently verified first callee at
`0x0049C970`. This is not a guessed new global. All 114 bytes and all three
relocations match the locked native code under the established x86 MSVC
19.44.35211 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
source profile. Real x86 class offsets are checked at compile time.

Both original C++ symbol spellings remain inferred; functional widths and
native member receiver identities come from independently correlated
constructors, factory publication, consumer calls and complete function bytes.

## Whole-provider exactness and portable behavior

Adding the two typed declarations affects the original compiler include
closures of **19** canonical objects and **147 previously exact functions**.
All nineteen provider objects were cold-built, serially and at reduced CPU
priority, into `build/core172-canonical/`. The 147 previous units and two
new complete units replay **149/149 strict exact**, totaling **18,875 full
compared bytes**. Fourteen MSVC-generated local string symbols shifted; each
was mapped only after checking byte-for-byte identical original/fresh COFF
literal extents and complete original PE literal bytes, including all native
section contents beyond NUL where present. None were guessed from target
relocation fields. All **38** original object/receipt hashes remain unchanged,
with **145** additional unaffected canonical receipts valid.

The unchanged native target and protected old/new products are indexed in
private `.analysis/core172-game-session-scope.json`,
`core172-literal-reconciliation.json`, `core172-strict-replay.json` and
`core172-final-exact-proof.json`.

The actual GameController + Session + PlayerTable host test executes the
production methods across **40 paired input/initial-state cases**, checking
Game's complete unmodified original input, PlayerTable's independently
clamped signed value, and snapshots of **both complete owner images** to
reject unrelated writes. The existing Session test additionally exercises
the actual setter across 14 signed boundaries with complete Session-image
preservation. Both focused O2/UBSan tests pass. Their host x64 type layouts
are not substituted for the verified native x86 offsets; these are separate
ABI and semantic claims.

## Outstanding complete root and OS boundaries

The complete `EnemyState::execute_opcode` control flow still needs its full
41,967-byte source body, all five pointer tables, its compressed index,
shared case exits, four rank tables, compiler-owned data/alignment and EH.
Its own opcode 524 case must be integrated and tested separately in the private
whole-root host, including cached operand order, the two distinct global
owners, and `field_280`/`field_284` write ordering. These two complete
leaf/callee matches contribute no partial root exactness. Game startup,
resource/graphics ownership and linked playable execution remain open.
