"""Whole maintained Item lifecycle through actual owned values and callbacks."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT=Path(__file__).resolve().parents[1]
sources=['Item','Animation', 'AnimationCallback','AnimationHandle','AnmVariables','Matrix4','Interpolation',
 'Easing','Timer','ClockScalar','Angle','ScalarMath','Vector3','Vector2','MotionMath',
 'IntegerTriple','FogValue','CollisionGeometry','DiagnosticAllocator','DebugMemoryResource',
 'LockRegistry','FunctionChain','FunctionChainAllocation','FunctionChainController',
 'TaskInfo','TaskInfoConstruction','EclDiagnostic','Context','Session','PlayerRecord',
 'OverlayCounter','GameRandom','GameRandomStream','AnimationFile','Cursor','EffectParameters','Worker','SoundEffects','WeaponStoneInfo']

class ItemLifecycleTests(unittest.TestCase):
    def test_rng_effect_order_and_observer_retirement(self):
        compiler=next((p for name in ('g++-13','clang++-18','c++')
                       if (p:=shutil.which(name))),None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-item-lifecycle-') as directory:
            output=Path(directory)/'item-lifecycle'
            subprocess.run([compiler,'-std=c++20','-O2','-Wall','-Wextra','-Werror',
                '-Wno-invalid-offsetof','-fsanitize=undefined','-fno-sanitize-recover=all',
                '-pthread','-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-Isrc',
                'tests/item_lifecycle_semantics.cpp',*[f'src/{n}.cpp' for n in sources],
                'src/ItemLifecycle.cpp','src/ItemLifecycleAccess.cpp','-o',str(output)],
                cwd=ROOT,check=True,timeout=60)
            subprocess.run([str(output)],cwd=ROOT,check=True,timeout=30)

if __name__=='__main__':
    unittest.main()
