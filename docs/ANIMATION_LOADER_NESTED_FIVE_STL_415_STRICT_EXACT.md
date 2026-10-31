# CORE/RECON-1096 — five more whole-original filesystem/PMR methods beneath the 1,022B ANM loader

Immutable Japanese TH20 Steamless v1.00a original SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The entire 1,022B/219-instruction game-owned AnimationFile loader
`0x0044A700` is already [WHOLE STRICT EXACT](ANIMATION_FILE_LOAD1022_STRICT_EXACT.md).
The real `std::filesystem::path::filename` and `stem` calls and PMR
filename assignments generate **five additional distinct complete
original native code heads, 415 executable bytes**, all under the
unchanged original C++20 owner `src/AnimationFileLoad1022.cpp`:

| Physical original head | Entire native function | Genuine original parent E8 |
| --- | ---: | --- |
| `0x0044B630` `filesystem::_Parse_filename` | **81B /30 i386**, 4 original E8 | native exact 82B `filesystem::path::filename` E8 `+0x2F` |
| `0x0044B690` `filesystem::_Parse_stem` | **132B /48 i386**, 6 E8 | native exact 82B `filesystem::path::stem` E8 `+0x2F` |
| `0x00447250` `pmr::string::assign(std::string)` | **104B /35 i386**, 7 E8 and **1 PE HIGHLOW** | native exact 25B PMR operator= E8 `+0x0E` |
| `0x0040E7C0` `std::wstring` to `string_view` | **54B /20 i386**, 2 E8 | native exact 82B filename E8 `+0x1F` |
| `0x00417DC0` `filesystem::path` from wide string view | **44B /18 i386**, 1 E8 | native exact 82B filename E8 `+0x3B` |

These helpers are not new game methods or separate facsimile
implementations. All are *genuinely instantiated from the same*
meaningful C++ `std::filesystem` and `std::pmr::string` operations
of the 1,022B game loader. The native 132B `_Parse_stem` calls
independently accepted complete 80B `_Find_filename` and 141B
`_Find_extension` helpers, so the actual multi-level native call
graph is preserved, not inferred from compiler symbol similarity.
The 104B PMR assign method also contains a **real original security
cookie HIGHLOW `+0x07 -> 0x005B25C0`** in addition to its seven E8.
It must not be misclassified as a zero-HIGHLOW generic helper.

Read-only [`verify-animation-loader-nested-five-native.py`](../scripts/verify-animation-loader-nested-five-native.py)
independently SHA-attests each entire original function from the
locked PE, verifies all complete i386 instructions and physical E8
and HIGHLOW destinations, then independently checks the real
82B/25B parent code and their original E8 into each child.
The source emits full canonical exact receipts under pinned MSVC19.44
i386 `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`:

```text
animation_load_parse_filename_81: exact (81/81 bytes)
animation_load_parse_stem_132: exact (132/132 bytes)
animation_load_pmr_assign_string_104: exact (104/104 bytes)
animation_load_wstring_view_54: exact (54/54 bytes)
animation_load_path_view_ctor_44: exact (44/44 bytes)
Original 1,022B game loader +9 earlier exact generic descendants: 10/10
Exact replay: 15/15 units, ONE affected cold object
```

The five newly accepted physical STL/PMR functions total **415
original `.text` bytes** with `origin=unknown`, `disposition=review`.
Thus **zero new game-authored head/byte credit** is issued.
The already credited 1,022B game loader, nine previous compiler
helpers (686B), and the separately SOURCE-PRESENT/NONEXACT
336B Renderer group parser are not re-credited by transitivity.
No full-project cold replay, native-code patch or source padding
was used.

```sh
scripts/repo-python scripts/verify-animation-loader-nested-five-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFileLoad1022.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
