# Animation VM opcode leaves — eight complete natural C++ reconstructions

Target: Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The 39,470-byte `Animation::update` at `0x0042B5D0` remains the active VM
Boss. These eight independent leaf functions were recovered from its
original opcode dispatch and rebuilt as ordinary typed C++ methods;
none is an assembly or padding substitute.

## Recovered opcode edges

| Original address | Bytes | Natural C++ method | VM relationship |
|---:|---:|---|---|
| `0x00429150` | 43 | `Color3(red, green, blue)` | Opcode `0x55` builds B/G/R three-byte color values |
| `0x00429280` | 29 | `Timer::set_from_current` | VM jump/reset paths copy the current frame through `Timer::set` |
| `0x00438AE0` | 24 | `Interpolation<Angle>::set_end` | Opcode `0x53` Angle interpolation endpoint |
| `0x00438B50` | 24 | `Interpolation<Angle>::set_tangent_end` | Opcode `0x53` Angle interpolation end tangent |
| `0x00439440` | 23 | `Interpolation<Angle>::set_start` | Opcode `0x53` Angle interpolation start |
| `0x004394B0` | 24 | `Interpolation<Angle>::set_tangent_start` | Opcode `0x53` Angle interpolation start tangent |
| `0x00439280` | 76 | `Animation::set_rotation_speed` | Opcode `0x57` writes angular-rate vector_44 and dirty flag `0x80000` |
| `0x00439390` | 62 | `Animation::set_scale_speed` | Opcode `0x58` writes scale-rate vector_60 and dirty flag `0x80000` |

The `Color3` constructor's original arguments are red/green/blue, while
its maintained value stores blue/green/red. `Timer::set_from_current` copies
only `source.current`, deliberately using the destination's original
`Timer::set` protocol rather than copying Timer flags/fraction wholesale.
The Angle methods are existing `Interpolation<T>` template members. The two
Animation setters feed the exact vector lanes read by the maintained
`Animation::update_motion` method.

## Independent original PE proof and candidate replay

`scripts/verify-animation-vm-leaves-native.py` checks each original function
body SHA-256, exact instruction coverage, return convention, all original
E8 targets and physical HIGHLOW fields, then compares the complete candidate
COFF contribution against the original PE. Seven leaves are pure code;
the Timer helper has one genuine `REL32 +0x12 -> 0x00423F80` to `Timer::set`.
All eight candidates are whole-function strict exact:

- 8/8 complete functions, **305/305 native bytes**.
- 301/301 ordinary bytes plus the Timer's 4-byte relocation field.
- Zero ordinary-byte differences; all original relocation targets solve.
- No handwritten assembly, NOPs, padding, dummy accesses, or alternate ABI
  views are used.

```bash
scripts/repo-python scripts/probe-animation-vm-leaves.py
scripts/repo-python scripts/replay-exact-units.py --source src/Color3.cpp
scripts/repo-python scripts/replay-exact-units.py --source src/Timer.cpp
scripts/repo-python scripts/replay-exact-units.py --source src/Interpolation.cpp
scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParameters.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## Boss boundary

These leaves make real VM opcode semantics reusable in natural source, but
they do **not** claim `Animation::update` itself exact. Its original body is
39,470 bytes, 8,559 decoded i386 instructions, 505 E8 calls to 81 distinct
targets, and 55 physical PE HIGHLOW relocation fields. The dispatcher still
contains 161 explicit opcode cases (values 0 through `0xA0`, including
unimplemented holes). The main Boss remains the next major reconstruction.
