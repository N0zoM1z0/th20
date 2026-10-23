# Enemy clear, selection and return protocol

CORE/EXACT-152 continues the same whole `EnemyState::execute_opcode` source
construction at `0x48C010`. The comparison target remains the locked Japanese
v1.00a Steamless executable, with the embedded 1.00c label in that same file.
Current totals and protected products belong in [the handoff](RE_HANDOFF.md).

## Complete accepted dependencies

| Genuine owner method | Native entry | Complete bytes | Origin |
| --- | --- | ---: | --- |
| EnemyController::clear_matching | 0x4A4810 | 521 | Authored |
| EnemyController::clear | 0x4A4A20 | 501 | Authored |
| EnemyController::clear_variant_565 | 0x4A4C20 | 514 | Authored |
| EnemyController::clear_variant_573 | 0x4A4E30 | 526 | Authored |
| EnemyState::flag_04_bit_30 | 0x4AB380 | 26 | Pending |

These five complete roots add 2,088 disjoint strict comparison bytes. The four
clear protocols account for 2,062 authored bytes. Custom Enemy filtering,
drop-state reset, defeat/resource ordering and variant-specific publication
establish application origin independently of byte identity. The small flag
query's broader meaning and origin remain unclassified.

The real Controller owns the list at +108 and Timer at +9C. Every clear uses the
existing `IntrusiveIterator<Enemy>` observer protocol, including its destructor.
It processes an actor when none of word00 bits 5, 7, 10 or word04 bits 6, 7 is
set, or when word00 bit 8 overrides those protection tests. The matching variant
then requires signed state.field30 equality. Variant 573 additionally excludes
word04 bit 30. Variant numbers identify their independent native ECL callers;
more specific gameplay names remain unproven.

For each eligible actor, the order is:

1. Reset the actual EnemyPattern; set vector6C X to zero and Y to 192, preserving Z.
2. Clear field284. Variant 565 also sets field27C to -1.
3. Call the genuine whole Enemy::defeat method, ignoring its return here.
4. Iterate the actor's current animation vector after defeat returns, retiring
   every handle, including zero; then clear the vector.
5. Set state.word04 bit 9, preserving fresh changes made by callbacks.

Only after iterator destruction does the Controller post-increment Timer8C.
An exception in defeat or retirement unwinds the real iterator and prevents
subsequent stores and the Timer tick. Callbacks may detach the current or pending
node, append a later node, or replace animation records; cached raw next pointers
would lose this observer behavior. No extra null guard or actor lifetime extension
is inserted. Fixtures keep all referenced actors alive.

`Enemy::defeat` is declared on the real 0x428-byte owner. Its full 1,371-byte
ordinary native body at 0x4A5640 has recursive child, script, resource, score,
drop and callback paths. It remains undefined in maintained source; the declaration
and captured fixture calls receive no source, mapping or exact credit for it.
Renderer retirement also retains its existing unresolved resource boundary.

## Compiler and independent identity evidence

Maintained bodies live in existing EnemySpawning.cpp and EnemyState.cpp, using
unchanged per-source profiles and the same 279 source/probe paths. The first
natural probe used early continues and a redundant vector reference; its complete
roots were 6–8 bytes longer. Keeping work inside the eligibility condition and
ranging directly over the actual vector explains all four complete native bodies.
No inert local, artificial padding, ABI change or alternate match body is used.

Relocations reuse previously accepted iterator, Timer, pattern, animation-range,
retirement, constant and security identities. The complete 116-byte vector clear
and its actual SDK helper bodies are separately replayed as support. The four
Controller roots share native cleanup/handler code at 0x5683C0: a complete
13-byte iterator cleanup plus 39-byte handler. Its complete 44-byte unwind-map
and FuncInfo section is at 0x5A9E04. A unique full code/state-map identity locates
both sections independently of the compared root relocation fields. Complete
canonical relocation replay then verifies every byte. Shared EH and SDK support
receive no additional physical or authored credit.

Private records include `core152-native-body-audit.json`,
`core152-independent-bindings.json`, `core152-cold-proof.json`,
`core152-affected-results.json.gz` and `core152-new-exact-results.json.gz` under
`.analysis/`. Original SHA-bound sources and receipts are preserved in
`core152-pre-clear-inputs.json.gz`; receipts are never rewritten.

## Whole-root caller construction

The private draft extends the same root to 96 values / 67 primary heads. All
previous 90 case bodies are preserved. Its host exercise now returns int32,
matching the independently observed common zero return and these native exits:

| ECL value | Reviewed caller behavior |
| --- | --- |
| 520 | Resolve selected slots 0, 1, 2 in order; return -1 on the first nonnull result. Reload the actual Context Controller for each lookup. |
| 525 | Call the current Controller's default clear. |
| 545 | Cache the Controller before reading integer operand 0, then clear matching that signed value. |
| 560 | Call state.entity->defeat and test the full EAX result; return 1 when nonzero, otherwise reach the common zero return. |
| 565 | Call the current Controller's variant 565 clear. |
| 573 | Call the current Controller's variant 573 clear. |

The 102 new integrated scenarios test short circuit, live Context/Controller
replacement, cached receiver versus operand callbacks, full-width defeat results,
clear side effects and exceptional exits. The retained movement, phase, counter,
drop, health/boss and Card scenarios bring the same O2/UBSan fixture to 19,350.
The production dispatcher stays undefined. Private factoring and its out-of-domain
exception do not establish whole-root source acceptance or partial exact credit.

## Semantic verification and limits

The public actual-owner creation fixture additionally passes 4,636 clear cases:
all seven relevant flag bits, signed selectors, empty and populated animation
vectors, zero/full-width handles, pre-defeat writes, fresh post-callback flags,
observer detachment/appending, vector replacement, and defeat/retirement failures.
It models unaffected owner bytes, checks the vector's storage/capacity/size
separately, and checks observer cleanup. Whole defeat and Renderer resource calls
are explicit captures; native startup, actor destruction during callbacks and
original resource execution remain outside this fixture's domain.

Captured include closures select 17 changed providers / 82 existing units. Fresh
serial builds and strict replay pass for those units and the five new roots;
147 unchanged providers reuse valid evidence. The focused public test and private
integrated fixture pass without full CI or unfiltered replay. Cleanup verifies
protected hashes only, with zero additional builds or replay.
