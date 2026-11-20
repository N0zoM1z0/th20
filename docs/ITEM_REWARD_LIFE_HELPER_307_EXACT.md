# Item life/power reward helper — whole native 307B exact

The original helper at `0x004C47C0` is now a natural `item_award_life_reward(Item*)` method in `src/ItemRewardHelpers.cpp`. It is the first of the four reward helpers called by the 4757B ItemInf update parent to be fully restored.

The source retains the native order and real owners:

1. Read the current PlayerRecord option-unit count and cap.
2. If the cap is reached, read the clamped score value, round it down to a multiple of ten (with a minimum of ten), enqueue the green score popup at the Item position, and update the Session score.
3. Re-read the PlayerRecord and option cap, then update the field_30 progress threshold.
4. When a threshold boundary is crossed, rebuild Player option animations, enqueue the native negative-value popup, and request the positional sound effect.

The pinned x86 candidate is **307 bytes**, exactly the original whole body. All **18 E8 call sites** and both original **DIR32** fields have the same physical offsets and target identities. The remaining **227 non-relocation bytes** are byte-identical; no ASM, padding, or inert compiler-shaping locals are used.

This exact child is not the parent update: the 4757B `ItemInf` update and the other three reward helpers remain open.
