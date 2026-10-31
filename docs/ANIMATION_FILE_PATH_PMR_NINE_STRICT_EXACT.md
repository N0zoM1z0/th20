# CORE/RECON-1094 — nine complete native CRT/filesystem/PMR methods, 686B whole strict exact

Original immutable Japanese TH20 Steamless v1.00a executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The game-owned **1,022B AnimationFile loader `0x0044A700`** is
independently WHOLE STRICT EXACT under CORE/RECON-1093. Its actual
regular C++20 source `src/AnimationFileLoad1022.cpp` naturally
instantiates **nine more distinct complete original physical
compiler/runtime library function heads**. The original native
bodies are each SHA-pinned from the immutable PE and every
original call-graph parent is independently confirmed; these are
not cut-out pieces or children blindly credited because a parent
matches. The original `std::filesystem::path` and PMR string
conversions are especially important to the parent C++ EH layout.

| Original head | Entire original function | Genuine original native parent E8 |
| --- | ---: | --- |
| `0x00429120` `sprintf_s<260>` wrapper | **39B/17 x86** | 1,022B game loader `+0x41` |
| `0x0040C720` `filesystem::path` constructor from narrow string | **44B/18 x86** | game loader `+0xB6` |
| `0x0044C590` `filesystem::path::filename()` | **82B/30 x86** | game loader `+0xCF` |
| `0x00451580` `filesystem::path::stem()` | **82B/30 x86** | game loader `+0x177` |
| `0x004189C0` allocator-parameterized `path::string<char>(allocator)` | **75B/28 x86** | game loader `+0x11B` and `+0x1C3` |
| `0x00446DC0` PMR string assign from `std::string` | **25B/11 x86** | game loader `+0x146` and `+0x1EE` |
| `0x0044B450` `filesystem::_Find_extension` | **141B/54 x86** | native 132B stem parser `0x0044B690` `+0x5D` |
| `0x0044B4E0` `filesystem::_Find_filename` | **80B/31 x86** | native 81B filename parser `0x0044B630` `+0x2A` and 132B stem parser `0x0044B690` `+0x2A` |
| `0x0044B970` PMR string byte-span assign | **118B/44 x86** | native 104B PMR string assignment owner `0x00447250` `+0x53` |

**All nine complete original functions have zero original PE
HIGHLOW fields**. Their true native E8 counts are respectively
1, 1, 3, 3, 2, 1, 0, 2, 4; each relative call and its actual
physical destination matches the naturally emitted MSVC C++20
method. The native source comes from the same one real
typed `AnimationFile` loader, not from reimplementing the
standard library by hand or inventing a new runtime module.

The most revealing discoveries are:

- The original **39B `sprintf_s<260>`** is used with a real
  **260-byte char path**, not the speculative Unicode array in an
  earlier Ghidra decompilation. The physical original format data
  at `0x0056E0E4` is actually ASCII `%s`.
- The original **75B allocator-aware `path::string<char>`** is
  **not** the modern no-argument overload (55B). Calling the
  genuine `string<char>(std::allocator<char>{})` template naturally
  emits its complete original two nested E8 and same 75/75 code;
  this is a real allocator used by PMR file name/stem assignment,
  not an inert compiler-shaping operand.
- Original **141B `_Find_extension`** precisely handles end iterator,
  `.`, `..` and last-dot traversal in a Windows UTF-16 path; it is
  naturally instantiated by the original 82B `path::stem()` chain.
  The earlier private handwritten 141B path-scan candidates varied
  in length and layout; actual C++ `<filesystem>` is the correct
  natural native source and generated a full **141/141**.
- Both original path basename and stem routines call the same
  80B filename search. Their original 81B/132B subparsers are
  **not** made exact automatically by their exact descendants.
- The complete 118B PMR string byte-span assignment is naturally
  instantiated from the parent PMR assignment path with four real
  original E8 calls. Its original 104B upstream method is still
  separately unaccepted; compiler-template origin remains review.

The read-only
[`verify-animation-file-path-stl-nine-native.py`](../scripts/verify-animation-file-path-stl-nine-native.py)
SHA-pins all nine entire physical original bodies, instruction
counts, exact original E8 destination graphs and the complete
original parent bytes/call sites (game loader, 81B/132B path
parsers and 104B PMR assignment). It independently confirms that
**no original code head overlaps another** and re-attests the
whole 1,022B game parent. The pinned compiler uses MSVC 19.44
x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` and produces all these genuine functions naturally:

```text
animation_file_load_resource_1022: exact (1022/1022) — game source
animation_load_sprintf_s_260_39: exact (39/39)
animation_load_path_ctor_44: exact (44/44)
animation_load_path_filename_82: exact (82/82)
animation_load_path_stem_82: exact (82/82)
animation_load_path_string_alloc_75: exact (75/75)
animation_load_pmr_string_assign_25: exact (25/25)
animation_load_find_extension_141: exact (141/141)
animation_load_find_filename_80: exact (80/80)
animation_load_pmr_string_assign_bytes_118: exact (118/118)
Exact replay: 10/10 strict units, 1 affected cold object
```

The newly admitted **nine original generic function heads cover
686 distinct original executable `.text` bytes**. Each is
classified `origin=unknown`, `disposition=review`; **none** is
credited as game-authored code. The previously credited 1,022B
AnimationFile game loader remains **one separate physical game
head**. Folded allocator/iterator methods already accepted at
other physical original addresses, original 81B/132B child
parsers, original 104B PMR parent and the 336B game group parser
are not counted again. No full-project cold replay or target
binary modification was performed.

```sh
scripts/repo-python scripts/verify-animation-file-path-stl-nine-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFileLoad1022.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1096 — deeper parser and PMR subfunctions exact

[Five further original whole-exact filesystem/PMR methods](ANIMATION_LOADER_NESTED_FIVE_STL_415_STRICT_EXACT.md)
(81B parse-filename, 132B parse-stem, 104B PMR assignment, 54B wide
string-view and 44B view-to-path construction) naturally compile from
the same existing 1,022B game AnimationFile loader. They contribute
415 distinct native generic `.text` bytes with no additional game
code credit. This owner now replays **15/15** original strict units.
