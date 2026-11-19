# Animation VM XY polar output helper — exact 88B leaf

The original helper at `0x004392D0` is an 88-byte x86 routine that writes two
independent float destinations:

- `*x = cos(direction) * length`
- `*y = sin(direction) * length`

The original call supplies four ordinary stack arguments and also places the
Animation pointer in ECX. The complete callee body never reads ECX and returns
with plain `ret`, leaving all four stack arguments for the caller to clean.
The natural C++ cdecl helper `th20::polar_components` therefore models the
actual data protocol directly without inventing an unused member receiver.

Its pinned MSVC x86 C++20 contribution is **88/88 bytes**, with the two
original `REL32` calls preserved at offsets `+0x12` and `+0x39`: the native
float cosine wrapper at `0x004371D0` and float sine wrapper at `0x00439530`.
The VM's opcode 0x24 now calls this typed helper directly with the two
independently resolved script-variable output pointers.

The name is a semantic source label; the original source spelling and
application-vs-library origin remain unknown. No authored-origin credit is
claimed, and this leaf does not make the enclosing Animation VM exact.
