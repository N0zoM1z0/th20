# Target inventory and initial architecture boundary

The canonical executable is the user-selected Japanese TH20 v1.00a Steamless
variant. Exact release/provenance is in `TARGET_PROVENANCE.md`; machine and
section details are pinned in `config/target.toml`.

| Property | Observed |
| --- | --- |
| Format | PE32 / i386 / Windows GUI |
| Image base | `0x00400000` |
| Entry point | `0x005435E0` |
| Image size | `0x001F9000` (2,068,480 bytes) |
| `.text` virtual extent | `0x00401000..0x0056B47A` inclusive |
| Linker | 14.44 |
| Rich header | absent in game; present in companion `custom.exe` |
| Base relocations | present |
| Sections | `.text`, `.rdata`, `.data`, `.fptable`, `.rsrc`, `.reloc` |

Target-observed imports cover KERNEL32, USER32, GDI32, ole32, OLEAUT32,
DINPUT8, DSOUND, d3d9, d3dx9_43, WINMM, XINPUT1_4 and gdiplus. These establish
API dependencies, not ownership of specific game subsystems.

The target contains a CodeView/PDB path ending in `bin/Release/th20.pdb`,
plus authored source-path strings under `src/game`, `src/pack` and `src/script`.
Those strings can route owner discovery; a `Release` path does not prove
optimization flags. Preserve the original Japanese semantics and source
provenance where independently corroborated.

Ghidra's initial import exports 6,928 provisional function candidates. All
origins remain unknown and all boundaries remain unreviewed. Do not inherit
TH095's engine roles or authorship classifications from similar function names.
Private architecture metrics/call edges/global and string references are
exported under `.analysis/architecture/`; they rank leads, not completeness.

The state model follows TH095: candidate boundary (`functions.csv`), origin
(`function-origins.csv`), mapping (`reccmp-functions.csv`), source presence
(`implemented.csv`), and exactness (`matches.csv` plus canonical units) are
separate. Semantic acceptance, whole-game linkage and playable behavior are
also independent.

The shared menu Cursor uses a PMR vector and two standard stack/deque owners.
Native constructor, iterator and stack adapter graphs establish its storage and
resource ownership. Eight methods are exact; constructor exception emission is
still unresolved. The separate four-byte PauseFlags value is exact without
introducing an enclosing menu facade. These additions remain component objects,
with no complete menu or original allocator/runtime linkage claim.

Progress and Replay share actual disk-value protocols and Replay input history.
Four small constructors and two members on the existing InputButtonState are
complete exact contributions. They do not close the reference's raw giant disk
owners, original thread/file/allocator lifetimes or full Replay integration.
Native intrusive-template/std::array ownership and full-int append ABI differ
from the reference helpers and remain explicitly recorded for further recovery.
