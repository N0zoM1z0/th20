# Native SoundInf positional sound requests (CORE/EXACT-167)

This investigation uses only the locked Japanese TH20 v1.00a Steamless PE32
(SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
The previously declared but unimplemented real member
`SoundInf::request_effect_at(int id, float x)` corresponds to the complete
**52-byte** native entry `0x00426EB0`. It is neither a standalone sound queue
nor a provisional invented service facade.

## Actual large-root caller and signal protocol

The complete native Enemy dispatcher contains opcode **516** at `0x00493F3F`.
It gets `state.position_ref()` and stores **X** before reading the integer
argument at index zero. Then it calls the real global `SoundInf` at
`0x005BA830` with that identifier and saved X coordinate. Thus an operand
read that mutates the Enemy's position cannot retroactively change the
already-captured coordinate. The same genuine member is independently used
by the complete Enemy defeat call sequence. The dispatcher is still one
41,967-byte root, not an already reconstructed collection of fragment units.

The callee multiplies binary32 X by `1000.0f`, divides by `192.0f`,
truncates toward zero to signed 32 bits, and forwards `(id, pan)` to its
actual `SoundInf::request_effect(int,int)` member at `0x00426D70`.
No unobserved clamping, integer rounding, global sound-state mutation, or
extra input read is inserted. Floating-point overflow and NaN conversion
remain outside the exercised C++ fixture domain; native x86 `cvttss2si`
conversion of invalid values is a separate open edge case.

Under pinned MSVC 19.44.35211 x86 C++20 `/Od /Ob0 /GS- /Gy /Zl
/arch:SSE2 /fp:precise /Gd`, natural source
`request_effect(id, static_cast<int>((x * 1000.0f) / 192.0f))` emits
**all 52 native bytes**. Three independent relocations identify the exact
`1000.0f` pool literal at `0x0056CDB0`, `192.0f` at `0x0056E050`, and
`SoundInf::request_effect` at `0x00426D70`. Each destination was already
established by other accepted source units, not by fitting the current
comparison fields. Four natural syntax variants were tested: only the
single inline expression matches the complete function; explicit float or
integer intermediates emit 60 or 66 bytes. The original argument and return
ABI, entire native comparison extent, and all three fields match.

## Scope, regression and provenance

The implementation is placed in the existing `src/SoundEffects.cpp` translation
unit with its actual `SoundInf` class. No new production header, global,
product-specific fake owner, or source/probe path is created. The authentic
original include receipts select exactly **one affected object** and three
previously exact SoundEffects constructor units. A fresh pinned object at
`build/core167-canonical/SoundEffects.obj` replays the three old units and
new `sound_effect_request_at` unit **4/4**. The other 163 canonical provider
objects reuse their valid recorded inputs and compiler receipts. The earlier
SoundEffects object and receipt retain their protected SHA-256.

The SoundLoading owner test now directly exercises the production pan adapter
against 13 signed spatial samples times four IDs (**52 calls**), preserving
receiver, complete ID, signed truncation and lack of side effects in its
captured downstream request. It additionally retains its original **140**
loading, notification, resource and error scenarios. The actual SoundInf
request queue is still an explicit fixture boundary. Test-only function-section
linking drops unrelated uncalled AnimationHandle methods, rather than
inventing functional definitions for the still-missing global animation
backend; the tested sound adapter itself is live and executed.

Private reproducibility artifacts are
`.analysis/core167-sound-scope.json`,
`core167-sound-final-proof.json` and the four scoped compiler syntax probes.
These are independent of code-only source commits and never replace the
original file or entire-game runtime with a private stub.

## Open boundaries

The true `SoundInf::request_effect` queue, process sound startup, the whole
Enemy opcode dispatcher (including 502/503 animation-flag traversal), and
the complete Animation VM/resource renderer are **not** accepted as exact
here. This checkpoint admits one 52-byte native member and documents one
real large-root constituent path, with **no** partial dispatch coverage.
