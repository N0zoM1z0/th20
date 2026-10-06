#!/usr/bin/env bash
set -euo pipefail
repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
if [[ $# -ne 1 ]]; then
  echo "usage: $0 /path/to/the-locked-steamless/th20.exe" >&2
  exit 2
fi
python3 "$repo_root/scripts/verify-target.py" "$1"
target_path=$(realpath -- "$1")
if [[ "$target_path" == "$repo_root/resources/th20.exe" ]]; then
  exit 0
fi
mkdir -p "$repo_root/resources"
if [[ -e "$repo_root/resources/th20.exe" && ! -L "$repo_root/resources/th20.exe" ]]; then
  echo "resources/th20.exe is an existing regular file; leaving it in place" >&2
  exit 1
fi
ln -sfn -- "$target_path" "$repo_root/resources/th20.exe"
python3 "$repo_root/scripts/verify-target.py"
