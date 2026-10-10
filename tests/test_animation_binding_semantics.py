"""Complete template preparation and scoped Animation child lookup."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
SOURCES = ['Animation', 'AnimationCallback', 'AnimationHandle', 'AnmVariables', 'Matrix4', 'Interpolation', 'Easing', 'Timer', 'ClockScalar', 'Angle', 'ScalarMath', 'Vector3', 'Vector2', 'MotionMath', 'IntegerTriple', 'FogValue', 'CollisionGeometry', 'DiagnosticAllocator', 'DebugMemoryResource', 'LockRegistry', 'AnimationChildren', 'AnimationFile', 'AnimationBinding']
class AnimationBindingTests(unittest.TestCase):
    def test_template_state_and_scoped_child_lookup(self):
        compiler = next((p for n in ('g++-13','clang++-18','c++') if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-animation-binding-') as d:
            output = Path(d) / 'binding'
            subprocess.run([compiler,'-std=c++20','-O2','-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-Wall','-Wextra','-Werror',
                '-fsanitize=undefined','-fno-sanitize-recover=all','-pthread','-Isrc',
                'tests/animation_binding_semantics.cpp',*[f'src/{s}.cpp' for s in SOURCES],
                '-o',str(output)],cwd=ROOT,check=True,timeout=60)
            subprocess.run([str(output)],cwd=ROOT,check=True,timeout=30)
if __name__ == '__main__': unittest.main()
