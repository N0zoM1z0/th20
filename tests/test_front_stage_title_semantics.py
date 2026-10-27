"""Actual native FrontInf stage-title gate, real Graphics and Session owners."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCES = [
    "HudGauge", "Graphics", "Session", "PlayerRecord", "Context",
    "AnimationFile", "AnimationHandle", "TaskInfoConstruction", "Timer",
    "ClockScalar", "Configuration", "ConfigurationValue", "Worker",
    "LockRegistry", "Vector2", "Vector3", "Angle", "FogValue",
]


class FrontStageTitleTests(unittest.TestCase):
    def test_native_stage_title_owner_and_spawn_gate(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix="th20-stage-title-") as folder:
            binary = Path(folder) / "stage-title"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-fno-sanitize-recover=all",
                "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections",
                "-pthread", "-Isrc", "tests/front_stage_title_semantics.cpp",
                *(f"src/{source}.cpp" for source in SOURCES), "-o", str(binary),
            ], cwd=ROOT, check=True, timeout=100)
            subprocess.run([str(binary)], cwd=ROOT, check=True, timeout=35)
