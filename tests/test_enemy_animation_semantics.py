"""Whole Enemy animation dispatch, actual values and bounded host dependencies."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]


class EnemyAnimationTests(unittest.TestCase):
    def test_whole_animation_protocol(self):
        compiler = next((p for n in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        sources = [
            "EnemyAnimation", "EnemyScript", "EclCallSetup", "Enemy", "EnemyState", "EnemyMovement",
            "EnemyCounters", "EnemySpawn", "EnemyHealth", "EnemyPattern",
            "AnimationParameters", "Animation", "AnimationCallback", "AnimationHandle", "AnmVariables",
            "Color3", "Matrix4", "Motion", "MotionConfiguration", "MotionUpdates", "MotionMath",
            "Vector2", "Vector3", "Angle", "Interpolation", "IntegerTriple", "FogValue",
            "Easing", "Timer", "ClockScalar", "ScalarMath", "Identifier32", "ScriptStack",
            "BulletValues", "ShotMetadata", "CollisionGeometry", "LockRegistry",
            "DiagnosticAllocator", "DebugMemoryResource",
        ]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "enemy-animation"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-pthread", "-Isrc", "tests/enemy_animation_semantics.cpp",
                *(f"src/{name}.cpp" for name in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
