# Window frame scheduler Boss 884B — complete typed source, NONEXACT

Target: Japanese Steamless TH20 v1.00a, immutable SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.
The game-authored complete original Window frame scheduler at 0x004193E0
is 884B /239 i386, SHA-256
615f5ad822a12bdad16238d5e88b9dc9e965eda8748a019cc4b2c7ef4f4bdeb6.
Its real PE has **32 E8 calls and 21 HIGHLOW relocation sites**.

The maintained src/WindowFrameSchedulerBoss884.cpp recovers the entire
WindowState source path as typed and compilable C++20:

- Calls the existing exact 346B WindowState seconds clock six times.
  Computes the original sleep budget from WindowState fields +0x20C8,
  +0x20E8 and +0x20FC and the genuine 1.0, 60.0, 1000.0 and 2.5
  double constants in original PE memory.
- Consults the exact 31B active RepeatCounter selector exactly fourteen
  times, with real +0x2100 current-index, +0x2104 12B counter array,
  native budget comparison order, 15-step saturation and clamping.
- Maintains the separate WindowState current-draw clock +0x20F0,
  original 0.019 and 0.013 double frame wait thresholds, real
  Graphics +0x104 predicate, and device poll at vtable +0x4C,
  with Windows Sleep(1) only on the real waiting path.
- Performs the original Window scene/frame update 0x00419760, actual
  Graphics COM present at vtable +0x44 and recovery/reset at +0x40
  when the presentation result signals failure. This preserves the
  real Graphics, Animation renderer owner, device presentation
  record at 0x005C4E24 and reset completion state at 0x005C586C.
- Calls the independently exact 32B Window/Frame dispatch and the
  original WinMM timeBeginPeriod/Sleep/timeEndPeriod pacing functions,
  then updates the real WindowState previous-frame timestamp.

Borrowed WindowState, Graphics, Animation renderer and D3D interfaces
have no fake allocated storage. The parent is not linked or runtime
tested.

## Real pinned-MSVC variants

The source was developed with actual MSVC 19.44 x86 C++20
/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc.

More than two dozen real compilations tested authentic branches,
member offsets, COM vtable byte addressing, stack evaluation order and
different equivalent device-poll loop conditions, not manual NOPs or
invented local variables.

| Compiled source variant | Complete candidate / x86 | Native E8 physical sites |
| --- | --- | --- |
| Initial typed all-stage function | 916B /245 | 3/32 |
| Restore original repeat/wait branch order | 899B /242 | 9/32 |
| Correct +0x20E8/+0x20F0 fields and budget comparison | 899B /242 | 11/32 |
| Direct byte-offset COM virtual methods and loop variants | 875–892B /235–241 | 11–12/32 |
| Current maintained candidate | **890B /240** | **12/32** |

The full current candidate has **32 compiler E8/REL32 and 21
DIR32**, matching **all 32/32 native callee target roles** and
**21/21 PE data destination roles** in exact original order.
The initial eleven physical E8 addresses agree; total physical
alignment is **12/32 E8 and 6/21 HIGHLOW**. Only **279 ordinary
bytes** are equal at their same positional byte offsets after masking
the candidate relocations. Thus original 884B/239i and candidate
890B/240i remain **NONEXACT**. This new source adds zero original
parent-game exact byte credit.

The original SHA-pinned independent proof is
scripts/verify-window-frame-scheduler884-native-frontier.py.
It attests the entire real PE function, all E8/HIGHLOW original
offsets and targets, true literal doubles, and independently exact
31B repeat /346B seconds /32B frame dispatch child receipts. It
explicitly rejects whole parent exactness; source presence is not
misrepresented as byte-exact reconstruction.

## Bounded reproduction

There is no canonical accepted exact unit for this nonexact parent.
Compile its source alone and compare the full resulting COFF; do not
run full-graph cold replay or claim 884B exact:

    nice -n 15 scripts/compile-probe.sh src/WindowFrameSchedulerBoss884.cpp build/gptweb20-window884/WindowFrameSchedulerBoss884.obj /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
    scripts/repo-python scripts/verify-window-frame-scheduler884-native-frontier.py
    scripts/repo-python scripts/validate-tracking.py --require-target

The remaining source lowering frontier includes genuine COM method
pointer/return lifetimes and the device poll input/output stack
ordering. The separately exact 31B RepeatCounter leaf was accepted
in a preceding commit and must not be double counted.
