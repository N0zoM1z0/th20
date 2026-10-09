"""Actual damage owner lifecycle and shared scheduler/allocator/region bodies."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class HitControllerTests(unittest.TestCase):
    def test_complete_pool_heap_lifecycle(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "hit-controller"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-ffunction-sections", "-fdata-sections",
                "-Wl,--gc-sections", "-ffp-contract=off", "-Isrc", "-pthread",
                "tests/hit_controller_semantics.cpp", "src/HitCtrlInf.cpp",
                "src/HitCtrlInfCreation.cpp", "src/DamageRegion.cpp", "src/DamageRegionLifetime.cpp",
                "src/FunctionChain.cpp", "src/FunctionChainAllocation.cpp", "src/FunctionChainController.cpp",
                "src/TaskInfo.cpp", "src/TaskInfoConstruction.cpp", "src/EclDiagnostic.cpp",
                "src/DiagnosticAllocator.cpp", "src/DebugMemoryResource.cpp", "src/LockRegistry.cpp",
                "src/Session.cpp", "src/Context.cpp", "src/PlayerRecord.cpp",
                "src/Motion.cpp", "src/MotionUpdates.cpp", "src/Timer.cpp", "src/ClockScalar.cpp",
                "src/Identifier32.cpp", "src/RectangleCollisions.cpp", "src/GeometryMetrics.cpp",
                "src/CollisionShapes.cpp", "src/CollisionGeometry.cpp", "src/Vector2.cpp", "src/Vector3.cpp",
                "src/MotionMath.cpp", "src/ScalarMath.cpp", "src/Angle.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)


if __name__ == "__main__":
    unittest.main()
