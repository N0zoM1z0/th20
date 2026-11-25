# 5,993B Animation Draw Boss: mode35/36 spill, width-order and local-reuse experiments

**Status: focused source/compiler investigation; no production-source promotion.**
The maintained `src/AnimationDrawBoss.cpp` remains the reference candidate.
All probes below are ordinary C++ compiled as isolated i386 COFF with the
repository's pinned MSVC 19.44.35211 profile (`/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`). No canonical object, target byte, match
manifest or source file is changed by these experiments.

## Baseline and width-before-half tradeoff

The maintained parent is 5,993 code bytes /1,502 decoded i386 instructions,
with **4,840/5,376** comparable ordinary bytes, **114/123** original physical
E8 positions, and **27/32** exact body HIGHLOW site/target pairs. A natural
mode35 source reorder was recompiled and re-ranked:

```cpp
const float shape_width = width + (height / native_two);
const float aux_half = height / native_two;
const float adjusted_scale =
    animation_inherited_aux_scale_x(animation) + aux_half;
```

This retains the full 5,993B contribution, 1,502 instruction heads, 123 E8
roles and the 27/32 data-site count. Its comparable ordinary-byte score rises
to **4,844/5,376** and the E8 position count remains **114/123**. However, the
second mode35 getter call moves from native `+0x1016` to `+0x102C`; the mode35
renderer call and following mode36 entry sites move by +8/+4 bytes, while the
mode36 final renderer call is four bytes early. The total absolute E8 offset
error rises from **44** to **62**. The four-byte raw score improvement is
therefore not a better reconstruction frontier and is not promoted.

A 16-way battery moved the same real width calculation before/after the first
getter, colors, count, half-height, second getter and adjusted-scale local,
with both named and inline adjusted-scale forms. All 4,844-byte variants share
the same worse call-site displacement pattern; the variants retaining the
native getter position return to 4,840/5,376. No placement improves the
maintained source's combined byte/call-site evidence.

## Function-scope first-return local

The original native x86 body writes the first mode35 and mode36 getter returns
to `[ebp-0x160]` at `+0x0FCD` and `+0x10BA`; a complete decoded-body operand
scan finds no subsequent read of that slot. A natural function-scope
`[[maybe_unused]] float first_inherited_scale`, assigned by each first getter,
reproduces both x87 memory stores. When combined with value-equivalent
half-height role reuse, it also recovers both adjusted-scale register-register
forms (`addss xmm0,xmm1` and `subss xmm0,xmm1`).

The best such scalar probe is **5,989B**, **3,801/5,372** ordinary bytes and
**89/123** E8 positions. Its first 88 E8 positions match, but every physical
E8 from the mode36 renderer call at native `+0x1198` onward is four bytes
early. The probe reuses the pre-getter half-height local for the width
argument; native mode36 recomputes `height / 2` after adjusted-scale. Replacing
the reused value with a post-getter width calculation removes the register
operand form when the adjusted-scale calculation consumes the saved half.
The source battery also tried keeping all current locals while adding the
first-return local, declaring it after position setup and after scale setup,
and reusing the width temporary. These either shift later locals/calls,
materialize extra stack loads, or lose the original function extent/call
census. No first-return probe is promoted.

## Other rejected source forms and compiler profiles

- The exact native mode45 half-height ownership (scale half before the getter,
  width half recomputed after it) compiled to **5,989B /109/123 E8** and
  **4,694/5,372** ordinary bytes. Its adjusted-scale addition remains a
  memory-source `addss`, not the native register-register form.
- The same mode45 native-order form was tried with const/mutable/assigned
  locals, reverse addition, comma expression, case-top predeclarations and
  inline width recomputation. None restored the current source's call-site
  census or ordinary-byte score.
- `__forceinline` scalar add/subtract wrappers under `/Ob0` were not inlined;
  they changed the call graph and contribution extent and are rejected.
- `/Od /Ob1`, `/Od /Ob2`, `/Od /Oi`, `/Od /Ob1 /Oi` and `/Od /Oy-` produced
  the same maintained 4,840/5,376, 114/123 candidate. `/O1`, `/O2` and `/Ox`
  changed the whole function's contribution substantially and did not retain
  the native E8 graph.
- A `shape_width` local initialized from the first getter and then reused for
  the width argument made the compiler read `[ebp-0x160]`, unlike the native
  write-only spill, and lost the parent call census. This is not the native
  lifetime.

The next useful avenue remains a natural C++ local/temporary lifetime that
simultaneously accounts for the write-only first-result spill, keeps the
pre-getter half alive in XMM1 across the recursive getter, recomputes width's
half at the original post-getter point, and preserves the 5,993B/123-E8/32-
HIGHLOW parent. The maintained source is unchanged; parent exact credit
remains zero.
