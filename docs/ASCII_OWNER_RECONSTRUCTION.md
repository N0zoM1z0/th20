# AsciiInf storage and shared text resources

CORE/EXACT-160 reconstructs the complete native AsciiInf storage and constructor
in TextLine.hpp/cpp. This is the actual receiver used by Dialogue, rather than
the reference renderer's service adapters. The sole comparison target remains
the locked Japanese v1.00a Steamless executable.

## Native evidence

The 687-byte constructor at 0x46A8E0 publishes process slot 0x5C0698 after
`initialize AsciiInf\n`. The independent deleting wrapper at 0x46B510 supplies
size 0x1A360. COL 0x5A3D44 and its hierarchy identify class AsciiInf, public
TaskInf at offset zero, and slots 0x46B510 / 0x46C930 / 0x421760. The source
preserves the native class key and inherited disable slot. Complete RTTI/vtable
data exactness is a separate open question.

| Offset | Established storage / behavior |
| --- | --- |
| 0 | Real 16-byte TaskInfo base |
| 0x10, 0x5F4, 0xBD8 | Three separate 0x5E4-byte Animations; three constructor calls |
| 0x11BC | std::array of 320 real 0x140-byte TextLines |
| 0x1A1BC | Signed line count |
| 0x1A1C0..0x1A1FC | Individually initialized color, scale, font, layer, alignment and unresolved scalar state |
| 0x1A200 | Actual eight-byte IntPoint texture size |
| 0x1A208 | Angle, constructed with float zero through 0x429210 |
| 0x1A20C | 24-byte observed IntrusiveList of TextJob pointers |
| 0x1A224 | Actual 16-byte Worker |
| 0x1A234 | Eight-byte std::list of std::function<void()> |
| 0x1A23C..0x1A24C | Font width, unresolved scalar, instance AnimationFile and two handles |
| 0x1A250..0x1A25C | Four distinct FunctionChainNode pointers |
| 0x1A260 | 256-byte text buffer; object ends at 0x1A360 |

The four draw nodes have independent stores, enable calls and retirement calls;
they are separate members. Line/job producers independently copy font, shadow,
layer, duration and alignment fields into their typed records. Unresolved scalar
roles retain neutral offset names. No reserved arrays or explicit padding are
introduced. TextJob itself remains a separate unresolved owner.

The queue's actual callable RTTI names include AsciiInf::JPrintf lambdas and
`_Func_impl_no_alloc` with void result and an empty argument pack. The pinned SDK
template and complete list construction corroborate std::function<void()>;
the reference declaration alone does not establish this identity.

The native constructor and typed TextLine array use complete flags-5 noexcept
EH support. TextLine's recovered noexcept declaration leaves its complete
219-byte code unchanged. The maintained constructor preserves the repeated
style assignments and publishes only after diagnostics.

The member at 0x470670 returns the shared AnimationFile slot 0x5C5880 and ignores
instance state. Independent resource publication at 0x4D8350 and actual File::spawn
consumers at 0x4DE360 / 0x4DE430 identify that slot. It differs from the instance
file at +0x1A244; replacing one with the other changes Dialogue's resource path.

## Complete compilation and comparison

Only TextLine.hpp/cpp change reconstruction inputs. Original receipts' captured
include closures select one provider / one previous unit. Its original receipt
and every required SHA-bound source version are archived before editing. The
other 163 providers reuse passing evidence; the maintained source path set stays
at 279. One diagnostic build and one final canonical build run serially at
reduced priority. The final profile uses /Od /Ob0 /GS /sdl /EHsc /arch:SSE2
/fp:precise with the locked x86 MSVC candidate.

| Complete unit | Entry | Code / compared bytes | Origin |
| --- | --- | ---: | --- |
| AsciiInf constructor | 0x46A8E0 | 687 / 692 | Authored |
| TextLine array constructor | 0x46A6B0 | 81 / 86 | Compiler |
| Pending-task list constructor | 0x46A8B0 | 45 / 45 | Library |
| Shared text-file getter | 0x470670 | 16 / 16 | Pending |

All four units strictly replay every byte and relocation. Both complete emitted
five-byte INT3 tails are included; no target-sized prefix is compared. The
affected previous TextLine unit also strictly passes. Independent complete EH
sections replay another 94 distinct bytes: two 29-byte handlers and shared
36-byte flags-5 metadata. These support bytes are separate from canonical
progress. Relocations use independent native identity, complete component
exports, unique literal contents, SDK types and prior verified dependencies;
none is solved from the field under comparison.

## Semantic corroboration and limits

The O2/UBSan fixture uses actual AsciiInf, all three Animation constructors,
320 TextLines, Angle, Worker, TaskInfo construction and standard containers.
It passes 256 guarded dirty-memory constructions, complete images of 81,920
TextLines, 768 shared-file selections through two live receivers, callable
ownership and virtual dispatch checks. A separate process confirms termination
on a captured diagnostic exception without publishing the new owner.

Process allocator startup, scheduler methods and AsciiInf's native resource
destructor are explicit fixture boundaries. The fixture's default destructor
exercises real member teardown; it does not reconstruct native resource cleanup.
Unloaded real AnimationFiles supply borrowed identities. No GDI, GPU, loader,
whole-game runtime or native CPU execution is claimed. At CORE160 the existing
whole-root fixture recorded TextLine.hpp as an input, so that affected fixture
was refreshed and passed all 36,244 cases. Its candidate/cases were unchanged.
The earlier FrontInf fixture retained its twelve unchanged input hashes and
passing 1,706 cases; it was not repeated in that batch.

The generic job-list constructor retains its known 31/native40 emission question;
it receives no new exact credit. Full AsciiInf destruction, initialization,
queue execution, formatting and drawing remain open. CORE161 subsequently closes
the complete 1,738-byte Dialogue constructor at 0x4AF310 over its real 0x140-byte
owner, actual Cursor cleanup, callbacks and cancellation receiver interfaces.
See [current Dialogue evidence](DIALOGUE_OWNER_RECONSTRUCTION.md) for that closure,
updated fixtures and remaining native resource/geometry work.
The production Enemy dispatcher and whole-game link remain incomplete.

Private reproducibility records under .analysis/ include core160-pre-ascii-inputs,
core160-pre-registration-ledgers and core160-probe-v1-original-inputs archives;
core160-independent-bindings.json, core160-ascii-native-identity.json,
core160-ascii-callable-identity.json, core160-sdk-container-origin.json,
core160-cold-proof.json, affected/new strict results, the semantic log and
core160-retirement-plan.json. Preserve native exports and unfinished inputs.
