# CORE/RECON-966 — original 2,884B particle Update Boss temporary Ghidra recovery and *NONEXACT* whole C++20 research source

**2026-11-11 continuation:** The entire large Boss now has maintained,
source-present C++ in
[`src/AnimationParticleGridUpdate2884.cpp`](../src/AnimationParticleGridUpdate2884.cpp),
with corrected Session/EffectInfo/AnimationFile/spawn owners, actual Timer
and Animation accessors, and real integer stages. Its complete current
compiler output is **2,969B/763 instructions**, versus original
2,884B/768: **still NONEXACT**. The source-present ledger and full
corroboration are in the
[new exact-owner source frontier](ANIMATION_PARTICLE_GRID_UPDATE_2884_TYPED_OWNER_SOURCE_FRONTIER.md).
The historical 2,953B experiments recorded below remain dated evidence,
not the current maintained compiler result.

This documents a **real but unaccepted** advance on TH20's complete
original `0x0045C360` polymorphic particle-grid Update Boss, whose
full native **2,884B/768-i386** extent, sole `ret`, vtable slot and
**99 original E8 /25 PE HIGHLOW** were independently established in
[CORE/RECON-953](ANIMATION_PARTICLE_GRID_UPDATE_2884_ORIGINAL_NATIVE_FRONTIER.md).
The target remains the same immutable Japanese TH20 v1.00a Steamless PE
with SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Canonical status: SOURCE ABSENT / NONEXACT.** The entire C++ research
source lives under `probes/`, not `src/`; no function/implemented/matches
ledger row, match unit, authored-game byte credit or replay receipt is
claimed for the 2,884B parent. Nearness of size and matching numbers
of relocation *fields* are **not codegen exactness**.

## Fixing a real Ghidra missed-function boundary without changing the database

The pinned Ghidra database has **no function at original `0x0045C360`**,
despite the original vtable pointer and uninterrupted 2,884B original
code. A normal function-context/decompile request fails with `no
function at 0045c360`; repeating a source-absent Ghidra inventory
cannot reveal its true control flow.

[`scripts/ghidra/RecoverParticleUpdate.java`](../scripts/ghidra/RecoverParticleUpdate.java)
is a purpose-built **ephemeral** headless script. It verifies the actual
2,884 source PE bytes directly against original body SHA-256
`0d8c82a2018031e59c5e7172e08318e133f3513b6fc4639a1bab506c41eb02d1`,
checks the following twelve original `INT3`, starts one Ghidra program
transaction, disassembles the verified entry and creates a temporary
function spanning **exactly** `0x0045C360..0x0045CEA3`, then invokes
the real decompiler. It always finishes by **rolling the transaction
back** and does not modify the executable, original game bytes or the
persistent Ghidra project. The pinned Ghidra launch is `-readOnly
-noanalysis` and also runs the repository's independent `VerifyTarget`
SHA-256 and mapped-text checks. This recovered a **13,411-byte /373-line**
original decompiler hypothesis at the ignored path
`.analysis/gptweb-particle2884-decomp/recovered.c`.

The decompiler output is **provisional**, not native code truth. Its
original `this` appears as an uninitialized stack variable because
no original signature was available; source reconstruction instead
uses the independently verified `NativeParticleGridGroup` polymorphic
class and its real `AnimationCallback` base, not this spurious local.

## Compiled entire C++ function: substantial progress, still not exact

[`src/AnimationParticleGridUpdate2884.cpp`](../src/AnimationParticleGridUpdate2884.cpp)
contains a maintained **whole-function** natural C++20 experiment on
one real `NativeParticleGridGroup::update()`. This is *not* a handwritten
machine-code blob, original PE patch, compile-time fake padding or
source accepted as exact. It recovers the actual source-level stages:

- Original `Animation::vector_5bc` center, three owner Vector3 members
  at group `+0x1908/+0x1914/+0x1920`, original two polar offsets and
  native Timer gate.
- Four **independent**, original-bound Animation spawning calls (three
  script `0x95`, one `0x96`), true `AnimationHandle` indexed slots, four
  palette/position source calls and independently four child-color plus
  `Animation::variables()` copy branches.
- True fourth-particle color transform: bytes **red, green and blue**
  each become `uint8_t(300 - channel)` before publication (alpha is
  not part of the original transform). A four-byte union with named
  channels produces stack-byte operations, rather than a bogus
  indexed-byte pointer loop.
- The actual **200-element** update, native game RNG
  `0x005BA4C4`, two already exact 202B `Vector3` normalizations,
  two separately exact 57B interpolation calls and the original
  integer stage transitions `0 -> 1 -> 2` at group `+0x15E8`.
- Original `0x1930` Timer advance only when an active animation was
  processed, else original negative return.

The pinned compiler is MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`. Actual experimental progression:

| Whole-function source trial | Actual emitted bytes/i386 instructions | Original mnemonic subsequence alignment | Relocation fields |
| --- | --- | --- | --- |
| First typed source | **2,297B /589** | 543 of original 768 | 66 REL32 /26 DIR32 |
| Four physical spawn/child sequences and original 4-byte indexing | **2,846B /740** | 679/768 | 94 REL32 /29 DIR32 |
| Correct native `Animation::variables()` twice per child, fourth owner color getter, integer stage bytes | **2,911B /752** | 699/768 | **99 REL32 /25 DIR32** |
| Real fourth-emitter color inversion, direct named byte channels | **2,987B /772** | 733/768 | **99 REL32 /25 DIR32** |
| Source-owned four-byte union of color word/byte channels, no unnecessary indexed-pointer temporaries | **2,953B /764** | **735/768** | **99 REL32 /25 DIR32** |
| **Immutable target** | **2,884B /768** | 768/768 is required | **99 native E8 /25 physical HIGHLOW** |

The latest complete experiment has **the same number of calls and data
fields** as the original, but it is **69 bytes longer and four
instructions shorter**, and their exact instruction order, original
addresses, call targets and stack local layout remain different.
The source does **not** satisfy a canonical strict replay and must not
enter the original authored exact accounting.

**2026-11-11 resolved type frontier:** The original 2,884B Update's
`+0x15E8` stage transitions are integers `0 -> 1 -> 2`, not floats.
The shared `NativeParticleGridGroup` now declares exactly **200
`std::int32_t` stage words** at this original offset, and its 172B
constructor initializes the typed array to zero. The original ctor's
800B `memset` did not distinguish float and integer values, so this
type correction relies on the independently attested Update instruction
reads and comparisons.

Canonical compiler receipts identified **eight exact units in six affected
object providers**. All six objects were rebuilt under the locked MSVC
profile and **8/8 affected strict units remain exact**, covering the
172B constructor, 49B deleting wrapper, 156B factory, 47B create,
31B config, 92B stop and both 200-element array constructors. The
research-only 2,884B Update still compiles as **2,953B/764 instructions,
99 REL32/25 DIR32**. **Further 2026-11-11 index-ownership closure:** After the correct integer
stage declaration was in place, the research source's thirteen remaining
4-byte indexing calls were rewritten from an old `Vector3` cast into
**nine natural `colors_08[index]` or `colors_08[emission_index+n]`
`AnimationHandle` accesses** and **four natural `stages_15e8[index]`
integer accesses**. The same correction was made in the independently
strict 92B Stop sibling. The entire 2,953B/764-instruction C++ candidate
is **byte-for-byte unchanged**, with the same 99 REL32/25 DIR32 field
sites; the only relevant relocation changes are true C++ template
symbol identities. Both `std::array` four-byte element accessor
instantiations emit the full **22/22** original folded leaf at
`0x00414580`, already canonically covered by `vector3_index` and not
recredited. The 92B Stop strict replay passes **92/92** with its
updated array symbol and unmodified physical E8 destination. These
changes remove invalid 12-byte `Vector3` aliasing without changing
gameplay semantics or claiming new exact parent credit. The other
file/palette member names and original 2,884B ABI remain unresolved. No parent-body exactness
is claimed and no unrelated provider was rebuilt.

Some `0x00437520` effect-file, `0x0045D100` palette/file, and
`0x0045D0A0` animation Timer accessor source names/signatures in the
candidate remain **hypotheses**. Their actual **physical original
E8 targets** are frozen separately by the original-only verifier and
must be proven before a full source implementation is accepted.

## Fast reproducible experiment and hard admission boundary

[`scripts/probe-animation-particle-grid-update2884.py`](../scripts/probe-animation-particle-grid-update2884.py)
first runs the immutable PE hash/call/data verifier, cold-compiles
**only the one research source**, reads its complete COFF function and
reports its original-boundary and relocation-count gap. It does not
run a whole graph cold replay, nominate a canonical match or generate
any game-authored byte credit:

```bash
scripts/repo-python scripts/probe-animation-particle-grid-update2884.py
scripts/repo-python scripts/verify-animation-particle-grid-update2884-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

A fresh ignored decompilation can be regenerated through the pinned
`scripts/ghidra.py` SHA-attested Ghidra runner and the temporary
`RecoverParticleUpdate.java` post-script. This requires an installed,
hash-attested local Ghidra project, but still never modifies the target.
The existing 92B virtual stop, 202B normalize, 83B spawn, 57B
interpolation wrapper and their independently exact callees remain
unchanged; they are not recredited as progress on the 2,884B parent.
