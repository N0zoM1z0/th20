# Actual damage-query consumer protocol

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-103 closes a coherent set of consumers of the complete native
1,707-byte HitCtrlInf query. Fourteen complete maintained bodies replay 1,025
bytes and 36 independently anchored relocations. Thirteen are new physical
units, adding 980 disjoint bytes. Timer::changed shares the existing 45-byte
Cursor::changed contribution; Context::player and EnemyHandle::get also share
existing physical heads. None of these aliases receives duplicate credit.

## Complete maintained functions

All bodies live in `src/DamageQueryProtocol.cpp`, using the existing real
Session, Player, Shot, Enemy, Context and Overlay declarations. This is one
coherent consumer translation unit with the unchanged locked /EHsc profile.

| Consumer | Address | Complete bytes |
| --- | --- | ---: |
| PlayerRecord::add_score | 0x004E14B0 | 88 |
| Session::add_score | 0x00488550 | 55 |
| Timer::changed, existing physical alias | 0x0045D030 | 45 |
| Timer::every | 0x00478E00 | 61 |
| Player::frame_changed | 0x004C0CE0 | 25 |
| Player::find_shot | 0x004C0FB0 | 38 |
| PlayerShotController::find | 0x00506360 | 246 |
| DamageRegion::player_shot | 0x004C0F70 | 55 |
| EnemyController::find | 0x00498A80 | 251 |
| Enemy::health_value | 0x004AABD0 | 19 |
| EnemyHealth::force_defeat | 0x004C1E90 | 26 |
| Enemy::reward_multiplier_enabled | 0x004C1AC0 | 26 |
| Enemy::set_damage_marker | 0x004C1FC0 | 45 |
| WeaponStoneInfo::record_damage | 0x004A9F80 | 45 |

The additional existing-head aliases are Context::player at 0x0040FF90,
17 bytes, and EnemyHandle::get at 0x0040C300, 16 bytes. Complete native extents,
all internal branches and final returns are decoded independently. Forty-five
complete template, EH handler, FuncInfo, state-map and cleanup contributions
replay as support. A private DamageRegion iterator FuncInfo belongs solely to
the excluded whole-query candidate and is not emitted by this production TU.

## Storage and behavior evidence

Shot lookup traverses the real PlayerShotController active list, comparing
Shot+14 state words through the reference-valued node accessor. Enemy lookup
traverses the real EnemyController+108 list, comparing EnemyState identifiers
through the value accessor. Both reject zero before traversal, return the first
matching node and release iterator observations on every return. No alternate
receiver, fake class prefix or fabricated list is introduced.

The query's Context+8 lookup is the existing actual EnemyController getter.
Its reward-stage result is an Enemy. Earlier item-receiver descriptions of
that physical getter were incorrect; Item spawning remains a separate, later
Counter dependency. Context+4 returns the actual Player under the native
consumer's published-pointer precondition. The field remains void* pending
complete native publication/owner lifetime reconstruction; the maintained
accessor performs the ordinary void*-to-Player* conversion.

Score divides an unsigned 64-bit delta by ten, adds modulo64 and then clamps
values at or above one billion to 999,999,999. The independently exported
native __aulldiv at 0x00543200 corroborates unsigned division and ret16.
Session always selects record zero and zero-extends its uint32 input. Timer
change is a full int32 result; periodic gating short-circuits unchanged frames.
For changed frames, zero divisors and INT32_MIN/-1 remain outside the valid
native/C++ division domain.

Forced defeat preserves health flags while setting bit one. Reward multiplier
reads EnemyState flags word04 bit30. Damage marking truncates its input bit zero
into word08 bit4 while preserving every other bit. The new union provides the
actual raw-word and bit-field views without changing owner size or offsets.
The 45-byte Overlay wrapper forwards into its real eight-byte Counter member.
At CORE/EXACT-103, Counter::add_reward was a genuine undefined production
interface. CORE/EXACT-104 now maintains its complete 90-byte threshold/modulo32
body and the actual Item owner/bulk-spawn caller; the primary gameplay spawn
remains undefined. See [Item ownership](ITEM_OWNER_RECONSTRUCTION.md).

## Semantic and exact gates

The actual production consumer scope exercises 256 real Shot slots, early,
late, duplicate, missing, zero and negative-bit-pattern identifiers; real Enemy
lists and detach behavior; observer cleanup; unsigned score overflow/cap and
Session record selection; changed/unchanged periodic gating; real region-to-shot
Context binding; forced defeat, multiplier and preserved-bit marker behavior;
and exact Overlay forwarding arguments. Private O2/ASan/UBSan execution passes.
The public test runs O2/UBSan against maintained source and temporary binaries.

ECL construction/destruction and process startup remain explicit fixtures.
Original Player/Overlay destruction and activation fixture definitions abort
if reached. Reward capture implements only the undefined Counter boundary;
it does not claim original Item spawning. Real owner constructors, member
storage, lookup loops, score accounting and flag updates execute unchanged.

The frozen 251-file graph passes 731 canonical units across 142 objects and
138,358 disjoint compared bytes. Source mappings are 745; fourteen whole
nonexact methods remain. Authored coverage remains 84 functions/24,209 bytes;
reference absorption remains 238, all 6,945 reference reviews remain terminal,
and claims remain header-only. Authored/compiler origin is still separate.

## Whole-query and remaining boundaries

The complete natural private query candidate emits 1,685/native1,707 bytes.
It is excluded from maintained source, mapping and semantic/exact acceptance.
No inert visit counter reproduces the native unused stores. Its three grouping
arrays have four slots, callback table has three entries, target is a genuine
EnemyHandle and reward lookup uses the actual EnemyController. Preview,
replacement-before-deduplication, forced-defeat bypass, retirement-before-later
reads, callback override, midpoint, double cap lookup and signed score input
ordering remain native observations requiring complete caller validation.

Heap-backed DamageRegion retirement releases the object before later native
reads; the valid lifetime/allocation domain remains unresolved. Pooled storage
lifetime does not establish heap validity. Original hit callbacks, Item spawning,
Player/Overlay/ANM owner lifetime, RTTI/full-link resolution, whole query and
playable game startup/runtime remain open. Existing private native exports,
original receipt/input archives and failed emission observations are preserved.
