# LaserController::find_laser — native 230-byte leaf

**CORE/RECON-1265.** The natural C++ implementation of the shared Laser
handle lookup at `0x00498FF0` is now linked into the maintained Enemy root
host and covered by native PE, i386 COFF, and ASan/UBSan regression checks.
This is a real leaf used by Enemy ECL opcodes 704–710; it is not a synthetic
replacement and does not claim that all seven parent opcode branches are
restored. Opcode 704 now has a separate inline source frontier; siblings
705–710 remain open.

## Locked native evidence

The original Japanese 1.00a PE body is exactly **230 bytes / 70 x86
instructions / 11 direct E8 calls**, from `0x00498FF0` through the `ret` at
`0x004990D5`. Its SHA-256 is:

`0b577415aa056a83ebb14cc6fde44c32a3524368450ee6951ae6ee0ae0770d1f`

The complete ordered call-site map is:

| Native call site | Target | Recovered operation |
| --- | --- | --- |
| `0x00499029` | `0x0040C080` | zero the 8-byte iterator storage |
| `0x00499035` | `0x00412280` | construct `active.begin()` |
| `0x00499044` | `0x00412540` | obtain the null end iterator |
| `0x00499051` | `0x00411C30` | advance the intrusive iterator |
| `0x0049905E` | `0x00411BB0` | compare iterator against end |
| `0x0049906D` | `0x0040C300` | get the current intrusive link |
| `0x00499078` | `0x0040C300` | read its `Laser*` for handle comparison |
| `0x0049908B` | `0x0040C300` | read the `Laser*` again for the return value |
| `0x0049909D` | `0x00411B00` | destroy iterator on a hit |
| `0x004990B3` | `0x00411B00` | destroy iterator on a miss |
| `0x004990CB` | `0x005429EE` | security-cookie check |

The `LaserController` active list is at `+0x10`; the compared handle is at
`Laser+0x8C`. The original compressed selector table maps opcodes 704–710 to
indexes 156–162, and each of those seven native cases contains a direct call
to `0x00498FF0`. Their call sites are independently checked at
`0x0049500A`, `0x004950BA`, `0x00495159`, `0x004951C6`, `0x00495233`,
`0x004952A0`, and `0x00494F89`.

## Natural C++ and important ordering

`src/LaserControllerFindLaser.cpp` uses the actual `LaserController::active`
`IntrusiveList<Laser>` and the existing `IntrusiveIterator`/`IntrusiveLink`
methods. It reads the node's `handle` at the original `+0x8C` offset and
returns null when the list is exhausted.

One non-obvious native detail is preserved: the matching path calls
`link->node_value()` twice. The first call supplies the `+0x8C` comparison;
the second call supplies the returned `Laser*`. Caching the first pointer
would silently remove an original native call and is deliberately avoided.
The iterator is destroyed on both match and miss paths.

The i386 COFF object preserves the ordered semantic relocation sequence:
iterator zero-init, list begin/end, advance/differs, iterator get, two separate
`node_value` calls, both iterator destructor paths, and the security-cookie
check. The handle load/compare remains at `+0x8C`.

## Root-host coverage and limits

The maintained root host executes the production leaf against the real
intrusive list and `DispatchTestLaser` instances. It checks empty-list lookup,
a later-element hit, a missing handle, and duplicate handles where the first
list entry wins. The focused root verifier links the source under ASan/UBSan
and compiles its locked-profile i386 COFF object.

This restores the shared leaf and is now exercised by the separately
recovered inline Enemy opcode-704 position-update fragment (176B/37
instructions/six direct E8 calls plus a conditional `set_position` vcall).
See [the opcode-704 source frontier](ENEMY_41967_704_LASER_POSITION_LOOKUP_SOURCE_FRONTIER.md).
Sibling caller fragments 705–710 remain open, and the 41,967-byte
`EnemyState::execute_opcode` parent remains **NONEXACT**. No parent-byte
credit is claimed and no full cold replay was run.
