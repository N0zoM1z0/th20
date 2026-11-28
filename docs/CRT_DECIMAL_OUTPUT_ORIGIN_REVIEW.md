# UCRT decimal-point insertion and trailing-zero cropping

Two complete Windows SDK 10.0.26100.0 x86 `libucrt.lib(output.obj)`
contributions identify pending library origins in the locked Japanese TH20
Steamless target: the 106B/53-instruction `crop_zeroes` at `0x005494CC`
and the 98B/43-instruction `force_decimal_point` at `0x00549573`.
All 204B/96 instructions match, including the original NOPs, branches,
register saves and shared returns. Both existing extents remain unchanged.

These are cdecl void helpers taking a buffer and a supplied locale handle.
They have no calls, relocations, HIGHLOW fields, owned data, padding or local
EH metadata. Every instruction is reachable from its owning main entry.

## The supplied locale selects the decimal byte and classifications

Both helpers obtain locinfo through the supplied locale's first pointer,
then lconv at locinfo `+0x88`. The first pointer in lconv supplies the decimal
string, and the first byte of that string is the actual separator used.

Insertion also reads the lowercase map at locinfo `+0x94`, and the public
16-bit ctype table through locinfo's first pointer. The original unsigned-byte
indexes and digit-mask bit 0x4 remain intact. These are fields of the runtime
locale argument, not new static-address bindings. The installed locale layout
and inline classification definitions corroborate the same reads.

## Insertion retains the exponent and hexadecimal paths

Force_decimal_point tests the lowercase mapping of the initial character.
Unless it maps to e, it advances at least one byte, then continues over
characters classified as digits. If the resulting character maps to x,
the original hexadecimal path advances exactly two more bytes to insert
after the hexadecimal digit.

The helper saves the displaced character and stores the locale's decimal
byte in its place. It then carries the displaced byte forward one position
at a time until the stored byte is zero. Each iteration reads the next
original byte before writing the carried byte, including the final iteration
that stores the terminator. The complete carry loop and original two-byte
hexadecimal adjustment remain in this owner.

## Cropping preserves the exponent suffix and terminator

Crop_zeroes finds the first decimal byte or string terminator. With no
decimal byte it returns without writing. Otherwise it scans to e, E or the
terminator, remembers that suffix position and walks backward over ASCII
zeroes. If only the decimal byte remains, it removes that byte too.

The original forward copy then moves the remembered exponent or terminator
over the removed suffix, including the final zero. With a period decimal byte,
the source protocol maps `1.2300e+4` to `1.23e+4` and `1.000E+4` to `1E+4`.
It preserves the locale-selected decimal byte rather than substituting a
fixed period. All original loop bounds, byte widths and returning branches
are retained.

## Evidence and affected scope

Private `.analysis/origin-boundary/format-decimal/` retains scoped locator
results, the attested full listing, complete comparison, locale-field and
copy-order observations, reachability proof and original rows. It reuses the
complete member/provenance in `format-buffer/`. Installed
`corecrt_internal_stdio_output.h` supplies both complete helper definitions;
`corecrt_internal.h` supplies the matching locale fields and classification
operations.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass; all 2,151 protected native input/product hashes
are unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
