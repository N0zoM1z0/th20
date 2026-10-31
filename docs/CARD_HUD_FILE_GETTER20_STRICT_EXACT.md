# CORE/RECON-1005 — whole native 20B renderer AnimationFile getter, original Card HUD source exact

Locked original: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original 20B/9-i386 function at `0x00437950..0x00437963`
(SHA-256 `6181bd2fb3b6c96cc30b6297ac35f8f97d01d5721aaced3fdee51766fbc89824`)
reads the **existing receiver's borrowed AnimationFile pointer at
`+0x1A244`** and returns it in EAX. The body ends at its original `ret`
and has **zero original E8 and PE HIGHLOW**. This is the genuine source
role consumed by the separately whole-exact **1,522B** result HUD Boss
at `0x004B90E0`: original physical E8 `+0xE0`, `+0x1FA`, and `+0x28C`
all target this exact original function.

[`scripts/verify-card-hud-file-getter20-native.py`](../scripts/verify-card-hud-file-getter20-native.py)
independently verifies the complete SHA-pinned original body, real
native receiver/member displacement, three immutable original 1,522B
parent call instructions, and genuine absence of relocation fields.
Its maintained source is the natural
`NativeCardRendererFileView::current_file_437950` method already present
in [`src/CardHudResult1522.cpp`](../src/CardHudResult1522.cpp). The
non-owning receiver does **not** imply a new Renderer class layout,
allocator ownership or a claim about the original C++ class spelling.

Pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` produces all 20 original bytes with no
relocations. The 1,522B original boss and this 20B getter share the
**same one canonical object and one fresh receipt**; both independently
replay strictly exact:

```text
card_hud_spell_result_boss_1522: exact (1522/1522 coverage bytes; 1552/1552 compared bytes)
card_hud_renderer_file_getter_20: exact (20/20 bytes)
Exact replay: 2/2 units, 1 cold objects
```

This adds **one physical strict unit /20 original code bytes**, but
not an authored-game head or authored byte: its original source-level
ownership, generic accessor folding and provenance remain uncertain,
so `origin=unknown/review`. The whole-exact game HUD Boss stays
credited once for 1,522B and does not receive duplicated callee credit.
No shared public layout changed and no full cold replay occurred.

```sh
scripts/repo-python scripts/verify-card-hud-file-getter20-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardHudResult1522.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
