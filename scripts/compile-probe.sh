#!/usr/bin/env bash
set -euo pipefail
repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
exec "$repo_root/scripts/repo-python" "$repo_root/scripts/compile-probe.py" "$@"
