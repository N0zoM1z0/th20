# CORE/RECON-1031 / corrected CORE/RECON-1037 — original 22B PMR string c_str, exact

**Corrected receiver and canonical owner:** The original `0x0044BAF0`
(22B/10 i386) is the native **`std::pmr::string::c_str() const`** method
on the string embedded at `NativeCardTextPayload+4`.
Its original SHA-256 is
`43bd0312020d597cfa7218127be88cc8f928d51c1671f92cda054524d49f043b`.
The actual Card text callback at `0x00486E80` adds 4 to the capture
pointer **before** E8 `+0x10`, proving the receiver is the string,
**not the full 36B Card capture**. The `c_str()` implementation then
adds 4 to reach the nested `_String_val` and invokes its real
`_Myptr` at `0x0040F2C0` via E8 `+0x0D`.
The earlier provisional `NativeCardTextPayload::name_c_str_44baf0`
method happened to reproduce identical machine bytes but had the
**wrong receiver semantics**. That source method has now been removed;
see the independent [complete 111B Card callback native proof](CARD_TEXT_CALLBACK111_STRICT_EXACT.md)
for the corrected call graph and corrected canonical C++ owner.

The ordinary `text.c_str()` in the actual
[`src/CardTextCallback111.cpp`](../src/CardTextCallback111.cpp)
causes MSVC to instantiate the true `std::pmr::string::c_str`,
matching all **22/22** original bytes, **18/18 nonrelocation** bytes,
and the sole original native relocation to `0x0040F2C0`.
The same original 22B physical unit `card_text_capture_cstr_22`
remains independently exact after its canonical source migration;
**no new original physical bytes are credited** for the correction.
Its generic standard-library source origin remains
`origin=unknown/review`, not game-authored.

The corrected proof checks the whole immutable original 22B and 111B
bodies, the original Card subobject pointer adjustment and all five
original callback relocation roles. The revised include-closure
regression passed **8/8 exact units from three cold objects**.

```sh
scripts/repo-python scripts/verify-card-text-callback111-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/CardTextPayloadNative.cpp \
  --source src/CardStartSpell1896.cpp \
  --source src/CardTextCallback111.cpp
```

## CORE/RECON-1038 — native `_Myptr` implementation separately accepted

The physical E8 `+0x0D` below this corrected PMR `c_str` now targets a
[whole-exact original 54B `_String_val::_Myptr` source unit](CARD_TEXT_STRING_MYPTR54_STRICT_EXACT.md).
The canonical 22B `c_str` remains unchanged, exactly once counted,
with the same correct embedded-string receiver.
