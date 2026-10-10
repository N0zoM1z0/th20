# Enemy State and ECL Manager script pipeline

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-080, 2026-10-08. Three complete contributions add 419 body/comparison bytes
on the locked Japanese Steamless target, using actual 752-byte EnemyState,
112-byte EclManager, 72-byte EclRuntime and 16-byte Timer owners.

| Contribution | Native address | Complete bytes | Source |
| --- | --- | ---: | --- |
| EclManager::tick | `0x0053E2B0` | 217 | `src/EclManagerTick.cpp` |
| EnemyState::advance_scripts | `0x004AB4C0` | 168 | `src/EnemyScriptAdvance.cpp` |
| Timer::step | `0x00456240` | 34 | `src/TimerStep.cpp` |

All use the locked MSVC x86 candidate with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
Complete COMDAT extents and every canonical relocation strictly match native
bytes. The frozen graph contains 597 units in 113 fresh objects and 104292
nonoverlapping comparison bytes. Origins remain 524 pending, 9 library and
64 authored functions /16948 bytes. Three complete reference associations close,
199 absorbed across all 6945 terminal implementation reviews. Original member
spelling and authored identity are still unknown.

## State progression and callback representation

Bit 26 gates the complete progression. An already-set bit returns zero without
movement, clock lookup, VM dispatch or callback. Otherwise the function sets it,
updates movements, reads the clock step from the actual Timer at +A8, advances
the entity's actual EclManager and invokes the optional callback. Every nonzero
movement, Manager or callback result becomes signed -1. The bit remains set on
both failure and success; the separate enclosing State tick clears it only after
its successful completion. This prevents callback reentry into progression.

Native +2E0 holds a four-byte callable word. Its indirect call supplies this
same State in ECX, takes no stack arguments and consumes the full EAX result.
The immutable table at `0x0056FE8C` contains null, `0x00488B80` and `0x00488E80`;
the two adjacent tables are null-only. The callable bodies independently use
State storage and return a full-width integer. Production represents +2E0 as
`int (EnemyState::*)()`, default-initialized to null. The locked compiler proves
its four-byte single-inheritance representation, offset +2E0, unchanged 752-byte
State layout and complete 168-byte invocation body. Native evidence establishes
the word/receiver/result protocol; the original C++ declaration is an inference,
not a recovered source identifier. Other neutral callback words remain unresolved.
No dummy fastcall argument or reinterpretation of a padded service facade is added.

## Manager traversal and retirement

Traversal starts at the real intrusive sentinel and saves its next pointer before
every VM tick. The first runtime is special: any nonzero result returns -1 before
current-runtime restoration. For later runtimes, any nonzero result destroys and
releases the current runtime, detaches its real link and releases that link.
Iteration then uses the saved next pointer. Successful completion restores
current_runtime to Manager.main and returns zero. Newly inserted nodes follow
this cached-next protocol rather than being automatically ticked immediately.

Typed node/next endpoints, whole detach and both 97-byte allocator release
instantiations also pass complete native comparisons. These five folded support
contributions add no duplicate exact credit. They use the shared maintained
intrusive and destruction-before-lock allocation protocols.

## Clock source boundary

The native getter selects `timer_clock_sources[(flags >> 1) & 3]` and converts the
pointed ClockScalar to float. It does not read current_fraction and does not
normalize mode. The independently checked pointer at `0x005AEFE0` targets the
real default scalar at `0x005AEFE4`; the next word is that scalar's 1.0f bits,
not another supplied clock pointer. Only mode 0 with a valid source pointer is
established. Nonzero modes are outside the supported lookup domain. The existing
one-slot declaration is retained; no fictitious four-entry array is introduced.

Movement runs before this lookup, so clock mutation by movement is observable.
Timer current/fraction fields and retained high flag bits are unaffected. The
34-byte native getter and all canonical global/method bindings are compared.

## Owned semantic verification

The O2/UBSan check executes the complete production EclRuntime tick, both new
Manager/State bodies, Timer getter, real ECL/State member lifetimes, actual PMR
containers and real typed destruction/release. Sixteen combinations cover every
three-child completion subset with primary success/failure. Two additional cases
use a distinct real primary object to distinguish early-failure context retention
from successful restoration to Manager.main. A two-frame spawn case proves
cached-next deferral while the real VM executes its spawn opcode.

Both owned PMR allocations in each failed runtime are observed retiring while
the link is still connected, before detachment. Thirty-six State combinations
cover preexisting gate, signed movement/callback failures and actual VM termination;
null callback and recursive actual member invocation have dedicated checks.
Movement changes the clock before lookup, with Timer fraction deliberately different.
Nine clock values include signed zero, negative values, infinities and NaN.

Explicit unresolved boundaries remain: loader instruction resolution, spawn
implementation, Enemy opcode root/movement/outer retirement and unused VM helper
routes. The process allocator startup is a fixture. The selected VM execution,
Manager traversal and State orchestration are production code; this check does
not accept full native loader/spawn/movement/Enemy runtime behavior.

## Whole State tick remains open

The complete private `0x004A8260` candidate still has a late missing NOP after
Pattern advancement, shifting subsequent Timer code. Natural void prefix
advancement and an in-class definition retain the complete 1280-byte extent and
180 canonical byte differences. No changed return ABI, inert NOP shaping,
shortened extent or partial credit is used. Candidate sources, exact header
versions, profiles and diagnostics are retained privately.

The 41 KB Enemy dispatcher, both complete variable readers, Player ownership,
full State tick and whole-game runtime remain open. Native exports are
core080-state-script-native.asm and core080-script-callbacks.asm; frozen replay,
support proofs and probe histories remain under ignored .analysis.

## Final verification and storage

All 51 public tests pass (133.069 seconds); target/tracking/reference/progress
gates pass. Protected cleanup retires 10 completed probe object/receipt products,
244614 bytes. Original receipts and 6 historical source/header versions are
losslessly preserved in compressed archives of 74399 and 5153 bytes; net savings
165062 bytes. All 226 current canonical product hashes and all native/failed
source evidence remain unchanged. Post-cleanup 597/597 strict replay uses existing
objects without a cold rebuild. Cumulative retired products: 2570 files /
1003225449 bytes; separate prior archival savings: 12865565 bytes. Analysis is
about 77 MiB and build 5.1 MiB; installed tools/game/reference remain protected.
Final source is frozen in core080-final-frozen-source.json; current complete proofs
are exact080-canonical-results.json.gz and core080-post-cleanup-results.json.gz.
One-time configuration/registration/cleanup writers are completed; never rerun.

