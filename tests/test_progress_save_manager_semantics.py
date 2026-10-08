"""Real complete SaveManager ownership with explicit pending file boundaries."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ProgressSaveManagerTests(unittest.TestCase):
    def test_owned_lifecycle_merge_and_buffer_release(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "save-manager"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-Isrc", "-pthread",
                "tests/progress_save_manager_semantics.cpp", "src/ProgressSaveManager.cpp",
                "src/ProgressStorage.cpp", "src/ProgressProfile.cpp", "src/ProgressRecords.cpp",
                "src/Worker.cpp", "src/LockRegistry.cpp", "src/DiagnosticAllocator.cpp",
                "src/DebugMemoryResource.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)


if __name__ == "__main__":
    unittest.main()
