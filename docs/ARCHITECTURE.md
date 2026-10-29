# Target architecture and reconstruction boundaries

The executable identity is pinned in [target provenance](TARGET_PROVENANCE.md)
and `config/target.toml`. Current acceptance is in [the handoff](RE_HANDOFF.md);
dated investigations are indexed in [evidence](EVIDENCE_INDEX.md).

## Native executable

| Property | Observed value |
| --- | --- |
| Format | PE32 / i386 / Windows GUI |
| Image base | `0x00400000` |
| Entry point | `0x005435E0` |
| Image size | `0x001F9000` (2,068,480 bytes) |
| Mapped .text virtual interval | `0x00401000..0x0056B47A` inclusive |
| Linker generation | 14.44 |
| Rich header | Absent in game; present in companion custom.exe |
| Sections | .text, .rdata, .data, .fptable, .rsrc, .reloc |

Imports establish Win32, DirectInput, DirectSound, Direct3D9/D3DX, XInput, WinMM,
COM and GDI+ dependencies. A CodeView path ends in `bin/Release/th20.pdb`; source
strings name `src/game`, `src/pack` and `src/script`. These are discovery evidence,
not proof of optimization flags or subsystem ownership.

## Maintained owner graph

The source uses canonical typed owners rather than method-only facades. Storage,
construction, destruction, resource interfaces and emitted code have independent
acceptance boundaries; a complete declaration may still have undefined methods.

| Area | Established structure | Remaining integration boundary |
| --- | --- | --- |
| Animation | Base 0x4C0, Animation 0x5E4, pooled record 0x600; complete 65,536-record pool lifetime, real values/links/vertices, descriptors/binding, template lifetime and File destruction | Whole VM, Renderer and loaded-File/buffer clearing |
| Animation callbacks | Eight-byte base, five virtual slots; cdecl entry/script callbacks | Remaining concrete owners, lambda adapters and native RTTI name identity |
| ECL | Runtime 72, Manager 112, Loader 564; actual stack/frame/async and indexed selection, whole Runtime tick, buffer registration and instruction resolution | Full resource/startup graph and whole-program linkage |
| Enemy | Actual EnemyState/Enemy, movement, parameters, handles and whole defeat; independently identified 0xB4 StoneEnemyController | Whole 0x48C010 dispatcher, queue/factory emission and resource/VM integration |
| Scheduler | Actual controller/nodes, observed lists, sorted registration/dispatch and scalar allocation/release | Unlocked removal emission and process-global startup |
| Player/Bomb/Bullet/Item/Hit | Typed ownership, pools, Context publication, SHT/damage consumers, Hit allocation/lifecycle and Item spawning | Whole damage query, full gameplay, resource callbacks and remaining controller factories |
| Archive/File/Progress | Real PMR/heap ownership, cipher/LZSS, file I/O, typed records, load/parse/serialization and destruction; **whole original 1,036B compressor and 706B decoder are already strict exact** | Remaining File write/SaveManager emission, integration and startup |
| Graphics/mesh | Actual Graphics, device/format accessors, RenderMesh, owned mesh allocation/retirement, surface/geometry records and two-bit flag view | Renderer declaration, mesh creation, full rendering and resource integration |
| Sound | Actual SoundInf storage and loading/preload protocol | Whole dispatcher, startup and resource-owning retirement |
| Platform/UI | Verified window/input/value/menu components; complete FrontInf, AsciiInf and Dialogue storage/construction, real ready/callback routing and Laser cancellation receiver | Native Dialogue/HUD/text resource retirement and frame execution, follow-box geometry, complete scene owners, OS resources and global initialization |

Animation +568 points to the actual virtual callback base. +5DC is an
`AnimationEntryCallback`; +5E0 is an `AnimationScriptCallback`. +5C8 is generic
`void* user_data`, because native producers publish different real owners.
The two parent pointers +558/+55C serve distinct operations. Vertex storage has
independently established 20-, 24- and 28-byte layouts; they are not interchangeable.
See [source ownership](SOURCE_MAP.md) for maintained files and focused evidence.

## Whole-function frontier

The original **39,470-byte Animation VM at 0x0042B5D0** and separate
**41,967-byte Enemy opcode dispatcher at 0x0048C010** remain open.
The 12,140B Bullet command parent at 0x0047DCF0 is also source-absent
NONEXACT, despite 203/210 native original E8s targeting existing canonical
heads and verified 34+8+11 switch pointers. The original **3,735B Bullet
emitter is already whole strict exact**; its earlier one-instruction
compiler frontier was superseded.

The independent ECL Runtime tick at 0x0053B5C0 is accepted with its complete
11,504-byte compiler contribution (11,110B game-body coverage), including
alignment and its 98-entry switch table. Exact callees do not establish
exactness of an unimplemented whole parent. Refer to the [current handoff](RE_HANDOFF.md)
and [original Bullet E8 map](BULLET_12140_E8_203_7_SOURCE_CLOSURE.md).

The Renderer allocation and still-unresolved original
Renderer+0x6000DFC..0x6000DFF field are documented in the focused
[Animation pool lifetime proof](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md)
and [native knowledge base](KNOWLEDGE_BASE.md), not necessarily repeated in
the short current handoff. Do not invent an owner field or padding from
negative searches. Ghidra function bodies can omit valid listing
instructions; only the complete original PE control flow/tables establish
whole native extents.

No whole-game compile/link or playable reconstruction is available. Test fixtures
exercise maintained owners with explicit unresolved boundaries; they do not
replace original startup, resource lifetimes or runtime execution.
