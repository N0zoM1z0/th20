# CORE/EXACT-383 — complete ProgressSaveManager Worker lifecycle and copy/merge methods

Comparison original: immutable Japanese TH20 v1.00a Steamless game
`resources/th20.exe`, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The actual game-owned `ProgressSaveManager` is a real 0x1242D8-byte
class containing current/backup `ProgressSnapshot` records,
a 64-byte zero-initialized interval and a live `Worker` at
offset `0x1242C4`. Two previously nonexact whole native
functions are now genuinely reconstructed to complete exact code,
and two other existing canonical-exact members have been independently
attributed to this game-owned class. The total newly authored-credit
amount is **451 unique original bytes across four separate original
function addresses**, with *two newly added strict native units*.

| Entire original native function | Original entry | Native body | Original x86 instructions | Original E8 / PE HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `ProgressSaveManager::ProgressSaveManager` | `0x0050E5D0` | **199B** | **55** | **6 / 3** |
| `ProgressSaveManager::commit` | `0x0050F660` | **70B** | **24** | **2 / 1** |
| `ProgressSaveManager::copy_current_to_backup` | `0x0050EEB0` | **75B** | **26** | **2 / 0** |
| `ProgressSaveManager::merge_current` | `0x0050F5F0` | **107B** | **35** | **4 / 0** |

The destructor at `0x0050E990` was **already separately authored-exact**
with **299 native body bytes / 304 compared bytes** including trailing
padding; it was explicitly reverified but receives **zero new credit**.
The entire five-member currently authored save-manager lifecycle
therefore totals **750 different physical native function bytes**.
This does **not** close separate save-file parsing, worker callbacks
or full runtime disk I/O.

## Two newly completed Worker/ProgressSnapshot C++ functions

The **entire 199-byte original constructor** automatically
constructs the real `current` and `backup` Snapshot members (each
0x92140 bytes), sets the scalar word at `+0x124280` and zeros all
64 bytes starting `+0x124284`, constructs the Worker, completes a
native `Worker::close_and_join()` operation, and starts the real
`ProgressSaveManager::load` member task. The native locked MSVC
C++20 profile is `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/EHsc /Gd`, including real SEH and security-cookie handling.

The previous production constructor naturally emitted **198B and
54 instructions**, with one missing original NOP after a
`Worker::close_and_join` call at original `+0x80`. Putting the
**real side-effecting operation** in its own ordinary C++ lexical
scope naturally emits the original `nop` at `+0x84`, giving
**199/199 original bytes and 55/55 original instructions**.

The **entire 70-byte original `commit()`** also calls the native
Worker close/join, then asynchronously starts the real
`ProgressSaveManager::save` member function and returns integer
zero. The old maintained method compiled **68B / 22 instructions**.
Real lexical scopes around **both** the close/join call and
the separate Worker::start call naturally preserve the original
two compiler NOPs at `+0x17` and `+0x3F`. This yields
**70/70 original bytes and all 24 native instructions**,
without manually inserted NOPs, fabricated extra locals, synthetic
return state or shortened comparison.

Both full methods are maintained in the existing
`src/ProgressSaveManager.cpp` source and one original canonical
owner `build/core164-canonical/ProgressSaveManager.obj`. The method
bodies, return register/hidden ABI, member pointer, request arguments,
SEH and all native offsets remain fully typed.

## Independent immutable PE references and old member ownership

A fresh 199/70/75/107-byte original PE decode independently
extracted every native E8 direct-call operand, as well as every
real HIGHLOW site in the original PE `.reloc` table.

For the 199-byte constructor the nine native references include
the real EH handler at `0x0056A923`, security cookie
`0x005B25C0`, two original
`ProgressSnapshot::ProgressSnapshot` calls at `0x0050E540`,
original `memset` at `0x00544760`, native
`Worker::Worker` at `0x0040B780`, native close/join at
`0x0040BCF0`, the real load member callback at
`0x0050F3B0` and the member-worker start at `0x0050AB10`.

The 70-byte commit's two native E8 calls are independently
`Worker::close_and_join` and `Worker::start`, while its
single PE HIGHLOW field binds the actual save member
`ProgressSaveManager::save` at `0x0050FB60`.

The independent 75-byte backup copy and 107-byte merge functions
preserve all actual `memcpy` source/destination addresses and
the real `ProgressSaveManager::parse` and backup publication
calls. Their original 2 and 4 E8 fields are strict exact.
Their whole C++ and canonical source already existed before this
turn; only their source ownership rows had incorrectly remained
`unknown/review`. All **18 original native E8/HIGHLOW fields across
these four bodies** were independently rescanned, matched to
current locked COFF offsets/types and actual original targets
before canonical promotion. Full private original audit:
`.analysis/core383-progress-manager-original-proof.json`.

## Focused strict replay and explicit accounting

The **only changed code provider** is the original existing
`src/ProgressSaveManager.cpp`. No shared header, class layout or
other exact source provider was changed. The true native
comparison now accepts:

- **199B constructor**: new canonical unit
  `progress_save_manager_ctor` from CORE/EXACT-382
- **70B commit**: new canonical unit
  `progress_save_manager_commit` from CORE/EXACT-383
- **75B copy and 107B merge**: *existing* canonical units,
  now separately reattributed as authored game operations
- **299B destructor**: preexisting authored canonical unit,
  freshly reverified and explicitly **not** counted twice

All **5/5 complete source-owner strict units in one cold rebuilt
object** pass, including **299B/304B full destructor body/padding**
and all real native relocation targets. Private replay log:
`.analysis/core383-progress-manager-replay.log`. No unfiltered
whole-repository cold replay was run. The origin/ledger change is
**four newly credited native game-function intervals, 451B total**,
with **two new actual codegen closures totaling 269B** and
two origin corrections totaling 182B.

The separate original file parser, async thread lifetime in a
running game, archive encoding, startup globals, and executable
linkage remain independently open.
