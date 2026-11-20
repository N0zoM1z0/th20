# PlayerRecord Item progress operands — six exact 73B leaves

The 4757B ItemInf update and its PlayerRecord reward-progress children use
six additional clamp-on-read accessors. Each is now a real PlayerRecord
method in src/PlayerRecordItemProgressAccessors.cpp.

| Native | Method | Field bound | Exact body |
|---|---|---|---:|
| 0x004B80B0 | clamped_field_b8() | -1..7 | 73/73 |
| 0x004B8100 | clamped_field_bc() | 0..7 | 73/73 |
| 0x004B8150 | clamped_field_c0() | 0..10 | 73/73 |
| 0x00477FF0 | clamped_field_cc() | 0..10 | 73/73 |
| 0x004B7E70 | clamped_field_d0() | 0..10 | 73/73 |
| 0x004B7E20 | clamped_field_d8() | 0..7 | 73/73 |

Every whole body contains the original std::clamp<int> call at +0x2A to
0x00471170. All 69 non-relocation bytes are identical per function. These
are mutating accessors, not pure getters: each writes the bounded value back
to its actual PlayerRecord field before returning it.

They provide the real operands for the adjacent 246B/86B/172B/187B
PlayerRecord reward-progress functions and the ItemInf update reward switch.
