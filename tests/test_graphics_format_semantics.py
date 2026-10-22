"""Actual Graphics texture-format selection and folded device/predicate methods."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class GraphicsFormatTests(unittest.TestCase):
    def test_native_format_identity_and_actual_receiver(self):
        compiler = next((found for name in ("g++-13", "clang++-18", "c++")
                         if (found := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix="th20-graphics-format-") as directory:
            output = Path(directory) / "graphics-format"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-ffunction-sections", "-fdata-sections",
                "-Wl,--gc-sections", "-Isrc", "-pthread",
                "tests/graphics_format_semantics.cpp", "src/Graphics.cpp",
                "src/Configuration.cpp", "src/ConfigurationValue.cpp",
                "src/AnimationHandle.cpp", "src/Worker.cpp", "src/Vector2.cpp",
                "src/Vector3.cpp", "src/FogValue.cpp", "src/LockRegistry.cpp",
                "-o", str(output),
            ], cwd=ROOT, check=True, timeout=60)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=15)


if __name__ == "__main__":
    unittest.main()
