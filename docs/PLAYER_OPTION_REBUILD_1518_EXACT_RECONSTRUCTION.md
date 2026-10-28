# CORE/EXACT-369 — whole original 1,518-byte Player option-animation rebuilding boss

Comparison oracle: immutable user-approved Japanese TH20 v1.00a Steamless
`resources/th20.exe`, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete original game-owned `Player::rebuild_option_animations(int)`
at `0x004FACA0..0x004FB28D` is now **1,518/1,518 strictly exact native
bytes** with **418/418 original x86 instructions** and all **60 original
PE relocation sites/targets**. Entire original function SHA-256:
`0efafdd89cb2d190c5bc4eca1ecd4f1343b1da8c6032d23870a6a6b4127b779b`.

The genuine maintained source is `src/PlayerOptionRebuild.cpp` and the
locked canonical unit `player_rebuild_option_animations`. Its earlier
authored but nonexact full-function frontier (CORE/RECON-333/343) has
been **promoted**, not duplicated; exactly **1,518 native original
bytes** are now newly credited. This closes the real original direct
callee of the independently exact **966-byte Player initialization boss**
at `0x004FB450` without overlap.

## Complete original gameplay function

This is the entire native function and not a prefix or a handful of
small helpers. It selects the Renderer view, sets real PlayerShotController
bit zero, replaces negative input with a PlayerRecord-derived option
count, respects original PlayerRecord clamp and signed division, and
handles both branches of the main option animation lifecycle. Existing
handles are retired or cancelled/cleared using actual complete native
methods; the early nullable AnimationFile branch uses the original
flag-2 wrapper and original shot-data script base at `+0xA8`.

For a changed active count, it reinitializes the actual 10-element
PlayerOption collection, applies both independently exact WeaponStone
focused/unfocused virtual offsets, converts the real float coordinates
to 128x fixed-position IntPoint values, copies current and previous
positions, and selects the second script base at shot-data `+0x88`.
It uses the true aggregate AnimationHandle return/copy path, resolves
the actual Animation and sets native Y to **-999.0f**, invokes the
complete native Weapon pair initializer, clears unused main handles,
publishes the active count, and runs the separately exact 165-byte
option field broadcast. Finally it clears all **12** secondary option
records and their actual bitflags. The larger serialized resource
schema containing shot-data +0x88/+0xA8 remains **unclassified**;
no invented resource arrays or fake game owners are used.

## Native frame, live aggregate and four shared loops

Several independent C++20/MSVC expression experiments resolved
the true local-variable lifetime rather than injecting padding:

- The original **one** PlayerOption pointer is reused through all
  gameplay branches and the ten/twelve-slot array traversals. A single
  real uint32_t loop counter is reused through **four** actual loops:
  signed comparisons against live count use explicit int32_t casts,
  while fixed-capacity checks use unsigned comparisons. Previously
  giving the loops separate variables consumed three extra four-byte
  stack slots, despite semantically equivalent high-level loops.
- The live eight-byte IntPoint result is naturally aligned, restoring
  the native MSVC i386 **8-byte stack realignment** and original
  `sub esp,0x9C` frame. The original pointer/reference selection has
  two real consumed reference stages and the actual focused offset
  conversion has its own C++ scope; MSVC naturally emits the observed
  one-byte NOP rather than manual assembly or filler.
- The original IntPoint sum is consumed as an xvalue through natural
  `std::move`, preserving the original returned EAX pointer and true
  eight-byte copy into the selected native option position. No
  unobserved call or dummy local is introduced.
- Crucially, **both** AnimationFile return values are assigned as full
  `AnimationHandle` objects, not by direct assignment to their four-byte
  `.value` members. That restores the original register evaluation
  order at native `+0x185` and `+0x487` and removes the final 10
  incorrect non-relocation bytes.

The accepted pinned compiler is MSVC 19.44.35211 i386 with
`/nologo /c /std:c++20 /Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise
/EHsc`. This native function has no unobserved security cookie.
No inline assembly, synthetic branch, inert padding, copied machine
code, dummy return or shortened comparison was used.

## Independently grounded full original PE references

The complete **1,518-byte original** was freshly decoded from the
unmodified original PE, not inferred from a previous candidate:
exactly **57 native E8/REL32 call fields** and three independent
`.reloc` HIGHLOW/DIR32 absolute fields. The three original absolute
fields are:

| Field offset | Original target | Meaning |
| --- | --- | --- |
| `+0x02C` | `0x005C0028` | Renderer owner global |
| `+0x1A9` | `0x0056FD7C` | first original -999.0f constant |
| `+0x4AB` | `0x0056FD7C` | second original -999.0f constant |

All **60 field offsets, types, and independently observed original
destinations** are recorded in
`.analysis/core369-independent-original-reference-proof.json`.
Forty field symbols were also corroborated by older independent
canonical original relocation evidence. Previously unseen symbol
labels were tied directly to independently decoded original E8/PE
targets (not invented from the candidate). The natural COFF body's
exact 60 relocations use those original native destinations.

The unchanged strict canonical comparator accepts **1,278/1,278
nonrelocated bytes and 240/240 relocated bytes = 1,518/1,518 exact
native original bytes**, and all **418 original instructions**. The
physical folded template accessors retain their original linker
aliases, with no duplicate original address/byte credit.

## Actual affected-only proof and remaining scope

The only maintained source changed was the previously nonexact,
already source-present `src/PlayerOptionRebuild.cpp`. **No shared
headers, already exact source provider, build flag, native target, or
other original matching bytes changed.** The actual strict replay scope
is therefore **one newly canonical source provider/object and 1/1
strict unit**, proven by the focused cold replay in
`.analysis/core369-player-option-rebuild-replay.log`. The new locked
object and receipt are `build/core369-canonical/PlayerOptionRebuild.obj`
and its matching receipt. Separately rechecking the original 966-byte
Player reset root still gives 966/966 exact. No unfiltered all-repository
cold replay was run.

Private forensic expression/stack audits:
`.analysis/core363-*` through `.analysis/core369-*`.
Earlier nonexact source experiments remain available for comparison,
but their old source status and provisional byte counts are
superseded. An entire original game-owned function being exact does
not establish complete executable linking, resource-loaded runtime
equivalence, or separate Bullet/Enemy large-dispatcher exactness.
