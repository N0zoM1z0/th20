# Exact Player main frame

`Player::update_main_frame` at `0x004F9C30` now strictly matches all
3,111 native bytes and 783 instructions. Representing the otherwise unused
`Timer::equals(8)` call as an empty conditional, separate from the following
16-frame test, restores the native register sequence throughout the function.
All 67 call fields and 37 data fields replay from independent anchors.
This adds one authored function and 3,111 exact bytes.

The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete native body, `0x004F9C30..0x004FA856`, has SHA-256
`7f0bff5c2e175ff3d223c9e958fd908e39016b136fd1ff0eb0e1ce0cf6672467`.
The canonical unit is `player_update_main_frame_3111` in
[the manifest](../config/match-units.toml), using
[PlayerMainFrame.cpp](../src/PlayerMainFrame.cpp) and locked MSVC
19.44.35211 x86:

```text
/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc
```

## Empty condition and register allocation

The previous source put `equals(8)` in the initializer of the next `if`.
It emitted 3,114B/783 instructions. The
[complete earlier audit](PLAYER_MAIN_3111_CFG_AND_REGISTER_CONTROLS.md)
matched every internal branch target, frame operand, ordinary immediate and
call/data role, while finding 327 ordinary instructions with different
scratch-register encodings. Seven accumulator ADD widths gave the net +3B.
The first mismatch immediately followed the ignored comparison call.

The maintained form is now:

```cpp
if (timer_2070.equals(8)) {}
if (timer_2070.at_least(16)) {
    clear_option_animations();
    set_movement_mode(0);
} else goto finish_normal_movement;
```

MSVC preserves the first call but emits neither a branch nor a NOP for the
empty condition. Its subsequent register allocation matches the original,
removing all 327 ordinary mismatches and all seven length differences.
The empty body expresses the native call's lack of a following action.
The existing Timer bool predicates retain their independently verified 46B
bodies. Exact bytes establish this source representation; the original
source spelling remains unknown.

The compiler controls showed that `/permissive` left the old
3,114B body unchanged. A C++17 compile fails because the included Worker
storage contains `std::jthread`. The successful main-frame unit remains
C++20; the separate [555B movement match](PLAYER_MOVEMENT555_STRICT_EXACT.md)
uses its own C++14 profile. Earlier comma, discard, comparison-operator,
receiver and byte-return controls remain useful failed attempts.

## Complete comparison and scope

Strict canonical replay passes **3,111/3,111 bytes**, including all internal
branches and relocation fields. The COFF contribution has its complete native
extent; there are no owned switch tables or EH contributions.
The 67 calls comprise 61 independently canonical call roles and six calls
using five folded source symbols. The latter were rechecked against complete
17B, 21B, 14B, 14B and 45B native bodies. Their physical heads are shared and
receive no additional credit.

All 37 DIR32 locations match PE HIGHLOW fields: 34 established global
references, two references to the original 72B direction table and the actual
seven-byte `effect` literal. The unchanged table object was reused and its
complete bytes/hash checked.

**Affected canonical replay: one unit from one fresh provider.** No shared
header changed. Current products are
`build/gpt61-player-main-canonical/PlayerMainFrame.obj` and its receipt;
the exact movement products remain intact. The active provider path is recorded
in the canonical unit manifest.
The direction-data checker now accepts the complete 3,111B contribution and
uses current product paths. Its real 72B/37-field check passes; negative
controls reject the old 3,114B parent and a changed direction-table value.
It continues to report data evidence separately from canonical exactness.

The enclosing [4,072B Player state-frame contribution](PLAYER_STATE4043_NATIVE_FRONTIER.md)
is now mapped and source-present. It matches ordinary bytes but remains NONEXACT
until its independent relocation bindings are complete.
