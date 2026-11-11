# Window synchronized no-wait frame controller 583B — strict whole-native exact

Japanese Steamless TH20 v1.00a original 0x00419DE0: **583B /
138 i386 instructions**, SHA-256
8be338e7187df3309e96af13f8d550ce3ebed483e99682ba4376b5a8a0e08b5f.
The original function contains **16 E8 and 20 PE HIGHLOW fields**,
independently identified from the pinned executable.

Maintained source src/WindowFrameNoWaitBoss583.cpp is real WindowState
frame synchronization. It obtains seconds from the already exact
346B clock, corrects backwards time on +0x20C8/+0x20D0/+0x20D8,
and sleeps 1ms when the true 1000.0 multiplier and original frame
time threshold require. When the elapsed deadline has passed,
it advances the next-update timestamp in increments of
1.0/60.0 seconds and executes the actual Renderer/FunctionChain
frame: native 611B FunctionChain update, 587B draw, D3D9
BeginScene, staging buffers reset, actual DWORD 0xFF to process
global 0x005C5AF8, fog reset, SetTexture(0,nullptr), EndScene,
the already strict 164B no-wait Window Presenter, and elapsed
duration write at 0x005C5B18. The existing folded frame-end
method is reused without duplicate original-byte credit.

The source derives from the sibling whole-exact 433B Window
controller, adding the genuine Window clock/backwards-time
branches, frame pacing Sleep import and deadline gating. On its
**first complete MSVC probe**, the generated function had the
native **583B/138-instruction** layout. Switching its temporary
borrowed receiver declaration to the existing shared Window
receiver preserves complete identity.

Pinned MSVC 19.44 x86 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc reproduces all **16/16 E8 and
20/20 PE HIGHLOW physical offsets and destinations**, every
**439/439 ordinary original byte**, and real compiler-generated
NOPs at +0x8E, +0x214 and +0x240. The canonical whole source
is **583/583B exact** without fake locals, handwritten padding,
instruction literals or a proxy object allocation.

Only relevant sources were cold replayed: new 583B 1/1,
and the five existing units that depend on the changed shared
Window header — 31B, 164B, 385B, 574B, 433B — each 1/1.
No all-graph cold replay occurred.

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowFrameNoWaitBoss583.cpp
    scripts/repo-python scripts/verify-window-frame-no-wait583-native.py

One distinct new game-authored original whole-exact head /
**583 original bytes**, in addition to the sibling 433B Boss
and existing 164B Presenter. The separate 884B frame scheduler
is still NONEXACT.
