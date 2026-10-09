"""Complete primary spawn through real Item pools, RNG and typed owners."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

from test_item_owner_semantics import SOURCES as OWNER_SOURCES

ROOT = Path(__file__).resolve().parents[1]
SOURCES = OWNER_SOURCES + ['ItemSpawn', 'Weapon', 'AnimationFile', 'Bullet',
                         'BulletController', 'BulletValues', 'PlayerDamageCap',
                         'WeaponStoneInfo']


class ItemSpawnTests(unittest.TestCase):
    def test_complete_primary_spawn_protocol(self):
        compiler = next((p for name in ('g++-13', 'clang++-18', 'c++')
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-item-spawn-') as directory:
            binary = Path(directory) / 'item-spawn'
            subprocess.run([
                compiler, '-std=c++20', '-O2', '-Wall', '-Wextra', '-Werror',
                '-fsanitize=undefined', '-fno-sanitize-recover=all', '-pthread',
                '-ffunction-sections', '-fdata-sections', '-Wl,--gc-sections',
                '-Isrc', 'tests/item_spawn_semantics.cpp',
                *(f'src/{name}.cpp' for name in SOURCES), '-o', str(binary),
            ], cwd=ROOT, check=True)
            subprocess.run([str(binary)], cwd=ROOT, check=True, timeout=60)


if __name__ == '__main__':
    unittest.main()
