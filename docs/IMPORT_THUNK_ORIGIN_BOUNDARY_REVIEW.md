# Import-library thunk origins and six-byte boundaries

The 31 entries below are import-library jumps, totaling 186 native bytes. Each
complete body is one `FF 25 <absolute IAT slot>` instruction. Their origin is
`library`, with disposition `exclude`; none receives authored or exact credit.
The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## Independent import and boundary evidence

The original PE import descriptors and original lookup table identify each DLL
and named import or ordinal. Each encoded jump operand equals the corresponding
IAT slot, whose original entry agrees with its lookup-table entry. Every absolute
operand has an original PE HIGHLOW relocation at function entry +2. Ordinals 11
and 2 remain unnamed; the review does not infer their exported API names.

Attested Ghidra queries independently report each entry's body minimum, maximum
and address count: entry through entry +5, exactly six addresses. The complete
instruction listing agrees byte-for-byte with the locked file. Indirect `JMP`
terminates each body without a fallthrough, local branch, switch table or owned
tail. The IAT cell belongs to import data and is not appended to the code extent.
No original calling convention or parameter prototype is inferred from a jump.

| Entry | IAT slot | Import DLL | Name or ordinal |
| --- | --- | --- | --- |
| 0x0054065A | 0x0056C290 | USER32.dll | WINNLSEnableIME |
| 0x00540660 | 0x0056C000 | DINPUT8.dll | DirectInput8Create |
| 0x00540666 | 0x0056C008 | DSOUND.dll | Ordinal_11 |
| 0x0054066C | 0x0056C2F8 | d3d9.dll | Direct3DCreate9 |
| 0x00540672 | 0x0056C32C | d3dx9_43.dll | D3DXVec3Transform |
| 0x00540678 | 0x0056C328 | d3dx9_43.dll | D3DXVec3Project |
| 0x0054067E | 0x0056C324 | d3dx9_43.dll | D3DXMatrixMultiply |
| 0x00540684 | 0x0056C320 | d3dx9_43.dll | D3DXMatrixRotationX |
| 0x0054068A | 0x0056C31C | d3dx9_43.dll | D3DXMatrixRotationY |
| 0x00540690 | 0x0056C304 | d3dx9_43.dll | D3DXMatrixRotationZ |
| 0x00540696 | 0x0056C334 | d3dx9_43.dll | D3DXLoadSurfaceFromFileInMemory |
| 0x0054069C | 0x0056C314 | d3dx9_43.dll | D3DXLoadSurfaceFromSurface |
| 0x005406A2 | 0x0056C300 | d3dx9_43.dll | D3DXCreateTexture |
| 0x005406A8 | 0x0056C318 | d3dx9_43.dll | D3DXVec3TransformCoord |
| 0x005406AE | 0x0056C308 | d3dx9_43.dll | D3DXVec3ProjectArray |
| 0x005406B4 | 0x0056C30C | d3dx9_43.dll | D3DXMatrixTranslation |
| 0x005406BA | 0x0056C310 | d3dx9_43.dll | D3DXMatrixLookAtLH |
| 0x005406C0 | 0x0056C330 | d3dx9_43.dll | D3DXMatrixPerspectiveFovLH |
| 0x005406C6 | 0x0056C2F0 | XINPUT1_4.dll | Ordinal_2 |
| 0x00540A27 | 0x0056C1E0 | KERNEL32.dll | GetCurrentThreadId |
| 0x00540FD9 | 0x0056C12C | KERNEL32.dll | LocalFree |
| 0x00543DE0 | 0x0056C33C | gdiplus.dll | GdipAlloc |
| 0x00543DE6 | 0x0056C340 | gdiplus.dll | GdipFree |
| 0x00543DEC | 0x0056C344 | gdiplus.dll | GdiplusStartup |
| 0x00543DF2 | 0x0056C360 | gdiplus.dll | GdiplusShutdown |
| 0x00543DF8 | 0x0056C348 | gdiplus.dll | GdipCloneImage |
| 0x00543DFE | 0x0056C34C | gdiplus.dll | GdipDisposeImage |
| 0x00543E04 | 0x0056C350 | gdiplus.dll | GdipSaveImageToFile |
| 0x00543E0A | 0x0056C354 | gdiplus.dll | GdipCreateBitmapFromHBITMAP |
| 0x00543E10 | 0x0056C358 | gdiplus.dll | GdipGetImageEncodersSize |
| 0x00543E16 | 0x0056C35C | gdiplus.dll | GdipGetImageEncoders |

## A misleading provisional overlap

The initial inventory assigns `0x005419AC` the convex span
`0x005419AC..0x00551F18` (66,925 bytes). Ghidra's actual function body contains
only 40 addresses: the local block ends at `0x005419CA`, and its zero-index
branch targets the separate nine-byte block at `0x00551F10..0x00551F18`.
Thus the span encloses the GDI+ jumps without owning them. Checking only CSV
interval overlap would incorrectly reject those ten independently bounded stubs.

The [subsequent lock ownership review](CRT_LOCK_OWNERSHIP_BOUNDARY_REVIEW.md)
resolves this partition using complete independent STL and UCRT objects:
31 bytes belong to `_Lockit::~_Lockit` and the distant nine bytes are the
separate `_unlock_locales` function. Both bodies and the conditional tail edge
are retained in the reviewed ledger. Other unusually large runtime spans still
need the same ownership check before being treated as native body sizes.

## Reproduction and checkpoint scope

Private evidence is retained under `.analysis/origin-boundary/`:
`import-thunks.txt`, `import-bodies.txt`, `import-neighbor-overlaps.txt`,
`discontiguous-locale-helper.txt`, and the independent PE audit
`imports-pe-audit.json` / `audit-imports.py`. Queries use `scripts/ghidra.py`
with reduced priority and attest both the locked file and database. To repeat
the body query, pass `function` and the table's entry addresses; use
`disassemble 3` for the instruction query. Query `disassemble 30 0x005419AC`
for the discontiguous counterexample.

Only the two classification/boundary ledgers, generated progress and review
notes change. Native source, headers, profiles, manifests, match records and
canonical objects/receipts are unchanged. The affected exact replay scope is
**zero units**. Tracking and generated progress are checked after the ledger
edits; protected executable inputs and current canonical products retain their
captured hashes. No compiler or whole-graph replay is needed.
