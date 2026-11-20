# ScreenInf's 37B default-priority wrapper and 81B allocation factory — whole exact

The native Japanese TH20 Steamless binary has a **three-stage real C++
ScreenInf creation chain**. First, 37-byte original `0x00425090` receives
five scalar inputs, appends priority `0x6D` and view `0`, and forwards all
seven arguments to `0x004250F0`. Second, 81-byte original `0x004250F0`
reads the actual `process_allocator` at `0x005B8894`, passes the original
`"D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\screen.cpp:580 ScreenInf"`
diagnostic allocation label at `0x0056D768` to `0x00422D40`, checks
for a null object, installs the chosen view at `ScreenInf+0x40`, then
initializes the allocated 0x44-byte object through the **whole exact
637B** ten-mode initializer `0x00423BF0`.

Sources are `src/ScreenEffectDefault37.cpp` and
`src/ScreenEffectFactory81.cpp` with shared typed view
`src/NativeScreenEffect.hpp`. The allocation call uses a non-allocating
receiver alias for the real allocator so this source does not invent a
second object or compiler shape. All caller operands and both original
source-level branches are expressed as natural C++, no assembly,
padding bytes or inert machine instructions.

Scoped pinned MSVC x86 C++20 cold builds and strict original-site relocation
replays verify **37/37 bytes with one E8**, and **81/81 bytes with two
E8 and two original PE HIGHLOW pointer fields**. The original file-label
string is independently verified at the pinned target address, rather
than inferred from a user-supplied source name. The 637B initializer
retains its independent `screen_init_boss_637` strict replay including
the real compiler-generated 40-byte table (not double-counted).

```sh
scripts/repo-python scripts/replay-exact-units.py --source src/ScreenEffectDefault37.cpp
scripts/repo-python scripts/replay-exact-units.py --source src/ScreenEffectFactory81.cpp
scripts/repo-python scripts/replay-exact-units.py --source src/ScreenInitialize637.cpp
```

The 67B allocator template at `0x00422D40` and 187B object constructor
at `0x004233B0` are separate source boundaries, not implicitly exact from
these wrappers. More ScreenInf per-mode update/draw bodies are open.
