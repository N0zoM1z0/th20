# Enemy opcode 575 and the genuine Player flag setter (CORE/EXACT-166)

The single fixed reconstruction target remains the Japanese 1.00a Steamless TH20
PE32, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This batch follows the **whole** 41,967-byte Enemy dispatcher rather than
counting a case fragment as an independent complete function. The dispatcher
and its jump tables/EH are **not** accepted as an exact unit.

## Independently verified native dependency

The native opcode 575 head starts at `0x004956EC`. Its control flow calls
`player(0)` at `0x004956EE`, saves that live receiver, then calls the current
`EnemyState::integer_argument(0)` at `0x00495704`, and finally invokes the
Player member at `0x0049C390` with the argument's complete 32-bit word. The
result of the operand read does **not** change which Player receives the call.
The common dispatcher exit follows. These concrete orderings are from the
locked original instruction listing and bounded call inventory; no private
source-draft assumption supplies the receiver or ABI.

The complete function at `0x0049C390` is 42 bytes, has an x86 thiscall
`RET 4`, and contains **zero relocations**. Its native member receiver reads
and writes the word at Player+0x14. Independently established object layout
places the actual `Player::entity_flags` there: the Player's `TaskInfo` base is
16 bytes, then `state` is four bytes. The native masks the argument to bit 0,
shifts by 10, clears only the previous bit 10, and combines the rest untouched.
There is no boolean clamping or additional application state change.

The recovered typed view is a four-byte `PlayerWordFlags` union containing the
original full `bits` storage and a **10/1/21** bitfield split. Natural
`entity_flags.fields.bit_10 = value` yields the exact 42 bytes under locked
MSVC x86 `C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
Two direct full-word mask/order rewrites did **not** match despite equivalent
logical state (initially 23/42, then 39/42); that is why this source uses the
genuine bitfield owner rather than a code-shaping temporary or inline assembly.
The full compiler contribution and all 42 native bytes match with no ignored
relocation fields, no trimmed tail, and no padding.

## Affected source and semantic validation

The Player declaration, its actual source, and PlayerWordFlags storage header
change together. Authentic compiler include closures identify **6 physical
objects and 36 previously exact units** affected. Each is cold rebuilt into
`build/core166-canonical/` without overwriting the originals. All 36 old units
plus this new 42-byte unit replay exactly (**37/37**, 6,521 complete compared
bytes). The Player constructor's generated local label for `initialize
PlayerInf\n` changes from `$SG81964` to `$SG81994`; old/new COFF literal bytes,
including NUL and all 22 bytes, match and the original PE string matches at
the independently established `0x00572B78`. This is a symbol relabel, not a
change to the destination or decoded program text. All six old objects and six
original receipts preserve their original SHA-256; 158 unchanged object receipts
also remain valid. Evidence receipts are in private
`.analysis/core166-player-scope.json`, `core166-player-literal-reconciliation.json`
and `core166-player-final-proof.json`.

The production `Player` and its complete SHT/resource protocol fixture exercise
all 24 combinations of 4 existing flag words and 6 input words, checking
exact preservation of unrelated bits, including sign/high bits. The existing
resource load and damage-cap cases still pass. Its original Player destructor,
activation and resource/OS startup remain explicit fixture boundaries. This is
portable O2/UBSan evidence, not native full-game execution.

## Remaining large root

The 41,967-byte Enemy dispatcher at `0x0048C010` is still absent from
production source and has no canonical unit. Its compressed primary index,
174 heads, four nested rank tables, shared tails, native EH and full COFF
contribution must be reconciled as a **single complete root**. Opcode 575 is
now a verified constituent path and its actual callee is exact; this does
not grant partial root bytes. Opcodes 502/503 and remaining animation, Stage,
audio and other real owner dependencies are still open. Refer to
[whole-root layout](CORE_ENEMY_DISPATCH_LAYOUT.md) and
[rank/control history](ENEMY_RANK_CONTROL_RECONSTRUCTION.md).
