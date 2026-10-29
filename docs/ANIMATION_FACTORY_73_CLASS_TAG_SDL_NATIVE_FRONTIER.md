# CORE/RECON-685 — original 73-byte Animation allocation and MSVC class-tag `/sdl` zero-init code generation

**Superseded by [CORE/EXACT-696](ANIMATION_FACTORY_73_CLASS_TAG_STRICT_EXACT_RECONSTRUCTION.md): the coherent public class-tag migration, unique `/sdl` factory, 73/73B exact native strict acceptance and 492/492 affected-only old unit replay are now complete. The NONEXACT language below is the older 685 private-probe status, retained as historical evidence.**

**Status: the original `0x00447800` 73-byte Animation allocation method remains NONEXACT in the maintained project.** This investigation is a complete original-PE versus real pinned-MSVC whole-function compiler experiment, and isolates a concrete source/ABI blocker without changing the linked game target, creating a fake class layout, patching compiler output, or accepting structural similarity as strict exactness.

Original target: Japanese TH20 v1.00a Steamless `resources/th20.exe`, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## Native original physical body — all bytes and all three true calls

The original function `0x00447800..0x00447848` is **73 bytes / 22 whole x86 instructions**. It allocates `0x5E4` bytes for one real Animation object, checks allocation success, clears the complete allocated region, invokes the actual original Animation constructor, and returns the resulting pointer (or null). The original *physical* direct-call fields are independently decoded, not inferred by comparing a candidate's relocations:

| Original E8 immediate field | Original target | Independently identified role |
| --- | --- | --- |
| `+0x0F` | `0x0054275D` | Original CRT operator new, also anchored by previously strict-exact AnimationFile factory |
| `+0x28` | `0x0040C080` | Original 31-byte compiler-generated `__autoclassinit2` / memset-clear helper, also used by strict AnimationFile factory |
| `+0x30` | `0x00448B40` | Complete previously strict-exact 498-byte original Animation constructor |

The native helper itself at `0x0040C080` has **31 bytes**; its one real E8 calls the native `_memset` at `0x00544760`. This is not an additional game-authored byte interval to be claimed by the factory.

## Independently discovered compiler behavior

Under actual locked MSVC 19.44.35211 i386, natural `DiagnosticAllocator::allocate_object<Animation>` template instantiation of the genuine generic C++ `new T()` expression produces:

| Private compiler-only experiment | Complete body | Original ordered x86 | Relocation fields |
| --- | ---: | ---: | ---: |
| **`class Animation` final type declaration + `/sdl`** | **73B** | **22/22** | **3 REL32** |
| `class Animation` without `/sdl` | 60B | 19/22 | 2 REL32 |
| Maintained `struct Animation` + `/sdl` | 60B | 19/22 | 2 REL32 |

The private `class` variant is a **copy of the real existing `Animation.hpp` source with only the C++ tag changed**; layout, fields, method bodies, constructor, factory template, allocator and original game state are otherwise unmodified. No padding, dummy calls, manual zeroing, assembly, `volatile` trick, target patch, or header replacement was committed.

For that private whole 73B object, the independent comparator reports **61/61 original nonrelocated bytes** identical, with all **three original PE E8 positions/types and physical destination roles** matching exactly. The compiler emits the genuine MSVC helper symbol `Animation::__autoclassinit2(unsigned)` in an independent 31-byte COMDAT; it matches **27/27 nonrelocated bytes** of original helper `0x0040C080`, with its true `_memset` call field at the original position. This is strong original-codegen evidence: the previously missing 13 bytes and third E8 are explained by a native compiler rule that depends jointly on the **C++ class/struct tag and `/sdl`**.

## Why this is NOT an accepted exact 73B unit yet

MSVC uses the two different type tags to emit **different decorated class/template symbols**: the private factory is `??$allocate_object@VAnimation...`, whereas the currently maintained real `struct Animation` produces `??$allocate_object@UAnimation...`. A source-local forward `class Animation;` followed by the maintained `struct Animation { ... }` does **not** resolve the difference: the factory still emits the 60B struct version. Simply linking the private 73B test object against canonical callers compiled for the U-tag would not establish that all genuine game E8 call roles resolve to one real class and coherent constructor ABI.

The original PE's dynamic C++ type *spelling* is not independently proven merely by 73/73 structural code equality, and the historical linker ICF settings are unknown. Introducing an alternate duplicate Animation class definition in the maintained repository would also be invalid source ownership. The proper next step is to reconcile the **single canonical Animation declaration** and every affected consumer's real decorated symbol while protecting existing native-exact objects.

Pre-edit current pinned MSVC receipts establish that changing the actual shared `src/Animation.hpp` would affect **62 canonical source/COFF providers with 284 previously accepted exact native units**. Those are the precise potential replay scope, **not the whole project**. Do not make a global type-tag switch without first preparing a complete source/relocation symbol audit and verifying all 284 original intervals by affected-only strict replay. Even if all units pass, accept the 73B only after a maintained source and complete independently anchored canonical 73/73 strict comparison, not from this private experiment.

Reproducible private proofs:

- `.analysis/core685-animation-factory-compiler-tag-native-proof.py/json` — immutable original 73B/22 instructions, all three original E8 roles, 31B auto-helper and 61/61+27/27 bytes; independent comparable code and correct physical destinations.
- `.analysis/core681-class-Animation.hpp` and `.analysis/core681-class-Animation-factory.cpp` — only class-tag-changed private exact-shape source probe; `build/core681-probes/class-exactprofile.obj` and `class-nosdl.obj` — genuinely compiled pinned MSVC i386.
- `.analysis/core675-factory-Original.cpp`, `build/core678-probes/Animation-generic-gssdl.obj` — real maintained struct-tag template compiled under the same `/sdl` option.
- `.analysis/core682-forward-class-factory.cpp` — private controlled experiment showing that one opposite-tag forward declaration is insufficient; no public type declaration edited.
- `.analysis/core683-animation-class-conversion-existing-closure.json` — receipt-derived **62/284** previous native strict-unit impact boundary.

The existing complete **298-byte `AnimationPoolOwner::allocate_animation`** is independently game-owned strict exact and physically invokes the original 73-byte factory on its allocation branch. The 73B factory's independent original *callee identities* are now understood; its maintained source/link ownership and strict exact status remain open. **No previously accepted strict provider was changed and no cold or full replay was needed for this diagnostic-only checkpoint.** Accepted game-authored totals remain **503 complete functions / 179,538 disjoint original bytes**, with zero new original body credit for the 73B factory.
