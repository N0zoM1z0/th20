"""Actual File/IFile production protocol with narrow OS/CRT boundary fixtures."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]

class PbgFileTests(unittest.TestCase):
    def test_real_file_modes_io_paths_and_lifetime(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            for level in ("-O0", "-O2"):
                output = Path(directory) / ("pbg-file-" + level[1:])
                subprocess.run([compiler, "-std=c++20", level, "-Wall", "-Wextra", "-Werror",
                    "-fsanitize=undefined", "-fno-sanitize-recover=all", "-Isrc",
                    "tests/pbg_file_semantics.cpp", "src/PbgFile.cpp", "-o", str(output)],
                    cwd=ROOT, check=True)
                subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)

if __name__ == "__main__":
    unittest.main()
