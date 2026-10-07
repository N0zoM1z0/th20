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


class ScriptIndexTests(unittest.TestCase):
    def test_python_nested_decorated_function_and_lambda_keep_original_bytes(self):
        source = ("# Unicode evidence: 錦\n@decorate\ndef outer():\n"
                  "    def inner():\n        return lambda x: x + 1\n"
                  "    return inner()\nouter()\n").encode()
        rows, file = indexer.script_inventory("tools/sample.py", source)
        self.assertEqual([r["name"] for r in rows], ["<module>", "outer", "inner", "<lambda>"])
        self.assertFalse(file["parse_errors"])
        self.assertEqual(rows[0]["body_sha256"], hashlib.sha256(source).hexdigest())
        self.assertEqual(rows[1]["start_line"], 2)
        self.assertEqual(rows[1]["body_sha256"], hashlib.sha256(b"\n".join(source.splitlines()[1:6])).hexdigest())
        self.assertEqual(rows[2]["body_sha256"], hashlib.sha256(b"def inner():\n        return lambda x: x + 1").hexdigest())
        self.assertEqual(rows[3]["body_sha256"], hashlib.sha256(b"lambda x: x + 1").hexdigest())
        self.assertTrue(all(r["file_sha256"] == hashlib.sha256(source).hexdigest() for r in rows))

    def test_top_level_python_and_powershell_are_not_silently_omitted(self):
        rows, file = indexer.script_inventory("tools/read.py", b"value = read_target()\n")
        self.assertEqual(len(rows), 1)
        self.assertFalse(file["parse_errors"])
        rows, file = indexer.script_inventory("tools/build.ps1", b"function build { invoke-compiler }\nbuild\n")
        self.assertEqual(len(rows), 1)
        self.assertEqual(file["parse_errors"][0]["node_type"], "unsupported_powershell_function_inventory")


@unittest.skipUnless(importlib.util.find_spec("tree_sitter_cpp"), "optional pinned reference parser")
class ReferenceIndexTests(unittest.TestCase):
    def test_naked_invoker_and_line_asm_retain_original_bytes_and_gaps(self):
        path = "incremental/native_bridge/abi_check.cpp"
        first = (b"__declspec(naked) void __cdecl invoke_probe() {\r\n"
                 b"    __asm {\r\n        xor eax, eax\r\n"
                 b"    finish:\r\n        ret\r\n    }\r\n}")
        second = (b"void controls() {\r\n    unsigned short saved;\r\n"
                  b"    __asm fnstcw saved\r\n}")
        source = first + b"\r\n" + second + b"\r\n"
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            file = root / path
            file.parent.mkdir(parents=True)
            file.write_bytes(source)
            rows, files = indexer.inventory(root, [path])
        self.assertEqual([row["name"] for row in rows], ["invoke_probe", "controls"])
        self.assertEqual(rows[0]["body_sha256"], hashlib.sha256(first).hexdigest())
        self.assertEqual(rows[1]["body_sha256"], hashlib.sha256(second).hexdigest())
        self.assertTrue(files[0]["parse_errors"])
        self.assertTrue(all(row["file_sha256"] == hashlib.sha256(source).hexdigest()
                            for row in rows))

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
