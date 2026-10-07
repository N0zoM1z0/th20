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
