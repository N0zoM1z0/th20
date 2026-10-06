"""Independent lattice and signed-overflow checks without private game data."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class TextGeometrySemanticsTests(unittest.TestCase):
    def test_inclusive_intersections_and_wrapped_endpoints(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler, "public geometry checks require a C++20 compiler")
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "text-geometry-semantics"
            subprocess.run([compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                            "-fsanitize=undefined", "-Isrc",
                            "tests/text_geometry_semantics.cpp", "src/Rectangle.cpp",
                            "-o", str(output)], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True)
