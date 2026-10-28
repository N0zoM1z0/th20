# CORE188: native queued-selector pair ABI and shared metadata ownership

This checkpoint corrects a result-type mistake in the continuing **entire
41,967-byte** Enemy dispatcher investigation. Neither the native COW selector
`0x00498B80` nor its ensure-only sibling `0x00498D10` returns a `shared_ptr`
by value. Each returns **two raw pointers** in an eight-byte aggregate. Their
internal `EnemyQueuedRecord::owner` is a genuine `shared_ptr<EtamaArgInf>`.
The provisional natural candidates and complete host are under ignored
`.analysis/core188-*` paths; no prematurely accepted native source was added.

## Independent target and ABI proof

The original target is the user-selected Japanese Steamless TH20 SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
All following ranges are complete native functions, without truncated tails:

| Entry | Native bytes | Independently observed role |
| --- | ---: | --- |
| `0x00498B80` | 396 | Indexed writable queued metadata, with copy-on-write |
| `0x00498D10` | 305 | Indexed queued metadata, ensure-only if null |
| `0x00467CC0` | 55 | Two-pointer pair construction, first at `+0`, second at `+4` |
| `0x0048B180` | 17 | Address of the first aggregate element |
| `0x0048B160` | 20 | Address of the second aggregate element |

The native `0x00467CC0` reads two pointer arguments through observed `move`
helpers and stores their values at output offsets `0` and `4`. Both queued
selectors call it at their complete return tails (`0x498CF3` and `0x498E28`).
The whole opcode 609–612 caller at `0x493210/0x49322E` retrieves the two
aggregate element addresses, then uses the first as the queue **record**
(for `record+0x30`) and the second as `ShotMetadata*` (for its command vector
at `+0x4`). This independent caller/return dataflow establishes the natural
ABI as `std::pair<EnemyQueuedRecord*, ShotMetadata*>`. The original source
spelling is inferred; the two-pointer result, sizes and x86 storage offsets
are direct observations. No reference repository's collapsed helper name is
being used as ABI evidence.

Original complete native function SHA-256 values:

- `0x00498B80`: `4e1f33ead2435656309f539da28892f31406753664656115accbbada9ea90ba4`
- `0x00498D10`: `0ef144cc989cf2703f11498f297562e408af056421daedcf31cc3a6b3af895d0`
- `0x00467CC0`: `a4d4d15f16bda62e38be5d1e6fcfa8e0bfc31e07953634b8e3acffab66a39d82`

The complete decoded function sizes, direct calls and independent original
hashes are protected in `.analysis/core188-queued-selector-native-audit.json`.

## Actual semantics established by producers and consumers

Both selectors compute a signed parameter's `index+1` in native x86, compare
it against the distance of the actual PMR forward list at `EnemyState+0x168`
with an **unsigned** bound, and resize the list when necessary. They then
advance an iterator to the indexed `EnemyQueuedRecord` and access its first
field, a genuine `shared_ptr<ShotMetadata>` with actual control-block RTTI.
Positive, in-bounds indices are the demonstrated semantic domain. Integer
wraparound, negative input and allocator exhaustion are not silently repaired.

The 396-byte writable selector checks for a missing owner or reference count
greater than one. A missing owner allocates a new `EtamaArgInf` using its
real, game-specific `DebugAllocator`. A shared owner allocates a *copy* of the
existing metadata and its PMR command vector, then replaces only the selected
record's owner. A unique nonnull owner is reused. In the 305-byte ensure-only
selector, an already nonnull owner is **never cloned**. Both construct the
same two-pointer result `{&record, record.owner.get()}` after these state
transitions. Original factory and shared-pointer swap/release callees are
independently observed; default/copy factory codegen remains a separate open
problem.

## Same complete-root integration and checks

The active entire Enemy root source draft is
`.analysis/core188-enemy-dispatch-candidate.cpp`. The single 609–612 case
now models the returned **pair ABI** and consumes `.second`, rather than
pretending that the native selector returns a `shared_ptr`. The host in
`.analysis/core188-dispatch-host.cpp` preserves the existing captured-boundary
fixture to replay previous caller observations and also executes two separate
natural C++ candidate selectors using actual `std::pmr::forward_list`,
`std::shared_ptr`, `DebugAllocator`, `std::allocate_shared`, `ShotMetadata`
and `BulletCommand` in newly added scenarios. That candidate is not a
machine-code-exact production source admission.

**631 additional real-owner scenarios** pass, comprising 144 deep COW copies,
288 first-time allocations, 144 unique-owner reuse situations, 144 real
forward-list growth situations, 192 real PMR command-vector expansions,
19 ensure-only selections and 36 thrown VM operand cases after the genuine
owner-selection step. Tests check record pointer and metadata pointer equality
with the new pair result, old shared owners' isolated command contents,
unchanged nonqueue Enemy state and earlier successful command writes.

The whole 81-translation-unit host now passes **40,492 / 40,492** scenarios:
all previous **39,861** plus the 631 new cases. GCC 13, `-O2`, `-Wall`,
`-Wextra`, `-Werror`, UBSan pass is recorded in
`.analysis/core188-dispatch-host.log`. An independent ASan+UBSan build
also passes in `.analysis/core188-dispatch-host-asan.log`, with leak detection
enabled and only `vptr` instrumentation excluded because the private fixture
does not link unrelated unimplemented `WeaponStoneInfo` key-function RTTI.
The `core188-enemy-whole-root-proof.json` captures hashes of five active
private source/recipe inputs, both binaries and both successful logs.
CORE187 and all earlier proof-bound artifacts remain protected, not reset.

## Exactness and next work

The **396-byte** writable selector, **305-byte** ensure-only selector and
**41,967-byte** whole Enemy root are **not MSVC machine-code exact**. Historical
candidate codegen showed substantive changes in allocator forwarding, EH and
temporary materialization. CORE188 verifies semantics and corrects ABI, but
has not solved those compiler differences. Authored exact totals and canonical
unit inventory therefore remain **219 functions / 57,291 bytes / 1,005 units**.
No production source, shared header, compiler profile, canonical object or
acceptance ledger changed: **zero** affected native cold-build/replay units;
only the complete-root GCC host was rebuilt. No full cold replay was run.

Continue with genuine native selector factory/copy/return emission and EH,
without fake temporaries or changing the shared ownership contract to match
a preferred compiler output. The real 151-byte
`EnemyController::animation_file` routing, native laser commands and the
remaining Enemy branch heads are also significant whole-root dependencies.
