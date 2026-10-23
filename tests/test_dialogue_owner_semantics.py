"""Whole Dialogue construction with real owners and captured resource producers."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class DialogueOwnerTests(unittest.TestCase):
    def test_construction_callbacks_ready_and_unwind(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        sources = [
            "DialogueText", "DialogueFlags", "Cursor", "HudGauge", "TextLine",
            "BulletController", "Bullet", "BulletValues", "ShotMetadata", "LaserParameters",
            "Context", "Session", "EnemyControllerConstruction", "EnemySpawning",
            "TaskInfoConstruction", "Worker", "Rectangle", "Animation", "AnimationFile",
            "AnimationHandle", "AnimationCallback", "AnimationBinding", "MeshResourceAccess",
            "AnmVariables", "Matrix4", "Interpolation", "Easing", "Timer", "ClockScalar",
            "Angle", "ScalarMath", "Vector3", "Vector2", "MotionMath", "IntegerTriple",
            "FogValue", "CollisionGeometry", "DiagnosticAllocator", "DebugMemoryResource",
            "LockRegistry", "Motion", "MotionConfiguration", "MotionUpdates",
            "FunctionChain", "EnemyPattern", "EnemyState", "EnemyData",
            "EnemyInitialization", "PlayerRecord",
            "EnemyCounters",
        ]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "dialogue-owner"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-fno-sanitize-recover=all",
                "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections",
                "-pthread", "-Isrc", "tests/dialogue_owner_semantics.cpp",
                "tests/dialogue_owner_fixture.cpp", *(f"src/{name}.cpp" for name in sources),
                "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)
