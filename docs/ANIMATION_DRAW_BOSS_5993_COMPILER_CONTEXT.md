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
