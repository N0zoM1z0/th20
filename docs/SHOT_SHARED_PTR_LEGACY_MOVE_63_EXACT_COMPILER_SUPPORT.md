# CORE/STL-577 — full original 63-byte `std::shared_ptr<EtamaArgInf>` move assignment, exact C++ toolchain support

**Later [CORE/EXACT-749](BULLET_SHARED_PTR_LEGACY_CTOR_100_LIBRARY_EXACT.md) update:** the original 46B shared_ptr move temporary constructor and original 54B pointer-base move helper now have actual natural pinned MSVC C++ whole native exact source in the same legacy STL owner; all three methods 63/46/54B pass **3/3 scoped strict**. The 33B _Ptr_base initializer and 8B std::move instruction bodies are real but fold-compatible with already credited physical heads, so no duplicate code is counted. The historical statement below that the separate **3,735B Bullet emitter parent** was nonexact has since been superseded by its full [3,735B original strict exact acceptance](BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md). The 12,140B game command dispatcher remains NONEXACT.

Target: immutable Japanese TH20 v1.00a Steamless executable
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The original complete native `std::shared_ptr<EtamaArgInf>` move
assignment at `0x0047C530..0x0047C56E` is now strictly exact:
63/63 original bytes, 23/23 native i386 instruction heads, four
independently original E8 calls and the remaining 47/47 native bytes.**
It was a real previously missing link dependency of the maintained
**3,735-byte `BulletController::emit`** at the original E8
`0x0048199B`. The new whole C++ source is
`src/ShotSharedPtrMoveLegacy.cpp`, compiled under a pinned local
MSVC 19.44.35211 x86 profile. It is **STL/library-origin compiler
support and is explicitly excluded from game-authored exact code
coverage**. The Bullet emitter itself remains **NONEXACT**: exactness
of this library callee and its other children is not full parent
byte equality, nor proof of a complete linked game.

## The specific original legacy C++ lifetime, not a guessed library API

The immutable original 63-byte native body has an actual
`std::move` E8 call, constructs a temporary
`std::shared_ptr<EtamaArgInf>` from the returned rvalue, immediately
calls `swap(*this)` **on the object returned by temporary construction**,
then destroys that temporary before returning the original receiving
`shared_ptr&`. The genuine source-level lifetime which reproduces
this is:

```cpp
shared_ptr<EtamaArgInf>&
shared_ptr<EtamaArgInf>::operator=(shared_ptr<EtamaArgInf>&& other) noexcept {
    shared_ptr<EtamaArgInf>(std::move(other)).swap(*this);
    return *this;
}
```

**Anonymous temporary ownership is decisive.** The older private
candidate created a **named** `shared_ptr<EtamaArgInf> temporary`,
then did `temporary.swap(*this)`. Under the actual `/Od` compiler the
named lvalue changes return-temporary and receiver evaluation order.
That candidate did *not* match the entire physical native method:
with a noninline source-level move, it emitted **66B / 24
instructions**, storing receiver/local state in a different order.
The source with the **anonymous prvalue** above emits exactly the
original **63B / 23 instruction heads** and the native receiver/stack
lifetime, including the original `nop` after temporary destruction.
No manual assembly, duplicated byte stream, artificial stack-filler,
copy of binary bytes or fake output field is present.

A second independent compiler mismatch was the **legacy
noninlined `std::move` helper**. The current locked MSVC standard
library's inline `std::move(other)` produces a **57B** compatible
move-assignment candidate with only three E8 calls when `/sdl` is off.
Forcing `/sdl` does *not* fix this: it creates an **87B** candidate
with unwanted security cookie and an automatic shared_ptr clear helper.
These were independently tested with variations of `/GS`, `/EHsc`,
`/Ob`, and `/sdl`; neither compiler switch is a faithful original
reconstruction.

The actual maintained source therefore supplies a **narrowly typed
noinline compatibility specialization** for the concrete old
`std::move<std::shared_ptr<EtamaArgInf>&>` operation, which simply
returns the correct `std::shared_ptr<EtamaArgInf>&&`. The physical
helper itself emits **8/8 original bytes**, exactly equal to native
`0x0040B280` (`push ebp; mov ebp,esp; mov eax,[ebp+8]; pop ebp; ret`).
That 8-byte original address was already canonical through a
physically folded `std::addressof` role in
`src/EclLoaderBuffer.cpp` (`ecl_records_storage_address`). **It is
not a new 8-byte original game or library credit**. The move helper
returns an rvalue reference with the same object identity and no
new observable side effect.

This file is a **locked toolchain compatibility overlay**, not a
claim to reproduce an unmodified modern standard-library header.
It uses explicit specializations in `namespace std` to model the
historical compiler/library code-generation contract for the one
concrete original shared owner. Portable standard-library
specialization/ODR compatibility outside this pinned MSVC build and
whole-program COMDAT/linker selection are **not established**; the
source is isolated in its own translation unit and should not be
blindly assumed safe for arbitrary compilers or other shared_ptr
types. The project has not yet linked a complete executable, and
this exactness proof does not establish a final game's runtime
behavior or eliminate other original STL ABI differences.

## Independently original PE and C++ full-reference proof

An independent original reader decoded **all 23 entire x86
instruction heads** from `0x0047C530` through its real `ret 4` at
`0x0047C56C`, without truncation. Each of the following **original
E8 source instruction heads** was independently decoded from its
immutable PE signed relative operand:

| Original game E8 | Original physical callee | Real original library role |
| --- | --- | --- |
| `0x0047C53D` | **`0x0040B280`** | Noninlined old `std::move<shared_ptr<EtamaArgInf>&>` |
| `0x0047C549` | **`0x0047B820`** | `std::shared_ptr<EtamaArgInf>` true move constructor |
| `0x0047C558` | **`0x00486690`** | `shared_ptr::swap(shared_ptr&)` on the anonymous temporary's returned pointer |
| `0x0047C560` | **`0x0047C300`** | `shared_ptr` temporary destructor, before returning the receiver |

The original executable's **actual PE `.reloc` HIGHLOW directory** has
**zero** absolute relocations inside the entire 63B method, so these
four original E8 fields form its complete original relocation census.
All **four genuine COFF REL32 relocation field sites and native
absolute destinations** match the original actual PE instruction
locations and decorated old STL source symbol identities, including
natural linker addends. The remaining **47/47 original nonrelocated
bytes** are identical in the fresh natural C++20 compiler object.
The entire original native method SHA-256 is
`c6c3e9194fe594ea962020332fa717d31a49f2d3a203414f6d3503c41733a073`.
The separate exact physical 8-byte original helper SHA-256 is
`d5a2b635b0bbb254914f2641e4508361a0c95686c0422dcebeb3abbcca7f1d2b`.
Neither physical body duplicates a previously accepted *authored game*
function interval. The separate 8B physical helper was already
represented in the compiler support graph and is intentionally not
registered or counted a second time.

The full independently native original function, actual `.reloc`,
all four callee target and nonrelocated-byte proof, plus the physically
folded helper evidence, is in
`.analysis/core576-shot-shared-move-63-native-original-proof.json`
and `.analysis/core576-shot-move-native-original-proof.log`.
The separately compiled source-lifetime/flag experiments are in
`.analysis/core572-shared-move-profile-screen.json`,
`.analysis/core573-legacy-move-build.log`, and
`.analysis/core574-legacy-move-build.log`.

## Formal strict canonical replay and correctly excluded authored credit

A new real canonical unit `shot_shared_ptr_legacy_move_assignment`
compiles the maintained `src/ShotSharedPtrMoveLegacy.cpp` under locked
MSVC 19.44.35211 i386 `/nologo /c /std:c++20 /Od /Ob0
/GS- /sdl- /Gy /Zl /arch:SSE2 /fp:precise /EHsc`. The actual
strict original source/object receipt is
`build/core577-canonical/ShotSharedPtrMoveLegacy.obj`. Formal
`compare-coff-function.py --unit shot_shared_ptr_legacy_move_assignment
--json` reports **`exact` for entire 63/63 original bytes** with all
four original E8 fields and destinations. Strict source-scoped replay
of only that one actual new object reports **1/1 native units exact**;
no shared header or previously exact source/provider was modified,
and **no 1,184-unit full cold replay** was run.

Tracked function `0x0047C530` has `owner=library`, native origin
`library`, `disposition=exclude`, and 100% original compiler
match. It is deliberately **not added to `config/matches.csv`**, which
tracks *game-authored* physical original exact code only. The
already canonical 8B std::move/addressof folded source at
`0x0040B280` remains in its prior review state pending a separate
full folded-source ownership decision; no duplicate native credit.

**Native strict canonical units increase from 1,183 to 1,184; real
MSVC object providers from 242 to 243; source-present function mappings
from 1,182 to 1,183.** Game-authored whole exact code remains
**498 functions / 175,709 distinct original game bytes**. The old
STL support source is independent of the as-yet NONEXACT 3,735B
Bullet emitter, original 63B shared_ptr *move constructor* 46B and
other legacy STL shared-owner support; full game linkage and runtime
remain open.
