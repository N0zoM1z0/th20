# CORE/RECON-1084 — complete original 266B persistent CP932 file input reader, whole strict exact

Immutable Japanese TH20 Steamless v1.00a original SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The real game-owned `0x00410990` is a complete **266B/74-i386**
function, original full SHA-256
`4c72d68bc74555900a166b2880a2de67ce56964aec974813fd98942dcd6fca4a`.
It reads from the actual process-global Win32 input HANDLE at
**`0x005AE060`**, which is created by the separate, already whole
strict-exact **368B CP932 input file opener** at `0x00410CF0`.
It is not the previously accepted 583B archive-vs-disk resource
loader or the persistent-output writer: these have other original
physical heads and distinct game ownership.

## Real original native file and allocator lifetime

The complete native method:

1. Acquires the game's actual `LockRegistry::slot(2)` recursive mutex
   through the original `std::lock_guard` with MSVC SEH/unwind.
2. If the original global input HANDLE is
   `INVALID_HANDLE_VALUE`, releases the guard and returns null without
   allocation or Win32 read.
3. Calls the separately whole-exact **88B** original
   `DiagnosticAllocator::allocate_bytes` `0x0041F610` on the actual
   game allocator-global `0x005B8894`, passing the input byte count
   and the real original source location label
   `D:\cygwin\home\zun\prog\th20\src\core\filectrl.cpp:496 void`
   from original `.rdata` at `0x0056C6D4`.
4. If allocation returns null, calls native Win32
   `CloseHandle(0x005AE060)` and returns null without resetting the
   process-global HANDLE (no unobserved state change).
5. Otherwise calls `ReadFile` with the allocated output buffer, the
   original requested byte count and a local `DWORD bytes_read`,
   ignoring the Win32 success BOOL and ignoring short-read detection
   exactly as the original executable does. It logs the genuine
   `Read ...\r\n` string at original `0x0056C710`, releases the
   mutex guard and returns the actual owned allocation.

The maintained function is
[`read_game_input_bytes_410990`](../src/GameFileInputRead266.cpp),
with true `DiagnosticAllocator`, Win32, `LockRegistry` and
`ecl_diagnostic_hint` dependencies. It is naturally expressed by
regular C++20, not by an opaque decompiler-translated function with
manually embedded machine-code constants.

## Independent whole original PE evidence

[`verify-game-file-input-read266-native.py`](../scripts/verify-game-file-input-read266-native.py)
SHA-pins the entire **266B/74 instruction native body**, all
**eight physical E8 and eleven PE HIGHLOW** fields and their true
targets, native return, the three separate references to the
**same original HANDLE global**, and the original complete separate
368B input opener and exact 88B allocator head. Original native
E8 references are:

| Original E8 | Native destination |
| --- | --- |
| `+0x2F` | `0x0040C310` lock-registry slot 2 |
| `+0x38` | `0x0040B730` recursive lock guard ctor |
| `+0x5E`, `+0xA7`, `+0xE9` | `0x0040B900` guard cleanup at three original returns |
| `+0x7A` | `0x0041F610` actual 88B allocator `allocate_bytes` |
| `+0xD1` | `0x0040C6B0` previously accepted folded game diagnostic |
| `+0x101` | `0x005429EE` real cookie check |

The original HIGHLOW entries `+0x46/+0x8A/+0xC1` independently
address `0x005AE060`; `+0x2B` addresses lock registry
`0x005C0240`; `+0x76` addresses allocator global `0x005B8894`;
`+0x91/+0xC8` are real `CloseHandle`/`ReadFile` IATs; `+0x6C`
and `+0xCD` point to original allocation provenance and read-log
strings. The SEH handler and native cookie make up the remaining two
physical native relocations. No target was inferred from compiled
candidate offsets without checking the original PE first.

Pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
naturally compiles this entire original function as **266B/74 i386**
with **190/190 nonrelocated native bytes** and **all 19 physical PE
relocation roles** exactly corresponding. One separate pinned source
provider, with the related input opener/writer rebuilt only because
receipt inputs changed, passes:

```text
game_input_cp932_open_368: exact (368/368 bytes)
game_cp932_write_once_493: exact (493/493 bytes)
game_input_bytes_read_266: exact (266/266 bytes)
Exact replay: 3/3 units, 2 affected cold objects
```

This contributes **one new game-authored whole-exact function /
266 distinct original `.text` bytes**, no duplicate credit for the
already exact 368B input opener, 493B one-shot writer, 88B allocator,
lock guards, CRT, Win32 IATs or folded diagnostic callback. The original
full game linkage and actual played disk I/O state remain unproven.
No full-repository cold replay, target byte patch or shortened
function extent was used.

```sh
scripts/repo-python scripts/verify-game-file-input-read266-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GameFileCp932Bosses.cpp \
  --source src/GameFileInputRead266.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
