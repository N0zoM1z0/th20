# CORE/RECON-1119 — original Card registration 121B and two 13B C callbacks strict exact

Target: immutable TH20 Japanese v1.00a Steamless `resources/th20.exe` (SHA256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
Three **distinct game-authored physical heads** were recovered and checked
against complete original instruction and relocation extents:

| Original address | Function and true behavior | Native and pinned MSVC | Original relocation roles |
| --- | --- | --- | --- |
| `0x00487B10` | Card setup; `bind_context(index)`, publish Card through `session.context(index).set_card`, register disabled update at priority `0x28`, disabled draw at `0x0C`, reset Card Timer to zero, return zero | **121/121B**, 41 i386 | **6 E8 /3 HIGHLOW** |
| `0x004885D0` | Native `int __cdecl` update callback, returns result of `0x00486F60` | **13/13B**, 6 i386 | **1 E8 /0 HIGHLOW** |
| `0x00488680` | Native `int __cdecl` draw callback, returns result of `0x00487590` | **13/13B**, 6 i386 | **1 E8 /0 HIGHLOW** |

Full original whole-function SHA-256 respectively:

- 121B registration: `291171ffef108b276b58d792a2fded039dc512edd792827bbb7276ba46a46ba8`
- 13B update bridge: `4252c6deb271e04cca8d29c3fb3b7ad05f0cb9bf3b66ec72fd012cb4429ac090`
- 13B draw bridge: `47116c4f8122744b9b4eed866079a6908916c42fdf551011c91138bef77a7855`

The original 121B registration embeds **physical pointers** to the two
callbacks at PE HIGHLOW sites `+0x37` and `+0x50`, plus a `Session` pointer
at `+0x1A`. Its six real original E8 calls occur at `+0x10`
(`Card::bind_context`), `+0x1E` (`Session::context`), `+0x2D`
(`Context::set_card`), `+0x3D` (`register_update_disabled`), `+0x56`
(`register_draw_disabled`) and `+0x6C` (`Timer::operator=(0)`). The
`FunctionChain` callback type is 32-bit `int (*)(void*)`, **not** void.
A first `void` callback experiment produced an additional compiler `nop`
and 14B; the real integer-return callback naturally emits **13B with no
artificial opcode**. Both bridges hold their proper E8 destination.

The native code is reconstructed as the natural C++20
[`CardRegisterCallbacks121.cpp`](../src/CardRegisterCallbacks121.cpp) and
[`CardCallbackBridges13.cpp`](../src/CardCallbackBridges13.cpp), with a
borrowed non-allocating receiver declaration in
[`NativeCardTickViews.hpp`](../src/NativeCardTickViews.hpp). Pinned
MSVC 19.44 x86 `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` emits **all 121, 13, and 13 original bytes**, after correct
COFF relocation matching. Original E8/HIGHLOW site offsets and target
symbols are recorded in the new strict manifests. The independently
pinned, original-only verifier
[`verify-card-registration121-bridges13-native.py`](../scripts/verify-card-registration121-bridges13-native.py)
checks complete original SHA, all branches/calls/pointers, compiled
objects and canonical cold build receipts.

Only the **five affected source files** were cold-replayed: this new
121B owner, the two 13B callbacks (one object), and the existing
exact Card 875B Boss, 32B HUD clear and 23B flag getter. All **6/6
original function units** passed strict replay across **5 MSVC objects**.
No full graph replay was performed.

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardRegisterCallbacks121.cpp \
  --source src/CardCallbackBridges13.cpp \
  --source src/CardTickBoss875.cpp \
  --source src/CardFlag8Getter23.cpp \
  --source src/CardTickUiClear32.cpp
scripts/repo-python scripts/verify-card-registration121-bridges13-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

**Three new authored whole-exact original heads /147 native bytes**. The
875B Card update parent was already accepted and is not credited again.
The downstream original **797B Card Draw** at `0x00487590` remains
**NONEXACT** in this step, as do the unrelated 1,896B Card Start and
6,073B battle-control Bosses. No complete link or playable game is claimed.
