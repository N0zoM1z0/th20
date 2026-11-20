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

The complete owner lifetime has now been expanded beyond those wrappers:

- `0x00422D40` — 67B real allocator body: `operator new(0x44)`, explicit
  null branch, original zero-memory helper `0x0040C080`, and direct
  constructor call. Whole strict exact.
- `0x004233B0` — 187B ScreenInf constructor: true TaskInfo base, derived
  vtable, eight scalar fields, Timer and diagnostic. Whole strict exact,
  including the original five-byte `INT3` alignment in the 192B comparison.
- `0x00425070` — 29B shutdown callback: the generic virtual destructor
  release at `0x0041F7C0`, real process allocator global and explicit local
  argument clear. Whole strict exact.

The 37B wrapper and 81B factory remain separate from the 637B initializer;
none of these boundaries double-counts the others. The factory's diagnostic
label now uses a named native-address symbol, avoiding compiler-generated
`$SG` literal labels that change between standalone cold builds. The
independent native lifecycle audit is
`scripts/verify-screen-inf-lifecycle-native.py`. More ScreenInf per-mode
update/draw bodies remain open.
