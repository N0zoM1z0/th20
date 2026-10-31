**CORE/RECON-1050 STATUS UPDATE:** The formerly NONEXACT original 681B GDI canvas creation parent is now [WHOLE STRICT EXACT, 681/681B](GLYPH_CANVAS_CREATE681_STRICT_EXACT.md). Earlier notes about its 684B candidate below are historical. The separate original 73B allocator and 2,227B glyph text Boss remain unaccepted.

# CORE/RECON-1048 — original 73B glyph canvas allocation wrapper and genuine class-preclear ABI frontier

Locked target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x00413C50..0x00413C98` is a **complete 73B/22-i386**
glyph canvas allocator wrapper, native SHA-256
`b82f916474d1365d308fa06635f6d8b54d7f305f8e6003f360d97879e7c9ee91`.
The independently pinned original **2,227B/470-i386** text Boss
`0x00415830` calls it at native E8 `+0x89`. The wrapper receives an
unused observed stack argument and a receiver in ECX, returns a
new glyph canvas pointer or null, and ends with `ret 4`. Its exact
native source-level declaration remains unresolved.

The complete original physical E8 graph is:

| Native E8 offset | Physical callee | Actual semantic role |
| --- | --- | --- |
| `+0x0E` | `0x0054275D` | actual `operator new(0x124)` allocation |
| `+0x27` | `0x0040C080` | real **31B `__autoclassinit2`** preclear of the newly allocated 0x124B object |
| `+0x2F` | `0x00414200` | whole-exact **124B native glyph canvas constructor** |

The wrapper checks the actual newly allocated pointer for null. On a
successful allocation, it first calls the original MSVC class
preclear with a true `0x124` size argument **and only then** calls
the real glyph canvas constructor. The preclear is not a guessed
static memset: the original physical `0x0040C080` is a full
**31B/14-i386** method whose actual E8 `+0x11` targets CRT `memset`
`0x00544760`, and it is already accepted under canonical unit
`hit_controller_auto_class_initialize` from a different original
receiver context. This is a **folded physical helper** and must
not be recounted as new exact bytes.

The complete 124B constructor is independently strict exact under
[`CORE/RECON-1047`](GLYPH_CANVAS_CONSTRUCTOR124_STRICT_EXACT.md)
with its own real `memset(0x124)`, distinct from the allocator's
preclear. The double-clear is **actually present in original native
code**, not an optimization to remove or an invented no-op; a
correct future allocator source must retain both calls and their
physical original order.

## Natural C++20 allocation trials, all NONEXACT

Under pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`, multiple bounded, real C++ allocation
expressions were compiled in ignored `.analysis/gptweb-cont-1048/`:

| Candidate C++ expression/ABI | Whole code result | Why it is not native exact |
| --- | ---: | --- |
| `new NativeCanvasAllocProbe()` with a `noexcept` constructor | **60B** | lacks original `__autoclassinit2` E8 and associated live state |
| Ordinary throwing constructor plus `new` | **122B** | adds SEH state and cookie not present in the original 73B wrapper |
| Genuine `::operator new` / preclear / legal placement-new construction | **83B** | contains an extra placement `operator new(size_t,void*)` call, absent in original physical E8 graph |
| Regular `new` followed by a genuine extra preclear call | **89B** | wrong native construction/zeroing order; extra code |
| Both class-tag and struct-tag variants | unchanged essential differences | changing only an isolated C++ class tag does not restore original compiler-generated preclear |

All trials preserve real allocation/call semantics; none manually
copies target bytes, changes the original compared range, injects
assembly, uses a forbidden direct C++ constructor invocation, or
pads a shortened function. In particular, the class/struct public
tag issue previously encountered by the 508B/511B Renderer list
Bosses cannot simply be assumed to explain the glyph allocator.

Read-only [`verify-glyph-canvas-allocator73-native.py`](../scripts/verify-glyph-canvas-allocator73-native.py)
SHA-pins all 73 original bytes and the complete 31B/124B child
bodies, proves all three original E8 destinations, the physical
0x124 size and absence of PE HIGHLOW within the wrapper, and
verifies the actual 2,227B original text Boss caller E8 `+0x89`.

**Status: SOURCE-ABSENT, NONEXACT** for original 73B allocator. The
31B class-preclear and 124B constructor have their *own previously
accepted exact* physical code heads. No new authored-game bytes
or strict unit are admitted by this evidence checkpoint. No
GDI/color header is modified and **no cold replay is necessary**
for an unchanged original reconstruction graph. The 681B bitmap
creation and 2,227B glyph text Bosses remain independent open work.

```sh
scripts/repo-python scripts/verify-glyph-canvas-allocator73-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```
