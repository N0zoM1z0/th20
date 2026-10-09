"""Whole local-coordinate mesh and viewport offsets through actual owned values."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]
SOURCES=[
    'RenderMesh', 'MeshInterfaces', 'Animation', 'AnimationHandle', 'AnmVariables',
    'Matrix4', 'Motion', 'MotionMath', 'MotionConfiguration', 'MotionUpdates',
    'Vector2', 'Vector3', 'SpriteVertices', 'Angle', 'Interpolation',
    'IntegerTriple', 'FogValue', 'Easing', 'Timer', 'ClockScalar',
    'ScalarMath', 'Identifier32', 'BulletValues', 'ShotMetadata', 'CollisionGeometry',
    'Session', 'PlayerRecord', 'LockRegistry', 'DiagnosticAllocator', 'DebugMemoryResource',
    'Graphics', 'Configuration', 'ConfigurationValue', 'Worker', 'Context',
    'TaskInfo', 'FunctionChain',
]

class RenderMeshSurfaceTests(unittest.TestCase):
    def test_local_uv_viewport_offsets_and_complete_strips(self):
        compiler=next((p for name in ('g++-13','clang++-18','c++')
                       if (p:=shutil.which(name))),None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-surface-grid-') as directory:
            output=Path(directory)/'surface-grid'
            subprocess.run([compiler,'-std=c++20','-O2','-Wall','-Wextra','-Werror',
                '-fsanitize=undefined,float-cast-overflow','-fno-sanitize-recover=all',
                '-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-pthread',
                '-Isrc','tests/render_mesh_surface_semantics.cpp','src/RenderMeshSurface.cpp',
                *[f'src/{n}.cpp' for n in SOURCES],'-o',str(output)],cwd=ROOT,check=True,timeout=60)
            subprocess.run([str(output)],cwd=ROOT,check=True,timeout=30)
if __name__=='__main__':
    unittest.main()
