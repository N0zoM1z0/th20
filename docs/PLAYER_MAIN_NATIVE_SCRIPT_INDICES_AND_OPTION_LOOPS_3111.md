# CORE/RECON-704 — original Player main 3,111B: correct direction-script indices, cached option bounds and by-value history copy

**Later [CORE/RECON-721](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md) operand audit:** genuine unchanged whole Player 3,114B/783 candidate and original 3,111B/783 share **164/164 nonrelocated ordinary immediate values** and **67/67 positive nonstack game member field displacements** under explicitly filtered operand definitions. Seven native original ADD accumulator/register encoding differences cause the net +3B, but many other operand and relocation positions remain unequal. The original parent is still NONEXACT.


**The entire original game Player::update_main_frame at 0x004F9C30 remains NONEXACT.** The original complete physical body is **3,111 bytes / 783 x86 instructions** in the locked Japanese TH20 v1.00a Steamless executable, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897. This checkpoint fixes actual gameplay and compiler value lifetimes in the maintained whole game function src/PlayerMainFrame.cpp; it does **not** claim partial native exact credit for the parent.

## Real gameplay bug: original uses Animation scripts 1 through 4, not 0 through 3

The previous maintained Player source indexed animation_scripts[0], [1], [2], [3] when horizontal motion crossed the previous signed direction. Original immutable PE machine code actually uses the **second through fifth** entries of the five-element Player array based at Player+0x22A0.

| Original method instruction offsets | Original index calculation and load | Actual word/byte offset | State transition |
| --- | --- | --- | --- |
| +0x8D1/+0x8D6/+0x8DC | mov eax,4; shl eax,0; load from +0x22A0+eax | animation_scripts[1], +4B | New negative X, previous nonnegative X |
| +0x919/+0x91E/+0x923 | mov ecx,4; shl ecx,1; load from +0x22A0+ecx | animation_scripts[2], +8B | New zero X, previous negative X |
| +0x95E/+0x963/+0x969 | mov edx,4; imul eax,edx,3; load from +0x22A0+eax | animation_scripts[3], +12B | New positive X, previous nonpositive X |
| +0x9A6/+0x9AB/+0x9B1 | mov ecx,4; shl ecx,2; load from +0x22A0+ecx | animation_scripts[4], +16B | New zero X, previous positive X |

All four original physical computed offsets were re-extracted from immutable PE instructions, not inferred from previously written documentation. The old maintained indexes selected different animation scripts in gameplay. The real source now uses **[1], [2], [3], [4]**, restores the four original indexing opcode *kinds*, and retains the authentic AnimationFile::bind_animation(Animation*,int,Animation*) E8 and its explicit null parent.

## Native original option loops cache begin and end ONCE per group

The original whole Player frame gets the actual primary 10-entry PlayerOption group at Player+0x684, saves its receiver, invokes begin() and end() ONCE before iteration, compares cached pointers, advances by the real 0x12C PlayerOption stride and passes an independently saved current PlayerOption pointer to the genuine option frame method. The secondary 12-entry group at Player+0x123C repeats the same protocol. The older source called end() anew on every loop test, contrary to the original E8 placement.

| Original physical E8 call | Original target |
| --- | --- |
| 0x004FA793 | 0x0040BDA0 — primary 10-entry begin, folded with another original helper |
| 0x004FA79E | 0x004FCE60 — primary 10-entry end |
| 0x004FA7EB | 0x0040BDA0 — secondary 12-entry begin, same physical folded helper |
| 0x004FA7F6 | 0x004FCE80 — secondary 12-entry end |

Corrected natural C++ now saves each group in one real reference, initializes one begin and end pointer before each loop, and copies each pointer to an ordinary const local before invoking update_option_frame. The compiled source has the native receiver/local/call grammar, without hand-written stride arithmetic, a fake helper, or compiler padding.

## Natural original 8-byte position-history copy

Original native motion gating checks dy then dx, and the original 33-entry history shift reads the complete 8-byte source IntPoint **before** calling the actual destination indexed accessor. The previous C++ local copy made MSVC insert a second unnecessary two-word stack copy (four extra mov instructions). A natural assignment from the source array element to the destination array element preserves the C++17-or-later RHS-before-LHS order and the game semantics of distinct adjacent entries. The complete genuine source still calls size() and at() with the original independent pointer and index values and writes history[0] from the real fixed position. There are no pointer casts or duplicate native calls.

## Complete pinned MSVC i386 whole game function comparison

| Whole-method check | Previous maintained source (post-699) | Corrected maintained source | Immutable original |
| --- | ---: | ---: | ---: |
| Body bytes | 3,077 | **3,114** | 3,111 |
| x86 instruction heads | 777 | **783** | 783 |
| Original mnemonic kinds in exact order | 766/783 | **783/783** | 783/783 |
| Original E8 versus candidate COFF REL32 | 67/67 | **67/67** | 67 |
| Original PE HIGHLOW versus candidate COFF DIR32 | 37/37 | **37/37** | 37 |
| Original ordinal physical E8 callee roles | 67/67 | **67/67** | 67 |
| Whole original strict byte exact | NO | **NO** | original |

**The parent is still NONEXACT.** The candidate is three bytes longer despite having 783/783 native mnemonic kinds in order; actual register choices, stack lifetime slots, branch encoding, relocation field positions and individual bytes still differ. Equal E8 counts and matched callee identities do not assert the target relocation sites are fully exact. No partial 3,111B original game bytes are credited. The separately original 555-byte Player movement child remains NONEXACT.

## Real whole-method evidence and validation scope

- .analysis/core698-player-main-option-iterator-probes.py and core698-player-option-loop-whole-results.json: twelve complete Player game method MSVC iterator source variants, rather than isolated leaves.
- .analysis/core699-player-true-script-indices-probes.py and core699-player-native-script-index-results.json: four immutable native script access arithmetic groups independently compared with nine actual whole C++ variants.
- .analysis/core700-player-history-copy-lifetime-probes.py and core700-player-history-copy-lifetime-results.json: seventeen complete whole-function natural history value-copy variants and their true original call counts.
- .analysis/core701-player-final-original-option-iterators.py and core701-player-native-option-iterator-results.json: cached option receiver, pointer and argument-local grammars, comparing full 3,111B original.
- .analysis/core702-player-maintained-script-options-history.json and build/core702-probes/PlayerMainFrame.obj with pinned MSVC receipt: actual newly maintained production C++ recompilation, verifying 3,114B/783 and 783/783 original ordered mnemonic heads, with 67/37 references by count.
- .analysis/core703-player-main-script-index-and-option-native-proof.json: independently scanned immutable original PE physical four script byte offsets and four original begin/end E8 call destinations.
- .analysis/core703-player-main-native-script-callee-proof.py/json: complete new candidate COFF compared in original ordinal order to all 67 immutable original E8 callee physical identities; no alias double counting.

Compiler: pinned MSVC 19.44.35211 x86 with /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc.

Only noncanonical src/PlayerMainFrame.cpp changed. Its canonical affected source-provider count is **ZERO**, and no public header, original PE, canonical strict object, match manifest or accepted exact ledger was changed. Only the entire affected Player parent was rebuilt and compared; no full/unfiltered cold replay was run. The game-authored exact total remains **504 complete functions / 179,611 disjoint original native code bytes**.
