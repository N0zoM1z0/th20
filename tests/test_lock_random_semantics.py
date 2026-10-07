"""Real mutex ownership and deterministic stream state, without game data."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class LockRandomSemanticsTests(unittest.TestCase):
    def test_tracking_recursion_and_owned_random_stream(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler, "public semantic checks require a C++20 compiler")
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "lock-random-semantics"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                            "-fsanitize=undefined", "-Isrc", "-pthread",
                            "tests/lock_random_semantics.cpp", "src/LockRegistry.cpp",
                            "src/GameRandom.cpp", "src/GameRandomStream.cpp", "-o", str(output)],
                           cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True)


if __name__ == "__main__":
    unittest.main()
