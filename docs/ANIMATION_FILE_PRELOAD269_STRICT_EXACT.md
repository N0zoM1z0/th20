# CORE/RECON-1097 — whole original 269B Renderer ANM file preload Boss, strict exact

Immutable Japanese TH20 Steamless v1.00a executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The previously source-absent original Renderer ANM preload method
`0x0044ED40` is now a complete **269B/79-instruction i386**
game-authored function, original SHA-256
`a802bfc6ec01c915d6c382ed0d6ed9c6098f5865507900690495871f8a50cb7d`.
It has natural maintained C++20 source in
[`src/AnimationFilePreload269.cpp`](../src/AnimationFilePreload269.cpp)
using a non-allocating Renderer type view and all previously verified
real `AnimationFile`, `DiagnosticAllocator`, `LockRegistry` and
`DiagnosticLog` interfaces. It genuinely performs the allocation,
registry publication, actual resource load and on-failure retirement,
not merely a scalar wrapper around a lower function.

## Original game allocation and lock boundary

The original logs the actual native `::preloadAnim : %s\n` diagnostic
through existing folded `ecl_diagnostic_hint`; tests the **signed**
file index against `42`, with an original CP932 Japanese file-slot
error message from `0x0056E38C` to the shared `DiagnosticLog`
`0x005C0678` when the index is out of range; and returns null
without touching any files or locks in that branch.

For an in-range file slot, it acquires the original recursive lock
**slot `0x11` (17)**, calls the existing whole-exact **67B**
`DiagnosticAllocator::allocate_object<AnimationFile>` at
`0x004477B0` using the original `sprtlib.cpp:950 SprtGroupInf`
source label, and registers the resulting actual **0x70B
AnimationFile** at the real Renderer instance's
**`this+0x06000730`** array of **42 pointers**, via the original
whole-exact checked **34B** `std::array<AnimationFile*,42>::at`
`0x0043EB10`. The native allocation occurs before the array
publication and writes the actual file ID at AnimationFile offset
`+0x00`. The method releases the lock **before** loading actual
resource bytes, preserving the original observed critical section
and not inventing additional lock coverage.

After the guard is destroyed, it calls the already whole-exact
**1,022B game AnimationFile resource loader** at `0x0044A700`.
If that load reports nonzero, the original calls the actual
whole-exact **97B** `DiagnosticAllocator::release_object<AnimationFile>`
`0x004473A0` through its own real allocator-global, then returns
null from a **distinct failure branch**. A successful load returns
the same AnimationFile pointer. As in the original executable, the
failure path does not invent extra cleanup of the Renderer array
slot; that remains a separate owner-lifetime concern.

## Exact original native PE E8 and HIGHLOW graph

The entire locked original has exactly **ten genuine E8**:

| Original E8 site | Physical original target |
| --- | --- |
| `+0x34` | `0x0040C6B0` existing folded diagnostic hint |
| `+0x4C` | `0x00454230` independently exact game `report_log_error` |
| `+0x62` | `0x0040C310` actual recursive lock registry lookup |
| `+0x6B` | `0x0040B730` actual `std::lock_guard` ctor |
| `+0x82` | `0x004477B0` exact 67B AnimationFile scalar factory |
| `+0x9D` | `0x0043EB10` exact 34B checked 42-file array access |
| `+0xBF` | `0x0040B900` real lock guard destructor |
| `+0xCC` | `0x0044A700` exact 1,022B AnimationFile resource loader Boss |
| `+0xDF` | `0x004473A0` exact 97B AnimationFile release helper |
| `+0x102` | `0x005429EE` actual native compiler cookie check |

The nine actual original PE HIGHLOW fields are compiler handler
`+0x06 -> 0x005676ED`, cookie `+0x15 ->0x005B25C0`, original
preload-log and out-of-slots strings `+0x30/+0x43` at
`0x0056E378/0x0056E38C`, actual diagnostic context
`+0x48 ->0x005C0678`, lock registry `+0x5E ->0x005C0240`,
original provenance label `+0x78 ->0x0056E3B0`, and the
**two genuine allocator-global references `+0x7E/+0xDB`
both to `0x005B8894`**. The real native compiler body ends
with `ret 8` at physical 269B.

The first meaningful candidate with success-first control flow
compiled to 271B with the error branch after allocation and
loading, not the original. Restoring the original **early capacity
failure** reduced it to 265B, but wrongly merged the negative
load return with the successful pointer return. Preserving the
real separate **`return nullptr` immediately after failed load
cleanup** naturally restores the remaining native error-return
block and generates **269B/79 i386**, including the genuine
critical-section unwind NOP and all original branch distances.
No fake side effects, target bytes, inline assembly, artificial
padding or dead compiler-shaping locals were introduced.

Pinned MSVC19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
then generates **269/269 native bytes** with **193/193 ordinary
nonrelocated bytes** and all 19 original physical relocation
field/type/target roles. The original whole-body SHA, native
instructions/returns, actual logger, checked array, genuine 67B
allocator and 97B release, and the already exact 1,022B game
loader are independently rechecked by read-only
[`verify-animation-file-preload269-native.py`](../scripts/verify-animation-file-preload269-native.py).

```text
animation_file_preload_269: exact (269/269 bytes)
Original whole game function: 269B /79 i386
Comparable original bytes: 193/193
Native original relocation roles: ten E8 REL32 /nine PE HIGHLOW
Exact replay: 1/1 unit, one affected cold object
```

This accepts **one distinct new game-authored original physical
head /269 original executable `.text` bytes**. The existing 67B,
34B, 97B, 1,022B and original logging/locking implementations
remain independently credited, without duplicate code bytes.
The 336B Renderer ANM group parser called *inside* the 1,022B
loader remains an independently sourced **NONEXACT** 2B stack-frame
frontier; its child code and original PE were not artificially
made exact by this preload wrapper. The whole game still does not
link/play, and no project-wide cold replay was run.

```sh
scripts/repo-python scripts/verify-animation-file-preload269-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFilePreload269.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1098 — original 182B find/preload caller now strict exact

The complete original [182B Renderer AnimationFile find/preload/wait
Boss](ANIMATION_FILE_FIND_OR_LOAD182_STRICT_EXACT.md) is now whole exact.
It calls this 269B game preloader at physical original E8
`0x0044EB30+0x43`, after first checking the real Renderer file
registry. On success the caller writes the original atomic stage,
waits via real atomic Boolean conversion and `Sleep(1)` under the
original async-mode flag, then returns the file. The 182B caller is
a distinct game native function; it does not recredit this already
accepted 269B preload or the 1,022B resource-load code.
