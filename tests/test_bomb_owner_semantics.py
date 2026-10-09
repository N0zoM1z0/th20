"""Actual Bomb lifecycle/dispatch with explicit unresolved gameplay/ANM bindings."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class BombOwnerTests(unittest.TestCase):
    def test_owned_lifecycle_and_dispatch(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "bomb-owner"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-ffunction-sections", "-fdata-sections",
                "-Isrc", "-pthread", "tests/bomb_owner_semantics.cpp",
                "src/Bomb.cpp", "src/BombCreation.cpp", "src/Context.cpp", "src/Session.cpp",
                "src/PlayerRecord.cpp", "src/AnimationHandle.cpp", "src/Interpolation.cpp",
                "src/FunctionChain.cpp", "src/FunctionChainAllocation.cpp", "src/FunctionChainController.cpp",
                "src/TaskInfo.cpp", "src/TaskInfoConstruction.cpp", "src/EclDiagnostic.cpp",
                "src/DiagnosticAllocator.cpp", "src/DebugMemoryResource.cpp", "src/LockRegistry.cpp",
                "src/Motion.cpp", "src/Timer.cpp", "src/ClockScalar.cpp", "src/Vector2.cpp", "src/Vector3.cpp",
                "src/Angle.cpp", "src/MotionMath.cpp", "src/ScalarMath.cpp",
                "-Wl,--gc-sections", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)


if __name__ == "__main__":
    unittest.main()
