# Front dialogue field views — 19B and 20B strict-exact leaves

Two native accessors used by the FrontInf dialogue-command path are now
reconstructed as narrow, non-owning C++ views. Neither view asserts the
original source class name or ownership of the containing object.

| Native entry | Meaning | Result |
| --- | --- | ---: |
| `0x004B8090` | `SoundInf` queued-track name at `this + 0x2444` | **19/19** |
| `0x004B8270` | borrowed `AnimationFile*` at `FrontInf + 0x170` | **20/20** |

Source: `src/FrontDialogueFieldViews.hpp` and
`src/FrontDialogueFieldViews.cpp`. Both methods are ordinary field accessors,
with no relocations, assembly, padding or extra data. They are cold-built in
one canonical MSVC i386 object and replayed as two independent strict units.

The getters are dependencies of the original 626-byte FrontInf dialogue
command at `0x004B9740`; that parent and its special stage-transition branch
remain open and NONEXACT.
