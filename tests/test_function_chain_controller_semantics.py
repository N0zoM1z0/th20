"""Whole scheduling protocol, mutation, locking and real owned destruction."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class FunctionChainControllerTests(unittest.TestCase):
    def test_complete_owned_protocol(self):
        compiler = next((p for name in ("g++-13", "clang++-18", "c++")
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "function-chain-controller"
            subprocess.run([
                compiler, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror",
                "-fsanitize=undefined", "-Isrc", "-pthread",
                "tests/function_chain_controller_semantics.cpp", "src/FunctionChain.cpp",
                "src/FunctionChainController.cpp", "src/DiagnosticAllocator.cpp",
                "src/DebugMemoryResource.cpp", "src/LockRegistry.cpp", "-o", str(output),
            ], cwd=ROOT, check=True)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=45)


if __name__ == "__main__":
    unittest.main()
