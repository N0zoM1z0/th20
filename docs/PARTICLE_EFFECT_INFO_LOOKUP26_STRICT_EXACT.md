# CORE/RECON-1106 — original session-indexed EffectInfo accessor, whole 26B exact

The immutable Japanese TH20 Steamless v1.00a executable (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains a complete game-owned resource-owner lookup at `0x00437520`,
**26 bytes /10 i386 instructions**, whole-body SHA-256
`253810baeef904d356fb22c20e14a5c17e055a53c9e7177ffe18ebb20530a915`.
The genuine `ret` terminates at `0x0043753A` with no more code in this body.
Its callers include the original 2,884B particle-grid Update at
`0x0045C360`, which calls this selector four times during particle emission.

The natural maintained source is
[`src/ParticleEffectInfoLookup26.cpp`](../src/ParticleEffectInfoLookup26.cpp):

```cpp
EffectInfo* particle_effect_info_for_session_437520(std::int32_t index) {
    return session.context(index).effect_info();
}
```

`Session::context(index)` returns an indexed 0x30-byte `Context` from the
real 0x2C0-byte game Session at `0x005BA568`. The subsequent
`Context::effect_info()` returns the actual owned `EffectInfo*` at context
`+0x20`. Both callees are existing independently matched/source-tracked
original functions; this checkpoint does not recredit them.

The complete original PE has exactly **two E8** calls and **one PE HIGHLOW**:

| Physical native field offset | Relocation type | Independently decoded original destination |
| --- | --- | --- |
| `+0x08` | HIGHLOW/DIR32 | `0x005BA568` — game Session global |
| `+0x0D` | E8/REL32 | `0x0040BBC0` — `Session::context` |
| `+0x14` | E8/REL32 | `0x0041CAD0` — `Context::effect_info` |

The original-only body, independently decoded calls and physical PE
relocations were checked before recording the canonical destination
addresses. Locked MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` emits **26B**, with **14/14
nonrelocation bytes identical** and all three correct COFF relocations.
Whole, independent-replay strict comparison passes **26/26 bytes**, so
this adds one distinct game-authored head and 26 original `.text` bytes.
No target instruction, shortened extent or compiler-shaping local was used.

The prior 2,884B particle Update research source incorrectly represented
the next original call `0x0045D100` as an unused free palette lookup,
rather than the real `EffectInfo::animation_file(index)` method. The
correct resource chain is `Session -> Context -> EffectInfo -> AnimationFile
-> spawn`. Reconstructing that larger call protocol is separate from the
independently exact 26B selector and must not grant credit to the still
nonexact 2,884B parent.

Only this new owner was cold built and replayed:

```sh
nice -n 15 scripts/repo-python scripts/build.py --unit particle_effect_info_lookup_26
scripts/repo-python scripts/compare-coff-function.py --unit particle_effect_info_lookup_26
```
