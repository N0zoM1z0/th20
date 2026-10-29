# CORE/RECON-792 — all 49 original Animation draw Boss mode paths independently recovered from native x86

> **Subsequent CORE/RECON-800:** The whole 5,993B Animation draw parent now has one maintained, compilable 49-mode C++ candidate and a 123/123 source/native E8 target-role census. It is **SOURCE-PRESENT but NONEXACT** (5,141 actual compiled instruction bytes vs 5,993 original). [Current whole-parent evidence](ANIMATION_DRAW_BOSS_5993_TYPED_49_MODE_PARENT_FRONTIER.md). Earlier SOURCE-ABSENT labels below were accurate only at this dated checkpoint.

The selected original comparison PE is Japanese TH20 v1.00a Steamless,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **complete original 5,993-byte /1,501-x86-instruction**
`0x00443880` Animation draw Boss remains **SOURCE-ABSENT and NONEXACT**.
This evidence checkpoint is a materially deeper reconstruction of its
**entire two-stage 49-mode dispatch and per-mode true native E8 routing**,
not a claim that either the 5,993B body or its 29 still-incomplete renderer
callees are compiled from exact maintained C++.

## Re-examined immutable original dispatch structure

The locked original function branches on the `Animation+0x498` byte after
testing its actual draw-enabled bit, original optional virtual callback,
real `+0x49A` state and retirement flag `+0x570`. It guards modes against
`0x30` and performs one indirect jump at native `0x0044391F` through the
**49-entry main table** `0x00444FEC`. Its original selected shared branch
for modes `0x10..0x16` and `0x1A..0x2E` obtains real geometry state,
then subtracts `0x10` and dispatches through the **31-entry nested table**
`0x004450B0` at native `0x00443D64`. Both tables have individually
original-PE-attested `IMAGE_REL_BASED_HIGHLOW` fields and targets that
land on real original instruction heads: **49 +31 =80** original data
pointer fields, in addition to **32** physical original HIGHLOW fields
inside the executable function body. Its native after-body alignment is
exactly 3 bytes `0F 1F 00`. These have not been credited as new functions.

A new source-independent CFG walker in
`scripts/verify-animation-draw-boss-native.py` starts from **each** real
49-entry main target, recursively follows the original fallthrough,
conditional jumps and direct jumps, and resolves the **second indirect
jump using the same mode's genuine nested PE table entry**. It reads all
native E8 displacement bytes to find actual action call sites and physical
destinations, then cross-checks a maintained machine-readable
[49-row mapping](../config/animation-draw-boss-mode-e8.csv), including
each path's reached instruction head count. This is not lifted Ghidra
pseudocode and does not require an unsupported historical class name.
It explores both sides of non-mode conditionals, so a listed E8 is **reachable
on at least one path**, not guaranteed executed under every runtime state.

The full verified physical facts:

- **49/49** mode entries have a validated original main jump-table target,
  **17 distinct** original main code heads.
- **28 modes** actually reach the second original jump and select a nested
  target; the 31-entry nested table has **29 distinct** original code heads.
  Modes **23, 24, 25** are in the numeric nested range but bypass the second
  switch because the primary table selects a different path.
- **47 of the 49** mode paths have one reachable E8 to a mode-specific
  render/action function; modes **10 and 23** go to default without one.
  The 47 modes use **43 distinct E8 instruction sites** and **29 distinct
  native callee heads**. Do not confuse those 43 physical mode-call sites
  with the entire Boss's separately verified **123 native direct E8 sites /
  43 unique total call destinations**.
- The original **modes 9, 12, 13, 14** share the *same* physical E8 at
  `0x00443B01 →0x00445350`; modes **24, 25** likewise share the same
  physical E8 at `0x00443B4F →0x00443020`. Thus neither 47 route occurrences
  nor multiple aliases to one function should be counted as distinct
  physical function bodies or original .text byte credit.
- Modes **47/48** share the same eventual callee `0x00443020` but have
  **different native call sites** (`0x00443B76` /`0x00443B9D`), with the
  second path's separately verified Graphics state transition.

## Original complete 49-mode main + nested + reachable call-site map

Every cell below is an actual address in the locked original PE. A dash for
nested means this mode **does not reach** that second indirect jump,
regardless of its numeric value. `render/action E8` is an actually reachable
original instruction address, and `native callee` is its decoded signed
REL32 destination. These are **not** claimed exact source-backed renderer
callee implementations.

| Mode | Original main entry | Used nested entry | Reachable original action E8 | Actual physical callee |
| ---: | --- | --- | --- | --- |
| 0 | `0x00443926` | — | `0x00443951` | `0x0043F550` |
| 1 | `0x0044395B` | — | `0x00443986` | `0x0043F630` |
| 2 | `0x00443BB3` | — | `0x00443BDE` | `0x0043F5C0` |
| 3 | `0x00443BE8` | — | `0x00443C13` | `0x0043F630` |
| 4 | `0x00443990` | — | `0x004439BB` | `0x00440310` |
| 5 | `0x004439C5` | — | `0x004439F0` | `0x004413A0` |
| 6 | `0x004439FA` | — | `0x00443A25` | `0x004408B0` |
| 7 | `0x00443A2F` | — | `0x00443A5A` | `0x00441C00` |
| 8 | `0x00443A64` | — | `0x00443A8F` | `0x00441F00` |
| 9 | `0x00443AE4` | — | `0x00443B01` | `0x00445350` |
| 10 | `0x00444FD7` | — | — | — |
| 11 | `0x00443B0B` | — | `0x00443B28` | `0x00445130` |
| 12 | `0x00443AE4` | — | `0x00443B01` | `0x00445350` |
| 13 | `0x00443AE4` | — | `0x00443B01` | `0x00445350` |
| 14 | `0x00443AE4` | — | `0x00443B01` | `0x00445350` |
| 15 | `0x00443A99` | — | `0x00443ACE` | `0x00441F00` |
| 16 | `0x00443C1D` | `0x00443E06` | `0x00443E7E` | `0x00439A00` |
| 17 | `0x00443C1D` | `0x004445FE` | `0x0044466D` | `0x0043B960` |
| 18 | `0x00443C1D` | `0x00444A23` | `0x00444A7D` | `0x0043BC60` |
| 19 | `0x00443C1D` | `0x00444A88` | `0x00444B02` | `0x0043BE80` |
| 20 | `0x00443C1D` | `0x00443F2E` | `0x00443FA6` | `0x00439A00` |
| 21 | `0x00443C1D` | `0x00443FB1` | `0x00444029` | `0x0043A1C0` |
| 22 | `0x00443C1D` | `0x00444034` | `0x004440B8` | `0x0043A1C0` |
| 23 | `0x00444FD7` | — | — | — |
| 24 | `0x00443B32` | — | `0x00443B4F` | `0x00443020` |
| 25 | `0x00443B32` | — | `0x00443B4F` | `0x00443020` |
| 26 | `0x00443C1D` | `0x00443D6B` | `0x00443DFB` | `0x0043CD40` |
| 27 | `0x00443C1D` | `0x00443E89` | `0x00443F23` | `0x0043B0E0` |
| 28 | `0x00443C1D` | `0x00444563` | `0x004445F3` | `0x0043E2C0` |
| 29 | `0x00443C1D` | `0x00444B0D` | `0x00444B94` | `0x0043BE80` |
| 30 | `0x00443C1D` | `0x00444B9F` | `0x00444C2A` | `0x0043BE80` |
| 31 | `0x00443C1D` | `0x00444678` | `0x00444703` | `0x0043C180` |
| 32 | `0x00443C1D` | `0x00444C35` | `0x00444C57` | `0x0043D830` |
| 33 | `0x00443C1D` | `0x0044470E` | `0x00444799` | `0x0043C4E0` |
| 34 | `0x00443C1D` | `0x004447A4` | `0x0044483A` | `0x0043C780` |
| 35 | `0x00443C1D` | `0x00444845` | `0x00444927` | `0x0043C780` |
| 36 | `0x00443C1D` | `0x00444932` | `0x00444A18` | `0x0043C780` |
| 37 | `0x00443C1D` | `0x004440C3` | `0x0044415E` | `0x0043A2B0` |
| 38 | `0x00443C1D` | `0x00444169` | `0x004441EF` | `0x0043A750` |
| 39 | `0x00443C1D` | `0x004441FA` | `0x00444304` | `0x0043AB20` |
| 40 | `0x00443C1D` | `0x0044430F` | `0x0044442C` | `0x0043AB20` |
| 41 | `0x00443C1D` | `0x00444437` | `0x00444558` | `0x0043AB20` |
| 42 | `0x00443C1D` | `0x00444C62` | `0x00444CED` | `0x0043D9B0` |
| 43 | `0x00443C1D` | `0x00444CF8` | `0x00444D6E` | `0x0043DCE0` |
| 44 | `0x00443C1D` | `0x00444D79` | `0x00444E0F` | `0x0043DF30` |
| 45 | `0x00443C1D` | `0x00444E1A` | `0x00444EEE` | `0x0043DF30` |
| 46 | `0x00443C1D` | `0x00444EF9` | `0x00444FD1` | `0x0043DF30` |
| 47 | `0x00443B59` | — | `0x00443B76` | `0x00443020` |
| 48 | `0x00443B80` | — | `0x00443B9D` | `0x00443020` |

The full CSV also retains each mode's exact count of reachable original
instruction heads. The new validation code checks those counts, original
jump-table entries, all physical destination instruction heads and the
entire direct E8 graph as separate assertions; changing a mode's target,
callsite, nested routing or reachable head count makes the original-PE
verification fail, rather than silently accepting a stale review record.
The original table boundaries and 123-call census continue to be checked
as before in the same native verification command.

## Impact on eventual C++ owner and replay scope

This mapping establishes the real 49-case/31-entry nested draw route
structure needed to author an actual coherent
`AnimationPoolOwner::draw(Animation*)` body. The later source must use
real `Animation+0x498` and field/geometry/Graphics API types, preserve
mode-specific preconditions and color/generator argument evaluation order,
and account for all **123** native original E8 occurrences and **32**
original body HIGHLOW before claiming a single exact byte for the parent.
The 29 discovered render/action callee functions remain separate original
methods, many large and still unsourced; this mode map does **not** assert
their source, exactness or eventual linker identity. Already separately
accepted whole game functions include four Animation field/recursive-scale
accessors (159B), three Graphics state cache transitions (276B) and the
original 192B batched draw flush, all physically separate and linked by
real original call sites.

**Compiler-input changes in this checkpoint: zero**. Only the original-PE
verification script, the 49-row original path CSV and native evidence docs
were modified, so scoped old/native cold replay is **zero**. The current
accepted game authored exact graph remains **577 complete physical functions
/188,625 original .text bytes, 1,224 strict units from 252 objects**.
There was no unfiltered whole-graph cold replay, no manual assembly or
invented function-padded source. The separate 12,140-byte Bullet command,
41,967-byte Enemy ECL and 39,470-byte Animation VM parents also remain
NONEXACT.

Reproduce from one immutable original executable:

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-animation-draw-boss-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target
