# CORE/EXACT-308 — original 73-byte Session/PlayerTable clamp and Player reset flags

Immutable native oracle: Japanese TH20 v1.00a Steamless original SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Independent original instruction decode, target-attested Ghidra exploration,
original direct-call destinations and new locked-MSVC x86 C++20 build
establish **three additional complete game-owned methods** in the original
966-byte Player reset caller's state/mode chain. All three complete native
functions now compile to zero-difference strict exact matches in
`src/PlayerResetStateAccessors.cpp`.

| Complete original | Native address | Native bytes | SHA-256 of original interval |
| --- | --- | ---: | --- |
| `PlayerTable::clamped_field_1e4()` | `0x004C5DB0` | **73** | `10372c6ed125c0f5685136b56f1a0b71373ee5eb4cf4b56657e84388719a67d4` |
| `Session::flag0_value() const` | `0x00474E00` | **20** | `03cf698291dbd157903f664dbc79c3307335b7ea367ecde597ba039fd376f2fa` |
| `Player::clear_entity_flag2()` | `0x004790C0` | **26** | `0edfaa204b27b97b27cc0c0e0fc09677956cd40feff15832d584db934874f058` |

New strict coverage: **119 complete native bytes** and three independent
canonical units. The original 966-byte `Player` initializer
`0x004FB450` calls **all three**, and also the previously exact 237-byte
option-animation clear and 19/29/19-byte Player state accessors.

## Correction: native 0x00471170 is a clamp dependency, not a search

The provisional Ghidra function name at `0x00471170` resembles a search or
`_Find_unchecked<>`, and Ghidra's 73-byte caller decompilation propagated
that uncertain label. That interpretation was **not** accepted as fact.
Direct original code at `0x004C5DB0` constructs actual integer locals `0`
and `1`, passes their references plus `&PlayerTable::field_1e4` into the
callee, copies the returned `int` reference to the same field, then returns
the resulting scalar value. The original **entire** function and its sole
native `REL32` at original `+0x2A -> 0x00471170` are reproduced by
natural

`field_1e4 = std::clamp(field_1e4, 0, 1); return field_1e4;`

with the pinned compiler, whose COFF relocation identifies the actual
`std::clamp<int>` template instantiation. Strict comparison matches all
**69 nonrelocation bytes** and the independently attested native call
field, for 73/73 original bytes. This validates the caller and the
original callee's ABI/name at the call site; the separate 0x00471170
complete callee body has not been newly accepted or double counted.

`Session::flag0_value` returns the low bit of the true `SessionFlags`
word at `Session+0x6C`. `Player::clear_entity_flag2` clears exactly bit
2 of the true `Player::entity_flags` at `Player+0x14`, without disturbing
any other bit. Both are entire independent 20B/26B routines with no
relocations and no fabricated byte offsets or replaced original paths.

## Entire affected-source verification, no full cold replay

Adding the true member interfaces to `src/Player.hpp` and
`src/Session.hpp` changes the include closure of **35 existing canonical
source objects**. The one new provider yields **36 affected cold objects**
and **195/195 strict exact units**, recompiled and strictly compared in
eight serialized, low-priority batches. This is **195/1,093 configured
units**, not a repository-wide cold replay. All previously accepted native
methods under the actual include closure stayed exactly matched.

Because MSVC numbers some internal `$SG` string symbols based on declarations
in included headers, **15 compiler-private symbol identities across
14 existing units** changed. No underlying native string, original
relocation offset/type, independently recorded target address, complete
COFF extent or comparable code bytes changed. The ignored audit
`.analysis/core308-reconciled-private-symbols.json` records each old/new
symbol, native relocation offset and unchanged original target. The private
`core308-reconcile-sg.py` verifier refused any altered relocation layout,
non-`$SG` identity, stale compiler object/receipt, different manifest target
or nonstructural-exact original body before updating a manifest identity.
Every affected unit was then recompiled and accepted again by the
**unmodified strict canonical comparator**. Its eight focused proof logs
are `.analysis/core308-replay-batch0.log` through `batch7.log`; the exact
source selection is derived from canonical receipt header hashes and saved
in `.analysis/core308-replay-sources.json`.

The full native Player reset boss at `0x004FB450` (966B), its 1,518-byte
option setup callee at `0x004FACA0`, Bullet 1,404B command-11 and 273B
single-group draw are **still nonexact**; the helper exact proofs do not
imply complete runtime startup, game linkage, or those parents' exactness.
