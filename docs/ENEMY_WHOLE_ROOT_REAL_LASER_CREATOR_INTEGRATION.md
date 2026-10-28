# CORE196: real 474-byte Laser creator in the entire Enemy opcode root

CORE/EXACT-195 already accepted the genuine complete native **474-byte**
`LaserController::create_laser` at `0x004D47F0`: exact code plus original
18-byte alignment/jump-table contribution (**492/492 full compared bytes**, all
**21 independently established relocations**), after **223/223** strict
old/new unit replays across the actual **33** affected MSVC x86 providers.
CORE/EXACT-194 separately accepted its full **75-byte**
`LaserController::register_laser` callee at `0x004C9300`.

This checkpoint **integrates those real maintained methods into the same
continuing 41,967-byte Enemy `execute_opcode()` complete-root source-draft
host**, rather than keeping their bodies as captured callbacks. No fake
stand-alone Enemy opcode fragment is introduced and no additional native
exactness credit is claimed for the large Enemy root. Its original entry
`0x0048C010`, switch partition and EH are still **not byte-exact**.

## Original creation chain and honest remaining boundaries

Native opcode **702** (original 682-byte branch) constructs a real
`LaserType0Parameters`; opcode **703** (original 787-byte branch) constructs a
real `LaserType1Parameters`. Both select the genuine `EnemyQueuedRecord` and
`ShotMetadata` pair through the still-nonexact queued COW selector, copy the
actual PMR BulletCommand vector into their own real parameter objects, and
lookup the *live* Context LaserController. Now the same whole-root host
passes the complete native parameter object to the **actual production
`LaserController::create_laser` C++** through a host-only interface adapter.
An old optional failure-injection hook remains solely to preserve earlier
CORE192 historical boundary scenarios. With the hook absent, the adapter
calls the unmodified accepted production method.

The creator checks the native **signed** count gate at 512 before changing
state; increments the handle and applies a signed floor at 0x10000 before
switching; selects four distinct real `DiagnosticAllocator` ABI members for
LaserLine/Infinite/Beam/Curve types; writes Laser+0x8C before the actual
virtual `initialize_laser(const void*)` invocation at vtable slot +0x14;
returns 0 for null factories or negative virtual initializer return values;
and uses the **production** 75-byte registration method only after successful
initialization. That registration initializes the actual Laser intrusive
link, prepends it to the controller's active list and only then increments the
native count. Unsupported types still preserve the advanced handle, as the
native original does.

The **four original type-specific 92-byte native allocation factories and
their actual concrete beam classes, constructors and virtual initialization
bodies are still undefined**. They are represented only by four explicit
private fixture implementations of the real `DiagnosticAllocator` interfaces
on this host, returning test-owned concrete Laser objects. These objects
participate in the real `Laser` vtable ABI and real list operations. No
production constructor/factory implementation, Stage/VM runtime or full
Laser lifetime is fabricated or accepted. The historical CORE192 reset host
is kept intact: a private copy changes only the previously unresolved slot-14
fixture override to match the now independently verified signed initializer
signature.

## Complete-root validation and scoped replay policy

The new `.analysis/core196-real-laser-factory-host-cases.inc` adds **1,146**
scenarios: **1,050 direct full native factory calls** and **96 original
Enemy opcode-702/703 calls that reach the real 474-byte creator**. Direct
checks span the signed count cap (including negative, 511, 512 and 513),
handle overflow and signed-floor behavior, all four supported and several
unsupported type indices, authentic source labels, missing factories,
negative virtual returns, allocator exceptions and virtual initializer
exceptions. **72 real registrations** are checked after both genuine
intrusive-list operations, along with 216 direct virtual initializer calls,
420 capacity-short-circuit cases, 270 unsupported-type cases, 72 each of
null factory, negative initializer, allocator-throw and initializer-throw
outcomes. The original 702/703 caller tests also verify queued COW ownership,
late Context re-selection, parameter lifetime and exception propagation
through the complete factory path; the captured four concrete factories are
never credited as native-exact implementations.

The full 84-translation-unit host passes **42,087 / 42,087** scenarios:
all **40,941** previous CORE192 cases plus **1,146** new genuine creator
scenarios under both GCC 13 `-O2 -Wall -Wextra -Werror` UBSan and
ASan+UBSan. The latter has leak detection enabled, excluding only
`vptr` instrumentation because unrelated unimplemented `WeaponStoneInfo`
key-function RTTI is absent from the fixture. Old source artifacts and their
SHA-bound proofs remain protected; we did not edit or delete historical
CORE192/CORE191/CORE188 sources or executable outputs.

The current inputs, recipe, full logs and binaries are:
`.analysis/core196-enemy-dispatch-candidate.cpp`,
`.analysis/core196-dispatch-host.cpp`,
`.analysis/core196-laser-reset-host-cases.inc`,
`.analysis/core196-real-laser-factory-host-cases.inc`,
`.analysis/core196-dispatch-host-recipe.json`,
`.analysis/core196-dispatch-host.log`,
`.analysis/core196-dispatch-host-asan.log`, and both
`build/core196-dispatch-host*` executables. All five private inputs,
production-method provenance, both binary hashes and successful log hashes
are recorded in `.analysis/core196-enemy-whole-root-proof.json`.

This CORE196 work modified **only ignored private whole-root test artifacts**,
not production files/headers or canonical match-unit profiles. The new
**affected native cold replay scope is therefore zero units**: CORE195's
separately attested **223/223** strict original native units are reused,
without rerunning the complete project or even the unrelated 33 original
MSVC source compiles. Current original Enemy source-draft semantic coverage
remains **130 effective opcode values / 98 native primary heads of 174**;
this is **not** a claim of compiled 41,967-byte original identity.

Next useful whole-system dependencies include the four 92-byte type-specific
Laser allocation wrappers, their real concrete constructors and derived
virtual initializers, other large Enemy cases, and the compiler EH/switch
structure of the 41,967-byte original dispatcher. See
[the native factory acceptance](LASER_CONTROLLER_CREATE_WHOLE_EXACT_RECONSTRUCTION.md)
for complete codegen proof and relocation targets.
