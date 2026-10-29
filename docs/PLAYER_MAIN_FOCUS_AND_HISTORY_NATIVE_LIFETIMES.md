# CORE/RECON-673 — complete Player main frame: native two-focus results and 33-slot history lifetimes

**Later [CORE/RECON-704](PLAYER_MAIN_NATIVE_SCRIPT_INDICES_AND_OPTION_LOOPS_3111.md):** immutable native original script slots [1..4], cached begin/end per option group and one-value history copy now yield **3,114B/783 C++ instructions, 783/783 native mnemonic kinds in order**. Original 3,111B parent remains NONEXACT; the measurement below is historical.

**Later [CORE/RECON-699](PLAYER_MAIN_3111_NATIVE_XY_ACCUMULATION_ORDER.md) update:** the maintained nonexact parent now emits **3,077B/777 instructions**, original ordered mnemonic alignment **766/783**, by restoring original X-then-Y residual update order. The 3,093B measurement below is the older pre-699 checkpoint, not current exactness.

**The complete original 3,111-byte, 783-instruction Player::update_main_frame at 0x004F9C30 remains NONEXACT.**
All machine-code evidence was independently read from the original
Japanese TH20 v1.00a Steamless executable (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`),
not from an older interpretation of project notes. The maintained
complete typed owner is `src/PlayerMainFrame.cpp`.

## Original focus state has TWO real input reads and one-use DWORD results

The native original reads focus input mask 8 at two distinct points;
it may not be cached into one read. Each read checks negative view
and the nullable game input view, returning zero if absent and making
one physical replay mask call if present. The resulting DWORDs have
independently visible lifetime and downstream state changes:

- The first native focus result lives at **[ebp-0x48]**. At original
  `+0x52F` the game performs `cmp dword ptr [ebp-0x48],0`, followed by
  the two DWORD assignments to **[ebp-0x4C]** at `+0x535` and `+0x53E`.
  It compares this full DWORD to zero-extended focused byte
  `Player+0x204C` and copies the actual 8-byte point from `+0x620`
  to `+0x630` if focus changes.
- The second native result lives at **[ebp-0x50]**; original `+0x5AE`
  compares its DWORD to zero, `+0x5B4/+0x5BA` write the one-byte
  boolean temporary **[ebp-0x11]**, and `+0x5C1` reads that byte
  to assign `Player+0x204C`.

The older maintained source introduced separate `first_focus`,
`new_focus` and `second_focus` locals, creating extra compiler-generated
copies and making the first comparison use an intermediate bool BYTE.
Under authentic pinned MSVC `/Od`, using the original conditional
expression directly at each **separate** consumer reproduces both native
DWORD comparison slots and the original second boolean byte slot without
invented variables, volatile, assembly, or a fake helper. Only the
original conditional input function can be called, and it remains called
twice when focus is evaluated. Private tests include direct-first,
integer-typed, byte-cast, ternary, and separately/directly used second
input results, all compiled as the complete game parent.

## Movement gating and the actual 33-slot history copy

The original movement guard tests **dy first** at `+0xA2D` using
`[ebp-0x10]`, then dx at `+0xA33` using `[ebp-0xC]`. C++
`if (dx || dy)` is game-logically equivalent but compiles in the
wrong order. The maintained source now uses `if (dy || dx)` and the
fresh whole MSVC object reproduces both physical operand locations
in original order.

The original 33-slot history shift is a genuine backwards source-to-
destination 8-byte `IntPoint` copy. It calls the real
`PlayerValues<IntPoint,33>::size` for the loop boundary and again
**immediately before** computing the source `n-2-index` argument,
then again to compute destination `size-1-index`. The previous
source named the middle return `const auto n`, causing an unnecessary
store/reload into a local before the subtraction. The maintained
source computes `points_20fc.size()-2-index` directly at the original
call site. It retains an actual by-value `const IntPoint saved`, the
original method's separate destination indexed call, and the final
write to `points_20fc.at(0)`. We did **not** choose a purely
reference-based history copy that eliminates the original 8-byte
saved value or changes overlap/aliasing semantics simply to reduce
code size.

## Complete C++ body vs immutable original

| Evidence | Before this correction | Updated full source | Immutable original |
| --- | ---: | ---: | ---: |
| Method bytes | 3,126 | **3,093** | 3,111 |
| x86 instructions | 788 | **779** | 783 |
| Original mnemonic kinds aligned in order | 763/783 | **764/783** | 783 |
| Whole original E8 vs COFF REL32 | 67/67 | **67/67** | 67 |
| Original PE HIGHLOW vs COFF DIR32 (count only) | 37/37 | **37/37** | 37 |
| Original physical E8 callee *roles* in ordinal order | 67/67 | **67/67** | 67 |
| Complete strict native body accepted | NO | **NO** | original |

Aligned displayed-operand comparison fell from 366 to **265** because
source variable lifetimes alter many subsequent frame slot allocations;
that diagnostic is NOT an original-byte match percentage. The
independently asserted two original focus DWORD operand locations and
the original dy-before-dx branch operands are a **local opcode-level
improvement**, while the full function remains nonexact with unresolved
stack lifetimes, later history and option iteration shapes, and real
relocation placements. The 555-byte `Player::apply_move_delta`
child remains a distinct NONEXACT full original function; matching
its call *identity* is not matching its body.

## Real bounded compiler/source evidence

- `.analysis/core670-player-history-native-source-probes.py/json`:
  14 complete-body history source variants, including rejected
  reference/aggregate/direct-assign forms. The original 67/37 field
  counts stayed unchanged on the accepted direct-size form.
- `.analysis/core671-player-focus-evaluation-source-probes.py/json`:
  genuine full-function C++ focus-typing, first/second independent
  input reading and direct-conditional variants. The accepted
  variant preserves native original 32-bit comparison slots.
- `.analysis/core672-player-maintained-focus-history-native-proof.json`:
  actual final maintained C++ object, disassembled against the entire
  independently verified original, with asserted original focus and
  dy-first stack operands.
- `.analysis/core672-player-main-all-67-callee-proof.py/json`:
  independent all-67 original E8 ordinal callee role reconciliation,
  including whole-byte folded-compatible helpers and the separately
  nonexact movement child; no duplicate original-byte credit.
- `build/core672-probes/PlayerMainFrame.obj` and input-closure receipt:
  pinned MSVC 19.44.35211 x86 `/std:c++20 /Od /Ob0 /GS /Gy /Zl
  /arch:SSE2 /fp:precise /EHsc` full maintained source build.

**Affected existing strict canonical units: zero.** The only changed
source is the noncanonical `src/PlayerMainFrame.cpp`. There are no
shared-header, original PE, canonical object, or accepted unit changes;
only this whole 3,111-byte original boss was compiled and compared.
No unfiltered whole-graph cold replay was run. Accepted authored
coverage stays at **499 complete functions / 179,444 original bytes**.
