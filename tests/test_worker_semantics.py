"""Owned real thread launch, replacement, detach, join and destructor behavior."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class WorkerSemanticsTests(unittest.TestCase):
    def test_owned_thread_lifecycle_and_shared_slot(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler, "public semantic checks require a C++20 compiler")
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "worker-semantics"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                            "-fsanitize=undefined", "-Isrc", "-pthread",
                            "tests/worker_semantics.cpp", "src/Worker.cpp", "src/LockRegistry.cpp",
                            "-o", str(output)], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)


if __name__ == "__main__":
    unittest.main()
