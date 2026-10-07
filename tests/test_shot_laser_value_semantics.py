"""Real command owners, allocator-sensitive transfer and nonthrowing construction."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ShotLaserValueTests(unittest.TestCase):
    def test_lifetimes_and_allocator_sensitive_move(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "shot-laser-values"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-Isrc", "tests/shot_laser_value_semantics.cpp",
                "src/ShotMetadata.cpp", "src/LaserParameters.cpp", "src/BulletValues.cpp",
                "src/Vector3.cpp", "src/Timer.cpp", "src/ClockScalar.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
            failed = subprocess.run([str(output), "--reject-allocation"], cwd=ROOT, timeout=10)
            self.assertEqual(failed.returncode, 77)
