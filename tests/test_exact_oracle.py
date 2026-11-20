"""Synthetic fixtures exercise strict replay and refusal paths; no game bytes."""
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
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


def coff(code, relocations, local_target=None, *, symbol=b"_global", literal=b""):
    names = [b"_probe", b"_callee", symbol]
    raw_offset = 100 if literal else 60
    reloc_offset = raw_offset + len(code) + len(literal)
    symbol_offset = reloc_offset + len(relocations) * 10
    header = struct.pack("<HHIIIHH", 0x14c, 2 if literal else 1, 0,
                         symbol_offset, len(names), 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), raw_offset,
                          reloc_offset, 0, len(relocations), 0, 0x60000020)
    if literal:
        section += struct.pack("<8sIIIIIIHHI", b".rdata", 0, 0, len(literal),
                               raw_offset + len(code), 0, 0, 0, 0, 0x40000040)
    target_section = 2 if literal else int(local_target is not None)
    sections = (1, 0, target_section)
    symbols = b"".join(struct.pack("<8sIhHBB", name, (local_target or 0) if i == 2 else 0,
                                   sections[i], 0x20 if i < 2 else 0, 3 if i == 2 else 2, 0)
                       for i, name in enumerate(names))
    records = b"".join(struct.pack("<IIH", *row) for row in relocations)
    return header + section + code + literal + records + symbols + struct.pack("<I", 4)


def pe(code, highlow=(6,)):
    result = bytearray(0x200 + len(code))
    struct.pack_into("<I", result, 0x3c, 0x80)
    result[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<HH", result, 0x84, 0x14c, 2 if highlow else 1)
    struct.pack_into("<H", result, 0x94, 224)
    struct.pack_into("<I", result, 0x98 + 28, 0x400000)
    struct.pack_into("<8sIIII", result, 0x98 + 224, b".text", len(code), 0x1000, len(code), 0x200)
    result[0x200:] = code
    struct.pack_into("<I", result, 0x98 + 92, 16)
    if highlow:
        fields = [0x3000 | offset for offset in highlow]
        if len(fields) % 2:
            fields.append(0)
        length = 8 + 2 * len(fields)
        struct.pack_into("<II", result, 0x98 + 96 + 5 * 8, 0x3000, length)
        struct.pack_into("<8sIIII", result, 0x98 + 224 + 40, b".reloc", length,
                         0x3000, length, len(result))
        result.extend(struct.pack("<II", 0x1000, length))
        result.extend(struct.pack(f"<{len(fields)}H", *fields))
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

    def test_matching_bytes_cannot_hide_missing_pe_highlow(self):
        code = bytearray(self.code)
        struct.pack_into("<I", code, 6, 0x402004)
        self.object.write_bytes(coff(code, [(1, 1, 0x14)]))
        self.unit["relocations"].pop()
        self._write_unit()
        with self.assertRaisesRegex(ValueError, "PE HIGHLOW: missing=\\[6\\]"):
            self.compare()

    def test_dir32_without_target_highlow_is_rejected(self):
        self.target = pe(self.target[0x200 : 0x20B], highlow=())
        with self.assertRaisesRegex(ValueError, "PE HIGHLOW: .*extra=\\[6\\]"):
            self.compare()

    def test_same_section_symbol_has_to_resolve_to_the_anchor(self):
        self.unit["relocations"][1]["target"] = 0x401006
        self.unit["relocations"][1]["symbol"] = "$LN40"
        self._write_unit()
        code = bytearray(self.target[0x200 : 0x20B])
        struct.pack_into("<I", code, 6, 0x40100A)
        self.target = pe(code)
        relocations = [(1, 1, 0x14), (6, 2, 6)]
        self.object.write_bytes(coff(self.code, relocations, local_target=6, symbol=b"$LN41"))
        self.assertEqual(self.compare()["result"], "exact")
        self.object.write_bytes(coff(self.code, relocations, local_target=7, symbol=b"$LN41"))
        with self.assertRaisesRegex(ValueError, "section-local symbol disagrees"):
            self.compare()
        self.object.write_bytes(coff(self.code, relocations, symbol=b"$LN40"))
        with self.assertRaisesRegex(ValueError, "no same-section definition"):
            self.compare()

    def test_renumbered_literal_requires_matching_anchored_contents(self):
        self.unit["relocations"][1].update(target=0x40100B, symbol="$SG123")
        self._write_unit()
        code = bytearray(self.target[0x200 : 0x20B])
        struct.pack_into("<I", code, 6, 0x40100F)
        self.target = pe(code + b"sample\0")
        relocations = [(1, 1, 0x14), (6, 2, 6)]
        self.object.write_bytes(coff(self.code, relocations, symbol=b"$SG124", literal=b"sample\0"))
        self.assertEqual(self.compare()["result"], "exact")
        self.object.write_bytes(coff(self.code, relocations, symbol=b"$SG124", literal=b"sampLe\0"))
        with self.assertRaisesRegex(ValueError, "literal differs"):
            self.compare()
        self.object.write_bytes(coff(self.code, relocations, symbol=b"$SG123"))
        with self.assertRaisesRegex(ValueError, "no readable definition"):
            self.compare()

    def test_prefix_comparison_is_rejected(self):
        self.unit["size"] = 5
        self._write_unit()
        with self.assertRaisesRegex(ValueError, "complete COFF contribution"):
            self.compare()

    def test_nonrelocation_byte_difference_is_rejected(self):
        data = bytearray(self.target)
        data[0x20A] ^= 1
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


def compiler_command(source):
    return ["cl", "Z:" + str(source).replace("/", "\\"), "/Fo", "/Fd"]


class ReceiptTests(unittest.TestCase):
    def test_only_executable_inputs_and_include_shadowing_invalidate_the_receipt(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "build").mkdir()
            (root / "src").mkdir()
            source = root / "src/probe.cpp"
            other = root / "src/other.cpp"
            included = root / "src/included.cpp"
            header = root / "src/shared.hpp"
            other_header = root / "src/other.hpp"
            control = root / "src/control.json"
            for path in (source, other, included, header, other_header, control):
                path.write_text("// original fixture\n")
            obj = root / "build/probe.obj"
            obj.write_bytes(b"fixture object")
            unit = {"source": "src/probe.cpp", "object": "build/probe.obj", "profile": ["/Od"]}
            lock = {"files": {"bin/HostX64/x86/cl.exe": "compiler"}}
            with patch.object(project, "ROOT", root), \
                 patch.object(project, "attest_compiler", return_value=(lock, root)), \
                 patch.object(project, "load_manifest", return_value={"target": {"sha256": "target"}}):
                receipt = {"object_sha256": project.digest(obj), "inputs": project.source_fingerprint(source),
                           "profile": ["/Od"], "compiler_sha256": "compiler", "target_sha256": "target",
                           "command": compiler_command(source),
                           "headers": {str(included): project.digest(included),
                                       str(header): project.digest(header),
                                       str(control): project.digest(control)}}
                receipt_path = obj.with_suffix(".receipt.json")
                original_receipt = json.dumps(receipt)
                receipt_path.write_text(original_receipt)
                other.write_text("// unrelated implementation changed\n")
                other_header.write_text("// unrelated header changed\n")
                project.verify_build_receipt(unit)
                self.assertEqual(receipt_path.read_text(), original_receipt)
                for path in (source, included, header, control):
                    with self.subTest(changed=path.name):
                        path.write_text("// relevant input changed\n")
                        with self.assertRaisesRegex(ValueError, "cold-build the unit"):
                            project.verify_build_receipt(unit)
                        path.write_text("// original fixture\n")
                added = root / "src/new.cpp"
                added.write_text("// added file\n")
                other.unlink()
                project.verify_build_receipt(unit)
                shadow = root / "probes/Shared.hpp"
                shadow.parent.mkdir()
                shadow.write_text("// alternate include\n")
                with self.assertRaisesRegex(ValueError, "stale or incompatible"):
                    project.verify_build_receipt(unit)
                shadow.unlink()
                del receipt["headers"]
                receipt_path.write_text(json.dumps(receipt))
                with self.assertRaisesRegex(ValueError, "headers"):
                    project.verify_build_receipt(unit)

    def test_stale_source_object_profile_and_header_are_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "build").mkdir()
            (root / "src").mkdir()
            source = root / "src/probe.cpp"
            source.write_text("unsigned probe() { return 7; }")
            other = root / "src/other.cpp"
            other.write_text("unsigned other() { return 7; }")
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
                           "command": compiler_command(source),
                           "headers": {str(header): project.digest(header)}}
                receipt_path = obj.with_suffix(".receipt.json")
                receipt_path.write_text(json.dumps(receipt))
                project.verify_build_receipt(unit)
                with self.assertRaisesRegex(ValueError, "compiled source"):
                    project.verify_build_receipt(dict(unit, source="src/other.cpp"))
                for key in ("object_sha256", "inputs", "profile", "compiler_sha256", "target_sha256"):
                    broken = dict(receipt, **{key: "changed"})
                    receipt_path.write_text(json.dumps(broken))
                    with self.assertRaisesRegex(ValueError, "stale or incompatible"):
                        project.verify_build_receipt(unit)
                receipt_path.write_text(json.dumps(receipt))
                header.write_text("// changed header\n")
                with self.assertRaisesRegex(ValueError, "included header changed"):
                    project.verify_build_receipt(unit)


class ReplayCommandTests(unittest.TestCase):
    def setUp(self):
        self.replay = load_script("replay-exact-units.py")
        first = {"source": "src/first.cpp", "object": "build/first.obj", "profile": ["/Od"]}
        self.units = {"first": first, "alias": dict(first),
                      "second": {"source": "src/second.cpp", "object": "build/second.obj", "profile": ["/O2"]}}

    def run_replay(self, arguments):
        with patch.object(sys, "argv", ["replay-exact-units.py", *arguments]), \
             patch.object(self.replay, "load_manifest", return_value={"units": self.units}), \
             patch.object(self.replay.subprocess, "run") as run, \
             patch("builtins.print"):
            self.replay.main()
        return [call.args[0][1:] for call in run.call_args_list]

    def test_existing_objects_keep_strict_checks_without_compiling(self):
        for arguments, names in ((["--existing-objects"], list(self.units)),
                                 (["--existing-objects", "--source", "src/first.cpp"], ["first", "alias"])):
            with self.subTest(arguments=arguments):
                commands = self.run_replay(arguments)
                self.assertEqual(commands, [["scripts/build.py", "--check"],
                                           *[["scripts/compare-coff-function.py", "--unit", name] for name in names]])

    def test_default_still_cold_builds_each_object_once(self):
        commands = self.run_replay([])
        self.assertEqual([c for c in commands if c[:2] == ["scripts/build.py", "--unit"]],
                         [["scripts/build.py", "--unit", "first"], ["scripts/build.py", "--unit", "second"]])
        self.assertEqual([c[-1] for c in commands if c[0] == "scripts/compare-coff-function.py"], list(self.units))

    def test_existing_object_failure_stops_without_rebuilding(self):
        with patch.object(sys, "argv", ["replay-exact-units.py", "--existing-objects"]), \
             patch.object(self.replay, "load_manifest", return_value={"units": self.units}), \
             patch.object(self.replay.subprocess, "run", side_effect=[None, subprocess.CalledProcessError(1, "compare")]) as run:
            with self.assertRaises(subprocess.CalledProcessError):
                self.replay.main()
        self.assertEqual([call.args[0][1:] for call in run.call_args_list],
                         [["scripts/build.py", "--check"], ["scripts/compare-coff-function.py", "--unit", "first"]])

    def test_stale_listing_checks_each_provider_once(self):
        lock = {"files": {"bin/HostX64/x86/cl.exe": "compiler"}}
        with patch.object(self.replay, "attest_compiler", return_value=(lock, None)), \
             patch.object(self.replay, "load_manifest", return_value={"target": {"sha256": "target"}}), \
             patch.object(self.replay, "source_tree_paths", return_value=set()), \
             patch.object(self.replay, "verify_build_receipt", side_effect=[None, ValueError("stale")]) as verify:
            self.assertEqual(self.replay.stale_sources(self.units), ["src/second.cpp"])
        self.assertEqual(verify.call_count, 2)


class ManifestTests(unittest.TestCase):
    def test_comparison_extents_cannot_share_owned_bytes(self):
        tracking = load_script("validate-tracking.py")
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "probe.cpp").touch()
            unit = {"source": "probe.cpp", "object": "build/probe.obj", "profile": ["/Od"],
                    "functions": ["probe"], "symbol": "_probe", "target_address": 0x401000,
                    "size": 3, "compare_size": 4, "relocations": []}
            neighbor = dict(unit, target_address=0x401003, size=1, compare_size=1)
            manifest = {"schema_version": 1, "target_sha256": "target",
                        "units": {"probe": unit, "neighbor": neighbor}}
            inventory = {0x401000: {"size": "3"}, 0x401003: {"size": "1"}}
            (root / "match-units.toml").touch()
            with patch.object(tracking, "ROOT", root), patch.object(tracking, "CONFIG", root), \
                 patch.object(tracking.tomllib, "load", return_value=manifest):
                with self.assertRaisesRegex(ValueError, "comparison extents overlap"):
                    tracking.validate_match_manifest({"sha256": "target"}, inventory)
                unit["compare_size"] = 3
                self.assertEqual(tracking.validate_match_manifest({"sha256": "target"}, inventory),
                                 manifest["units"])


if __name__ == "__main__":
    unittest.main()
