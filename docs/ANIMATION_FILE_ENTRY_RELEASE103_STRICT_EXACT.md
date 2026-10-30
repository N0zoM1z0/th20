# CORE/RECON-973 — full 103B original file-object retirement, genuine existing 16B STL callee

Target: immutable Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native `0x00447330` is the complete **103B/36-i386**
allocator-side pointer-to-`AnimationFile` retirement function, used by
an independently exact [209B RendererPool file-slot release](ANIMATION_FILE_SLOT_RELEASE209_STRICT_EXACT.md).
Original PE verification in
[`scripts/verify-animation-file-entry-release103-native.py`](../scripts/verify-animation-file-entry-release103-native.py)
checks all 103 native bytes, 36 instructions through `ret 4`, all **six
actual E8 instruction offsets and physical targets**, the two genuine
PE HIGHLOW locations, and the real 209B parent E8 call.

| Original native field | Actual original address / meaning |
| --- | --- |
| E8 `+0x23` | **`0x00447850`** — already separately exact 16B `std::destroy_at<AnimationFile>` |
| E8 `+0x32/+0x3B/+0x51` | `0x0040C310/0x0040B730/0x0040B900` — actual lock slot, lock_guard ctor/dtor |
| E8 `+0x46` | `0x005429FC` — actual global `operator delete` |
| E8 `+0x5C` | `0x005429EE` — original security-cookie check |
| DIR32 `+0x07/+0x2E` | `0x005B25C0` security cookie, `0x005C0240` process lock registry |

**Important duplicate correction.** An initial dirty source hypothesis
had added a second 16B match unit for `0x00447850`, with a provisional
`native_destroy_file_447850` wrapper spelling. Independent inspection
of the actual canonical ledger and original disassembly established
that the **same original 16B address was already whole strict exact**
under the genuine `std::destroy_at<AnimationFile>` symbol in
[`src/Animation.cpp`](../src/Animation.cpp), with original provenance
`library/exclude` (CORE/EXACT-132). This duplicate hypothesis was
**withdrawn**, not committed or credited. The maintained 103B source
now directly calls the existing actual `std::destroy_at` function and
replays against its **already accepted** COFF symbol and physical
address. Its own `NativeDiagnosticFileAllocator` view adds no storage.

Original `/Od` emits an intentional empty null-pointer branch before
the valid cleanup path. Natural
[`src/AnimationFileEntryRelease103.cpp`](../src/AnimationFileEntryRelease103.cpp)
faithfully preserves it, including a scoped `std::lock_guard` on
lock slot **1** around only the final delete. A simple `if (*entry)`
emits an incorrect 101B implementation; the empty null arm naturally
emits the original **103B/36 instructions** with 71/71 matching
nonrelocated bytes. There is no hand-inserted NOP or target patch.

Original-target-bound MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` local replay, after retiring the
conflicting 16B duplicate unit and sharing a single allocator view
with the 209B parent:

```text
animation_file_entry_release_103: exact (103/103 bytes)
animation_file_slot_release_209: exact (209/209 bytes)
animation_file_clear_284: exact (284/284 bytes)
animation_texture_record_release_94: exact (94/94 bytes)
animation_renderer_file_detach_691: exact (691/691 bytes)
Exact replay: 5/5 affected units, 5 cold objects
```

This adds **one original function head and 103 whole strict source
bytes**, but **zero game-authored credit**, because the original
allocator/template implementation's source authorship is not yet
proven. The previously exact 16B STL callee is not added as a second
head, and the existing 691B/284B/209B/94B game functions are not
recredited. The whole executable still does not link/play, and no
full-graph cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-file-entry-release103-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationFileEntryRelease103.cpp --source src/AnimationFileSlotRelease209.cpp --source src/AnimationRendererFileDetach691.cpp --source src/AnimationFileClear284.cpp --source src/AnimationTextureRelease94.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
