# CORE/RECON-1194 — shared 66B IntrusiveList prepend boundary

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
and both original relocation roles. **53/58 ordinary bytes match**. The only
five ordinary-byte differences are at `+0x2C..+0x30`, in the final tail-sentinel
comparison: the native compiler form compares the memory operand against the
saved `this` register, while the candidate loads the tail pointer and compares
it against the saved stack value. Both preserve the same sentinel test and
conditional tail update; the two call destinations and function boundary are
identical.

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
original E8 targets, all 15 physical callers, and the fresh natural C++
instantiation's 53/58 ordinary-byte comparison. It explicitly does not award
strict exactness.
