"""Check interpreter selection, argument forwarding and decoder rejection."""
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
WRAPPER = ROOT / "scripts/repo-python"


class RepoPythonTests(unittest.TestCase):
    def test_explicit_interpreter_and_arguments_from_another_directory(self):
        environment = dict(os.environ, TH20_PYTHON=sys.executable)
        with tempfile.TemporaryDirectory() as temporary:
            result = subprocess.run(
                [str(WRAPPER), "-c", "import json,sys; print(json.dumps([sys.executable, sys.argv[1:]]))",
                 "argument with spaces", "$(literal)", ""],
                cwd=temporary, env=environment, text=True, capture_output=True, check=True)
        interpreter, arguments = json.loads(result.stdout)
        self.assertEqual(interpreter, sys.executable)
        self.assertEqual(arguments, ["argument with spaces", "$(literal)", ""])

    def test_missing_override_does_not_fall_back(self):
        result = subprocess.run([str(WRAPPER), "-c", "print('should not run')"],
                                env=dict(os.environ, TH20_PYTHON="/nonexistent/th20-python"),
                                text=True, capture_output=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(result.stdout, "")

    def test_mismatched_decoder_is_rejected_before_running_command(self):
        with tempfile.TemporaryDirectory() as temporary:
            (Path(temporary) / "capstone.py").write_text('__version__ = "4.0.2"\n')
            result = subprocess.run([str(WRAPPER), "-c", "print('should not run')"],
                                    cwd=temporary,
                                    env=dict(os.environ, TH20_PYTHON=sys.executable, PYTHONPATH=temporary),
                                    text=True, capture_output=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(result.stdout, "")
        self.assertIn("differs from pinned 5.0.6", result.stderr)
