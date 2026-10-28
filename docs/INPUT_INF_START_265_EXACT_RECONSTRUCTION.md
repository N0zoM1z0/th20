# CORE/EXACT-484 — entire 265-byte native InputInf start/configuration boss

Comparison original: immutable Japanese TH20 v1.00a Steamless
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The actual game-owned `InputInf::start()` at `0x00420990`
is now **265/265 original machine-code bytes, all 75 complete
i386 instructions strictly exact** under the genuine MSVC 19.44
x86 C++20 `/Od /Ob0 /GS- /fp:precise` source profile.
The complete original function SHA-256 is
`66e51a2efcb94a02d0dce52b58bf39c5e0d964189d449e06c013d3b0e1deb17f`.

The ordinary typed gameplay C++ lives in new
`src/InputInfStart.cpp`, on the independently original
RTTI-attested `InputInf` class in `src/InputInf.hpp`.
It adds **one complete game-authored function / 265 new
physically unique original bytes**. It does not credit
its still-nonexact child.

## Complete native initialization and true resource owner

The original first prints the genuine `start InputInf`
diagnostic and clears the real `InputInf+0x10` state flag.
It copies **two genuine 48-byte `InputBindings` records**
from the actual global graphics configuration into the
existing input manager's four-record bindings C-array
at `InputInf+0x2E38` (stride `0x30`).
Each InputBindings record has three independently
authored and typed 16-byte members: `pad`,
`alternate_pad` and `keyboard`, with their
original native MSVC record layouts.

The original machine code does **not** copy one 48-byte
InputBindings aggregate with `rep movsd`. Each loop
iteration copies `pad`, then `alternate_pad`, then
`keyboard` separately using **four complete 32-bit
loads/stores per true 16-byte subrecord**. Natural
`bindings[i].pad = ...pad` and corresponding
`alternate_pad` and `keyboard` assignments
produce all **75 original instructions**. A previous
whole-aggregate C++ assignment generated a 157-byte
candidate and was explicitly rejected. An alternate
C++ alias/reference form produced a different register
evaluation order and was rejected.

The source's true graphics owner is
`process_graphics` at original PE global
`0x005C4D40`, with already established
`Graphics::configuration` offset `+0x1C8`
and `Configuration::bindings` offset `+8`.
Consequently the original three absolute
configuration references are at
`0x005C4F10`, `0x005C4F20` and
`0x005C4F30`. These are **one Graphics
symbol plus three authentic COFF addends**,
not three invented unrelated globals.

After copying, the original calls its separate
`InputInf::initialize_devices()` at
`0x00420D80` (**465B, still NONEXACT**),
then writes **four genuine
`InputButtonState*` pointers** into original
global index table `0x005B889C`, taken
from the actual four 0x2C0-byte
`InputButtonState` objects at `0x005B88B0`
and successive 0x2C0 strides. It then
returns integer zero. The original true
`InputInf::for_view` at `0x00498FB0`,
called from the 3,111B Player main frame,
continues to access the separately authenticated
two-entry input view table inside the InputInf
instance at +0x2E30. Do not conflate that
instance-owned table with the original process
global `0x005B889C` just published by start.

## Complete original PE E8/HIGHLOW fields

The independently decoded entire original has
**two E8/REL32 calls and six genuine PE
HIGHLOW/DIR32 relocation fields**:

| Original field | Native type | Original target | Canonical symbol interpretation |
| --- | --- | --- | --- |
| `+0x0A` | DIR32 | `0x0056D674` | original `start InputInf` diagnostic literal |
| `+0x0F` | REL32 | `0x0040C6B0` | previously exact diagnostic function |
| `+0x42` | DIR32 | `0x005C4F10` | real `process_graphics` base +`0x1D0` |
| `+0x6F` | DIR32 | `0x005C4F20` | same `process_graphics` base +`0x1E0` |
| `+0x9D` | DIR32 | `0x005C4F30` | same `process_graphics` base +`0x1F0` |
| `+0xCE` | REL32 | `0x00420D80` | separate **nonexact 465B** device initializer |
| `+0xF3` | DIR32 | `0x005B88B0` | actual four native 0x2C0 ButtonState objects |
| `+0xFD` | DIR32 | `0x005B889C` | actual four process input view pointers |

All **eight offsets, types, immutable PE destinations,
true original C++ compiler symbols and genuine
relocation addends** agree. The manifest records
`process_graphics` **base `0x005C4D40`**
with the actual emitted source COFF addends
464/480/496 decimal, not the three already-offset
original physical field values as independent
symbol base targets.

The original immutable `.text` and `.reloc`
were independently decoded *before* accepting
the compiled result. The unchanged strict
comparator accepts **233/233 nonrelocated
original bytes and all 32/32 original relocated
bytes**, totaling **265/265 complete exact
native bytes**. The independent original
PE SHA, all eight native fields and true
compiler addends are in
`.analysis/core484-inputinf-start-independent-original-pe-proof.json`.

## Real header-receipt-only regression

The only existing shared-header change adds
the actual `InputInf::start()` declaration
and the declaration of the independent
still-open `initialize_devices()` callee
to `src/InputInf.hpp`. The complete natural
native start function is in **one new
source/object provider**,
`build/core484-canonical/InputInfStart.obj`,
without changing Graphics.hpp, Configuration.hpp,
InputState.hpp or their other source owners.

Before editing, the actual pinned canonical
compiler receipt include graph for
`InputInf.hpp` contained exactly
**three previous source providers / ten
whole strict native units**:
`src/InputInf.cpp`, `src/InputInfConstruction.cpp`
and `src/InputInfShutdown.cpp`.
The new whole start function raises this
to **11/11 native strict units in four
freshly cold-built source objects**,
replayed serially at low priority, without
a global unfiltered cold replay.
The previous 261B exact constructor
(including five true original CC bytes),
120B exact destructor, 49B compiler-created
deleting wrapper, 466B exact COM shutdown,
50B interface release, 26B input view
accessor and four additional 49/27/26/26B
native members all remain unchanged
full-body exact.

Adding the method declaration caused only
five diagnostic-string MSVC-private `$SG`
symbol number changes in the already exact
InputInf constructor/destructor/shutdown.
Each was separately compared against the
**independent immutable original PE string
destination, relocation offset/type and
complete unchanged nonrelocation bytes**:
`.analysis/core484-original-private-compiler-label-reconciliation.json`
and
`.analysis/core484-shutdown-original-pe-private-symbol-renumber.json`.
Only private compiler spelling changed;
**no original physical target address
or comparison extent was rewritten**.

Original pre-edit compiler receipt scope:
`.analysis/core484-start-preedit-source-receipt-closure.json`;
the successful exact replay of all eleven
original units:
`.analysis/core484-inputinf-start-all-exact-replay.log`.

The original **465-byte InputInf::initialize_devices**
at `0x00420D80`, original **3,490-byte
InputDevice frame processor** at `0x00421B00`,
555-byte Player motion and 3,111-byte
Player main-frame are separately
**NONEXACT**. The exact 265B start
does not prove their code or linked
whole-game runtime.


## Subsequent CORE/EXACT-487 — entire 465B device initialization callee closed

**Current status:** this document's earlier statement that the
direct `InputInf::initialize_devices` callee at `0x00420D80`
remains NONEXACT is historical and superseded. Its **entire
465B / 118 original i386 instructions** are now
**465/465 strict native exact** with all **nine immutable E8
and six original PE HIGHLOW references** independently checked.
Native signed device-count comparisons and a true two-DWORD
`ConfigurationCounterPair::values[2]` layout naturally reproduce
the original code, including two original Graphics base
`+0x230` COFF addends. The actual old
`Configuration.hpp` and `InputInf.hpp` compiler receipt
source closure was **17 old sources / 60 strict units**;
adding a single source provider for the original 465B
callee gives **61/61 strict native exact units in 18
low-priority cold objects**, with no full graph replay.
The further 726B DirectInput and 170B XInput discovery
callees, plus the 3,490B InputDevice frame processing,
remain separately NONEXACT. See
[whole original 465B InputInf discovery/route initialization proof](INPUT_INF_INITIALIZE_DEVICES_465_EXACT_RECONSTRUCTION.md).
