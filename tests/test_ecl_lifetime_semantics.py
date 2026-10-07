"""Owned real Runtime/Manager lifecycle and async scalar disposal checks."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EclLifetimeTests(unittest.TestCase):
    def test_lifetime_and_async_disposal(self):
        compiler = next((p for n in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "ecl-lifetime"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-pthread", "-Isrc",
                "tests/ecl_lifetime_semantics.cpp", "src/EclRuntimeLifetime.cpp",
                "src/EclSelection.cpp", "src/ScriptStack.cpp",
                "src/ScriptStackCopy.cpp", "src/EclLoaderBase.cpp",
                "src/DiagnosticAllocator.cpp", "src/DebugMemoryResource.cpp",
                "src/LockRegistry.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=15)
