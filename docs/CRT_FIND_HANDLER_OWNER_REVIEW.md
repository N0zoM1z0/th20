# VCRuntime FindHandler owner

The complete MSVC 14.44.35207 x86 `libvcruntime.lib(frame.obj)` FindHandler
contribution identifies one pending library origin at `0x00546B5A` in the
locked Japanese TH20 Steamless target. All 930B/300 instructions and the
final INT3 at `0x00546EFC` agree. The existing instruction extent is unchanged.
This parent owns no additional data or local EH table; its shared providers
and class/throw metadata retain their complete preceding proofs.

## Current state and rethrow adoption

The owner obtains current frame state and requires `-1 <= state < maxState`,
aborting on failure. Its strict MSVC record predicate requires C++ code
0xE06D7363, exactly three parameters and magic 0x19930520, 21 or 22.
A matching record with null ThrowInfo denotes rethrow.

If no current exception is stored in VCRT PTD+0x10, that rethrow returns
immediately. Otherwise FindHandler adopts the saved exception and context
at PTD+0x10/+0x14, marks its local IsRethrow byte and validates the adopted
record. A null record or another strict null-ThrowInfo rethrow aborts.
No replacement exception or termination is added to the empty-current path.

## Unexpected's specification is consumed before replacement

For a rethrow with current specification at PTD+0x1C, the owner saves that
pointer locally and clears the slot immediately. If the exception belongs
to the specification, ordinary search continues. Otherwise an inlined scan
compares each specified type with the complete bad_exception TypeDescriptor
at `0x005B4030`, through the reviewed type_info equality method.

Without an allowed bad_exception, the owner calls the established terminate.
When replacement is allowed, it destroys the original exception with
throw-not-allowed true, constructs a 12B bad_exception locally and calls the
complete CxxThrowException with ThrowInfo `0x005AC1FC`. Clearing the spec slot
before these calls prevents the replacement throw from repeating that branch.
These two static identities come from the full independent class/throw proof,
not from the parent fields being compared.

## Typed search preserves the rethrow jump to the next try

For a strict C++ exception with try blocks, the complete range helper selects
the current-depth range. Each in-scope 20B try entry scans its 16B handlers,
and each handler scans the thrown object's catchable conversions. The actual
TypeMatchHelper supplies the match decision.

A match invokes the complete CatchIt owner with the original marker, depth,
local IsRethrow and recursive flags. If CatchIt returns on rethrow, search
advances directly to the next try block. It does not try another conversion
or another handler in that same try. All copied entries, loop guards and
continuation edges remain inside the full parent extent.

After an unmatched recursive x86 translation, the owner destroys the translated
exception with throw-not-allowed true before continuing to the specification
checks. The original byte-width recursive test is retained.

## Specification, noexcept and foreign terminal paths

The specification/noexcept gate preserves its masked magic thresholds,
specification-pointer test and noexcept catch-depth condition. Once entered,
noexcept publishes the current exception/context and calls terminate.
Otherwise a failed specification check publishes those same values, unwinds
the supplied marker or subject node, unwinds the subject to empty state and
calls the complete CallUnexpected provider.

A non-C++ exception with try blocks goes to the reviewed foreign-search owner
unless recursive is true; that recursive foreign case aborts. With no try
blocks it skips foreign search. General returning paths verify that the
current-spec slot is null. The empty-current rethrow's earlier return remains
separate. No terminal, replacement or final-verification branch is removed
from the 930B body.

## Evidence and affected scope

Private `.analysis/origin-boundary/find-handler/` retains `review.py`,
`reviewed.json` and the original row. It reuses the full frame member and
bounded attested `find-handler-native.txt` in `type-info/`. All 300 instructions
are listed, with no omitted bytes. Every branch, REL32/DIR32 role and HIGHLOW
field agrees; the only HIGHLOW fields name the bad_exception TypeDescriptor
and ThrowInfo. Eleven complete unchanged code/data sections are reused through
their existing object hashes and provider proofs. Installed x86 `frame.cpp`
corroborates the ordered search, rethrow, replacement and terminal protocol.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new authored or maintained-source
exact credit.
