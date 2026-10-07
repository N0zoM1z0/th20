"""Portable independent arithmetic and state-invariant tests, without game data."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class CoreSemanticsTests(unittest.TestCase):
    def test_arithmetic_sequences_and_timer_invariants(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler, "public semantic checks require a C++20 compiler")
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "core-semantics"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                            "-fsanitize=undefined", "-Isrc", "tests/core_semantics.cpp",
                            "src/Random.cpp", "src/Timer.cpp", "src/ClockScalar.cpp",
                            "src/FunctionChain.cpp", "src/LockRegistry.cpp", "src/TaskInfo.cpp",
                            "src/ArchiveCrypt.cpp",
                            "src/InputState.cpp",
                            "src/Configuration.cpp",
                            "src/GameRandom.cpp",
                            "src/WindowState.cpp",
                            "src/SceneResources.cpp", "tests/scene_resource_semantics.cpp",
                            "src/SoundEffects.cpp",
                            "src/AnimationHandle.cpp",
                            "src/Vector3.cpp",
                            "src/TrophyText.cpp",
                            "src/Cursor.cpp", "tests/cursor_semantics.cpp",
                            "src/PauseFlags.cpp",
                            "src/TitleFlags.cpp",
                            "src/ProgressRecords.cpp", "src/ReplayRecords.cpp",
                            "tests/replay_record_semantics.cpp",
                            "src/EffectParameters.cpp", "src/Interpolation.cpp",
                            "src/IntegerTriple.cpp", "src/FogValue.cpp",
                            "tests/fog_value_semantics.cpp",
                            "tests/effect_value_semantics.cpp",
                            "src/Vector2.cpp", "src/BulletValues.cpp",
                            "src/CollisionGeometry.cpp", "tests/bullet_value_semantics.cpp",
                            "src/BulletStyle.cpp",
                            "src/Angle.cpp", "src/Motion.cpp", "src/Rectangle.cpp",
                            "tests/motion_value_semantics.cpp",
                            "src/ScoreEntry.cpp", "src/HudGauge.cpp", "src/OverlayCounter.cpp",
                            "tests/display_value_semantics.cpp",
                            "src/DialogueFlags.cpp", "src/DialogueText.cpp",
                            "tests/dialogue_value_semantics.cpp",
                            "src/ScalarMath.cpp", "tests/scalar_math_semantics.cpp",
                            "src/ScriptStack.cpp", "src/EnemyCounters.cpp",
                            "tests/script_value_semantics.cpp",
                            "src/EnemySpawn.cpp", "src/EnemyMovement.cpp",
                            "tests/enemy_value_semantics.cpp",
                            "src/EnemyHealth.cpp", "src/EnemyPattern.cpp",
                            "tests/enemy_health_pattern_semantics.cpp",
                            "-pthread", "-o", str(output)],
                           cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True)
