# CORE/RECON-1093 — original 1,022B AnimationFile resource loader Boss, WHOLE strict exact

Immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original game `0x0044A700` is a **complete 1,022B /219-i386**
AnimationFile resource-loading Boss, SHA-256
`b750b3b8810f442dfe717b1c4b49eabad84423ed2771efa794c28c0321273021`.
It now has ordinary C++20 source in
[`src/AnimationFileLoad1022.cpp`](../src/AnimationFileLoad1022.cpp),
using the previously established real **0x70-byte `AnimationFile`**
layout through a *non-allocating inherited receiver view*. The
natural pinned MSVC19.44 x86 result is **1,022/1,022 bytes strict
exact, with 882/882 nonrelocated bytes, all 23 original E8 and
12 original PE HIGHLOW roles**. It is a complete game Boss, not a
truncated prefix of a standard-library function.

## Correcting the original decompiler's wide-path and owner mistakes

The original caller has a real **260-byte `char file_path[260]`**
on its stack, not the speculative `wchar_t local_118[130]` seen in
the Ghidra decompile. The native original formatted path at
PE HIGHLOW **`+0x36 -> 0x0056E0E4`** contains physical **ASCII
`%s\0`** (not UTF-16 `"猥"`). The real original **39B**
`sprintf_s<260>` wrapper at E8 **`+0x41 -> 0x00429120`** receives
that char array, native `%s` and the caller's path pointer. The
result is passed directly into the previously strict-exact
**583B** `read_game_resource` at E8 **`+0x54 ->0x00410AA0`**
with a null size output and archive mode zero. A missing resource
returns genuine `-1` without attempting to initialize any
AnimationFile output fields.

After success the source initializes four independent original
integer locals (group, script and sprite counts, and group index)
**before entering the native filesystem exception scopes** and
publishes the real resource byte pointer to **`AnimationFile+0x3C`**.
The game constructs one actual Win32 `std::filesystem::path` from
the input, then obtains the real `filename()` and `stem()` paths
and stores them into `AnimationFile+0x04` and `+0x20` native
`std::pmr::string` members. Crucially, the two conversions use the
true allocator-parameterized standard C++20
`path::string<char>(std::allocator<char>{})` overload, which
naturally emits original **75B** `0x004189C0` with two genuine
calls and the original native 14B allocator access, *not* the
current STL's 55B no-argument `.string()` method. Both real
ordinary `std::filesystem::path` return temporaries and PMR
string assignments retain their actual MSVC EH cleanup order.

The original 336B group parser at `0x0044EBF0` belongs to the
**Renderer manager pointed to by original global `0x005C0028`**,
*not* directly to an AnimationFile member method. The first
natural source attempt missed original PE HIGHLOW **`+0x32E ->
0x005C0028`**. The corrected source borrows
`NativeRendererAnmGroupView : AnimationPoolOwner` and calls its
true `parse_group_44ebf0(AnimationFile*,index,header)` on that
live global. The verified original E8 is at **`+0x332`**. The
336B parser remains an independent native body whose whole
source and exactness are not established by this parent.

## Exact two-pass ANM header and allocation protocol

The original loaded group descriptor has a true **0x28-byte**
physical header: a four-byte signature, native sprite count
**u16 at +0x04**, script count **u16 at +0x06**, and
next-group relative byte offset **u32 at +0x24**. The narrow
`NativeAnmGroupHeader` view statically attests these offsets;
other fields are explicitly provisionally named. The native
resource loader:

1. Iterates over linked group headers using their relative
   `next_header_offset`, counting groups, cumulative sprites and
   scripts. All four original counters are zeroed as separate
   native stack members before path/PMR construction.
2. Publishes actual group count to AnimationFile `+0x44` and
   allocates the native `TextureRecord` array at `+0x58`,
   `SpriteData` array at `+0x50` and script-pointer array at
   `+0x54` using existing real `DiagnosticAllocator::allocate_array`
   instantiations (native 205B/205B/158B respectively). The
   allocator provenance strings are the four immutable source
   labels `sprtlib.cpp:905/906/907/929` in original `.rdata`.
   The script and sprite counts are published to `+0x48/+0x4C`.
3. Traverses the linked group headers again, calling the *live
   Renderer manager's* original 336B decoder once per group.
   If it returns negative, the original method **returns zero**
   (not a newly manufactured error code), with an independent
   filesystem-path exception-unwind/destructor exit. It does not
   invent cleanup or rollback of the already allocated arrays.
4. If all groups parsed, the final group breaks the loop, then
   the method allocates the actual `Animation` template array at
   `AnimationFile+0x40` using the existing 238B array factory,
   sized by accumulated script count, and returns original zero.

The final exact code required preserving this very specific
last-group **fallthrough outside the second loop**, rather than
putting the allocation and return inside the loop or using a
`while(true)` literal. The latter generate extra non-native
branch tests, misplaced zero-local initialization or an
unreachable extra filesystem EH destructor; all were investigated
in ignored source probes and rejected. A properly structured
C++ `for (;;) { if (parse_result < 0) return 0; ++index;
if (!next_header_offset) break; next(); }` followed by real
`allocate_array<Animation>` reproduces the original two genuine
path destructor exit sites and the full original function length.

## Whole immutable E8 and physical PE data proof

[`verify-animation-file-load1022-native.py`](../scripts/verify-animation-file-load1022-native.py)
independently SHA-pins the entire original 1,022B extent and all
219 decoded native x86 instructions, including the actual
`ret 4`. It checks **all 23 native E8** site/destination pairs,
including original narrow-format wrapper, resource read, path
ctor/filename/stem, two **75B** path-to-string conversions, two
PMR-string assignments, four separate file/string destructors,
four native allocation factories, live Renderer group parser,
and compiler cookie. All **12 true PE HIGHLOW fields** are
independently bound to their physical original handler, cookie,
ASCII `%s`, 4 actual allocator/source-label pairs and one
Renderer-global pointer. The compiler's 35 entire COFF relocation
field positions/types and targets are compared against the *native
PE evidence*, not accepted by trying to solve target offsets from
source symbols alone.

```text
animation_file_load_resource_1022: exact (1022/1022 bytes)
Original immutable body: 1022B /219 i386
Nonrelocated native bytes: 882/882
Original call/data relocations: 23 E8 REL32 /12 PE HIGHLOW
Exact replay: 1/1 unit, 1 affected cold object
```

**One newly distinct game-authored original function /1,022B
executable `.text` code is credited.** The original 39B CRT
`sprintf_s`, 44B filesystem path ctor, 82B filename/stem, 75B
conversion, 141B extension and 25B PMR string assignment are
compiler-library methods, not new authored game functions. Their
independent whole-native exactness and provenance are tracked
separately and must not be recredited with the parent. Similarly,
existing allocator factory bodies, 583B resource input and the
still-open 336B group parser are independently owned. Full game
linkage and runtime playability remain unproven. No global cold
replay or synthetic source padding was used.

```sh
scripts/repo-python scripts/verify-animation-file-load1022-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFileLoad1022.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1094 — nine independent whole-exact generic descendants

The same native game loader source now additionally generates
[nine distinct original CRT/filesystem/PMR code heads, 686B total](ANIMATION_FILE_PATH_PMR_NINE_STRICT_EXACT.md):
39B `sprintf_s<260>`, 44B filesystem path constructor, 82B
filename and stem, 75B allocator-parametrized conversion,
25B/118B PMR string assignments and 141B/80B native path helpers.
All nine complete original bodies and their genuine independent
native parent E8 are SHA-pinned and whole strict exact from the same
C++20 source object (**10/10 scoped units**). Their
`origin=unknown/review` is maintained; the 1,022B game-authored
parent is not credited twice. The original 336B Renderer group
parser remains an independent outstanding larger function.

## CORE/RECON-1095 — the native 336B Renderer group decoder is now sourced

The genuine Renderer-global callee `0x0044EBF0`, E8 `+0x332` from
this exact 1,022B game loader, now has a distinct
[complete 336B/83-i386 source candidate](ANIMATION_FILE_GROUP336_NATIVE_FRONTIER.md)
implementing the observed ANM group signature/embedded name,
original Japanese CP932 diagnostics, external resource byte load,
and 24B texture metadata writes. Its six original E8/eight PE
HIGHLOW are all matched naturally, but **two native frame/local
bytes still differ** (278/280 comparable). The 336B method
remains SOURCE-PRESENT/NONEXACT; no original loader or child
code is recredited.

The shared 0x28B ANM group header now correctly records the original
`header+0x20` as one `uint8_t flag_20` (plus the three remaining
native bytes) instead of a guessed full `uint32_t` field, while
preserving all required `sprite_count`, `script_count`, embedded
name and next-header offsets. A focused exact replay of this single
affected C++20 file object preserved **10/10 whole strict units**
after its header's include-closure change.

## CORE/RECON-1097 — upstream original 269B Renderer preload now exact

The actual game Renderer `0x0044ED40` now has a
[whole original 269B native exact preload function](ANIMATION_FILE_PRELOAD269_STRICT_EXACT.md).
Its original E8 `+0xCC` invokes this complete 1,022B loader
*after* the Renderer releases its lock17 critical section; on
nonzero result, the caller separately invokes existing 97B
`DiagnosticAllocator::release_object<AnimationFile>` and returns
null. The upstream 269B game preload and 1,022B game loader are
**different original code heads**, each independently whole exact,
with no re-crediting of allocation, checked 42-file array or
file-IO callee code.
