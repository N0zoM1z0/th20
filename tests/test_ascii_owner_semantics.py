"""Actual AsciiInf storage, publication, shared resources and noexcept boundary."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class AsciiOwnerTests(unittest.TestCase):
    def test_construction_and_shared_resource(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "ascii-owner"
            sources = [
                "TextLine", "TaskInfoConstruction", "Worker", "Rectangle",
                "Animation", "AnimationFile", "AnimationHandle", "AnimationCallback",
                "AnmVariables", "Matrix4", "Interpolation", "Easing", "Timer",
                "ClockScalar", "Angle", "ScalarMath", "Vector3", "Vector2",
                "MotionMath", "IntegerTriple", "FogValue", "CollisionGeometry",
                "DiagnosticAllocator", "DebugMemoryResource", "LockRegistry",
            ]
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-fno-sanitize-recover=all",
                "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections",
                "-pthread", "-Isrc", "tests/ascii_owner_semantics.cpp",
                *(f"src/{name}.cpp" for name in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)
            terminated = subprocess.run([str(output), "terminate"], cwd=ROOT, timeout=30)
            self.assertEqual(terminated.returncode, 42)
