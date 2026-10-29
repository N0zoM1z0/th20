# CORE/RECON-806 — complete 352-byte original Animation quad batch append strict exact

The real original **0x0043E9B0** whole 352-byte/98-x86 game renderer
appender is now strictly native exact as
`AnimationQuadSubmitOwner::append_quad(SpriteTexturedVertex*)` in
`src/AnimationQuadBatchAppend.cpp`, compiled by pinned MSVC x86. It
checks the genuine 28-byte vertex array capacity, copies six full
28-byte vertices using **six original `rep movsd` instructions**, advances
the stream pointer 168 bytes and increments the original queue count.
There are no physical original relocations within its 352-byte body,
and there is no second mapping or duplicate original game byte credit.

For the full original PE proof, intermediate natural C++ compiler
experiments, the independently 26/26-byte exact texture-state sibling,
real shared receiver and the accepted scoped replay, see
[CORE/RECON-806/807 — 352B+26B whole strict exact](ANIMATION_QUAD_BATCH_APPEND_352_AND_TEXTURE_PREPARE_26_EXACT.md).
The original **3,159-byte** rendering submission parent remains
**NONEXACT**, as does the separate **5,993-byte** draw dispatcher.
