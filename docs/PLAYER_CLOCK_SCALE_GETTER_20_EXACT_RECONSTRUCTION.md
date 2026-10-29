# CORE/EXACT-684 — original whole 20B Player clock-scale x87 getter, exact native C++

**A previously unclassified original game method is now reconstructed as genuine C++ source and canonical strict exact:** `Player::clock_scale_value() const` at original physical `0x004AAA40`, 20 bytes and 9 full native x86 instruction heads. The historical method spelling is source-inferred from the actual storage/ABI; the original file and physical object identity are not inferred from that spelling.

## Independent immutable TH20 source-owner and ABI evidence

Comparison target is the independently verified Japanese TH20 v1.00a Steamless `resources/th20.exe`, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

- Full original native body `0x004AAA40..0x004AAA53` is exactly **20 bytes and 9 instructions**. It saves the real 32-bit `__thiscall` receiver, loads `fld dword ptr [eax+0x223C]` into the **x87 floating return register**, restores the stack frame and exits with ordinary `ret` (no explicit arguments). The complete original native body contains **zero E8 calls**; an independent sweep of the original PE `.reloc` section also confirms **zero HIGHLOW fields** within the original 20 bytes.
- The separately already canonical strict-exact **29B `Player::set_clock_scale(float)`** at original `0x004AB590` writes the *same* floating member with native `movss [eax+0x223C],xmm0`. Its real game source `src/PlayerAccessors.cpp` and the existing `src/Player.hpp` `Player` owner layout establish the original field as **clock_scale**. The native updated header asserts `offsetof(Player,clock_scale)==0x223C` with no added storage.
- Independent genuine original E8 callers of this physical original 20B body occur in the entire **734B original body at `0x004A5040`**, at `0x004A5274`, and in the distinct **4,673B original body at `0x004A5DF0`**, at `0x004A64BF`. Each real caller reads a live receiver pointer and consumes the x87 result in its subsequent float calculation. These enclosing original functions are still unclassified/nonexact, **not** admitted as exact merely because their call destination is now known.

This confirms a typed, source-owned Player gameplay scalar getter rather than a fabricated trampoline or CRT helper. The actual native control flow, getter and already exact setter are independent of any source-name guess.

## Complete original code restoration and canonical acceptance

The maintained C++ is the natural `float Player::clock_scale_value() const { return clock_scale; }` added alongside its existing setter in `src/PlayerAccessors.cpp`, with one actual method declaration added to `src/Player.hpp`. There is no unsafe reinterpret cast, inline assembly, volatile shaping or target/compiler-output byte patch. Two earlier isolated real MSVC object profiles independently emitted the full **20/20 identical original bytes** using a typed proxy. The final real Player class method was rebuilt under the original matching pinned MSVC 19.44.35211 x86 profile:

`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`

The new canonical unit `player_clock_scale_value` uses the existing `src/PlayerAccessors.cpp` provider at `build/core307-canonical/PlayerAccessors.obj`, with the original address `0x004AAA40`, comparison and authored size **20**, and **zero** relocation entries. The genuine repository strict comparator reports:

- **`player_clock_scale_value: exact (20/20 bytes)`**
- Existing independently original **`player_set_clock_scale: exact (29/29 bytes)`** remains unchanged.

No new canonical provider object is created; one new complete method/unit is added to the already existing PlayerAccessors native object. No former original function body overlaps the new physical 20B interval.

## Exact include-closure protection — no global cold replay

Before touching `Player.hpp`, original pinned compiler receipt header SHA-256 values were independently inspected for **all** currently configured canonical objects. Exactly **26 previous source/COFF providers and 73 previously accepted strict whole-function units** included the shared Player header. The affected objects alone were freshly compiled under their unchanged original pinned MSVC profiles in four serialized low-priority batches. The scoped strict original replay passed **74/74 complete units** (33 + 9 + 16 + 16), including the new 20B getter, in **26/26 fresh native providers**. The refreshed input/header/object SHA-256 receipts were independently rechecked, including the full 3,735B game-owned Bullet emitter, whose entire 3,832B code/NOP/two-switch-table contribution remained exact.

Only one MSVC-private COFF diagnostic-string label changed inside the previously accepted Player constructor: **`$SG82289` → `$SG82291`** at the same original relocation offset `+0x2FC`. The new COFF string's full original **22 NUL-ended bytes** were compared independently with the *previously anchored* immutable PE bytes at **`0x00572BB8`**, **before** changing only this private compiler symbol in `config/match-units.toml`. The original relocation offset, type, physical destination and all other canonical source anchors remained unchanged. No manifest matching threshold was relaxed or original binary bytes patched.

Reproducible ignored native proof files:

- `.analysis/core681-player-header-preedit-closure.py/json` — old original header SHA and all 26 actually affected MSVC receipts / 73 old strict units.
- `.analysis/core682-player-header-affected-batches.py/json`, `.analysis/core682-build-affected-only.py`, four `core682-player-affected-cold-build-batch-N.log` — only the real affected pinned MSVC source objects cold rebuilt.
- `.analysis/core683-player-header-private-drift-audit.py/json` — independent COFF relocation-site and original PE string proof, one safe unchanged-target private label rename.
- `.analysis/core683-replay-player-header-batch.py`, four `core683-player-affected-strict-batch-N.log` — all **74/74 actual scoped strict units** replayed from fresh native objects; no other graph sources.
- `.analysis/core684-player-clock-scale-original-game-getter-proof.py/json` — full original 20B x87 function, complete 29B native setter, actual 734B/4,673B original caller method bodies, true PE `.reloc` absence, independently verified executable identity.

**New game-authored strict progress is one function and 20 original nonoverlapping code bytes:** **502 / 179,518 → 503 / 179,538**. Source-present mappings increase **1,183 → 1,184** and configured canonical units **1,185 → 1,186**; provider count stays **244**. This proves complete method-level original x86 native exactness, not a linked or playable game, and does not establish strict exactness of the 3,111B Player main-frame, 555B movement, 273B Bullet draw group, 4,673B caller, or the larger Enemy/Animation dispatchers.
