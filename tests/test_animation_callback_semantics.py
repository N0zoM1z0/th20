"""Whole callback owner, signed remapping and actual virtual retirement."""
from pathlib import Path
import shutil, subprocess, tempfile, unittest
ROOT = Path(__file__).resolve().parents[1]
SOURCES = ['Animation', 'AnimationHandle', 'AnmVariables', 'Matrix4', 'Interpolation', 'Easing', 'Timer', 'ClockScalar', 'Angle', 'ScalarMath', 'Vector3', 'Vector2', 'MotionMath', 'IntegerTriple', 'FogValue', 'CollisionGeometry', 'DiagnosticAllocator', 'DebugMemoryResource', 'LockRegistry', 'AnimationChildren', 'AnimationCallback', 'AnimationBinding', 'AnimationFile', 'Bullet', 'BulletController', 'BulletValues', 'ShotMetadata', 'TaskInfoConstruction', 'TaskInfo', 'FunctionChain']
class AnimationCallbackTests(unittest.TestCase):
    def test_real_callback_owner_and_script_protocol(self):
        compiler=next((p for n in ('g++-13','clang++-18','c++') if (p:=shutil.which(n))),None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-animation-callback-') as d:
            output=Path(d)/'callback'
            subprocess.run([compiler,'-std=c++20','-O2','-Wall','-Wextra','-Werror','-ffp-contract=off',
                '-fsanitize=address,undefined,float-cast-overflow','-fno-sanitize-recover=all',
                '-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-pthread','-Isrc',
                'tests/animation_callback_semantics.cpp',*[f'src/{s}.cpp' for s in SOURCES],'-o',str(output)],
                cwd=ROOT,check=True,timeout=90)
            result=subprocess.run([str(output)],cwd=ROOT,check=True,capture_output=True,text=True,timeout=40)
            self.assertIn('PASS 149903 ',result.stdout)
if __name__ == '__main__': unittest.main()
