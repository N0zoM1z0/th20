# Runtime no-life-decrement launcher

Run `run_th20_no_life_decrement_attach.bat` in
`D:\Entertainment\Game\Touhou\th20`. The launcher, `repo-python.cmd`
and `runtime-no-life-decrement.py` are installed there. Close the current game
before starting another instance. The launcher verifies the executable, starts
it with its game directory as the working directory, then patches its memory.
Normal `th20.exe` launches are unchanged. Exit the game to discard the patch.

This preserves the life stock when a hit reaches death processing. Hits,
respawning, power loss, death counters and other original effects still run;
it is an unlimited-lives patch. No game executable on disk is modified.

The script accepts only the locked Japanese Steamless SHA-256 from
`config/target.toml`. Ghidra independently verifies death entry 0x004F8420:
0x004F849C pushes -1; 0x004F84A1 calls the receiver at 0x004E1250, which adds
that parameter to life stock at receiver +0xB8. Replacing the immediate at
RVA 0x000F849D with zero retains the call and its stack convention. All
surrounding instructions are checked before writing. Other rewards and
positive life additions use unchanged call sites.

The Windows implementation verifies the process path/hash and discovers the
actual module base, including ASLR. It checks the original or already-patched
byte and surrounding call, restores memory protection, flushes the instruction
cache, and reads back the result. Ambiguous processes or different builds are
rejected. A failed patch terminates only the instance launched by that attempt.
The log is `runtime_patch_log.txt` in the game directory.

Windows Python runs through `repo-python.cmd`, the Windows companion to the
repository entry point. It honors `TH20_PYTHON`, a local Windows virtual
environment, the installed IDA Python, then the Windows Python launcher.
Use Python 3.11 or later. The patcher itself uses only the standard library.

To install elsewhere, copy the three files from `scripts/` beside the verified
`th20.exe`. The batch launcher also accepts `TH20_GAME_DIR`. Offline verification
from this repository uses:

```bash
scripts/repo-python scripts/runtime-no-life-decrement.py --game-dir /path/to/game --check
```

On 2026-10-06 the installed Windows launcher flow successfully started PID
71528, discovered relocated module base 0x00760000, and verified the byte at
0x0085849D changed from FF to 00. A second attach confirmed idempotence. The
on-disk SHA-256 remained unchanged. A complete hit/respawn playthrough has not
yet been observed. Private disassembly and launch receipts remain under
`.analysis/`; the game-directory log also records the live validation.

This user-requested memory patch is a separate play aid. It receives no
reconstruction, exact-function, or whole-game runtime acceptance credit and
never changes the file oracle or the Ghidra database.
