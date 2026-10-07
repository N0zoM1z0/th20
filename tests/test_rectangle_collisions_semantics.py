"""Native rectangle/segment protocols, with finite independent geometric cases."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class RectangleCollisionsSemanticsTests(unittest.TestCase):
    def test_native_boundaries_aliasing_and_rotation(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler, "public semantic checks require a C++20 compiler")
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "rectangle-collisions-semantics"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                            "-fsanitize=undefined", "-ffp-contract=off", "-Isrc",
                            "tests/rectangle_collisions_semantics.cpp", "src/RectangleCollisions.cpp",
                            "src/GeometryMetrics.cpp", "src/CollisionShapes.cpp", "src/CollisionGeometry.cpp",
                            "src/Vector2.cpp", "src/Vector3.cpp", "src/MotionMath.cpp",
                            "src/ScalarMath.cpp", "src/Angle.cpp", "-o", str(output)],
                           cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True)
