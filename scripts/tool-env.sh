#!/usr/bin/env bash
th20_repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
export JAVA_HOME="$th20_repo_root/.tools/jdk"
export GHIDRA_HOME="$th20_repo_root/.tools/ghidra"
export WINEPREFIX="$th20_repo_root/.tools/wine"
export PATH="$th20_repo_root/.tools/objdiff:$PATH"
unset th20_repo_root
