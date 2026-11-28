# UCRT thread parameters, startup and exit

Six complete SDK 10.0.26100.0 x86 `libucrt.lib(thread.obj)` contributions
identify five pending origins and recover three entries in the locked
Japanese TH20 Steamless target. All 493B in `0x00547BC3..0x00547DAF` agree:
490B of instructions and three terminal INT3 bytes. The complete 28B SEH
table independently identifies the recovered startup filter and handler.

| Entry | Instruction bytes | Role |
| --- | ---: | --- |
| `0x00547BC3` | 94 | stdcall beginthreadex startup, recovered |
| `0x00547C21` | 20 | startup SEH filter, recovered |
| `0x00547C35` | 11 | startup SEH handler, recovered |
| `0x00547C41` | 55 | thiscall parameter destructor/release |
| `0x00547C78` | 86 | common thread exit |
| `0x00547CCF` | 80 | thread-parameter creation |
| `0x00547D1F` | 131 | public beginthreadex |
| `0x00547DA2` | 13 | public endthreadex |

INT3 occupies `0x00547C40`, `0x00547CCE` and `0x00547DAF`. The old
endthreadex extent included its final INT3; its instruction extent is now
13B, with that byte retained in the complete contribution. All other old
extents remain unchanged. The six sections contain no unassigned instruction
bytes. The separate destructor and release COMDATs have identical full bytes
and relocation roles at one physical head, with no duplicate entry credit.

## Parameter ownership and creation

The native calloc-base call allocates one 20B parameter object. The installed
`corecrt_internal.h` layout agrees with every accessed offset: procedure at
+0, context at +4, thread handle at +8, module handle at +12 and apartment
flag at +16. The allocation zeroes the handles, flag and structure padding.
Creation writes procedure/context, calls GetModuleHandleExW with flags 4
and the procedure address, and ignores that call's result. It does not turn
a failed module lookup into a creation failure.

The original temporary-owner protocol remains visible: creation calls
free_base(null) after calloc, detaches a successful parameter, and invokes
the full parameter destructor on its now-null local. These calls are part
of the native body, not reasons to add null or allocation recovery branches.
The independently reviewed calloc/free bases are `0x00557B40` and
`0x00557BA0`.

The parameter destructor skips a null object. For a real object it closes
the nonnull thread handle, releases the nonnull module handle, frees the
object and clears its owning pointer. It tests these handles only against
zero. Unlike common thread exit, it has no separate INVALID_HANDLE_VALUE
test. Both destructor and release source roles share this complete body.

## beginthreadex transfers the parameter after CreateThread succeeds

A null procedure sets errno to 22 and invokes the existing resumable
invalid-parameter helper; if it returns, beginthreadex returns zero.
Parameter-allocation failure likewise returns zero. CreateThread receives
the original security descriptor, stack size and creation flags, the
recovered startup entry and the complete parameter pointer. This path adds
no forced suspension or ResumeThread call.

CreateThread failure maps GetLastError through the reviewed errno mapper,
destroys the parameter and returns zero. On success, the function copies
the local thread ID only when the caller supplied an output pointer, detaches
the parameter, calls the original null-owner destructor and returns the
thread handle. It never stores that handle into parameter+8. That field
belongs to the separately compiled beginthread path; for beginthreadex the
caller retains handle ownership. The standalone beginthread section has no
complete target location and receives no body credit.

## Startup callback and exceptional partitions

The recovered stdcall startup receives the parameter passed to CreateThread.
A null parameter exits immediately using GetLastError. Otherwise it stores
the parameter in UCRT PTD+0x360 and queries the already reviewed thread-init
policy. Policy value 2 calls RoInitialize with type 1. Only HRESULT zero
sets parameter+16 true; a nonzero result, including S_FALSE, sets it false.

Within the active SEH region, startup guard-checks and invokes the original
stdcall user procedure with parameter+4. It passes the returned unsigned
value to endthreadex. There is no returning startup epilogue to invent.

The whole SEH table at `0x005AC258` contains header values
`[-2,0,-44,0]` followed by scope `[-2,0x00547C21,0x00547C35]`.
The filter saves the exception code and forwards it with the exception
information to the independently reviewed seh_filter_exe at `0x005529D7`,
returning its decision. It is not an unconditional catch. If selected, the
handler restores the parent ESP, passes that saved code to the reviewed
process `_exit` at `0x00552DED`, and does not return. Ghidra's listing omits
the handler's three instructions; the retained supplemental decode and full
archive comparison cover all eleven bytes and its real call relocation.

## Common exit and module lifetime

Common exit calls the UCRT nullable PTD getter at `0x00557A13`. Missing PTD
or beginthread context immediately calls ExitThread with the original code.
An apartment flag calls the already reviewed RoUninitialize shim. A thread
handle is closed only when neither zero nor -1. A module handle satisfying
the same two tests goes to FreeLibraryAndExitThread with the original code;
otherwise the terminal call is ExitThread. No separate FreeLibrary followed
by ExitThread is substituted for the combined module-release operation.

These terminal bodies contain no parameter free, PTD free, context reset or
return epilogue. The public cdecl endthreadex forwards its code to common
exit and ends with the retained INT3. Cleanup beyond these bodies remains
with its actual external owners.

## Negative candidates and validation scope

The SDK's eight-byte endthread shape matches at `0x0055234D` and
`0x0055C4C1`, inside other pending owners. Both actually call invoke_watson
at `0x005480CC`, not common thread exit. The three-byte pointer getter shape
matches inside the owners at `0x0054C5FB` and `0x0054C620`. None establishes
a thread helper entry or alias. Unlocated weak helpers receive no credit.

Private `.analysis/origin-boundary/ucrt-thread/` retains the complete member
and archive path, bounded attested listings, locator results, original ledger
rows, `review.py` and `reviewed.json`. All ordinary bytes, internal branches,
REL32/DIR32 roles, HIGHLOW fields and the full SEH table agree. Seven actual
Windows import names are checked independently through the PE import
directory; reviewed external bodies retain their previous identities.
Installed UCRT `startup/thread.cpp` and `inc/corecrt_internal.h` corroborate
the protocol, layout and calling conventions.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no authored or maintained-source exact
credit added.
