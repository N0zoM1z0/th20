# Exact glyph task allocator application

The task allocator's complete tuple-application chain now strictly replays:
78B `apply`, 65B `_Apply_impl`, 17B `invoke` and the 61B construction lambda.
The C++17 construction owner preserves native forwarding and empty index-sequence
passing; the surrounding list implementation keeps its C++20 profile. All
previous eighteen matches survive. The affected scope is **22/22 units from
two fresh objects**, with every owned code extent and relocation included.

| Native head | Complete extent / instructions | Canonical unit |
| --- | ---: | --- |
| `0x00413A40` | 78B / 30 | `glyph_queue_apply_78` |
| `0x00413190` | 65B / 25 | `glyph_queue_apply_impl_65` |
| `0x00413D30` | 17B / 8 | `glyph_queue_invoke_17` |
| `0x004130E0` | 61B / 23 | `glyph_queue_construct_lambda_61` |

These are library-support matches. Their original provenance remains
unknown/review, and no authored-game bytes are added. The target remains the
Japanese TH20 v1.00a Steamless executable with SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The locked compiler is MSVC 19.44.35211 x86; both profiles use
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

## Source and compiler finding

The same language-mode boundary was established for the mask allocator in
[the existing protocol investigation](GLYPH_OFFSET_PMR_FIVE_PARENTS_NATIVE_FRONTIER.md#2026-11-26-follow-up-exact-apply-protocol-and-source-ownership).
C++20 emits 34B `apply` and 30B `_Apply_impl`; redeclaring the forwarding
templates with `noinline` does not restore the calls. The native 78B body
also has three real empty index-sequence byte stores. C++17 emits these
naturally, together with both out-of-line forwarding calls.

`NativeGlyphTaskAllocator.hpp` declares the real PMR node allocator's task
construction specialization. `GlyphTaskAllocatorConstruct.cpp` owns that
specialization and its C++17 argument-tuple compatibility implementation.
Its destination-capturing lambda placement-constructs the actual
`std::function<void()>` from the forwarded task. The existing 78B PMR unit
moves to this owner without changing its native code. The list source retains
its function-specific forwarding instantiation and seventeen other units.
The two owners share this declaration; no SDK header is modified.

## Bindings and complete comparison

Attested Ghidra exports corroborate the call chain. `apply` forwards the tuple
and callable to the shared eight-byte identity at `0x0040B280`, then calls
`_Apply_impl`. The latter extracts the argument through the folded 10B
`get<0>` at `0x0040B2A0`, forwards the callable and invokes the construction
lambda through the 17B trampoline. Its lambda calls placement new at
`0x0040E700`, forwarding, and function move construction at `0x004140C0`.

The latter head carries an inherited Ghidra `shared_ptr` annotation. The
emitted complete 46B `std::function<void()>` move constructor matches its
code and all three call fields: the independently established function-base
constructor at `0x00413F80`, shared identity, and `_Reset_move` at
`0x00414BE0`, also identified by the native function-swap owner. The focused
checker verifies this callee as supporting evidence without adding another
canonical unit. It also compares the actual emitted forwarding, tuple-get
and complete 26B pointer-capture constructors. Shared tuple-argument heads
at `0x00413D50` and `0x00413CE0` retain their existing canonical owners.

All four new contributions end at their returns and have no additional
EH contributions or data relocations. The existing node/guard EH code and
complete 44B/36B metadata remain exact. Private negative controls reject
corrupt forwarding, tuple-get and capture bodies, and a move call redirected
to the wrong function-base member.

## Reproduction and next work

The new header is captured only by the two changed providers; the prior list
receipt captured no local headers. Replay scope is seventeen list units and
five allocator units. Fresh objects and receipts are under
`build/gpt61-glyph-apply-canonical/`. Both previous queue canonical objects
and receipts remain unchanged.

```sh
nice -n15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueueList151.cpp --existing-objects
nice -n15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTaskAllocatorConstruct.cpp --existing-objects
nice -n15 scripts/repo-python scripts/verify-glyph-queue-list-native.py
```

Private evidence is in `.analysis/glyph-apply-session/`: `native.c`,
`ghidra-log.txt`, `allocator17-proof.txt`, `canonical-queue-replay.txt`,
`canonical-allocator-replay.txt`, `canonical-native-proof.txt` and
`verifier-controls.txt`. The constructor, guard and PMR descendant checkers
also pass. Earlier compiler controls remain useful in the linked mask note.

The function-move/reset support is now accepted by the
[movement/swap checkpoint](GLYPH_FUNCTION_SWAP188_NATIVE_FRONTIER.md). The 294B
queue submit and 578B/586B formatting frontiers remain open. This local
partition is reproducible; the original game's global language mode and
translation-unit partition are still unknown.
