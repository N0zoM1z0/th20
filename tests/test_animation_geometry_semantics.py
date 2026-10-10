"""Actual whole geometry and parent-position contracts with guarded vertices."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[1]
SOURCES = ['Animation', 'AnimationCallback', 'AnimationHandle', 'AnmVariables', 'Matrix4', 'Interpolation', 'Easing', 'Timer', 'ClockScalar', 'Angle', 'ScalarMath', 'Vector3', 'Vector2', 'MotionMath', 'IntegerTriple', 'FogValue', 'CollisionGeometry', 'DiagnosticAllocator', 'DebugMemoryResource', 'LockRegistry', 'AnimationChildren', 'AnimationGeometry', 'WindowAnimation', 'WindowState', 'SpriteVertices']
class AnimationGeometryTests(unittest.TestCase):
    def test_actual_owner_vertices_and_frames(self):
        compiler = next((p for n in ('g++-13', 'clang++-18', 'c++') if (p := shutil.which(n))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-animation-geometry-') as d:
            output = Path(d) / 'geometry'
            subprocess.run([compiler, '-std=c++20', '-O2','-ffunction-sections','-fdata-sections','-Wl,--gc-sections', '-Wall', '-Wextra', '-Werror',
                '-ffp-contract=off', '-fsanitize=undefined', '-fno-sanitize-recover=all',
                '-pthread', '-Isrc', 'tests/animation_geometry_semantics.cpp',
                *[f'src/{s}.cpp' for s in SOURCES], '-o', str(output)],
                cwd=ROOT, check=True, timeout=90)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=40)
if __name__ == '__main__': unittest.main()
