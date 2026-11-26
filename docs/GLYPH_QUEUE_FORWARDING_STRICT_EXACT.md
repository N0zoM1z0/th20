# Exact glyph queue insertion and allocator forwarding

The glyph task queue's **151B insertion**, **158B node constructor**,
**31B allocator-traits construction** and **78B PMR construction** now pass
complete canonical relocation replay. One local explicit instantiation
restores the native forwarding calls. All eleven previously accepted units
remain unchanged; the full affected scope passes **18/18 units from one
fresh object**, including owned exception code and metadata.

The four bodies are generated from SDK library source. Their original-source
provenance remains unknown/review, separately from matching status. Owned EH
code is classified as compiler support. No entry is added to the authored-game
exact ledger.

The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The compiler is locked MSVC 19.44.35211 x86 with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

## Source finding

The installed `list` header calls `std::forward` in both `_Emplace` and
`_List_node_emplace_op2` construction. The original has the corresponding
out-of-line calls to the shared eight-byte reference identity at
`0x0040B280`; current MSVC otherwise inlines this constexpr specialization.
The maintained `GlyphTextQueueList151.cpp` now retains this one instance:

```cpp
template __declspec(noinline) std::function<void()>&&
std::forward<std::function<void()>>(std::function<void()>&) noexcept;
```

This restores the actual SDK implementation without editing SDK headers,
changing the compiler profile or introducing another node implementation.
The emitted specialization matches all eight original identity bytes and
has no relocations. It receives no duplicate physical-function credit.

The insertion grows from 130B/44 instructions to the native 151B/51, with
all eight calls and two data fields matching. The node constructor grows
from 143B/46 to 158B/51, matching all five calls and two data fields. Their
allocator result/forwarded argument temporaries and frame layouts follow
naturally from the restored calls. No extra local or padding is added.

Earlier records called the folded identity `_Unfancy` or `move`. Its
physical bytes do not establish one unique C++ spelling. The installed
source and complete caller matches identify `std::forward` at the missing
sites; node-value address forwarding separately uses `std::addressof`.

## Complete matched support functions

| Native address | Extent / instructions | Canonical unit |
| --- | ---: | --- |
| `0x004131E0` | 151B / 51 | `glyph_queue_list_emplace_151` |
| `0x00413000` | 158B / 51 | `glyph_queue_node_ctor_158` |
| `0x00413B00` | 31B / 14 | `glyph_queue_traits_construct_31` |
| `0x00413B20` | 78B / 30 | `glyph_queue_pmr_construct_78` |

The exact 56B queue bridge calls insertion at its original `+0x2C`.
Insertion calls the node constructor at `+0x5B`, then the existing 124B
link operation and 118B guard destructor. The node constructor calls
allocator traits at `+0x7B`; traits forwards the callable into the real PMR
constructor. Its tuple construction, one-pointer lambda capture and apply
roles are corroborated by bounded attested Ghidra decompilation of the
native callees. The shared argument-tuple head at `0x00413D50` already has
an independent canonical owner; it is not credited again here.

External bindings use those independently reviewed call roles, established
allocator/cookie/CRT heads and the original caller graph. The pooled
`list too long` constant is checked as all fourteen actual COFF and PE
bytes at `0x0056C8BC`. No destination is solved from a compared field.

## Owned exception contributions

The node constructor retains its allocation rollback state:

- `0x00567CB0`: 8B cleanup plus five original INT3 alignment bytes,
  compared as the complete 13B contribution.
- `0x00567CBD`: complete 29B handler, selecting FuncInfo at `0x005A993C`.
- `0x005A9934`: complete 44B metadata, comprising the one-action map and
  FuncInfo, including both DIR32 fields.

The previously exact node guard also retains its complete 29B handler at
`0x00567750` and 36B metadata at `0x005A91B8`. The latter has zero states,
no relocations and flags word five. The guard's own 118B code and five
INT3 tail bytes still compare as 123B.

Handler addresses reuse the independently pinned constructor/guard evidence.
All handler and cleanup code is replayed with its real destructor, cookie,
frame-handler and metadata bindings. The node metadata has a unique match
with its map self-pointer excluded and its cleanup owner fixed; the guard's
36B data has a unique exact `.rdata` match. This verifies the owned metadata
without deriving its anchors from the handler fields being compared.

## Reproduction and retained evidence

At the forwarding checkpoint, no shared header changed. Only
`src/GlyphTextQueueList151.cpp` was freshly
compiled; its eleven existing helpers, four new library bodies and three
EH code units pass from `build/gpt61-glyph-queue-canonical/`. The old
`core1061-canonical` object and receipt are preserved unchanged.

The later [application checkpoint](GLYPH_QUEUE_APPLY_STRICT_EXACT.md) splits
the construction owner and records current replay commands.

The constructor, guard and PMR descendant checkers pass against the new
provider. Private controls reject a wrong node state count, map symbol,
guard flags, cleanup receiver and error-message byte, and reject the old
130B insertion extent. They mutate only private object copies.

Native exports and proof logs are retained in
`.analysis/glyph-queue151-session/`: `native.c`, `allocator-native.c`,
`forward-proof.txt`, `canonical-replay.txt`, `canonical-native-proof.txt`,
`node-ctor-proof.txt`, `guard-proof.txt`, `descendants-proof.txt` and
`verifier-controls.txt`.

The downstream `std::apply` and `_Apply_impl` heads at `0x00413A40` and
`0x00413190` are now accepted by the linked application checkpoint, together
with their invoke/construction lambda. The forwarding finding and owned EH
proof above remain applicable.
