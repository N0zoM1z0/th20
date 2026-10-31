# CORE/RECON-1009 — original 128-byte PMR string name constructor in Card start, whole strict exact

Locked target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The genuine original `0x0046A830..0x0046A8AF` is a complete
**128B/41-i386** `std::pmr::string(const char*)` constructor (native SHA-256
`415b1e69052289e12f81ff767adfe7714aa896eac6c56df04471d47189c165cb`).
The original **1,896B Card::start_spell** invokes this exact physical head
at its E8 `+0x2D3` while creating the local Card spell-name text string.
This direct relationship is proved from the immutable original executable,
not inferred by decompiler display names or from candidate source symbols.

The ordinary maintained C++ call `std::pmr::string display_name(spell_name)`
in [`CardStartSpell1896.cpp`](../src/CardStartSpell1896.cpp) naturally instantiates
the complete 128-byte original standard-library body with the original
allocator and exception-handling behavior. Its true native instruction and
relocation roles are independently attested by
[`verify-card-start-pmr-char128-native.py`](../scripts/verify-card-start-pmr-char128-native.py):

| Native field | Actual original destination |
| --- | --- |
| DIR32 `+0x06` | real compiler EH handler `0x00568D2D` |
| DIR32 `+0x15` | real security cookie `0x005B25C0` |
| E8/REL32 `+0x36/+0x37` | native string compressed-pair default construction `0x00446C10` |
| E8/REL32 `+0x46/+0x47` | original narrow-character length `0x00411180` |
| E8/REL32 `+0x4F/+0x50` | original size conversion `0x0040B280` |
| E8/REL32 `+0x5F/+0x60` | original string `_Construct` `0x00468030` |

Locked MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` generates the entire body with
**104/104 nonrelocated bytes**, and the same six genuine relocation
locations, types and targets. The source is the actual Card start C++
translation unit, not a contrived or empty fake wrapper; one fresh
source-filtered canonical object/receipt accepts only the complete nested
constructor, not the unaccepted Card start parent:

```text
card_start_pmr_string_char_ctor_128: exact (128/128 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This adds **one newly accepted whole-native strict unit /128 distinct
original physical `.text` bytes** but **zero game-authored exact heads or
bytes**. It is standard-library compiler-generated work, whose original
source ownership is left `origin=unknown/review`; it must not be
misclassified as authored Card code. Its separate original 167B PMR copy
constructor, 56B Card text-payload constructor and 23B text-payload
destructor all remain independently exact under
[CORE/RECON-1007](CARD_TEXT_PAYLOAD_56_23_167_STRICT_EXACT.md).

The **1,896B Card start Boss remains SOURCE-PRESENT, NONEXACT**:
its text-task queue/EH and remaining live owner graph are unclosed, and
a newly generated exact PMR constructor does not make the parent exact.
No project-wide cold replay was used.

```sh
scripts/repo-python scripts/verify-card-start-pmr-char128-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardStartSpell1896.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
