"""Owned Enemy creation/reset/generation and ECL selection protocol."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EnemyCreationTests(unittest.TestCase):
    def test_creation_and_initialization(self):
        compiler = next((p for n in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        sources = [
            "EnemySpawning", "EnemyInitialization", "EclSelection", "EclLoaderBase", "Enemy",
            "EnemyState", "EnemyMovement", "EnemyCounters", "EnemySpawn",
            "EnemyHealth", "EnemyPattern", "Motion",
            "MotionConfiguration", "MotionUpdates", "MotionMath", "Vector2",
            "Vector3", "Angle", "Interpolation", "Easing", "Timer", "ClockScalar",
            "ScalarMath", "Identifier32", "ScriptStack", "AnimationHandle", "Context",
            "IntegerTriple", "FogValue", "Color3",
            "BulletValues", "ShotMetadata", "CollisionGeometry", "LockRegistry",
            "DiagnosticAllocator", "DebugMemoryResource",
        ]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "enemy-creation"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-pthread", "-Isrc", "tests/enemy_creation_semantics.cpp",
                *(f"src/{name}.cpp" for name in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
