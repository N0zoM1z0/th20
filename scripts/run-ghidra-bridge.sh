#!/usr/bin/env bash
set -euo pipefail
th20_repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
if [[ ! -f "$th20_repo_root/.env" ]]; then
  echo "Create an ignored .env from config/mcp-ghidra.env.example before starting the optional local bridge" >&2
  exit 1
fi
set -a
source "$th20_repo_root/.env"
set +a
source "$th20_repo_root/scripts/tool-env.sh"
exec node "$th20_repo_root/.tools/mcp_for_gptweb-ghidra/dist/index.js"
