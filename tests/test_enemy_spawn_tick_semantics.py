"""Production Enemy spawn application and time-scale orchestration."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EnemySpawnTickTests(unittest.TestCase):
    def test_production_orchestration(self):
        compiler = next((p for n in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        names = [
            "EnemySpawnApplication", "EnemyTick", "Enemy", "EnemyState", "EnemyMovement",
            "EnemyCounters", "EnemySpawn", "EnemyHealth", "EnemyPattern", "Session", "Context",
            "PlayerRecord", "EclRuntimeLifetime", "Animation", "AnimationParameters",
            "AnimationHandle", "AnmVariables", "Matrix4", "Motion", "MotionConfiguration",
            "MotionUpdates", "MotionMath", "Vector2", "Vector3", "Angle", "Interpolation",
            "IntegerTriple", "FogValue", "Color3", "Easing", "Timer", "ClockScalar", "ScalarMath",
            "Identifier32", "ScriptStack", "BulletValues", "ShotMetadata", "CollisionGeometry",
            "LockRegistry", "DiagnosticAllocator", "DebugMemoryResource",
        ]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "enemy-spawn-tick"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-ffunction-sections", "-fdata-sections",
                "-Wl,--gc-sections", "-pthread", "-Isrc", "tests/enemy_spawn_tick_semantics.cpp",
                *(f"src/{name}.cpp" for name in names), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=15)
