"""Whole owned dispatcher behavior with bounded unresolved VM dependencies."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EclTickSemanticsTests(unittest.TestCase):
    def test_owned_whole_dispatcher(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "ecl-tick"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-Wno-sign-compare", "-fno-strict-aliasing", "-fsanitize=undefined",
                "-Isrc", "tests/ecl_tick_semantics.cpp", "src/EclRuntimeTick.cpp",
                "src/ScriptStack.cpp", "src/EclLoaderBase.cpp", "src/GameRandom.cpp", "src/GameRandomAngle.cpp",
                "src/Interpolation.cpp", "src/Easing.cpp", "src/Timer.cpp",
                "src/ClockScalar.cpp", "src/Angle.cpp", "src/ScalarMath.cpp",
                "src/Vector3.cpp", "src/Vector2.cpp", "src/MotionMath.cpp",
                "src/IntegerTriple.cpp", "src/FogValue.cpp", "src/CollisionGeometry.cpp",
                "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True)
