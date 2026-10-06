# Source and build ownership

There are no reconstructed production translation units at the bootstrap
checkpoint. `src/` is reserved for canonical shared C/C++ source. `probes/`
contains infrastructure-only compiler inputs, which are excluded from mapping,
source-present and exact ledgers.

`config/match-units.toml` will own each canonical source/object/profile and
compared function. One output must have one source/profile, and a source must
have one canonical profile. Compiler EH helpers, CRT/library contributions,
static initializers, switch tables and global storage require their own origin
and ownership review. Do not assign authored credit to them automatically.

A production source should name its target-local evidence and be represented
in this map when accepted. Whole-game compile/link/runtime products will be
added only after a real production graph exists; the toolchain smoke console
executable is not that graph.
