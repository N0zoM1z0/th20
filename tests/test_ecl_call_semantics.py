"""Owned ECL invocation/frame tests with explicitly bounded dependencies."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EclCallSemanticsTests(unittest.TestCase):
    def test_frames_argument_conversion_and_failure(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "ecl-call"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fno-strict-aliasing", "-fsanitize=undefined", "-Isrc",
                "tests/ecl_call_semantics.cpp", "src/EclRuntimeCall.cpp",
                "src/EclDiagnostic.cpp", "src/ScriptStack.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True)
