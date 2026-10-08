"""Whole borrowed-buffer registration, mutation, recursive includes and failure."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EclLoaderBufferTests(unittest.TestCase):
    def test_owned_buffer_protocol(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "ecl-loader-buffer"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fno-strict-aliasing", "-fsanitize=undefined",
                "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections",
                "-Isrc", "tests/ecl_loader_buffer_semantics.cpp",
                "src/EclLoaderBuffer.cpp", "src/EclLoaderBase.cpp",
                "src/EclDiagnostic.cpp", "src/ScriptStack.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
