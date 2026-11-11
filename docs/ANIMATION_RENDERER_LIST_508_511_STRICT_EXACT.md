# CORE/RECON-1110 — complete 508B/511B Renderer list-update Bosses, whole strict exact

**WHOLE STRICT EXACT, both game-authored parents.** Locked original TH20
Japanese Steamless v1.00a (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains two distinct original Renderer Animation update functions:

| Physical native body | Original range | Original instructions | E8 calls | PE HIGHLOW | New canonical result |
| --- | --- | ---: | ---: | ---: | --- |
| Primary list update `0x00449870` | `0x00449870..0x00449A6B` | **508B /152 i386** | 30 | 5 | **508/508B exact** |
| Secondary list update `0x00449B20` | `0x00449B20..0x00449D1E` | **511B /153 i386** | 30 | 5 | **511/511B exact** |

Their entire original code SHA-256 values are respectively
`72f3b77118e6fba3230975dc9998241d7251a6cfa01c058a02bdb535b618fc6d`
and `82610fc6e8e74938e509de8a188f053c31e2e9e08ff4039f498b7046861258d8`.
Both functions end at their real `ret`, followed by original `INT3`
alignment. The independently whole-exact 150B/164B Renderer wrappers call
the corresponding original function and remain strict exact after migration.

## Genuine C++ algorithm and compiler class-key repair

The maintained parent sources are
[`src/AnimationRendererListUpdate508.cpp`](../src/AnimationRendererListUpdate508.cpp)
and
[`src/AnimationRendererListUpdate511.cpp`](../src/AnimationRendererListUpdate511.cpp).
They both implement the real **two-pass deferred retirement** protocol:
clear `Animation+0x554/+0x550` on each live element; queue animations in
native state `+0x570==1`, or animations whose state is zero and whose VM
`update()` returns nonzero; then traverse the pending list and release its
contents through the real `AnimationPoolOwner::release_animation()`.
The secondary source adds the original `+0x18` list selection; it is not
identical to the primary and receives separate, nonoverlapping byte credit.
The 39,470B Animation VM remains independently NONEXACT, and this parent
match does not imply VM exactness or a working linked game.

The only original code gap was a real **ten-byte MSVC `/sdl` class
initialization**, `push 0x18; lea ecx,[ebp-0x38]; call 0x0040C080`
at original primary and secondary offset `+0x2B..+0x34`. A generic
`struct IntrusiveList<T>` causes locked MSVC to omit this instruction
and emits 498B/501B instead. The maintained
[`src/IntrusiveListAnimation.hpp`](../src/IntrusiveListAnimation.hpp)
now declares an explicit **`class IntrusiveList<Animation>` specialization**
with the same genuine 24B list/link layout and real operations. It is
seen consistently by the specific Animation users and owner/API headers,
without changing the generic `src/IntrusiveLink.hpp` or hundreds of unrelated
`IntrusiveList<OtherType>` instantiations. The actual folded `front()`
definition was moved from the PoolAllocate `.cpp` specialization into this
single class owner; the independently exact 298B pool allocator still
matches and the original physical `front()` target remains `0x0040FF90`.

No artificial no-op, inline assembly, shortened function, patched target
or invented relocated destination was introduced.

## Whole independent original / complete relocation attestation

[`scripts/verify-animation-renderer-list-update-native.py`](../scripts/verify-animation-renderer-list-update-native.py)
SHA-attests each immutable original **entire function**, independently
decodes **all 30 native E8 destinations** and **five physical PE HIGHLOW
field/destination pairs**, verifies original instruction count, return
boundary, real `/sdl` class preclear, and secondary `+0x18` list choice.
The new `--whole-candidate-object` mode compares exactly the full original
508B/511B COFF contributions against the physical PE: all 35
corresponding relocation offsets, kinds, and destinations must agree
with the *original-only* evidence. The original nonrelocation ordinary
bytes match **368/368** for primary, **371/371** for secondary.

The authoritative `compare-coff-function.py --unit` then performs **full
relocation replay**, not just structural or normalized comparison. Under
locked MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` both canonical full objects passed
**508/508 relocated bytes** and **511/511 relocated bytes**. The
normalization that removed the native ten-byte initializer in historical
[CORE/RECON-993/994](ANIMATION_RENDERER_LIST_UPDATE_508_511_NATIVE_FRONTIER.md)
is no longer needed for either accepted unit.

The original list constructor `0x00418A50` (40B) and reset `0x0044A640`
(42B) remain separate unresolved native helpers. This checkpoint does
**not** claim them exact: the compiled constructor still differs in size,
and the reset still has a register-selection byte mismatch. Their original
physical targets are nevertheless independently pinned at E8 fields in
the now-exact parent functions. The already exact 411B recursive-retirement
and 308B pool-release callees are not recredited.

## ABI migration and all affected previously exact units

The old `struct`/new `class` tag changes how MSVC decorates a
`IntrusiveList<Animation>*` argument (`PAU` → `PAV`) even when the entire
C++ code sequence is identical. No ABI symbol was simply ignored or
mapped to an invented physical address. Exactly five changed identity
records were migrated with **original destination addresses unchanged**:

- The original 298B pool allocator's one compiler-generated `$SG...`
  constant label, physical DIR32 target still `0x0056E5BC`.
- The 150B primary Renderer wrapper's one `PAU`→`PAV` E8 symbol,
  original native E8 destination still `0x00449870`.
- The 411B retirement callee's declared method symbol, true EH-handler
  symbol, and self-recursive E8 symbol, with unchanged original targets
  `0x0044F840` / `0x0056867D`.

All necessary direct Animation consumer `.cpp` files and the four relevant
Renderer/retirement owner headers now see the same special class definition.
A *complete included-header dependency audit* identified **82 previously
strict units in 22 distinct compiler objects**. Rather than running a cold
project replay, the native exact ledger was replayed **only for those
22 objects**, grouped as follows:

| Scope | Original exact units | Recompiled objects | Strict result |
| --- | ---: | ---: | --- |
| Animation core/children/handles | 58 | 5 | **58/58 pass** |
| AnimationFile spawn / pool allocation/resolve/lifetime | 9 | 6 | **9/9 pass** |
| Renderer retirement, classification, wrappers and staging | 15 | 11 | **15/15 pass** |
| **Existing exact coverage protected** | **82** | **22** | **82/82 whole relocated pass** |

An initial private test comparing just original code `size` rather than
configured COFF `compare_size` mistakenly interpreted five bytes of
existing *after-ret* compiler padding in several `Animation.cpp`
constructors/destructors as an ABI regression. That error was corrected
before promotion: the complete original `Animation.cpp` translation unit
and all **38/38 canonical contributions**, including the authentic
padding and relocation fields, match. A separate anonymous-namespace
function-checker initially missed lower-case `t` local COFF symbols;
actual canonical whole-function replay independently passed all **4/4**
AnimationHandle resolver/list predicate units.

**Accepted credit from this checkpoint:** +2 distinct game-authored
functions, +**1,019** original `.text` code bytes. No helpers, padding,
external VM code or duplicated folded symbols are added. At this checkpoint
the game ledger totals **774 whole authored exact heads /265,580 bytes**;
there are **1,583 strict units, 437 canonical object providers** and
**1,585 source-covered functions**.

## Reproduce only this migration

```sh
# Physical original PE + full new canonical object roles
scripts/repo-python scripts/verify-animation-renderer-list-update-native.py \
  --variant 508 --whole-candidate-object build/core1110-canonical/AnimationRendererListUpdate508.obj
scripts/repo-python scripts/verify-animation-renderer-list-update-native.py \
  --variant 511 --whole-candidate-object build/core1110-canonical/AnimationRendererListUpdate511.obj

# Strict full native byte comparison, including all relocations
scripts/repo-python scripts/compare-coff-function.py --unit animation_renderer_list_update_primary_508
scripts/repo-python scripts/compare-coff-function.py --unit animation_renderer_list_update_secondary_511

# Historical independent isolated class-key research
scripts/repo-python scripts/probe-animation-renderer-list-class-tag.py
```

The 82 already exact units were freshly rebuilt and replayed in three
source-scoped `replay-exact-units.py --source ...` batches. The exact
individual source lists and receipts are preserved in the build tree;
**no full all-source cold replay was run**.
