# CORE/RECON-909 — complete 42B forwarded-reference slot constructor strict native exact

The selected original TH20 1.00a Japanese Steamless image SHA-256 remains
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original physical `0x0045ECC0..0x0045ECE9` is **42B /17 complete i386
instructions**, including a final `ret 4`. Six adjacent `INT3` bytes are
outside this complete function body and are not silently counted as code.

## Immutable-original evidence

[`scripts/verify-cxx-forward-ref42-native.py`](../scripts/verify-cxx-forward-ref42-native.py)
independently authenticates the native body against the locked original PE:

| Original physical field | True destination | Meaning |
| --- | --- | --- |
| E8 `+0x0B` | `0x0040B280` | Reference-forwarding helper, first stage |
| E8 `+0x14` | `0x0040B280` | Forwarding the returned reference, second stage |
| Caller E8 `0x0045EE77` | `0x0045ECC0` | Whole 61B upstream C++ construction function |

The complete original constructor has **zero in-body PE HIGHLOW**. After
those two calls, it stores the actual pointer returned from the second
forwarding stage at receiver offset zero and returns the receiver in EAX.
The original `0x0040B280` has a separately accepted 8B folded `std::move` /
`std::forward` / address-helper body. This does **not** establish a unique
original C++ template instantiation name or game authorship.

## Native C++ reconstruction and exact verification

[`src/CxxForwardRefSlot42.cpp`](../src/CxxForwardRefSlot42.cpp) expresses an
ordinary pointer-sized reference-holding constructor with nested
`std::forward<uint32_t&>`. It has one semantic pointer storage body, no
manual instruction bytes, compiler-shaping no-op statements, ABI lies,
private vptr edits or artificial padding. The nominal class name is a
reconstruction label, **not** an assertion of the original template type.

Pinned MSVC 19.44.35211 x86, C++17 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl` generates the entire natural constructor with both genuine
REL32 relocation sites at `+0x0C`, `+0x15`, resolving to the physical
original 8B folded helper. The canonical unit
`cxx_forward_ref_slot_42` includes the whole 42B, not a prefix:

```text
PASS original 0x0045ECC0: complete 42B/17 i386, RET 4
PASS two original E8 at +0x0B/+0x14 to 0x0040b280, zero HIGHLOW
cxx_forward_ref_slot_42: exact (42/42 bytes)
```

The original **42B function is complete and strict exact**, but its
original C++ class name, allocation context and authored-vs-library origin
remain unproven. It remains `origin=unknown/review` and adds **zero**
authored-game function or `.text` byte credit; the enclosing 61B/79B/90B
constructor chain is not rendered exact by its child.

### Reproduce only the affected provider

```bash
scripts/repo-python scripts/verify-cxx-forward-ref42-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/CxxForwardRefSlot42.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

The affected cold-replay scope is exactly **one new C++17 source/object,
one strict unit**; previously accepted compiler inputs are unchanged.
