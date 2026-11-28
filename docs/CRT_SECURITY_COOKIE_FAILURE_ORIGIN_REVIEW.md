# VC cookie checking and complete failure-report state

Five whole installed MSVC x86 secchk.obj/gs_report.obj contributions match the
locked Japanese TH20 Steamless target: 526B/124 instructions and four
REL32/fifty-eight DIR32 roles, including the shared pointer record. All five
existing extents remain unchanged. The complete data scope is 872B: a 68B
cookie definition, 796B report state and an eight-byte exception-pointer pair.
Three original NOPs and every native epilogue remain within the code extents.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x005429EE` | 14 | `__security_check_cookie` |
| `0x00542A32` | 40 | `__raise_securityfailure` |
| `0x00542A5A` | 251 | `__report_gsfailure` |
| `0x00542B55` | 13 | `__report_rangecheckfailure` |
| `0x00542B62` | 208 | `__report_securityfailure` |

The reporting group forms a complete contiguous 512B interval. The checker
is a separate full 14B section; its internal failure label at offset nine
is not another physical function. No additional code alignment, EH scope or
switch table belongs to these five contributions.

## Cookie register protocol and caller attribution

The checker compares ECX with the global DWORD cookie. Equality returns;
mismatch takes the original tail JMP to the independently located report
entry. It does not push another return address. The x86 vcruntime.h declaration
is void fastcall with one uintptr_t argument, matching the decorated name and
native ECX use. Report_gsfailure is void cdecl with zero formal arguments;
ECX is part of its failure-state protocol, not a new cdecl/fastcall parameter.

Report_gsfailure retains its 804B (0x324) frame: 796B of stack-preservation space
and two cookie DWORDs. It tests processor feature 23; the supported path puts
failure code 2 in ECX and executes INT 29h. The original instructions then
place legacy capture after that feature query. General register stores are
DWORDs, segment stores are WORDs and EFLAGS comes from PUSHFD. Moving capture
before the query or widening segment stores would change the original state.

The legacy context obtains caller EBP from `[EBP]`, EIP from `[EBP+4]` and
ESP from `EBP+8`. The checker tail jump preserves that attribution. The
stack-preservation area's original volatile read remains. The report sets
ContextFlags to 0x10001, copies context EIP into ExceptionAddress, assigns
status 0xC0000409, noncontinuable flag one, one parameter and failure code 2.
Both global cookie values are then copied into the original local array
before calling the shared raise helper. No blanket context/record clear
replaces these partial writes.

## Generic/range reports keep their own state and epilogues

The generic report takes one ULONG failure code, uses a 796B (0x31C) preservation
frame and supplies that code to both fastfail and ExceptionInformation[0].
Its legacy capture and caller-address construction remain local to this
entry. It does not write ContextFlags or save the two cookie values. Thus
sharing a replacement capture helper that always initializes those fields
would change this owner. It otherwise writes the same exception status,
noncontinuable flag and one-parameter count before invoking the shared raise.

The range stub passes code 8 to the generic report. Its original CALL, NOP,
POP EBP and RET remain, including the absence of cdecl argument cleanup after
that call. Do not normalize this source-noreturn wrapper into an ordinary
returning function. The GS and raise functions have source noreturn annotations,
yet their emitted sections retain the original post-call epilogues as well.
The byte-level epilogues do not establish a successful returning API contract.

The 40B raise helper clears the process unhandled filter, calls the actual
UnhandledExceptionFilter with its supplied pointer pair, then calls
TerminateProcess(GetCurrentProcess(), 0xC0000409). All five kernel32 imports
in the group are independently named through the PE import table. No debugger
hook or alternate termination loop is introduced into the selected bodies.

## Full data, declarations and retained evidence

The full gs_cookie.obj data section uniquely matches `0x005B25C0`: initial
cookie 0xBB40E64E, sixty original zero alignment bytes and complement
0x44BF19B1 at +64. This establishes both addresses from the complete source
contribution rather than treating them as adjacent DWORDs. Its already reviewed
[initializer and SEH4 use](CRT_SEH4_COOKIE_DISPATCH_REVIEW.md) retain their credit;
no second initialization entry is added here.

The shared BSS begins at observed `0x005E4F68`: complete 80B EXCEPTION_RECORD
followed by 716B CONTEXT at `0x005E4FB8`, all in the loader-zero virtual tail.
The complete readonly pointer pair at `0x00597128` references those two source
objects, with both HIGHLOW fields checked. Unwritten register/record fields
retain their prior values. These report-state placements are observed linked
identities; zeros and the linked record do not independently establish new
canonical addresses.

Both objects refer to an unavailable external libcmt.i386.pdb type server.
Procedure names/extents are retained from CodeView; calling conventions,
formal parameters and field widths instead use installed x86 declarations,
complete COFF symbol/storage extents and the actual native sequences. The
source is VC crt/src/vcruntime/gs_report.c, gs_cookie.c and vcruntime.h.

Private `.analysis/origin-boundary/security-cookie-check/` retains gs_report.obj,
provenance, whole locations, three attested listings, external-type metadata,
full data and complete instruction/CFG/relocation/import comparisons. It reuses
secchk.obj in `catch-transfer/` and gs_cookie.obj in `seh4-dispatch/`. The separate
284B report_securityfailureEx has no whole ordinary-byte location and receives
no entry.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected hashes remain unchanged. Exact replay scope is **zero
units**, with no new authored or maintained-source exact credit.
