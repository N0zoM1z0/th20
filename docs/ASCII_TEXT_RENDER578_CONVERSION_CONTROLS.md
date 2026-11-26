# ASCII text conversion controls and call-role validation

The current `AsciiTextRender578.cpp` still compiles to **574B / 138
instructions** against the complete **578B / 139-instruction** original at
`0x0044B020`. Four bounded conversion controls did not recover the native
lowering. The maintained source and canonical providers are unchanged.
The investigation also exposed and fixed a false pass in its call-role
checker: a relocation redirected from lock lookup to `strlen` was accepted.

The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The compiler is locked MSVC 19.44.35211, x86 C++20 with
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /sdl /EHsc` and the floating-point
setting below. Native call/data identities and the complete baseline
comparison are in [the renderer frontier](ASCII_TEXT_RENDER578_NATIVE_FRONTIER.md).

## What the controls distinguish

| Source/control | FP setting | Complete result | Native difference |
| --- | --- | ---: | --- |
| Maintained explicit correction table | precise | 574B / 138 | Width spill precedes the `strlen` argument preparation; memory-source multiply replaces the native load plus register multiply |
| Inline width and comma-sequenced length assignment/correction | precise | 550B / 136 | `strlen` moves before width calculation; conversion also loses the double temporary |
| Inline width and explicit unsigned → double → float casts | precise | 566B / 138 | Width is evaluated before `strlen`, but double-to-float converts directly from XMM0 rather than the native stored double; multiply accumulates in XMM1 |
| Assign the unsigned-to-double result inside the float conversion | precise | 562B / 137 | Restores a double store/load but moves `strlen` before width and changes local slots |
| Inline width and natural unsigned-to-float conversion | strict | 578B / 139 | All eleven call positions align; the same five SSE operand bytes still differ |

The last control matches 497/502 ordinary bytes. Its differences are at
`+0x16D`, `+0x171`, `+0x17F`, `+0x184` and `+0x188`: multiplication and
division accumulate in XMM1, followed by sprite subtraction/conversion in
XMM0, while the original uses the opposite registers. `/fp:strict` therefore
does not resolve this natural-conversion candidate.

The native sequence requires the width spill after the `strlen` LEA/PUSH,
unsigned conversion through the real `{0.0, 4294967296.0}` table, a stored
double at `[ebp-0x550]`, conversion back to float, then a separate width load
and register multiply. The explicit double cast demonstrates why a
semantically equivalent conversion can remove twelve bytes and change the
frame. The assigned-double and comma controls demonstrate why introducing
an assignment into the expression does not preserve evaluation order.

Anonymous conversion constants in the cast/strict controls were checked
against the complete 16B COFF `.rdata` definition and original `0x0056CDD0`
contents. Their bindings were not solved from compared relocation fields.
The maintained source retains its explicit typed table owner.

All four controls retain the eleven ordered call roles and eight identified
data roles. The assigned-double control also changes their data-role order;
the other controls preserve that order while differing in complete code. All six accepted helper bodies and relocation
records remain identical to the fresh baseline. A private manifest, changing
only the object path, also passes all six complete existing helper comparisons:
93B function copy, 20B function destructor, and 25B/71B/20B/30B function-class
helpers. This does not admit a new parent or move a public provider.

## Fixing the observed verifier false pass

The previous checker iterated each character of a prefix string inside
`any(...)`. It consequently accepted a foreign callee if its name contained
one shared character. A private copy of the fresh baseline redirects the
first REL32 from `LockRegistry::slot` to the existing `_strlen` symbol,
leaving code bytes, offsets and relocation kinds intact. The previous
checker passes this object; the corrected checker rejects it at the
complete expected-prefix comparison.

Call and data symbols now use case-sensitive `startswith` checks. The
ordinary-source substring assertions were removed; generated code,
relocations, conversion-table bytes and the independent native census remain
the evidence. The fresh 574B baseline passes the corrected checker. A width
multiplier redirected to the one-float global is also rejected. Target and
canonical objects were never mutated.

Private sources, objects and proofs are retained under
`.analysis/ascii-render578-session/` and `build/gpt61-ascii-render-probe/`.
Useful proof files are `baseline-frontier.txt`, `conversion-expression-proof.txt`,
`double-stage-proof.txt`, `assigned-double-proof.txt`,
`native-conversion-strict-proof.txt`, `current-helper-proof.txt`,
`fixed-verifier-positive.txt` and `verifier-controls.txt`.

**Public native replay scope: zero.** No native source, shared header,
profile, manifest, layout or relocation anchor changed. The next useful
step needs evidence for the original scalar lowering or compiler context;
repeat syntax variants and insertion of a synthetic load would not resolve
that question. Card finish at `0x004878B0` is already independently
[whole 602B exact](CARD_FINISH_602_STRICT_EXACT.md), so it is not a remaining
matching target.
