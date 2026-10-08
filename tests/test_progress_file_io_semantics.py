"""Real complete save/load protocol; only startup/data, OS and CRT boundaries fixture."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ProgressFileIoTests(unittest.TestCase):
    def test_complete_file_protocol_and_native_short_write(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        sources = [
            "ProgressSaveManager", "ProgressFileLoad", "ProgressFileWrite", "ProgressFileParse",
            "ProgressInitialize", "ProgressIntegrity", "ProgressStorage", "ProgressProfile", "ProgressRecords",
            "GameFileIo", "DiagnosticLog", "GameRandom", "GameRandomStream", "Worker",
            "ArchiveCrypt", "ArchiveLzss", "ArchiveLzssEncode", "ArchiveLzssTree", "EclDiagnostic",
            "DiagnosticAllocator", "DebugMemoryResource", "LockRegistry",
            "GameResourceIo", "ArchiveOwner", "PbgFile",
        ]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "progress-file-io"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-Isrc", "-pthread", "-Wl,--wrap=malloc", "-Wl,--wrap=free",
                "tests/progress_file_io_semantics.cpp", *[f"src/{name}.cpp" for name in sources],
                "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)


if __name__ == "__main__":
    unittest.main()
