"""Actual complete HUD owner construction and script-facing state operations."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class FrontOwnerTests(unittest.TestCase):
    def test_storage_publication_and_gauges(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "front-owner"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-fno-sanitize-recover=all",
                "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections",
                "-pthread", "-Isrc", "tests/front_owner_semantics.cpp",
                "src/HudGauge.cpp", "src/TaskInfoConstruction.cpp",
                "src/AnimationHandle.cpp", "src/Timer.cpp", "src/ClockScalar.cpp",
                "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)
