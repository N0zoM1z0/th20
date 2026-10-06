# Runtime invincibility launcher

Run `run_th20_invincible_attach.bat` in
`D:\Entertainment\Game\Touhou\th20`. The launcher, `repo-python.cmd`
and `runtime-no-life-decrement.py` are installed there. The earlier
`run_th20_no_life_decrement_attach.bat` is a compatibility alias with the same
new behavior. Close the current game before starting another instance.

The launcher verifies the executable, starts it in its game directory, then
patches its memory. Hits return immediately from the player hit handler:
no hit sound/effect, death state, power loss or respawn is triggered by that
handler. Movement and firing continue. The earlier life-stock-only patch is
superseded. Normal executable launches are unchanged; exit to discard the patch.
The executable on disk is never modified.

Ghidra independently verifies hit entry 0x004F86F0, complete through RET at
0x004F883F. It uses the player in ECX, has no stack arguments, and its three
collision callers ignore its return value. Those callers are 0x004F8CE0,
0x004F8FF0 and 0x004F91D0; after their hit calls they produce their own result.
Replacing the entry's PUSH EBP byte at RVA 0x000F86F0 with RET returns before
any hit-side effects or player-state writes. Collision detection itself remains
active, so collision callers can still retire colliding bullets normally.

The Windows script accepts only the locked Japanese Steamless SHA-256 from
config/target.toml. It verifies the process path/hash and actual ASLR module
base, checks the original/already-patched byte and complete surrounding entry,
restores memory protection, flushes the instruction cache, and reads back.
It also checks death-call context at RVA 0x000F849C and restores an earlier
stock-only 00 immediate to its original FF if present. Other modifications
or ambiguous processes are rejected. A failed patch terminates only the game
instance launched by that attempt. Logs go to runtime_patch_log.txt.

Windows Python runs through repo-python.cmd, the Windows companion to
scripts/repo-python. It honors TH20_PYTHON, a local Windows virtual environment,
the installed IDA Python, then the Windows Python launcher. Use Python 3.11 or
later; the patcher needs only the standard library.

To install elsewhere, copy either batch launcher, the patcher and repo-python.cmd
from scripts/ beside the verified th20.exe. TH20_GAME_DIR can select another
game directory. Offline verification from the repository uses:

```bash
scripts/repo-python scripts/runtime-no-life-decrement.py --game-dir /path/to/game --check
```

The earlier stock-only version passed Windows launch, ASLR write/readback and
idempotence on 2026-10-06, with no file changes. The hit-suppression revision also
launched successfully: PID 74036, actual module base 0x00760000, hit entry
0x008586F0 changed from 55 to C3 and read back correctly. The disk SHA-256
remained unchanged. A full hit/respawn
playthrough is not inferred from memory readback. Private disassembly and
launch receipts remain under .analysis/ and in the game-directory log.

This user-requested memory patch is a separate play aid. It receives no
reconstruction, exact-function, or whole-game runtime acceptance credit and
never changes the file oracle or the Ghidra database.
