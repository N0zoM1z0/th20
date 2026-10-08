"""Real whole parser/checksum/cipher/decoder/allocator and current-backup merge."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ProgressFileParseTests(unittest.TestCase):
    def test_real_record_pipeline(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "progress-file-parse"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-Isrc", "-pthread",
                "tests/progress_file_parse_semantics.cpp", "src/ProgressFileParse.cpp",
                "src/ProgressSaveManager.cpp", "src/ProgressStorage.cpp",
                "src/ProgressProfile.cpp", "src/ProgressRecords.cpp", "src/Worker.cpp",
                "src/ArchiveCrypt.cpp", "src/ArchiveLzss.cpp", "src/ArchiveLzssTree.cpp",
                "src/EclDiagnostic.cpp", "src/LockRegistry.cpp",
                "src/DiagnosticAllocator.cpp", "src/DebugMemoryResource.cpp",
                "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)


if __name__ == "__main__":
    unittest.main()
