# VCRuntime catch-object construction

Two complete MSVC 14.44.35207 x86 `libvcruntime.lib(frame.obj)` contributions
close two pending origins and recover six entries in the locked Japanese
TH20 Steamless target. All 472 instruction bytes, two terminal INT3 bytes,
two full SEH tables and the complete WinRT callback slot agree. The whole
474B code interval is `0x005468FF..0x00546AD8`.

| Entry | Instruction bytes | Role |
| --- | ---: | --- |
| `0x005468FF` | 285 | catch-object helper primary |
| `0x00546A1C` | 4 | helper exception filter, recovered |
| `0x00546A20` | 5 | helper exception handler, recovered |
| `0x00546A25` | 18 | helper return continuation, recovered |
| `0x00546A37` | 5 | helper abort path, recovered |
| `0x00546A3D` | 143 | catch-object constructor primary |
| `0x00546ACC` | 4 | constructor exception filter, recovered |
| `0x00546AD0` | 8 | constructor exception handler, recovered |

The helper's old 317B instruction extent is repartitioned across its complete
318B section, retaining INT3 at `0x00546A3C`. The constructor's existing
143B primary is unchanged; its missing filter/handler and INT3 at
`0x00546AD8` complete the 156B section.

## Destination selection and the WinRT callback

The helper returns zero before construction for ellipsis (null or empty
TypeDescriptor), or for a zero catch displacement without COM+ EH. The
COM+ flag is the sign bit of the full catch-adjective DWORD. That path uses
the passed registration pointer directly as the destination; ordinary x86
catches use registration+12+catch displacement.

The bad_alloc compatibility path separately tests low-byte catch flag 0x80,
catchable flag 0x10 and a nonnull WinRT OOM callback. The raw callback slot
at `0x005E52A0` is the complete four-byte loader-zero BSS definition from
`ehhelpers.obj`; installed `ehhelpers.cpp` initializes it to null. Its
stdcall no-argument pointer passes the existing guard check before invocation.
The returned exception pointer and destination must be nonnull or the
original verification aborts. The helper stores the pointer, applies the
catchable PMD adjustment and returns zero.

The COM+ sign-bit test and low-byte compatibility test have different widths
and roles. Neither may be replaced by testing whether the entire adjective
value is simply nonzero.

## References, simple copies and class construction

For a reference catch, the helper stores the thrown-object pointer and
adjusts it by the catchable PMD. For a simple type, it memmoves the specified
byte count to the catch destination. Only a four-byte copy with a nonnull
copied pointer then receives PMD adjustment at the destination.

For a class without a copy function, the helper instead adjusts the source
object first, then memmoves the full object size. For a class with a copy
function, it leaves construction to its caller: result one selects a normal
copy constructor and result two selects a virtual-base copy constructor
(catchable flag 4). These paths retain the original object/destination
verification and abort behavior.

The outer constructor computes the same catch destination and invokes the
complete helper. Result one calls the reviewed one-argument thiscall bridge
with the adjusted thrown object. Result two uses the two-argument bridge
and passes an additional integer **one**. The helper's discriminator two
is not the constructor's extra argument. Result zero and the default switch
path perform no member call. The outer function returns void.

The copy target `0x00543E20` is independently identified by the complete
unique 1,396B ordinary-byte signature of `memmove.obj`. Its own relocation,
table and protocol review remains pending, with no body credit here. The
existing AdjustPointer and member-call bridge proofs retain their complete
PMD and stdcall/thiscall contracts.

## Complete exceptional owners

The helper's 28B SEH table at `0x005AC1C0` has header `[-2,0,-48,0]` and
scope `[-2,0x00546A1C,0x00546A20]`. The constructor's 28B table at
`0x005AC1E0` has header `[-2,0,-40,0]` and scope
`[-2,0x00546ACC,0x00546AD0]`. Both filters unconditionally return
execute-handler one, covering structured exceptions in their active scopes.

The helper handler restores parent ESP and branches to its shared abort
path. The constructor handler restores ESP and directly calls the same
established abort. There is no recovering return from either handler.
Ghidra omits their ten filter/handler instructions; the retained supplemental
decode covers all 21 bytes, and the complete archive comparison checks their
call/branch roles and independent table labels.

The normal helper return continuation retains the original state reset and
FS-chain restoration. The constructor likewise resets its try state and
restores its chain after successful/no-op construction. The full metadata
closure is 56B of SEH plus four bytes of callback BSS; caller-supplied catch
and conversion tables receive no local ownership credit.

## Evidence and affected scope

Private `.analysis/origin-boundary/catch-build/` retains `review.py`,
`reviewed.json`, original rows and the full memmove identity member. It
reuses frame.obj and bounded attested `catch-build-native.txt` in
`type-info/`, plus ehhelpers.obj in `exception-lifetime/`. Every ordinary
byte, branch, REL32/DIR32 role, HIGHLOW field, complete SEH table and full
callback definition agrees. Installed `frame.cpp`, `ehhelpers.cpp`,
`ehhelpers.h` and `ehdata.h` corroborate the protocol and layouts.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new authored or maintained-source
exact credit.
