"""Owned ECL resources retain their allocator and borrowed-buffer lifetimes."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EclResourceLifetimeTests(unittest.TestCase):
    def test_allocator_capture_and_virtual_cleanup(self):
        compiler = next((path for name in ("g++-13", "clang++-18", "c++")
                         if (path := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "ecl-resource-lifetime"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-Isrc",
                "tests/ecl_resource_lifetime_semantics.cpp", "src/EclLoaderBase.cpp",
                "src/ScriptStack.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
