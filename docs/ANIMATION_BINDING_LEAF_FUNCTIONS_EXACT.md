# Animation callback and lifecycle leaves — original native exact

The immutable Japanese TH20 v1.00a original PE contains five complete,
independently native-attested Animation member functions in this leaf family.
Their maintained source is ordinary C++ in `src/AnimationBinding.cpp`; each
whole function now has a strict canonical replay against the original PE.

| Reconstructed source role | Original entry | Native body | Strict replay |
| --- | ---: | ---: | ---: |
| `Animation::copy_base` | `0x004371F0` | 34B / 14 x86 instructions | 34/34 |
| `Animation::clear_pending_fields` | `0x00429E30` | 32B / 14 x86 instructions | 32/32 |
| `Animation::clear_field_570` | `0x00429E50` | 24B / 9 x86 instructions | 24/24 |
| `Animation::set_field_5e0` | `0x00438A30` | 25B / 10 x86 instructions | 25/25 |
| `Animation::set_field_5dc` | `0x00438A50` | 25B / 10 x86 instructions | 25/25 |

`copy_base` is a real `thiscall` Animation method. It passes the exact
`0x4c0`-byte `AnimationBase` size, source pointer and destination receiver to
the original CRT `memcpy`, then returns with `ret 4`. The wrapper is game-owned
because the original `AnimationFile::apply_template` calls it after selecting
a template at `AnimationFile+0x40+script*0x5e4`; the source method copies only
the embedded base, not the whole 0x5e4-byte template record. The CRT `memcpy`
callee is external and receives no game-owned byte credit. The reconstructed
method name describes the native operation and does not claim the original
source's identifier spelling.

`clear_pending_fields` is a real `thiscall` method. The original pushes null,
restores the Animation receiver in ECX, and calls the setter at `0x00438A50`
first. It repeats that sequence for `0x00438A30`. The two setter bodies take
one stack argument (`ret 4`) and store that callback pointer to the receiver's
`+0x5dc` and `+0x5e0` members respectively. The source-level names describe
those observed roles; this evidence does not claim the original source's
identifier spellings.

`clear_field_570` is a separate `thiscall` leaf that stores zero at
`Animation+0x570`. The existing
[retirement-state analysis](ANIMATION_RETIREMENT_STATE_570_SEMANTICS.md)
independently establishes the lifecycle meaning of that word and its
same-storage `retirement_state` alias.

## Original callers establish game ownership

The original 84-byte `AnimationFile::apply_template` method calls
`clear_field_570` at `+0x0a`, then `clear_pending_fields` at `+0x12`, before
copying the template's 0x5e4-byte Animation base and resetting its timers.
The original 298-byte `AnimationPoolOwner::allocate_animation` method calls
`clear_pending_fields` in both its recycled-animation branch (`+0x6c`) and its
fresh-allocation branch (`+0x111`). These original callers, together with the
Animation receiver and the two concrete callback member stores, establish
that these are game-owned Animation lifecycle operations rather than generic
compiler/runtime helpers.

## Reproduction

The focused native audit is:

```sh
scripts/repo-python scripts/verify-animation-binding-leaves-native.py
```

The strict canonical units are `animation_copy_base`, `animation_clear_pending_fields`,
`animation_clear_field_570`, `animation_set_field_5dc`, and
`animation_set_field_5e0`. The parent `animation_file_apply_template` was also
strictly replayed while checking the original caller sequence. No assembly,
manual opcodes, byte patching, or padding are used.
