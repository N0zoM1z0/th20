"""Actual Game defaults, retained Configuration storage and state observations."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class GameControllerTests(unittest.TestCase):
    def test_game_construction_and_flags(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        sources = ["GameController", "TaskInfoConstruction", "TaskInfo",
                   "FunctionChain", "Timer", "ClockScalar", "Configuration",
                   "ConfigurationValue", "EclDiagnostic"]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "game-controller"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-Isrc", "tests/game_controller_semantics.cpp",
                *(f"src/{name}.cpp" for name in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
