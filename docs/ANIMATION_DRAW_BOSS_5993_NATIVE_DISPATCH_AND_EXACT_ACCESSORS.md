# CORE/RECON-782 — the original 5,993-byte Animation draw Boss and four complete exact game accessors

> **Subsequent CORE/RECON-785:** Three more complete original 92B Graphics render-state transitions are now strictly exact (**276B game .text**) on this same 5,993B Boss call graph. [Native D3D9 state transition proof](GRAPHICS_DRAW_RENDERSTATES_276_STRICT_EXACT_RECONSTRUCTION.md). The counts below are the historical CORE/RECON-782 snapshot, not live totals.

The hash-locked original is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint independently investigates the complete, previously source-absent
**`0x00443880` Renderer/Animation draw Boss** and admits **four independently
complete, game-authored original children: 159 nonoverlapping .text bytes**.
It does **not** count the parent as exact: **the 5,993-byte parent remains
SOURCE-ABSENT and NONEXACT**, separate from its already exact Player draw
caller and the separate still-NONEXACT Bullet 273-byte per-group draw caller.

## The entire original 5,993B Boss: real native control flow

Original-PE-first disassembly (not copied decompiler text) proves:

| Original physical evidence | Independently checked result |
| --- | --- |
| Native function | `0x00443880..0x00444FE8`: **5,993 complete .text bytes /1,501 x86 instruction heads**, original `ret 4` at `0x00444FE6` |
| Direct calls | **123 physical `E8` /43 distinct actual call targets**, separately parsed from signed original displacements |
| Original in-body PE relocations | **32 actual IMAGE_REL_BASED_HIGHLOW fields**, including original jump-table operands `0x00443922` and `0x00443D67` |
| First actual indexed jump | `0x0044391F`, mode `Animation+0x498` guarded to `0..0x30` (49 entries) |
| **Main** native dispatch table | **49 original 32-bit HIGHLOW code pointers** at `0x00444FEC..0x004450AF`; exactly **17 unique native instruction entry heads** |
| Second, **nested** indexed jump | `0x00443D64`, mode reloaded from `Animation+0x498`, **subtract 0x10** and guard to `0..0x1E` (31 entries) |
| **Nested** native dispatch table | **31 real original HIGHLOW code pointers** at `0x004450B0..0x0044512B`; exactly **29 unique native instruction entry heads** |
| Native `.text` table separation | The original 5,993B body ends before three original alignment bytes `0F 1F 00`; the two jump tables come after those three bytes, not inside the body |

**Both original dispatch tables are required.** They total **80/80 genuine
PE HIGHLOW pointer sites**, and the enclosing Boss has another **32/32
in-body HIGHLOW** sites; these are three distinct physical regions and
**112 independently original PE relocation locations**. Every pointer target
is a real decoded instruction boundary inside this same 5,993B function.
It is incorrect to assume the primary 49-way table is the whole dispatch
just because it follows the body. The main entries for modes 0x10..0x16
and 0x1A..0x2E share one original 0x00443C1D block, and its second table
selects their actual render path. Modes 0x18/0x19, 0x2F and 0x30 enter
separate whole-function internal cases. Cases 0x17, 0x18, 0x19 of the nested
0x10-relative range are explicit shared/default paths in the original
inner table, not independently compiled child functions.

The native entry tests the real flag at `Animation+0x49C` bit 0, may invoke a
non-null callback at +`0x568` through its virtual slot `+8`, checks the
separately original **26B `Animation+0x49A` low-bit getter**, and excludes
`Animation+0x570 != 0` before mode dispatch. It uses real mode byte at
`Animation+0x498`, not a floating-point opcode. A separate exact native
Player draw caller at its original REL32 anchor to `0x00443880` establishes
the maintained `AnimationPoolOwner::draw(Animation*)` native method role;
original automatic names do not establish the historical class spelling.

A newly hash-attested read-only Ghidra decompile of this address was obtained
under `.analysis/core780-renderer-draw-5993-decompile.txt` as a *hypothesis*
only. The native x86 and PE are decisive. For example, Ghidra's generic
float casts on `FUN_004456E0`/`FUN_004456C0` are not valid evidence that
those 20B helpers return floats: their actual x86 loads full raw 32-bit
**packed Animation color words** in EAX at +`0x490`/+`0x494`, and the
original 5,993B caller preserves/stores those actual raw EAX words.

## Four game-authored entire native functions closed from this Boss

| Original address | Original bytes / source contribution | Genuine role | Original-Boss E8 calls |
| --- | ---: | --- | ---: |
| `0x004456E0` | **20/20B** `th20::animation_draw_color_490` | Read original packed `AnimationBase::color_490` at `Animation+0x490` | **32** |
| `0x004456C0` | **20/20B** `th20::animation_draw_color_494` | Read alternate packed color `Animation+0x494` | **22** |
| `0x00445AB0` | **26/26B** `th20::animation_draw_enabled` | Read actual `AnimationFlags::bit_10` at `Animation+0x49A` bit 0 | **1** |
| `0x00445880` | **93/93B** `th20::animation_inherited_aux_scale_x` | Recursively multiply `Animation+0x58` scale by parent's identical scale unless `Animation+0x49C` bit12 disables inheritance | **12** |

These are all maintained natural typed C++ bodies in one new
`src/AnimationDrawAccess.cpp`, without changing the public `Animation`
class/header or creating fake Renderer owners. The one-argument
`__fastcall` receiver ABI is independently attested by the original ECX
call convention; spelling the original role as an out-of-class operation
remains a source-level ABI-compatible reconstruction, **not** historical
member-name proof. The 93B recursive method is physically separate from
both **already accepted exact 93B** `Animation::inherited_scale_x` and
`Animation::inherited_scale_y` methods at `0x00445940`/`0x004458E0`:
those read `Animation+0x50/+0x54`; this original method instead reads
**`Animation+0x58`**. No folded/overlapping physical byte credit is counted.

The original recursive 93B body has **one true PE HIGHLOW data reference at
`0x0044588D`** to the existing immutable original 1.0f `0x0056C8CC`
and **one real original direct E8 at `0x004458BC`** returning to its own
physical head `0x00445880`; both match native COFF relocation type/offset
and destination without inferring targets from compiled code. The other
20B/20B/26B bodies have **zero real native relocation fields**, and all
body boundaries include their genuine return instructions.

## Reproducible original PE and focused compiler validation

`scripts/verify-animation-draw-boss-native.py` independently validates:
all 5,993 bytes/1,501 instruction boundaries, **123** entire original E8
sites and 43 destinations, the **49+31** distinct HIGHLOW switch tables and
both original guards, all 32 body HIGHLOW, the original 3-byte table
alignment, original callback/visibility gates, every relevant game child
E8 occurrence and full original recursive-scale data/E8 anchors.
The source-origin claim and both table cardinalities are therefore not
copied from Ghidra or inherited from a previous hypothesis.

Pinned MSVC 19.44.35211 x86, `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` compiles exactly **one new** canonical
`build/core782-canonical/AnimationDrawAccess.obj` and receipt.
All **4/4 whole complete native methods** pass canonical strict original
code/relocation replay from that sole object:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawAccess.cpp
    scripts/repo-python scripts/verify-animation-draw-boss-native.py

No old canonical source, public header, profile or previously accepted
exact object input was edited. Affected existing strict units = **0**, one
new provider/four newly admitted units. **No full cold replay** was run.
The entire original 5,993B Boss has **no newly asserted exact body bytes**
and its original 80 switch pointer words are compiler dispatch metadata,
not separately credited game-authored functions.

The game-authored complete strict whole-function count advances
**569 →573**, disjoint authored code bytes **187,998 →188,157**.
Source-present mappings advance **1,214 →1,218**, strict canonical
units **1,216 →1,220**, distinct canonical object providers **249 →250**.
Next reconstruct the actual main+inner mode routing and native draw helper
contracts in one coherent `AnimationPoolOwner::draw` C++ implementation,
checking its entire 5,993B body. The 12,140B Bullet command Boss, 41,967B
Enemy ECL dispatcher, 39,470B Animation VM and 273B Bullet draw-group
remain separate **NONEXACT** unfinished original game functions.
