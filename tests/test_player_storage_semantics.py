"""Production Player storage construction and complete 256-slot list protocol."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class PlayerStorageTests(unittest.TestCase):
    def test_complete_storage_and_pool(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        sources = ["PlayerStorage", "Timer", "ClockScalar", "Vector2", "Vector3",
                   "Rectangle", "Identifier32", "AnimationHandle", "Motion", "Angle"]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "player-storage"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-ffunction-sections", "-Wl,--gc-sections",
                "-Isrc", "tests/player_storage_semantics.cpp",
                *(f"src/{name}.cpp" for name in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
