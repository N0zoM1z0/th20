# AnimationFile::spawn_child — complete 604B native reconstruction

The original TH20 v1.00a Steamless executable is SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete function at **`0x00451050`** is **604 bytes / 184 i386
instructions**, a `__thiscall` AnimationFile member returning the
nontrivial `AnimationHandle` by value. Its original function-body SHA-256 is
`7ae6f4a1803e1bc53636ad8dd08447e45071364ccee71f8cc037ef7f30e4c650`.

## Original Animation VM ownership

This is a direct child of the still-NONEXACT 39,470B Animation VM at
`0x0042B5D0`. The VM invokes it for opcodes **0x72, 0x73, 0x74, 0x75,
0x77 and 0x7C**. The first four use flags `0`, `4`, `2` and `6`; opcode
0x77 chooses `0` or `4` from Animation flag bit 18, and opcode 0x7C
chooses `2` or `6`. Opcode **0x76** is a separate 619B recursive-spawn
helper at `0x004512B0`, not this function.

The receiver is the actual `AnimationFile`. Under recursive lock slot 9,
the method increments `field_68`, allocates a real Animation from
`current_animation_pool`, inherits the parent's renderer pointer and layer,
sets the native `0x200` Animation flag, constructs a zero Vector3, applies
`0x40000` according to flag bit 2, and calls the exact
`AnimationFile::bind_animation(animation, script, parent)` method. The
`AnimationHandle` is returned through MSVC's hidden return-object pointer;
this is why the natural source returns `AnimationHandle` by value rather
than accepting a fourth explicit output pointer.

If the inherited renderer pointer is non-null, the two spawn flag bits
select one of the four already-exact Renderer registration methods:

| Flags | Native registration target | Follow-up |
|---:|---|---|
| `6` | `0x0044B890` | Clear Animation mode bits 0–1 |
| `4` | `0x0044B8E0` | Clear Animation mode bits 0–1 |
| `2` | `0x0044B840` | Preserve mode bits |
| `0` | `0x0044B7F0` | Preserve mode bits |

Finally, the method inserts `animation->child_links[0]` immediately after
`parent->child_links[1]` through the original `AnimationChildLinks::operator[]`
and `IntrusiveLink<Animation>::insert_after` methods. This is the actual
parent/child Animation tree protocol, not merely renderer registration.

## Whole-function proof

The independent original PE parser pins the complete 604B body, decodes
**184/184** instructions through `ret 0x10`, and independently recovers
**15 original E8 destinations**:

| Offset | Original destination | Role |
|---:|---:|---|
| `+0x32` | `0x0040C310` | recursive lock registry slot 9 |
| `+0x3B` | `0x0040B730` | lock-guard construction |
| `+0x5C` | `0x0044C9B0` | Animation Pool allocation |
| `+0xB1` | `0x00422DD0` | zero Vector3 construction |
| `+0x124` | `0x004382B0` | parent-aware script binding |
| `+0x12C` | `0x00425CC0` | hidden AnimationHandle construction |
| `+0x162` | `0x0044B890` | Renderer flags 6 |
| `+0x198` | `0x0044B8E0` | Renderer flags 4 |
| `+0x1CD` | `0x0044B840` | Renderer flags 2 |
| `+0x1E6` | `0x0044B7F0` | normal Renderer registration |
| `+0x203`, `+0x21B` | `0x004494B0` | child-link indexed access |
| `+0x22A` | `0x00411EE0` | intrusive child-list insertion |
| `+0x239` | `0x0040B900` | lock-guard destruction |
| `+0x251` | `0x005429EE` | original security-cookie check |

The four original PE HIGHLOW fields are at `+0x06` (EH handler
`0x0056872D`), `+0x15` (security cookie `0x005B25C0`), `+0x2E`
(`process_locks`, `0x005C0240`) and `+0x58` (`current_animation_pool`,
`0x005C0028`).

Pinned MSVC 19.44 x86 C++20 emits the complete **604B** natural member
function. The canonical comparison reports **528/528 ordinary bytes** and
all **76/76 relocation bytes** exact, with zero ordinary-byte differences.
All **19 candidate relocations** solve to the independently recovered
original destinations. The focused verifier is
`scripts/verify-animation-file-spawn-child604-native.py`; the standalone
probe is `scripts/probe-animation-file-spawn-child604.py`. The canonical
unit is `animation_file_spawn_child_604`.

The original **39,470B Animation VM** remains source-absent/NONEXACT.
This exact child-spawn method does not claim any bytes of that parent or of
the separate 619B opcode-0x76 helper.
