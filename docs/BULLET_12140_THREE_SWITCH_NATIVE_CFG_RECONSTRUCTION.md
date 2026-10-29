# CORE/RECON-713 — native complete 12,140B Bullet command Boss: all THREE nested switch tables and bounded original per-case control flow

**Original TH20 Bullet::run_extended_commands remains NONEXACT and has no complete maintained C++ method definition.** This newly original-PE-attested analysis corrects a material omission in CORE/RECON-710: the single 34-word command table is not all original switch data. Two actual nested 8-word and 11-word switch tables immediately follow it. All 53 words are individually confirmed HIGHLOW original PE relocations, and all three integer-guarded branches have been followed to recover every original command entry's bounded native CFG.

The locked target is the Japanese TH20 1.00a Steamless original PE with SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897. No source, MSVC canonical object, PE target or canonical original relocations are edited by this checkpoint.

## Actual native whole-Boss and complete 53-pointer switch metadata

The real original game function occupies 0x0047DCF0 through 0x00480C5B, inclusive, **12,140 complete original code bytes / 2,490 actual x86 instructions**. Its real return is at 0x00480C5B. After that RET, the original PE contains exactly three contiguous native switch tables:

| Actual original native indirect branch | Real integer maximum guard | Original PE table address | Original entries / bytes | Distinct native instruction entry heads |
| --- | --- | --- | ---: | ---: |
| 0x0047DE4D — primary BulletCommand opcode | cmp at 0x0047DE3A with 0x21 (33) | **0x00480C5C** | **34 / 136B** | 32 (case IDs 5/14/28 share original 0x00480C25) |
| 0x0047E8FF — command 4 nested subtype | cmp at 0x0047E8EC with 7 | **0x00480CE4** | **8 / 32B** | 7 (subtypes 1/4 share one code path) |
| 0x0047F48A — command 9 sprite/style selector | cmp at 0x0047F477 with 10 | **0x00480D04** | **11 / 44B** | 11 |
| **All three native tables** | Actual integer 0..33 / 0..7 / 0..10 | **0x00480C5C..0x00480D2F** | **53 HIGHLOW / 212B** | All entries real original instruction boundaries |

Each 32-bit field is extracted as an original little-endian absolute destination in the PE. Its *physical relocation field address* is independently present in the immutable IMAGE_REL_BASED_HIGHLOW relocation directory, not reverse-solved from a new object or inferred from a decompiler. All 53 original pointer values refer to actual instruction starts inside the single 12,140B body. The original function body itself has 38 further PE HIGHLOW fields, so the combined **whole Boss body plus three original tables has 91 distinct actual PE HIGHLOW fields**.

In particular, the old 34-word table analysis completely omitted the next 19 table words and the two nested switch decision graphs. Neither the original 32B nested subtype table nor the original 44B sprite/style table is a separately authored function. The additional 212 post-body bytes are native compiler/dispatch support and **are not counted as independent game-authored body credit**.

## Correct the Ghidra whole-function decompiler's original opcode type

The locked, hash-attested original Ghidra 12.1.3 whole-function decompiler output is preserved privately. Its 1,252-line automatic hypothesis declares the bullet command pointer as a float pointer, and consequently prints original integer case bit patterns as floating-point denormals: case 1 as 1.4013e-45, case 2 as 2.8026e-45, and so on. This is not game logic.

The immutable x86 instead loads the BulletCommand opcode from +0x20 into an integer local, compares the integer directly with 0x21, and dispatches through the primary native indexed DWORD table. The first inner table is similarly guarded by integer 7 after loading the command subtype from original command+0x18; the second inner table compares an integer sprite/style value selected from original bullet style/color data against 10. The correct future C++ is integer switch semantics with actual ECL operand word aliases, **not** floating-point comparisons against denormal values. Even the native source-typing hypothesis should be checked against exact original opcode/offsets; do not mechanically copy Ghidra's anonymous float locals.

## All thirty-four original case entry CFGs — actual calls by branch

Starting from the 34 original PE main-table targets, a bounded original x86 CFG follows each real direct JMP/Jcc and the **two separately attested nested indirect tables**, stopping at the shared native command advance 0x00480C25, the top of the next-command loop 0x0047DD36, and the native SEH return epilogue 0x00480C3F. This prevents later independent command iterations from spuriously appearing in every command case.

With both nested tables resolved, all **2,387 distinct case-reachable original x86 instructions out of 2,490** are identified, including **204 separate original E8 sites out of the 210** physically present in the whole Boss. There are **zero unresolved indirect branches within any case-reachable original path**. The six E8 sites outside case CFG are exactly:

- Original command-list/metadata prelude: 0x0047DD53, 0x0047DD5D, 0x0047DD7E, 0x0047DDA8 and 0x0047DDEC.
- Native security-cookie function epilogue: 0x00480C50.

Thus **all 210/210 original E8 call sites are accounted for by either a physical case CFG (204) or an independently original prelude/epilogue path (six)**. This is whole-original call-graph coverage, **not 12,140B exact compilation**.

A case's reported reachable instruction count is a native CFG reachability result, **not a separate disjoint body extent or isolated function byte credit**. Some original branches share real command-advance or setup labels; a case can have multiple possible outcomes. Nested case branches are included without inventing fake helper calls or recomputing unknown command operand aliases.

<!-- BEGIN AUTOMATED INDEPENDENT ORIGINAL CASE CFG TABLE -->
| Original command | Original PE entry | Case-reachable x86 heads | Real case E8 | Most frequent grounded native callee roles |
| ---: | --- | ---: | ---: | --- |
| 0 | 0x47dee2 | 23 | 3 | bullet_extended_commands_at (2), timer_assign_integer (1) |
| 1 | 0x47de54 | 32 | 3 | animation_interrupt (1), vector3_scale (1), vector3_subtract_assign (1) |
| 2 | 0x47df50 | 122 | 12 | bullet_extended_commands_at (7), clock_scalar_read (1), bullet_aim_selector (1) |
| 3 | 0x47e69c | 61 | 6 | bullet_extended_commands_at (4), timer_assign_integer (1), sound_effect_request_queue (1) |
| 4 | 0x47e7c4 | 270 | 29 | bullet_extended_commands_at (16), game_random_signed_unit (3), clock_scalar_read (2) |
| 5 | 0x480c25 | 0 | 0 | No direct E8 in this case path |
| 6 | 0x47ed51 | 89 | 8 | bullet_extended_commands_at (8) |
| 7 | 0x480036 | 5 | 0 | No direct E8 in this case path |
| 8 | 0x47f0ea | 35 | 3 | bullet_extended_commands_at (2), timer_assign_integer (1) |
| 9 | 0x47f194 | 267 | 14 | animation_reset (2), animation_file_load_script_whole (2), identifier_get (2) |
| 10 | 0x47f691 | 10 | 1 | bullet_cancel (1) |
| 11 | 0x47f6bd | 15 | 1 | sound_effect_request_at (1) |
| 12 | 0x47ef27 | 35 | 3 | bullet_extended_commands_at (3) |
| 13 | 0x47f6fc | 153 | 15 | identifier_get (3), 0x47c300 (2), hit_controller_auto_class_initialize (1) |
| 14 | 0x480c25 | 0 | 0 | No direct E8 in this case path |
| 15 | 0x47ff6c | 10 | 0 | No direct E8 in this case path |
| 16 | 0x47ff98 | 36 | 0 | No direct E8 in this case path |
| 17 | 0x480188 | 150 | 18 | bullet_extended_commands_at (9), vector3_add_assign (1), timer_assign_integer (1) |
| 18 | 0x480477 | 76 | 7 | angle_assign_float (2), timer_current_value (1), player_direction_to (1) |
| 19 | 0x4805e2 | 81 | 8 | bullet_extended_commands_at (6), motion_polar (1), timer_assign_integer (1) |
| 20 | 0x48077e | 26 | 3 | 0x4865d0 (1), 0x45e5b0 (1), 0x45e590 (1) |
| 21 | 0x47e427 | 127 | 12 | bullet_extended_commands_at (7), clock_scalar_read (1), bullet_aim_selector (1) |
| 22 | 0x4807e1 | 71 | 7 | float_interpolation_set_start (1), float_interpolation_set_end (1), 0x439460 (1) |
| 23 | 0x48093c | 50 | 4 | bullet_extended_commands_at (3), clock_scalar_read (1) |
| 24 | 0x480a37 | 53 | 3 | enemy_spawn_construct (1), link_previous (1), enemy_create (1) |
| 25 | 0x480b51 | 10 | 0 | No direct E8 in this case path |
| 26 | 0x47f063 | 30 | 2 | bullet_extended_commands_at (1), timer_assign_integer (1) |
| 27 | 0x47f99f | 296 | 21 | identifier_get (2), 0x47c570 (2), clock_scalar_read (2) |
| 28 | 0x480c25 | 0 | 0 | No direct E8 in this case path |
| 29 | 0x480b7d | 26 | 1 | bullet_radius (1) |
| 30 | 0x47efdb | 30 | 2 | bullet_extended_commands_at (1), timer_assign_integer (1) |
| 31 | 0x48004d | 59 | 6 | bullet_extended_commands_at (5), timer_assign_integer (1) |
| 32 | 0x47e1a9 | 129 | 12 | bullet_extended_commands_at (7), clock_scalar_read (1), bullet_aim_selector (1) |
| 33 | 0x480bfa | 10 | 0 | No direct E8 in this case path |

<!-- END AUTOMATED INDEPENDENT ORIGINAL CASE CFG TABLE -->

## Two independently original nested switch tables completely mapped

The 8-way nested original switch under main command 4 has subtype IDs 0..7. IDs 1 and 4 enter the same native case code at 0x0047EA52. The 11-way nested original sprite/style switch under main command 9 has IDs 0..10 and eleven different native entry heads. Their native original jump pointers and physical original PE HIGHLOW fields are listed below.

<!-- BEGIN AUTOMATED INDEPENDENT NESTED TABLES -->

### command-4-subtype

| Native subtype | Genuine PE HIGHLOW address | Original native instruction target |
| ---: | --- | --- |
| 0 | 0x480ce4 | 0x47e906 |
| 1 | 0x480ce8 | 0x47ea52 |
| 2 | 0x480cec | 0x47e937 |
| 3 | 0x480cf0 | 0x47e9e2 |
| 4 | 0x480cf4 | 0x47ea52 |
| 5 | 0x480cf8 | 0x47eade |
| 6 | 0x480cfc | 0x47ea83 |
| 7 | 0x480d00 | 0x47eb38 |

### command-9-sprite-style

| Native subtype | Genuine PE HIGHLOW address | Original native instruction target |
| ---: | --- | --- |
| 0 | 0x480d04 | 0x47f491 |
| 1 | 0x480d08 | 0x47f4ad |
| 2 | 0x480d0c | 0x47f4f3 |
| 3 | 0x480d10 | 0x47f51a |
| 4 | 0x480d14 | 0x47f52c |
| 5 | 0x480d18 | 0x47f53e |
| 6 | 0x480d1c | 0x47f550 |
| 7 | 0x480d20 | 0x47f5c9 |
| 8 | 0x480d24 | 0x47f5ed |
| 9 | 0x480d28 | 0x47f611 |
| 10 | 0x480d2c | 0x47f635 |

<!-- END AUTOMATED INDEPENDENT NESTED TABLES -->

## Distinguish real original source progress from unproved whole-byte exactness

The original symbol is independently identified as th20::Bullet::run_extended_commands() from **two previously strict-exact whole game callers and their authentic C++ COFF E8 relocations**: original 3,735B Bullet emitter at 0x004826B5 and original 1,846B Bullet physics at 0x00485D7B. These physical original E8 both enter 0x0047DCF0, with the same real class method symbol, and both caller bodies remain whole strict exact.

The canonical BulletCommand source layout in BulletValues.hpp has the actual 32-bit opcode at +0x20, the actual subtype operands, and Bullet carries its real 64-bit command_flags at +0x90 and command vector owner at +0x98. A genuinely complete future C++ switch must use these typed members, preserve the 24-command index/metadata vector guard, reproduce all 34 commands and both subtype switch trees, authentic per-case state/timer updates, original 210 call roles, native SEH and genuine 38+53 PE HIGHLOW fields. It must not use floating-point Ghidra case-label artifacts, copied disassembly, assembly jumps, artificial compiler spills or fake child methods.

The original project **still has no complete C++ body** for the 12,140B member, and this analysis by itself does not add that source. It remains high-confidence game-owned but source-absent, unclassified, NONEXACT, and receives **zero original body credit**. The current game-authored strict total remains **520 whole functions / 182,446 original disjoint bytes**.

## Reproducible bounded evidence

- .analysis/core709-bullet-12140-original-switch-callgraph.py/json: original complete 12,140B/2,490 x86, 210 original E8 and the primary 34-case table (historically incomplete table scope).
- .analysis/core710-bullet-dispatcher-12140-game-owner-proof.py/json: two independently original strictly exact Bullet game callers and real compiled C++ E8 symbol identity.
- .analysis/core711-bullet-12140-original-whole-decompile.txt and core711-bullet-12140-ghidra-attested.log: locked/attested original 1,252-line whole decompiler hypothesis and its wrong floating-point opcode-type inference.
- .analysis/core712-bullet-original-34-case-CFG.py/json: first original native CFG pass exposed two unresolved indirect switch edges and only 184/210 original E8 case coverage, proving primary-only analysis was incomplete.
- .analysis/core713-bullet-12140-all-three-switch-CFG.py/json and core713-bullet-12140-three-table-native-CFG.log: actual **34+8+11 original PE switch words, 53 independently original HIGHLOW, all three integer guards, 2,387 case-reachable original instructions and 204 original E8 case call sites**, six genuine prelude/exit sites and zero unresolved indirect case branches.
- The previously accepted complete 3,735B Bullet emitter (3,832B whole contribution) and 1,846B Bullet physics (1,864B whole contribution) are individually unchanged and exact.

No original executable or canonical source/object was altered, no new match unit or authored bytes were claimed, and **no full cold replay was run**. Only original native whole Boss control-flow evidence and source-handoff descriptions are corrected.
