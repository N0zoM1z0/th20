# Ghidra workspace

Ghidra 12.1.3 and Temurin JDK 21.0.12.1+1 reuse the installed TH095 tools via
private `.tools/` symlinks. Critical installed fingerprints are verified;
archive URLs/hashes are retained for a fresh independent bootstrap. The TH20
project is a separate `ghidra-project/TH20.gpr` and does not share databases.

```bash
python3 scripts/ghidra.py import        # first import, attest, create initial ledgers
python3 scripts/ghidra.py check
python3 scripts/ghidra.py query .analysis/entry.asm disassemble 40 0x005435E0
python3 scripts/ghidra.py query .analysis/entry.txt function 0x005435E0
python3 scripts/ghidra.py query .analysis/calls.txt callees 0x005435E0
python3 scripts/ghidra.py query .analysis/xrefs.txt xrefs_to 40 0x005435E0
python3 scripts/ghidra.py query .analysis/functions.txt list_functions 0 40 ''
python3 scripts/ghidra.py query .analysis/strings.txt search_strings 40 'th20'
python3 scripts/ghidra.py decompile .analysis/entry.c 0x005435E0
python3 scripts/ghidra.py architecture
python3 scripts/ghidra.py inventory
```

Initial import runs with two analysis CPUs. Every subsequent inspection uses
`-readOnly -noanalysis` and independently re-attests the target and project.
`inventory` exports into `.analysis/inventory/` without overwriting reviewed
ledgers. A file lock rejects concurrent CLI/bridge access to this project.
Analysis outputs must stay under `.analysis/`; decompilation accepts at most
16 explicit addresses. Script completion markers are checked so an earlier
attestation cannot hide a failed query/export/decompile script.

No target byte patching is allowed. Accepted names/types/boundaries/evidence
belong in the repository ledgers and knowledge base, not only in the database.
The available remote IDA database identifies TH09 and is outside this workflow.

## Optional ChatGPT web bridge

The project-agnostic bridge already installed in TH095 can use this wrapper.
`config/mcp-ghidra.env.example` and `scripts/run-ghidra-bridge.sh` select TH20's
workspace, workflow and scratch paths with a separate local port. It is not
started or externally published by the repository bootstrap. A public URL,
service installation or credentials are deployment choices separate from the
Ghidra analysis workspace. The CLI above is the validated analysis interface.
