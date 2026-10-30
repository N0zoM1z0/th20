# CORE/RECON-953 — native 2,884B particle-grid update Boss: original full body, CFG and relocation inventory (SOURCE ABSENT)

Immutable original target: Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

> **CORE/RECON-966 updated frontier:** The original boundaries and native
> relocation fingerprints below remain valid. A temporary in-memory Ghidra
> function transaction recovered the entire provisional decompilation,
> and a [tracked whole typed C++20 research probe](ANIMATION_PARTICLE_GRID_UPDATE_2884_TEMP_GHIDRA_AND_TYPED_FRONTIER.md)
> now compiles to **2,953B/764-i386**, with 99 call and 25 data relocation
> fields versus original 2,884B/768. **Still NONEXACT and not canonically
> source-present**; do not count probe source as accepted game code.

This original **2,884B/768-i386** particle-grid virtual Update Boss
was **not correctly represented as a function** at `0x0045C360` in the
initial Ghidra function ledger. This checkpoint recovers its **actual
original physical bounds and call/data roles** directly from the
unchanged PE rather than guessing a size from adjacent decompiler
records. It is deliberately **SOURCE-ABSENT / NONEXACT**: no candidate
C++ source, strict object, accepted mapping or game-authored `.text`
credit is claimed here.

## Native original boundaries and independent call-role fingerprint

[`scripts/verify-animation-particle-grid-update2884-native.py`](../scripts/verify-animation-particle-grid-update2884-native.py)
authenticates all 2,884 original code bytes and 768 disassembled i386
instructions through the sole actual `ret` at `0x0045CEA3`, and verifies
all **12 genuine native `INT3`** bytes `0x0045CEA4..0x0045CEAF`.
The next byte `0x0045CEB0` is the independently exact original
[92B particle-grid virtual stop](ANIMATION_PARTICLE_GRID_STOP92_STRICT_EXACT.md),
not part of this Boss. The original PE `.rdata` vtable at `0x0056EC14`
contains the actual pointer to `0x0045C360` in slot 1:

| Original virtual slot | Original pointer | Current status |
| --- | --- | --- |
| 0 | `0x0045C320` | 49B scalar deleting wrapper, exact/uncredited compiler code |
| 1 | `0x0045C360` | **This native 2,884B Update Boss; SOURCE ABSENT** |
| 2 | `0x00412540` | Independently existing folded/default method |
| 3 | `0x0045CEB0` | 92B handle stop loop, independently exact |
| 4 | `0x0045D060` | 51B event method, native verified but source NONEXACT due folded Timer ABI |
| 5 | `0x00414B50` | Independently existing folded/default method |

All six physical vtable pointer fields have genuine original PE HIGHLOW
relocations. The large Boss itself has exactly **99 true original E8
sites and physical destinations**, **25 real PE HIGHLOW sites and physical
targets**, and no direct decoded conditional/unconditional branch that
jumps outside the 2,884B body. This is not a shortened/concatenated set
of little helpers. The independent validator freezes SHA-256 fingerprints
of the **ordered full 99-site call list** and **ordered 25-field data
list**, as well as the complete original 2,884B body and the twelve
alignment bytes. The original target hash is rechecked every run.

### Actual high-frequency original call evidence

| Original callee | E8 occurrences | Grounded role or status |
| --- | ---: | --- |
| `0x00414580` | 13 | Original indexed `Vector3::operator[]` physical folded accessor |
| `0x0045D0C0` | 12 | Separate scalar/view helper; requires its own source and ABI investigation |
| `0x00439330` | 6 | Original polar vector conversion |
| `0x00429830` | 6 | Original game RNG unit |
| `0x004297D0` | 4 | Original RNG radians |
| `0x0045CF10` | 2 | **202B three-dimensional normalization**, now independently whole strict exact |
| `0x0044CED0` | 5 | Original AnimationHandle resolve |
| `0x0045D030` | 1 | Original Timer change gate |
| `0x00423540` | 1 | Timer advancement |
| `0x005429EE` | 1 | Original stack security-cookie verifier |

The original global RNG at `0x005BA4C4` occurs in **ten physical HIGHLOW
fields**. Separate native constant/data targets include `0x0056EC84`,
`0x0056EC8C`, `0x0056EC90`, `0x0056EC94`, `0x0056EC98`, `0x0056EC9C`
and `0x0056E04C`. Their unique gameplay meanings are **not presumed**
from proximity to this group; the next reconstruction should compare
original caller arguments and field values before naming these constants.

In the current function ledger, **82 of the 99 E8 occurrences** resolve
to previously matching/reconstructed callees, and 17 to still
unclassified entries. These are counts of **call occurrences**, not
unique functions, and can change as child functions are added. This
checkpoint makes no assertion that the enclosing Boss is exact merely
because many of its children are.

## Reproduction and honest exactness status

```bash
scripts/repo-python scripts/verify-animation-particle-grid-update2884-native.py
scripts/repo-python scripts/verify-animation-particle-grid-stop92-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

No `config/functions.csv` source-present row, `config/matches.csv` exact
row or `config/match-units.toml` compiler unit was added for this
2,884B parent. No source-level or global cold replay is appropriate yet.
This inventory provides a target-bound original function boundary and
full-role fingerprint for subsequent structured C++/CFG reconstruction,
not a playable game or whole native exactness claim.
