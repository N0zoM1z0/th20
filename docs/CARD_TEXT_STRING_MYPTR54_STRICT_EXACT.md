# CORE/RECON-1038 — whole original 54B PMR String_val::_Myptr exact beneath Card text callback

Locked original: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The native `0x0040F2C0` is a **complete 54B/21-i386**
`std::_String_val<Char>::_Myptr() const` body with SHA-256
`c3a6a6bc297539e707d0ab4e7f8bf1336e9fab94acc6b28a65da5486b2a2ea03`.
It is physically called by the actual **22B**
`std::pmr::string::c_str()` method at `0x0044BAF0` via genuine
E8 `+0x0D`. That caller is itself invoked by the separately whole-exact
**111B Card text callback** at `0x00486E80`, with the receiver being
the real embedded PMR string at `NativeCardTextPayload+4`.

The native 54B helper tests the real string storage capacity before
returning either the small-string inline buffer or the large-string
allocated pointer. Its two original physical E8 targets are
`+0x12 -> 0x0040F180`, a **42B** original `_Large_mode_engaged`
helper, and `+0x24 -> 0x0040B280`, an **8B** original
`std::_Unfancy` pointer helper. Both lower heads are **already**
strict exact in independent canonical providers; neither is
reconstructed or credited again here. The 54B body has **zero PE
HIGHLOW**.

[`verify-card-text-myptr54-native.py`](../scripts/verify-card-text-myptr54-native.py)
checks the entire immutable original 54B body and its 21 decoded
instructions through native `ret`, both exact E8 instructions and the
absence of HIGHLOW. It also hashes the entire original 22B `c_str`
caller and proves the genuine `+0x0D` edge to this physical head.

The ordinary `text.c_str()` in the correctly typed
[`CardTextCallback111.cpp`](../src/CardTextCallback111.cpp)
instantiates the genuine standard-library `_String_val::_Myptr` method,
with **46/46 nonrelocated original code bytes**, two original call
field locations, types and destinations. Locked MSVC 19.44 x86 C++20
replays all **54/54** original native bytes. One scoped source object
covers this new helper and its two unchanged original parent units:

```text
card_text_capture_cstr_22: exact (22/22 bytes)
card_text_callback_111: exact (111/111 bytes)
card_text_string_myptr_54: exact (54/54 bytes)
Exact replay: 3/3 units, 1 cold objects
```

This contributes **one new whole strict unit /54 distinct physical
original native code bytes**, but the generic C++ STL/PMR source owner
is `origin=unknown/review`. It earns **zero new credited game-authored
heads/bytes**. The two previously accepted 42B/8B lower functions
are not counted twice. The original 578B ASCII text renderer and
1,896B Card start Boss remain separately SOURCE-PRESENT/NONEXACT;
no transitive or full-game exactness is claimed.

```sh
scripts/repo-python scripts/verify-card-text-myptr54-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardTextCallback111.cpp
```
