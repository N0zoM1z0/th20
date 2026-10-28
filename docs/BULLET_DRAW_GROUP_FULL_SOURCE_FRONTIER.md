# CORE/RECON-304 — complete typed Bullet single-group drawing loop (nonexact)

## CORE/RECON-375 — native byte bitfield and full affected-only regression

Current maintained `src/BulletDrawGroup.cpp` is still **NONEXACT**,
but now uses the actual one-byte `AnimationFlags` upper-three-bit view:
`Animation+0x4A2` bits 5 through 7 are a genuine C++ 3-bit byte
field, retaining the original raw `field_0a` alias for other consumers.
The locked MSVC i386 source emits original
`mov al,byte ptr [edx+0x4A2]; shr al,5; and al,7`,
not the earlier nonnative 32-bit signed `sar eax,5`.

The whole maintained function now emits **283B / 84 instructions** and
all **82/82 original mnemonic kinds in order**, with the expected eight
external COFF reference locations/types in the candidate. The original
whole function remains **273B / 82 instructions**: two unwanted float
offset `movss` spills add **10 bytes** around the native pi/2 rotation
argument. Therefore there is **no newly accepted exact original draw
range**. Current pinned native compiler probe:
`build/core375-probes/BulletDrawGroup-maintained.obj` and receipt, with
private complete-score evidence
`.analysis/core375-bullet-draw-typed-abi-score.txt`.
Original floating-point evaluation/profiles were independently tested
in `.analysis/core371-*` through `.analysis/core374-*`; none of those
bounded candidates passed strict native comparison. No NOPs, manual
asm, fake returns, inert variables or shortened comparison ranges.

From the **previous canonical compiler receipts**, the affected actual
`Animation.hpp` include closure is **56 source providers with 263 old
strict units**. All **263/263** original exact units were cold rebuilt
in **56 objects**, across twelve serial reduced-priority batches
**66+34+15+6+29+10+43+23+8+12+13+4**, including the complete 2,018B
Bullet collision and 1,518B Player option rebuild roots. The draw
function itself remains nonexact, was compiled in full as an isolated
probe, and received **zero exact credit**. There was no unfiltered
all-repository cold replay.

Five MSVC-private `$SG` identities in RenderMesh and Ascii
constructors renumbered after the shared-header change. Each retained
its independently original PE string destination, original reference
offset/type, receipt and complete nonrelocation bytes, then passed
the unchanged strict comparator. The already present, dirty
`bullet_cancel` private `$SG` renumbering was likewise retained and
strictly checked against original `0x0056FD14`, not hidden or discarded.
Full private evidence:
`.analysis/core375-animation-receipt-closure.json`,
`.analysis/core375-replay-groups.json`,
`.analysis/core375-replay-batch0.log` through `batch11.log` and
`.analysis/core375-reconciled-private-symbols.json`.

The former CORE/RECON-304 **279B / 79-of-82** candidate measurements
below are **historical**. The production source now uses the native
byte bitfield and produces the **283B / 84-instruction** nonexact
candidate above. Original six-group drawing parent `draw_groups` at
`0x0047DC90` remains separately exact (81B).


The entire original game-authored `BulletController::draw_group(int)` at
`0x0047DB70..0x0047DC80` is **273 native bytes / 82 original x86
instructions**. Its direct caller is the separately exact original
**81-byte six-group draw orchestrator** `0x0047DC90`. The current
maintained full-function source is `src/BulletDrawGroup.cpp`, using the
real Bullet, Animation and AnimationPoolOwner interfaces. This **is a
nonexact whole-function reconstruction**: it is not listed as a canonical
`matching` unit or counted as exact bytes.

## Independent complete-original behavior and references

The Japanese v1.00a Steamless original target is unmodified (whole-file
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
Fresh target-attested function/call graph evidence and an independent
full-span Capstone decode confirm the four-stage loop:

1. Iterate the original `draw_heads[group]` intrusive forward chain,
   initially at `BulletController+0x14`, using `Bullet::draw_next`
   (`Bullet+0x60`) until null.
2. Copy the actual Bullet position (`+0x64`, three floats) to its embedded
   Animation position (`Animation+0x5BC`, `vector_5bc`). If the high three
   bits, 5..7, of the actual Animation flag byte at `+0x4A2` are nonzero,
   update sprite rotation from native `add_angles(float(Angle),pi/2)`.
   The production header exposes the observed raw byte `field_0a`; the
   C++ source tests those high bits directly rather than fabricating a
   second overlapping bitfield representation.
3. If Bullet flag bit 6 is set, call native `Animation::set_scale_58` with
   the same Bullet scalar from `+0x48` twice. Both flag and floating
   argument order are observable in the complete native body.
4. Submit the original embedded Animation pointer to the current native
   Renderer; continue to the next Bullet and return integer one after
   the chain ends.

All **eight original native relocation fields**, independently extracted
from the unmodified original instructions, are:

| Original field | Kind | Original destination |
| --- | --- | --- |
| `+0x67` | DIR32 | `0x0056E0F0` native pi |
| `+0x6F` | DIR32 | `0x0056C8D0` native two |
| `+0x83` | REL32 | `0x004292E0` float Angle accessor |
| `+0x8C` | REL32 | `0x00438600` normalized angle addition |
| `+0xA5` | REL32 | `0x00450590` Animation rotation setter |
| `+0xE1` | REL32 | `0x004864F0` Animation scale setter |
| `+0xEF` | DIR32 | `0x005C0028` Renderer pool pointer |
| `+0xF4` | REL32 | `0x00443880` Renderer draw call |

This source consumes all eight observed ABI dependencies, without
rebuilding their separate exact children or claiming the Renderer global
and lifetime are implemented.

## Locked-MSVC whole-function experiment and remaining exactness debt

Fresh native headers in the maintained repository were used, **not**
unverified private substitutions: `Bullet.hpp`, `Animation.hpp` and
`AnimationRuntimeOwner.hpp`. Exactly one isolated, reduced-priority
locked MSVC 19.44 x86 compilation of the maintained source produced
`build/core304-probes/BulletDrawGroup-maintained.obj` and receipt. Its
entire emitted contribution is **279 bytes / 82 instructions**, while
mnemonic sequence alignment to the whole original is **79/82**; the
candidate has eight ordinary COFF relocation sites. The maintained
header exposes only the raw 8-bit flag, producing a `sar` pattern rather
than the original `mov/shr/and` bitfield accessor. There are also two
extra real float offset spill/reload instructions before
`add_angles`, and original result-temp ownership has a distinct stack
layout. Earlier private *bitfield-view* probes reached **82/82 aligned
original mnemonic kinds** but produced **283 bytes**, not 273. Those
private layouts were deliberately not introduced into a shared header
just to manipulate codegen.

These differences are real and **no 273-byte exactness, full Renderer
linkage, or original compiler-local C++ variable identity is claimed**.
The result is a completely maintained semantic implementation that
replaces only this previously unimplemented caller target. No accepted
exact source, canonical object or shared header was edited by CORE/RECON-304,
so the previously accepted strict-unit replay scope is **zero**. A local
whole-body compilation, original-target validation and source-ledger
consistency check are appropriate; a full cold replay is not.
