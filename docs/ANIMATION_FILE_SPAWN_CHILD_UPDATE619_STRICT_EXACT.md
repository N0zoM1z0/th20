# AnimationFile::spawn_child_and_update — complete 619B native reconstruction

The original TH20 v1.00a Steamless executable is SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete function at **`0x004512B0`** is **619 bytes / 186 i386
instructions**, a `__thiscall` AnimationFile member returning
`AnimationHandle` by value. The original whole-body SHA-256 is
`63f83e1057f2c7771b7b095f0b8c75e4a9e7c7f3d1f47ef0f40c56c8bb0d3a3e`.

## Original VM role

The 39,470B Animation VM at `0x0042B5D0` invokes this helper for opcodes
**0x76 and 0x78**. This is the recursive child-spawn variant, distinct from
the 604B `AnimationFile::spawn_child` used by opcodes 0x72-0x75, 0x77 and
0x7C. The latter inserts the new Animation into the parent's child list;
this 619B variant instead applies a template, inherits the parent transform,
executes the new Animation's VM immediately, then registers it with the
Renderer.

## Exact behavior

1. Acquire recursive lock registry slot 9, increment `AnimationFile+0x68`,
   and allocate a new Animation from `current_animation_pool`.
2. Apply the selected file template through the existing exact
   `AnimationFile::apply_template` method.
3. Inherit the parent's renderer pointer and layer. Set Animation flag
   `0x200`, copy parent flag bit 24, and set/clear `0x40000` from spawn flag
   bit 2.
4. Compute the parent's raw world position with the existing exact
   `0x0044CB80` recursive raw-position helper and write it to the child's
   `vector_5bc`.
5. Copy the parent's `base.vector_38` into the child's `base.vector_38`,
   and the parent's `base.vector_2c` into the child's `base.vector_484`.
6. Execute the new Animation immediately by calling the original
   `Animation::update` at `0x0042B5D0`. This callee is the 39,470B
   NONEXACT VM; its call target is preserved exactly but its bytes are not
   claimed here.
7. Return an `AnimationHandle` by value. If the inherited Renderer exists,
   choose the same four registration modes as the 604B child-spawn helper:
   flags 6, 4, 2 or 0. Modes 6 and 4 clear Animation mode bits 0–1.

The source calls the actual `Animation::world_position_for_spawn` member,
which is independently reconstructed and whole-function exact at
`0x0044CB80`; no derived ABI view or duplicate 236B implementation is used.

## Whole-function proof

The independent original PE parser pins all **619 bytes**, decodes
**186/186** instructions through `ret 0x10`, and independently recovers
13 E8 calls:

| Offset | Original destination | Role |
|---:|---:|---|
| `+0x32` | `0x0040C310` | recursive lock registry slot 9 |
| `+0x3B` | `0x0040B730` | lock-guard construction |
| `+0x5C` | `0x0044C9B0` | Animation Pool allocation |
| `+0x7B` | `0x00438B70` | file template application |
| `+0x124` | `0x0044CB80` | inherited raw world position |
| `+0x16F` | `0x0042B5D0` | recursive child Animation VM update |
| `+0x177` | `0x00425CC0` | hidden AnimationHandle construction |
| `+0x1AD` | `0x0044B890` | Renderer flags 6 |
| `+0x1E3` | `0x0044B8E0` | Renderer flags 4 |
| `+0x219` | `0x0044B840` | Renderer flags 2 |
| `+0x232` | `0x0044B7F0` | normal Renderer registration |
| `+0x248` | `0x0040B900` | lock-guard destruction |
| `+0x260` | `0x005429EE` | original security-cookie check |

The four original PE HIGHLOW fields are at `+0x06` (EH handler
`0x0056824D`), `+0x15` (security cookie `0x005B25C0`), `+0x2E`
(`process_locks`, `0x005C0240`) and `+0x58` (`current_animation_pool`,
`0x005C0028`).

Pinned MSVC 19.44 x86 C++20 emits the complete **619B** natural member
function. The canonical comparison reports **551/551 ordinary bytes** and
all **68/68 relocation bytes** exact, with zero ordinary-byte differences.
All **17 candidate relocations** solve to the original destinations. The
focused verifier is `scripts/verify-animation-file-spawn-child-update619-native.py`;
the standalone probe is `scripts/probe-animation-file-spawn-child-update619.py`.
The canonical unit is `animation_file_spawn_child_update_619`.

The original **39,470B Animation VM** remains source-absent/NONEXACT. This
exact 619B child-spawn method does not claim any bytes of that parent.
