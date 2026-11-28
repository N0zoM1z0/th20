# UCRT application-type state and accessor identities

The complete SDK `_query_app_type` at `0x005558F0` (6B) and `_set_app_type`
at `0x005558F6` (15B) identify two pending library origins in the locked
Japanese TH20 Steamless target. Both access the same four-byte application
type state at `0x005E55D0`. All ordinary bytes, DIR32 fields and HIGHLOW
relocations agree with Windows SDK 10.0.26100.0 x86 `libucrt.lib` member
`report_runtime_error.obj`. Existing extents remain unchanged.

The getter's ordinary bytes occur at eleven target locations; the setter's
occur at five. The previously reviewed complete `_free_osfhnd` SDK section
names its call to `_query_app_type`, independently locating the real getter.
Its storage address then selects the one setter that writes the same slot.
All fourteen other accessor candidates reference different storage and are
rejected. Ordinary opcode shape alone cannot assign these identities.

The getter returns the raw enum value in EAX. The setter copies the entire
32-bit argument into the state, without range validation, normalization,
locking or atomic exchange. Source `ucrt/internal/report_runtime_error.cpp`
initializes the static enum to unknown/zero. Its complete four-byte BSS
contribution lies in the PE loader-zero tail. The original startup at
`0x0054339D` pushes GUI value 2 before calling this setter at `0x0054339F`;
`vcruntime/exe_common.inl` supplies the matching WinMain policy. The loader's
initial zero is therefore distinct from the configured GUI application type.

The pair ends at `0x00555904`, followed by eleven original INT3 bytes through
`0x0055590F`. No branch, tail or independent entry is omitted. This also
closes the named query dependency in the
[descriptor association review](CRT_DESCRIPTOR_LIFETIME_ORIGIN_REVIEW.md):
its console-only SetStdHandle branch compares the raw application type to 1.

The same SDK member's debug notification, console selection/output and full
runtime-error reporter do not acquire identities from these accessors. The
current complete-section search found no match for the larger contributions;
the 3B false-return helper has ten ordinary-byte candidates. Those remain
unresolved. In particular, adjacent target code is not named as the reporter
merely because it is near the accessor pair.

Private `.analysis/origin-boundary/runtime-app-type/` retains the SDK member,
complete search results, bounded attested listings/xrefs, `review.py` and
`reviewed.json`. The audit compares both complete code sections, their full
BSS closure and alignment, rejects all fourteen wrong-storage candidates,
rechecks the actual REL32 call in the earlier reviewed descriptor owner,
and retains the original GUI startup call. All 2,151 protected native
input/product hashes remain unchanged. This classification-only change has
**zero exact replay units**, with no new authored or maintained-source exact
credit.
