# Animation Draw compiler and link-context controls

These controls address the missing first-result stores and scalar register
reloads in the 5,993B Draw at `0x00443880`, using the
[locked target](../config/target.toml) and MSVC 19.44.35211. The maintained
5,969B source and compiler profile remain unchanged.

## Retained target metadata

The original PE reports linker **14.44** and retains an RSDS record:

- GUID: `56A9F350-4047-4207-BB83-CBDE0DF5C5C8`, age **8**.
- PDB path: `D:\cygwin\home\zun\prog\th20\bin\Release\th20.pdb`.
- Vendor-reported feature counts `(Pre-VC++11, C/C++, GS, SDL, guardN)`:
  `(0, 437, 437, 103, 331)`.
- A `GCTL` COFF-group directory and an empty `iltcg` debug entry.

The feature counts are aggregate metadata and do not identify Draw's own
translation-unit flags. The 44 group records contain section names; Draw lies
inside `.text$mn` at `0x0040AF10`, length 1,426,912B. They do not supply local
variable names or a PDB's symbol/type information.

## Backend and compiler-version controls

[Microsoft's 2016 optimizer article](https://devblogs.microsoft.com/cppblog/new-code-optimizer/)
describes `/d2SSAOptimizer-` as an optimizer diagnostic switch. Passing it to
the locked compiler leaves all five reviewed `/Od` callers' complete COFF
bytes and relocation records unchanged. Bare discard remains `fstp st(0)`;
the saved-half addition remains memory-source.

The existing shared **19.10.25017** compiler was also tested with a header-free
C++14 fixture through TH20's Wine prefix. Direct and saved-half additions are
byte/relocation-identical to 19.44. Bare discard and the two sink callers differ
only by 19.44's extra final NOP: sizes 15/16B and 55/56B respectively. The older
compiler retains the same two unresolved instruction forms.

## Link-mode markers and actual IR code generation

A regular COFF object linked with `/LTCG:OFF /DEBUG` has a zero group signature
and no `iltcg` entry. Linking the same object with `/LTCG:INCREMENTAL` produces
`GCTL` and empty `iltcg`, while reporting **no code generation required**.
These markers can arise from the link mode alone; they do not show whether
Draw itself was compiled from `/GL` IR.

Actual `/GL` callers were then linked with incremental LTCG and one codegen
thread. Every byte of all five caller contributions matches ordinary COFF
after replaying relocations from the independent linker MAP: **16B discard,
51B direct addition, 57B saved-half addition, and two 56B sink callers**.

The real `animation_inherited_aux_scale_x` was supplied both as its accepted
ordinary COFF object and as freshly compiled IR. In both contexts, three
callers retain identical **16/51/57B** code after MAP replay. The getter's
complete **93B**, including its constant and recursive-call relocations, also
matches in both contexts. These are small compiler-context controls, not a
linked reconstruction of the complete Draw. They give no reason to change its
profile or introduce a new acceptance path.

Incremental LTCG rejected `/OPT:NOREF`; successful links use `/OPT:REF`.
The successful x86 DEF uses undecorated C export names; the prefixed alias
attempt failed. Installed CRT libraries supplied the security-check support.

Private evidence is under `.analysis/draw-boss-session/`:
`draw-compiler-context-controls.txt` contains complete comparisons and
independent MAP replays; `draw-target-debug-directory-headers.txt` retains the
vendor metadata output. The `draw-v141-*`, `draw-float-ltcg-*` and
`draw-real-getter-ltcg-*` build logs retain commands, versions, hashes and useful
failed attempts. Compiler payloads were reused in place; the locked profile,
target, public headers, canonical providers and exact claims are unchanged.
Affected exact replay scope is zero.

## Volatile access metadata distinguishes otherwise identical code

Draw's native volatile-access table lists only the GS cookie save at
`0x00443890` and reload at `0x00444FD9`. Neither first-getter m32 store
(`+0xFCD`, `+0x10BA`) nor any of the four saved-half reloads is listed.
The metadata range `0x00401000 + 0x13F65A` covers the complete Draw body.

The PE load-config directory advertises only `0x40` bytes, but its embedded
size is `0xC0`. The pinned SDK's `IMAGE_LOAD_CONFIG_DIRECTORY32` places
`VolatileMetadataPointer` at offset `0xA0`; its value is `0x005A6E14`.
The six-DWORD metadata header is
`(0x18, 0x80038003, 0x1A6E2C, 0x1F38, 0x1A8D64, 0x78)`:
the access table contains 1,998 instruction RVAs and the coverage table
contains 15 RVA/length pairs. Reading only the advertised directory size
would miss this evidence.

[Microsoft documents `/volatileMetadata`](https://learn.microsoft.com/en-us/cpp/build/reference/volatile?view=msvc-170)
as metadata for volatile accesses used by x86/x64 emulation on ARM64.
A locked-compiler control confirms which instructions the tables describe:

| Caller | Complete code | Marked instruction offsets |
| --- | ---: | --- |
| Discard first return, then return a second call | 23B | None |
| Store first return in a volatile float, then return a second call | 27B | `+0x0C`: `fstp m32` |
| Save a plain half, then add the getter result | 57B | None |
| Save a volatile half, then add the getter result | 57B | `+0x13`: `movss` store; `+0x28`: memory-source `addss` |

The two 57B callers have identical instruction bytes and relocation records;
their metadata distinguishes the accesses. Separate integer read/write
controls mark their actual memory instructions too. All six complete caller
contributions were independently replayed into a private DLL using its linker
MAP, including every call and constant relocation. That DLL has the same
metadata header size/version flags and covers all six functions.

Under this compiler model, explicit volatile storage would leave metadata
that is absent from the native writes and reloads. Volatile locals therefore
do not explain the missing instructions. Keep their ownership unresolved.

The fixture is `DrawVolatileMetadataControl.cpp`, with separate opaque getter
support. `draw-volatile-metadata-controls.txt` retains native table coordinates,
linked access offsets, complete MAP comparisons and object/source/include
hash checks under `.analysis/draw-boss-session/`. The private DLL and objects
remain under `build/gptweb-drawboss-session/`.

## Additional narrowing and optimization-boundary controls

Direct `static_cast<float>(double_getter()) + (height/native_two)` and its
subtract counterpart emit the same complete **51B** as their float-getter
counterparts, apart from the expected call symbol. The getter still precedes
the division. Earlier narrowed-wide controls used a named half; these new
direct expressions close that separate evaluation-order question.

Enabling `/fp:strict`, `float_control(except, on)` and `fenv_access(on)` together
leaves all nine reviewed narrowing callers' complete bytes and relocations
unchanged: two 16B discards, three 57B saved-half expressions and four 51B
direct expressions. Explicit narrowing with observable floating-point status
does not recover the native stores or register reloads in these controls.

A separate fixture compiled with global `/O2 /Ob0` and local
`#pragma optimize("", off)` matches all five ordinary `/Od` callers in full:
16/51/57/56/56B, including relocations. This optimization boundary supplies
no new full-Draw candidate. Sources are `DrawDirectNarrowedCall.cpp`,
`DrawNarrowedEnvironmentBoundary.cpp` and `DrawFloatPragmaOffBoundary.cpp`;
their comparisons and receipt hashes are also in
`draw-volatile-metadata-controls.txt`. Maintained native inputs and exact
claims remain unchanged; affected exact replay scope is zero.

Value-category controls also fail to recover the forms: discarded
`std::move`/`std::forward` results produce 31B callers with an extra scalar
copy, while moved/forwarded half expressions produce 67B callers and retain
memory-source arithmetic. Moving a named half leaves the ordinary 57B caller
unchanged. Complete code and relocations are retained in
`draw-value-category-controls.txt`; no full-Draw variant is warranted.
