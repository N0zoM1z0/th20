# VCRuntime throw records and unexpected rethrow

Three complete MSVC 14.44.35207 x86 `libvcruntime.lib` contributions close two
pending origins and recover three entries in the locked Japanese TH20 Steamless
target. All 198 instruction bytes, six INT3 bytes and the complete 88B C++ EH
metadata agree. The members are `throw.obj` and `frame.obj`.

| Entry | Instruction bytes | Role |
| --- | ---: | --- |
| `0x00544A7C` | 109 | stdcall CxxThrowException |
| `0x005473F3` | 35 | CallUnexpected primary |
| `0x00547416` | 20 | compiler catch/rethrow entry, recovered |
| `0x0054742A` | 5 | shared terminal abort, recovered |
| `0x0056B272` | 29 | compiler EH handler, recovered |

The old 60B CallUnexpected extent is repartitioned without dropping bytes.
Six original INT3 bytes follow at `0x0054742F..0x00547434`, completing its
66B section. The throw extent remains unchanged. The EH handler's two initial
NOPs are instructions, included in its complete 29B body.

## Throw parameters, WinRT and pure magic

CxxThrowException preserves the original exception-object pointer and starts
with magic 0x19930520. For nonnull ThrowInfo with WinRT attribute 0x10, it
loads the object's pointer, steps back one pointer slot to obtain the WinRT
exception-info pointer, and adopts throwInfo from that structure at +0x18.
It guard-checks and calls PrepareThrow at +0x20 with the pointer-slot address.
The adopted ThrowInfo is loaded before that call and retained afterward.

A nonnull final ThrowInfo with pure attribute 8 selects magic 0x01994000.
Otherwise the original magic remains. The independent RaiseException import
receives code 0xE06D7363, noncontinuable flag one, count three and the stack
array `[magic, original object pointer, final ThrowInfo]`. This x86 body has
no image-base lookup or fourth parameter. Its original emitted epilogue,
including RET 8 after RaiseException, remains in the whole contribution.
Installed `throw.cpp` and `ehdata_values.h` corroborate the flags and magic.

## Unexpected preserves the exception specification through rethrow

CallUnexpected first verifies that VCRT PTD+0x1C, the current exception-
specification pointer, is null. Failure calls the shared abort. The protected
path invokes the previously reviewed unexpected implementation.

Its compiler catch entry sets PTD+0x1C to the supplied specification and
calls the complete CxxThrowException with both arguments null, preserving
the original rethrow protocol. It does not construct another exception
object or return to unexpected. The shared abort also retains the original
terminal fallthrough after the rethrow call.

This is a C++ catch(...) with HandlerType adjective 0x40. It is distinct from
the SEH execute-handler filters reviewed elsewhere: the foreign-exception
search's standard-ellipsis exclusion still applies.

## Complete C++ metadata identifies the compiler handler

The full 88B section at `0x005AC168` contains a 16B catch descriptor, two
eight-byte unwind entries, one 20B try entry and a 36B FuncInfo record.
The catch points to `0x00547416`; both unwind actions are null with next
state -1. The try spans states 0/0 with catchHigh 1 and one catch. FuncInfo
at `0x005AC19C` has magic 0x19930522, maxState two and EHFlags one. All
internal table pointers and all four HIGHLOW fields agree.

Of thirty complete ordinary-byte EH-handler candidates, only `0x0056B272`
references this full metadata with the real catch destination. It calls
the independently identified cookie checker and tail-jumps to the reviewed
shared CxxFrameHandler3 entry at `0x00544722`. Its EAX FuncInfo channel is
preserved. The guard computes the cookie argument from registration-20 XOR
registration+12, matching the original catch prologue layout. This entry is
also registered in the target's central SafeSEH table.

The other twenty-nine candidates name different metadata or bindings and
receive no aliases. Identification uses the whole metadata/catch closure,
before checking CallUnexpected's handler pointer under comparison.

## Evidence and affected scope

Private `.analysis/origin-boundary/throw-unexpected/` retains the full throw
member, bounded attested listings, EH-candidate negatives, original rows,
`review.py` and `reviewed.json`. It reuses frame.obj in `type-info/` and the
previous cookie/entry proofs. Every ordinary byte, branch, REL32/DIR32 role,
HIGHLOW field and complete local EH section agrees. RaiseException is named
independently through the PE import directory. Installed `frame.cpp` supplies
the unexpected/specification protocol.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new authored or maintained-source
exact credit.
