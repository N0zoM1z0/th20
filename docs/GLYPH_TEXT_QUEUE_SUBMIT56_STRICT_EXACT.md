# CORE/RECON-1060 — complete original 56B glyph text render queue bridge, whole strict exact

Immutable target: Japanese TH20 v1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x004162F0` is a **complete 56B/22-i386** game-owned
text render queue submission method, native SHA-256
`5213451236ddccc50439af53540e50639d92771ca89506c80233331e217ebac9`.
Its entire original 2,227B glyph text core caller at `0x00415830`
physically invokes this method via E8 `+0x824` after constructing
the real 132B glyph render job and wrapping it in `std::function`.

The method receives a borrowed existing **40B
`std::function<void()>&`**, not a new by-value-owned task. It reads
the actual nested queue child pointer from **receiver `+0x04`**, forwards
a pointer to the borrowed function through the authentic MSVC C++
standard-library `std::_Unfancy`, and passes that existing callable
as an rvalue reference to the **151B game-owned queue append method**
`0x004131E0`. The physical original E8 graph is:

| Native call site | Real physical target |
| --- | --- |
| E8 `+0x0D`, relocation field `+0x0E` | `std::_Unfancy` folded 8B helper `0x0040B280` |
| E8 `+0x2C`, field `+0x2D` | original game queue append 151B `0x004131E0` |

The complete original 56B method has **zero PE HIGHLOW** and ends
with `ret 4`, confirming one borrowed four-byte stack argument.
The native 8B folded standard-library helper is already exact in an
independent provider and is not duplicated here. The 151B queue
append is a separate, as-yet unaccepted original code owner.

The maintained source is
[`src/GlyphTextQueueSubmit56.cpp`](../src/GlyphTextQueueSubmit56.cpp)
on the true nonowning [`NativeGlyphQueueView`](../src/NativeGlyphTextQueueView.hpp)
interface. It uses the original meaningful internal field and genuine
`std::_Unfancy(&task)` forwarding, then calls the real unresolved
`append_4131e0` implementation; neither call is replaced with a
fake body. Ordinary `std::move(task)` alone compiled a **33B**
method with **one** E8; passing a by-value `std::function` introduced
unobserved EH/destruction and compiled to **97B**. The correct
native borrowed-reference/std::_Unfancy source naturally emits
**56B/22 instructions**, all **48/48 nonrelocated original bytes**,
with both authentic original E8 positions, symbols and destinations.
This is not an opcode patch, dead padding, or manual shortcut.

Independent read-only proof
[`verify-glyph-text-queue-submit56-native.py`](../scripts/verify-glyph-text-queue-submit56-native.py)
SHA-pins the full native 56B/22 body, both physical E8 destinations,
actual receiver `+4` pointer load, `ret 4`, absence of HIGHLOW, the
entire immutable 2,227B original parent E8 `+0x824`, and the full
151B original backend SHA. With pinned MSVC 19.44 i386 C++20, this
one new physical function is admitted as a separate strict unit:

```text
glyph_text_queue_submit_56: exact (56/56 bytes)
glyph_text_job_capture_132: exact (132/132 bytes)
Exact replay: 2/2 units, 2 new/captured objects
Related 93B std::function copy and its five siblings:
  6/6 units exact, 1 local existing owner rebuilt when receipt expired
```

This adds **one new game-authored exact head /56 original executable
`.text` bytes**. The previously exact 132B glyph job capture, folded
8B forwarding leaf and earlier source-present 2,227B core are not
credited again. Correcting the parent source's task ownership to
construct an lvalue then call this borrowed-reference method changes
its nonexact candidate to **2,072B/484-i386, 25 E8/54 DIR32**, matching
native 25 E8 count but **not** its original 2,227B/470-i386, 43
physical HIGHLOW. The original 151B queue backend and 102B
std::function wrapper remain separate research targets.
No broad/unfiltered full cold replay was run.

```sh
scripts/repo-python scripts/verify-glyph-text-queue-submit56-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextQueueSubmit56.cpp \
  --source src/GlyphTextCore2227.cpp
```

## CORE/RECON-1061 — original list backend and five exact nested methods

The original 151B native list Emplace invoked by this strict 56B
queue bridge is now [maintained as an actual
`std::pmr::list<std::function<void()>>` source frontier](GLYPH_QUEUE_LIST_59_124_34_19_48_STRICT_EXACT.md).
It remains NONEXACT at 130B/44 generated C++20 versus 151B/51 native,
but five distinct original standard-library child code heads
(59B/124B/34B/19B/48B) are whole strict exact from one canonical
source/receipt. The original 56B game bridge and 132B job capture
remain independently accepted; generic code is not double-counted.
