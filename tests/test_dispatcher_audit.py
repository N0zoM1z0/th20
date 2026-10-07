import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("dispatcher_audit", ROOT / "scripts/audit-dispatcher.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


@unittest.skipUnless(importlib.util.find_spec("capstone"), "optional pinned x86 decoder")
class DispatcherAuditTests(unittest.TestCase):
    # Synthetic x86 fixture: NOP; JNE entry; RET. No game bytes.
    code = bytes.fromhex("90 75 fd c3")
    listing = "0x00001000  90  NOP\n0x00001003  C3  RET\n"

    def test_complete_body_and_compressed_table_preserve_omissions(self):
        result = audit.audit_bytes(self.code, 0x1000, [0x1000, 0x1003], self.listing, bytes([1, 0, 1]))
        self.assertEqual(result["instructions"], 3)
        self.assertEqual(result["returns"], [0x1003])
        self.assertEqual(result["outside_direct_branches"], [])
        self.assertEqual(result["ghidra_omitted_heads"][0]["address"], 0x1001)
        self.assertFalse(result["exact_claim"])
        self.assertFalse(result["source_accepted"])

    def test_bad_boundaries_tables_and_listing_fail_closed(self):
        for code, table, listing, indices in [
            (bytes.fromhex("90 0f"), [0x1000], None, None),
            (self.code, [0x1002], None, None),
            (self.code, [0x1004], None, None),
            (self.code, [0x1000], None, bytes([1])),
            (self.code, [0x1000], self.listing + "[truncated after 2 instructions]", None),
            (self.code, [0x1000], "0x00001000 CC INT3\n", None),
            (self.code, [0x1000], "0x00001002 FD STD\n", None),
            (self.code, [0x1000], "function: no instructions\n", None),
        ]:
            with self.subTest(code=code, table=table, listing=listing, indices=indices):
                with self.assertRaises(ValueError):
                    audit.audit_bytes(code, 0x1000, table, listing, indices)

    def test_external_branch_is_reported_for_reconciliation(self):
        result = audit.audit_bytes(bytes.fromhex("eb 02 c3"), 0x1000, [0x1002])
        self.assertEqual(result["outside_direct_branches"], [{"address": 0x1000, "destination": 0x1004}])
        self.assertFalse(result["exact_claim"])

    def test_opcode_aliases_and_shared_tails_preserve_call_sites(self):
        # CMP; JE shared NOP; CALL external; JMP shared RET; NOP; RET.
        code = bytes.fromhex("83 f8 01 74 07 e8 f6 0f 00 00 eb 01 90 c3")
        result = audit.audit_bytes(code, 0x1000, [0x1000, 0x100c, 0x100d],
                                   indices=bytes([0, 0, 1, 2]), opcode_base=300)
        paths = {path["head"]: path for path in result["case_paths"]}
        self.assertEqual(paths[0x1000]["opcodes"], [300, 301])
        self.assertEqual(paths[0x100c]["opcodes"], [302])
        self.assertEqual(paths[0x100d]["opcodes"], [303])
        self.assertEqual(paths[0x1000]["direct_calls"], [{"address": 0x1005, "target": 0x2000}])
        self.assertEqual(paths[0x1000]["other_case_entries_reached"], [0x100c, 0x100d])
        self.assertEqual(paths[0x100c]["instruction_addresses"], [0x100c, 0x100d])
        self.assertEqual(result["instructions_not_reached_from_cases"], [])
        self.assertFalse(result["exact_claim"])
        self.assertFalse(result["source_accepted"])

    def test_unselected_entries_and_disconnected_instructions_are_retained(self):
        # JMP RET; two disconnected NOPs; RET. A table entry is unselected.
        code = bytes.fromhex("eb 02 90 90 c3")
        result = audit.audit_bytes(code, 0x1000, [0x1000, 0x1004],
                                   indices=bytes([0]), opcode_base=400)
        self.assertEqual(result["case_paths"][1]["opcodes"], [])
        self.assertEqual(result["instructions_not_reached_from_cases"], [0x1002, 0x1003])
        self.assertFalse(result["exact_claim"])

    def test_indirect_and_external_successors_stay_unresolved(self):
        result = audit.audit_bytes(bytes.fromhex("ff e0 c3"), 0x1000,
                                   [0x1000], opcode_base=500)
        self.assertEqual(result["case_paths"][0]["unresolved_indirect_jumps"],
                         [{"address": 0x1000, "operand": "eax"}])
        self.assertEqual(result["instructions_not_reached_from_cases"], [0x1002])
        outside = audit.audit_bytes(bytes.fromhex("eb 02 c3"), 0x1000,
                                    [0x1000], opcode_base=500)
        self.assertEqual(outside["case_paths"][0]["outside_successors"], [0x1004])
        with self.assertRaises(ValueError):
            audit.audit_bytes(self.code, 0x1000, [0x1000], opcode_base=-1)

    def test_nested_tables_require_the_actual_jump_operand_and_complete_heads(self):
        # JMP [EAX*4+0x3000]; NOP; RET. Explicit synthetic nested table.
        code = bytes.fromhex("ff 24 85 00 30 00 00 90 c3")
        nested = {0x1000: {"address": 0x3000, "entries": [0x1007, 0x1008]}}
        result = audit.audit_bytes(code, 0x1000, [0x1000], opcode_base=529,
                                   nested_tables=nested)
        self.assertEqual(result["case_paths"][0]["instruction_addresses"], [0x1000, 0x1007, 0x1008])
        self.assertEqual(result["case_paths"][0]["unresolved_indirect_jumps"], [])
        self.assertEqual(result["instructions_not_reached_from_cases"], [])
        for invalid in [
            {0x1000: {"address": 0x3004, "entries": [0x1007]}},
            {0x1000: {"address": 0x3000, "entries": [0x1001]}},
            {0x1000: {"address": 0x3000, "entries": []}},
            {0x1007: {"address": 0x3000, "entries": [0x1008]}},
        ]:
            with self.subTest(binding=invalid):
                with self.assertRaises(ValueError):
                    audit.audit_bytes(code, 0x1000, [0x1000], opcode_base=529,
                                      nested_tables=invalid)
        with self.assertRaises(ValueError):
            audit.audit_bytes(code, 0x1000, [0x1000], nested_tables=nested)
