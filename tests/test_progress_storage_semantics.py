"""Complete dirty Snapshot hierarchy, preserved names and live record aliases."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ProgressStorageTests(unittest.TestCase):
    def test_complete_snapshot_hierarchy(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            for standard in ("c++17", "c++20"):
                with self.subTest(standard=standard):
                    output = Path(directory) / standard
                    subprocess.run([
                        compiler, f"-std={standard}", "-O2", "-Wall", "-Wextra", "-Werror",
                        "-fsanitize=undefined", "-Isrc", "tests/progress_storage_semantics.cpp",
                        "src/ProgressStorage.cpp", "src/ProgressProfile.cpp",
                        "src/ProgressRecords.cpp", "-o", str(output),
                    ], cwd=ROOT, check=True)
                    subprocess.run([str(output)], cwd=ROOT, check=True, timeout=15)
