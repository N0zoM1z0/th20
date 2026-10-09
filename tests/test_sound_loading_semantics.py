"""Whole loading protocol with actual owners, allocation and failure paths."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class SoundLoadingTests(unittest.TestCase):
    def test_loading_resources_failures_and_notification_arithmetic(self):
        compiler = next((p for name in ('g++-13', 'clang++-18', 'c++')
                         if (p := shutil.which(name))), None)
        self.assertIsNotNone(compiler)
        with tempfile.TemporaryDirectory(prefix='th20-sound-loading-') as directory:
            output = Path(directory) / 'sound-loading'
            subprocess.run([
                compiler, '-std=c++20', '-O2', '-Wall', '-Wextra', '-Werror',
                '-fsanitize=undefined', '-Isrc', '-pthread',
                'tests/sound_loading_semantics.cpp', 'src/SoundLoading.cpp',
                'src/GraphicsSound.cpp', 'src/Graphics.cpp', 'src/SoundEffects.cpp',
                'src/Configuration.cpp', 'src/ConfigurationValue.cpp',
                'src/AnimationHandle.cpp', 'src/Worker.cpp', 'src/Vector2.cpp',
                'src/Vector3.cpp', 'src/FogValue.cpp', 'src/DiagnosticAllocator.cpp',
                'src/DebugMemoryResource.cpp', 'src/LockRegistry.cpp',
                '-Wl,--wrap=malloc', '-Wl,--wrap=free', '-o', str(output),
            ], cwd=ROOT, check=True, timeout=60)
            subprocess.run([str(output)], cwd=ROOT, check=True, timeout=30)


if __name__ == '__main__':
    unittest.main()
