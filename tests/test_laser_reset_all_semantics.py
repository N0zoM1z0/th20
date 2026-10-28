"""Focused actual LaserController reset traversal, including iterator mutation/EH."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCES = ["LaserParameters", "TaskInfoConstruction", "BulletValues",
           "Timer", "ClockScalar", "Vector3"]

class LaserResetAllTests(unittest.TestCase):
    def test_real_laser_owner_and_observer(self):
        compilers = [path for name in ("g++-13", "clang++-18")
                     if (path := shutil.which(name))]
        self.assertTrue(compilers)
        for compiler in compilers:
            with self.subTest(compiler=compiler), tempfile.TemporaryDirectory(prefix="th20-laser539-") as temp:
                binary = Path(temp) / "laser539"
                subprocess.run([
                    compiler, "-std=c++20", "-O2", "-g", "-Wall", "-Wextra", "-Werror",
                    "-fsanitize=address,undefined", "-fno-sanitize-recover=all",
                    "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections",
                    "-pthread", "-Isrc", "tests/laser_reset_all_semantics.cpp",
                    *(f"src/{name}.cpp" for name in SOURCES), "-o", str(binary),
                ], cwd=ROOT, check=True, timeout=100)
                subprocess.run([str(binary)], cwd=ROOT, check=True, timeout=35)

if __name__ == "__main__":
    unittest.main()
