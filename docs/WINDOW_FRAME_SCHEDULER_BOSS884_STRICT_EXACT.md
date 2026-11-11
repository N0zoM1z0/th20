# Window frame scheduler Boss 884B — complete original strict native exact

The original TH20 Japanese Steamless v1.00a function at 0x004193E0
is a game-authored **884B /239 x86-instruction Window frame scheduler**.
Complete original SHA-256:
615f5ad822a12bdad16238d5e88b9dc9e965eda8748a019cc4b2c7ef4f4bdeb6.

The maintained src/WindowFrameSchedulerBoss884.cpp now reproduces the
**entire original 884/884 native bytes**, not merely the destination
roles. All **32 E8 call sites and 21 PE HIGHLOW data fields** match
the original physical positions and target identities. The other
**672/672 ordinary code bytes** are identical. The source has a
fresh pinned-MSVC 19.44 C++20 x86 object and canonical strict
1/1 source-scoped cold replay receipt.

The actual game scheduling code is preserved:

- Six samples from the separately exact 346B WindowState seconds
  clock, plus the original 1.0/60.0, 1000.0, 2.5, 0.019 and 0.013
  double constants. It maintains real WindowState frame deadlines
  and frame delay records at +0x20C8, +0x20E8, +0x20F0 and +0x20FC.
- Four real 12B RepeatCounter records at Window+0x2104, selected by
  the exact 31B active-counter getter 14 times.
- Native two-DWORD D3DRASTER_STATUS output, with real InVBlank
  and ScanLine fields. Its original debug build also stores the
  previous scanline in an observed local at [EBP-0x30], first
  setting the local to zero at +0x1BB and then copying the raster
  scanline at +0x206. Both writes are established from immutable
  native code; these are observed source-value lifetimes, not
  synthetic stack padding.
- Win32 Sleep(1) during the real raster polling interval,
  real Direct3D9 device GetRasterStatus at vtable +0x4C,
  original 574B screenshot/scene exact callee, D3D9 Present at
  +0x44, and on error the authentic Graphics and Animation
  Renderer lost/reset/restored path at vtable +0x40.
- The separately exact 32B frame-clock dispatch and genuine
  timeBeginPeriod(1), Sleep(delay), timeEndPeriod(1) WinMM pacing.

## How the final native code was recovered

The initial full C++ function had the original 32 callee and
21 data destination roles but compiled to 890B and was NONEXACT.
Replacing manual vtable access with actual IDirect3DDevice9
methods and native D3DRASTER_STATUS reduced it to 866B while
preserving every target role.

A literal comparison of original disassembly identified the
genuine previous-scanline stack copy (0x1BB / 0x206) and the
double seconds sample stored at +0x320. Reinstating these
observed storage lifetimes and moving the captured scanline
declaration into its actual polling scope produced a
**883B/238-instruction near-exact** candidate, with 22/32 E8
physical sites aligned.

The last byte and instruction came from placing the real
D3D9 Reset device pointer inside its own lexical scope
immediately after Renderer device-loss notification. MSVC
then naturally emits the original NOP at +0x2C6, rather than
a handwritten instruction or fake local. The result is
**884B/239-instruction strict whole exact**, every relocation
and every ordinary byte in its original place.

Evidence: scripts/verify-window-frame-scheduler884-native.py
also independently confirms original SHA, all 32 physical
call destinations, all 21 actual PE data destinations, locked
literal double constants and the whole canonical source
receipt. The historical NONEXACT frontier verifier path
delegates to this accepted exact proof.

Only this source had a cold compile/replay:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowFrameSchedulerBoss884.cpp
    scripts/repo-python scripts/verify-window-frame-scheduler884-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target

**One distinct game-authored whole-exact original function,
884 newly accepted original bytes.** Its already exact 31B
RepeatCounter, 346B Window seconds clock, 574B screenshot,
and 32B dispatch children are not double-counted. The full
playable game is still not built, linked or runtime validated.
