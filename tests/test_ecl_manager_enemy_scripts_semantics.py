"""Actual VM/Manager/Enemy script pipeline with explicit unresolved boundaries."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EclManagerEnemyScriptsTests(unittest.TestCase):
    def test_actual_vm_and_script_pipeline(self):
        compiler = next((p for n in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        sources = [
            "EclManagerTick", "EclManagerAsync", "EclCallSetup", "EclRuntimeCall",
            "EclDiagnostic", "EnemyScriptAdvance", "TimerStep", "EclRuntimeTick",
            "EclArguments", "EclRuntimeLifetime", "EclSelection", "EclLoaderBase",
            "Enemy", "EnemyState", "EnemyMovement", "EnemyCounters", "EnemySpawn",
            "EnemyHealth", "EnemyPattern", "Motion", "MotionConfiguration", "MotionUpdates",
            "MotionMath", "Vector2", "Vector3", "Angle", "Interpolation", "Easing",
            "Timer", "ClockScalar", "ScalarMath", "Identifier32", "ScriptStack",
            "ScriptStackCopy", "AnimationHandle", "IntegerTriple", "FogValue", "Color3",
            "BulletValues", "ShotMetadata", "CollisionGeometry", "GameRandom",
            "GameRandomAngle", "GameRandomStream", "LockRegistry", "DiagnosticAllocator", "DebugMemoryResource",
        ]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "ecl-manager-enemy-scripts"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-Wno-sign-compare", "-fno-strict-aliasing", "-fsanitize=undefined",
                "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections", "-pthread",
                "-Isrc", "tests/ecl_manager_enemy_scripts_semantics.cpp",
                *(f"src/{name}.cpp" for name in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=15)
