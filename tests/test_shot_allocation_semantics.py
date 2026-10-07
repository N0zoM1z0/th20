"""Actual locked raw allocation and shared payload/control-block lifetimes."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ShotAllocationTests(unittest.TestCase):
    def test_locking_copy_move_and_weak_lifetime(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "shot-allocation"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-pthread", "-fsanitize=undefined", "-Isrc",
                "tests/shot_allocation_semantics.cpp", "src/ShotMetadata.cpp",
                "src/LockRegistry.cpp", "src/BulletValues.cpp", "src/Vector3.cpp",
                "src/Timer.cpp", "src/ClockScalar.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
