# CORE/RECON-1194/1195 — shared 66B IntrusiveList prepend boundary

Target: Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The previously unclassified original `0x0044A6B0..0x0044A6F2` is a 66-byte,
25-instruction `__thiscall` intrusive-list prepend operation. Its immutable
body SHA-256 is
`773c78d2fa904d530e27b1f0fa76ab56a43e66454e1504d7259462f822399c2b`.

The body inserts the supplied link after the list sentinel, assigns its owner,
and updates the list tail only when the old tail is the sentinel. Its two real
calls are `+0x16 -> 0x00411EE0` (`IntrusiveLink::insert_after`) and
`+0x22 -> 0x00412DC0` (the folded owner-pointer setter). It ends with the
original `ret 4`. There are **15 physical original callers**, including the
3735B BulletEmitter at `0x00481975`, Animation callers at `0x0044B867` and
`0x0044B8BA`, and twelve other gameplay/list owners.

## Natural C++ source owner

The maintained implementation already exists in `src/IntrusiveLink.hpp` as
`IntrusiveList<T>::prepend`. A fresh locked MSVC x86 C++20 compilation of the
`IntrusiveList<Bullet>` instantiation contributes the complete 66-byte body
and both original relocation roles. The first natural source form matched **53/58 ordinary bytes**. Reversing the
C++ equality operands to `if (this == tail)` changed the emitted sequence to
**56/58 ordinary bytes** without changing semantics or function extent. The
candidate now has the same two `this` reloads as the original; only the two-byte
CMP opcode/modrm sequence at `+0x2E..+0x2F` remains different. Native uses
`cmp dword ptr [ecx+0x14], eax` (`39 41 14`); the current compiler emits the
commuted equality as `cmp ecx, dword ptr [eax+0x14]` (`3B 48 14`). Both set the
same equality flags, and both branch to the same unchanged tail-update block.
The two call destinations and function boundary are identical.

This is now classified as a reconstructed shared C++ template boundary, not
as an exact function. It contributes **zero exact bytes** and has no
`match-units.toml` exact unit. No assembly, volatile access, padding, or fake
instruction is used to force the remaining comparison encoding. The next
attempt should continue from natural source/lifetime and compiler evidence.

## Focused verification

```bash
scripts/repo-python scripts/verify-intrusive-list-prepend-frontier.py
```

The verifier checks the immutable 66B body hash, 25 instruction heads, both
original E8 targets, all 15 physical callers, the fresh natural C++
instantiation's 56/58 ordinary-byte comparison, and a host semantic test in
`tests/intrusive_list_prepend_semantics.cpp` covering empty, first, repeated
head insertion, link ownership and stable-tail behavior. It explicitly does
not award strict exactness.
