"""Damage Region routing and state transitions, without private game data."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class DamageRegionSemanticsTests(unittest.TestCase):
    def test_routing_configuration_and_shared_storage(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler, "public semantic checks require a C++20 compiler")
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "damage-region-semantics"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                            "-fsanitize=undefined", "-ffp-contract=off", "-Isrc",
                            "tests/damage_region_semantics.cpp", "src/DamageRegion.cpp",
                            "src/Motion.cpp", "src/MotionUpdates.cpp", "src/Timer.cpp",
                            "src/ClockScalar.cpp", "src/Identifier32.cpp", "src/RectangleCollisions.cpp",
                            "src/GeometryMetrics.cpp", "src/CollisionShapes.cpp", "src/CollisionGeometry.cpp",
                            "src/Vector2.cpp", "src/Vector3.cpp", "src/MotionMath.cpp",
                            "src/ScalarMath.cpp", "src/Angle.cpp", "-o", str(output)],
                           cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True)
