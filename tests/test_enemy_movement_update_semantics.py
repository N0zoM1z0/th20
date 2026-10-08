"""Whole Enemy movement and real graphics construction with bounded fixtures."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EnemyMovementUpdateTests(unittest.TestCase):
    def test_whole_update_and_owner_construction(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        sources = [
            "EnemyMovementUpdate", "Enemy", "EnemyData", "TaskInfoConstruction", "EnemyState", "EnemyMovement",
            "EnemyCounters", "EnemySpawn", "EnemyHealth", "EnemyPattern",
            "Context", "Graphics", "ConfigurationValue", "Configuration",
            "AnimationFile", "Animation", "AnimationHandle", "AnmVariables",
            "Matrix4", "Motion", "MotionConfiguration", "MotionUpdates", "MotionMath",
            "Vector2", "Vector3", "Angle", "Interpolation", "IntegerTriple",
            "FogValue", "Easing", "Timer", "ClockScalar", "ScalarMath",
            "Identifier32", "ScriptStack", "BulletValues", "ShotMetadata", "CollisionGeometry",
            "Worker", "LockRegistry", "DiagnosticAllocator", "DebugMemoryResource",
        ]
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "enemy-movement"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-pthread", "-Isrc",
                "tests/enemy_movement_update_semantics.cpp",
                *(f"src/{source}.cpp" for source in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
