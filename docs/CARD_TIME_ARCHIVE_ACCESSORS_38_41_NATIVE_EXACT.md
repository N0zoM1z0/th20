# Card clock archive: 38B and 41B game selectors whole strict exact

The immutable selected Japanese TH20 Steamless v1.00a executable is SHA256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

The accepted [645B Card clock settlement Boss](CARD_CLOCK_BOSS645_CALLBACK37_STRICT_EXACT.md)
uses two separate native record selectors to write or recover an encoded
time. Their source is now reconstructed in
**src/CardTimeArchiveAccessors38_41.cpp**:

| Physical original | Recovered native ownership | Full native match |
| --- | --- | --- |
| 0x00488740 | Primary record via 50 pointers at receiver+0x20, calling native 22B indexed pointer-slot accessor 0x00414580 | **38/38B**, 15 x86, 1 E8, 0 HIGHLOW |
| 0x00488770 | Alternate 44-byte-stride record table at receiver+0xE8, returning the original slot+0x10 pointer; calls the native 20B stride indexer 0x00486E30 | **41/41B**, 15 x86, 1 E8, 0 HIGHLOW |
| 0x00486E30 | General 44-byte array element accessor, source-defined 20B/9-instruction index helper | **20/20B**, 9 x86, 0 E8/HIGHLOW; origin held review, **not credited as authored** |

The original complete-body SHA-256 values respectively are:

- 38B: 5f48bb4da1245bfaf0b30ef8b3b11fa2a4080dc49c38cd6f7b1604340367da8f
- 41B: 0161cabfee8293db70aa366e0a193190568abee5cde6e9707d80045c5d89ead0
- 20B: 33b39b0c90faa5ff9aa9c9bf53adeedd1be72cb87b1e4c5bba1183ad916cd171

The source retains a **C array of 50 real four-byte pointer slots**
(200B from +0x20 through +0xE7) and a borrowed array of genuine 44B
raw record slots. Record field semantics not established by original
callers remain bytes, not invented named members or fake padding.
The sole proven member at slot+0x10 is read as a pointer.

Using std::array instead would generate additional 33B helper wrappers
that do NOT match original 22B and 20B indexed callee functions. The
ordinary C-array source naturally produces the complete native 22B and
20B indexers. The 22B pointer indexer at **0x00414580** is physically
identical to the **already canonical** Vector3 index unit, and was
verified against its original SHA and receipt; it is NOT credited twice.
The 20B record indexer has five native callers and compiler-like generic
behavior. Its source/native bytes are exact, but its original authorship
is not established. Accordingly its function remains under origin review
and is excluded from the **authored-game whole-exact byte ledger**.

The independent
**scripts/verify-card-time-archive-accessors-native.py** checks whole
original bodies and SHAs, exact native E8 target sites, zero HIGHLOW
fields, generated COFF bodies and strict receipts for all three new
source units. It also independently checks the previously accepted
22B folded indexer and the original 645B parent E8 callsites.

Only one affected translation unit was rebuilt, without full replay:

    card_time_primary_archive_38: exact (38/38 bytes)
    card_time_alternate_archive_41: exact (41/41 bytes)
    card_time_raw_record_index_20: exact (20/20 bytes)
    Exact replay: 3/3 units, 1 cold objects
    vector3_index: exact (22/22 bytes), existing receipt

To reproduce:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/CardTimeArchiveAccessors38_41.cpp
    scripts/repo-python scripts/verify-card-time-archive-accessors-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target

**Two newly credited game-authored heads, +79 original .text bytes.**
The 20B generic indexer is an additional exact compiler contribution
but does not count as authored game bytes. The 645B parent and 22B
folded child were credited in earlier separate checkpoints.
