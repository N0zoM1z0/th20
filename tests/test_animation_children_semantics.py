"""Whole recursive Animation flag propagation through actual child storage."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
SOURCES = ['Animation', 'AnimationCallback', 'AnimationHandle', 'AnmVariables', 'Matrix4', 'Interpolation', 'Easing', 'Timer', 'ClockScalar', 'Angle', 'ScalarMath', 'Vector3', 'Vector2', 'MotionMath', 'IntegerTriple', 'FogValue', 'CollisionGeometry', 'DiagnosticAllocator', 'DebugMemoryResource', 'LockRegistry', 'AnimationChildren']
class AnimationChildrenTests(unittest.TestCase):
    def test_recursive_flags_and_owned_trees(self):
        compiler = next((p for n in ('g++-13', 'clang++-18', 'c++') if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-animation-children-') as d:
            output = Path(d) / 'children'
            subprocess.run([compiler, '-std=c++20', '-O2','-ffunction-sections','-fdata-sections','-Wl,--gc-sections', '-Wall', '-Wextra', '-Werror',
                '-fsanitize=undefined', '-fno-sanitize-recover=all', '-pthread', '-Isrc',
                'tests/animation_children_semantics.cpp', *[f'src/{s}.cpp' for s in SOURCES],
                '-o', str(output)], cwd=ROOT, check=True, timeout=60)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)
if __name__ == '__main__': unittest.main()
