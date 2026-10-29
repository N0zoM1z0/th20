# CORE/ORIGIN-708 — twelve complete original game ECL argument and ScriptStack functions, 2,073 native bytes

**Twelve previously strict-exact complete TH20 original functions are independently confirmed game-authored**, totaling **2,073 disjoint original native bytes**. This evidence records genuine original ECL runtime parameter handling and tagged stack ownership. It does not count earlier source matches twice or claim newly exact giant interpreter code.

Target: Japanese TH20 v1.00a Steamless original resources/th20.exe, SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Full original game methods

| Original whole game method | Physical native head | Complete bytes | Existing canonical unit |
| --- | --- | ---: | --- |
| EclRuntime::current | 0x005403D0 | 80 | ecl_runtime_current |
| EclRuntime::integer_argument | 0x0053ED50 | 209 | ecl_integer_argument |
| EclRuntime::consuming_integer | 0x0053EEE0 | 197 | ecl_consuming_integer |
| EclRuntime::integer_argument_value | 0x0053EE30 | 163 | ecl_integer_argument_value |
| EclRuntime::float_argument_value | 0x0053EA90 | 212 | ecl_float_argument_value |
| EclRuntime::consuming_integer_value | 0x0053EFB0 | 158 | ecl_consuming_integer_value |
| EclRuntime::consuming_float_value | 0x0053EC80 | 196 | ecl_consuming_float_value |
| EclRuntime::integer_destination | 0x0053E850 | 136 | ecl_integer_destination |
| EclRuntime::float_destination | 0x0053E720 | 148 | ecl_float_destination |
| EclRuntime::float_destination_at | 0x0053E7C0 | 140 | ecl_float_destination_at |
| ScriptStack::pop | 0x0053F0B0 | 242 | script_stack_pop |
| ScriptStack::peek | 0x00540450 | 192 | script_stack_peek |
| **New confirmed authored exact originals** | **12 distinct heads** | **2,073B** | **12/12 whole strict** |

The complete twelve original native body intervals were freshly disassembled through their actual returns. Within these bodies, **31 original direct E8 fields and nine physical original PE HIGHLOW fields** were independently decoded. The HIGHLOW fields are read from the immutable original executable relocation directory, and actual original target addresses/offsets/kinds agree with the previously accepted canonical COFF anchors. No new original method overlaps any of the prior 508 credited game intervals or the other eleven newly credited functions.

## Actual authored ECL runtime and stack semantics

The real ECL instruction header contains a 16-bit reference mask. The separate integer and float read functions decode four-byte immediate arguments, frame-relative local stack words, tagged negative parameters and original manager-level variable slots. Read variants preserve stack state; consuming variants pop four-byte values and convert tagged integer or float values. Explicit destination variants select genuine writable integer/float storage. The explicit-frame float destination uses its passed instruction and base, not an invented global context. Float return and conversion use original x87 ABI, including the observed negative-parameter 8.0f conversion and signed truncation behavior.

The distinct game-owned ScriptStack::pop and ScriptStack::peek methods operate on the real ScriptStack word storage and ECL type tags 'i' and 'f'. Both use the original byte stack pointer, relative addressing and conversion rules. Their use of the standard C memcpy inside one copy branch does not convert the complete methods into CRT functions. They are original game-specific tagged VM operations implemented in natural maintained C++.

## Independently decoded whole-game Boss callers

The separately already exact **11,110B EclRuntime::tick** at 0x0053B5C0 has **2,525 original x86 instruction heads**. Full native PE disassembly reveals **185 actual original E8 call sites into this ECL parameter/stack protocol**, including already credited ECL argument and stack methods. Among them are 20 calls to float_destination, 18 to integer_argument, three to integer_destination, one to float_destination_at, and numerous calls to ScriptStack::pop; these numbers come from the genuine original 11,110B body, not old source guesses. The original Runtime tick remains whole-native strict exact with **11,110/11,110 coverage bytes and 11,504/11,504 whole compiler bytes**, already fully credited before this review.

Separately, the existing strict **923B EclRuntime::call_into** at 0x0053F3B0 has 304 original instruction heads and **12 direct original calls into this same protocol**. Its typed arguments invoke both consuming_float_value and consuming_integer_value, and it uses the real current() and ScriptStack::pop. ECL invocation frame construction/restoration, typed argument transfers and subroutine selection are authentic game logic. No additional 923B parent bytes are credited.

The supplied-value read variants also have independent real game callers:
- **47B Enemy::float_argument_value**, native E8 at **0x004AB064 to 0x0053EA90**.
- **40B Enemy::integer_argument_value**, native E8 at **0x004AB12D to 0x0053EE30**.

These full original Enemy forwarding methods are separately canonical strict exact. The original ScriptStack::peek is specifically called by individually strict ECL argument functions: physical original E8 sites **0x0053EDD9, 0x0053EA3B, 0x0053EE99 and 0x0053EB28**. Do not incorrectly imply the giant tick calls peek directly. The pop operation is directly called throughout the giant interpreter as well as the ECL-consuming argument functions and call_into.

## Bounded source compiler receipts and zero double counting

Two actually affected C++ source owners were cold rebuilt and compared with strict original replay, **not an unfiltered global cold replay**:

- src/EclArguments.cpp: **12/12 strict** complete canonical units in one cold MSVC source object.
- src/ScriptStackCopy.cpp: **3/3 strict** complete canonical units in one cold MSVC source object.
- The separately already exact EclRuntime::call_into had only its own stale receipt refreshed, 923/923 strict. The unchanged 11,110B Runtime was compared strictly. Both 47B and 40B Enemy forwarding methods were individually compared strictly.

Three original methods in the same source group had already been accepted as authored and are **not** credited a second time: **287B ecl_float_argument, 261B ecl_consuming_float, and 265B script_stack_push**. The giant exact 11,110B Runtime and 923B call_into also receive no additional credit.

Private reproducible proofs, ignored by Git:
- .analysis/core707-ECL-args-whole-parent-caller-matrix.json — original complete ECL interpreter and call_into native E8 roles.
- .analysis/core707-ECL-args-all-native-callers.json — original E8 references from all 6,928 provisional native function heads, including separate Enemy argument wrappers.
- .analysis/core708-ecl-args-stack-2073-native-provenance.py/json — actual original function/relocation bytes, 31 E8, nine physical original HIGHLOW, independently exact callers, native body completeness, strict canonical receipts and original-game interval non-overlap.

**Origin/credit-only change:** no C++ source, header, binary target, canonical unit, native profile or PE relocation was altered. Previously game-authored exact status **508 functions / 180,373 original bytes** becomes **520 functions / 182,446 original disjoint bytes**, adding exactly **12 complete ECL/ScriptStack game methods, 2,073 original bytes**. The original 41,967B Enemy ECL dispatcher and 39,470B Animation VM remain separate NONEXACT bosses. Whole-game linking or playability is not established.
