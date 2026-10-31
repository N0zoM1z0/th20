# CORE/RECON-1099 — two whole-original STL atomic wrappers for ANM preload, 49B strict exact

Immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The independently [WHOLE STRICT EXACT **182B** game Renderer
AnimationFile find/preload/wait method](ANIMATION_FILE_FIND_OR_LOAD182_STRICT_EXACT.md)
`0x0044EB30` naturally instantiates two distinct complete native
`std::atomic<std::uint32_t>` compiler/library methods. They are not
another game-side preloader or invented source stubs:

| Whole original head | Genuine native code | Independently original caller and nested callee |
| --- | --- | --- |
| `0x004493C0` atomic assignment `operator=(uint32_t)` | **28B/12 i386**, SHA-256 `92b9ef8a164060015ffd17d7e4fd8dc3b4e51cb2035abcc33df7051c195705c7` | original 182B parent E8 `+0x5D`; child E8 `+0x0E -> 0x0040C550` atomic-storage `store` |
| `0x004292C0` atomic value conversion `operator uint32_t()` | **21B/10 i386**, SHA-256 `c0826eff4a5d0e01f268b19ea363af174e4165357bef14133664b1cf291bd715` | original 182B parent E8 `+0x69`; child E8 `+0x0C -> 0x0040C420` atomic-storage `load` |

Both original physical heads contain **zero PE HIGHLOW** fields and
have exactly one native E8 each. The original 182B game caller reads
its real `AnimationFile::stage` at `AnimationFile+0x5C` and uses an
atomic **value conversion followed by a Boolean test** in the polling
condition. The original method does not call the modern STL's direct
`stage.load()` expression, which emits a different function graph.
The corrected parent source uses `static_cast<bool>(file->stage)`,
which invokes the ordinary MSVC atomic integer value conversion and
naturally reproduces the actual native call, without a fake temporary,
NOP or ABI substitution.

Read-only checker
[`verify-animation-file-atomic-two-native.py`](../scripts/verify-animation-file-atomic-two-native.py)
SHA-attests each *whole* original 28B and 21B head, all instruction
boundaries, real original 182B parent SHA and E8 sites, and each
separate original atomic-storage target. It requires whole strict
canonical receipts for both original code contributions. Pinned
MSVC19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` generates these naturally from
[`src/AnimationFileFindOrLoad182.cpp`](../src/AnimationFileFindOrLoad182.cpp):

```text
animation_file_find_or_load_182: exact (182/182 bytes)
animation_file_atomic_assign_28: exact (28/28 bytes)
animation_file_atomic_value_21: exact (21/21 bytes)
Exact replay: 3/3 strict units, ONE affected source object
```

These add **49 distinct original generic STL `.text` bytes /two
independent native code heads**. Their provenance is
`origin=unknown`, `disposition=review`, so they add **zero
new game-authored exact bytes or heads**. The 182B original game
method, its whole-exact 269B preload and 40B file lookup, and their
own atomic-storage descendants are separate physical methods not
credited twice. No full-project cold replay was run.

```sh
scripts/repo-python scripts/verify-animation-file-atomic-two-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFileFindOrLoad182.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
