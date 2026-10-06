"""Optional parser regression for a declaration swallowed as a function body."""
import hashlib
import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("reference_index", ROOT / "scripts/index-reference-functions.py")
indexer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(indexer)


@unittest.skipUnless(importlib.util.find_spec("tree_sitter_cpp"), "optional pinned reference parser")
class ReferenceIndexTests(unittest.TestCase):
    def test_inline_assembly_keeps_the_real_enclosing_function(self):
        path = "source_reconstruction/platform_services/cpu_compare.cpp"
        source = (b"double conversion(unsigned value) {\n"
                  b"    double result;\n"
                  b"    __asm { mov ecx, value }\n"
                  b"    __asm { call target }\n"
                  b"    __asm { movsd result, xmm0 }\n"
                  b"    return result;\n"
                  b"}\n")
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            file = root / path
            file.parent.mkdir(parents=True)
            file.write_bytes(source)
            rows, files = indexer.inventory(root, [path])
        self.assertEqual([row["name"] for row in rows], ["conversion"])
        self.assertFalse(files[0]["parse_errors"])
        self.assertEqual(rows[0]["start_line"], 1)
        self.assertEqual(rows[0]["end_line"], 7)
        self.assertEqual(rows[0]["body_sha256"], hashlib.sha256(source.rstrip(b"\n")).hexdigest())
        self.assertEqual(rows[0]["file_sha256"], hashlib.sha256(source).hexdigest())

    def test_forward_declaration_does_not_consume_following_class(self):
        path = "source_reconstruction/core_scheduler/cpu_compare.cpp"
        source = (b"int __cdecl callback(void*);\n"
                  b"struct World { World() {} int run() { return 1; } };\n"
                  b"int __cdecl callback(void*) { return 0; }\n")
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            file = root / path
            file.parent.mkdir(parents=True)
            file.write_bytes(source)
            rows, files = indexer.inventory(root, [path])
        self.assertEqual([row["name"] for row in rows], ["World", "run", "callback"])
        self.assertFalse(files[0]["parse_errors"])
        callback = rows[-1]
        self.assertEqual(callback["start_line"], 3)
        self.assertEqual(callback["body_sha256"], hashlib.sha256(source.splitlines()[2]).hexdigest())
        self.assertEqual(callback["file_sha256"], hashlib.sha256(source).hexdigest())


if __name__ == "__main__":
    unittest.main()
