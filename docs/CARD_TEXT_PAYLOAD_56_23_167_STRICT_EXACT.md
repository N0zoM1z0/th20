# CORE/RECON-1007 — whole-original Card text payload 56B/23B and 167B PMR string copy exact

Locked Japanese TH20 v1.00a Steamless target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The **1,896B/512-i386 original Card::start_spell** at `0x00487C30` creates a
Card text task and later destroys its string capture. Rather than hiding the
operation in an unnamed `void*` callback, a natural typed **36-byte capture**
is now recovered as [`NativeCardTextPayload`](../src/NativeCardTextPayload.hpp):
Card* at `+0`, a real `std::pmr::string` at `+4` and a borrowed Animation*
at `+0x20`. It is the native payload of the original Card name/animation
closure; no fabricated vtable, inherited class or arbitrary padding is used.

The normal C++ constructor copies its PMR string member. An empty
out-of-line destructor invokes the standard member destructor naturally.
The compiler also instantiates the original PMR string copy constructor;
all three complete bodies are now maintained in one file,
[`CardTextPayloadNative.cpp`](../src/CardTextPayloadNative.cpp).

| Original physical head | True entire body | Native call and PE role | Parent |
| --- | ---: | --- | --- |
| `0x00486B70` payload constructor | **56B /21 i386** | E8 `+0x21` to genuine PMR copy constructor `0x0046A780` | Original 1,896B start E8 `+0x30D` |
| `0x0046ADE0` payload destructor | **23B /11 i386** | E8 `+0x0D` to existing exact PMR string destructor `0x00449240` | Original 1,896B start E8 `+0x33F` |
| `0x0046A780` generated PMR copy constructor | **167B /54 i386** | E8 at `+0x31/+0x3B/+0x58/+0x73/+0x86` to five real STL/allocator providers, original PE HIGHLOW `+0x06` EH handler `0x00568CFD`, `+0x15` security cookie `0x005B25C0` | Invoked by the original 56B constructor |

The PMR copy body has native SHA-256
`dac331f72705a53ef1c0e4f6b038420924fef85570274e6a330db00aff997294`.
The constructor and destructor original body hashes are independently
pinned in [`verify-card-text-payload-native.py`](../scripts/verify-card-text-payload-native.py).
The verifier checks the immutable entire physical bodies, genuine return
instructions, all seven original E8 destinations and two original PE HIGHLOW
field locations. The 1,896B parent is independently SHA-pinned, and the
true original call sites are verified; no relocation target is inferred
from the candidate COFF value.

Locked MSVC 19.44 i386 C++20 emits all **246 original `.text` bytes**
with complete PE relocation role fidelity. One canonical provider object
and fresh receipt pass three strict comparisons:

```text
card_text_payload_ctor_56: exact (56/56 bytes)
card_text_payload_dtor_23: exact (23/23 bytes)
card_text_payload_pmr_copy_167: exact (167/167 bytes)
Exact replay: 3/3 units, 1 cold objects
```

Original source ownership of the wrapper constructor, destructor and
lambda capture is not proven, while the 167B body is standard-library
compiler code. Consequently all three are classified
`origin=unknown/review`, accepted as **three distinct complete physical
strict units /246 native bytes**, with **zero credited authored-game
heads/bytes** until the ownership question is resolved. The previously
accepted PMR destructor at `0x00449240` retains its own physical credit.

This closes the *typed captured payload* subchain but not the original
text task creation, enqueue, unwind or scope. The full 1,896B Card start
parent remains **NONEXACT**. No original binaries or generated objects
are committed; no all-graph cold replay is run.

```sh
scripts/repo-python scripts/verify-card-text-payload-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardTextPayloadNative.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1008: payload integrated into maintained Card start source

The [full-route, NONEXACT Card start candidate](CARD_START1896_TYPED_NATIVE_FRONTIER.md)
now constructs and destroys the *real* `NativeCardTextPayload` around its
text task submission scope, rather than hiding the already exact 56B/23B
lifetime inside a single speculative function call. The original 1,896B
parent remains unaccepted while the text queue and EH details are open.
