# Animation callback owners and calling conventions

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-123 reconstructs the callback protocol used by the whole ANM VM.
Native evidence establishes the complete eight-byte callback base, its five
virtual slots, the two C callback signatures and the actual Bullet owner used
by one script callback. The 40,752-byte VM remains a whole, open reconstruction
objective. This batch does not claim a partial match for that function.

## Complete owners and native contracts

Native RTTI names the base `SprtFuncBaseInf` and a directly derived 72-byte
`EffectMenuWindowInf`. The base has a vptr followed by `Animation*` at +4.
Constructor `0x446B60`, destructor `0x446BA0`, deleting destructor `0x446BC0`, the
five-entry vtable `0x56E1AC` and native RTTI independently corroborate the eight-byte
owner. The derived hierarchy has exactly two base descriptors: itself and this
base. The reference hypothesis with a four-byte abstract base and a separate
eight-byte attached class does not explain that hierarchy.

Maintained source uses `th20::AnimationCallback` as its semantic name. Its
native layout and emitted slot table are verified; its different RTTI name is
explicitly outside exact admission. The derived owner, its drawing operation
and its natural constructor's exception contract remain unimplemented.

| Native virtual slot | Maintained operation | Native contract |
| --- | --- | --- |
| +00 | Virtual destruction | Deleting flags; sized scalar delete uses eight bytes |
| +04 | `update()` | int32 result; nonzero makes the VM retire the animation |
| +08 | `draw()` | int32 result; base returns zero |
| +0C | `slot_0c()` | Base returns int32 zero; concrete role unresolved |
| +10 | `interrupt(event)` | int32 argument and result; callee pops four bytes |

The three no-argument defaults fold to `0x412540`, already represented by a whole
canonical iterator unit. The one-argument default folds to `0x414B50`, already
represented by a whole canonical loader unit. Their complete 13/15-byte
emissions are independently replayed, without duplicate physical byte credit.

`Animation::set_callback` returns the incoming pointer after publishing +568.
`Animation::interrupt` first calls the virtual interrupt slot, discards its
result, then publishes the event at AnimationBase+438. A null callback still
publishes the event. Tests cover callbacks which change this field during the
call, so the observed ordering is checked rather than assumed.

## C callbacks and signed script selection

The VM has one call through +5DC and three through +5E0. Together with the
native setters and their producers, they establish these x86 default `__cdecl`
contracts:

```cpp
std::int32_t (*entry)(Animation*);
std::int32_t (*script)(Animation*, std::int32_t);
```

The caller removes four/eight argument bytes. The unary callback runs at VM entry
and its result participates in retirement; script results are signed selections.
Maintained +5DC/+5E0 storage and
setters now use these function pointer types. Zero reset remains null assignment.
The unary type is named `AnimationEntryCallback` after its observed execution
point. Native evidence does not establish a collision trigger.
No portable fixture fabricates an integer token as a callable pointer.

Native producers `0x48227D`/`0x47F315` publish `0x47D580`, whose complete 121-byte
callback reads the genuine 528-byte `Bullet` through `Animation::user_data`.
Signed 16-bit type/color getters at `0x485640`/`0x485720` sign-extend to 32 bits.
The callback checks
the signed view of `bullet_styles[type].colors[0].words[0]`. A negative sentinel
returns the incoming script unchanged, without reading color or indexing a
word. Otherwise it returns the selected unsigned word's signed 32-bit pattern.
The existing 158-byte style and 20-byte color records retain their original
unsigned storage declaration; one signed consumer does not rewrite the owner.
Native address `0x5C06AC` is colors at +4 within the independently anchored
array at `0x5C06A8`.

The nonnegative path retains the native unchecked domains type 0..49,
color 0..15 and script 0..4. The negative path permits any int32 script and
does not require a valid color index. Ghidra omitted an internal two-byte JMP
at `0x47D5F0`; complete PE control-flow review and the compiler comparison retain it.

Other producers publish `0x4CF550`/`0x4CF5C0` with a different user-data owner, or
single-argument lambda adapters `0x4AC290`/`0x531050`. Their complete native contracts
and bodies are recorded privately. Those concrete owners and lambda emission
remain open; they receive no source or exact credit in this batch.

## Real virtual retirement

Animation resource cleanup now uses the existing shared
`DiagnosticAllocator::release_object<T>` body for the complete callback type.
It returns immediately for null, runs `std::destroy_at` before taking lock 1,
then performs scalar storage release under that lock. The full 97-byte callback
instantiation folds to the already canonical Bomb instantiation at `0x41F7C0`.
The complete 27-byte virtual destroy helper at `0x41F880` is newly represented
physically.
The constructor, resource and lock startup boundaries remain explicit fixtures.
Existing independently anchored CRT/STL callees are not newly reconstructed.

Tests exercise actual virtual destruction rather than an opaque callback token.
At destruction they observe cleared geometry, the still-published callback,
the original handle and instruction offset. A second thread can acquire lock 1
during destruction, corroborating destruction outside the storage-release lock.
After cleanup, callback/handle are null/zero and the instruction offset is -1.

## Compiler, exact and semantic gates

The private batch passes nine new whole physical roots (414 bytes) and five folded
aliases (151 bytes). An independent full 20-byte vtable replay corroborates the slot
contract but is not an admitted data unit. Its COFF weak vector-deleting spelling
falls back to the independently verified 46-byte scalar deleting body. Complete
native RTTI parsing establishes the original hierarchy; it is not inferred from
the constructor relocation under comparison.

The natural typed setters and shared virtual-release migration independently
preserve all 18 affected whole Animation/Binding units (3,360 bytes). Maintained
semantic fixtures pass 149,903 cases under O2, ASan, UBSan and float-cast-overflow:
all 65,536 signed 16-bit getter representations, every valid type/color/word selection,
signed result bits, negative-sentinel bypass, full-width events, virtual dispatch,
field publication order, null handling and real resource retirement.

Production root/support replay passes the frozen 276-source graph, 827 complete
strict units, 160 fresh objects and 160,921 disjoint comparison bytes. Maintained
production 149,903-case semantics and all 79 public tests pass. Authorship,
original global initialization,
gameplay execution and native RTTI identity are separate acceptance boundaries.
