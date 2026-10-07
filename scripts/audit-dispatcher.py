#!/usr/bin/env python3
"""Audit a whole dispatcher interval and its independently supplied jump tables.

This read-only target audit does not accept source, origins, compiler matches or
function ownership. Ghidra's listing is checked against the locked PE; omitted
heads remain explicit, including code outside an inferred function body.
"""
from __future__ import annotations

import argparse
from collections import defaultdict
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import struct

from project import ROOT


def catalog_case_paths(instructions: list, table: list[int],
                       indices: bytes | None, opcode_base: int,
                       nested_tables: dict[int, dict] | None = None) -> dict:
    """Follow normal control flow from every case, preserving shared tails.

    These reachable sets are navigation aids, not function contributions or
    disjoint comparison intervals. Implicit exception edges are not inferred.
    """
    import capstone

    if opcode_base < 0:
        raise ValueError("opcode base must be nonnegative")
    heads = {instruction.address: instruction for instruction in instructions}
    nested_tables = nested_tables or {}
    for jump, nested in nested_tables.items():
        instruction = heads.get(jump)
        if instruction is None or instruction.mnemonic != "jmp":
            raise ValueError("nested table binding is not an indirect JMP instruction head")
        operand = instruction.operands[0]
        if (operand.type != capstone.x86.X86_OP_MEM or
                operand.mem.base != capstone.x86.X86_REG_INVALID or
                operand.mem.index == capstone.x86.X86_REG_INVALID or
                operand.mem.scale != 4 or
                (operand.mem.disp & 0xffffffff) != nested["address"]):
            raise ValueError("nested table binding disagrees with the indexed JMP operand")
        if not nested["entries"] or any(target not in heads for target in nested["entries"]):
            raise ValueError("nested table has an invalid instruction destination")
    groups = defaultdict(list)
    selections = indices if indices is not None else range(len(table))
    for offset, selection in enumerate(selections):
        groups[table[selection]].append(opcode_base + offset)
    # Include even table entries unselected by the compressed index table.
    for head in table:
        groups[head]
    reached = set()
    paths = []
    for head, opcodes in sorted(groups.items()):
        pending = [head]
        visited = set()
        calls, indirect_calls, exits, unresolved, shared_entries = [], [], [], [], set()
        while pending:
            address = pending.pop()
            if address in visited:
                continue
            instruction = heads.get(address)
            if instruction is None:
                exits.append(address)
                continue
            visited.add(address)
            if address != head and address in groups:
                shared_entries.add(address)
            if instruction.mnemonic == "call":
                operand = instruction.operands[0]
                if operand.type == capstone.x86.X86_OP_IMM:
                    calls.append({"address": address, "target": operand.imm})
                else:
                    indirect_calls.append({"address": address, "operand": instruction.op_str})
            if instruction.group(capstone.CS_GRP_RET):
                continue
            if instruction.group(capstone.CS_GRP_JUMP):
                operand = instruction.operands[0]
                if operand.type == capstone.x86.X86_OP_IMM:
                    pending.append(operand.imm)
                elif address in nested_tables:
                    pending.extend(nested_tables[address]["entries"])
                else:
                    unresolved.append({"address": address, "operand": instruction.op_str})
                if instruction.mnemonic == "jmp":
                    continue
            pending.append(address + instruction.size)
        reached.update(visited)
        paths.append({
            "head": head, "opcodes": opcodes,
            "instruction_addresses": sorted(visited),
            "direct_calls": sorted(calls, key=lambda item: item["address"]),
            "indirect_calls": sorted(indirect_calls, key=lambda item: item["address"]),
            "other_case_entries_reached": sorted(shared_entries),
            "outside_successors": sorted(set(exits)),
            "unresolved_indirect_jumps": unresolved,
        })
    return {
        "opcode_base": opcode_base, "case_paths": paths,
        "nested_tables": [{"jump": jump, **nested} for jump, nested in sorted(nested_tables.items())],
        "instructions_reached_from_cases": len(reached),
        "instructions_not_reached_from_cases": sorted(set(heads) - reached),
        "case_path_limitations": "Normal direct control flow only; calls are not followed. "
        "Implicit exception edges are unknown. Shared tails can appear in multiple paths. "
        "Unselected table entries remain explicit. These are not source acceptance, "
        "function extents, disjoint byte coverage or partial exact results.",
    }


def audit_bytes(code: bytes, entry: int, table: list[int],
                listing: str | None = None, indices: bytes | None = None,
                opcode_base: int | None = None,
                nested_tables: dict[int, dict] | None = None) -> dict:
    import capstone

    if not code or not table:
        raise ValueError("body and independently supplied jump table must be nonempty")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, entry))
    if sum(i.size for i in instructions) != len(code):
        raise ValueError("decoder did not cover the complete supplied body")
    heads = {i.address: i for i in instructions}
    if any(address not in heads for address in table):
        raise ValueError("jump-table destination is outside the body or inside an instruction")
    if indices is not None and (not indices or max(indices) >= len(table)):
        raise ValueError("compressed dispatch index does not select a table entry")
    observed = set()
    if listing is not None:
        if "[truncated" in listing:
            raise ValueError("Ghidra listing is truncated")
        for address, encoded in re.findall(r"^0x([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+", listing, re.M):
            address = int(address, 16)
            if not entry <= address < entry + len(code):
                continue
            instruction = heads.get(address)
            if instruction is None or bytes.fromhex(encoded) != instruction.bytes:
                raise ValueError(f"Ghidra instruction disagrees with the locked PE at {address:08X}")
            observed.add(address)
        if not observed:
            raise ValueError("Ghidra listing contains no instruction from this body")
    calls, indirect, outside = [], [], []
    for instruction in instructions:
        if instruction.mnemonic == "call":
            if instruction.operands[0].type == capstone.x86.X86_OP_IMM:
                calls.append(instruction.operands[0].imm)
            else:
                indirect.append({"address": instruction.address, "operand": instruction.op_str})
        if instruction.group(capstone.CS_GRP_JUMP) and instruction.operands[0].type == capstone.x86.X86_OP_IMM:
            destination = instruction.operands[0].imm
            if destination not in heads:
                outside.append({"address": instruction.address, "destination": destination})
    missing = [] if listing is None else [
        {"address": i.address, "operation": f"{i.mnemonic} {i.op_str}".strip()}
        for i in instructions if i.address not in observed]
    result = {
        "entry": entry, "size": len(code), "body_sha256": hashlib.sha256(code).hexdigest(),
        "instructions": len(instructions), "returns": [i.address for i in instructions if i.group(capstone.CS_GRP_RET)],
        "ghidra_listed_heads": len(observed) if listing is not None else None,
        "ghidra_omitted_heads": missing, "outside_direct_branches": outside,
        "direct_calls": len(calls), "distinct_direct_dependencies": sorted(set(calls)),
        "indirect_calls": indirect, "table_entries": len(table),
        "distinct_case_heads": len(set(table)), "table": table,
        "index_entries": len(indices) if indices is not None else None,
        "exact_claim": False, "source_accepted": False,
    }
    if opcode_base is not None:
        result.update(catalog_case_paths(instructions, table, indices, opcode_base, nested_tables))
    elif nested_tables:
        raise ValueError("nested tables require an opcode base and case-path audit")
    return result


def address_count(value: str) -> tuple[int, int]:
    try:
        address, count = (int(part, 0) for part in value.split(":"))
    except ValueError as exc:
        raise argparse.ArgumentTypeError("expected ADDRESS:COUNT") from exc
    if address < 0 or count <= 0:
        raise argparse.ArgumentTypeError("address must be nonnegative and count positive")
    return address, count


def nested_table_spec(value: str) -> tuple[int, int, int]:
    try:
        jump, address, count = (int(part, 0) for part in value.split(":"))
    except ValueError as exc:
        raise argparse.ArgumentTypeError("expected JUMP_ADDRESS:TABLE_ADDRESS:COUNT") from exc
    if min(jump, address) < 0 or count <= 0:
        raise argparse.ArgumentTypeError("invalid nested table address/count")
    return jump, address, count


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--entry", type=lambda v: int(v, 0), required=True)
    parser.add_argument("--size", type=lambda v: int(v, 0), required=True)
    parser.add_argument("--jump-table", type=address_count, required=True)
    parser.add_argument("--index-table", type=address_count)
    parser.add_argument("--opcode-base", type=lambda v: int(v, 0),
                        help="expand opcode selections and normal reachable case paths")
    parser.add_argument("--nested-table", type=nested_table_spec, action="append", default=[],
                        help="independently reviewed JUMP_ADDRESS:TABLE_ADDRESS:COUNT; repeatable")
    parser.add_argument("--ghidra-export", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    output = args.output.resolve()
    if not output.is_relative_to((ROOT / ".analysis").resolve()):
        raise ValueError("raw dispatcher reports must remain below .analysis/")
    if args.entry < 0 or args.size <= 0:
        raise ValueError("invalid body interval")
    spec = importlib.util.spec_from_file_location("dispatcher_pe", ROOT / "scripts/compare-coff-function.py")
    oracle = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(oracle)
    pe = oracle.verified_target()
    code = oracle.pe_bytes_at(pe, args.entry, args.size)
    table_address, count = args.jump_table
    raw_table = oracle.pe_bytes_at(pe, table_address, count * 4)
    table = list(struct.unpack(f"<{count}I", raw_table))
    indices = None
    if args.index_table:
        index_address, index_count = args.index_table
        indices = oracle.pe_bytes_at(pe, index_address, index_count)
    nested_tables = {}
    for jump, address, count in args.nested_table:
        if jump in nested_tables:
            raise ValueError("duplicate nested table JMP binding")
        raw = oracle.pe_bytes_at(pe, address, count * 4)
        nested_tables[jump] = {"address": address,
                               "entries": list(struct.unpack(f"<{count}I", raw)),
                               "sha256": hashlib.sha256(raw).hexdigest()}
    result = audit_bytes(code, args.entry, table, args.ghidra_export.read_text(),
                         indices, args.opcode_base, nested_tables)
    result.update(target_sha256=hashlib.sha256(pe).hexdigest(),
                  table_address=table_address, table_sha256=hashlib.sha256(raw_table).hexdigest())
    if indices is not None:
        result.update(index_address=index_address, index_sha256=hashlib.sha256(indices).hexdigest())
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, indent=2) + "\n")
    print(f"{args.entry:08X}: {len(code)} complete bytes, {result['instructions']} instructions, "
          f"{len(table)} table entries, {result['distinct_case_heads']} distinct case heads; "
          f"Ghidra omitted {len(result['ghidra_omitted_heads'])} heads; exact not claimed")


if __name__ == "__main__":
    main()
