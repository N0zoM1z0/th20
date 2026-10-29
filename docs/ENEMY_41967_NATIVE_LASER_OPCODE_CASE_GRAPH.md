# CORE/RECON-716 — original 41,967-byte Enemy ECL Boss: native Laser opcode case ownership

**The original Enemy opcode dispatcher at 0x0048C010 remains NONEXACT.** This independent original x86 audit confirms the four game Laser parameter class construction/destruction paths inside the giant dispatcher without claiming any parent bytes as original strict exact.

Locked target: Japanese TH20 1.00a Steamless original PE, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Original compressed integer switch, independently attested

The actual original body is 41,967 bytes and 8,896 native x86 instruction heads, ending with the real RET at 0x004963FE. The opcode guard at 0x0048C090 subtracts 300 and compares the resulting integer index against 703. Original 0x0048C0A6 fetches a selector from **704 genuine byte values at 0x004966B8**. The opcode dispatch at 0x0048C0AD uses that selector to read **one of 174 original absolute code pointers at 0x00496400**. All 174 pointer fields were independently verified against immutable original PE IMAGE_REL_BASED_HIGHLOW relocation records, and all 174 original values point to real instruction boundaries inside the 41,967-byte function.

Earlier CORE_ENEMY_DISPATCH_LAYOUT correctly described this 704-byte/174-pointer compression scheme. This analysis re-reads the actual original PE table and individual native instructions, rather than assuming those older notes were right. Additional genuine four/eight-way nested tables belong to other ECL opcodes and are not confused with these four Laser command roots.

## Original Laser opcode routes and source-object lifetimes

| Actual opcode | Original compressed selector | Native original case start | Original case reachable x86 heads | Real native constructor E8 | Real native destructor E8 |
| ---: | ---: | --- | ---: | --- | --- |
| **702** | 154 | **0x004944C7** | 153 | **0x004944CD to 0x0047C130**, LaserType0Parameters | **0x00494766 to 0x0047C4B0**, LaserType0Parameters |
| **703** | 155 | **0x00494771** | 176 | **0x00494777 to 0x0047C030**, LaserType1Parameters | **0x00494A79 to 0x0047C490**, LaserType1Parameters |
| **711** | 163 | **0x00494CE7** | 141 | **0x00494CED to 0x0048B650**, LaserType2Parameters | **0x00494F47 to 0x0048B8B0**, LaserType2Parameters |
| **713** | 165 | **0x00494A84** | 137 | **0x00494A8A to 0x0048B5B0**, LaserType3Parameters | **0x00494CDC to 0x0048B890**, LaserType3Parameters |

Each original entry was selected from the actual compact opcode byte and the actual HIGHLOW code pointer. A bounded original x86 control-flow walk then followed each genuine JMP/Jcc to the common original epilogue at 0x004963DF. All four paths have zero unresolved indirect or out-of-body branch edges; every constructor/destructor E8 appears in its own opcode path. These reachable x86 head counts are **not** separately credited native function ranges or new exact parent bytes.

## Relation to native-exact children and the Bullet Boss

The four original Laser parameter constructor/destructor pairs are already complete canonical strict native exact under the maintained src/LaserParameters.cpp. CORE/ORIGIN-715 independently credited eight original parameter class bodies plus two LaserController context accessors as **ten game-owned complete original functions / 936 nonoverlapping bytes**; the 179B LaserController constructor and 263B reset were already credited and excluded.

The separate source-absent 12,140B Bullet::run_extended_commands original also creates/retires LaserType0/1 parameters in original command 27, with three original switch tables of 34+8+11 entries independently reverified. Both giant original Bosses remain **NONEXACT**. Previously accepted giant exact Bullet emitter, Bullet physics and Dialogue constructor bytes are not credited again.

## Reproducibility and scoped progress

- .analysis/core716-enemy-41967-Laser-opcode-native-case-CFG.py/json: original whole 41,967B/8,896 instruction body, 704 native compact opcode bytes, original PE HIGHLOW for all 174 primary table pointers and bounded original 702/703/711/713 CFGs with every constructor/destructor E8.
- .analysis/core715-laser-10-game-origin-original-pe-audit.py/json: independently strict original Laser class source bodies, 17 original E8/3 actual PE HIGHLOW within the ten credited methods and genuine two-Boss original native callers.
- .analysis/core713-bullet-12140-all-three-switch-CFG.py/json: distinct original Bullet game 34+8+11 native switch architecture.
- LaserParameters.cpp source-scoped MSVC cold replay previously passed **12/12 strict native units** in one affected-only object.

This is original big-Boss gameplay ABI evidence only. **No source, canonical object, original executable, original match unit, target relocation, game strict exact credit or full cold replay was changed.** Existing game-authored exact coverage remains **530 complete functions /183,382 disjoint original native bytes**.
