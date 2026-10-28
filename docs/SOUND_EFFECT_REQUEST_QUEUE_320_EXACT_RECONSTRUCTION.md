# CORE/EXACT-445 — complete original 320-byte SoundInf effect request manager

Comparison original: immutable Japanese TH20 v1.00a Steamless
`resources/th20.exe`, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The genuine original game-authored `SoundInf::request_effect(int,int)`
at `0x00426D70..0x00426EAF` is now **320/320 strict original
native byte-exact** with **102/102 original i386 instructions**,
under the original locked MSVC 19.44 i386 C++20 compiler profile.
Complete original interval SHA-256:
`6279d9839178f4f4e52f0cba70c64cb3b4c496f0e8fa0605961b69b9cb644`.
The real source implementation lives beside the earlier exact
52-byte `request_effect_at` in existing `src/SoundEffects.cpp`.

## Entire genuine TH20 request lifecycle: 12 requests, 60 pan samples and 90 channels

The native game method reads the **signed 16-bit sound effect
definition field at record offset +8** through its actual
sound-ID index of stride **20 bytes**. It retains that value
for the eventual channel cooldown initialization.

The method walks the real `std::array<SoundEffectRequest,12>`
starting at `SoundInf+0x1C`. Every request is exactly
**0x208 bytes**, with an identifier, signed counter and
128-element signed pan buffer. The original loop uses
genuine MSVC `std::array::_Unchecked_begin` and
`_Unchecked_end` pointers, then steps by 0x208 bytes:
it stops at the end or at the first request whose
identifier is negative. For an existing identifier
matching the incoming sound effect, the method appends
the new signed pan only if **0 <= count < 60**,
increments count and returns. A full request or
negative counter returns without modifying the
request.

If a new request is required, it rejects queue positions
at or beyond twelve. Otherwise, it assigns the
requested ID through the real checked
`std::array::at(index)`, puts the pan into the
first buffer entry through the genuine un-checked
array indexer, sets count to one and selects
the real sound channel at `SoundInf+0x1994`
using the **90-channel** array indexer.
Finally it sets that channel's integer cooldown
using the original effect definition's signed field.
There is no invented device scheduling, startup
resource ownership or out-of-bounds fallback
beyond what the original code executes.

The separate 22-byte
`SoundEffectChannel::set_cooldown(int)`
is implemented as a real C++ member, assigning
the live channel field at offset +4. The linker
original shares its identical physical native
`0x00411570` body with the **already exact**
`EnemyPattern::set_base_kind`, which performs
the same four-byte field write. It receives
**zero additional physical exact byte credit**;
this is only one original folded address.

## Original 7 direct E8 fields and one real absolute volume lookup

The complete 320-byte original x86 was independently decoded
from the immutable PE. **Exactly seven native direct E8 fields
and one original PE `.reloc` HIGHLOW field** were collected
*before* matching the compiled source. The original relocation
offsets/types and the true physical destinations are:

| Original field | Type | Independently original target | Native role |
| --- | --- | --- | --- |
| `+0x10` | DIR32 | `0x005AE6F2` | sound definition signed 16-bit field |
| `+0x2B` | REL32 | `0x0040BDA0` | request-array raw begin |
| `+0x36` | REL32 | `0x00428C40` | request-array raw end |
| `+0xC9` | REL32 | `0x00428E20` | checked request-array at(index) |
| `+0xE3` | REL32 | `0x004260B0` | request-array index |
| `+0x107` | REL32 | `0x004260B0` | request-array index again |
| `+0x126` | REL32 | `0x004260F0` | 90-channel array index |
| `+0x135` | REL32 | `0x00411570` | live channel cooldown setter, folded |

**Important original PE/COFF addend distinction:**
the absolute original field at `+0x10` encodes
`0x005AE6F2`, whereas the canonical compiler
symbol is `sound_effect_definitions` with actual
record base **`0x005AE6EA`** and original emitted
`+8` addend. The manifest therefore stores
**base 0x005AE6EA**, *not* the already-field-offset
native 0x005AE6F2; the strict oracle adds the
real eight-byte field addend to reproduce the
immutable original. The literal table bytes
were reread from the PE. No guess at other
unspecified original table members is made.

The raw begin at `0x0040BDA0` also shares
a previously accepted exact physical body with
`Motion::position_ref`. The scalar cooldown
setter at `0x00411570` is previously exact as
a different game class's four-byte assignment.
The STL array end/index helpers at
`0x00428C40`, `0x00428E20`,
`0x004260B0` and `0x004260F0`
are **not newly claimed as whole exact native
functions**; the caller's exactness is not
mistaken for callee exactness.

All **eight original relocation locations,
types, PE destinations and actual compiler COFF
symbols/addends** agree. The source strictly
compares **288/288 nonrelocation bytes plus
32/32 actual relocated original bytes**, giving
**320/320 whole native bytes**, with no
padding, artificial locals, manually emitted
machine code or truncated branches.
Entire independent original references,
native SHA, compiler symbols and addends:
`.analysis/core445-sound-request-original-refs.json`.

The original MSVC profile for this existing source
owner is
`/nologo /c /std:c++20 /Od /Ob0 /GS- /Gy /Zl
/arch:SSE2 /fp:precise /Gd`.
The actual native MSVC array protocol's
`_Unchecked_begin/end` calls are used deliberately:
ordinary debug-iterator wrappers generated
extra calls and wrong instructions, while true
raw iterators generated the original native loop.
The nested/combined **count <60 && count >=0**
source condition generates exactly the original
two conditional branches instead of two extra
unobserved unconditional jumps.

## Complete real changed-input-only cold replay

Only `src/SoundEffects.hpp` (the true native
SoundEffectChannel scalar setter declaration)
and `src/SoundEffects.cpp` changed. The original
`SoundInf` class declaration already had this
authentic two-parameter effect request member.
**Before editing**, actual existing compiler
receipt includes for `SoundEffects.hpp` and
`SoundInf.hpp` were captured: their union
identified exactly **12 previously canonical
source providers with 24 strict native units**.
One newly exact 320B body is added to the
**existing** `build/core167-canonical/SoundEffects.obj`
provider. The entire true affected set is therefore
**25/25 strict original units across exactly
12 freshly cold-built objects**, replayed serially
at low priority in batches of **5 + 15 + 5**.
Full frozen scope and complete strict logs:
`.analysis/core445-sound-request-preedit-closure.json`,
`.analysis/core445-sound-request-replay-groups.json`
and `.analysis/core445-sound-request-replay-batch0.log`
through `batch2.log`.

Existing exact 52B positional `SoundInf::request_effect_at`,
SoundEffectRequest/Command/Channel constructors,
2,018B Bullet collision and the Bullet/Item/Enemy
sound-request caller paths remain strictly exact.
Ten MSVC-private `$SG` symbol labels in affected
diagnostic-heavy Bullet, Item and Sound objects
renumbered. For each, the original PE destination,
relocation offset/type and unchanged nonrelocation
bytes were independently checked before accepting
only the private compiler symbol spelling, followed
by complete unchanged-oracle exact replay.
`.analysis/core445-reconciled-private-symbols.json`
holds the true old/new labels and original PE
destination evidence.

This original 320B game-owned function is called
twice by the still-nonexact original **3,111B
Player main-frame** at `0x004F9C30`.
The enclosing parent now has **64/67** original
E8 call sites pointing to independently strict
exact callees; the remaining three are separate
native roots. This change credits **one** new
game-authored complete native function and
**320** nonoverlapping original bytes, not the
still-open 3,111B parent or unimplemented
sound device initialization/linked runtime.
No unfiltered whole-repository cold replay occurred.
