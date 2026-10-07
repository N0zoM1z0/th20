"""Owned complete runtime resolution and tagged generic stack-copy checks."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EclArgumentsTests(unittest.TestCase):
    def test_runtime_and_stack_protocol(self):
        compiler = next((p for n in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "ecl-arguments"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fno-strict-aliasing", "-fsanitize=undefined", "-Isrc",
                "tests/ecl_arguments_semantics.cpp", "src/EclArguments.cpp",
                "src/ScriptStackCopy.cpp", "src/ScriptStack.cpp", "src/EclLoaderBase.cpp",
                "src/EclRuntimeLifetime.cpp", "src/LockRegistry.cpp", "-pthread",
                "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
