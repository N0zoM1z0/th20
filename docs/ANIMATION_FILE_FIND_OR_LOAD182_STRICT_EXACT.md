# CORE/RECON-1098 — original whole 182B Renderer AnimationFile find/preload/wait, strict exact

Immutable Japanese TH20 Steamless v1.00a source target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original game-owned `0x0044EB30` Renderer method is a complete
**182B/64-i386** resource lookup/preload-and-completion polling Boss,
original whole native SHA-256
`559e1e2c9c7e103c8f856e127908eb1b10b4929f2a25ac714b1d8089b5d276fe`.
It now has natural C++20 source
[`AnimationFileFindOrLoad182.cpp`](../src/AnimationFileFindOrLoad182.cpp)
which generates **182/182 whole-native strict exact** on the pinned MSVC
19.44 x86 C++20 profile.

The method first calls the separately exact 40B
`AnimationPoolOwner::file_by_index` at original native E8 `+0x10`,
then either returns the already loaded `AnimationFile*` after the
original `::preloadAnim already` message and a second native file-index
lookup E8 `+0x31`, or invokes the independently exact **269B
`preload_anm_44ed40`** at E8 `+0x43`. A failed preload returns null.
On success the original sets the actual `AnimationFile::stage`
`std::atomic<uint32_t>` at original file offset `+0x5C` to `1`, then
polls its state until completion, checking original process global
`0x005C5888` bits 5-6; if no override is requested it calls the
native Win32 `Sleep(1)` IAT to retry. After successful completion it
logs `::preloadAnimEnd` and returns the same resource pointer.

## Original atomic boolean conversion is essential

An initial meaningful C++20 source used `file->stage.load()` in the
loop and produced a **172B/61-instruction** body with all seven E8
and four data fields, but an incorrect STL conversion target and a
missing compiler-generated boolean lifetime path. The actual native
original contains:

| Native original E8 | Actual physical callee |
| --- | --- |
| `+0x10`, `+0x31` | same exact game file-array lookup `0x00437970`, 40B |
| `+0x22`, `+0xA5` | the existing game diagnostic `0x0040C6B0` |
| `+0x43` | exact game 269B Renderer preload `0x0044ED40` |
| `+0x5D` | original 28B `std::atomic<uint32_t>::operator=(uint32_t)` `0x004493C0` |
| `+0x69` | **original 21B atomic Boolean conversion** `0x004292C0`, not a no-argument `.load()` body |

Expressing the real semantic operation as the implicit Boolean test
`while (file->stage && ((native_renderer_async_mode_5c5888 >> 5) & 3) == 0)`
naturally causes MSVC to invoke the original 21B conversion wrapper,
generate the original two conditional branches and temporary Boolean,
and retain the two genuine post-atomic/Sleep compiler NOPs.
The explicit `static_cast<uint32_t>(file->stage)` and direct `.load()`
forms were separately compiled and did **not** reproduce the original
native method. This is not padding or an
inert code-shaping local: an atomic value is actually used as a Boolean
completion predicate. The entire compiled method is now **182B/64
instructions** with **138/138 nonrelocated bytes** and all original
seven E8 calls/four HIGHLOW. The original ends in `ret 8`.

The original four PE HIGHLOW fields are the existing log literal
`+0x1E -> 0x0056E3F4`, actual process asynchronous status global
`+0x85 -> 0x005C5888`, Win32 Sleep IAT
`+0x95 -> 0x0056C16C`, and completed-preload log literal
`+0xA1 -> 0x0056E410`. The two atomic wrapper original physical
heads are independently verified at full extents, SHA and native E8:
28B `0x004493C0` delegates to `0x0040C550`; 21B `0x004292C0`
delegates to `0x0040C420`. These library/compiler functions are
separately owned and are not credited as new authored gameplay code
just because this game Boss invokes them.

Read-only native verifier
[`verify-animation-file-find-or-load182-native.py`](../scripts/verify-animation-file-find-or-load182-native.py)
SHA-attests the original **entire** 182B function, all original
64 instructions and seven E8/four PE HIGHLOW positions and
physical destinations, and complete original 40B/269B game callees
and 28B/21B generic atomic wrappers. It independently compares
the exact current canonical C++ object against all original target
relocation roles and requires a fresh whole-native strict receipt:

```text
animation_file_find_or_load_182: exact (182/182 bytes)
Original physical function: 182B /64 i386
Ordinary bytes: 138/138
Original relocation roles: 7 E8 REL32 +4 PE HIGHLOW
animation_file_atomic_assign_28: exact (28/28 bytes), generic STL
animation_file_atomic_value_21: exact (21/21 bytes), generic STL
Exact replay: 3/3 units, 1 affected cold object
```

**One newly distinct game-authored original physical head /182 native
`.text` bytes** is credited. Previously exact 40B game file lookup,
269B game preload and downstream 1,022B resource loader remain separate
physical code; the separately whole-exact **28B/21B generic atomic wrappers add
49 distinct original STL bytes** but are never counted as game-authored
code. The existing game-owner credits are not duplicated.
Original executable global linking and playability remain unresolved.
No full-project cold replay, executable patch, fake local or handwritten
instruction was used.

```sh
scripts/repo-python scripts/verify-animation-file-find-or-load182-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFileFindOrLoad182.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1099 — two original atomic wrappers independently accepted

The genuine 28B `std::atomic<uint32_t>::operator=(uint32_t)` and 21B
`std::atomic<uint32_t>::operator uint32_t()` methods invoked by
this 182B game Boss are now separately
[WHOLE strict exact under their own original native heads](ANIMATION_FILE_ATOMIC_28_21_STRICT_EXACT.md).
Their two original E8 into atomic-storage backends and their true
original parent E8 are independently verified. The two wrappers
contribute **49 distinct native generic/library bytes**, with no
additional authored-game credit or duplicate parent coverage.
