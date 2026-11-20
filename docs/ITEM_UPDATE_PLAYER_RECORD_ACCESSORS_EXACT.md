# Item update PlayerRecord scalar dependencies — strict native leaves

The 4,757-byte `ItemInf` update parent at `0x004C25A0` and its reward helpers query and mutate several fields of the real 240-byte `PlayerRecord`. Four additional complete PlayerRecord methods now have natural typed C++ implementations and independent match units.

| Native | Method | Native field operation | Whole-body replay |
|---|---|---|---|
| `0x004C4B30` | `clamped_field_40()` | clamp field_40 to 10,000..1,000,000 | 64/64 bytes |
| `0x004B82C0` | `clamped_field_44()` | clamp field_44 to 0..1,000,000 | 64/64 bytes |
| `0x004B8300` | `clamped_field_48()` | clamp field_48 to 5,000..10,000 | 64/64 bytes |
| `0x004C46A0` | `add_field_3c_clamped(amount)` | increment field_3c then clamp to 0..1,000,000 | 75/75 bytes |

All four are real methods on `PlayerRecord`, not address-based helpers. The compiler emits the original `std::clamp<int>` REL32 call at the same offset (`+0x27` for the three getters, `+0x36` for the mutator) to the original helper at `0x00471170`. The dedicated source is `src/PlayerRecordItemUpdateAccessors.cpp`.

These boundaries are used by the ItemInf reward/display helper cluster (`0x004C47C0`, `0x004C4960`, `0x004C4B90`) and the large update callback. The parent update and the 307/453/523-byte reward helpers remain separate open reconstruction targets; their existence is not inferred from these leaf matches.
