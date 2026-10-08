"""Complete encoder/cipher pipeline with independent token/permutation models."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ArchiveWriteTests(unittest.TestCase):
    def test_real_compression_encryption_and_failure(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "archive-write"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-Isrc", "-pthread",
                "tests/archive_write_semantics.cpp", "src/ArchiveCrypt.cpp",
                "src/ArchiveLzss.cpp", "src/ArchiveLzssEncode.cpp", "src/ArchiveLzssTree.cpp",
                "src/DiagnosticAllocator.cpp", "src/DebugMemoryResource.cpp",
                "src/LockRegistry.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)


if __name__ == "__main__":
    unittest.main()
