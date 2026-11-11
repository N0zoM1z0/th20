#!/usr/bin/env python3
"""Compatibility: 884B Window scheduler former NONEXACT frontier is now full exact."""
from pathlib import Path
import runpy
if __name__=='__main__':
 runpy.run_path(str(Path(__file__).with_name('verify-window-frame-scheduler884-native.py')),run_name='__main__')
