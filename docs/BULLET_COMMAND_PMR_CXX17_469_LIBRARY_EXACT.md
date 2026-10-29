# CORE/EXACT-738 — recover 469 full native bytes of original Bullet PMR vector STL allocation and copy

**Three additional whole original standard-library methods used by the 12,140-byte Bullet command Boss are now strict exact under one coherent pinned-MSVC C++17 template source owner.** They account for 200 + 196 + 73 = **469 distinct original native code bytes**, without adding any game-authored functions or authored-byte credit. The surrounding original 470B counted-range helper remains NONEXACT.

Locked Japanese TH20 v1.00a Steamless original PE, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Three complete original function bodies, not shortened prefixes

| Original native standard-library operation | Physical head | Whole body | Real original relocs | Original 470B caller |
| --- | --- | ---: | --- | --- |
| PMR vector of BulletCommand _Clear_and_reserve_geometric | 0x004844A0 | **200/200B, 70 x86** | **7 native E8** | 0x0047A937 |
| PMR allocator _Uninitialized_copy_n of BulletCommand | 0x0047B050 | **196/196B, 63 x86** | **8 native E8 + 2 genuine PE HIGHLOW** | 0x0047A966 and 0x0047AA38 |
| BulletCommand pointer _Copy_memmove_n | 0x0047AB60 | **73/73B, 29 x86** | **3 native E8** | 0x0047A9B9 |
| **Total source-present library code** | Three distinct original intervals | **469B** | **18 true E8 + 2 true original HIGHLOW** | Real 470B upstream function, not exact |

All three whole original methods were independently decoded to their real return boundaries, and their complete pinned MSVC 19.44 x86 generated bodies compare structurally exact against the original immutable PE. The original nonrelocation byte counts are respectively **172/172, 156/156 and 61/61**, with every real relocation field separately anchored to a genuine original PE value. No original physical code interval overlaps an earlier credited game-authored method. All three methods are standard-library template instantiations, not original game-authored logic, despite being physically linked into the game's Bullet command processor.

### Actual original 196B SEH and security-cookie fields

The original _Uninitialized_copy_n native body has a real SEH prolog. Its two COFF **DIR32**, not E8/REL32, entries correspond to physical original PE HIGHLOW fields:

- Original 0x0047B056 contains absolute original EH handler-related pointer **0x00567D6D**.
- Original 0x0047B065 contains absolute original security cookie global address **0x005B25C0**.

The original .reloc directory independently contains both field sites and their actual 32-bit original pointer values. Its other eight native relocation fields are genuine original E8 calls. This proves that the entire 196B original method is correctly accounted for, including real exception/SEH state, rather than accepting only the 156 nonrelocation bytes or incorrectly interpreting an absolute EH pointer as an E8 relative destination.

## One genuine C++17 standard library owner, no incompatible duplicated instantiations

The existing maintained src/ShotMetadataVectorInstantiation.cpp is the sole canonical source provider for real vector<BulletCommand,pmr> explicit template instances. CORE/EXACT-734 already added the genuine 121B copy assignment and20B vector destructor to the existing 33B operator[] and41B size() functions. Those four originally used /std:c++20 under the pinned compiler.

Comparing natural, **unchanged C++ source under both actual MSVC language profiles**, rather than trusting the prior source flag, reveals:

| Original STL method | Original whole native bytes | Pinned C++20 generated | Pinned C++17 generated |
| --- | ---: | ---: | ---: |
| Vector copy assignment | 121 | 121 exact | **121 exact** |
| Vector destructor | 20 | 20 exact | **20 exact** |
| Vector index/size | 33B and 41B | both exact | **both exact** |
| _Clear_and_reserve_geometric | 200 | 200 exact | **200 exact** |
| _Uninitialized_copy_n | 196 | 187 NONEXACT | **196 exact** |
| _Copy_memmove_n | 73 | 62 NONEXACT | **73 exact** |
| _Copy_n_unchecked4 | 96 | 96 byte-identical privately | **84 NONEXACT** |
| _Assign_counted_range | 470 | 401 NONEXACT | **458 NONEXACT** |

A single coherent C++17 profile recovers **three whole native source methods** while preserving the four existing source acceptance units. Mixing C++17 and C++20 object providers under the same private STL function name to get the 96B _Copy_n_unchecked4 would introduce potentially incompatible **duplicate COMDAT implementations**. This checkpoint deliberately DOES NOT do that. The 96B helper therefore remains separately untracked as strict exact in this coherent owner, notwithstanding its private C++20 byte-identical probe.

Only the four preexisting strict unit **profile** fields in config/match-units.toml were changed from /std:c++20 to /std:c++17 for this one template owner. No C++ source, public header, previously pinned target byte address or physical relocation was changed. The three new units are in the same source/object with the exact same C++17 compiler flags.

One source-filtered cold build:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/ShotMetadataVectorInstantiation.cpp

**Result: 7/7 strictly exact original native functions, ONE real MSVC object**. All four original old units still exact, and three additional 200/196/73B original methods exact. No global/full cold replay.

## Exact 470B counted-range upstream mismatch: one real constexpr helper call

The original upstream STL _Assign_counted_range at **0x0047A8D0** is **470B /174 original x86 instructions /12 original E8 calls**, not yet exact. Its real original native E8 at **0x0047A99F** calls the separately already strictly exact **7B std::is_constant_evaluated** at **0x00411170**. That result is tested, with a real branch selecting the copy path. This original source/runtime check was previously not explained by older C++20/odd-compiler-register mismatch hypotheses.

With current pinned C++17 STL, the natural typed source compiles to **458B/170 x86/11 COFF E8**, and 170/174 original mnemonic heads are aligned in order. The original additional **12 bytes /four instructions** are the real call, MOVZX, TEST and conditional branch to the already known 7B std::is_constant_evaluated helper. Pinned C++20 instead generates **401B/150 x86/9 E8**, using a different STL counted-copy code path; /sdl, /GS, floating-point mode and iterator-debug-level-0 toggles do not repair this whole helper. Forcing C++20 STL feature macros on a C++17 compiler fails to compile, and a C++20 build with C++20 features disabled produces 389B, not the original.

**Do not artificially add a no-op is_constant_evaluated call or modify the pinned STL headers to mimic this path.** Historical native SDK/library implementation details remain unresolved; neither this 470B counted-range method nor its incompatible 96B copy helper is admitted as exact. The 32B vector cleanup helper also remains separately NONEXACT. These are true remaining native library frontiers within the source-absent 12,140B game Bullet Boss.

## Evidence and conservative accounting

- .analysis/core736-vector-counted-range-profile-probes.py/json — full 470B original vs natural C++17/20 whole typed MSVC source and profile variants, revealing 458B/170 vs401B/150 and original missing constexpr call.
- .analysis/core737-vector-range-feature-flag-probes.py/json — C++ feature/iterator and standard mode controls, never a fake C++ source definition.
- .analysis/core738-register-real-std17-bullet-vector-native.py — compares all four old original strict methods under C++17, re-reads original complete 200/196/73B native code, all 18 true original E8 and two real original PE HIGHLOW fields, then reconciles precisely one provider compiler standard and three strict units.
- .analysis/core739-verify-Bullet-CXX17-native-469.py — **after-admission, nonmutating reproducible verifier**: 7/7 full original exact, native original two SEH/cookie absolute fields, original 470B still NONEXACT with authentic std::is_constant_evaluated branch.
- Existing [121B copy and20B destructor real STL source](BULLET_COMMAND_PMR_VECTOR_121_20_LIBRARY_EXACT.md) — source is unchanged; original language-profile tests preserved their exactness.

Canonical strict units rise from **1,191 to 1,194**, and source-present function mappings from **1,189 to 1,192**, all within the one existing original ShotMetadataVectorInstantiation.cpp source owner. **Game-authored exact coverage remains 549 whole functions /186,446 disjoint original game code bytes**; these 469 original bytes are classified library/excluded. No original target patch, fabricated source method, duplicate source owner or whole-project cold replay.
