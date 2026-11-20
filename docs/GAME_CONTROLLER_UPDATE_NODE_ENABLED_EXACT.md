# GameController update-node enable gate — exact reconstruction

Two adjacent native leaves are now reconstructed and cold-replayed as natural
C++ methods:

- `FunctionChainNode::enabled()` at `0x00464390`, 22 bytes. It returns bit 1
  of the node's flags word at `+0x4`.
- `GameController::update_node_enabled()` at `0x00464350`, 56 bytes. It
  checks the inherited `TaskInfo::update_node` pointer and calls the first
  method, returning an integer 1/0 through the native local-result path.

The first function matches 22/22 bytes with no relocations. The second matches
52/52 non-relocation bytes; its sole REL32 at `+0x20` resolves to
`0x00464390`. Both use the scoped MSVC x86 `/Od /Ob0 /GS-` profile and are
independently admitted as exact units. Their provenance remains unknown; no
extra authored-origin credit is claimed.

The 1,018-byte WeaponStone update calls the GameController wrapper at its
original native call site rather than inlining a source-only duplicate of the
flag test.
