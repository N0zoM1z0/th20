# ScalarMath acos/atan adapters — exact 35B leaves

The complete float-to-double CRT adapters at `0x00439760` and `0x00439790`
compute **acos and atan**, respectively. The earlier asin/acos labels and
canonical external bindings were incorrect. Independent complete archive
sections identify `_acos` at `0x0054FEB0` and `_atan` at `0x0054FF00`; see
[math dispatch evidence](CRT_MATH_DISPATCH_ORIGIN_BOUNDARY_REVIEW.md) and
[the binding correction](CRT_X87_CONTROL_TANGENT_ORIGIN_REVIEW.md).

| Original | Maintained function | External REL32 at `+0x12` | Unit |
| --- | --- | --- | --- |
| `0x00439760` | `scalar_math::arccosine(float)` | `_acos` at `0x0054FEB0` | `scalar_math_arccosine_35` |
| `0x00439790` | `scalar_math::arctangent_single(float)` | `_atan` at `0x0054FF00` | `scalar_math_arctangent_single_35` |

Both natural bodies in `src/ScalarMath.cpp` widen float to double, call the
standard function, narrow to float and return with the cdecl stack contract.
Fresh locked MSVC 19.44.35211 objects reproduce each complete **35/35-byte**
contribution, including all 31 ordinary bytes and the correctly named call.
Both passed the 84-unit affected replay after the shared-header correction.
The separate two-argument `arctangent(y,x)` continues to call atan2.
`square_root` continues to call true `_sqrt` at `0x00550050`.

Animation VM opcodes `0x21` and `0x22` now call these correct owners. Its
compiled complete contribution is unchanged after the two symbol substitutions;
the VM remains NONEXACT. Names here are maintained semantic labels. The two
adapter origins remain unknown/review and receive no authored exact credit.
