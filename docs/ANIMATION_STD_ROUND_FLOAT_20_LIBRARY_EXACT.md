# CORE/RECON-833 — native 20B global round(float) C++ math wrapper, strict exact, library-excluded

The locked original TH20 Japanese v1.00a Steamless PE
(SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains a complete original **20-byte /9-x86** function at **`0x00445B80`**.
This was provisionally called `th20::animation_snap_round` because four
original E8 sites of the 3,159B quad submission Boss at `0x0043F6A0`
refer to it. Re-evaluating the original native bytes and ordinary locked-MSVC
output shows that this is actually the global C++ `<cmath>` **`round(float)`**
overload, with decorated name **`?round@@YAMM@Z`**, naturally emitted in the
quad submission translation unit from `std::round(float)` calls. It is
**library code, not game-authored code**. The identity is grounded in its
native forwarding protocol, generated standard header overload and actual
compiler COFF symbol. The previous provisional game wrapper hypothesis was
not a justified owner attribution.

## Original independent native PE and CRT callee

The [immutable PE-only verifier](../scripts/verify-animation-round-library-native.py)
checks the complete original wrapper bytes (no PE HIGHLOW sites) and its
nine native instructions. Its true call at `0x00445B8A` goes to **`0x00550060`**,
a separately observed **123-byte** CRT `_roundf` function. The CRT contains
real IEEE754 bit-domain thresholds `0x4B000000`, `0x3F800000`, and
`0x3F000000`, with four native return paths and no PE HIGHLOW. Thus the
float rounding operation is not a hand-assembled game-owned helper or a
caller-owned rounding algorithm.

The original wrapper byte structure is:

```text
55                 push ebp
8B EC              mov ebp, esp
51                 push ecx
8B 45 08           mov eax, [ebp+8]
89 04 24           mov [esp], eax
E8 xx xx xx xx     call _roundf   ; original target 0x00550060
83 C4 04           add esp, 4
5D                 pop ebp
C3                 ret
```

## Pinned compiler profile and whole strict acceptance

An ordinary `std::round(float)` call in
[`src/AnimationQuadSubmit.cpp`](../src/AnimationQuadSubmit.cpp) under the
pinned i386 MSVC 19.44.35211 profile
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:strict /sdl /EHsc`
produces the **same real 20-byte function** with exactly one COFF
relocation, `REL32` at offset `+0xB`, symbol `_roundf`, independently attested
original target **`0x00550060`**. The complete canonical
`animation_std_round_float_20` unit compares **20/20 exact**. The target
address is established from the native original E8 and the CRT function
head, not solved by comparing target fields.

Crucially, this native function does **not** appear as a separate manually
written `th20::animation_snap_round` body. Plain `::roundf` in a custom
wrapper and `/fp:precise` or `/fp:fast` naturally emit different code:
MSVC `/fp:precise` emits an x87 `fld`/`fstp` input transfer in the standard
float wrapper, rather than the original 32-bit `mov`/`mov`. Under
`/fp:strict`, the compiler emits the observed native 20B overload and the
**existing 3,159B parent Boss remains full strict exact**, with all four
parent E8 references naturally resolved to `?round@@YAMM@Z`. The canonical
parent itself is still the *same* native 3,159B game-original function,
not four duplicated wrapper copies.

Both the entire parent `animation_quad_submit_boss_3159` and this library
unit are supplied from a **single shared compiler source and profile** in
`build/core833-canonical/AnimationQuadSubmit.obj` with the matching pinned
receipt. A fresh **source-filtered replay of precisely two units/one cold
object** verifies:

```text
animation_quad_submit_boss_3159: exact (3159/3159 coverage bytes; 3180/3180 compared bytes)
animation_std_round_float_20: exact (20/20 bytes)
Exact replay: 2/2 units, 1 cold objects
```

## Attribution and scope

`config/functions.csv` marks the function `reconstructed` with 100% matching
code under `owner = library`, and `config/function-origins.csv` records
`origin = library`, `disposition = exclude`. Its source-present mapping is
`::round(float)` at `0x00445B80`. The accepted `config/matches.csv` remains
**authored-game functions only**: the 20 native library bytes and associated
CRT are not included in its authored game exact totals. The original
3,159B renderer Boss remains fully game-authored strict exact and retained
in `config/matches.csv` **once**.

This adds one library-only strict canonical unit and one source-present
mapping, **zero new authored-game functions/bytes**. The locked target,
previous accepted canonical providers and headers are unchanged. The only
native compiler input changed is `src/AnimationQuadSubmit.cpp`, so the
current verification replays its **two units from one source/object**, not
all ~1,240 exact units or an unfiltered cold build.

## Reproduce

```bash
scripts/repo-python scripts/verify-animation-round-library-native.py
scripts/repo-python scripts/verify-animation-quad-submit-native.py
nice -n 15 scripts/repo-python scripts/verify-animation-quad-submit-source-roles.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationQuadSubmit.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/progress.py --check
```

The [original whole parent proof](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md)
records the strict original 3,180B code-plus-table extent. Future work
should prioritize the unfinished 5,993B Animation draw Boss, 12,140B
Bullet extended-command Boss and 41,967B Enemy ECL dispatch Boss rather
than creating unnecessary game-authorship claims for native CRT wrappers.
