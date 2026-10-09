# Damage controller and whole query evidence

## CORE/EXACT-100 dependency update

The actual HitCtrlInf pool/heap lifecycle and complete find/update/destruction
are maintained and exact after CORE098/099. Actual Bomb Context lookup,
event dispatch, lifetime and publication now also have complete canonical
source. These supersede the historical missing-owner statements below. See
[hit lifecycle](HIT_CONTROLLER_LIFECYCLE_RECONSTRUCTION.md),
[core dispatch](CORE_ITERATION_EXACT_RECONSTRUCTION.md) and
[Bomb ownership](BOMB_OWNER_RECONSTRUCTION.md).

The full 1,707-byte query remains unimplemented. Original Player, damage-cap
producers, item/reward/callback bodies and allocation-dependent region reads
remain open. Closing actual Bomb dependencies does not establish query
acceptance or game startup/runtime. Historical private input files and receipts
have been archived before retiring their obsolete objects; completed trial
recipes must use their SHA-bound archived inputs rather than current headers.

## CORE/EXACT-097 scheduler ownership update

The actual 56-byte FunctionChainController and all four registration entries
now have maintained source. Complete update/draw, insertion and removal
protocols run against shared node/list/lock/allocator owners. Independent native
deleting destruction identifies the existing 41-byte callback-clear root as
ordinary FunctionChainNode destruction; the source now owns that lifetime.
Locked removal and disabled-update registration used by HitCtrlInf are complete
canonical exact functions. See [scheduler protocol](FUNCTION_CHAIN_CONTROLLER_RECONSTRUCTION.md).
Earlier statements below that scheduler registration/destruction lacks source
are historical. HitCtrlInf itself still needs actual initialization, region
disposal and complete owner/query admission; scheduler source alone adds no
HitCtrlInf canonical or runtime credit.

CORE096 investigates the actual HitCtrlInf owner and the complete damage query
at 0x004C0480. It follows the existing DamageRegion collision, lifetime,
intrusive observation, TaskInfo and Session protocols. This is a private
reconstruction checkpoint; production and canonical coverage remain unchanged.

## Whole query boundary and dependencies

An attested Ghidra export and independent decoding of the approved executable
cover all 1,707 bytes, 454 instructions and the final `ret 0x20`. Every direct
internal branch lands on a decoded instruction, with no external branch.
There are 65 direct calls to 33 distinct physical heads, plus an indexed
callback call. Eight stack arguments carry position, optional dimensions,
angle, radius, optional hit flag/position, preview and a four-byte identifier.
Source-level pointer versus reference spelling remains separate from this ABI.

The query gates on player-frame change, includes bomb damage, traverses actual
intrusive observations and filters region period, cooldown, damage and geometry.
Group replacement subtracts the previous effective contribution before target
deduplication. Target marking and enemy flag side effects precede damage
accumulation. Retirement at the configured damage limit precedes subsequent
region reads; allocation/lifetime domains must therefore be established before
claiming a complete active-query semantic oracle. Preview suppresses accumulation
and hit callback execution. Final player damage cap can be queried twice, and
non-preview nonzero totals update score after signed division by ten.

Three stack arrays each initialize four integer slots. Native address biases
map positive groups 1–4 into those four slots; the reference's five-element
arrays do not establish the original declaration or exact emission. Native also
increments a local visit counter without reading it later. No inert source
counter has been added to reproduce that emission.

The callback table at 0x00570C78 contains exactly three observed entries: null,
0x004BFCD0 and 0x004BFD60. The next word at 0x00570C84 is the HitCtrlInf RTTI
complete-object-locator pointer, not a fourth callback. Active valid callback
indices 1 and 2 and the original unchecked indexing remain distinct facts.

Context's physical +4 getter shares the Timer current-word head at 0x0040FF90;
this use is not evidence that the returned player object is a Timer or the
Context's +0 BulletController slot. Bomb, Player, item/reward, score, active
callback bodies and full query source remain dependencies. Existing canonical
geometry/math/identifier/observer heads supply reusable physical anchors.

## Independently established owner

The constructor writes vtable 0x00570C88. Its complete-object locator and base
descriptors identify `HitCtrlInf` with the actual `TaskInf` base at offset zero.
The three virtual slots are deleting destructor 0x004C0290 and inherited
enable/disable 0x00421680/0x00421760. Constructor diagnostics independently supply
the exact `initialize HitCtrlInf` string and newline.

| Offset | Actual storage |
| --- | --- |
| 0x0000 | 16-byte TaskInfo base |
| 0x0010 | 256 actual 196-byte DamageRegion objects |
| 0xC410 | Next identifier word |
| 0xC414 | 24-byte active intrusive list |
| 0xC42C | 24-byte free intrusive list |
| 0xC444 | Visited-region count |
| 0xC448 | Actual 16-byte Timer |
| 0xC458 | View index |
| 0xC45C | Context pointer |

Whole native extent is 0xC460. Independent array construction passes count 256,
stride 196 and the established nonthrowing DamageRegion constructor to the
actual vector construction helper. The private natural `std::array` hypothesis
reproduces this entire construction contribution; original template spelling
remains an inference. It introduces no raw clear, replacement child constructor
or array-size adjustment.

## Complete private compiler results

Fresh locked MSVC x86 compilation with /Od, /Ob0, /GS, /Gy, /Zl, /arch:SSE2,
/fp:precise, /sdl and /EHsc strictly replays these whole contributions:

| Operation | Address | Body bytes | Compared bytes |
| --- | --- | ---: | ---: |
| Typed 256-region array construction | 0x004BFE80 | 81 | 86 |
| HitCtrlInf construction | 0x004BFEE0 | 191 | 196 |
| Context selection | 0x004C2090 | 54 | 54 |
| Identifier advance | 0x004C0C60 | 67 | 67 |
| Owner detach/free-list return | 0x004C1EB0 | 70 | 70 |

All 473 comparison bytes include both five-byte compiler alignment tails.
Relocations use independently exported functions, established canonical heads,
constructor-written RTTI and complete NUL-terminated literal identity. Both
complete 29-byte constructor handlers and 36-byte zero-state flags-5 FuncInfo
records also replay. The entire 49-byte deleting destructor replays as support,
including its native sized-delete call and full 0xC460 size. These support
results do not close the undefined ordinary destructor.

The complete private find, update and allocation bodies remain respectively
261/native 264, 243/native 248 and 265/native 225. Cached list endpoints improve
the first two over the earlier 254/237-byte experiments, but do not close native
iterator auto-initialization or all call/temporary partitioning. Allocation
still needs the real front/region-context member partition and independently
accepted factory pre-clear. The existing factory template is shared unchanged;
no replacement allocator, artificial iterator constructor or fabricated clear
has been introduced. Native allocation has no newly invented failure return.

No production unit, authored credit, reference absorption, active-query semantic
acceptance or playable-game claim is added. Private source and receipts remain
under `.analysis/` and `build/`. Preserve the V2 probe and its original inputs
until callback registration/destruction, complete initialization and allocation
ownership are closed. Evidence is in core096-damage-query-audit.json,
core096-damage-rtti.json, the three attested native exports and
core096-whole-bindings.json. Completed proof writers must not rerun.
