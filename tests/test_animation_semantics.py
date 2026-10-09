"""Whole ANM construction/reset/scales and bounded resource-call protocol."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class AnimationSemanticsTests(unittest.TestCase):
    def test_owned_animation_lifetime_and_reset(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "animation"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-pthread", "-Isrc",
                "tests/animation_semantics.cpp", "src/Animation.cpp", "src/AnimationChildren.cpp",
                "src/AnimationHandle.cpp", "src/AnmVariables.cpp", "src/Matrix4.cpp",
                "src/Interpolation.cpp", "src/Easing.cpp", "src/Timer.cpp",
                "src/ClockScalar.cpp", "src/Angle.cpp", "src/ScalarMath.cpp",
                "src/Vector3.cpp", "src/Vector2.cpp", "src/MotionMath.cpp",
                "src/IntegerTriple.cpp", "src/FogValue.cpp", "src/CollisionGeometry.cpp",
                "src/DiagnosticAllocator.cpp", "src/DebugMemoryResource.cpp",
                "src/LockRegistry.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
            with self.assertRaises(subprocess.TimeoutExpired):
                subprocess.run([str(output), "nonreturning"], cwd=ROOT,
                               check=True, timeout=0.5)
