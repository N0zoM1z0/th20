"""Whole mesh construction, Graphics creation, VM output and buffer retirement."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]
SOURCES=['RenderMeshLifecycle', 'GraphicsMesh', 'MeshResourceAccess', 'RenderMesh', 'MeshInterfaces', 'Animation', 'AnimationCallback', 'AnimationHandle', 'AnimationParameters', 'AnimationFile', 'AnmVariables', 'Matrix4', 'Motion', 'MotionMath', 'MotionConfiguration', 'MotionUpdates', 'Vector2', 'Vector3', 'SpriteVertices', 'Angle', 'Interpolation', 'IntegerTriple', 'FogValue', 'Easing', 'Timer', 'ClockScalar', 'ScalarMath', 'Identifier32', 'BulletValues', 'ShotMetadata', 'CollisionGeometry', 'Session', 'PlayerRecord', 'LockRegistry', 'DebugMemoryResource', 'Graphics', 'Configuration', 'ConfigurationValue', 'Worker', 'Context', 'TaskInfo', 'FunctionChain']
class RenderMeshLifecycleTests(unittest.TestCase):
    def test_whole_owned_protocol(self):
        compiler=next((p for n in ('g++-13','clang++-18','c++') if (p:=shutil.which(n))),None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-mesh-lifetime-') as directory:
            output=Path(directory)/'mesh'
            subprocess.run([compiler,'-std=c++20','-O2','-Wall','-Wextra','-Werror',
                '-fsanitize=undefined,float-cast-overflow','-fno-sanitize-recover=all',
                '-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-pthread',
                '-Isrc','tests/render_mesh_lifecycle_semantics.cpp',
                *[f'src/{n}.cpp' for n in SOURCES],'-o',str(output)],cwd=ROOT,check=True,timeout=60)
            subprocess.run([str(output)],cwd=ROOT,check=True,timeout=40)
if __name__=='__main__':unittest.main()
