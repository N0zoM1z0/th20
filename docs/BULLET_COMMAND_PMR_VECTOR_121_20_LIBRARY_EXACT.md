# CORE/EXACT-734 — original Bullet command-vector STL copy and destructor, 141 complete native bytes

**Later [CORE/EXACT-738](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md) update:** the one coherent PMR BulletCommand source profile was switched to native C++17 after confirming its original 33/41/121/20-byte functions stay **4/4 whole strict exact**. This also matches three real original 200/196/73-byte upstream STL allocation/copy helpers, now **7/7 strict total** in one affected-only cold object. The original 470B counted-range helper still has an independently verified std::is_constant_evaluated branch absent from current pinned C++17 code; it is NONEXACT. The original C++20 profile in the dated first acceptance below is historical.

**Two real standard-library PMR vector methods in the original 12,140-byte Bullet command Boss now have whole native strict source.** These are library functions, not game-authored methods, and contribute **zero** new game-authored code bytes. The 12,140B original game Boss remains source-absent and NONEXACT.

Locked target: Japanese TH20 v1.00a Steamless, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Entire native original methods

| Real original library function | Native physical head | Complete native code | New exact canonical unit |
| --- | --- | ---: | --- |
| std::pmr::vector<BulletCommand> copy operator=(const&) | 0x0047C570 | **121B /44 i386** | shot_command_vector_copy_assignment_library: 121/121 |
| std::pmr::vector<BulletCommand> destructor | 0x0047C300 | **20B /10 i386** | shot_command_vector_dtor_library: 20/20 |
| **Two original physical heads** | | **141B** | **2 newly strict; both library-origin** |

The immutable original full 121B body has five direct E8 fields; the original whole 20B destructor has one. Every other byte compares strictly: **101/101 and 16/16 original native nonrelocated bytes**, respectively, under the locked native MSVC. The exact original physical E8 targets and offsets were independently decoded from the original PE rather than deriving them from the compiler output.

The original 12,140B Bullet::run_extended_commands calls the copy at original E8 **0x0047F8FE, 0x0047F9F3 and 0x0047FC8A**. It calls the destructor at original **0x0047F97F and 0x0047F994**. The real game ShotMetadata (EtamaArgInf) contains the native 44B-element PMR vector at +4, and the original Bullet at +0x98 owns a shared pointer to that metadata. The original 121B routine is natural vector self-assignment, allocator propagation and counted-range copying, with no invented game wrapper.

## All original six original native helper calls

| Parent whole method | Native E8 callsite | Original physical destination | Exact source role |
| --- | --- | --- | --- |
| vector copy | 0x0047C57D | 0x0040B280 | STL const-vector addressof |
| vector copy | 0x0047C592 | 0x0040F160 | STL mutable vector allocator getter |
| vector copy | 0x0047C59D | 0x0040F160 | STL const vector allocator getter |
| vector copy | 0x0047C5AD | 0x0040C6B0 | STL allocator copy propagation |
| vector copy | 0x0047C5DB | 0x0047A8D0 | original 470B counted-range helper, **not exact** |
| vector destructor | 0x0047C30A | 0x00484570 | original 32B vector cleanup helper, **not exact** |

The original first four helper E8 destinations are independently whole native identical under naturally typed MSVC sources: 8/8B addressof, both 19/19B const and mutable allocator access, and 5/5B allocator copy propagation. Those game executable physical heads were previously accepted with different legitimate fold-compatible source roles, and **no extra physical bytes are credited**.

The distinct original 470B counted-range helper and 32B cleanup method remain **NONEXACT**. Their real physical native E8 destinations are known, but a correct 121B/20B parent does not prove their larger original bodies or historical linker ICF settings.

## Coherent source owner, rejected alternative and scoped replay

The existing maintained src/ShotMetadataVectorInstantiation.cpp already explicitly instantiates the same real PMR vector element's operator[] (33B exact) and size (41B exact). This checkpoint adds the natural, genuine C++ vector copy-assignment and destructor template instances in **that same file**, preserving one coherent standard-library template owner. No public header, fake wrapper or original compiler patch was introduced.

An alternative private experiment appended the copy instantiation to game-authored ShotMetadata.cpp and unexpectedly made its previously exact 255B constructor generate **260B**. That regression was rejected. A second standalone trial emitted the correct 121B/20B methods; its redundant source file was consolidated into the existing vector-owner TU. The actual maintained original 33B/41B methods remain byte-identical.

Only ONE actual affected canonical MSVC source object was cold rebuilt:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/ShotMetadataVectorInstantiation.cpp

Result: **4/4 complete original strict units /one cold object**. Profile: pinned MSVC 19.44 i386 /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc.

Private reproducible native evidence:
- .analysis/core731-command-vector-instantiation.cpp — typed standard library copy/dtor first isolated native compiler probe.
- .analysis/core732-ShotMetadataNativeVectorCopy.cpp — rejected alternative that changed unrelated game-authored 255B constructor code.
- .analysis/core733-ShotMetadataVectorInstantiation.cpp — accepted same-owner template source private probe; original 33B/41B source remains exact.
- .analysis/core734-register-original-bullet-stdlib-vector.py — entire original physical 121B/20B native bodies, genuine six E8 target and COFF relocation field identities, manifest registration preserving 1,189 previous strict units.
- Current exact units shot_command_vector_copy_assignment_library and shot_command_vector_dtor_library.

## Correct accounting

These functions are marked **library origin, exclude authored byte credit**. Canonical native strict units advance from **1,189 to 1,191** and mapped/source-present functions from **1,187 to 1,189**. The authored game total **549 whole functions /186,446 distinct original game code bytes is unchanged**.

The original 12,140B Bullet Boss, 470B native range helper and 32B native cleanup helper remain NONEXACT. No unfiltered/full cold replay was run.
