# Enemy phase producer investigation

## CORE146 investigation boundary

This unfinished investigation continues the whole EnemyState opcode dispatcher
at 0x48C010 beyond the private movement draft. It accepts no production source,
semantic reconstruction, origin classification or exact unit. The current
acceptance graph remains the CORE/EXACT-145 graph recorded in the
[handoff](RE_HANDOFF.md). Raw exports and probe sources remain private.

The private catalog `.analysis/core146-state-family-catalog.json` covers 75
effective values in 500..575, excluding default value 569, across 71 primary
heads. Complete implementation still needs genuine HUD, laser and other receiver
owners; reference service adapters do not establish those interfaces.

## Native producer observations

The attested export `.analysis/core146-phase-producers-native.asm` records two
complete candidate bodies:

| Entry | Body bytes | Observed receiver and behavior |
| --- | ---: | --- |
| 0x4AB650 | 301 | Enemy receiver; grow phases, write life, then conditionally write time and names |
| 0x4AB780 | 154 | Enemy receiver; grow phases, then replace or clear the timeout name |

Both access the vector at Enemy+0x340, corresponding to the maintained
EnemyState+0x2B8 subobject at Enemy+0x88. The maintained EnemyPhase is 136 bytes:
two 32-bit integers followed by two independent 64-byte names. These are Enemy
producer candidates, not EnemyState member candidates.

The first body grows the vector when its size is less than the unsigned 32-bit
`index + 1`, then writes life. Negative life preserves the existing time and both
names. Otherwise it writes time and either copies the same supplied name into
both arrays through `strcpy_s`, or clears only each array's first byte.

The second body has an asymmetric access contract: a non-null name uses checked
vector access at 0x4AA160 before copying into the timeout array, while a null
name uses unchecked access at 0x48BD40 and clears its first byte. Preserve that
distinction and the observed unsigned arithmetic; extra bounds or overflow
guards have not been established.

The observed storage dependencies are size at 0x4ABA00, resize at 0x4AB570,
unchecked access at 0x48BD40 and checked access at 0x4AA160. Native copy calls
target the independently existing `strcpy_s` anchor at 0x548610. This navigation
does not yet supply complete canonical relocation identities for the producers.

## Compiler result and unresolved construction

The retained private source `.analysis/core146-phase/Phase.cpp` proposes
`Enemy::configure_phase` and `Enemy::configure_timeout`, with local header copies.
Its MSVC 19.44.35211 x86 profile is C++20, /Od, /Ob0, /GS, /Gy, /Zl, SSE2,
/fp:precise, /sdl and /EHsc. `build/core146-probes/Phase.obj` and its authentic
receipt remain protected.

`.analysis/core146-phase-probe-diagnostic.json` reports complete 301- and 154-byte
producer bodies with no differences outside relocation fields. This is a
structural diagnostic, not strict exact replay or evidence for every dependency.

The probe also adds a provisional `EnemyPhase` constructor that initializes life
and time to -1. Its complete 33-byte emitted body has no full-byte occurrence in
the locked PE, as recorded in
`.analysis/core146-phase-constructor-independent.json`. That result does not
establish a replacement constructor or native default values. Do not copy this
guess into the maintained aggregate in `src/EnemyState.hpp`.

## Resume point and protected evidence

Trace actual value construction before editing production declarations. Existing
read-only exports follow resize through 0x4A1F80, uninitialized construction at
0x4A2380, backout emplacement at 0x4A19B0 and allocator construction at 0x4A25D0
and 0x4A25F0. The last export shows a call from 0x4A2623 to 0x4A2470; its complete
construction behavior remains unresolved in this investigation.

Reuse these private exports rather than repeating unchanged queries:

- `core146-phase-storage-native.asm`
- `core146-phase-growth-native.asm`
- `core146-phase-value-construction-native.asm`
- `core146-phase-emplace-native.asm`
- `core146-phase-allocator-native.asm`
- `core146-phase-construct-chain.asm`

All filenames above are relative to `.analysis/`. Preserve their associated
Ghidra logs, the producer export, catalog, compiler log, diagnostics, local probe
inputs and object receipt. After establishing construction, use natural shared
source, independent relocation identities and fresh affected builds before any
acceptance. The whole dispatcher's default, tables, EH and full compiler extent
remain open under [whole-root evidence](CORE_ENEMY_DISPATCH_LAYOUT.md).
