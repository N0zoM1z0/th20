"""Actual complete query consumers with explicit original owner boundaries."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCES = ['ArchiveOwner', 'PbgFile', 'GameResourceIo', 'ArchiveCrypt', 'ArchiveLzss', 'DiagnosticAllocator', 'DebugMemoryResource', 'LockRegistry', 'EclDiagnostic', 'Animation', 'AnimationHandle', 'AnmVariables', 'Matrix4', 'Interpolation', 'Easing', 'Timer', 'ClockScalar', 'Angle', 'ScalarMath', 'Vector3', 'Vector2', 'MotionMath', 'IntegerTriple', 'FogValue', 'CollisionGeometry', 'PlayerStorage', 'Identifier32', 'Motion', 'TaskInfo', 'TaskInfoConstruction', 'FunctionChain', 'Rectangle', 'OverlayCounter', 'Context', 'PlayerRecord', 'Session', 'Player', 'ShotData', 'PlayerDamageCap', 'WeaponStoneInfo', 'Enemy', 'EnemyState', 'EnemyMovement', 'EnemyCounters', 'EnemySpawn', 'EnemyHealth', 'EnemyPattern', 'EnemyData', 'EnemyControllerConstruction', 'ScriptStack', 'MotionConfiguration', 'BulletValues', 'ShotMetadata', 'DamageRegion', 'EnemyInitialization', 'EclLoaderBase', 'DamageQueryProtocol']

class DamageQueryProtocolTests(unittest.TestCase):
    def test_search_score_and_enemy_protocol(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            binary = Path(directory) / "query-protocol"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-fno-sanitize-recover=all", "-Isrc",
                "-pthread", "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections",
                "-Wl,--wrap=malloc", "-Wl,--wrap=free",
                "tests/damage_query_protocol_semantics.cpp",
                *(f"src/{name}.cpp" for name in SOURCES), "-o", str(binary),
            ], cwd=ROOT, check=True)
            subprocess.run([str(binary)], cwd=ROOT, check=True, timeout=30)
