# CORE/EXACT-358 — complete 271-byte EffectInfo deferred-effects frame boss

Original comparison target: immutable Japanese TH20 v1.00a Steamless
executable, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire original game-owned EffectInfo request processing method at
`0x0049D4A0..0x0049D5AE` is **271 native bytes, 90 x86 instructions**,
original full-interval SHA-256
`e262d89c9cdb830a08a496ebda99b59a3b1b2c8d88ea81ecddd934ed092ff01a`.
It is now strict native exact as `EffectInfo::process_queued_effects` in
the same maintained `src/EffectQueue.cpp` owner as the independently
accepted 143-byte `EffectInfo::queue_effect` producer. Its original
method spelling is inferred; the real typed receiver, complete control
flow and native return ABI are independently observed.

## Two entire 1024-slot gameplay loops

The method begins by selecting the real Renderer view at
`EffectInfo+0x1303C` through the original global Renderer pointer
`0x005C0028`. It then scans **all 1024 four-byte
`EffectAnimationHandle` entries** at `EffectInfo+0x3C`, invoking the real
`AnimationHandle::resolve()` on each. An unresolved handle is cleared via
the *native* `AnimationHandle::operator=(0)` member. This is **not** a
raw store to a fabricated owner; the complete original array getter and
setter calls remain observable.

The second loop obtains the first of **1024 `EffectRequest` records**, at
`EffectInfo+0x103C`, each of actual 72-byte stride. Records with a
negative `type` are skipped. For active requests, `delay > 0` is
counted down by one, while `delay <= 0` invokes the actual
`EffectInfo::spawn_effect(type,parameters,policy)` operation via its
original hidden `AnimationHandle` result and real C++ member ABI.
After submitting the effect, it sets `type = -1` to mark the request free.
This branch reads exactly the record's `policy` at `+0x8`, `delay` at
`+0xC`, and its 56-byte `EffectParameters` value at `+0x10`, corroborating
**independently** the type correction from CORE/EXACT-352. The complete
frame method then returns the native integer constant **1**.

Initial full C++ compilation emitted 279 bytes and 92 instructions.
Two authentic, more direct source expressions closed the difference:
`handles[i].handle.resolve()` avoids an unrelated reference spill, and
`handles[i].handle = 0` restores native right-hand-side argument evaluation
*before* the array indexing call. Using the actual `delay <= 0` condition
also restores the native `jg` branch rather than a value-one `jge` check.
The resulting source emits **271/271 original bytes, 90/90 original
instructions**, complete loops and true C++ member semantics, without
manual NOPs, assembly, inert locals, copy-pasted machine bytes or a
shortened comparison range.

## Independent complete original relocation evidence

A fresh original x86 disassembly and the unmodified PE's `.reloc` table
attest **seven `E8 / REL32` call fields and one `HIGHLOW / DIR32` absolute
field**, at these original offsets:

| Native field offset | Original destination | Role |
| --- | --- | --- |
| `+0x15` DIR32 | `0x005C0028` | Renderer owner global |
| `+0x1A` REL32 | `0x004776A0` | select view |
| `+0x4B` REL32 | `0x00414580` | first indexed animation handle |
| `+0x52` REL32 | `0x0044CED0` | resolve animation handle |
| `+0x6D` REL32 | `0x00414580` | second indexed animation handle |
| `+0x74` REL32 | `0x004117A0` | assign zero handle |
| `+0x8D` REL32 | `0x00449490` | first request array element |
| `+0xDC` REL32 | `0x0049DB70` | hidden-result effect spawning |

Every original reference location/type/target was established
**before** canonical acceptance and matches the exact corresponding
COFF function relocation and native target. Private full attestation is
`.analysis/core357-effect-frame-original-relocations.json`.
The final strict whole-body oracle reports **271/271 exact bytes** under
the pinned MSVC 19.44.35211 i386 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` source profile.

## Scoped replay and remaining independent roots

Only the real `src/ItemResourceOwners.hpp` gained a typed
`EffectInfo::process_queued_effects()` method; the implementation lives
beside the earlier accepted 143-byte queue producer in the **same**
existing canonical provider `build/core352-canonical/EffectQueue.obj`.
The **previous exact receipt include closure** identifies eight affected
providers containing **25 old strict units**; adding the new 271-byte
method yields **26/26 strict units across eight cold objects**.
Two serialized low-priority scoped batches of **5 + 21** strict units
pass. Three compiler-private MSVC `$SG` identities in two older sources
were renumbered; the original string destinations, relative fields,
locked receipts, full non-relocation bytes and independently observed
native offsets were checked before changing only local private symbol
names. The unchanged strict comparator re-accepted all these functions.
Details: `.analysis/core358-effect-frame-header-impact.json`,
`.analysis/core358-replay-groups.json`,
`.analysis/core358-replay-batch{0,1}.log`, and
`.analysis/core358-reconciled-private-symbols.json`.

The separate original `EffectInfo::spawn_effect` at `0x0049DB70` is
**227 bytes and remains independently open**. Neither its implementation
nor the broader EffectInfo construction, renderer lifecycle or whole
game executable linkage is made exact by this 271-byte frame. No
unfiltered all-repository cold replay was performed.
