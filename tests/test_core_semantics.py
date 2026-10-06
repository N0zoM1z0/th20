"""Portable independent arithmetic and state-invariant tests, without game data."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class CoreSemanticsTests(unittest.TestCase):
    def test_arithmetic_sequences_and_timer_invariants(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler, "public semantic checks require a C++20 compiler")
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "core-semantics"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                            "-fsanitize=undefined", "-Isrc", "tests/core_semantics.cpp",
                            "src/Random.cpp", "src/Timer.cpp", "src/ClockScalar.cpp",
                            "src/FunctionChain.cpp", "-o", str(output)],
                           cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True)
