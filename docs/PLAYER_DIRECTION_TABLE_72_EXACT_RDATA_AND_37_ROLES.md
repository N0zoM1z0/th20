# CORE/RECON-729 — original Player 9×2 direction data and all 37 main-frame data-reference roles

**The original signed Player movement direction table at 0x00572C48 is now implemented by a genuine external C++ read-only object. Its 72 data bytes match the immutable TH20 original PE exactly.** The separately sourced 3,111-byte Player main-frame Boss remains NONEXACT. This is real gameplay data recovery, **not a new complete game-code function**.

Original target: Japanese TH20 v1.00a Steamless resources/th20.exe, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Actual original game data and corrected C++ ownership

The complete immutable original 72-byte table at physical 0x00572C48 lies in the actual original PE .rdata section at file offset **0x171648**. It contains nine ordered pairs of signed 32-bit little-endian integers:

| Direction index | Original X | Original Y |
| ---: | ---: | ---: |
| 0 | 0 | 0 |
| 1 | 0 | -1 |
| 2 | 0 | +1 |
| 3 | -1 | 0 |
| 4 | +1 | 0 |
| 5 | -1 | -1 |
| 6 | +1 | -1 |
| 7 | -1 | +1 |
| 8 | +1 | +1 |

The original 72-byte SHA-256 is **4cf7f804794295868934c5ed0b405f2737beee23ef953538799354b612402f7d**. The already maintained Player main at src/PlayerMainFrame.cpp indexes the original two dimensional scalar array in the correct native way: table[Player+0x67C][0] and table[Player+0x67C][1]. Its real original i386 code at function offsets +0x5E3 to +0x616 contains the otherwise surprising zero-index IMUL and zero-shift instructions. The older flat IntPoint[9] source hypothesis had equivalent values but a different real compiler instruction stream, and was previously rejected using original PE opcode evidence.

**The repository previously provided only an extern declaration** for this table, without any maintained definition. New real source src/PlayerDirectionTable.cpp now provides exactly one externally linked definition with all nine original signed pairs and an explicit compile-time 72-byte size assertion. No game-binary patch, reinterpret-cast table, duplicated per-call storage, assembly or fabricated padding is involved.

## Exact native MSVC data and genuine external symbol

Under pinned 32-bit MSVC 19.44 C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc, the new real production file emits **one 72-byte eight-byte-aligned .rdata section**. Its actual generated data contents are byte-for-byte identical to the entire physical original PE table, with the same 72-byte SHA-256.

The genuine C++ exported symbol is:

    ?native_player_direction_table@th20@@3QAY01$$CBHA

It exactly matches the two existing actual PlayerMainFrame.obj DIR32 source symbols at function displacement fields **+0x5F7 and +0x612**, ordinally corresponding to actual original physical PE HIGHLOW fields and original target **0x00572C48**. The complete 3,114-byte Player main was separately rebuilt after introducing the data owner: all 3,114 native code bytes, all 783 instruction heads, all 67 REL32 and 37 DIR32 symbol fields stayed unchanged from the immediate preceding whole-source compilation.

## Every original Player main absolute data role independently authenticated

A fresh original PE .reloc walk establishes **37 real HIGHLOW fields** in the complete original 3,111B function at 0x004F9C30, matched ordinally against 37 actual COFF DIR32 fields from the whole 3,114B maintained source. Those 37 have been proven by more than equal counts:

| Physical original data role | Original fields | Independent native proof |
| --- | ---: | --- |
| process_input_inf, process_sound, process_input_views, native_one, native_two, current_animation_pool, native_128 | **34** | Same C++ symbol and original target physically attested in separate previously strict-exact canonical whole-method receipts |
| Original Player 9×2 signed direction table | **2** | New real production .rdata definition with 72/72 original PE bytes and matching external C++ symbol |
| Original NUL-terminated effect animation script name | **1** | Genuine MSVC-private string label $SG208275 contains the exact 7-byte original PE string "effect" plus NUL at **0x0056EC84** |
| **Total** | **37/37** | All independently grounded original PE data roles, zero inconsistent targets |

The compiler-generated string is not invented as a new public data symbol; it already exists as genuine private .rdata in PlayerMainFrame.obj. Its full 7/7 original bytes were independently compared against original executable data.

**The entire Player main is still NONEXACT.** Ordinally correct global source identities and original data bytes do not solve the remaining register, stack-local, branch-offset and relocation-site differences. Its original 3,111B/783 x86 differs from the maintained 3,114B/783 x86, despite 783/783 original mnemonic kinds in order and 67/37 actual E8/absolute field counts. The separate 555B Player movement remains NONEXACT too.

## Reproducible source and evidence

- src/PlayerDirectionTable.cpp — newly maintained natural C++ game source for the real external signed 9×2 array, with a compile-time layout check.
- build/core729-probes/PlayerDirectionTable-production.obj — compiled actual new source with one .rdata data symbol, 72-byte section and complete original byte equality.
- build/core729-probes/PlayerMainFrame.obj — freshly recompiled whole Player main source, with all 3,114 bytes and relocation symbol roles unchanged by adding the independent data owner.
- .analysis/core728-player-main-all-37-PE-data-roles.py/json — all 37 original physical PE HIGHLOW targets against actual ordinal C++ COFF symbol roles; 34 independently canonical-attested and three newly resolved.
- .analysis/core729-original-player-72B-data-and-37-main-data-roles.json — exact original/compiled data SHA, PE section/file address, real symbol, exact 7-byte effect string and two original main table references.
- PLAYER_MAIN_FRAME_NATIVE_9X2_DIRECTION_TABLE.md — older original opcode and 9×2 indexing proof, now extended by the new actually compiled table definition.

**No original executable, previously accepted C++ source, shared header, canonical strict unit, match manifest, earlier relocation target or original game-code credit was changed.** The new 72B read-only game-data recovery is separate from authored .text bytes. No global cold replay ran. The strict game-code baseline remains **546 complete functions /186,351 disjoint original bytes**; the whole game remains not yet linked/playable.
