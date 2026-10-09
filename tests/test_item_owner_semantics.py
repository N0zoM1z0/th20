"""Actual Item pool/lifetime, scheduler, reward Counter and scaled RNG."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCES = ['Item', 'Animation', 'AnimationHandle', 'AnmVariables', 'Matrix4',
           'Interpolation', 'Easing', 'Timer', 'ClockScalar', 'Angle', 'ScalarMath',
           'Vector3', 'Vector2', 'MotionMath', 'IntegerTriple', 'FogValue',
           'CollisionGeometry', 'DiagnosticAllocator', 'DebugMemoryResource',
           'LockRegistry', 'FunctionChain', 'FunctionChainAllocation',
           'FunctionChainController', 'TaskInfo', 'TaskInfoConstruction',
           'EclDiagnostic', 'Context', 'Session', 'PlayerRecord', 'OverlayCounter',
           'GameRandom', 'GameRandomStream']


class ItemOwnerTests(unittest.TestCase):
    def test_pool_lifetime_publication_rewards_and_bulk_spawn_calls(self):
        compiler = next((p for name in ('g++-13', 'clang++-18', 'c++')
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-item-') as directory:
            binary = Path(directory) / 'item-owner'
            subprocess.run([
                compiler, '-std=c++20', '-O2', '-Wall', '-Wextra', '-Werror',
                '-fsanitize=undefined', '-fno-sanitize-recover=all', '-pthread',
                '-ffunction-sections', '-fdata-sections', '-Wl,--gc-sections',
                '-Wl,--wrap=free', '-Isrc', 'tests/item_owner_semantics.cpp',
                *(f'src/{name}.cpp' for name in SOURCES), '-o', str(binary),
            ], cwd=ROOT, check=True)
            subprocess.run([str(binary)], cwd=ROOT, check=True, timeout=30)


if __name__ == '__main__':
    unittest.main()
