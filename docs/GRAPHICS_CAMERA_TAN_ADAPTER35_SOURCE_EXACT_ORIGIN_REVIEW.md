# Graphics camera tangent adapter 35B — source exact, origin review

The complete 35-byte adapter at `0x00439850` converts float to double, calls
**tan**, narrows the result to float and returns through x87. Its thirteen x86
instructions have SHA-256
`883a31db55344f543fa8f0c7823bf4aa241c5e0db38e7dac33a591917ce25f7a`.
The single E8 at `+0x11` calls `0x00550000`; there are no PE HIGHLOW fields.

The earlier sqrt interpretation was wrong. The complete CRT dispatcher,
FPTAN fallback, SSE kernel and tangent table independently identify this callee
as `_tan`; true `_sqrt` is at `0x00550050`. See
[the complete CRT review and affected validation](CRT_X87_CONTROL_TANGENT_ORIGIN_REVIEW.md).
Ordinary bytes of these float adapters are identical across math operations,
so the earlier wrong-symbol source could pass a comparison with a wrong binding.
Its retained object is now a negative case for the tangent verifier.

`src/GraphicsCameraTanAdapter35.cpp` maintains one natural `std::tan(double)`
body. Locked MSVC 19.44.35211 x86 C++20 with
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` emits the complete
**35/35 bytes**, including all 31 ordinary bytes and the `_tan` relocation at
`+0x12`. Unit `graphics_camera_tan_adapter_35` and the distinct 846-byte camera
both passed the captured 84-unit strict replay. The camera computes half-height
divided by tan(FOV/2); Animation VM opcode `0x20` uses the same adapter.

The adapter is standard math/compiler-like glue, with authorship still unknown.
It remains origin=unknown, disposition=review, and absent from `matches.csv`.
The camera owns only its own 846 bytes. No new authored exact credit is added.

For a future change to this adapter alone:

```bash
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/GraphicsCameraTanAdapter35.cpp
scripts/repo-python scripts/verify-graphics-camera-tan35-native.py
```
