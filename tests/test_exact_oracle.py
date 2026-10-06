"""Synthetic fixtures exercise strict replay and refusal paths; no game bytes."""
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import project


def load_script(name):
    path = Path(__file__).resolve().parents[1] / "scripts" / name
    spec = importlib.util.spec_from_file_location(name.replace("-", "_"), path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


oracle = load_script("compare-coff-function.py")


def coff(code, relocations):
    names = [b"_probe", b"_callee", b"_global"]
    raw_offset = 60
    reloc_offset = raw_offset + len(code)
    symbol_offset = reloc_offset + len(relocations) * 10
    header = struct.pack("<HHIIIHH", 0x14c, 1, 0, symbol_offset, len(names), 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), raw_offset,
                          reloc_offset, 0, len(relocations), 0, 0x60000020)
    symbols = b"".join(struct.pack("<8sIhHBB", name, 0, 1 if i == 0 else 0,
                                   0x20 if i < 2 else 0, 2, 0) for i, name in enumerate(names))
    records = b"".join(struct.pack("<IIH", *row) for row in relocations)
    return header + section + code + records + symbols + struct.pack("<I", 4)


def pe(code):
    result = bytearray(0x200 + len(code))
    struct.pack_into("<I", result, 0x3c, 0x80)
    result[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<HH", result, 0x84, 0x14c, 1)
    struct.pack_into("<H", result, 0x94, 224)
    struct.pack_into("<I", result, 0x98 + 28, 0x400000)
    struct.pack_into("<8sIIII", result, 0x98 + 224, b".text", len(code), 0x1000, len(code), 0x200)
    result[0x200:] = code
    return bytes(result)


class ExactOracleTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / "build").mkdir()
        self.object = self.root / "build/probe.obj"
        self.code = b"\xe8\x00\x00\x00\x00\xa1\x04\x00\x00\x00\xc3"
        self.object.write_bytes(coff(self.code, [(1, 1, 0x14), (6, 2, 6)]))
        target = bytearray(self.code)
        struct.pack_into("<I", target, 1, 0x401100 - 0x401005)
        struct.pack_into("<I", target, 6, 0x402004)
        self.target = pe(target)
        self.unit = {"source": "probe.cpp", "object": "build/probe.obj", "profile": ["/O2"],
                     "symbol": "_probe", "functions": ["probe"], "size": 11,
                     "target_address": 0x401000,
                     "relocations": [{"offset": 1, "type": "REL32", "symbol": "_callee", "target": 0x401100},
                                     {"offset": 6, "type": "DIR32", "symbol": "_global", "target": 0x402000}]}
        self.manifest = self.root / "units.toml"
        self._write_unit()

    def _write_unit(self):
        # JSON strings are valid TOML quoted strings for these fixture values.
        text = 'target_sha256 = "fixture"\n[units.probe]\n'
        for key, value in self.unit.items():
            if key == "relocations":
                continue
            text += f"{key} = {json.dumps(value)}\n"
        for row in self.unit["relocations"]:
            text += "[[units.probe.relocations]]\n"
            text += "".join(f"{key} = {json.dumps(value)}\n" for key, value in row.items())
        self.manifest.write_text(text)

    def compare(self):
        receipt = {"object_sha256": "fixture-object", "compiler_version": "fixture", "target_sha256": "fixture"}
        with patch.object(oracle, "ROOT", self.root), patch.object(oracle, "UNITS_MANIFEST", self.manifest), \
             patch.object(oracle, "verified_target", return_value=self.target), \
             patch.object(oracle, "verify_build_receipt", return_value=receipt), \
             patch.object(oracle, "load_manifest", return_value={"target": {"sha256": "fixture"}}):
            return oracle.compare_unit("probe")

    def test_full_rel32_and_dir32_replay(self):
        report = self.compare()
        self.assertEqual(report["result"], "exact")
        self.assertEqual(report["matched_compared_bytes"], 11)

    def test_wrong_relocation_destination_is_a_mismatch(self):
        self.unit["relocations"][0]["target"] += 1
        self._write_unit()
        self.assertEqual(self.compare()["result"], "mismatch")

    def test_missing_manifest_relocation_is_rejected(self):
        self.unit["relocations"].pop()
        self._write_unit()
        with self.assertRaisesRegex(ValueError, "relocations differ"):
            self.compare()

    def test_prefix_comparison_is_rejected(self):
        self.unit["size"] = 5
        self._write_unit()
        with self.assertRaisesRegex(ValueError, "complete COFF contribution"):
            self.compare()

    def test_nonrelocation_byte_difference_is_rejected(self):
        data = bytearray(self.target)
        data[-1] ^= 1
        self.target = bytes(data)
        self.assertEqual(self.compare()["result"], "mismatch")

    def test_relocation_symbol_identity_cannot_be_ignored(self):
        self.unit["relocations"][0]["symbol"] = "_other"
        self._write_unit()
        with self.assertRaisesRegex(ValueError, "relocations differ"):
            self.compare()

    def test_same_manifest_with_a_different_target_hash_is_rejected(self):
        self.manifest.write_text(self.manifest.read_text().replace('"fixture"', '"wrong-target"'))
        with self.assertRaisesRegex(ValueError, "different executable"):
            self.compare()

    def test_ordinary_coff_machine_must_be_i386(self):
        raw = bytearray(self.object.read_bytes())
        struct.pack_into("<H", raw, 0, 0x8664)
        self.object.write_bytes(raw)
        with self.assertRaisesRegex(ValueError, "i386"):
            self.compare()


class ReceiptTests(unittest.TestCase):
    def test_stale_source_object_profile_and_header_are_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "build").mkdir()
            (root / "src").mkdir()
            source = root / "src/probe.cpp"
            source.write_text("unsigned probe() { return 7; }")
            header = root / "shared.h"
            header.write_text("// fixture header\n")
            obj = root / "build/probe.obj"
            obj.write_bytes(b"fixture object")
            unit = {"source": "src/probe.cpp", "object": "build/probe.obj", "profile": ["/O2"]}
            lock = {"files": {"bin/HostX64/x86/cl.exe": "compiler"}}
            with patch.object(project, "ROOT", root), \
                 patch.object(project, "attest_compiler", return_value=(lock, root)), \
                 patch.object(project, "load_manifest", return_value={"target": {"sha256": "target"}}):
                receipt = {"object_sha256": project.digest(obj), "inputs": project.source_fingerprint(source),
                           "profile": ["/O2"], "compiler_sha256": "compiler", "target_sha256": "target",
                           "headers": {str(header): project.digest(header)}}
                receipt_path = obj.with_suffix(".receipt.json")
                receipt_path.write_text(json.dumps(receipt))
                project.verify_build_receipt(unit)
                for key in ("object_sha256", "inputs", "profile", "compiler_sha256", "target_sha256"):
                    broken = dict(receipt, **{key: "changed"})
                    receipt_path.write_text(json.dumps(broken))
                    with self.assertRaisesRegex(ValueError, "stale or incompatible"):
                        project.verify_build_receipt(unit)
                receipt_path.write_text(json.dumps(receipt))
                header.write_text("// changed header\n")
                with self.assertRaisesRegex(ValueError, "included header changed"):
                    project.verify_build_receipt(unit)


if __name__ == "__main__":
    unittest.main()
