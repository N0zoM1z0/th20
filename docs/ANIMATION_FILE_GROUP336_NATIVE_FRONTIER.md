# CORE/RECON-1095 — entire 336B native Renderer ANM group parser, 2B nonexact stack-origin frontier

Immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0044EBF0` is a complete **336B/83-instruction i386**
game Renderer ANM resource-group parser, whole native SHA-256
`0ab86e2cc9985d672ff96e5fe0e9ae4b52b5a02c69b63e87a310344ae21b3a67`.
It is the real physical parser invoked by the independently
WHOLE-EXACT **1,022B AnimationFile loader** `0x0044A700` at original
E8 **`+0x332 -> 0x0044EBF0`**. The caller obtains the actual Renderer
process-global `0x005C0028` immediately before passing the file,
index and group header. Its true native original callee ends in
**`ret 0x0C`**, receiving three by-value stack arguments as a
Renderer-owned `__thiscall` method, not an AnimationFile member.

The maintained typed C++ method is
[`NativeRendererAnmGroupView::parse_group_44ebf0`](../src/AnimationFileGroupParse336.cpp)
under the already verified non-allocating Renderer and AnimationFile
borrowed types in [`NativeAnimationFileLoadView.hpp`](../src/NativeAnimationFileLoadView.hpp).
The source is **SOURCE-PRESENT, NONEXACT**, with a complete natural
**336B/83-i386 C++20 compiler body** and no invented native code
bytes.

## Original header, resource and error behaviors

The real group header has signature at **+0x00** (the target
requires `8`), unsigned sprite count at +0x04 as 16-bit, script
count at +0x06, embedded name offset at **+0x10**, a texture mode
byte at **+0x20**, and the linked next-header byte distance at
**+0x24**. The original:

- For a null group pointer, calls the actual
  `0x00454230` game diagnostic using original CP932 error message
  `0x0056E428` and real shared diagnostic context at `0x005C0678`,
  then returns `-1`.
- For a non-null group with signature different from `8`, calls
  the same diagnostic with the distinct original version-error
  string `0x0056E464`, returns `-1`, and does not touch any texture
  record.
- For a valid group whose native flag byte at `header+0x20`
  is zero, forms an embedded texture path at
  `reinterpret_cast<const char*>(header)+embedded_name_offset`,
  checking the original first byte against `'@'`. If that first
  byte is `'@'`, no external texture file is loaded.
- Otherwise copies the narrow name through the whole-exact
  original **39B** `sprintf_s<260>` at native E8 `+0xC6` with
  real ASCII `%s` data at `0x0056E0E4`, then calls the separate
  original **583B** game resource reader at E8 `+0xDE` in mode `1`,
  passing a genuine local byte-count output. On failure, logs the
  named texture with the original CP932 diagnostic `0x0056E488`
  and returns `-1`.
- On successful external load, writes actual file length to the
  existing 24B `TextureRecord.external_size` at offset `+0x08`
  and actual returned texture bytes to `TextureRecord.external_bytes`
  at `+0x04`, indexing the texture table at the real
  `AnimationFile+0x58` by the actual 24B stride.
- Returns `1` for an accepted group (including groups with a
  marked internal texture or the `'@'` path exclusion).

The native source uses the three genuine Japanese CP932
error strings from the immutable game, not invented UTF-16 diagnostics.
The logger object is the already reconstructed actual shared
`DiagnosticLog diagnostic_log` from [`DiagnosticLog.hpp`](../src/DiagnosticLog.hpp),
whose native `report_log_error` is independently whole exact at
`0x00454230`. One earlier C++ probe instead declared a speculative
`NativeAnmLoadDiagnostic` and a duplicate logger function name; a
later review corrected these false owners to the existing real
`DiagnosticLog` type and checked that all 14 native E8/HIGHLOW roles
and the same two remaining original ordinary byte differences hold.
The ANM group `+0x20` field was also corrected from a premature
`uint32_t` label into a genuine `uint8_t flag_20` with three byte
reserved slots. The original x86 reads it with `movzx ... byte ptr`;
this header representation is important for the full 1,022B parent,
and does not alter the established 0x28B header size or offset.
An independent second private, typed 336B source candidate using
these true owners generated the same complete 336B/83-i386 body and
the same 278/280 original ordinary bytes. Its meaningful alternative
is retained under ignored `.analysis/`, avoiding conflicting duplicate
method definitions in maintained `src/`.

## Complete original E8/PE evidence and two missing ordinary bytes

The native original has six real E8 sites:

| E8 site | Physical original target |
| --- | --- |
| `+0x33`, `+0x61`, `+0x106` | three genuine uses of the original diagnostic `0x00454230` |
| `+0xC6` | native 39B `sprintf_s<260>` `0x00429120` |
| `+0xDE` | whole-exact 583B resource reader `0x00410AA0` |
| `+0x145` | native security-cookie check `0x005429EE` |

Its eight original PE HIGHLOW fields are security cookie
`+0x0A ->0x005B25C0`; three error-string pointers
`+0x2A/+0x58/+0xFD -> 0x0056E428/0x0056E464/0x0056E488`;
three references `+0x2F/+0x5D/+0x102` to the same original
diagnostic object `0x005C0678`; and the original narrow `%s`
`+0xBB ->0x0056E0E4`. The full C++ source naturally emits all
**six REL32/eight DIR32** at the correct 14 original positions,
all physical call/data destinations, the genuine 83 instructions
and original `ret 0x0C`.

With pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`,
the generated method is exactly **336B/83 instructions**, with
**278/280 equal nonrelocated original bytes**. The only ordinary
mismatches are original function offsets **`+0x05`** and
**`+0x1B`**, both physical original stack-frame/local-slot
operands:

```text
Original stack allocation: sub esp,0x120
Candidate allocation:      sub esp,0x11C
Original initial zero slot: [ebp-0x120]
Candidate initialized size: [ebp-0x10C]
Original 336B/83; current source 336B/83, 6 E8, 8 HIGHLOW/DIR32
Comparable native code: 278/280, NOT whole exact
```

The original `0x120` local holds a zero-initialized word whose
historical source meaning is unresolved. In the C++ source the real
`read_game_resource` output-size local is explicitly initialized,
producing a different stack-offset zero store. There are no
additional failed calls, wrong resource-field offsets or
misidentified API targets. **We must not add an unused extra local,
change a legitimate pointer into a bogus stack alias, insert dead
code, or patch the original 336B to force the two bytes**.
The C++ source therefore remains **NONEXACT**, with no original
authored-game byte credit for this 336B parent. Its whole-exact
1,022B caller and separately whole-exact CRT and PMR children
retain their own independent credit.

[`verify-animation-file-group336-native.py`](../scripts/verify-animation-file-group336-native.py)
independently SHA-attests the entire original 336B/83 instruction
extent, every original E8/PE HIGHLOW physical role, original CP932
string and resource pointers, the true 1,022B parent E8, the
complete 336B generated C++ method and the *only two* native
nonrelocation differences. This is strictly a source-present
compiler-frontier verification; **no** canonical exact unit
or target-prefix comparison is accepted. The shared ANM header
change required a focused cold replay of the **one affected exact
source**, `src/AnimationFileLoad1022.cpp`, which preserved **10/10
whole exact original units** (the 1,022B authored game Boss and
nine separate generic library/CRT functions). The actual 336B native parser remains NONEXACT.
No entire-project cold replay was run.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AnimationFileGroupParse336.cpp build/core1095-probes/AnimationFileGroupParse336.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-animation-file-group336-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```
