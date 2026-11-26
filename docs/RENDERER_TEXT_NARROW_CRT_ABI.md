# Renderer text uses narrow formatting and 0x500-byte buffers

`format_text_447940` forwards `char*` output and format arguments to
`vsprintf_s`, with a **0x500-byte** capacity. The previous wide-character
declaration followed Ghidra's initial library labels. Tracing the actual
implementation resolves the type without changing the locked target.

## Native character-width evidence

The complete native path is:

| Address | Size | Role |
| --- | ---: | --- |
| `0x00447940` | 30B | Output, format, varargs and fixed `0x500` capacity |
| `0x00439880` | 31B | `vsprintf_s`, supplying a null locale |
| `0x0041F1D0` | 77B | `_vsprintf_s_l`, loading printf options |
| `0x0054A498` | 65B | `__stdio_common_vsprintf_s`, cached CRT context |
| `0x005488AF` | 159B | `common_vsprintf_s<char>` |

The last function loads the output buffer into ESI from `[ebp+0x10]` and
clears **one byte** at `0x00548910` using `mov byte ptr [esi],al`.
Its complete 159B matches all **147 non-relocation bytes** of the locked
SDK's `common_vsprintf_s<char>` in `libucrt.lib`'s `output.obj`. The wide
specialization is a distinct **154B** function and clears a two-byte element.
The preceding 65B entry matches all 53 ordinary bytes of the library entry,
but its narrow/wide variants have identical ordinary code; that entry alone
cannot establish character width.

The installed SDK source at
`Windows Kits/10/Source/10.0.26100.0/ucrt/stdio/output.cpp` supplies both typed
entry points and the shared template. The native `0x0054FE20` length routine
also reads bytes and returns a byte count. This agrees with the existing
typed `sprintf_s<260>` loader support, whose independently accepted call
already targets `vsprintf_s` at `0x00439880`.

`verify-animation-text-format30-native.py` now checks every complete body and
ordered call in this path, plus the byte terminator store. Private controls
reject the actual SDK wide specialization, a missing terminator and a
duplicate terminator. No analyzer name is used as type proof.

## Maintained source and comparison scope

One shared `AnimationTextFormat.hpp` declaration now agrees with its
definition and all three Renderer callers. They use `char formatted[0x500]`;
the two formatted Renderer methods accept `const char*`. The artificial
wide/narrow pointer casts are removed. The wrapper calls the real SDK
`vsprintf_s` declaration through the existing secure-CRT header.

Fresh locked-compiler comparisons pass:

| Unit | Complete canonical replay |
| --- | ---: |
| `animation_text_format_30` | 30/30B |
| `animation_renderer_formatted_text_417` | 417/417B |
| `crt_vsprintf_s_31` | 31/31B |
| `crt_vsprintf_s_l_77` | 77/77B |

The latter two bodies are emitted naturally by the SDK header in the same
formatter object. Their library origin is recorded separately; they add no
authored game-byte credit. The 10B printf-options accessor and deeper CRT
bodies are not newly accepted units.

Captured include closures identify the 417B method as the only exact provider
of the changed Renderer-view header. The changed formatter and its consumers
give **four exact units in two source providers**. The two NONEXACT callers
are checked separately below. Original canonical objects and receipts
remain in their old directories; current builds use
`build/gpt61-renderer-text-canonical/`.

The complete **586B** centered candidate and **574B** ASCII candidate retain
their prior instruction bytes and relocation records after normalizing the
corrected symbol names. Each method also retains all owned **66B EH code and
52B EH data**. The accepted 417B method's corresponding EH sections are
unchanged too. Centered evaluation order and the ASCII scalar load remain
open, so neither parent gains exact credit. Identical x86 pointer widths had
allowed the earlier character-type error to survive byte comparison.

Private evidence is under `.analysis/renderer-centered-session/`:
`narrow-crt-proof.txt` records complete library comparisons, native call paths,
negative controls, SDK hashes and the affected include closure;
`renderer-abi-object-controls.txt` records complete before/after code and EH
comparisons; `narrow-crt-canonical-replay.txt` records the three formatter
provider units. The source snapshots and original provider products are
retained for the ABI correction. A bounded Wine smoke links the production
formatter object with the real static CRT and verifies `"%s:%u"` produces
`"TH20:20"`; its commands and exit status are in `runtime-link-run.txt`.
