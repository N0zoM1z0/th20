# ECL invocation and frame protocol

EXACT-056 accepts the complete 923-byte invocation at `0053F3B0` and the actual
five-byte empty release diagnostic hook at `0040C6B0`. The invocation is authored
application behavior. The empty hook's library/template/ICF origin remains
unresolved and receives no authored credit. This coherent protocol directly
supports the whole ECL dispatcher; it does not establish exactness of tick.

The accepted graph is 395 whole canonical units / 72 cold objects / 62,507
disjoint comparison bytes. Authored credit is 63 functions / 5,838 bytes.
The complete graph was rebuilt after adding declarations to ScriptStack.hpp.

## Shared ownership and native behavior

EclRuntime.hpp defines one native owner model: Instruction16, Runtime72,
ScriptStack24, ScriptInterpolation56, Manager112 and Loader564 on MSVC x86.
The interpolation derives the maintained FloatInterpolation; runtime stacks use
the maintained PMR ScriptStack. The loader owns actual PMR subroutine records
and its global stack. The manager has six concrete virtual defaults, rather
than pure virtual methods: its observed vtable at `005703B0` points to deleting
destructor `004A4120`, zero-argument integer default `00412540`, one-argument
integer/pointer default `00414B50`, float-zero default `004AB070`, and aliases.
Loader's two one-word callback slots precede its destructor at `005703A0`;
their higher-level purposes remain unclassified.

Native construction, destruction, flags initialization wrapper, callback roles,
production startup and enclosing ownership remain open. Their declarations
grant no source implementation, linkability or runtime credit.

call_into reads the current instruction and transfers descriptor arguments into
the target's stack ahead of its pointer. Descriptor offsets and the name skip
are word-addressed; name_skip is not a mode flag. Sources marked `f` or `g`
consume floats, other source tags consume integers. Destination `f` selects
float storage, otherwise integer storage; cross-type stores use numeric
conversion. Argument reads remain ordered and may consume the caller's stack.

An empty target first receives a zero frame word. Its return record contains the
post-consumption pointer followed by three minus-one sentinels. An existing
target preserves the previous frame word at the original boundary, then saves
the post-consumption pointer and caller time, offset and subroutine. Argument
storage starts after this return record. Stack offsets are bytes, not indices.

The manager switches its current runtime to the target before activation.
Success restores the previous current runtime. Missing subroutine failure
invalidates the caller's offset and subroutine and **retains the target as
current**. The hook invoked on failure has an empty complete native body; it
does not produce a log. This corrects CORE-055's earlier logging interpretation.

## Independent relocation and data evidence

All 27 invocation relocation fields are replayed from independently identified
callee definitions, layout producers and consumers. Structural comparison's
solved fields were not used as canonical addresses.

| Symbol role | Native address | Evidence |
| --- | --- | --- |
| Runtime current instruction | `005403D0` | Complete position/loader consumer |
| Stack pointer read / write | `00411700` / `00412DA0` | Receiver +16 access and invocation call sites; physical ICF aliases |
| Stack generic push / pop | `0053F260` / `0053F0B0` | Complete 263/242-byte generic copy/tag protocol |
| Stack absolute word | `0053E630` | Previously accepted maintained PMR owner |
| Consuming float / integer | `0053EC80` / `0053EFB0` | Reference mask, stack and manager consumers |
| Manager loader getter | `00437660` | Receiver +88 load |
| Loader activation | `0053FDF0` | Complete 95-byte instruction interval |
| Empty diagnostic hook | `0040C6B0` | Whole five-byte frame/return, no observable operation |
| Original diagnostic format | `00576A20` | Readable literal and exact CP932 data comparison |
| Security cookie / checker | `005B25C0` / `005429EE` | Existing independently accepted CRT/global anchors |

Loader activation's first call is set_loader `0041DFB0`, followed by
set_subroutine `00540550`, set_offset `00540590`, set_time `00540510` and current
instruction `00499310`. Name lookup is the sorted-record binary search at
`00540340`, invoked by set_subroutine. These dependencies are attested but not
new exact units in this checkpoint. `0053F9A0` is inside library vector insertion
and must not be labeled as name lookup.

The error literal preserves original Japanese text. EclDiagnostic.cpp's recipe
explicitly selects UTF-8 source and CP932 execution encoding. Its COFF data
symbol's complete 28 bytes, including NUL, match native `00576A20`; SHA-256 is
`d4b344c5ef705eae46fb25acb8bbe808750cf6253cb34e1534baa2c9d5be004a`.
This data check is separate from counted function coverage.

## Compiler and semantic checks

Invocation uses the pinned MSVC 19.44.35211 x86, C++20, /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:strict /Gd /sdl profile. The diagnostic uses the same base without
/sdl and adds the explicit charset flags. Each has one maintained semantic
body, with no profile branches, invented returns or shaping locals.
Canonical replay compares every byte, including relocated fields.

tests/ecl_call_semantics.cpp uses actual maintained owners and checks fresh and
nested frames, float/integer numeric conversion, ordered reads, skip offsets,
post-consumption pointer capture, saved return state, guard words and failure
retention. Constructor/destructor, argument resolution, generic four-byte stack
copy and activation definitions are explicitly test-only dependency fixtures.
They grant no native implementation credit. Portable C++20 /O2-equivalent host
checks run with UBSan and -fno-strict-aliasing to model MSVC's raw-word float/int
stack access; they are not proof of portable ISO strict-aliasing behavior or
whole-game runtime acceptance. Full public CI and private target/tracking/Ghidra
attestation are required alongside the cold replay.
All 29 public tests and private target/tracking/progress/full Ghidra gates pass
at this checkpoint.

```bash
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/ci.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
```

## Whole dispatcher remains pending

The best private tick hypothesis has the complete native 11,110-byte body,
two alignment bytes and 392-byte table: 11,504 bytes total. Structural diagnostics
match 9,875 of 9,900 non-relocation bytes, with 25 differences concentrated in
opcode 81. The 1,604 excluded relocation bytes and table replay remain unproven.
The nested polar expression evaluates argument 3 before 2, unlike native.
Saving a scalar fixes the order but changes frame size and temporary placement.
This checkpoint additionally tested aggregate and structured-binding snapshots:
both retain the complete size and frame reservation, but broadly alter native
stack slots (6,331 and 5,581 structurally matching bytes). They were rejected.
No dispatcher prefix, case fragment or exact-size hypothesis is credited.

Continue with the whole tick's ordered polar-argument lifetime and full replay,
then the complete 41,967-byte EnemyState dispatcher. Defer unrelated leaves.
Raw probes, objects, exports and rejected experiments remain ignored.
