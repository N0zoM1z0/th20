# Whole Enemy dispatcher control flow and compiler tables

EXACT-063 subsequently closes the five actual temporary construction/destruction
owners and ShotMetadata move assignment, including complete PMR/EH support.
The graph is now453units/86objects/85406bytes; the whole dispatcher and queue/
factory protocol remain pending. See EXACT_ENEMY_TEMPORARY_RECONSTRUCTION.md.
The CORE-062 graph and counts below record the historical investigation.

CORE-062 continues the complete 0048C010 dispatcher. This is a native protocol
and boundary investigation; no new source function or exact unit is accepted.
The accepted graph remains 442 units / 84 objects / 84,017 comparison bytes.

## Full native graph

The locked PE and attested Ghidra listing agree on all 8,896 instructions over
41,967 body bytes. The signed opcode is reduced by 300 and unsigned-range checked
through 1003. The 704-byte compressed index selects 174 distinct primary heads:
173 nondefault heads cover 224 opcode values; the normal default covers 480.

Normal paths initially left four indirect branches and 240 instruction heads
unresolved. Independently reviewing the rank switches closes four nested tables:

| Opcode | Indexed jump | Table | Pointers | Native rank bound |
| --- | --- | --- | ---: | ---: |
| 529 | 00491F68 | 00496978 | 4 | 3 |
| 530 | 0049203C | 00496988 | 4 | 3 |
| 570 | 00492123 | 00496998 | 8 | 7 |
| 571 | 004922AB | 004969B8 | 8 | 7 |

The jump operands, preceding unsigned bounds, Ghidra data xrefs and every decoded
pointer independently establish these tables. Argument reads occur before
argument-destination resolution. The last listed rank and the unsigned default
share the final argument branch. An indexed argument calculation in the reference
adapter does not establish the original nested switch emission.

With these explicit bindings, the 174 case paths reach 8,856 instruction heads.
The remaining 40 are exactly the entry/prologue/primary dispatch sequence through
0048C0AD. There are no unresolved indirect jumps, external successors or unselected
primary entries. Calls are recorded but not traversed; implicit exception paths
are a separate protocol. Case paths share the normal exit, and opcodes309..312
can enter the common300-family body. Reachable sets are not disjoint function
contributions and cannot justify partial exact credit.

The complete direct-call inventory contains 1,264 sites and 236 distinct targets.
55 canonical entry addresses cover 590 sites. Physical aliases and library support
are excluded from these navigation counts; they do not measure root completion.

## Comparison extent still needs compiler ownership

The native body ends at004963FE. A single NOP at004963FF precedes the main
696-byte pointer table00496400 and704-byte index table004966B8. The four nested
tables add96bytes and end at004969D8. The raw contiguous block is therefore
43,464 bytes, followed by eight INT3 bytes before the next entry004969E0.

This corrects the earlier two-table inventory. All five pointer tables, the
compressed indices, alignment and trailing-byte attribution must be reconciled
with the complete cold COFF contribution. Neither43,464 nor a shorter prefix is
an accepted comparison size yet. Do not omit the nested tables or silently drop
the eight trailing bytes merely to obtain a match.

The native EH handler at005694AC decodes42bytes and references FuncInfo005AA704.
Its observed flags are1, distinct from the flags5 nonthrowing constructors.
Five unwind entries at005AA728 point to11-byte cleanup thunks00569470/47B/486/491/49C.
State stores associate them with opcode600 and laser opcodes702/703/713/711.
The cleanup targets are47C450,47C4B0,47C490,48B890 and48B8B0 respectively.
Actual temporary record ownership and complete compiler/EH replay remain open;
do not add a nonthrowing root contract or use raw trivial replacement records.
Ghidra has no function membership for the handler, so these observations come
from read-only decoding of the independently locked PE, not repaired database data.

## Reproduce the complete case audit

```bash
scripts/repo-python scripts/audit-dispatcher.py \
  --entry 0x48C010 --size 41967 --jump-table 0x496400:174 \
  --index-table 0x4966B8:704 --opcode-base 300 \
  --nested-table 0x491F68:0x496978:4 \
  --nested-table 0x49203C:0x496988:4 \
  --nested-table 0x492123:0x496998:8 \
  --nested-table 0x4922AB:0x4969B8:8 \
  --ghidra-export .analysis/exact055-enemy-range.asm \
  --output .analysis/core062-enemy-case-catalog-complete.json
```

Each nested binding must name the actual indexed JMP operand and complete valid
instruction destinations. Unknown indirect branches, unselected table entries
and disconnected instructions remain explicit. Synthetic tests cover shared
case tails, opcode aliases, disconnected code, external/indirect branches and
invalid table/operand bindings; they contain no original game bytes.

Private evidence includes core062-enemy-case-catalog-complete.json,
core062-enemy-dependency-inventory.json, the attested nested-table xrefs and
argument/owner exports, and core062-enemy-exception-info.json. A natural C++ draft
of the four rank statements is kept privately for whole-root integration; it is
not a separate function, compile target or accepted partial dispatcher.
Continue with actual destination wrappers, shared shot metadata and four real
laser temporary owners, then the complete natural dispatcher source/COFF replay.
