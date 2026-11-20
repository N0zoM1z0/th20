# `Context::bullet_controller()` physical alias

`Context::bullet_controller()` at `0x0040C300` is a 16-byte natural C++
getter returning `primary_owner`. Its scoped MSVC x86 `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc` contribution structurally matches
all 16 native bytes with no relocations.

The same physical 16-byte body is already indexed as `Identifier32::get`;
the Context-specific source name is therefore documented as a source-level
alias, not added as a second `reccmp-functions.csv` mapping or duplicate byte
credit. The alias is useful
for native call-site reconstruction: the Line Laser `cancel_circle` handler
uses this accessor to obtain its owning BulletController before incrementing
`cancel_counter` and resolving the AnimationFile.
