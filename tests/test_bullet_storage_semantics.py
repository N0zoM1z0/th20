"""Actual Bullet pool, shared metadata release and Context routing protocol."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class BulletStorageTests(unittest.TestCase):
    def test_complete_bullet_storage_and_lifetime(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        sources = ["Bullet", "BulletController", "BulletValues", "ShotMetadata",
                   "TaskInfoConstruction", "TaskInfo", "FunctionChain", "Timer",
                   "ClockScalar", "Vector2", "Vector3", "Angle", "AnimationHandle",
                   "Interpolation", "Session", "Context", "PlayerRecord", "EclDiagnostic"]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "bullet-storage"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-ffunction-sections", "-Wl,--gc-sections",
                "-Isrc", "tests/bullet_storage_semantics.cpp",
                *(f"src/{name}.cpp" for name in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
