"""Actual Animation motion, interpolation and parent binding contracts."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
SOURCES = ['Animation', 'AnimationCallback', 'AnimationHandle', 'AnmVariables', 'Matrix4', 'Interpolation', 'Easing', 'Timer', 'ClockScalar', 'Angle', 'ScalarMath', 'Vector3', 'Vector2', 'MotionMath', 'IntegerTriple', 'FogValue', 'CollisionGeometry', 'DiagnosticAllocator', 'DebugMemoryResource', 'LockRegistry', 'AnimationChildren', 'AnimationFile', 'AnimationBinding', 'AnimationParameters', 'AnimationUpdates']
class AnimationUpdateTests(unittest.TestCase):
    def test_actual_owner_state_transitions(self):
        compiler = next((p for n in ('g++-13', 'clang++-18', 'c++') if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-animation-updates-') as d:
            output = Path(d) / 'updates'
            subprocess.run([compiler, '-std=c++20', '-O2','-ffunction-sections','-fdata-sections','-Wl,--gc-sections', '-Wall', '-Wextra', '-Werror',
                '-ffp-contract=off', '-fsanitize=undefined', '-fno-sanitize-recover=all',
                '-pthread', '-Isrc', 'tests/animation_update_semantics.cpp',
                *[f'src/{s}.cpp' for s in SOURCES], '-o', str(output)],
                cwd=ROOT, check=True, timeout=60)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)
if __name__ == '__main__': unittest.main()
