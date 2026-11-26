# Exact glyph function movement and swap

The complete **188B function-base swap**, **125B move reset** and **46B
function move constructor** now strictly replay, including all relocation
fields. Retaining one out-of-line `std::move<std::_Func_class<void>&>`
instance restores the swap's three missing calls. The affected scope passes
**22/22 units from two providers**, retaining fifteen prior matches. The
queue pump's complete 68B EH contribution and 60B state metadata also match.

| Native head | Complete extent / instructions | Canonical unit |
| --- | ---: | --- |
| `0x00414C80` | 188B / 63 | `glyph_queue_func_class_swap_188` |
| `0x00414BE0` | 125B / 44 | `glyph_queue_func_reset_move_125` |
| `0x004140C0` | 46B / 18 | `glyph_queue_func_move_ctor_46` |

These three SDK-library bodies remain origin-unknown/review. Compiler-owned
EH entries are excluded from authored-game credit. The target is Japanese
TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Both providers use locked MSVC 19.44.35211 x86 and
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

## Source and native behavior

`GlyphTextQueuePump254.cpp` retains the real SDK function-base move instance:

```cpp
template __declspec(noinline) std::_Func_class<void>&&
std::move<std::_Func_class<void>&>(std::_Func_class<void>&) noexcept;
```

The C++20 source otherwise emits a complete 161B/54-instruction swap,
missing exactly three live nine-byte call/stack-forwarding groups. With
this instance retained, the SDK's original semantic body emits all
188B/63 instructions, fifteen calls and the security-cookie field. Its
26B public `std::function::swap` caller and the queue pump's other nine
accepted units retain their complete code and relocation records.
Earlier notes called the folded identity `_Unfancy`; the SDK source and
complete caller match identify `std::move` at these three sites.

Swap exchanges implementation pointers when both functions use heap storage.
Otherwise it constructs a real 40B function-base temporary and performs
three move resets. Reset leaves an empty source alone; it moves an inline
callable through virtual slot +4 and tidies the source, or transfers a heap
implementation pointer and clears the source. Its original NOPs and branches
are retained by the natural SDK body. Move construction initializes the
function base and invokes this same reset. These noexcept bodies emit no
owned EH contributions.

The move constructor and reset already emit exactly from the unchanged
C++17 task allocator owner added by the [application checkpoint](GLYPH_QUEUE_APPLY_STRICT_EXACT.md).
Their canonical owner is `GlyphTaskAllocatorConstruct.cpp`; the pump's
folded reset instance receives no duplicate unit. The original Ghidra
`shared_ptr` annotation at `0x004140C0` is preserved as target evidence in
the inventory, while the reviewed proposed identity is corrected to the
actual `std::function<void()>` move constructor.

## Independent bindings and queue-pump exception ownership

Attested Ghidra exports corroborate all three native bodies. The previously
reviewed 26B swap wrapper calls `0x00414C80` at +0x0E. The independently
accepted 61B allocator lambda calls the move constructor at +0x32; the
constructor calls reset at +0x1F. Reset's base empty/local/get/set/tidy
operations and swap's base constructor/destructor use their established
native heads. The actual emitted eight-byte move leaf matches the shared
identity at `0x0040B280`. No address is solved from a compared field.

The unchanged 254B queue pump also owns these complete contributions:

| Native head | Semantic body / compared extent | Canonical unit |
| --- | ---: | --- |
| `0x00567E10` | 8B / 8B | `glyph_queue_pump_unwind_0` |
| `0x00567E18` | 8B / 8B | `glyph_queue_pump_unwind_1` |
| `0x00567E20` | 8B / 13B | `glyph_queue_pump_unwind_2` |
| `0x00567E2D` | 39B / 39B | `glyph_queue_pump_eh_handler_39` |

The three unwind actions release the first lock, second lock and task as
states become live; unwinding visits them in reverse order. The final
cleanup owns five original INT3 alignment bytes. The 39B handler performs
two security-cookie checks, then selects FuncInfo at `0x005A98E4` and the
established C++ frame handler.

The complete 60B metadata starts at `0x005A98CC`: three map entries followed
by 36B FuncInfo. Its four DIR32 fields bind the cleanups and map self-pointer.
The prior handler anchor and actual COFF offsets establish the cleanup
heads. Searching the complete metadata with the map self-pointer excluded
finds one `.rdata` location. All bytes and physical PE relocation sites
match. No EH extent is shortened to a prefix.

## Reproduction and retained controls

Only the pump source changed; no shared header changed. Its fifteen units
replay from one fresh object under `build/gpt61-function-move-canonical/`.
The unchanged task allocator object/receipt under
`build/gpt61-glyph-apply-canonical/` are re-attested and reused for seven
complete units. The old `core1075-canonical` pump object/receipt are preserved.

```sh
nice -n15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueuePump254.cpp --existing-objects
nice -n15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTaskAllocatorConstruct.cpp --existing-objects
nice -n15 scripts/repo-python scripts/verify-glyph-func-swap188-native.py
```

Private evidence is in `.analysis/glyph-function-move-session/`: `native.c`,
`ghidra-log.txt`, `move-proof.txt`, `eh-proof.txt`, `pump-replay.txt`,
`allocator-replay.txt`, `native-proof.txt` and `verifier-controls.txt`.
Controls reject a corrupt move leaf, wrong state count, flags or map owner,
and the old 161B extent. The pump checker passes. The nine-helper checker
passes its nine owned bodies and pump, then reaches a pre-existing stale
ASCII destructor receipt; that unrelated source/provider was not rebuilt.

Next useful game-owned work is the unresolved 294B text submission method at `0x0044FFF0`.
The 578B/586B text-formatting callers remain separate compiler frontiers.
