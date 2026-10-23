"""Complete Enemy defeat with actual owner storage and explicit native interfaces."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EnemyDefeatTests(unittest.TestCase):
    def test_complete_defeat_protocol(self):
        compiler = next((p for n in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        sources = [
            "Enemy", "EnemySpawnApplication", "EnemyData", "TaskInfoConstruction",
            "EnemyState", "EnemyMovement", "EnemyCounters", "EnemySpawn",
            "EnemyHealth", "EnemyPattern", "Context", "Graphics", "ConfigurationValue",
            "Configuration", "AnimationFile", "Animation", "AnimationCallback", "AnimationHandle",
            "AnmVariables", "Matrix4", "Motion", "MotionConfiguration", "MotionUpdates", "MotionMath",
            "Vector2", "Vector3", "Angle", "Interpolation", "IntegerTriple", "FogValue", "Easing",
            "Timer", "ClockScalar", "ScalarMath", "Identifier32", "ScriptStack", "BulletValues",
            "ShotMetadata", "CollisionGeometry", "GeometryMetrics", "Worker", "LockRegistry",
            "DiagnosticAllocator", "DebugMemoryResource", "GameRandom", "GameRandomStream",
            "GameRandomAngle", "MeshInterfaces", "Player", "PlayerStorage", "Rectangle",
            "EclDiagnostic", "DamageQueryProtocol", "Session", "PlayerRecord", "Card",
            "EnemySpawning", "WeaponStoneInfo", "OverlayCounter", "EffectParameters",
            "ItemLifecycleAccess", "SoundEffects", "EclSelection", "EclLoaderBase",
        ]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "enemy-defeat"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-fno-sanitize-recover=all", "-ffunction-sections",
                "-fdata-sections", "-Wl,--gc-sections", "-pthread", "-Isrc",
                "tests/enemy_defeat_semantics.cpp", *(f"src/{n}.cpp" for n in sources),
                "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)
