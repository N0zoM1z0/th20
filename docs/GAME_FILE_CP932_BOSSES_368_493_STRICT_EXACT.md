# CORE/RECON-1083 — complete original 368B CP932 input opener and 493B one-shot file-write game Bosses, whole strict exact

Original locked Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Two originally unclassified **game-authored Windows file-I/O Bosses**
are now reconstructed from their genuine native behavior with complete
C++20 source in [`src/GameFileCp932Bosses.cpp`](../src/GameFileCp932Bosses.cpp):

| Original physical head | Entire original function | Native SHA-256 | Exact result |
| --- | ---: | --- | --- |
| `0x00410CF0` CP932 input-file opener | **368B /94 i386** | `e4b51fd1da74296dbefab1aeda7143e27cc6d3e25e71bd9c78e9daaf94bce009` | **368/368 whole exact**, 8 E8/12 HIGHLOW |
| `0x00410E70` CP932 one-shot output writer | **493B /125 i386** | `583da3e1d06de98d5b12071b04f393c743ee8c73c36336553089d3898dacd3e3` | **493/493 whole exact**, 10 E8/14 HIGHLOW |

These are **distinct original physical game functions** from the
previously accepted `0x00410840` 323B persistent-file output opener,
`0x00411060` 255B persistent output writer, and `0x004106E0`
179B closer in [`GameFileIo.cpp`](../src/GameFileIo.cpp).
The 368B function opens a **persistent input handle** at native global
`0x005AE060`, whereas the separate 493B writer uses a **local HANDLE**,
writes and closes it on both successful and short-write returns.
Neither one is an alias of the existing persistent-output functions.

## Native complete CP932 and Win32 API protocol

Both real game functions hold the same lock-registry recursive mutex
**slot 2**, acquire a `std::lock_guard` with native SEH/unwind,
and stage a real 261-wide-character local path buffer. The original
clears **0x20A bytes** via native CRT `memset` and converts from
Japanese Windows **CP932** via
`MultiByteToWideChar(932,0,filename,-1,converted,0x104)`.
The native original conversion capacity is 0x104 (260 UTF-16
code units), which is exactly what maintained source calls; no
unobserved conversion-failure policy is invented here.

The **368B input opener** calls native Win32 `CreateFileW` with
`GENERIC_READ`, `FILE_SHARE_READ`, `OPEN_EXISTING`, and
`FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN`, saving the
returned physical HANDLE to original process global `0x005AE060`.
If the original API returns `INVALID_HANDLE_VALUE`, it obtains
`GetLastError()`, formats the error via actual `FormatMessageW` flags
`0x1300` and language `0x400`, emits the native file diagnostic via
previously accepted folded `ecl_diagnostic_hint`, frees the
Win32-owned error message with `LocalFree`, and returns `-1`.
On success it logs the native open diagnostic and returns zero.
There is **no `CloseHandle` in this input opener** because the
persistent input handle is used by separate file functions.

The distinct **493B one-shot output writer** calls `CreateFileW`
with `GENERIC_WRITE`, shared read, `CREATE_ALWAYS`, and normal
attributes. On `INVALID_HANDLE_VALUE`, it logs the Win32 error with
the same authentic native formatting and returns `-1`. Otherwise
it calls `WriteFile`, compares the **actual 32-bit byte count**
against the requested size, calls `CloseHandle` on either branch,
then logs short write and returns `-2`, or logs success and returns
zero. The function does not manufacture a persistent global output
handle, a short-write retry, or Win32 BOOL-result checking absent
from the immutable original machine-code flow.

## Exact natural MSVC compiler lowering, not opcode substitution

Pinned MSVC 19.44 C++20 i386
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
naturally generates the complete **368B/94** opening method
**288/288** nonrelocated bytes and the original **eight E8/twelve
PE HIGHLOW** positions, using ordinary `std::lock_guard`, `wchar_t`
array, CRT and Win32 API calls.

The initial meaningful 493B source also generated **493B/125 i386**
with all 24 real relocation positions matching but **nine ordinary
bytes differing**: the compiler chose the opposite branch condition
and swapped the two return-result stack locals for the *short-write
failure* and *successful write* paths. The source originally wrote
`if (size == written) { success; } else { failure; }`, which is
semantically correct but x86-control-flow nonexact.
Reconstructing the authentic original branch order:

```cpp
if (size != written) {
    CloseHandle(file);
    ecl_diagnostic_hint("error : %s write error\r\n", filename);
    return -2;
}
CloseHandle(file);
ecl_diagnostic_hint("%s write ...\r\n", filename);
return 0;
```

naturally generates the full original **493B/125 i386**, with
**397/397 nonrelocated native bytes** and **all ten E8/fourteen
HIGHLOW**. It is real observed short-write control flow, not a
handcrafted branch instruction, dead local or padding. The entire
original function was compared, not a shortened prefix.

[`verify-game-file-cp932-bosses-native.py`](../scripts/verify-game-file-cp932-bosses-native.py)
independently SHA-pins each whole original physical extent,
all decoded native instructions, real return widths, original
Win32 CP932/lock/cookie/message constants, and **all actual PE
E8/HIGHLOW destinations**. It then independently verifies every
compiled canonical reloc-field type/position/target, using pinned
original targets rather than solving them from the source candidate.
Original source code and compiled bytes are not used to redefine
the selected immutable game target. Both accepted units use one
pinned compiler object and have distinct original source owners:

```text
game_input_cp932_open_368: exact (368/368 bytes)
game_cp932_write_once_493: exact (493/493 bytes)
Exact replay: 2/2 units, 1 cold object
```

This contributes **two new game-authored whole-native exact heads /
861 distinct original executable `.text` bytes**. Previously
accepted folded `LockRegistry::slot`, lock guards, CRT `memset`,
Win32 IATs and `ecl_diagnostic_hint` are separately owned and **not
credited twice**. Runtime game-file linkage and actual playable
startup remain unproven. No full-project cold replay was run.

```sh
scripts/repo-python scripts/verify-game-file-cp932-bosses-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GameFileCp932Bosses.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
