# Japanese release and selected target provenance

Verified on 2026-10-06. The user explicitly selected the supplied Steamless
variant as exact oracle, retaining the Steam-original backup as provenance.

## Official sources

- [ZUN's release announcement](https://touhou-project.news/news/14975/)
  announces the full TH20 release for 2025-08-17 at Comic Market 106.
- [The official Steam storefront](https://store.steampowered.com/app/3671710/)
  identifies Team Shanghai Alice as developer, Mediascape as publisher, and
  Japanese interface/subtitles support. Its displayed release date may be
  2025-08-16 in the storefront's timezone.
- The supplied Japanese `readme.txt` independently records v1.00a and
  2025-08-17. This document corroborates the package version but cannot prove
  executable identity by itself. No publisher-issued executable checksum was found.

## Independent whole-file identification

[THCRAP's executable registry](https://github.com/thpatch/thcrap-tsa/blob/25acfe37f0bed5008eb8b94afc3d72679fd50384/base_tsa/versions.js)
at commit `25acfe37f0bed5008eb8b94afc3d72679fd50384` registers all three
supplied executables by exact SHA-256. This is evidence from the authors of
that registry, not an official publisher checksum.

| File/variant | Bytes | SHA-256 | Identification |
| --- | ---: | --- | --- |
| `game_exe/th20.exe` | 1,858,560 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` | v1.00a, original Steamless |
| `game_exe/th20.exe.bak` | 2,044,936 | `b0b5847b5f6dc43d51535ed9903a85485547b27dc053587544aac0f148ea4eaf` | v1.00a, original Steam release |
| `game_exe/custom.exe` | 141,312 | `261fb74f64b8a9908b128d30d59af64c59e2c37f6f917ee6646f4c3e42d50f33` | v1.00a, original custom program |
| Non-Steam retail (not supplied) | registry: 1,858,560 | `e6c4371e214c95dd4dbcaaf6818c79c5e89881270f65b62b8c3c965b65851e2d` | v1.00a, original |

The local selected executable matches the registered Steamless variant, not
unmodified non-Steam retail. The backup has a `.bind` section, wrapped entry
and encrypted `.text`; the selected binary has six sections and a decrypted
`.text` with entry `0x005435E0`. The other five raw sections compare identical
between those two files. This observation supports their relationship but is
not an independent reproduction of the unwrapping transformation.

`resources/th20.exe` is an ignored symlink to the supplied file; it is not a
new patched copy. Both originals remain unmodified outside the public repo.

```bash
python3 scripts/verify-provenance.py --fetch
python3 scripts/verify-target.py
```

The registry URL and snapshot hash are fixed in
`config/version-identities.toml`. `--fetch` re-downloads that immutable
snapshot and refuses changed contents. No complete game files or archives
are redistributed or included in Git.
