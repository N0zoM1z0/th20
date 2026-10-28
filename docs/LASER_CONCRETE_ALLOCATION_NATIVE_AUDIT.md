# CORE197: independent native factory and concrete Laser construction frontier

The complete game-authored `LaserController::create_laser` at `0x004D47F0`
has already been accepted as **474/474 native function bytes**, including its
18-byte compiler padding/jump-table tail (**492/492 bytes** and 21 original
relocations), under CORE/EXACT-195. CORE196 linked that genuine method and
the previously exact 75-byte registration into the *same full 41,967-byte*
Enemy source-draft host, passing **42,087/42,087** GCC UBSan and ASan+UBSan
semantic checks. **The entire Enemy boss machine code remains nonexact.**

This new checkpoint investigates the native bodies *beneath* those two exact
functions. It adds **no source or exact native credit**. All observations
below are independently decoded from the locked TH20 Japanese v1.00a
Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
not imported as assumptions from historical documentation or a reference
project. The structured nine-function audit, original function hashes and
call-site lists are protected at
`.analysis/core197-laser-factory-constructor-frontier.json`.

## Four complete factory wrappers and object sizes

All four `DiagnosticAllocator` member implementations are complete **92-byte
original functions** with the same actual control flow: call native
scalar `operator new` at `0x0054275D` with the concrete object size; if
nonnull, invoke the independent class-initialization helper at `0x0040C080`,
zero the exact allocated region with native `_memset` at `0x00544760`,
then invoke the corresponding *distinct concrete Laser constructor* and
return its pointer. An explicit null branch returns zero. These factories
are real, separate native functions; the declarations in maintained
`DiagnosticAllocator.hpp` remain unresolved interfaces, not placeholder
implementations.

| Game Laser family | Factory entry/bytes | Original allocation size | Actual derived constructor |
| --- | --- | --- | --- |
| Line | `0x004C8190`, 92B | `0x18F8` | `0x004C88E0`, 88B |
| Infinite | `0x004C8130`, 92B | `0x1338` | `0x004C8880`, 87B |
| Beam | `0x004C8080`, 92B | `0x1370` | `0x004C8410`, 159B |
| Curve | `0x004C8020`, 92B | `0x1D30` | `0x004C8390`, 122B |

Each allocation size is an immediate argument in the original factory, not
inferred from a guessed C++ class or a fabricated padding array. The four
constructor addresses are independently confirmed by their original call
sites from the corresponding wrapper. Their original vtable words are
`0x00571148` (Line), `0x005712E8` (Infinite), `0x00571214` (Beam) and
`0x00571374` (Curve), consistent with the separately decoded native
34-slot `Laser` virtual protocol. Exact source spellings of the derived
classes and allocator methods remain inferred.

## Actual derived subobject topology

Each constructor first calls the **same 522-byte real Laser base constructor
at `0x004C85B0`**, then replaces the base vtable pointer and constructs a
concrete native parameter object at `+0x6F8` relative to the true Laser
object. These fields correspond to the existing genuine `LaserType0/1/2/3`
parameter layouts, not anonymous raw bytes.

| Derived owner | Original members and independent native construction |
| --- | --- |
| Line | Type0 parameters at `+0x6F8`, then **three** genuine `Animation` subobjects at `+0x74C`, `+0xD30`, `+0x1314` |
| Infinite | Type1 parameters at `+0x6F8`, then **two** `Animation` subobjects at `+0x770`, `+0xD54` |
| Beam | Type2 parameters at `+0x6F8`, two `Animation` subobjects at `+0x754`, `+0xD38`, scalar stores at `+0x131C..0x132C`, and an independently constructed 64-byte object at `+0x1330` (original `0x004C82C0`) |
| Curve | Type3 parameters at `+0x6F8`, one `Animation` at `+0x748`, a scalar at `+0xD2C`, and **two exact 0x800-byte zeroed arrays** starting at `+0xD30` and `+0x1530` |

The native `Animation` constructor at `0x00448B40` is a genuine previously
accepted complete method, not a replacement stand-in. Its original size
and the immediate offsets make the Line/Infinite allocated extents and
Curve's `0x1D30` terminus independently understandable as real object
composition. The type-specific copy and resource/virtual-init lifetimes
remain nontrivial and cannot be replaced with inert padding merely to make
one wrapper match.

## Big unfinished dependency: Laser base constructor

The shared Laser base constructor at **`0x004C85B0`, 522 original bytes**
sets its actual vtable and intrusive link, constructs multiple typed Timers
and Vectors plus its 24-element `ExtendedCommand` array, initializes native
field sentinels, performs a complete zero-initialization pass over the
**0x6F8-byte** base, then applies its actual Timer assignment. This specific
ordering comes from independent native calls and stores, not a guessed
standard constructor policy.

To test the current typed layout without compromising accepted code, we
compiled a **private MSVC x86 probe** using a copy of the maintained Laser
declaration and an explicitly authored natural constructor candidate:
`.analysis/core197-LaserParameters.hpp` and
`.analysis/core197-laser-base-ctor-probe.cpp`. That candidate emits **538
COFF bytes**; the original complete Laser constructor is **522 bytes**,
and the positional structural comparison also differs. **No native exactness
is accepted** from this probe. Do not fix the gap by truncating the function,
inserting inert locals or fabricating opaque member padding. The proper work
is to reconcile actual native field types, initialization rules and the
complete original 522-byte constructor/EH chain before changing maintained
`LaserParameters.hpp`.

## Acceptance discipline and next steps

The four **92-byte native allocators** and all four derived constructors
(88/87/159/122 bytes), plus the **522-byte** base constructor, are
independently audited and **all still nonexact and source-unaccepted**.
CORE197 touched **only ignored private analysis/probe artifacts and this
focused evidence document**. No production header, native match-unit
manifest, original PE, or prior protected host proof was changed; the
**affected native cold-build/replay scope is therefore zero**, not an excuse
to run full replay. Conservative totals remain **222 confirmed authored
exact functions / 57,991 bytes / 1,008 strict units**. The prior CORE196
entire Enemy host still passes **42,087/42,087** source-draft scenarios; it
uses explicit fixture boundaries for these four concrete allocator bodies.

A high-value continuation is to recover the **522-byte Laser base owner
constructor and complete member type layout** first, then the four real
concrete derived constructors, with original vtables/`Animation` and
`LaserTypeNParameters` members. Those owners unlock the four 92-byte
factory wrappers without losing actual allocation, EH or lifetime effects.
The separate 41,967-byte original Enemy dispatcher remains a larger Boss
closure requiring native switch tables and EH after these dependencies.
