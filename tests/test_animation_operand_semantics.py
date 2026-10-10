"""Complete operand tables, mutable aliases, RNG streams and parent frames."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
SOURCES = ['Animation', 'AnimationCallback', 'AnimationHandle', 'AnmVariables', 'Matrix4', 'Interpolation', 'Easing', 'Timer', 'ClockScalar', 'Angle', 'ScalarMath', 'Vector3', 'Vector2', 'MotionMath', 'IntegerTriple', 'FogValue', 'CollisionGeometry', 'DiagnosticAllocator', 'DebugMemoryResource', 'LockRegistry', 'AnimationChildren', 'AnimationGeometry', 'AnimationOperands', 'AnimationFile', 'Graphics', 'Configuration', 'ConfigurationValue', 'Worker', 'GameRandom', 'GameRandomStream', 'Item', 'TaskInfo', 'FunctionChain']
class AnimationOperandTests(unittest.TestCase):
    def test_actual_owners_random_and_recursive_frames(self):
        compiler = next((p for n in ('g++-13', 'clang++-18', 'c++') if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-animation-operands-') as d:
            output = Path(d) / 'operands'
            subprocess.run([compiler, '-std=c++20', '-O2', '-Wall', '-Wextra', '-Werror',
                '-ffp-contract=off', '-fsanitize=undefined,float-cast-overflow', '-ffunction-sections', '-fdata-sections', '-Wl,--gc-sections', '-fno-sanitize-recover=all',
                '-pthread', '-Isrc', 'tests/animation_operand_semantics.cpp',
                *[f'src/{s}.cpp' for s in SOURCES], '-o', str(output)],
                cwd=ROOT, check=True, timeout=90)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=40)
if __name__ == '__main__': unittest.main()
