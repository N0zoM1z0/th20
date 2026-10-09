"""Real Card construction, time encoding and Context publication protocol."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class CardTests(unittest.TestCase):
    def test_card_construction_and_time_state(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        sources = ["Card", "TaskInfoConstruction", "TaskInfo", "FunctionChain",
                   "Timer", "ClockScalar", "Vector3", "AnimationHandle",
                   "EclDiagnostic", "Session", "Context", "PlayerRecord"]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "card"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-ffunction-sections", "-fdata-sections",
                "-Wl,--gc-sections", "-Isrc", "tests/card_semantics.cpp",
                *(f"src/{name}.cpp" for name in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
