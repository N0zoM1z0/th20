# CORE/ORIGIN-677 — whole 32B native AnimationFile bind wrapper admitted as game-authored exact

**One distinct, previously strict-exact 32-byte original AnimationFile method is newly admitted as game-authored.** This is an evidence-based origin review, not an attempt to label a separately compiled support function or to double-count an existing 194-byte callee.

## Independently observed complete game method

Immutable Japanese TH20 v1.00a Steamless original `resources/th20.exe`, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

- The complete physical native **`0x00438380..0x0043839F`** method is 32 bytes and **15 actual x86 instructions**, with the original `__thiscall` AnimationFile receiver. It pushes a null `Animation*` parent, then forwards the real `(Animation*,script,parent)` arguments to a direct native E8 at **`0x00438394 → 0x004382B0`**. It executes one authentic compiler NOP and returns with `ret 8`. Exactly **one original E8**, **zero original PE HIGHLOW** relocations are present. This is not the distinct 338-byte `AnimationFile::load_script` at 0x004383A0.
- The **entire original 1,576B game-owned `Item::spawn`** at `0x004C3C90` has two real E8 callers of this function: **`0x004C4236`**, **`0x004C4278`**. The different whole **381B original `Item::activate`** at `0x004C4420` has four: **`0x004C44FF`, `0x004C4522`, `0x004C4545`, `0x004C4568`**. These are original PE machine-code destinations, independently observed inside both already strictly exact game-owned Item bodies, not deduced from the method spelling.
- The wrapper's actual E8 target `0x004382B0` is the independent **complete 194-byte original `AnimationFile::bind_animation(Animation*,int,Animation*)`**, already game-authored and strict exact. Its source has the real AnimationFile receiver, game template/parent binding and real VM state, so the 32-byte overload is a game-defined state-preparation interface rather than a CRT/STL construction artifact.
- The existing maintained C++ `src/AnimationFile.cpp` implements the normal overload by `bind_animation(animation,script,nullptr)`. Its accepted distinct `animation_file_bind_script` unit matches **all 32/32 bytes** with the original direct-callee relocation, not just a mnemonic prefix.

The two independent game-owned Item callers and the separately game-owned 194-byte underlying binder substantiate an authored, high-confidence original class method. Original machine code and whole caller spans are nonoverlapping; no independent game source file or class layout is invented.

## Strict acceptance and scoped verification

Only existing canonical objects and original PE were used:

- `animation_file_bind_script: exact (32/32 bytes)`
- `item_spawn_primary: exact (1576/1576 bytes)`
- `item_activate: exact (381/381 coverage bytes; 400/400 compared bytes)`
- `animation_parent_binding: exact (194/194 bytes)`

Independent original game E8/ownership audit: `.analysis/core677-animation-bind-script-original-game-origin.py/json`. The original target hash, original E8 offsets, complete bodies and real source symbols are checked independently. No new source, shared header, canonical manifest/provider, compiler flags, or native target bytes changed. The original 1,576B Item spawn, 381B Item activation and 194B Animation parent binder were all previously exact; their bytes are **not** credited again.

The origin/match-ledger admission adds **one** physically distinct complete game-authored **32-byte function** to existing native exact coverage: **500 / 179,463 → 501 / 179,495 original bytes**. Precisely four existing relevant units were strictly compared with existing pinned input-closure receipts. **Zero native providers were edited or cold recompiled**, and no unrelated/full cold replay occurred. The 3,111B Player frame, 555B Player movement, and 39,470B Animation VM parent remain separately NONEXACT.
