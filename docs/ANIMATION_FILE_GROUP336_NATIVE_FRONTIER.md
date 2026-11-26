# 336B Renderer ANM group parser: separate zero and size-output slots

The native parser at `0x0044EBF0` does **not initialize the resource-size
output**. Its entry zero store targets `[ebp-0x120]`; the resource reader
receives `[ebp-0x10C]`. The maintained source now leaves `length` for the
successful reader to write. The separate native zero store remains unowned.

The locked Japanese TH20 v1.00a Steamless target has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete original method is **336B/83 instructions**, ending in `ret 0x0C`,
with body SHA-256
`0ab86e2cc9985d672ff96e5fe0e9ae4b52b5a02c69b63e87a310344ae21b3a67`.
Its current candidate is **326B/82 instructions**, SOURCE-PRESENT, NONEXACT.

## Native frame ownership

A full decoded-body operand audit checks complete memory-access intervals:

| Four-byte slot | Complete parser accesses |
| --- | --- |
| `[ebp-0x120]` | `+0x19`: `mov dword ptr [ebp-0x120],0` |
| `[ebp-0x10C]` | `+0xD0`: address passed to the reader; `+0x11D`: loaded after reader success |

No lower-frame `lea` exposes the zero slot, and the parser contains no
ESP-relative memory operand. The two early logger messages contain no format
conversions. The texture-error message and `sprintf_s` format each contain
one `%s`, with one explicit corresponding string argument; they do not consume
an unpassed formatting argument from this word.

The size read is reached through the nonnull-result branch at
`+0xF3 -> +0x113`. The separately exact 583B `read_game_resource` receives
mode `1` and writes the requested size before its successful return.
Failure paths return before the parser reads `length`. This supports an
uninitialized output variable in natural C++; it does not identify the source
meaning of the separate zero word.

## Preserved resource protocol

[`AnimationFileGroupParse336.cpp`](../src/AnimationFileGroupParse336.cpp)
belongs to the borrowed Renderer owner in
[`NativeAnimationFileLoadView.hpp`](../src/NativeAnimationFileLoadView.hpp).
The exact 1,022B AnimationFile loader at `0x0044A700` calls it at `+0x332`,
using the real Renderer global `0x005C0028` and passing file, index and header
as three stack arguments. It is a `__thiscall` method with `ret 0x0C`.

The real 0x28B group header requires signature `8`, has an embedded name
offset at `+0x10`, a **byte** texture flag at `+0x20`, and the next-header
distance at `+0x24`. Null headers and wrong signatures log the original CP932
messages and return `-1`. A nonzero flag or an embedded path beginning with
`'@'` accepts the group without reading an external texture. Other paths copy
the name into the original 260-byte buffer, load in mode `1`, and either log
failure or store the returned bytes and size into the actual 24B texture
record at `AnimationFile+0x58`. Accepted groups return `1`.

All six native E8 roles remain:

| Native call offset | Destination |
| --- | --- |
| `+0x33`, `+0x61`, `+0x106` | `0x00454230`, shared `report_log_error` |
| `+0xC6` | `0x00429120`, SDK `sprintf_s<260>` |
| `+0xDE` | `0x00410AA0`, game resource reader |
| `+0x145` | `0x005429EE`, GS cookie check |

The eight native HIGHLOW fields remain at `+0x0A -> 0x005B25C0`;
`+0x2A/+0x58/+0xFD -> 0x0056E428/0x0056E464/0x0056E488`;
`+0x2F/+0x5D/+0x102 -> 0x005C0678`; and `+0xBB -> 0x0056E0E4`,
the original `%s` literal. Diagnostic ownership is the existing
`DiagnosticLog`; no speculative logger or duplicate Renderer instance is used.

## Complete comparison and remaining gap

| Source context | Code / instructions | Frame | Initial zero |
| --- | ---: | ---: | --- |
| Original target | 336B / 83 | 0x120 | `[ebp-0x120]` |
| Earlier `length=0` candidate | 336B / 83 | 0x11C | `[ebp-0x10C]` |
| Current reader-owned output | 326B / 82 | 0x11C | None |

The old candidate's **278/280 ordinary-byte** score hid the wrong local
initialization. A fresh baseline reproduces its two differences at `+0x05`
and `+0x1B`; that result is retained as a failed ownership hypothesis.
Removing the initializer exposes the real **10B entry-store gap** and extra
**four bytes of native frame allocation**. No unused local is introduced to
imitate the unresolved store.

[`verify-animation-file-group336-native.py`](../scripts/verify-animation-file-group336-native.py)
checks the complete original 336B and complete candidate 326B. All 14 candidate
relocations are resolved from named function/global bindings and the verified
`%s` literal, rather than solving target fields at candidate offsets. The
remaining decoded instructions and internal branch targets agree after explicitly
accounting for the unmatched native zero store and frame size. This diagnostic
retains the original extent and does not establish strict exactness.

The verifier passes the current compiler output, rejects the previous
initialized-size object, and rejects an incorrect reader binding. Fresh
MSVC 19.44.35211 compilation uses the unchanged
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` profile.
Only this nonexact source and its focused audit changed. No shared header,
exact provider or source-including consumer changed: **exact replay scope is
zero**. The exact 1,022B loader and 583B reader retain their existing evidence.

Private evidence is in `.analysis/anm-group336-session/`: `native-slot-proof.txt`,
`source-proof.txt`, `verifier-controls.txt` and `old-source-differences.txt`.
The previous source and both fresh objects/receipts are retained, including
`build/gpt61-anm-group-probe/Group-before.obj`. Historical outputs and receipts
under `build/core1095-probes/` are unchanged.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AnimationFileGroupParse336.cpp \
  build/gpt61-anm-group-probe/AnimationFileGroupParse336.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-animation-file-group336-native.py
```

Next work is the native zero word's actual source ownership or compiler context.

A private class-key control changes the header and Renderer view to public
`class` definitions with the same field layout. Its complete 326B body and
all 14 relocation records remain identical; the list constructor's earlier
`/sdl` preclear finding does not explain this word. The private header/source
and `class-key-controls.txt` are retained under the same analysis directory.
No public-header change or replay expansion is justified by that result.
