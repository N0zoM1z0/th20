**CORE/RECON-1003 update:** Five whole native Card-start helper heads (29B+42B+61B+22B+71B) are now [exact under pinned MSVC](CARD_START_FIVE_225_STRICT_EXACT.md). The full 1,896B Card::start_spell remains source-absent/NONEXACT; no parent exact credit follows.

**Current status correction (CORE/RECON-1002):** `Card::finish_spell` at `0x004878B0` is now [whole 602/602B strict exact](CARD_FINISH_602_STRICT_EXACT.md). Dated NONEXACT statements below predate the accepted complete original source. `Card::start_spell` 1,896B remains source-absent.

# Enemy Card caller protocol and flag ownership

## CORE/EXACT-151 scope

The same private whole EnemyState dispatcher at 0x48C010 now includes 522, 523,
528, 531..533, 536, 537, 561 and 562. It contains 90 effective values / 61 primary
heads, preserving the preceding movement, phase, counter, drop and health/boss
bodies. Its explicit instruction argument, packet helper and out-of-domain
exception remain host exercise factoring. No production dispatcher or partial
exact credit is claimed; remaining owners, native default, tables, EH and whole
compiler contribution remain open.

| Entry | Complete bytes | Maintained function |
| --- | ---: | --- |
| 0x497450 | 26 | Card::request_flag_3 |
| 0x497420 | 38 | Card::request_flag_4 |
| 0x49CA10 | 42 | Card::set_flag_8 |
| 0x49C360 | 36 | EnemyHealth::set_scaled_enabled |

These four complete contributions add 142 strict comparison bytes. Their
origins remain pending; authored exact coverage does not increase. Card.cpp and
EnemyHealth.cpp retain their existing profiles and canonical owner declarations.
Their four-byte flag words expose only the independently observed bit views;
full old constructors and other affected units retain exact output.

## Name decoding and live instruction metadata

All five start opcodes share the native head at 0x494170. It zeroes a local
128-byte buffer, reads a signed raw length from instruction+28, and decodes bytes
beginning at instruction+32. This length is not an ECL integer-argument query.
Negative or zero lengths decode no bytes. Valid fixture lengths are at most 128;
no invented clamp, termination store or exception replaces native behavior.

The initial key is 0x77 and step is 7. Each byte is XORed with the current key,
then key advances by step and step advances by 0x10, both modulo 256. The
independent fixture encoder uses the closed form key(i)=119+8*i*i-i modulo 256.
High-bit bytes preserve their low-eight-bit XOR results. Only bytes not written
by the loop retain initial zeroes; length 128 receives no extra terminator.

After decoding, native code reads integer argument0, then reloads the signed
instruction opcode. Only a reloaded 531, 532 or 533 reads Session.mode and adds
mode, mode-1 or mode-2 to the selected spell word. Arithmetic wraps at 32 bits.
The original entry selector cannot replace this later read. The decoded local
buffer remains independent of subsequent mutations to encrypted bytes/length.

Next it obtains and caches the actual Card from the live Context, reads integer2
and then integer1, and calls start_spell(index,decoded,duration,arg_3). The final
argument's broader meaning remains unresolved. Context/Card retargeting during
those last operand calls does not replace the cached receiver.

Only after a successful Card return does the caller enable scaled-health mode,
read current raw health again, store its sevenfold low-word value, and assign
TimerA8 zero through the real Timer protocol. These updates observe callee
mutations. An escaping host callee exception prevents these later operations;
this test establishes caller ordering, not original CRT/resource unwinding.

## Other Card and health paths

Opcode562 caches the actual health receiver before integer0 and writes only
scaled-mode bit0 from that full word's low bit. The native damage consumer
independently establishes this bit's scaling role. Other health flags survive.

Opcode523 calls finish_spell on the Context's Card, then disables scaled-health
mode using the post-call flag word. It does not rescale health or reset TimerA8.
The complete native finish call remains a separate implementation boundary.

Opcode536 sets Card flag bit3 without operands. Opcode537 sets bit4 before
unconditionally invoking the real effect_handle.retire member, including a zero
handle. Opcode561 caches its Card before integer0 and replaces only bit8 from
the low input bit. The broader Card flag meanings remain unknown.

The complete 37-byte native handle retirement at 0x44FCD0 forwards its scalar
through the real Renderer global at 0x5C0028, then clears the handle word. Its
identity is independently shared with the previously exact Enemy movement
caller. The new 38-byte Card helper reuses that relocation; Renderer execution
remains undefined and is captured in host tests. No destination is solved from
a compared field. The real Context::card pointer getter fully equals the prior
17-byte chain_node_shutdown contribution at 0x411700, with compatible x86
pointer return/offset/calling convention and no relocations. This typed use
adds no physical mapping, unit or exclusive tag identity.

## Complete native Card producers still need source

The genuine 0xC8 Card owner, five typed handles, Timer, 64-byte name, clocks,
Context and original construction identity remain as established in
[Card construction](EXACT_CARD_RECONSTRUCTION.md). start_spell and finish_spell
are declarations on this actual owner; no prefix facade or service adapter is
introduced. Both production bodies remain undefined and receive no mapping,
source-presence, canonical-unit or exact credit.

The complete ordinary start body at 0x487C30 covers 1,896 bytes. It resets age,
stores spell/name, changes active/capture/other flags, updates paired spell
records through the process storage owners, coordinates game/UI/ANM state,
uses the actual selected boss position, writes duration and animation variables,
and computes bonus/stage-dependent effects. The fourth argument also indexes
stage-related records; its complete source role is not settled. The native
PMR-string cleanup and associated EH contribution need to remain in scope.

The complete ordinary finish body at 0x4878B0 covers 602 bytes. Inactive calls
return before side effects. Active calls release three info handles, clear the
active flag, retire background/effect handles and clear another flag. Capture
paths publish bonus/score, update two record sets, scan 113 spell records for
completion and select distinct sounds. UI and Renderer ownership are genuine
open dependencies, rather than disposable wrappers around scalar fields.

Both ordinary listings cover their full byte extents without gaps and keep
direct branches inside those extents. These independent game-specific callers,
record/achievement logic and owned resources establish authored origin for the
two functions. Their associated compiler contributions and executable-wide
integration are not accepted. Authorship is separate from source and exactness.
Continue closing the actual UI/record/Renderer producers before maintaining
these full bodies; the integrated fixture captures their whole member calls.

## Verification and limits

Captured includes select 19 providers / 95 prior units. Each is cold-built once
and strictly replays, followed by the four complete new units. The other 145
providers reuse valid evidence. Three literal-label renames preserve complete
old/new COFF data, roles, addends and destinations. No profile, layout extent or
exception contract is changed to shape output. There is no unfiltered replay,
full CI or cleanup-triggered compiler/replay invocation.

The public Card fixture passes O2, Werror and nonrecovering UBSan. Existing
construction, guarded gaps, encoding, time queries and Context publication
still run. Its 104 new whole-owner/mask/callback cases exercise the actual Card
and health methods, unconditional zero-handle calls, flag-before-retirement,
callee mutations and failure ordering. Only Renderer retirement and Card
disposal remain explicit boundaries in that fixture.

The integrated private root passes all 15,619 prior cases plus 3,629 Card
callers: 19,248 total. The new cases include 3,365 decoded-name/start paths and
264 flag/finish paths. Whole State, Session and Card images check signed length,
complete 128-byte decoding, high-bit names, full-word wrapping, live opcode,
late difficulty reads, cached Card receivers, argument order and post-call
health/Timer writes. Opaque Card start/finish and Renderer calls are captures
on real owners. Synthetic full-width spell/time/arg_3 inputs test the caller
contract; they do not prove the native Card accepts invalid record indices.
Decoded names are valid C strings of at most 63 bytes, including full-length
packets with trailing decoded data. No original ECL allocation, resource VM,
startup, CRT exception or whole-program runtime claim follows from these tests.

## Preserved evidence and next work

Private paths are relative to `.analysis/`:

- `core151-card-callers-native.asm`, `core151-card-native.asm`, `core151-retirement-native.asm`
- `core151-native-body-audit.json`, `core151-flags-probe-diagnostic.json`, `core151-independent-bindings.json`
- `core151-flags/`, `core151-enemy-dispatch-candidate.cpp`, `core151-draft-scope.json`
- `core151-card-host-cases.inc`, `core151-dispatch-host-recipe.json`, `core151-dispatch-host.log`
- `core151-card-semantics.log`, `core151-pre-card-inputs.json.gz`, `core151-retired-inputs.json.gz`
- `core151-cold-proof.json`, `core151-affected-results.json.gz`, `core151-new-exact-results.json.gz`
- `core151-graph-audit.json`, `core151-cleanup.json`, `core151-retirement-plan.json`, `core151-gates.json`

Continue the same root through real UI/record, clear/selection and laser owners.
Preserve full Card start/finish, the original Renderer boundary and all rejected
emission evidence. See [whole dispatcher layout](CORE_ENEMY_DISPATCH_LAYOUT.md)
and [health/boss state](ENEMY_HEALTH_BOSS_STATE_RECONSTRUCTION.md).

## CORE/RECON-1000 update: original 602B finish now has complete source

The historical source-absent status above has been superseded by a
[complete maintained Card finish C++ body](CARD_FINISH_602_TYPED_SOURCE_AND_41_23_EXACT.md)
that includes both capture-record groups, the 113-record completion scan and
all resource/sound branches. The compiler candidate is 577B versus native
602B, so it is **NONEXACT** and receives **no authored game byte credit**.
Two new 41B/23B physical Card caller leaves are whole strict exact, with just
23B credited to game-authored code; the 1,896B start remains open.
