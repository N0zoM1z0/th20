# CORE/RECON-1078 — whole original 188B `std::_Func_class<void>::_Swap`, three missing authentic native forwarding calls

Locked TH20 Japanese Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x00414C80` is a complete **188B/63-instruction i386**
`std::_Func_class<void>::_Swap` standard-library function, original
whole-function SHA-256
`bd26afa8cbf43e1b3a8a8537b77b089f737ca7a740074f1d8ac3fbdb11d85858`.
This is not an invented game callback. The actual original **26B
`std::function<void()>::swap`** at `0x00417A90` physically calls
it at E8 `+0x0E`. That 26B method is itself a previously admitted
whole-exact native generic code head. The native game-owned **254B
queued-glyph task dispatcher** calls its own whole-exact 60B
`std::function<void()>::operator=(const&)`, which calls the same
26B swap method at native E8 `+0x25`.

## Original native control flow and the exact compiler delta

The original 188B `std::_Func_class` swap checks both callable
implementations' local-storage state, directly swaps internal
function implementation pointers when neither is local, and
otherwise constructs a real temporary 40B function object and
performs three genuine `_Reset_move` operations followed by
native destructor cleanup. Its original full body has exactly
**15 E8** and **one PE HIGHLOW** security cookie at offset `+0x07`
pointing to `0x005B25C0`; the security-cookie check is E8
`+0xB1 -> 0x005429EE`.

The 15 immutable original native E8 instruction offsets are:
`+0x16/+0x25` local-storage tests to `0x00414AF0`,
`+0x34/+0x3F` implementation getters to `0x00414AD0`,
`+0x48/+0x54` function implementation setter to `0x00414C60`,
`+0x5F` function default constructor `0x00413F80`,
**`+0x68/+0x7D/+0x92` three separate folded
`std::_Unfancy` calls to `0x0040B280`**,
`+0x74/+0x89/+0x9E` three native `_Reset_move` calls to
`0x00414BE0`, `+0xA6` native destructor `0x00414310`, and
`+0xB1` original cookie check. The original entire function ends
with `ret 4`.

The actual meaningful C++20 source in
[`GlyphTextQueuePump254.cpp`](../src/GlyphTextQueuePump254.cpp)
naturally instantiates the compiler's true
`std::_Func_class<void>::_Swap` through ordinary
`std::function` copy-assignment and swap in a real glyph task queue.
Using pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, the
complete generated template method is **161B/54-i386**, with
**12 REL32 E8/one DIR32**. It implements the same function swap
with the three function-pointer moves but **does not generate the
three original folded `_Unfancy` forwarding call sequences**.

The whole opcode/instruction comparison shows that the entire
**27-byte /nine-instruction** difference consists of **exactly
three live three-instruction pointer forwarding groups**, 9B each:
`call _Unfancy`, `add esp,4`, `push eax` at the first two sites,
and `push edx`, `call _Unfancy`, `add esp,4` at the third site.
They occur at native E8 offsets **`+0x68`, `+0x7D`, `+0x92`**
and affect the subsequent E8 and branch positions. That gap
is an authentic old-MSVC STL compiler lowering difference, not
three harmless alignment NOPs. It must **not** be fixed by
handwritten `call` instructions, inert compiler-shaping operands,
byte patching or claiming only 161 bytes of an original 188B
function.

Read-only [`verify-glyph-func-swap188-native.py`](../scripts/verify-glyph-func-swap188-native.py)
independently SHA-attests the **entire original 188B/63**, all 15
physical native E8 and one PE HIGHLOW, the full 26B native caller
with its genuine E8 `+0x0E`, and verifies that the actual source
naturally generates **161B/54 instructions** with 12 E8/one DIR32.
It confirms the three extra original native pointer-forwarding
sites and preserves all previously whole-exact canonical units
for the 26B swap, 60B assignment and 254B game dispatcher.

**Status: SOURCE-PRESENT, NONEXACT**, with an independently verified
physical 188B native extent and genuine original STL semantics.
There is **no** canonical strict unit or game-authored exact byte
credit for the 188B parent. Source-scoped exact replay of the one
accepted glyph task dispatcher source confirms its 10/10 previously
accepted whole-native game and standard-library functions still
match; the original 188B is tracked separately. No entire-repo cold
replay ran.

```sh
scripts/repo-python scripts/verify-glyph-func-swap188-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueuePump254.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
