# ScalarMath arcsine/arccosine CRT adapters — exact 35B leaves

The original functions at `0x00439760` and `0x00439790` are complete 35-byte
x86 cdecl wrappers. Each converts its incoming `float` to `double`, calls the
corresponding CRT math entry, narrows the returned value back to `float`, and
returns with the ordinary caller-cleaned stack.

- `0x00439760`: `std::asin(static_cast<double>(value))`, one `REL32` at `+0x12`
  to the original `_asin` import at `0x0054FEB0`.
- `0x00439790`: `std::acos(static_cast<double>(value))`, one `REL32` at `+0x12`
  to the original `_acos` import at `0x0054FF00`.

`th20::scalar_math::arcsine` and `arccosine` in `src/ScalarMath.cpp` reproduce
all 31 ordinary bytes and the one relocation for each complete function.
Both isolated C++20 MSVC object contributions replay **35/35 bytes**. The
existing sine/cosine wrappers at `0x00439820`/`0x004397C0` are the same
35-byte float/double CRT adapter family. The four VM trigonometric opcodes
now call these natural cdecl owners directly; the unused dummy ECX receiver
and numeric member-call adapters are gone.

The names are semantic source labels, not recovered original identifiers.
These wrappers may be CRT/compiler/library glue; origin remains unknown and
no game-authored byte credit is claimed. This is leaf exactness only and does
not make the enclosing `Animation::update` Boss exact.
