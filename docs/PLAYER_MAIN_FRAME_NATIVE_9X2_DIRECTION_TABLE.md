# CORE/RECON-669 — original 9×2 signed Player direction table and full-frame C++ indexing

**The 3,111-byte / 783-instruction original Player main frame is still NONEXACT.**
The pinned Japanese TH20 v1.00a Steamless executable is resources/th20.exe,
SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.
This checkpoint corrects a concrete previously mistaken source-level type
in the real maintained whole game function src/PlayerMainFrame.cpp;
no original game executable bytes or canonical helper are patched.

## Original native 2D subscripts, not merely flattened IntPoint members

The original game has 72 initialized bytes at **0x00572C48**, representing
nine consecutive pairs of signed 32-bit (dx, dy) values, in index order:

    (0,0), (0,-1), (0,1), (-1,0), (1,0),
    (-1,-1), (1,-1), (-1,1), (1,1)

Their *values alone* supported the earlier guess of `IntPoint[9]`,
but did **not** prove its original source indexing syntax.
The immutable original Player x86 at method offsets:

- **+0x5E3 / +0x5E6:** obtain Player+0x67C direction selector.
- **+0x5EC:** `mov eax, 4`;
  **+0x5F1:** `imul ecx, eax, 0`;
  **+0x5F4:** `mov edx, [ecx + edx*8 + 0x00572C48]`
  — real element-zero second-dimension indexing.
- **+0x5FE / +0x601:** independently reread Player+0x67C.
- **+0x607:** `mov edx, 4`;
  **+0x60C:** `shl edx, 0`;
  **+0x60F:** `mov eax, [edx + ecx*8 + 0x00572C48]`
  — real element-one second-dimension indexing.
- **+0x5FB / +0x616:** preserve the two native x/y velocity slots.

These intentionally unoptimized /Od constant inner-subscripts are
physically absent from ordinary `native_player_direction_table[i].x/.y`
member access. The original function is effectively indexing a
**signed int32_t [9][2]** table, not simply making two field loads
from a named `IntPoint[9]` table. The C++ source now declares the
same 9×2 scalar shape and uses `table[field_67c][0/1]` directly.

## Whole real MSVC native validation

Original complete code: **3,111B, 783 i386 instructions**.
Under pinned MSVC 19.44.35211 /std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /EHsc:

| Whole-function diagnostic | Prior maintained | Corrected 9×2 source |
| --- | ---: | ---: |
| Compiled method code bytes | 3,110 | **3,126** |
| Compiled x86 instruction heads | 784 | **788** |
| Original mnemonic heads aligned in order | 759/783 | **763/783** |
| Text-identical operands among aligned heads | 359 | **366** |
| Original E8 / C++ REL32 by count | 67/67 | **67/67** |
| Original HIGHLOW / C++ DIR32 by count | 37/37 | **37/37** |
| Full native parent accepted exact | NO | **NO** |

The corrected two subscript groups reproduce **all 12 original
instruction kinds and register/stack operand identities in order**.
Their two absolute COFF relocation fields remain unlinked placeholders,
while the native PE points to the independently read 0x00572C48 data.
The exact original source type spelling cannot be inferred solely from
machine code, but the natural two-dimensional scalar indexing has
stronger direct original opcode evidence than the previous IntPoint member
hypothesis. Candidate whole-method size grows by sixteen bytes because
those real /Od inner-index instructions are no longer omitted.
The parent still has other control-flow and local-lifetime differences;
a nearer numeric byte length would not justify retaining a wrong access
shape. No new whole-parent exact code bytes are claimed.

Private source experiments compiled *the entire original parent*:
- `.analysis/core666-player-original-2d-direction-table-probes.py/json`:
  five complete candidates (typed IntPoint rows, true 9×2 / unbounded×2,
  flattened linear words and reversed read ordering).
- `.analysis/core667-player-native-2d-direction-and-focus-variants.py/json`:
  seven whole-function combinations with independently tested focus
  state source grammars. Alternate focus grammars had poorer original
  direct dataflow evidence and were not promoted.
- `.analysis/core668-player-maintained-native-2d-direction-proof.json`:
  fresh real `src/PlayerMainFrame.cpp` method, two complete native
  second-subscripts and 67/37 original relocation count comparison.
- `.analysis/core668-player-main-all-67-callee-proof.py/json`:
  independent recheck of **all 67 original E8 source/physical callee
  roles in original order** against this final corrected parent.
  Sixty were previously independently anchored, six call occurrences
  have fully byte-identical folded-compatible source implementations,
  and the remaining mapped movement child remains separately NONEXACT.
- `build/core668-probes/PlayerMainFrame.obj` and associated pinned
  compile receipt: single affected whole-parent source object.

There is no configured canonical unit for src/PlayerMainFrame.cpp.
**Affected previously accepted units: zero; fresh whole-parent probes only.**
No public header, unrelated strict provider or original target changed,
no global or unfiltered cold replay, no double credit for folded helpers.
Current accepted original authored coverage remains **499 complete
functions / 179,444 non-overlapping code bytes**. The 555-byte
Player movement and 12,140-byte Bullet dispatcher are distinct
still-nonexact complete functions.
