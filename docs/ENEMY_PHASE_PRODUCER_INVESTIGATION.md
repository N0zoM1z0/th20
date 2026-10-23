# Enemy phase producer reconstruction

## CORE/EXACT-147 acceptance

The maintained Enemy owner now implements the complete phase and timeout
configuration protocol used by the whole opcode dispatcher. EnemyInitialization.cpp
owns both producers; EnemyState.hpp keeps the record's implicit member defaults.
Original translation-unit ownership and C++ spelling remain unproven. This work
accepts no switch fragment or partial exactness for EnemyState::execute_opcode.

| Entry | Complete bytes | Canonical contribution | Origin |
| --- | ---: | --- | --- |
| 0x4A3530 | 71 | EnemyPhase implicit default construction | Compiler |
| 0x4AB650 | 301 | Enemy::configure_phase | Authored |
| 0x4AB780 | 154 | Enemy::configure_timeout | Authored |
| 0x4AB570 | 32 | PMR vector size-only resize wrapper | Library |
| 0x4ABA00 | 41 | PMR vector size | Library |
| 0x48BD40 | 36 | PMR vector unchecked element access | Library |
| 0x4AA160 | 66 | PMR vector checked element access | Library |

All seven full contributions, totaling 701 bytes, strictly replay from the fresh
canonical EnemyInitialization object. The two authored producers account for
455 authored exact bytes; compiler/library support is excluded from authored
coverage. Complete COFF sections agree with reviewed native entries, returns and
extents. No target-sized prefix, padding insertion or synthetic wrapper is used.

## Actual receiver and state transitions

Both producers receive Enemy and access the vector at Enemy+0x340, corresponding
to EnemyState+0x2B8 at Enemy+0x88. EnemyPhase is 136 bytes: two signed 32-bit values
followed by two independent 64-byte names at +8 and +72.

configure_phase grows when size is less than unsigned 32-bit `index + 1`, then
writes life. Negative life preserves time and both names. Otherwise it writes
time and copies the supplied name into both arrays through the existing
strcpy_s interface, or clears only each array's first byte for a null name.

configure_timeout preserves the native asymmetry: a non-null name uses checked
vector access before copying the timeout name, while a null name uses unchecked
access and clears only its first byte. There are no invented overflow checks or
extra bounds guards. The native producers' ignored/unequal return-register
contents support the maintained void interface.

## Implicit construction and independent bindings

The native construction chain is traced independently through vector resize
0x4A1F80, uninitialized construction 0x4A2380, backout emplacement 0x4A19B0,
allocator dispatch 0x4A25D0/0x4A25F0, tuple application 0x4A2470, construction
adapters 0x4A17D0/0x4A2AD0 and value construction 0x4A15A0.

At 0x4A15A0, the caller obtains the real placement address, zeroes all 136 bytes
and invokes 0x4A3530. That complete constructor writes life/time as -1 and zeroes
both entire name arrays. Natural in-class initializers preserve this implicit,
non-user-provided construction contract. A hand-written constructor would remove
the implicit outer value-initialization pass; no forced extra memset is added.
The fresh canonical provider also matches that complete 62-byte lowering outside
relocation fields. This is separate compiler corroboration, not a new exact unit.

The earlier CORE146 private 33-byte constructor guess initialized only life/time.
It had no complete raw target occurrence and was never production source. Its
inputs and failed observation remain preserved. The corrected 71-byte body first
agreed completely through the already established memset anchor, then passed
fresh canonical strict replay.

Relocation identities come from independently reviewed complete callees, actual
receiver/argument flow and pinned SDK definitions. The relocation-free 36-byte
index and 41-byte size bodies each have one complete raw target occurrence.
Resize delegates to the independently reconciled 254-byte shrink/no-op/grow
algorithm; checked access uses the native range-failure wrapper and observed
invalid-vector-subscript string. Neither underlying delegate receives standalone
exact credit in this batch. memset at 0x544760 and strcpy_s at 0x548610 reuse
existing independent anchors. No compared producer field is solved for an anchor.

## Behavior and verification scope

The existing actual-Enemy creation fixture now executes 720 phase/timeout
transitions against independent 136-byte record images, checking every live
record after each transition. It covers growth and gaps, retained capacity,
negative/zero/positive life, signed time extremes, null/empty/63-byte names,
untouched tails, copy order and the non-null checked overflow branch. Separate
dirty-storage and vector-growth checks verify both complete name arrays and
life/time defaults. Both relevant O2/UBSan public tests pass.

Valid nonoverlapping names delimit the fixture's explicit CRT capture boundary;
native oversized-input/invalid-parameter behavior is not claimed. The unchecked
null overflow branch is outside the valid test domain. Startup, complete VM
dispatch, original resource integration and native runtime execution remain open.

Captured include closures select 17 affected providers / 72 previous units.
Each provider is cold-built once, and all 72 previous units strictly replay.
Two literal-label renames preserve complete old/new COFF data, roles, targets and
addends. The other 147 providers reuse valid existing evidence. Only those 72
affected and seven new units are replayed; cleanup adds no replay requirement.

## Protected evidence and remaining whole-root work

Private results are relative to `.analysis/`:

- `core147-independent-bindings.json`, `core147-new-exact-results.json.gz`
- `core147-value-construction-corroboration.json`
- `core147-cold-proof.json`, `core147-affected-results.json.gz`
- `core147-enemy-phase-semantics.log`, `core147-core-semantics.log`
- `core147-pre-phase-inputs.json.gz`, `core147-retired-inputs.json.gz`
- `core147-graph-audit.json`, `core147-cleanup.json`, `core147-gates.json`

Preserve the CORE146 and CORE147 attested native exports, Ghidra logs, private
probe sources and original receipts/inputs in the retirement archive. Rejected
source is evidence, not an alternate production implementation.

The private 500..575 catalog still covers 75 effective values, excluding default
569, across 71 primary heads. Whole opcode 514 includes additional practice and
state handling beyond these producers; opcode 521's caller also remains in the
unimplemented root. Continue that same whole-root construction with genuine
receivers. HUD, laser and other unresolved owners cannot be replaced by reference
service adapters. Preserve full default behavior, tables and EH under
[whole-root evidence](CORE_ENEMY_DISPATCH_LAYOUT.md).

CORE148 continues the caller paths in the same private whole-root draft; see the
[state opcode frontier](ENEMY_DISPATCH_STATE_RECONSTRUCTION.md) for replacement
conditions, borrowed strings, repeated indices and receiver caching. These caller
paths remain outside production source and add no partial dispatcher exact credit.
