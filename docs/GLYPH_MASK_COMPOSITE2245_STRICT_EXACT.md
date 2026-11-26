# Exact 2,245-byte glyph outline compositor

`NativeGlyphCanvasView::composite_glyph_mask_416420` at `0x00416420` now
strictly replays its complete **2,245B / 612-instruction** body. All **37 REL32
calls**, **five HIGHLOW/DIR32 fields** and every ordinary byte match the locked
Japanese TH20 Steamless target. The original `grpfont.cpp` diagnostic path,
GDI bitmap receiver and two pixel-format branches retain the independently
reviewed game-authored origin. This adds one authored exact function / 2,245B.

The maintained implementation is in `src/GlyphMaskComposite2245.cpp` and the
canonical unit is `glyph_composite_mask_2245` in `config/match-units.toml`.
It uses the locked MSVC 19.44.35211 C++20 profile:
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

## Source findings that close the whole body

The old 2,224B / 591-instruction candidate had the correct broad behavior and
call roles but differed in several concrete native operations:

- Generate offsets in outer-X, inner-Y order, and test the outer displacement
  first. Both native aggregates store the outer loop value as element zero.
- Pass each two-word offset as a temporary bound to the existing const-reference
  insertion path. A named array local occupied ordinary local storage; the
  native aggregates occupy compiler temporary slots. The natural
  `emplace_back<const GlyphMaskOffset&>({delta_x,delta_y})` expression restores
  both their storage and the surrounding stack layout without extra locals.
- Cache a separate snapshot base for each format. BGRA32 reuses one real
  neighbor pointer through its four guarded alpha checks. Group the X offset
  before adding it to the row offset, matching the native arithmetic order.
- Derive the BGRA pixel size from `sizeof(PackedColorChannels)` and use it for
  the stride-to-word conversion. This restores the original constant-size
  initialization and its actual consumer.
- Initialize Y before the row-advance accumulator. Skip zero-alpha BGRA pixels
  with `continue`; after the ordinary RGB writes, both formats continue directly
  to the pixel-loop update. Jumping to a nearby label instead produced two
  short jumps where the original has near jumps to the loop updates.
- Release and clear the snapshot through the existing
  `TH20_RELEASE_ARRAY_AND_RESET` protocol. The original clears this owning
  pointer after the release; this is separate from the Boolean success return.

The four-bit RGBA channel writes, nine live stride reads, single bitmap getter,
four array-index calls and ordered neighbor guards remain intact. There is one
semantic implementation, with no assembly, byte arrays, artificial padding,
extra compiler-shaping locals or exact-only source branches.

The final probe reached 2,239B with all 612 instructions and all non-branch
operands matching. Its only two instruction-length differences were the normal
pixel exits at native +0x3FF and +0x862: each needed the direct `continue`
boundary rather than a jump to the end label. Restoring those exits yielded
all 37 physical E8 positions and all 2,077 ordinary bytes before canonical
relocation replay.

## Complete exception ownership

| Native head | Complete contribution | Canonical unit |
| --- | ---: | --- |
| `0x00567E60` | 8B BGRA vector cleanup | `glyph_composite_eh_cleanup_bgra_8` |
| `0x00567E68` | 13B RGBA cleanup, including five native INT3 bytes | `glyph_composite_eh_cleanup_rgba_13` |
| `0x00567E75` | 42B cookie-checking EH handler | `glyph_composite_eh_handler_42` |

Both cleanup actions invoke the independently exact vector destructor at
`0x00414440`, using the native receivers at `[ebp-0x3C]` and `[ebp-0x2C]`.
The handler selects FuncInfo at `0x005A9830`; its two-state map at `0x005A9820`
selects these two cleanup actions. The complete **52B** COFF .xdata contribution
replays all three DIR32 fields and matches every native byte. No state is added
for the raw snapshot, preserving the original exception behavior.

Call anchors come from the previously reviewed native glyph/PMR protocol,
allocator and CRT roles. They are not solved from the parent fields being
compared. The diagnostic string relocation also checks its actual PE literal.
The compiler-owned supporting code and metadata receive no authored-game credit.
The public 35B insertion wrapper remains 34B in the current compiler and is
still independently NONEXACT; the parent comparison covers its real call role
without granting exactness to that child.

## Verification and reusable evidence

The source was freshly built with `build.py --unit glyph_composite_mask_2245`.
The complete affected scope then replayed **39/39 units from that one freshly
built object**, using `replay-exact-units.py --source
src/GlyphMaskComposite2245.cpp --existing-objects`. All 35 prior units remain
exact. No shared header changed, and the separate C++17 allocator owner's
seven unchanged units retain their passing evidence.

The chain, array-index, live-pixel, five-parent and deep-nine verifiers pass.
The obsolete source-spelling and historical progress-count assertions in the
array-index frontier checker were replaced by complete canonical comparisons.
Six malformed state-count/cleanup-relocation cases across move, growth and
compositor metadata are rejected. A same-size inverted zero-alpha branch is
also rejected without changing the target or canonical objects.

Attested native decompilation is retained privately at
`.analysis/draw-boss-session/glyph-compositor-current-native.c`. The bounded
source probes, instruction alignment, slot map and call map are in that same
investigation directory. Final proof output is retained as
`glyph-compositor-strict-replay.log`, `glyph-compositor-array-proof.txt`,
`glyph-compositor-chain.txt` and `glyph-compositor-five-parents.txt`.

The remaining Glyph frontier includes the public insertion wrapper and the
separate 2,227B text core. A complete game build and runtime validation remain
open; this proof covers the compositor and the supporting extents listed above.
