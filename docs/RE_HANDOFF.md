# TH20 reconstruction — current agent handoff

**Reconciled 2026-10-30, CORE/RECON-892.** Start here, then consult the
[evidence index](EVIDENCE_INDEX.md) for dated native experiments and original
PE proofs. The old 813-line handoff is in Git history at
git show 3e0f343:docs/RE_HANDOFF.md. **Historical checkpoint numbers and old
NONEXACT labels are not current acceptance facts.**

## Locked original target and accepted native coverage

| Verified item | Current state |
| --- | --- |
| Original PE | Japanese TH20 v1.00a **Steamless**, resources/th20.exe, 1,858,560 bytes |
| Required SHA-256 | a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897 |
| Embedded title/replay label | 1.00c in that **same** locked file, not a separate target |
| Provisional Ghidra function heads | **6,928**, not all native-confirmed boundaries |
| Source-present mapped methods | **1,288** across game, compiler and STL/library |
| Complete native strict units | **1,287**, supplied by **298** distinct canonical MSVC objects with **298** matching receipts |
| **Original authored-game whole-function exact** | **636 distinct physical game functions /233,662 original .text bytes** |
| Whole game linked/playable | **No** |

Get live status with:
scripts/repo-python scripts/report-reconstruction-status.py --summary

The origin ledger, provisional function inventory, full-native match manifest
and credited authored ledger are different facts. Exactly one physical
original function body may be counted once, even if distinct C++ template or
member aliases produce the same bytes. STL/compiler code remains excluded
from authored game-code totals. Progress percentages are **not** percentages
of the entire game binary.

## Already complete exact original bosses — do not reopen on old notes

| Original physical function | Whole-native strict proof |
| --- | --- |
| 0x0053B5C0 ECL runtime tick | **11,110B** exact, [ECL runtime](EXACT_ECL_TICK_RECONSTRUCTION.md) |
| 0x004818E0 Bullet emitter | **3,735B** original, **3,832B** whole compiler extent exact, [emitter proof](BULLET_EMITTER_3735_3832_STRICT_EXACT_RECONSTRUCTION.md) |
| 0x00481200 Bullet command-11 | **1,404B** exact, [state machine](BULLET_COMMAND11_1404_EXACT_RECONSTRUCTION.md) |
| 0x00421B00 InputDevice polling | **3,490B** exact, [input source](INPUT_DEVICE_POLL_3490_EXACT_RECONSTRUCTION.md) |
| 0x0043F6A0 Animation quad-submit renderer Boss | **3,159B /763 x86** whole original game body strict exact; **3,180/3,180B** including genuine NOP and five native relocated case-table pointers, 41 E8 plus 101 DIR32 independent roles, [full parent proof](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md) |
| 0x00539550 LZSS compressor | **1,036B** exact (historical 964B attempt was NONEXACT), [native compressor](ARCHIVE_LZSS_COMPRESS_1036_EXACT_RECONSTRUCTION.md) |
| 0x00447800 Animation factory | **73B** exact with coherent class tag and SDL ABI, [native allocation proof](ANIMATION_FACTORY_73_CLASS_TAG_STRICT_EXACT_RECONSTRUCTION.md) |
| 0x0044C9B0 Animation pool allocation | **298B** exact, [pool allocator](ANIMATION_POOL_ALLOCATE_298_EXACT_RECONSTRUCTION.md) |
| 0x0044CD00 Animation pool handle resolver | **456B /141 x86** whole strict exact, plus [159B/154B exact linked-list predicate and wrapper](ANIMATION_LINK_FIND_159_154_EXACT_RECONSTRUCTION.md), [original SprtID identity and 20 E8 proof](ANIMATION_POOL_RESOLVER_456_STRICT_EXACT_RECONSTRUCTION.md) |
| 0x004DDFE0 Graphics depth-write enable leaf | **Whole 92B /30 native x86 strict exact**, one real `Graphics+DBC` state-1 game transition; actual `IDirect3DDevice9::SetRenderState(14,1)`, original AnimationPool `flush_draws` E8 and one independent original PE HIGHLOW `0x005C0028` global. **92/92B** full pinned COFF and canonical relocated bytes exact; [independent native and whole strict proof](GRAPHICS_DEPTH_WRITE_ENABLE_92_STRICT_EXACT.md). Its 2,136B Mesh caller is already separately whole exact; no duplicate code credit. |
| 0x00443020 Animation Mesh mode24/25 render Boss | **Whole 2,136B /504 x86 native strict exact**, `0x130` frame /`ret 0xC`, all 32 original E8 and 20 true PE HIGHLOW physical sites/destinations, original D3DX XYZ matrix rotations, texture matrix/quad caching, original D3D9 FVF and texture stage state. **2,136/2,136B** canonical relocated code zero differences; [independent original and strict compiler proof](ANIMATION_DRAW_MESH2425_2136_STRICT_EXACT.md). Three genuine 5,993B main Draw dispatcher E8 callers; enclosing parent remains NONEXACT. |
| 0x004408B0 Animation whole 2,769B color/fog renderer Boss | **Whole 2,769B/683-i386 game-authored strict exact**, original `0x64` stack, 28 original E8 and 83 physical original HIGHLOW (78 body +5 after-RET pointers) all independently target/offset exact. Actual genuine 3B NOP, five original 2/2/1 case pointers and three physical entry heads, full **2,792/2,792 canonical relocated bytes zero differences**; [complete independent native/COFF proof](ANIMATION_DRAW_MODE6_2769_STRICT_EXACT.md). Enclosing 5,993B Draw dispatcher remains separate NONEXACT. |
| 0x00440340 Animation Mode6 1,378B screen-projection preparation Boss | **Whole 1,378B/335-i386 game-authored native strict exact**, true 17 original E8 /21 PE HIGHLOW physical fields, actual [2][3][4] screen offset tensor, real D3DX viewport/project and four strict projected XY subcalls; [complete independent native/replay proof](ANIMATION_DRAW_MODE6_SETUP_1378_STRICT_EXACT.md). Its 2,769B mode6 caller is separately whole strict exact; only the 5,993B enclosing dispatcher remains nonexact. |
| 0x004399B0 /0x00445B20 Animation Mode6 projection math | **73B Vector3 magnitude +86B projected XY rotate/translate =159 original game bytes**, each original whole strict exact. Five physical E8 sites in the original 1,378B Mode6 preparation parent, one real sqrt E8, no other data relocations. [Full original/strict projection math proof](ANIMATION_PROJECTION_MATH_73_86_STRICT_EXACT.md). Enclosing 1,378B Mode6 preparation remains open. |
| 0x00441430 Animation draw mode7 setup / matrix + corners Boss | **1,996B/459 i386 full original game-authored strict exact**, all original 11 E8 and 26 HIGHLOW physical sites, actual 3×64B matrix copies, D3DX XYZ rotations/multiplications, original parent/window translation and four Vector3 corners. [Full original PE/native strict proof](ANIMATION_DRAW_MODE7_SETUP_1996_STRICT_EXACT.md). Already strict 753B caller remains 753/753 after real int-return ABI symbol correction. |
| 0x0043B0E0 Animation five-vertex closed line-strip Boss | **Whole original 2,169B /533-i386 strict exact**, real `0x68` frame and 9-arg `ret 0x24`, native 65,536×20B renderer pool guard and typed 5-vertex closed contour. Corrected original D3D9 `D3DPT_LINESTRIP=3` (not triangle fan), five W1/XY/color stores, four exact 78B XY callee calls, **12/12 native E8 and 17/17 PE HIGHLOW** original site/targets, **2,053/2,053 nonrelocation and 2,169/2,169 full original relocated bytes exact**; [immutable native/strict proof](ANIMATION_SHAPE_LINESTRIP_2169_STRICT_EXACT.md). Original 5,993B main Draw parent remains NONEXACT. |
| 0x0043EF20 Animation rotated quad-corner projection Boss | **Whole semantic source PRESENT but strictly NONEXACT**: original 1,486B/372-i386, native `0x54` stack/RET0x14, 13 actual E8 and nine HIGHLOW PE roles. Natural C++ currently **1,485B/371 x86**, missing one genuine original `NOP` after Angle constructor at `+0x41`; an in-memory diagnostic only aligns **1,398/1,398 other nonrelocation bytes**, never patches bytes or credits this Boss. Genuine original 96B **2×3×4** corner table now has an externally linked natural C++ definition, compiled `.rdata` **96/96 exact**, [full original PE/source frontier](ANIMATION_CORNER_AXIS_96_ROTATED_1486_FRONTIER.md). Original 97B `draw_quad_mode1` E8 caller independently verified. |
| 0x0045FD10 polygon registry-to-group cdecl wrapper | **Whole original 47B/18-i386 strict exact**, authentic native EAX return forwarded from 296B configuration Boss rather than incorrectly discarded; original **2 E8 +2 PE HIGHLOW** site/target pairs and **47/47 relocated bytes**. Original global registry pointer `0x005B8894`, original type marker `0x0056EE68`, and original 156B registry resolver E8 documented; the resolver remains SOURCE-ABSENT/NONEXACT. [Original-only PE/COFF full native proof](ANIMATION_POLYGON_REGISTRY_WRAPPER_47_STRICT_EXACT.md). |
| 0x0045FC90 polygon palette Boss + 0x0045FFC0/0x0045FFA0 forwarding helpers | **Whole original 120B/39-x86 palette strict exact**, real original color zeroing and 32.0f radius, **5 E8/1 HIGHLOW original physical roles**. Both **31B/14-x86 tag `0x3D` color and `0x3E` radius forwarders** also whole strict exact (3/3 source-scoped units/one distinct /GS no-/sdl object); their likely template-generated origin remains **unknown/review** and excluded from authored game credit. **True adjacent 16.0f/32.0f `.rdata` 8/8B exact** as compiled externals. Old 296B/233B/23B/19B group methods stay strict exact after shared header split; [independent PE/COFF proof](ANIMATION_POLYGON_PALETTE_120_TAG_31_STRICT_EXACT.md). |
| 0x0045FB60 polygon group configuration Boss | **Whole original 296B/90-i386 native strict exact**, real `0x2C` frame/RET8, original three `0x3D4` segment palette records, control/Timer/input position and real Animation configuration; all **11 native E8 site/targets, zero original HIGHLOW and 296/296 relocated bytes** match. Removed seven redundant source block scopes generating eight extra compiler NOPs, retained all real used locals. All **4/4 units of same 297th previously accepted object** still exact; original 120B palette child remains open. [Independent original PE/COFF proof](ANIMATION_POLYGON_GROUP_CONFIG_296_STRICT_EXACT.md). |
| 0x0045F9B0 polygon Motion group Boss + 0x0045F400/0x0045FD40 native array helpers | **Whole original game Boss 233B/78 i386 strict exact**, genuine **3×`0x3D4`** segment array, native `+0xB9C` cached Vector3 and `+0xBA8` choice flag, all **9 original E8 +2 PE HIGHLOW** physical site/targets and **233/233 bytes**. Its separate **23B unchecked index and 19B array-end helpers** also whole strict exact in the same pinned object (3/3 units); likely template-like origin still **unknown/review**, deliberately excluded from authored code credit. Original **104B outline child remains NONEXACT**. [Native PE/COFF proof](ANIMATION_POLYGON_MOTION_GROUP_233_23_19_STRICT_EXACT.md). |
| 0x0045FB10/0x0045FAA0 Motion polygon fan and outline caller pair | **Whole original 76B/27-i386 TRIANGLEFAN caller strict exact**, three genuine E8 and one original HIGHLOW; direct call to previously exact 455B fan. Its sibling **104B/36-i386 outline caller is SOURCE-PRESENT/NONEXACT**: natural 102B/34-x86 misses original ESI save/restore and byte-offset computation ordering; it calls the exact 1,204B polygon Boss with native 16.0f stroke width. Both called by the original separate 233B parent; [original PE/strict source proof](ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md). |
| 0x0043D370 Animation polygon outline TRIANGLESTRIP Boss | **Whole original 1,204B/354-i386 strict exact**, true `0xA8` frame/RET0x18, first/interior/last polygon joins and native signed closed flag, four true by-value Vector2 compound leaf E8 calls, 20 original E8 and eight original PE HIGHLOW physical offsets/targets. **1,092/1,092 nonreloc and 1,204/1,204 whole relocated bytes**; [independent native PE/COFF proof](ANIMATION_POLYGON_OUTLINE_1204_STRICT_EXACT.md). Original **writes two 20B vertices per point but publishes only count×20B** in the persistent cursor—do not silently correct. Separate original 104B game caller and 5,993B main Draw parent stay NONEXACT. |
| 0x00439910/0x00439960 Vector2 compound value-return leaf pair | **Whole original 72B/24-i386 and 77B/26-i386 strict exact**, true mutating `operator*=(float)` and `operator+=(const Vector2&)` **return Vector2 by value** with hidden return pointer/`ret 8`, not `Vector2&`. Zero original E8/HIGHLOW fields; direct original 1,204B polygon outline parent E8 at `+0x2A9` and `+0x120/+0x1E0/+0x258` respectively; [independent original PE source/ABI and complete COFF proof](ANIMATION_VECTOR2_COMPOUND_VALUE_72_77_STRICT_EXACT.md). The 1,204B parent remains SOURCE-ABSENT/NONEXACT. |
| 0x0043EB40 Animation four-corner projector | **Whole original 985B/233-x86 strict exact**, native `0x24` frame and five-argument RET0x14, genuine **2 axes ×3 modes ×4 corners** source index at `0x56E140` and 16B grouped mode stride. All **6 E8 and 13 PE HIGHLOW** original physical site/targets, **909/909 nonrelocation plus 985/985 entire relocated bytes**; [independent PE/COFF proof](ANIMATION_CORNER_PROJECTION_985_VERTEX_DRAW_455_STRICT_EXACT.md). Historical nominal owner remains provisional, original game caller sites verified. |
| 0x0043CB70 Animation colored vertex TRIANGLEFAN Boss | **Whole original 455B/129-x86 strict exact**, real 65,536×20B buffer, count>=3, D3D9 TRIANGLEFAN=6 and count−2 primitives. All **4 E8+3 HIGHLOW** true original roles and entire **455/455 bytes**, [PE evidence](ANIMATION_CORNER_PROJECTION_985_VERTEX_DRAW_455_STRICT_EXACT.md). |
| 0x0043D1A0 Animation colored vertex LINESTRIP Boss | **Whole original 455B/129-x86 strict exact**, original count>=2 and D3D9 LINESTRIP=3, count−1 primitives, **4 E8+3 HIGHLOW** physical roles, **455/455 original native bytes**, [original proof](ANIMATION_CORNER_PROJECTION_985_VERTEX_DRAW_455_STRICT_EXACT.md). |
| 0x0043D830 Animation single-point renderer | **Whole original 375B/100-x86 POINTLIST strict exact**, real fixed 65,536×20B pool and typed vertex[0] access; **5 original E8 +4 HIGHLOW physical site/targets**, full 375/375 native bytes, [source/PE evidence](ANIMATION_SHAPE_FINAL_THREE_375_809_583_STRICT_EXACT.md). Enclosing 5,993B main Draw NONEXACT. |
| 0x0043D9B0 Animation alternating-radius TRIANGLEFAN | **Whole original 809B/214-x86 strict exact**, native center[0] and true signed i%2 radius alternate, D3D9 type6, **8 E8/8 HIGHLOW** and full 809/809 original bytes; [independent PE proof](ANIMATION_SHAPE_FINAL_THREE_375_809_583_STRICT_EXACT.md). |
| 0x0043DCE0 Animation alternating-radius LINESTRIP | **Whole original 583B/160-x86 strict exact**, original signed i%2 perimeter and D3D9 LINESTRIP type3, **6 E8/5 HIGHLOW** and full 583/583 original bytes; [original PE proof](ANIMATION_SHAPE_FINAL_THREE_375_809_583_STRICT_EXACT.md). Main Draw still NONEXACT. |
| 0x0043C4E0 Animation elliptical LINESTRIP Boss | **Whole original 660B/178 native i386 strict exact**, original `0x40` frame/RET0x20, 65,536×20B pool, genuine local Vector3 constructor, one cosine/sine/XY rotation per ellipse perimeter vertex and D3D9 LINESTRIP type3. **12/12 real E8 and 8/8 PE HIGHLOW physical site/targets, 580/580 nonrelocation +660/660 whole native relocated exact**; [independent original PE/COFF proof](ANIMATION_SHAPE_ELLIPTIC_660_863_STRICT_EXACT.md). Enclosing 5,993B main Draw still NONEXACT. |
| 0x0043C180 Animation elliptical TRIANGLEFAN Boss | **Whole original 863B/226 native i386 strict exact**, native `0x40` frame/RET0x20, actual center vertex[0] and perimeter, genuine Vector3 constructor **before** perimeter pointer increment, D3D9 TRIANGLEFAN type6. **12 E8 and 9 original PE HIGHLOW sites/true destinations, 779/779 nonrelocation and 863/863 whole relocated strict exact bytes**; [original source/PE evidence](ANIMATION_SHAPE_ELLIPTIC_660_863_STRICT_EXACT.md). Main Draw parent still NONEXACT. |
| 0x0043DF30 Animation signed-parity alternating-radius TRIANGLESTRIP Boss | **Whole original 899B/236 real i386 strict exact**, native `0x3C` frame/`ret 0x24`, fixed 65,536×20B renderer pool, four genuine radius±thickness/2 local values computed **before** the loop and two signed `i%2` selections per angle, D3D9 TRIANGLESTRIP type5. **All seven original E8 and 10 PE HIGHLOW physical site/targets**, **831/831 nonrelocation and 899/899 strict relocated bytes exact**; [original PE/native proof](ANIMATION_SHAPE_ALTERNATING_899_STRICT_EXACT.md). Original 5,993B main Draw calls at 3 genuine E8 sites, parent still NONEXACT. |
| 0x0043C780 Animation rotated two-radius ellipse TRIANGLESTRIP Boss | **Whole original 1,001B/258 x86 strict exact**, native `0x58` frame/RET0x24, real Vector3 ctor plus 2 cosine/2 sine/2 XY rotate calls and native two-radius 20B vertex ring, D3D9 TRIANGLESTRIP type5. **15 genuine E8 +13 PE HIGHLOW source/physical destinations and 889/889 nonrelocation /1,001/1,001 whole strict relocated bytes**; [original native PE/COFF proof](ANIMATION_SHAPE_ROTATEDRING_1001_TWOPOINT_1116_STRICT_EXACT.md). The original 5,993B main Draw dispatcher has 3 E8 callers but is still NONEXACT. |
| 0x0043CD40 Animation two-point LINESTRIP Boss | **Whole original 1,116B/282 x86 strict exact**, original `0x3C` frame/RET0x20, two real XY transform helper calls, X[2]/Y[2] anchor state, and **five genuine reciprocal-W=1 writes** despite only two submitted vertices. **10 E8 +13 HIGHLOW real site/targets, 1,024/1,024 nonreloc and full 1,116/1,116 strict bytes exact**, [independently immutable native proof](ANIMATION_SHAPE_ROTATEDRING_1001_TWOPOINT_1116_STRICT_EXACT.md). Actual main Draw still NONEXACT. |
| 0x0043BC60 Animation simple circular LINESTRIP Boss | **Whole original 541B/147-i386 strict exact**, frame0x24/RET0x18, true one-perimeter-vertex 20B buffer and input angle overwritten by original `2*pi/count` step; D3D9 **LINESTRIP type3**, no fabricated Graphics depth state. **6 E8 +5 HIGHLOW original physical field/targets, 497/497 nonreloc and complete 541/541 native strict bytes**; [PE/COFF whole proof](ANIMATION_SHAPE_POLAR_LINES_541_766_STRICT_EXACT.md). Original parent 5,993B Draw remains NONEXACT. |
| 0x0043BE80 Animation dual-radius polar TRIANGLESTRIP Boss | **Whole original 766B/201-i386 strict exact**, frame0x2C/RET0x20, actual two polar2 calls and two real radius±thickness/2 inputs per angle, original inner/outer color, D3D9 **TRIANGLESTRIP type5** with 2*count segments and 20B stride. **7 E8 +8 HIGHLOW original physical role/target pairs, 706/706 nonreloc and whole 766/766 strict relocated bytes**, [independent original PE/native proof](ANIMATION_SHAPE_POLAR_LINES_541_766_STRICT_EXACT.md); 5,993B enclosing dispatcher still NONEXACT. |
| 0x0043A750 Animation rounded rectangle LINESTRIP Boss | **Whole original 971B/255 real i386 strict exact**, native `0x28` frame/`ret 0x20`, no center vertex, original 65,536 ×20B vertex pool, polar/rotation signed-quarter perimeter, **D3D9 LINESTRIP primitive type3**. **9/9 original E8 physical site/destinations, 18/18 PE HIGHLOW physical fields, 863/863 nonrelocation and complete 971/971 strict relocated bytes exact**; [source and immutable PE proof](ANIMATION_SHAPE_ROUNDEDLINE_971_STRICT_EXACT.md). Parent 5,993B Draw still NONEXACT. |
| 0x0043B960 Animation simple center/perimeter TRIANGLEFAN Boss | **Whole original 755B/197 real i386 strict exact**, native `0x24` frame/`ret 0x1C`, real center `[0]` record and input angular parameter reused for `2*pi/count`, D3D9 TRIANGLEFAN type6. **8/8 original E8 site/targets, 8/8 native PE HIGHLOW site/targets, 691/691 nonrelocation bytes, whole 755/755 relocated exact**; [original PE/COFF proof](ANIMATION_SHAPE_SIMPLEFAN_755_STRICT_EXACT.md). Original 5,993B main Draw remains NONEXACT. |
| 0x0043A2B0 Animation center+rounded triangle FAN Boss | **Entire original 1,174B/303 native i386 strict exact**, true original `0x28` frame/RET0x24, real center `[0]` vertex and 65,536×20B pool, signed-quarter polar/rotation outer ring and original D3D9 TRIANGLEFAN type6. **9 genuine original E8 and 19 PE HIGHLOW offset/target pairs, 1,062/1,062 nonrelocation and 1,174/1,174 complete native relocated bytes**; [whole original PE/native/COFF proof](ANIMATION_SHAPE_ROUNDEDFAN_1174_STRICT_EXACT.md). Original 5,993B main Draw still NONEXACT. |
| 0x0043A1C0 Animation two-pass outline rectangle leaf | **Whole 240B/76-i386 original game leaf strict exact**, native RGB preservation and α/2 color shift in genuine `SHR24,SHR1,SHL24` order, 1.0f width/height margin and two authentic E8 to the already exact 1,980B rectangle. 2 E8 and 2 HIGHLOW independently attested, **240/240 whole bytes**; [original/native strict proof](ANIMATION_SHAPE_OUTLINE_240_STRICT_EXACT.md). |
| 0x0043E2C0 Animation three-vertex triangle Boss | **Whole original 1,601B/394 native i386 strict exact**, real `0x50` frame/RET0x24, original 65,536×20B vertex-pool 3-vertex guard, true 3-float X/Y anchor arrays and source-owned ±width/3, 2width/3, height/2; **11 original E8 and 19 PE HIGHLOW physical roles exact**, D3D9 TRIANGLESTRIP type5 primitive count1. **1,481/1,481 nonreloc and 1,601/1,601 strict relocated bytes**, [independent PE/COFF whole proof](ANIMATION_SHAPE_TRIANGLE_1601_STRICT_EXACT.md). Enclosing original 5,993B main Draw remains NONEXACT; shared int-return ABI corrected and old affected sources scoped replayed. |
| 0x0043B0E0 Animation closed five-vertex LINESTRIP Boss | **Whole original 2,169B/533 native x86 strict exact**, `0x68` frame/RET0x24, authentic 65,536×20B buffer and five typed vertices closing first XY/Z, original 2x4 anchored coordinates and native **D3D9 LINESTRIP type3, four primitives** (not TRIANGLEFAN type6). **12/12 original E8 and 17/17 physical HIGHLOW site/targets, 2,053/2,053 nonrelocation and 2,169/2,169 whole strict bytes**; [complete independent PE/native proof](ANIMATION_SHAPE_LINESTRIP_2169_STRICT_EXACT.md). Main 5,993B parent remains NONEXACT; previously exact affected header consumers scoped replayed. |
| 0x00439A00 Animation 4-vertex rectangle Boss | **Whole original 1,980B/486 i386 strict exact**, genuine `0x68` frame/RET0x24, real two four-float X/Y coordinate arrays and six 3-mode anchor states, meaningful original signed/half-scalar temporaries, 65,536×20B vertex-buffer unsigned guard. Original **12/12 E8 and 16/16 PE HIGHLOW** site/targets (including native 128-bit float sign mask), **1,868/1,868 nonrelocation and 1,980/1,980 whole strict relocated bytes**; [full immutable PE/COFF evidence](ANIMATION_SHAPE_RECT_1980_STRICT_EXACT.md). Original main 5,993B caller twice; parent stays NONEXACT, 11 existing affected exact units independently scoped replayed. |
| 0x00445AD0 game shape XY transform leaf | **78B/20 native-i386 cdecl whole strict exact**, genuine seven-argument SSE x*cos−y*sin+tx, x*sin+y*cos+ty and real Vector2 field stores. Zero original native PE HIGHLOW/E8 fields; 11 independently original E8 *callers* from source-absent 1,980B/2,169B/1,601B shape Boss parents, [independent entire PE/COFF proof](ANIMATION_SHAPE_XY78_STRICT_EXACT.md). 78/78 native bytes pinned strict, no duplicate code-parent credit. |
| 0x0043AB20 Animation polygon shape-ring Boss | **Whole original 1,468B/387-i386 game-authored native strict exact**, true `0x2C` frame and EAX-zero `ret 0x28`, 65,536 ×20B original typed vertex pool and genuine one-cursor inner/outer ring generation, pi/-pi angle progression, original 20B triangle strip and D3D state. **11/11 E8 and 26/26 PE HIGHLOW physical site/targets, 1,320/1,320 non-relocation bytes, 1,468/1,468 complete strict relocated bytes**; [source, immutable PE and whole canonical proof](ANIMATION_SHAPE_RING_1468_STRICT_EXACT.md). Corrected shared renderer method's integer return ABI; 10 existing affected strict units replayed and remain exact; main 5,993B Draw dispatcher still NONEXACT. |
| 0x00445350 Animation Strip Mode9 612B renderer | **Whole native 612B/182 x86 strict exact**, `0x40` frame/ret0xC, original Animation byte/flag guards, real 28B vertex stride, authentic D3D9 FVF/texture/cache and native 2-bit color mode. **11 original E8 physical sites and 5 PE HIGHLOW field targets all exact**, **612/612B** whole original strict pinned native relocation replay. [Independent original/strict source proof](ANIMATION_DRAW_STRIP_MODE9_612_STRICT_EXACT.md). Enclosing 5,993B main Draw dispatcher remains separate NONEXACT. |
| 0x00445130 Animation Strip Mode11 534B renderer | **Whole 534B /159-i386 original game method strict exact**, native 0x3C frame, ret0xC, true 28B vertex stride, bit21 one-shot translated vertices, original FVF/texture and depth-write state, **10/10 genuine E8 and 6/6 PE HIGHLOW physical sites/targets exact**, complete **534/534B** canonical original byte replay; [independent original PE proof](ANIMATION_DRAW_STRIP_MODE11_534_STRICT_EXACT.md). Enclosing 5,993B main Draw dispatcher still NONEXACT. |
| 0x00441F00 Animation Mode8 6-rotation-order Draw Boss | **Whole original 4,347B /1,063 x86 game-authored strict exact**, native `0x1BC` stack and RET4, six original X/Y/Z D3DX rotation-order cases with exactly **101 genuine E8 calls and 39 native body HIGHLOW fields plus 6 after-RET code pointers**. Real 1B NOP and six unique case labels, **4,372/4,372 original full relocated COFF/native bytes strict exact**. [Independent original/whole canonical proof](ANIMATION_DRAW_MODE8_4347_STRICT_EXACT.md). Enclosing 5,993B Draw dispatcher remains NONEXACT. |
| 0x00441C00 Animation draw mode7 fog/projection Boss | **753B /178 x86 whole-native strict exact**, 7 actual E8 calls +29 in-body HIGHLOW original sites, true D3DX four-corner transform, native 25B depth/math and exact 3,159B quad-submit; [complete original/COFF proof](ANIMATION_DRAW_MODE7_753_STRICT_EXACT.md). Main 5,993B parent stays NONEXACT. |
| 0x00445700 /0x00445720 Animation vector depth /squared-depth | **25B+70B =95B original game-authored strict exact**, real x87/SSE Vector3 math; native mode6/7 original callers and two genuine E8 targets independently PE-attested. [Full original/canonical proof](ANIMATION_DEPTH_MATH_25_70_STRICT_EXACT.md). The 753B mode7 caller and its 1,996B setup callee are now independently strict exact. |
| 0x00437930 /0x004379A0 /0x004379C0 Animation gameplay value getters | **3 ×17B =51B original game-authored strict exact**; original full nine-instruction thiscall FLD and 12 native E8 game-caller sites; previously strict but origin unreviewed, [independent authorship proof](ANIMATION_VALUE_GETTERS_51_AUTHORED_ORIGIN.md) |
| Other completed original methods | [Geometry](GEOMETRY_ORIGIN_13360_EXACT_RECONSTRUCTION.md), [Interpolation](INTERPOLATION_BOSSES_8571_EXACT_ORIGIN_AUDIT.md), [game owner constructors](GAME_OWNER_CONSTRUCTION_6057_EXACT_ORIGIN_AUDIT.md), [Laser lifetimes](LASER_PARAMETERS_936_ORIGINAL_GAME_EXACT_ORIGIN.md), [ECL argument/ScriptStack](ECL_ARGUMENT_TAGGED_STACK_2073_ORIGINAL_GAME_EXACT_ORIGIN.md); historical group sums are not additional current byte credit. |

The [complete 3,159B quad submission Boss](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md)
is still whole strict exact. Its genuine `0x00445B80` callee has now been
independently identified as the C++ `round(float)` standard-header overload:
[20B/9-x86 library exact](ANIMATION_STD_ROUND_FLOAT_20_LIBRARY_EXACT.md),
forwarding to native `_roundf` at `0x00550060`. The pinned shared
`/fp:strict` compilation naturally emits both from
`src/AnimationQuadSubmit.cpp`: **3,180/3,180B parent +20/20B library**, one
canonical source object and **two scoped units**. The 20B library wrapper
is excluded from **590 original authored game functions /196,671B**; it
adds a source-present mapping and strict unit, not game byte credit.

**11,110B ECL runtime and 41,967B Enemy ECL opcode dispatcher are
different functions.** The 3,735B Bullet emitter is already whole exact,
although the 12,140B Bullet command parent which it calls remains NONEXACT.

## Unfinished large original functions — active source and next evidence

**All sizes and instruction counts below refer to the locked original unless
explicitly marked as candidate output.** The status is per *parent function*;
strict-exact children cannot be counted as matched parent bytes. Historical
compiler sizes, source-absence labels and batch totals in linked dated reports
are not current. Verify each claim against the original PE and live ledgers.

| Priority / original head | Current parent state and immediate next work |
| --- | --- |
| **1. Bullet extended-command Boss `0x0047DCF0` — 12,140B /2,490 x86** | **SOURCE-ABSENT, NONEXACT.** Original 210 E8 occurrences: **208** have whole-native-exact game-callee source; remaining **two are compiler runtime** (`__security_check_cookie`, `__allshl`), not game-function gaps. Original 34+8+11 switch pointers (53 PE HIGHLOW) and 38 body HIGHLOW. Next: author the **complete 34/8/11-switch command parent**, verify each native case and its source, then match full x86/relocations. [Immutable original CFG](BULLET_12140_THREE_SWITCH_NATIVE_CFG_RECONSTRUCTION.md), [current native 210-call verifier](../scripts/verify-bullet-command-call-coverage.py), [exact recursive Animation children](ANIMATION_RETIRE_SUBTREE_362_EXACT_RECONSTRUCTION.md). |
| **2. Animation 49-mode draw Boss `0x00443880` — 5,993B /1,501 x86** | **SOURCE-PRESENT, NONEXACT**, `src/AnimationDrawBoss.cpp`. The current pinned C++ source naturally emits **exactly 5,993B/1,501 x86** with original **`0x204` stack frame**, identical **3B after-body alignment**, and original **49+31 direct pointer table positions** (6,316B total COFF). **All 123 native E8 target roles in exact original order**; first 81 sites consecutive, **86/123 physical E8 site-and-target pairs exact**, **32/32 original PE in-body HIGHLOW target counts with 23/32 physical site+target matches**. Provisional 3,819/5,376 nonrelocation byte match is **NOT full exact**. Original mode35/36, 29/30 and 46 color/count/half-height/aux-scale observable evaluation order restored through meaningful used locals; private inert x87 spill experiment rejected. Native **first mode35 inherited-scale return spill** and late nested SSE/relocation operands remain different. Next: establish actual x87 result ownership, align remaining nine PE HIGHLOW sites and 37 E8 offsets, then canonical zero-difference acceptance only. [Current native-length/stack frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md); [exact 753B mode7 child](ANIMATION_DRAW_MODE7_753_STRICT_EXACT.md); [strict 1,996B mode7 setup child](ANIMATION_DRAW_MODE7_SETUP_1996_STRICT_EXACT.md), [complete 49+31 table and 18-backend ABI proof](ANIMATION_DRAW_BOSS_5993_NATIVE_80_TABLE_ABI_FRONTIER.md), [focused original PE/source verifier](../scripts/verify-animation-draw-boss-source-roles.py). One isolated NONEXACT object only, zero exact-provider replay; no game exact credit. |
| **3. Player main `0x004F9C30` — 3,111B /783 x86** | **SOURCE-PRESENT, NONEXACT.** Source candidate **3,114B /783 x86**, 67 actual call roles and 37 frame-data references; differences persist in register/stack/branch encoding despite matching mnemonic count. Next: expression and receiver lifetime. [Full operand evidence](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md), [independent 72B input data table](PLAYER_DIRECTION_TABLE_72_EXACT_RDATA_AND_37_ROLES.md). |
| **4. Player movement `0x004FFA10` — 555B** | **SOURCE-PRESENT, NONEXACT.** Candidate **561B /136 x86** vs original **555B /135**; one excess 6B SSE lifetime spill remains. [Native movement source evidence](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md). |
| **5. Bullet group drawing `0x0047DB70` — 273B** | **SOURCE-PRESENT, NONEXACT.** Candidate approximately **283B /84 x86** vs original **273B /82**, extra SSE expression spill. [Full source frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md). |
| **6. Enemy ECL opcode dispatcher `0x0048C010` — 41,967B /8,896 x86** | **SOURCE-ABSENT, NONEXACT.** Original opcode base 300, 704B compressed mode index, 174 actual PE HIGHLOW case pointers. Next: complete parent opcode source/CFG; separate exact Laser children do not close it. [Original native opcode graph](ENEMY_41967_NATIVE_LASER_OPCODE_CASE_GRAPH.md). |
| **7. Animation VM update `0x0042B5D0` — 39,470B** | **SOURCE-ABSENT, NONEXACT.** Native child script parsers and Animation helpers are exact, but whole interpreter source and codegen are not. [Source ownership](SOURCE_MAP.md). |
| **8. Enemy mesh `0x004A4190` — 1,649B** | **SOURCE-PRESENT, NONEXACT.** Coherent C++ exists, but original temporary/retirement lifetime codegen differs. [Native mesh frontier](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md). |
| **9. STL counted-range `0x0047A8D0` — 470B** | **LIBRARY, NONEXACT (not authored game credit).** Real original **470B /174 x86 /12 E8** vs modern C++17 **458B /170 x86 /11 E8**; real missing `std::is_constant_evaluated` call is a toolchain/STL issue. Do not fabricate a game call. [Library proof](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md). |

The **3,159B quad submission parent is now entire whole-native strict exact**,
not merely source-present with exact children. Its natural 20B `std::round(float)`
callee is independently strict exact but library-excluded. The 5,993B Animation draw
parent calling it remains separate and NONEXACT. See the
[complete renderer parent proof](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md).

Completed Bullet library support includes **610B PMR vector functions**
([proof](BULLET_COMMAND_PMR_CXX17_469_LIBRARY_EXACT.md)) and **100B
shared_ptr moves** ([proof](BULLET_SHARED_PTR_LEGACY_CTOR_100_LIBRARY_EXACT.md)),
correctly **excluded from authored game credit**. Seven game-authored
Bullet interpolation tangent/mode/reset methods add **199B strict**
([original whole-native and 114-object closure](BULLET_199_INTERPOLATION_TANGENT_TIMER_EXACT.md)).
Exact children never imply exact big parents.

## Native acceptance, scope and proof discipline

- Read [AGENTS.md](../AGENTS.md), [workflow](RE_WORKFLOW.md), [build
  matching](BUILD_MATCHING.md), [source map](SOURCE_MAP.md) and [evidence
  index](EVIDENCE_INDEX.md). Native original PE bytes / real E8 / .reloc
  HIGHLOW are the source of truth, not old Ghidra names or prose.
- Use natural shared C++ source, genuine type layout and real original
  compiler calling convention. No assembly, no padding, no deliberately
  inert register temporaries, no fake ABI wrappers, no binary/COFF patches.
- Strict whole native acceptance needs entire original byte extent,
  independently PE-attested relocated targets, real pinned i386 MSVC
  source and **zero-difference canonical replay**. Structural-exact
  diagnostics or aligned mnemonic counts alone are not acceptance.
- Inspect all dirty, staged and untracked files: **they are our work**.
  Preserve useful private hypotheses, repair actual compiler fallout,
  commit checkpoints with prefix **gpt-web:**.

### Targeted validation only — do NOT run whole-graph cold replay

For native source/header/manifest/profile changes, calculate the actual
affected provider closure **before** editing, then build/replay only its
sources/units at low priority. Example:

    git status --short --branch -uall
    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/validate-tracking.py --require-target
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/Interpolation.cpp
    scripts/repo-python scripts/compare-coff-function.py --unit UNIT_NAME
    scripts/repo-python scripts/build.py --check
    scripts/repo-python scripts/progress.py --check

A previous real interpolation header edit affected **114 objects /542 old
whole strict units**, all separately replayed with 25 original-PE-proven
private compiler string symbol renames; that was a **historical change
closure**, not a reason to replay it again on an unchanged graph.

The latest `src/AnimationQuadSubmit.cpp` changes affect only its **one
canonical provider/two exact units** under `/fp:strict`: the original 3,159B
quad parent and 20B C++ library `round(float)` wrapper. No other canonical
source, header, profile or original target changed; no unfiltered replay.

For **documentation and ignored-cache cleanup only**, there are **zero
native compiler-input changes and zero cold replay units**. Check target
hash, protected original/canonical file hashes, Markdown links, the
actual live ledger, edited tooling's focused tests and git diff --check.

## Protected source, data and storage

Keep original resources/th20.exe, private provenance, _reference/, attested
ghidra-project/, installed MSVC/Wine/D3DX in .tools/, .venv/, source,
Git history, original PE native research and unique .analysis/*.json.gz
frozen snapshots. Do **not** delete build/ or .analysis/ as a whole.
All **260 protected canonical .obj plus 260 matching receipt files** are
taken from the **live** match-units.toml, not hardcoded old 243/236/212
counts.

For reproducible **noncanonical generated probes only**, run the guarded
dry-run-first cleanup tool and inspect its protected scope:

    scripts/repo-python scripts/prune-generated-artifacts.py
    # After auditing its actual candidate set:
    scripts/repo-python scripts/prune-generated-artifacts.py --apply --inventory .analysis/NEW-UNIQUE-AUDIT.json

The tool must retain all manifest objects, original native evidence,
active Player/Bullet/Mesh probes, file-specific documented evidence and
original PE hashes. See the [latest protected retirement audit](MAINTENANCE_STORAGE_2026_10_30.md),
[historical October 29 audit](MAINTENANCE_STORAGE_2026_10_29.md) and
[prior retirement guards](ARTIFACT_RETIREMENT_CORE628.md).
No cleanup demands MSVC/Ghidra or full replay. Do not push unless requested.
