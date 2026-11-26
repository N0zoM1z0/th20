# Text-submit parameter cleanup and compiler controls

The two missing NOPs in the 294B text submitter follow destruction of its
**incoming by-value callback**, not two copied temporary callbacks. All three
in-body destructor sites address `[ebp+0x38]`. The first two precede returns;
the third is compiler-emitted fallthrough cleanup. The separate EH cleanup
also destroys that same parameter.

The game body remains **NONEXACT at 292B/104 instructions**, compared with
the full original 294B/106. Its complete **42B owned EH code and 44B metadata**
now strictly replay as two compiler-support units. No authored-game bytes
are added. The source-presence ledger now includes the existing submit body.

The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The controls use locked MSVC 19.44.35211 x86, with the baseline
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

## Compiler and return-expression results

| Private control | Complete body | Result |
| --- | ---: | --- |
| Maintained C++20 source | 292B / 104 instructions | Only two native NOPs absent |
| C++17 | 332B / 116 | Additional result copies and normal cookie check |
| C++17 plus `/Zc:nrvo` | 292B / 104 | Complete bytes and relocation records equal the baseline |
| Baseline plus `/Z7` | 292B / 104 | Complete bytes and relocation records equal the baseline |
| Baseline plus `/ZI` | 300B / 112 | All three cleanup NOPs, but a different frame |
| Direct `std::bit_cast` return, explicit force-inline instantiation | 333B / 118 | Still calls the library helper twice |
| Direct compiler bit-cast return | 349B / 122 | Additional result temporaries/copies |
| Prvalue union or bound-reference return | 321B / 114 | Three cleanup NOPs, additional result copies |

`/ZI` changes the stack allocation from `0x1C` to `0x68`, introduces saved
EBX/ESI/EDI and shifts local slots. It is not a matching profile. Its three
NOPs show that their emission can depend on compiler debug mode; their
presence alone does not establish the original source lifetime. C++17's
larger result is specifically separated from language-mode effects by the
NRVO control. No public compiler profile or executable body was changed.

Earlier explicit-copy, const-result and nested-scope controls remain under
`.analysis/gptweb-submit294-phase2/`; they need not be repeated. The earlier
[return-buffer investigation](ASCII_TEXT_SUBMIT294_TWO_NOP_FRONTIER.md)
explains the maintained two-word result representation.

## Complete exception ownership

The reviewed native handler anchor is `0x005686FD`. Actual COFF offsets place
the owned cleanup at `0x005686F0`: eight bytes plus five real INT3 alignment
bytes, compared as the complete 13B contribution. The cleanup calls the
established 20B function destructor at `0x00414400`. The complete 29B handler
uses the established cookie checker and C++ frame handler.

The complete 44B metadata at `0x005A9E88` contains an eight-byte one-action
map and 36B FuncInfo at `0x005A9E90`. The cleanup is live in state zero;
flags are one. Its two DIR32 fields bind the cleanup and map self-pointer.
A search excluding only the self-pointer finds one `.rdata` location. Actual
COFF metadata comes from `.xdata$x`; all 44 bytes and both physical PE
relocations match. The handler's metadata address is resolved from this
independent search, not from its compared field.

Only `AsciiTextSubmit294.cpp` was freshly compiled; no shared header changed.
**Canonical replay scope is two EH units from one fresh object** under
`build/gpt61-submit294-canonical/`. The 292B parent has no exact unit.
Existing text-core and queue products remain unchanged.

```sh
nice -n15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AsciiTextSubmit294.cpp --existing-objects
nice -n15 scripts/repo-python scripts/verify-ascii-text-submit294-native.py
```

Attested Ghidra output, source controls, build receipts and complete listings
are retained under `.analysis/ascii-submit294-session/`. Relevant proof logs
are `eh-proof.txt`, `canonical-replay.txt`, `canonical-native-proof.txt` and
`verifier-controls.txt`. Negative controls reject a wrong state count, flags,
map owner, callback address and relocation kind. A complete-extent check also
rejects awarding 294B credit to the 292B body.

The remaining question is how to reproduce the two return-cleanup NOPs with
the native frame and complete result-store sequence. Reuse these controls
before trying another language-mode switch or return-copy formulation.
