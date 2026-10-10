# Actual process Session and player-table reconstruction

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-073 closes the complete Session storage and construction protocol used by
the Enemy variable readers. Twenty whole contributions add 1,167 instruction
bytes and 1,177 comparison bytes. The maintained definition owns two real
Contexts and two existing PlayerRecord values; it also supplies the actual
process global, its compiler-generated initializer and the native lookup
partitions. The two whole Enemy readers remain pending.

## Storage and independent type evidence

The original initializer at `401180` calls the Session constructor on `5BA568`.
Its independent CRT table entry is at `56C3CC`. The installed compiler emits a
704-byte BSS contribution and a four-byte `.CRT$XCU` relocation to the same
complete initializer. The native Session range lies in the PE data section's
zero-filled virtual tail, beyond its file-backed data; it is not a raw-file byte
array. Complete game linking and overall CRT initialization order remain open.

| Actual Session storage | Offset | Evidence |
| --- | ---: | --- |
| Two Context values | 00 | Constructor passes stride48/count2/real `423320` to `40BC20` |
| Paired 64-bit value | 60 | Constructor performs the paired integer zero stores |
| Scalar and flag aggregate | 68 /6C | Constructor, two independent low-bit setters |
| Five independent scalar words | 70..80 | Complete native constructor assignments |
| Actual PlayerTable | 88 | Member constructor `422F20`, getters and indexed PlayerRecord access |
| Double clock value | 2B0 | Constructor, independent clock storage and double subtraction |
| Two final scalar words | 2B8 /2BC | Constructor defaults0/1 |

PlayerTable has two 240-byte PlayerRecord values, three words at `1E0..1E8`,
fourteen more words through `220`, and natural eight-byte alignment. Neither
the gap at Session `84..87` nor the table tail `224..227` is represented by
invented padding. Existing PlayerRecord alignment supplies both gaps. Record
gaps at `A6/A7` and `B1..B3` also remain untouched by construction.

The constructor's `MOVSD` alone was insufficient to establish the clock type.
Original loading code at `4BBCFD` supplies the actual Session to `4BD6E0`;
that complete native member stores the returned clock with `FSTP double` at
`+2B0`. The separate `4BCE10` statistics path uses `SUBSD`, comparison and double
arithmetic on the same member. These native bodies are retained as type evidence,
without claiming their implementations exact.

Original names, several scalar roles/signedness choices and original source
declarations remain unknown. The neutral offset names preserve those limits.
The queried table mode is `PlayerTable::field_1e0`, distinct from Session's
separate word at `70`. Context's `24` slot now has the actual PlayerRecord pointer
type; its 17-byte getter folds with existing native code and receives no new
byte credit. Unknown entity pointers remain unresolved in Context.

## Complete contributions

| Contribution | Native address | Body /comparison bytes |
| --- | ---: | ---: |
| Session construction | 422E40 | 214 /219 |
| PlayerTable construction | 422F20 | 298 /303 |
| Process Session initializer | 401180 | 16 /16 |
| Session indexed Context | 40BBC0 | 20 /20 |
| Session PlayerTable query | 4989F0 | 19 /19 |
| Process PlayerTable query | 498F40 | 15 /15 |
| PlayerTable indexed record | 488720 | 23 /23 |
| Table mode and Session forwarder | 4640C0 /4640A0 | 20 /25 |
| Table mutating clamps | 4994D0 /499480 /499580 | 73 each |
| Session clamp forwarders | 499330 /499460 | 25 each |
| Process EnemyController lookup | 478060 | 26 /26 |
| Process selected PlayerRecord lookup | 464080 | 26 /26 |
| Add continue count | 4BCCF0 | 87 /87 |
| Session increment forwarder | 4BCCC0 | 35 /35 |
| Two low flag-bit setters | 4BE220 /4BDD60 | 36 /38 |

Both constructors include their five natural compiler INT3 bytes in strict
comparison. Each complete 29-byte EH handler and 36-byte FuncInfo matches the
independently verified common native handler at `567600`, information at
`5A91B8`, zero unwind state and nonthrowing flag5. The real array-construction
helper also matches all56 bytes at `40BC20`. No helper, EH or folded getter adds
duplicate coverage.

The indexed Session query physically folds with the complete 20-byte
`std::array<std::recursive_mutex,22>::operator[]` used by the maintained
LockRegistry. Its fresh canonical object independently replays the same native
address without relocations. This closes the reference slot association's
second contribution without identifying one unique original type at that
shared address or adding duplicate coverage.

The native constructors call child constructors directly through the array
helper and real PlayerTable member. Declaring the two allocation-free outer
constructors nonthrowing reproduces their EH contract. The initial throwing
declarations emitted172/256 bytes and are retained as failed private hypotheses.
The final candidate profile remains `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc`; it is not a claim about every original translation unit.

The two flag updates use actual bitfields in a four-byte aggregate. An earlier
mask expression preserved behavior but differed in register/order emission;
the natural bitfield members reproduce the complete original stores. Continue
addition deliberately wraps in unsigned32-bit arithmetic before interpreting
the result as signed and clamping to0..9. The native store occurs before its
reference-returning clamp call. No undefined signed overflow is needed.

## Semantic scope and remaining owners

The owned O2/UBSan test runs production global initialization, dirty guarded
Session construction, both record defaults and all natural alignment gaps.
It checks real Context/record aliases, nullable current-record selection,
independent two-player Controller pointer lookup, nonmutating mode queries,
all three clamp boundaries and full-object preservation. Continue cases cover
signed extremes and modulo32 overflow; flag cases verify truncation and retained
upper bits. Controller identity tokens are explicit borrowed test boundaries
and are never dereferenced or substituted for actual Controller construction.

Source ownership and exactness do not establish a playable game. Player entity,
primary game/frame owner, card owner, complete Controller searches/range
iteration, process clock/statistics behavior, all production entity factories
and whole-game link/runtime remain open. The reference's merged tagged reader,
checked Movement indexing and altered null/error policies are not imported.
Both whole reader CFG/table audits from EXACT-072 remain authoritative; their
full source and strict comparison are the next work, with actual owner protocols
closed as needed. The 41 KB Enemy opcode root also remains open.

## Verified checkpoint

The frozen source graph passes all 560 strict comparisons across 101 fresh
objects, covering 98,007 disjoint comparison bytes. Origin review remains
487 pending /9 library /64 authored, with 16,948 authored bytes unchanged.
Eleven complete reference associations close; all 6,945 indexed reviews remain
terminal, with 177 absorbed. No authored origin follows from this byte match.

Private complete replay is stored compressed from the outset at
`.analysis/exact073-canonical-results.json.gz`; the constructor/EH/CRT/BSS audit
is `.analysis/core073-audit.py`, with results in `.analysis/core073-support.json`.
Configuration and registration writers are completed one-time operations and
must never be rerun. Public semantic verification and protected cleanup are
recorded in the current handoff: all 45 public tests pass, eight obsolete probe
products are retired and two inactive successful snapshots are losslessly
archived. All 202 current canonical hashes remain unchanged. No additional
unchanged cold build is needed for cleanup or documentation.
