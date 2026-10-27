# Whole Enemy opcode 502/503 visibility propagation (CORE169)

The locked reconstruction target is Japanese TH20 v1.00a Steamless PE32,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This work advances the **whole EnemyState::execute_opcode** root at `0x0048C010`
(41,967 native body bytes). These cases are part of that large function, not
independent externally callable functions or separately comparable units.
Nothing in this batch adds whole-root machine-code exactness or partial credit.

## Two independently bounded large native branches

An independent complete decode from the attested original PE32, cross-checked
against the existing native dispatch case catalog, fixes two distinct physical
branches:

| Opcode | Start (inclusive) | End (exclusive) | Native bytes | Instructions |
| --- | --- | --- | ---: | ---: |
| 502 | `0x00490E09` | `0x004913C9` | 1,472 | 296 |
| 503 | `0x004913C9` | `0x00491989` | 1,472 | 296 |
| **Both** | | | **2,944** | **592** |

Both entries call the existing `EnemyState::integer_argument(0)` at `0x4AB080`
exactly once, then update **14 independent bit positions (0..13)** in the
actual `EnemyStateFlags::word_00` at State+`0x2C8`:

- **502** performs `old_bit | operand_bit` on each of those fourteen positions,
  leaving all upper 18 bits untouched
- **503** performs `old_bit & !operand_bit` for the same fourteen positions,
  likewise retaining all higher bits

The original code emits fourteen ordered individual read/modify/write bitfield
sequences, not a single prepacked C++ arithmetic statement. No game callbacks
occur between those writes. The private semantic draft uses the corresponding
`word_00 |= (mask & 0x3fff)` and
`word_00 &= ~(mask & 0x3fff)` as an observable-state model; it is **not** a
claim of native compiler emission, atomicity or original source spelling.
The exact low-bit numbers and 28 native clear masks were separately enumerated
and independently audited, rather than inferred from the historical adapter.

## Updated bit-five branch and real animation tree

Immediately **after** all fourteen stores, each case reloads State+`0x2C8`
and examines **bit 5 of the updated word**, not an earlier cached flag:

| Opcode | Condition for visiting every record | Native wrapper | Actual Animation method |
| --- | --- | --- | --- |
| 502 | Updated bit 5 is **set** | `0x00450120` | `clear_flag0_recursively` at `0x00450160` |
| 503 | Updated bit 5 is **clear** | `0x0044FA30` | `set_flag0_recursively` at `0x0044FA70` |

The original loops obtain begin/end from the existing `std::pmr::vector` at
State+`0x0C` using the complete existing begin/end ABI operations at
`0x414F30`/`0x414F70`. Each entry is a real 20-byte `EnemyAnimationLink`,
whose first field is its four-byte `AnimationHandle`. Iteration visits **all**
records, including zero and otherwise unresolvable handles, in vector order.

Both 50-byte handle wrappers query the native Renderer owner at
`0x005C0028`; if lookup fails they simply return, **without changing the old
handle word**. This is materially different from the separately accepted
`AnimationHandle::resolve()`, which clears an unresolved handle. The true
Renderer/pool storage and lookup are still unresolved, so the private host
captures only this lookup boundary. On successful fixture resolution, it
executes the **real accepted** `Animation::clear_flag0_recursively` or
`set_flag0_recursively` production implementation, including actual child and
grandchild traversal. No fake production Renderer facade or general-purpose
replacement for `resolve()` has been introduced.

## Full root integration and independent checks

The previous, SHA-protected CORE168 private complete Enemy switch is preserved.
CORE169 adds **two distinct case blocks**, taking it from **112 effective opcode
values / 83 native primary heads to 114 / 85**, with earlier 516/575 source
ordering and their exact SoundInf/Player callees retained. An independent
read-only audit preserves the complete 1,472-byte interval and all 296
instructions for each case, verifies fourteen bit clears in numerical order,
confirms both bit-five gates and concrete native call destinations, and checks
the attested target SHA-256. The original 41,967-byte root, all shared tables,
and whole exception/COFF contribution are still outside exact acceptance.

The private full-root host is freshly built with **78 actual C++ translation
units** under `g++-13 -O2 -fsanitize=undefined -fno-sanitize-recover=all`.
It passes all **36,310** earlier scenarios and **492** new visibility cases:

- **480** combinations: 2 opcodes × 10 old state words × 12 complete operand
  words × 2 operand callback mutations. They check exact low-14 transformations,
  preservation of State flag words +4/+8, the post-write bit-five gate, all
  four animation handles including invalid values, and four real Animation
  nodes including a two-level child chain
- **6** argument-read exceptions: no bit or animation mutation before the
  input callback completes
- **6** downstream renderer-boundary exceptions: the complete flag update and
  already-visited subtree effects remain, later entries are untouched, and
  no handle word is silently cleared

The aggregate private test result is **36,802/36,802**. This is genuine
host-side semantic corroboration using real C++ state owners and real
`Animation` recursion, **not** native game execution. It does not model every
possible Renderer failure, concurrent observation between native bitfield
stores, OS startup or whole-game linkage.

## Preserved private proof and remaining reconstruction

All below are ignored local evidence paths (relative to `.analysis/`), not
tracked production source or new canonical contributions:

- `core169-opcode-502-native.txt`, `core169-opcode-503-native.txt`, and
  `core169-enemy-502-503-native-audit.json`: complete bounded original
  instruction ranges, masks, call destinations and SHA-256
- `core169-enemy-dispatch-candidate.cpp`: two distinct case blocks in the
  **entire** retained Enemy draft; prior `core168-*` versions preserved
- `core169-dispatch-host.cpp`, `core169-visibility-host-cases.inc`,
  `core169-dispatch-host-recipe.json`, `core169-dispatch-host.log`: current
  complete host, source compilation, 492 cases and passing output
- `core169-whole-enemy-root-proof.json`: attested target/code identities,
  89 original/new source-and-fixture hashes, 78 host sources, old-input hashes,
  exact case bounds, 36,802 scenarios and valid unchanged 164 canonical receipts

The tracked acceptance graph stays at **208 authored exact functions / 56,444
bytes**, **994 strict units**, and **164 objects**. The **41,967-byte Enemy
root itself remains nonexact and source-unadmitted**. Next resolve the true
Renderer lookup/handle wrapper ABI and additional cases including opcode
517/518 allocation-and-resource behavior, opcode 524, 539 and the remaining
large shared-dispatch exits. [Whole dispatch tables and EH](CORE_ENEMY_DISPATCH_LAYOUT.md)
and the earlier [516/575 integration](ENEMY_WHOLE_ROOT_516_575_INTEGRATION.md)
retain the surrounding evidence.
