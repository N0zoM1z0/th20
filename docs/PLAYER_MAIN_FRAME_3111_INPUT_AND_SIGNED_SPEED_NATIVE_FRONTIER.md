# CORE/RECON-655 — original Player frame input, Timer and signed speed control

**The complete game-owned Player::update_main_frame at 0x004F9C30 is still NONEXACT.**
The locked original Japanese TH20 v1.00a Steamless executable is
resources/th20.exe (SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897).
Its original whole method is **3,111 bytes, 783 native x86 instructions**.
The maintained full function is src/PlayerMainFrame.cpp.

## Genuine original input evaluation lifetimes

The immutable original checks directional input masks 0x50, 0x60,
0x90, 0xA0, then 0x20, 0x10, 0x40 and 0x80. It stops on the
first match. Each check rejects a negative input view and an absent
view pointer before invoking the true InputButtonState replay read.
The first four tests compare the entire masked word against the
requested diagonal combination; the last four test nonzero.

The previous source materialized eight named const word locals
even though each result was only used once. Pinned MSVC /Od generated
additional intermediate stack copies. The new source places each
genuine short-circuit conditional input read directly into its
corresponding comparison. It preserves one and only one game input
E8 per valid tested direction, the original null/invalid behavior,
all native masks, and the short-circuit decision order.

## Four signed speed-selection decisions

Original native offsets +0x751, +0x781, +0x7F3 and +0x823
all use **signed JL** to enter the lower-speed branch when
the Player+0x67C direction is less than 5. Its first executed
branch selects the higher-speed field when direction >= 5.
Focused upper/lower sources are Player+0x20C0 and +0x20B8;
unfocused upper/lower sources are Player+0x20BC and +0x20B4.
The game makes independent x and y selections.

Previous source treated Player+0x67C as unsigned, generating
unsigned JAE decisions and redundant local copies. This differs
in behavior for negative direction indices and in emitted code.
The new C++ interprets the original 32-bit direction as signed
and selects >= 5 first using an ordinary local. All four real
signed JL branches now appear in the complete compiled parent.
Integer motion multiplication retains defined modular 32-bit
arithmetic and original field reads.

## Timer lifetime and positive completion control flow

The original native E8 at +0x19D invokes Timer::equals(8),
discarding the return, directly before the real at_least(16)
call. The original uses a positive completion test and a JE
to skip clearing animations and resetting the movement mode
when below 16. The standard C++17 if-initializer retains both
real original calls and their order while avoiding a spurious
compiler NOP that separate source statements emitted. No
invented call, no volatile, no target byte edit or ASM.

## Complete original versus genuine pinned MSVC C++ comparison

| Native evidence | Previous source | Corrected full source |
| --- | ---: | ---: |
| Original body | 3,111B / 783 x86 | Same |
| Generated body bytes | 3,254 | **3,110** |
| Generated x86 heads | 808 | **784** |
| Original mnemonic heads aligned in order | 733/783 | **758/783** |
| Identical operands in aligned instructions (diagnostic) | 286 | **359** |
| Original E8 vs CXX REL32 | 67/67 | **67/67** |
| Original HIGHLOW vs CXX DIR32 (counts only) | 37/37 | **37/37** |
| Whole original parent strict exact | NO | **NO** |

**The parent is still NONEXACT.** It has 1 fewer byte but 1
additional instruction relative to the actual original, and
the 104 relocation fields have not all been accepted as
matching physical locations/targets. The separately checked
67 original physical E8 call identities retain 60 independently
confirmed matches, **one confirmed wrong call** and six
folded or unknown target roles. The known wrong call is native
0x004FA273 targeting the original 45-byte
EffectAnimationHandle::matches_value(0) at 0x00449430;
the currently typed source instead invokes the distinct
45-byte AnimationHandle::operator!=(0) at 0x0047C650.
These are not equivalent native bodies. Original Player constructor
calls AnimationHandle constructors directly at +0x60C/+0x610,
so an unrelated wrapper reinterpret cast would violate C++
object lifetime and is NOT an acceptable workaround.

## Bounded evidence and replay scope

- .analysis/core649-player-timer-branch-source-probes.py/json:
  whole-parent Timer control grammar tests.
- .analysis/core650-player-input-direct-tests.py/json:
  incremental eight-input and subgroup source variants.
- .analysis/core651-player-frame-native-signed-speed-probes.py/json:
  the actual four signed original comparison branches.
- .analysis/core652-player-speed-signed-native-branch-probes.py/json:
  natural local, ternary, and conditional-multiply trials.
- .analysis/core653-player-main-combined-control-probes.py/json:
  independent combinations in complete whole method builds.
- .analysis/core654-player-main-maintained-native-frontier.json:
  actual maintained C++ full-source result after fresh compilation.
- .analysis/core654-player-main-physical-callee-audit.py/json:
  67 original native E8 callee identities and source COFF roles.
- build/core654-probes/PlayerMainFrame.obj and receipt: ignored,
  locked MSVC 19.44.35211 x86 full source object under
  /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc.

No public header, original target, already strict source/receipt,
or canonical match manifest was changed. This source is
not a configured canonical-unit provider: **zero previously accepted
strict units are affected**, so there was no unrelated or full
cold replay. Canonical game-authored exact totals remain
**499 functions / 179,444 original native bytes**.
