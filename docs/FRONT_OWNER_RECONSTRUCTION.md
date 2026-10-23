# FrontInf owner and Enemy HUD callers

## CORE/EXACT-159 acceptance

The maintained HUD module now declares the complete 0x2D8-byte FrontInf owner,
its real TaskInfo base, 0x54-byte boss panels and four-byte flags. The complete
883-byte constructor and nine other physical functions strictly replay from
natural C++. Ten new units compare 1,647 bytes, retaining all 25 compiler-emitted
trailing INT3 bytes. A separate 151-byte complete EH code/data proof establishes
constructor cleanup and shared noexcept support without adding those bytes to
the canonical progress total.

Only the FrontInf constructor receives new authored exact credit: 883 bytes.
Four std::array constructors are compiler-generated and excluded from authored
coverage. The five remaining functions retain unknown origins. Full resource
loading, actual destruction, frame/draw execution and RTTI/vtable data exactness
remain separate acceptance boundaries.

| Native entry | Code / comparison bytes | Maintained function |
| --- | ---: | --- |
| 0x4AEF90 | 883 / 883 | FrontInf::FrontInf |
| 0x4AEB40 | 159 / 164 | FrontBossPanel::FrontBossPanel |
| 0x4AEBF0 | 146 / 146 | FrontFlags::FrontFlags |
| 0x478160 | 44 / 44 | FrontInf::has_dialogue |
| 0x49C720 | 25 / 25 | FrontInf::set_field_180 |
| 0x49C9C0 | 65 / 65 | FrontInf::set_boss_gauge |
| 0x4AED50 / 0x4AEDA0 / 0x4AEDF0 / 0x4AEE40 | 75 / 80 each | std::array of 2 / 3 / 7 / 10 AnimationHandles |

The 5-byte tails are present in the complete COFF contributions and native
inter-function storage. They are compared in full, not discarded to match a
Ghidra body span or inserted into source. No arbitrary padding is declared.

## Independent owner evidence

The native allocator at 0x4AE8A0 allocates and clears 0x2D8 bytes before calling
the constructor. The deleting wrapper independently uses the same size. Both
constructor and destructor write vptr 0x57062C. Its three slots are deleting
destructor 0x4B06A0, enable 0x4B5BB0 and inherited disable 0x421760. COL 0x5A45BC
and its two-entry hierarchy explicitly name FrontInf and TaskInf, with the base
at offset zero. This corroborates the existing canonical TaskInfo declaration;
it does not accept the reference CallbackOwner adapter or original RTTI bytes.
The declaration preserves the observed class key and explicit public base.

Native constructor calls establish std::array handle groups at +10/+2C, +48,
+94/+D0 and +BC, individual handles, two genuine Timers and the boss panel array.
Each boss panel contains two floats, two scalar words, four actual eight-byte
HudGauges, seven handles and two final words. The flags constructor clears nine
bit-field groups covering low14 bits and preserves upper18. Its field meanings
remain provisional.

Paired constructor stores cover +158/+160/+168; 64-bit arithmetic on the latter
two corroborates the eight-byte values and natural alignment. Natural alignment
accounts for +154 and +2D4 in the maintained declaration, without invented
members. Native construction retains those bytes; their original declaration
details remain unknown. Names for neutral scalars and the first 64-bit value's
semantic role remain unknown. Resource producers independently identify
message_file at +170, Dialogue at +1BC, writable message bytes at +1C0 and
front_file at +2CC. Construction deliberately retains front_file until loading.

The constructor calls the existing empty diagnostic with `initialize FrontInf`
and then publishes this to process slot 0x5C06A4. This explicit game-specific
publication body and diagnostic identity establish authored origin independently
of auto-analysis or byte equality. Resource-owning destruction remains undefined.
The pinned SDK array header has no written default-constructor body; compiler
emission, element count/stride, native callers and complete EH corroborate the
four generated array constructors. Boss/flags origin remains unpromoted because
original written versus synthesized initialization is not established.

## Complete EH and compiler scope

The actual FrontInf constructor is throwing-capable: FuncInfo 0x5AAB78 has flags1
and one unwind state. Native handler 0x56989D independently identifies its code
section. Complete COFF-relative roles place the section at 0x569890: eight bytes
of TaskInfo cleanup, five retained INT3 bytes and the 29-byte handler. The full
44-byte metadata section starts at 0x5AAB70 and includes its unwind map.

The boss and four array constructors share a complete 29-byte handler at
0x567600 and 36-byte FuncInfo at 0x5A91B8, with flags5 and no unwind states. All
raw code, metadata and relocation roles strictly replay, including every alias.
Bindings use the independent parent entries, native type/call evidence and
complete COFF-relative labels; no compared relocation field is solved.

Maintained source changes are confined to HudGauge.hpp/cpp. Captured includes select one
provider / one previous unit. Its profile now uses the locally verified GS/EHsc
configuration required by these complete constructors; the old 34-byte HudGauge
constructor still strictly passes. Two canonical builds were needed, the final
one after preserving the native class key. Final verification covers the same
old unit and ten new units; 163 unaffected providers reuse valid evidence. The
one generated literal-label change and pointer class-tag change preserve their
complete data and native roles. No
unfiltered replay, full CI or additional cleanup replay runs.

## Semantic checks and whole-root frontier

The public O2/UBSan fixture passes 1,706 construction/publication/gauge cases.
It checks all 256 dirty-byte patterns, retained fields/padding/upper flags,
guard bytes, publication after the diagnostic, base cleanup on injected failure,
virtual slot shape, all 3x4 valid markers, full signed tag bits and copied float
words. Scheduler and resource destruction are explicit host boundaries.

At CORE159 the integrated private whole-root draft passed 36,244 scenarios:
26,781 prior cases and 9,463 new FrontInf callers. It contains 110 effective values /
81 primary heads. Production dispatch remains undefined and receives no partial
source acceptance or exact credit.

Opcode 534 reads its value before loading the live process FrontInf and writing
field180. Opcode 519 short-circuits the actual Dialogue-pointer predicate, then
tests the full integer result of the genuine Dialogue-ready operation. At CORE159
that whole callee was still undefined and captured by the fixture.

CORE161 subsequently implements the actual ready getters, complete Dialogue
storage/construction and callback partition. The current root fixture uses a
live complete Dialogue and passes 36,232 cases after retiring twelve synthetic
getter mutation/exception cases. See [Dialogue evidence](DIALOGUE_OWNER_RECONSTRUCTION.md)
for current validation scope and remaining resource/geometry boundaries.

Opcode 527 reads float1, integer2, the signed initial-health word, then integer0
and the current boss index. It divides by binary32(initial health) before the
last operand and loads the process HUD after operand evaluation. The physical
offset-four getter is folded with Timer::operator int, but its real receiver is
EnemyHealth at state+18C. It reads field04, not current health or a Timer base.
The private source preserves that semantic distinction; exact whole-root member
call partitioning remains open. Tests cover denominator mutation, late boss/HUD
selection, zero/negative denominators, failure prefixes and complete state/owner
images. Portable NaN checks establish classification, not native NaN payloads.
All marker indices and resource/frame pointers stay within documented valid
domains; unchecked out-of-range native behavior is not replaced by exceptions.

Fourteen nondefault state paths remain: 502/503, 516..518, 524, 539, 548/549,
551, 553..555 and 575. This owner removes a layout blocker; it does not close
the remaining Dialogue, Stage, scene/menu, sound or Renderer/resource protocols.

## Protected private evidence

Paths below are relative to `.analysis/`:

- `core159-front-layout-native.asm`, `core159-front-typed-consumers-native.asm`, `core159-front-native-identity.json`
- `core159-front-v1-diagnostic.json`, `core159-independent-bindings.json`, `core159-cold-proof.json`
- `core159-affected-results.json.gz`, `core159-new-exact-results.json.gz`, `core159-front-semantics-v3.log`
- `core159-enemy-dispatch-candidate.cpp`, `core159-dispatch-host.cpp`, `core159-front-host-cases.inc`, `core159-dispatch-host-recipe.json`, `core159-dispatch-host-v4.log`
- `core159-pre-front-inputs.json.gz`, `core159-pre-registration-ledgers.json.gz`, `core159-probe-original-inputs.json.gz`, `core159-canonical-v1-original-inputs.json.gz`, `core159-dispatch-host-v3-original-inputs.json.gz`
- `core159-graph-audit.json`, `core159-retirement-plan.json`, `core159-cleanup.json`, `core159-gates.json`

Original REF-032/033 exports and rejected reference-body decisions remain
protected. Read [whole dispatcher evidence](CORE_ENEMY_DISPATCH_LAYOUT.md) and
[rank/control](ENEMY_RANK_CONTROL_RECONSTRUCTION.md) for the preceding frontier.
