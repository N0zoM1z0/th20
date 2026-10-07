# Core ECL and Enemy dispatch reconstruction

CORE-055 is an investigation checkpoint. Neither dispatcher has accepted source
or an exact unit. EXACT-056 subsequently accepts its complete 923-byte invocation
dependency and actual empty diagnostic hook; see EXACT_ECL_CALL_RECONSTRUCTION.md.
The accepted graph now has 395 complete units and 62,507 disjoint comparison
bytes. The current priority is whole core dispatchers and their real protocols.

## Complete native intervals

All observations below refer to the locked Japanese Steamless executable.
Entries and table destinations were checked against complete PE instruction
decoding and attested, read-only Ghidra exports.

| Root | Body | Instructions | Dispatch tables | Direct calls / distinct dependencies |
| --- | --- | --- | --- | --- |
| ECL Runtime tick | `0053B5C0`, 11,110 bytes | 2,525 | `0053E128`: 98 pointers, 76 distinct case heads | 288 / 52 |
| EnemyState opcode execution | `0048C010`, 41,967 bytes | 8,896 | `00496400`: 174 pointers; `004966B8`: 704 byte indices | 1,264 / 236 |

Both complete intervals have one return and no direct branch outside the supplied
interval. Every dispatch pointer selects an instruction head within its body.
The Enemy index table selects the 174 primary entries after the signed opcode
is reduced by 300 and range-checked against 703. This does not establish source
ownership or justify adding either interval to the exact manifest.

The ECL comparison must also retain two alignment bytes and the complete
392-byte pointer table: 11,504 bytes in total. Enemy's two tables are independently
audited; complete compiler contribution ownership and alignment remain pending.

Body SHA-256 values:

- ECL: `fa8620503a045c427059ed013fd04c98316eb099442ec923468e1a0757af902d`.
- Enemy: `e6874e1ee7d7def173d3c4af12934573812db26a5572987ec0fa6fafb24a73f0`.

## Ghidra function membership is incomplete

The Enemy function-based export contains only 54 instruction heads. Its remaining
8,842 heads exist in the listing but are outside the inferred function body.
The new `disassemble_range` operation reads existing instructions throughout an
inclusive address interval, without changing the database, bytes or function
ownership. Its Enemy export contains all 8,896 heads and agrees with the PE.

ECL's function and range exports each contain 2,445 heads. Eighty heads are not
defined in the existing listing. Complete PE decoding retains these explicitly;
the wrapper does not silently repair the database or drop these instructions.

Reproduce the read-only exports and audits in the provisioned environment:

```bash
scripts/repo-python scripts/ghidra.py query \
  .analysis/core-ecl.asm disassemble_range 3000 0x53B5C0 0x53E125
scripts/repo-python scripts/audit-dispatcher.py \
  --entry 0x53B5C0 --size 11110 --jump-table 0x53E128:98 \
  --ghidra-export .analysis/core-ecl.asm --output .analysis/core-ecl-audit.json
scripts/repo-python scripts/ghidra.py query \
  .analysis/core-enemy.asm disassemble_range 12000 0x48C010 0x4963FE
scripts/repo-python scripts/audit-dispatcher.py \
  --entry 0x48C010 --size 41967 --jump-table 0x496400:174 \
  --index-table 0x4966B8:704 --ghidra-export .analysis/core-enemy.asm \
  --output .analysis/core-enemy-audit.json
```

The audit rejects partial decoding, invalid table destinations, invalid compressed
indices, truncated exports and listing/PE disagreements. Missing Ghidra heads and
external direct branches are reported for review. Reports explicitly leave source
acceptance and exactness false and remain under ignored `.analysis/`.

## Corroborated owners and call protocols

| Owner or record | Native x86 layout | Corroboration |
| --- | --- | --- |
| Instruction | 16-byte header; signed 16-bit opcode; payload follows header | Complete dispatch and argument-reader consumers |
| ScriptStack | 24 bytes: actual 16-byte PMR vector, signed stack pointer and frame base | Constructor `004A36D0`, push/pop/frame operations |
| Runtime | 72 bytes: time at 0, script position at 4, stack at `0C`, manager at `28`, interpolation vector at `34`, flags at `44` | Constructor `004A3580` and whole tick |
| ScriptManager | 112 bytes: current runtime at `0C`, main Runtime at `10`, loader at `58`, 20-byte intrusive sentinel at `5C` | Constructor `004A35F0`, async producers/consumers and virtual calls |
| ScriptInterpolation | 56 bytes: shared float interpolation at 0, saved frame base at `2C`, script position at `30` | Tick's configuration and final interpolation pass |
| Loader | 564 bytes: PMR record vector at `20C`, actual ScriptStack at `21C` | Constructor `004A3650`, stack constructor xrefs, instruction lookup |

Reference Runtime80 and Loader's proposed string tail cannot establish the native
ABI. The prior reference review already records the Loader discrepancy. Keep
the byte after Runtime rank as implicit layout alignment; its meaning is unknown.
The flags wrapper's construction and complete startup lifetime also remain open.

Important call contracts recovered from producers and consumers:

- `0053F0B0` / `0053F260` are generic stack pop/push with byte count, actual
  buffer pointer and requested type tag; they return integer status. They are
  not a fixed-word facade.
- `0053F3B0` calls from the current Runtime into a target Runtime and returns
  status. It takes target, argument-skip and an integer mode argument.
- `0053E390` async spawn returns status, not a Runtime reference.
- `0053E920` searches for an intrusive link, including the main sentinel.
- Argument readers obtain the current instruction internally. The final
  interpolation destination reader takes the original instruction, saved frame
  base and argument index 1; `2C` is not the argument index.
- Manager has six virtual slots: destructor, opcode execution, integer read,
  integer destination, float read and float destination.
- The 25-byte Enemy wrapper at `004969E0` adjusts its receiver by `88` before
  calling `0048C010`. The large dispatcher's receiver is the EnemyState subobject.

The root's random angle uses the actual shared random owner and signed-unit
output multiplied by pi. Reference names or mathematically convenient replacements
do not override the observed call and floating-point sequence.

## Whole C++ compiler hypothesis and remaining work

The private C++ hypothesis compiles all 98 ECL switch entries as one real x86
member function, including frame return/call, async control, jumps, waiting,
typed stack expressions, vector math and interpolation. Its owner layout asserts
pass with the locked headers. Direct dependencies remain declarations while
their production ownership and complete implementations are reconciled.

The local candidate profile is MSVC 19.44.35211 with `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:strict /Gd /sdl` and C++20. `/sdl` supplies the observed GS shape;
strict floating-point compilation retains the native division and comparison
forms. These are local compiler observations, not a whole-game profile claim.

Sequencing argument reads matters: opcode 87 reads 1, 2, 3, 4 before computing
the two differences; opcode 89 reads 1 then 2; opcode 90 retains its rotation
argument before normalization. Explicitly preserving these reads removed extra
compiler temporaries and brought the whole probe's frame reservation to the
native `5A0`. Shared stack expression macros and scoped return restoration now
reproduce many complete case instruction shapes. Case diagnostics are navigation
only; equal case lengths do not establish byte identity or exactness.

Remaining work includes full local-variable placement and common exits, whole
relocation/table replay, floating comparison edge behavior, real stack/frame
failure handling, dependency bodies and startup/lifetime ownership. The reference
does not resolve these. Invocation failure calls the native empty diagnostic
hook before returning failure; it does not output a log. EXACT-056 corrects the
earlier interpretation and preserves caller invalidation and current-runtime
retention. An invented throw or silent success is not acceptable.

Neither whole dispatcher hypothesis is a canonical exact result. Keep all
raw disassembly, decompiler output, object files, case diagnostics and candidate
source private. Continue with the whole tick and its immediate protocols, then
the complete Enemy dispatcher; defer unrelated leaves.
