# CRT optional Win32 API initialization and system-time fallback

The 80-byte system-time wrapper at `0x0054242B` has a reviewed library origin.
Its missing 52-byte initializer at `0x005423F7` is now inventoried and classified
as library code. Complete `winapisupp.obj` contributions preserve five alignment
bytes, the existing shared 29-byte handler and its full 36-byte EH record.
The target remains Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Code bytes | Independent archive symbol |
| --- | ---: | --- |
| 0x005423F7 | 52 | `?initialize_pointers@@YAHXZ` |
| 0x0054242B | 80 | `___crtGetSystemTimePreciseAsFileTime` |

## Explicit startup initializer and two cached pointers

The original pointer at `0x0056C424` references `0x005423F7` and has a PE HIGHLOW
relocation. Independently, the archive's complete four-byte `.CRT$XIC` section
has one relocation to the named initializer. The corresponding written static
function in `winapisupp.cpp` establishes its library origin.

The initializer obtains the existing `kernel32.dll` module and looks up
`GetSystemTimePreciseAsFileTime` and `GetTempPath2W`. It stores the results at
`0x005E4E6C` and `0x005E4E70`, then returns zero. The original complete literals,
PE import identities and two adjacent cache locations agree with the archive.
There is no added lookup-failure branch. The bounded original references show
the time wrapper reading the first cache; the second has only the initializer
write in that query. No `GetTempPath2W` consumer is classified by this review.

## Fallback path and physical sharing

The time wrapper passes its `FILETIME*` to the cached function when nonnull,
including the established CFG check. A null cache instead calls the imported
`GetSystemTimeAsFileTime`. It has a void, cdecl interface and retains its original
cookie/exception-frame setup and restoration. This matches the compatibility
branch in the installed source; it does not establish the whole game's SDK or
minimum operating-system selection.

The complete archive contribution is 85 bytes: 80 bytes of code through
`0x0054247A` and five original INT3 bytes through `0x0054247F`. The next lock
entry at `0x00542480` stays separate. The prologue references `0x00567600`, whose
complete 29-byte handler was already reviewed with the global exit controller.
The archive's time-handler contribution agrees with that same physical body,
including the security-check call, metadata operand and frame-handler tail.
It receives no duplicate row or replacement owner.

The complete 36-byte FuncInfo at `0x005A91B8` also remains shared. It equals the
whole relevant archive `.xdata$x` section, with zero states/maps/catches and
flags five. There are no extra owned unwind records for these two entries.

## Evidence and validation

The independent member is from installed
`VC/Tools/MSVC/14.44.35207/lib/x86/libcpmt.lib`, with corresponding source
`crt/src/stl/winapisupp.cpp`. Private `.analysis/origin-boundary/winapi/` retains
the object, bounded reference query, symbol locator and `reviewed.json`.
`review.py` verifies archive identity, complete ordinary-byte and instruction
coverage, relocation roles, full HIGHLOW sets, literal sections, the startup
pointer/COFF relocation, alignment and shared EH. It reuses the original method
listing in `.analysis/origin-boundary/ios-native.txt` and previously retained
handler listing in `.analysis/origin-boundary/locks-atexit-handler.txt`.

Tracking and generated progress pass. All 2,089 protected native inputs and
canonical products retain their hashes. This review adds no canonical source
mapping or exact credit. No compiler run is required, and the canonical exact
replay scope is **zero units**.
