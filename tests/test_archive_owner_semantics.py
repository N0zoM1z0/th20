"""Actual archive/resource, File, C-heap and cipher/LZSS pipeline with OS boundaries."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]

class ArchiveOwnerTests(unittest.TestCase):
    def test_real_catalog_members_resource_modes_and_ownership(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        sources = ("ArchiveOwner", "PbgFile", "GameResourceIo", "ArchiveCrypt", "ArchiveLzss",
                   "DiagnosticAllocator", "DebugMemoryResource", "LockRegistry", "EclDiagnostic")
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "archive-owner"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-fno-sanitize-recover=all", "-Isrc", "-pthread",
                "-Wl,--wrap=malloc", "-Wl,--wrap=free", "tests/archive_owner_semantics.cpp",
                *[f"src/{name}.cpp" for name in sources], "-o", str(output)], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)

if __name__ == "__main__":
    unittest.main()
