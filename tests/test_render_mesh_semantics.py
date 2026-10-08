"""Real mesh/State/Animation/Session owners and geometric pipeline."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]

class RenderMeshTests(unittest.TestCase):
    def test_actual_grid_strips_and_enemy_deformation(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        sources = ["RenderMesh", "EnemyMesh", "MeshInterfaces", "EnemyState", "EnemyMovement",
                   "EnemyCounters", "EnemyHealth", "EnemyPattern", "Animation", "AnimationHandle",
                   "AnmVariables", "Matrix4", "Motion", "MotionMath", "MotionConfiguration", "MotionUpdates",
                   "Vector2", "Vector3", "SpriteVertices", "Angle", "Interpolation", "IntegerTriple", "FogValue", "Easing",
                   "Timer", "ClockScalar", "ScalarMath", "Identifier32", "BulletValues", "ShotMetadata",
                   "CollisionGeometry", "Session", "Context", "PlayerRecord", "LockRegistry",
                   "DiagnosticAllocator", "DebugMemoryResource"]
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "render-mesh"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                            "-fsanitize=undefined,float-cast-overflow", "-ffunction-sections", "-fdata-sections",
                            "-Wl,--gc-sections", "-pthread", "-Isrc", "tests/render_mesh_semantics.cpp",
                            *(f"src/{name}.cpp" for name in sources), "-o", str(output)], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=15)
