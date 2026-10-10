# x86 build and matching

## Installed toolchain

| Item | Locked candidate |
| --- | --- |
| Compiler | MSVC 19.44.35211, x64 host / x86 target |
| Linker | 14.44.35211.0 |
| Toolset directory | 14.44.35207 |
| Windows SDK | 10.0.26100.0 |
| Legacy D3DX | Microsoft.DXSDK.D3DX 9.29.952.8 |
| Install manifest | Visual Studio 2022 17.14.6, immutable snapshot |

The directory version and compiler banner differ by design. The historical
manifest avoids silently selecting a serviced compiler from the live channel.
Payloads come from Microsoft's manifest URLs and are checked against manifest
hashes. The manifest itself, downloader Git commit and installed critical
binaries are pinned in `config/tools.lock.toml`. MSVC headers are used with
Wine's native case-insensitive path lookup; they are not rewritten.
The private Wine prefix is `.tools/wine`; other repositories' prefixes are
untouched. All generated products and PDBs stay under `build/`.

```bash
scripts/bootstrap-tools.sh
scripts/repo-python scripts/doctor.py
scripts/repo-python scripts/toolchain-smoke.py
```

The smoke probe includes Win32, Direct3D9/D3DX9, DirectInput8, DirectSound,
XInput and GDI+ headers, links the target's API library families, checks PE32
machine identity and executes a console/D3DX calculation under Wine. It is
not a reconstructed game or exact-match credit. Its `/O2 /Ob1 /MT /EHsc /GR-
/Gy /Z7` profile is a **smoke profile**, not the original game's build profile.

## Explicit compilation

```bash
scripts/compile-probe.sh .analysis/probes/example.cpp build/probes/example.obj /Od /MT /EHsc /Gy /Z7
scripts/repo-python scripts/build.py --check
scripts/repo-python scripts/build.py --unit example
scripts/repo-python scripts/compare-coff-function.py --unit example --json
scripts/repo-python scripts/replay-exact-units.py
```

The first flags are an invocation example, not target-observed truth. `/fp:`,
optimization, inlining, security, exception, RTTI and runtime flags must be
recovered per unit. The wrapper uses `/showIncludes` for freshness receipts;
no source-body selector or compiler patch is injected. Each output is ordinary
x86 COFF and has a matching `.receipt.json` recording inputs/header hashes.

A unit uses TH095's schema:

```toml
[units.example]
source = "src/Example.cpp"
object = "build/exact/Example.obj"
profile = ["/Od", "/MT", "/EHsc", "/Gy", "/Z7"]
functions = ["Example"]
symbol = "_Example"
target_address = 0x00401000 # illustrative only; not a TH20 semantic mapping
size = 32                  # reconcile against target before use
compare_size = 32
relocations = []            # must enumerate every actual COFF relocation
```

Add real relocation rows with offset, `DIR32`/`REL32`, decorated symbol and an
independently established target address. The live manifest records accepted
component units and their per-source profiles.
It is not a whole-game compile/link graph. Whole-program linkage must expose real
unresolved dependencies, without stubs or `/FORCE:UNRESOLVED`. Current counts
and verification are in [the handoff](RE_HANDOFF.md).
