# CORE/EXACT-275 — complete original 51B AnimationHandle resolver and 44B Bullet handle test

The immutable Japanese TH20 v1.00a Steamless PE,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
is the independent native source. These two entire game-authored functions
are original real dependencies of the **2,018-byte** Bullet collision boss
`0x00484A20`, which remains separately nonexact.

| Complete original function | Entry | Native bytes | Original relocations | Canonical strict result |
| --- | --- | ---: | ---: | ---: |
| `AnimationHandle::resolve()` | `0x0044CED0` | **51** | **2** | **51/51** |
| `bullet_animation_handle_valid(AnimationHandle&)` | `0x00485A10` | **44** | **1** | **44/44** |

**95 entire original native bytes** and **3 independently identified
original relocated destinations**, one new C++20 translation unit
`src/BulletCollisionHandle.cpp` and its own narrow interface header.
There is no target-byte array, guessed Renderer layout, compiler padding,
assembly or partial function admission. Original full-body SHA-256 values
are `635176978dab8b6305977fd67facd4ac2a4aec600ca9d185eee74e5e1ceab209`
(51B/18 x86 instructions) and
`d413838a798996599a9a65fe9ce913b03ac01e6892ad39cefab8921623c165f4`
(44B/15 original instructions).

The real four-byte `AnimationHandle::value` is passed to the original
`AnimationPoolOwner::resolve_handle(index)` at **`0x0044CD00`** through
the true `current_animation_pool` pointer at **`0x005C0028`**.
If that actual native resolver returns null, the `AnimationHandle`
clears its stored `value` to zero. It returns the authentic
`Animation*` pointer (possibly null); its original complete 51B ABI
and both native call/data relocations match exactly. The separate
456B manager resolver remains nonexact: this submission adds no
invented array/state definition to `AnimationRuntimeOwner.hpp`.

An independent 44B fastcall wrapper consumes a genuine live
`AnimationHandle&`, calls the exact 51B method, and returns 0 or 1
as a **full 32-bit `std::int32_t`** value. The decompiler called this
`bool`, but that initially emitted 45B due to an extra `movzx eax,byte
ptr [...]`. Its actual PE disassembly shows `mov eax,dword ptr [...]`
and a **full-word 32-bit return**. Correctly typing this original
return produces **44/44 bytes** and the real `0x0044CED0` call target,
without changing control-flow meaning or adding a dummy instruction.

All original relocation sites were independently bound by Capstone
reading the **original PE instruction operands**, not the COFF
comparator's proposed targets: 51B offsets `+0x11 DIR32` to
`0x005C0028` and `+0x16 REL32` to `0x0044CD00`, and 44B
`+0x0D REL32` to `0x0044CED0`. Original bytes of every relocated
word were checked against these actual destinations. Private original
attestation is `.analysis/core275-handle-native-attestation.json`, and
the locked MSVC 19.44 x86 canonical build strict result is in
`.analysis/core275-handle-native-canonical-replay.log`:
**2/2 exact whole units, one fresh cold object**. Actual compiler
profile is `/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` with reduced scheduling priority.

This batch changes only a **new source and its own header** plus native
tracking/evidence. No previously accepted compilation input, shared
owner layout, existing header, original relocation or build profile
changes. Therefore **zero previously exact units need recompilation**;
only the **two new full 51B/44B functions** were cold built and strictly
replayed. No unfiltered full-graph cold replay was run.

The original **2,018-byte** `Bullet::process_collision` boss, original
**332B** Player graze response `0x004F8B90`, complete **336B** Player
damage handler `0x004F86F0`, native **3,735B** shot emitter, **1,404B**
Bullet command11, **12,140B** Bullet command root, and **41,967B**
Enemy ECL dispatcher remain separate nonexact whole functions.
