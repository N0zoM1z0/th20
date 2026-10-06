# Source and build ownership

| Owner | Maintained source | Target component | Acceptance |
| --- | --- | --- | --- |
| RandomState | src/Random.hpp, src/Random.cpp | transition 0x00422CB0; invocation 0x004235F0 | Exact library equivalents; excluded from authored credit |
| Timer | src/Timer.hpp, src/Timer.cpp | reset 0x00423F50; set 0x00423F80; mode 0x00423FE0 | Reset/set exact; mode semantics checked, three compiler byte differences |

RandomState represents the four-byte STL engine subobject. It does not replace
its enclosing 28-byte game RNG, distribution state, four streams or locking.
Timer is a checked 16-byte value record; delta/tick operations and their global
clock/rounding protocol remain unimplemented.

`config/match-units.toml` owns two objects and one canonical profile per source.
Four units cover complete COFF function contributions. Library units can be
replayed without becoming authored progress. Timer mode is compiled from the
same production body but is not an exact unit. Its address is an independently
verified relocation anchor for Timer::set.

`probes/` remains infrastructure-only. Production currently builds objects for
component comparison; no whole-game linker or runtime acceptance is available.
Future owners must close storage, initialization, ABI and lifetime protocols.
Reference module names do not prescribe our directories or translation units.
