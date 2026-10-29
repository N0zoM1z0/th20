# CORE/ORIGIN-726 — nine complete original TH20 game methods, 1,686 distinct native exact bytes

**Nine previously canonical strict-native whole original methods are independently confirmed game-owned**, totaling **1,686 disjoint original game code bytes**. This is an actual original PE interval/call/relocation provenance admission, not a new claim that any surrounding unresolved game Boss is playable or strictly byte-exact.

Original Japanese TH20 v1.00a Steamless executable SHA-256: a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Original whole game methods

| Genuine original game function | Original code head | Whole original bytes | Previously accepted strict native unit |
| --- | --- | ---: | --- |
| Pbg::convert_filename — CP932 and relative game-file path | 0x00538E10 | 248 | pbg_file_convert_filename: 248/248 |
| DamageRegion::player_shot — real Player object lookup | 0x004C0F70 | 55 | region_player_shot: 55/55 |
| Player::find_shot — Player+0x22B4 shot-controller member | 0x004C0FB0 | 38 | player_find_shot: 38/38 |
| PlayerShotController::find — actual intrusive shot identifier search | 0x00506360 | 246 | player_shot_find: 246/246 |
| normalize_to_length — gameplay Vector3 scaling | 0x004532C0 | 229 | normalize_to_length: 229/229 |
| FogValue::operator- — native six-field fog subtraction | 0x00471E60 | 226 | fog_subtract: 226/226 |
| FogValue::operator+ — native six-field fog addition | 0x00471F50 | 226 | fog_add: 226/226 |
| Session::Session — actual game global session constructor | 0x00422E40 | 214 | session_ctor: 214/214 native coverage, 219/219 compared |
| GraphicsFlags::GraphicsFlags — game rendering mode defaults | 0x004D88C0 | 204 | graphics_flags_ctor: 204/204 |
| **Newly confirmed game-authored original bodies** | **Nine disjoint original heads** | **1,686** | **9/9 whole-original strict** |

The complete original native x86 methods were freshly disassembled through their returns. The nine bodies have **31 original direct E8 fields and ten physical PE IMAGE_REL_BASED_HIGHLOW fields**. Their original immediate destinations, independently extracted PE relocation sites, kinds and full values were compared with previously configured strict COFF relocation anchors. Every newly admitted interval is mutually disjoint and does not overlap any of the earlier **537 credited complete original game methods**.

## True complete game call graph evidence

**The Player-shot query is a three-stage original game protocol, not isolated numeric wrappers.** Two genuine original complete but NONEXACT 131B and 126B collision methods at 0x004BFCD0/0x004BFD60 call the full 55B DamageRegion::player_shot at original 0x004BFCE3/0x004BFD73. The real region method calls Player::find_shot at **0x004C0F9E → 0x004C0FB0**. That complete 38B method reads the actual Player+0x22B4 controller and calls PlayerShotController::find at **0x004C0FCB → 0x00506360**. All **55+38+246 = 339** game bytes are independently strict exact and newly credited once. Neither 131B/126B upstream parent receives any exact byte credit.

**Pbg::convert_filename, 248B** is called from the separately exact whole **346B Pbg::File::open** at original **0x00538D2E → 0x00538E10**. The game/Pbg routine does CP932 MultiByteToWideChar conversion, drive-colon absolute-path testing, executable-relative path retrieval and safe wide-string concatenation. It is not a generic CRT wcscat or wide-character helper; the original 346B opening body was previously credited and is not duplicated.

**Gameplay Vector3 normalize_to_length, 229B** has original E8 callers in separately exact **313B regular-polygon collision geometry** at 0x00456731 and **324B star-polygon geometry** at 0x00456871. Both are genuinely game-authored geometry, with near-zero-length and desired-radius Vector3 source semantics. These caller bytes are unchanged.

**FogValue subtraction/addition, 226B each** are consumed by a separately complete strict **1,074B Fog interpolation Boss**: subtract at **0x00473960**; add at **0x004736C9, 0x0047371F, 0x0047374A, 0x004738B0, 0x004738EC, 0x00473928, 0x00473993**. They operate on the real game fog near/far/color fields, not anonymous STL vectors. The original 1,074B interpolation body remains previously accepted, not added again.

**Session constructor, 214B** is invoked by the original module's actual **16B Session static initializer** through E8 **0x00401188 → 0x00422E40**. The wrapper is itself whole-native strict but **compiler-generated startup support and expressly NOT newly credited as game-authored**, while the called 214B custom game Session state initializer is original authored object behavior.

**GraphicsFlags constructor, 204B** is invoked by the independently complete strict **941B Graphics::Graphics** at **0x004D8C3A → 0x004D88C0**, initializing the real game rendering bit flags, including bit7 and bit11 default values. The parent original 941B is not counted again.

## Actual bounded MSVC cold replay, including dirty receipt handling

All **six original source providers** for the nine functions were independently cold rebuilt and replayed under their pinned MSVC profiles:

| Actual relevant provider | Whole strict native units |
| --- | ---: |
| src/PbgFile.cpp | 12/12 |
| src/DamageQueryProtocol.cpp | 14/14 |
| src/MotionMath.cpp | 11/11 |
| src/FogValue.cpp | 6/6 |
| src/Session.cpp | 25/25 |
| src/Graphics.cpp | 5/5 |
| **Six real source providers** | **73/73** |

The initial original game-owner caller checks exposed **two existing stale canonical receipts**. They were not ignored: only src/Interpolation.cpp (**41/41 native strict**) and src/CollisionShapes.cpp (**7/7 strict**) were cold rebuilt and rechecked. **All eight actual bounded native source objects /121/121 original strict whole units passed.** The 1,074B Fog, 313B/324B geometry, 941B Graphics, 346B file-open and authentic 16B static Session wrapper were independently compared strict after the affected-only rebuilds. No entire-game cold replay was run.

Private reproducible evidence: .analysis/core726-game-nine-medium-native-provenance.py/json. It reads the immutable PE hash and whole original function returns, all 31 E8, ten genuine original PE HIGHLOW, all genuine parent original call sites (including both nonexact collision callers), existing strict original whole receipts and disjointness from the **537 previous game intervals**. The 16B compiler startup thunk is evidence only, not game body credit.

**This is an origin/credit-only tracking change, not a source C++ or original target modification.** No shared header, canonical compiler unit, existing strict original method or native relocation anchor changed. **537 previously game-authored complete original strict functions /184,665 bytes → 546 /186,351 bytes**, adding exactly **nine whole original game functions and 1,686 disjoint original bytes**. The 3,111B Player main, 555B Player movement and 12,140B/41,967B dispatch Bosses remain separate NONEXACT challenges.
