# Window paced frame controller 370B — whole original native exact

The SHA-locked TH20 Japanese Steamless v1.00a executable contains
this distinct game-authored Window controller at 0x0041A030.
Its whole 370B/97-i386 body has SHA-256
287e51977fe5528aa1e5061d80d2306ee552ea5950090d48c95c453b86e0bfa8,
with 15 original E8 and 15 PE HIGHLOW relocation fields.

The natural C++20 source src/WindowFramePacedBoss370.cpp uses the
real WindowState receiver, Renderer queued-draw flush, FunctionChain
update and draw callbacks, D3D9 BeginScene / SetTexture(0,nullptr) /
EndScene, genuine 32-bit render-alpha 0xFF status, the independently
whole-exact 385B Window paced Presenter at 0x00419A50, original
elapsed-seconds clock, and folded frame-end member. No other game
owner is allocated or copied into invented storage.

The initial source was 357B/94 instructions. Every one of its 15
native E8 calls was shifted -13B because the original had a real,
compiler-emitted constant-true frame enable guard. Native disassembly
at +0x09 through +0x15 contains mov eax,1 / test eax,eax /
near conditional jump past the work. Expressing the actual
always-enabled control condition as a normal C++ if (true) wrapping
the complete frame body restores exactly 13 missing bytes and the
original branch, without dummy locals, manual NOPs, assembly or
instructions added solely as padding.

Pinned MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc yields full 370/370B, 97/97 instructions,
every original E8 and PE HIGHLOW physical position and destination,
and all 250/250 ordinary bytes. One new whole-authored original
game head/370 executable bytes receives exact credit. The 385B
Presenter, 433B controller, 583B synchronized sibling and folded
frame-end are separate heads and not credited again.

Independent physical native SHA/relocation proof:
scripts/verify-window-frame-paced370-native.py.

Only changed-source cold replay:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowFramePacedBoss370.cpp

The six existing strict Window source units importing the modified
shared Window view header were each also cold replayed individually
(31B, 164B, 385B, 574B, 433B and 583B), all 1/1 exact. The whole
dependency graph was never replayed. The separate 884B Window
scheduler remains source-present and NONEXACT.
