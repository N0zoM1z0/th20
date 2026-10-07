"""Owned archive scratch, persistent tokens, ring/tree and aligned allocation."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ArchiveCodecSemanticsTests(unittest.TestCase):
    def test_owned_codec_and_allocator_protocol(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler, "public semantic checks require a C++20 compiler")
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "archive-codec-semantics"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                            "-fsanitize=undefined", "-Isrc", "-pthread",
                            "tests/archive_codec_semantics.cpp", "src/ArchiveCrypt.cpp",
                            "src/ArchiveLzss.cpp", "src/ArchiveLzssTree.cpp",
                            "src/DiagnosticAllocator.cpp", "src/DebugMemoryResource.cpp",
                            "src/LockRegistry.cpp", "-o", str(output)], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)


if __name__ == "__main__":
    unittest.main()
