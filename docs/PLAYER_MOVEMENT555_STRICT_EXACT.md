# Exact Player movement and playfield clamp

`Player::apply_move_delta` at `0x004FFA10` now strictly matches its complete
555-byte, 135-instruction native body. Direct integer assignment of the
recomputed Y bound in MSVC C++14 mode restores the native ESI lifetime;
separate world-coordinate float values restore the final spill/call order.
All 17 call fields and ten absolute data fields match through independent
canonical anchors. This adds one authored function and 555 exact bytes.

The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete native body has SHA-256
`eef3217c41849ecd607fb36bf0d760b83cddaee6a97050c845bbf751b9bef1bf`.
The canonical unit is `player_apply_move_delta_555` in
[the manifest](../config/match-units.toml), built from
[PlayerMovement.cpp](../src/PlayerMovement.cpp) with locked MSVC
19.44.35211 x86:

```text
/std:c++14 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc
```

## Source and compiler finding

The previous C++20 source emitted 561B/136 instructions. A complete audit
accounted for every difference: a five-byte float spill, a one-byte-longer
memory-source conversion, a four-byte larger frame, and four displaced
world-coordinate spill/reload operands. All eight internal branches,
17 call roles and ten data roles already agreed. The old description of
an extra six-byte MOVSS was inaccurate: the six-byte increase was **5 + 1**.

Removing the named upper float alone under C++20 emits 559B/135, spilling
the converted integer across `fixed_position_ref()`. C++14 instead emits
the original `cvttss2si esi,xmm0`, preserving that integer in ESI through
the getter. With direct final coordinate assignments it produces 555B,
but loads ECX before each float spill. Naming the two real world-coordinate
values restores the original spill → receiver → call → reload order without
changing their frame locations. Separate scopes produce the same exact body.
The same source/header control under C++20 remains 559B.

The calculation still reads the clock twice, copies all three vector lanes
when required, applies wrapping 32-bit fixed-coordinate additions and clamps
only in movement mode zero. The Y upper bound is recomputed after its
comparison. Both final divides retain the shared `native_128` data owner.
The mode match is specific to this unit; the original game's global language
mode remains unproven.

Earlier reference/pointer getter controls, `noexcept`, C++17, `/Ob1`, `/Ot`,
`long` conversion and a shared inline bound computation did not reproduce
the native body. `/Os` also changed the vector-copy protocol. Reuse these
controls rather than repeating that search.

## Complete comparison and affected providers

The fresh canonical object and receipt are
`build/gpt61-player-movement-canonical/PlayerMovement.obj` and
`PlayerMovement.receipt.json`. Strict replay compares all 555 bytes, ending
at the original `ret 8`. There are no owned tables or EH contributions.
All ten DIR32 fields agree with original PE HIGHLOW positions. Call/data
addresses come from existing canonical units and relocation bindings;
`native_16` uses the established `native_sixteen` alias at `0x0056CD90`,
whose actual four bytes encode 16.0f. No address is solved from its compared
field.

[Player.hpp](../src/Player.hpp) only needs an AnimationFile pointer, so its
unnecessary complete PMR-dependent definition was replaced by a forward
declaration. Consumers calling AnimationFile methods include that definition
directly. The captured header closure contains **91 existing units across
35 former providers**. Their complete affected replay passed. It exposed
an old routing error: the 88B PlayerRecord and 55B Session score methods
already lived in `SessionScore.cpp`, but their units still named
`DamageQueryProtocol.cpp`. Routing them to their actual maintained owner
restores both strict comparisons and adds no credit.

Including that corrected owner and the new movement unit, this checkpoint
covers **92/92 units from 37 fresh providers**. Old canonical objects and
receipts are preserved. The separate Player main-frame and WeaponStone
update consumers remain NONEXACT. Fresh comparisons preserve their complete
3,114B/104-relocation and 1,023B/49-relocation contributions respectively,
including actual literal payloads when compiler-local labels differ.

The enclosing [3,111B Player main frame](PLAYER_MAIN3111_STRICT_EXACT.md)
has since become independently whole strict exact under C++20. Its empty
Timer condition resolves the register frontier without changing this child.
