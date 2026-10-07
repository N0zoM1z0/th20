"""Owned whole ECL loading/cache/cycle/failure protocol with real resource owners."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EclFileLoadingTests(unittest.TestCase):
    def test_whole_loading_cache_and_temporary_cleanup(self):
        compiler = next((path for name in ("g++-13", "clang++-18", "c++")
                         if (path := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "ecl-file-loading"
            sources = ["EclFileLoader", "EclLoaderBase", "EclDiagnostic", "ScriptStack", "Context",
                       "EnemyData", "EnemyCounters", "AnimationHandle", "Timer", "ClockScalar", "Identifier32"]
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-Isrc", "tests/ecl_file_loading_semantics.cpp",
                *(f"src/{name}.cpp" for name in sources), "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=10)
