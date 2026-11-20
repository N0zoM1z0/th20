# Item reward helper cluster — natural C++ frontier

The Item update parent dispatches to four original reward helpers. Three now have natural C++ source in `src/ItemRewardHelpers.cpp`; two of the four helpers have strict whole-body matches.

| Native | Source method | Native bytes | Current candidate | Status |
|---|---|---:|---:|---|
| `0x004C47C0` | `item_award_life_reward(Item*)` | 307 | 307 | Exact |
| `0x004C4960` | `item_award_reward_type_1(Item*)` | 453 | 463 | Reconstructed, nonexact |
| `0x004C4B90` | `item_award_reward_type_0(Item*)` | 523 | 519 | Reconstructed, nonexact |
| `0x004C4DA0` | `item_award_reward_type_2(Item*)` | 346 | 346 | Exact |

The type-1 path reconstructs PlayerRecord's field_40/44/48 reward formula, the Player motion-parameter Y boundary, distance falloff, popup color, score award and field_3c update. The current compiler still spills two x87-derived integer intermediates differently from the original and is 10 bytes larger.

The type-0 path reconstructs the Player Y/motion threshold, the life-progress award, the capped score falloff, the Player animation reset, negative reward popup and sound. The current candidate is four bytes shorter than native; the original uses EBX/ESI/EDI for three live intermediates across a Player getter, while the current compiler spills those values to stack. It remains nonexact.

The type-2 path is exact at 346B. It follows the Item's actual Context to PlayerRecord, uses the shared `Context + 0x24` and `Context + 0x04` accessor heads, reads starting power, updates the progress threshold, resets Player animations, publishes the queue entry through the shared `+0x1C` accessor and adds the Session score. All 18 E8 physical call sites and four DIR32 fields match the original; all 258 non-relocation bytes match.

Together with the exact 255B reward popup queue, 26B queue lookup, 146B PlayerRecord threshold update, and the exact type-7 helper, this gives the 4757B ItemInf update a substantially more complete set of real gameplay dependencies. The parent update itself is still open.
