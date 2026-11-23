# Enemy ECL opcode 714 — virtual Laser parameter flag

**CORE/RECON-1268.** Enemy opcode 714 is now a natural C++ inline source
fragment in `src/EnemyStateLaserOpcode.cpp`, wired into the production
`EnemyState::execute_opcode()` dispatcher and exercised by the maintained
ASan/UBSan root host. The 41,967-byte parent remains **NONEXACT**; this work
claims only the recovered case and its actual virtual leaves.

## Locked original branch

The Japanese TH20 1.00a selector maps opcode 714 to index **166**, whose
original branch is `0x004952D6..0x0049535E`: **136 bytes / 29 x86 instructions /
four direct E8 calls and one indirect virtual call**. Its SHA-256 is:

`1897fa2091dedde2fa20479d159c7f646dbf5933a24fdcbb3d5b4f320a5d426e`

The ordered direct targets are:

1. `0x0041CA90` — capture `Context::laser_controller()`;
2. `0x004AB080` — read integer handle operand 0;
3. `0x00498FF0` — `LaserController::find_laser(handle)`;
4. `0x004AB080` — read integer flag operand 1, only after a hit.

On a successful lookup the native branch loads the Laser vtable pointer,
then captures slot `+0x0C` at `0x00495329`. It reads operand 1 at
`0x0049533A`, then calls the previously captured function pointer at
`0x00495352`. The missing-handle branch skips both the second operand and the
virtual call. The case rejoins the original dispatcher epilogue at
`0x004963DF`.

## Four real vtable targets

The native Laser vtables all use the same slot index for this virtual:

| Native vtable | Slot `+0x0C` | Meaning |
| --- | ---: | --- |
| `0x00571148` | `0x0040EC90` | base no-op |
| `0x00571214` | `0x0040EC90` | base no-op |
| `0x005712E8` | `0x0040EC90` | base no-op |
| `0x00571374` | `0x004D7D20` | `LaserBeamInf` override |

The three non-Beam types intentionally do nothing for this flag command. Their
13-byte no-op body at `0x0040EC90` is physically folded with the already
tracked `std::_Iterator_base0::_Adopt` contribution. It is not registered as a
second function or credited twice.

The type-3 Beam override at `0x004D7D20` is 42 bytes / 15 instructions. It
updates only bit zero of `LaserBeamInf::parameters.flags`, preserving every
other flag bit. The native layout is explicit: `LaserBeamInf::parameters`
starts at `+0x6F8`, and `LaserType3Parameters::flags` is at `+0x38`, hence the
actual Laser field is `+0x730`. The i386 layout now has a corresponding
`static_assert`.

The implementation in `src/LaserCommandMethods.cpp` is ordinary C++:

```cpp
void LaserBeamInf::set_parameter_flag(std::uint32_t value) {
    parameters.flags = (value & 1u) | (parameters.flags & ~1u);
}
```

The locked MSVC COFF body is **39/42 bytes matching**. The three differing
bytes are register-allocation choices in the OR destination and final store;
the complete body, field offset and bit-mask behavior are reconstructed, but
this override is deliberately classified as `reconstructed`, not strict
exact. No assembly or padding is used. The base no-op's folded physical body
also receives no duplicate Laser exact credit.

## Root behavior and compiler ordering

The production helper preserves the native sequence:

- capture the current Context's LaserController;
- read integer operand 0 and resolve the handle through the real intrusive
  `LaserController::find_laser`;
- if missing, return without reading operand 1;
- if found, capture the virtual function at slot `+0x0C` before reading
  operand 1, then invoke that captured function with the integer value.

The root fixture uses actual `LaserBeamInf` instances and a second test vtable.
During operand-1 evaluation it temporarily changes the selected Laser's
vtable and retargets the Enemy Context. The call still reaches the original
captured Beam setter, updates only flag bit zero, and does not dispatch through
the replacement vtable. Separate cases verify that a missing handle suppresses
operand 1 and that an operand-1 exception leaves the flags untouched.

The independent verifier
[`verify-enemy-laser-mutation-opcodes-source.py`](../scripts/verify-enemy-laser-mutation-opcodes-source.py)
pins the PE identity, selector and pointer table, full branch hash/instruction
extent, four E8 targets, indirect call site, all four vtable slot targets,
base/Beam leaf hashes, 24 ordered COFF relocations and both virtual calls. The
maintained root suite runs the real production helper under ASan/UBSan. The
six separate 705–710 setter leaves still replay **172/172 bytes in 6/6 strict
units**; the Beam flag override is kept outside that exact set.

See also the [705–710 mutation frontier](ENEMY_41967_705_710_LASER_MUTATIONS_SOURCE_FRONTIER.md)
and [six-setter exactness frontier](LASER_MUTATION_SETTER_LEAVES_EXACT.md).
