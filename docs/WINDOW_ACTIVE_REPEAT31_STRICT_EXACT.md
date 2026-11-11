# Window active RepeatCounter selector 31B — whole strict exact

Japanese Steamless TH20 v1.00a original native head 0x0041CA50:
31 bytes, 11 i386 instructions; original complete SHA-256
c11144f7911afde92376e350a33c7d514a79ac683cf11885551195b85e08648b.

The source src/WindowActiveRepeat31.cpp implements the actual native
WindowState frame period selector. It reads the real +0x2100 index and
multiplies by the 0x0C stride of WindowState RepeatCounters starting at
+0x2104. Its borrowed NativeWindowFrameScheduleView adds no storage or
synthetic object. An initial temporary WindowState* caused an extra
stack slot (39B); direct meaningful this/field expressions produce
the exact 31B body without artificial locals, hand-assembled instructions,
padding or NOPs.

Pinned MSVC x86 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc compiles the complete 31/31 native bytes with 0 COFF
relocations. The original has zero E8 and zero PE HIGHLOW fields.
The enclosing 884B Window frame scheduler calls this real head at 14
distinct original physical E8 sites, independently SHA/disassembly
attested by scripts/verify-window-active-repeat31-native.py.

Only this source translation unit was cold replayed:

    window_active_repeat_31: exact (31/31 bytes)
    Exact replay: 1/1 units, 1 cold objects

Reproduce:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/WindowActiveRepeat31.cpp
    scripts/repo-python scripts/verify-window-active-repeat31-native.py

One new game-authored whole original exact head, 31 native bytes.
The 884B frame scheduler remains nonexact; its bytes are not credited
through an exact child call.
