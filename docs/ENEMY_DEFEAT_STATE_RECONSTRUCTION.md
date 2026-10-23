# Defeat feedback, reward and indexed-script protocols

CORE/EXACT-156 maintains the complete state dependencies of the accepted
[Enemy defeat caller](ENEMY_DEFEAT_RECONSTRUCTION.md). Eleven strict units add
666 comparison bytes, including six authored roots / 493 code bytes. The full
Feedback update has semantic source and remains nonexact at 114/native115.
Current totals and protected products are in [the handoff](RE_HANDOFF.md).
Member offsets below are hexadecimal; gameplay constants use decimal.

## Feedback storage and update

The maintained 0x5C PlayerFeedback now derives from the actual sixteen-byte Timer
at offset zero; its other Timer members remain +10 and +20. Raw words +30/+34/
+38/+3C, Vector3 +40, handle +4C, byte +50, player index +54 and Context +58
retain their observed x86 positions. The complete 133-byte constructor still
strictly replays. Construction alone did not distinguish a base from a first
member. Ordinary forwarding/update calls corroborate base inheritance: the old
composition candidate introduced an extra receiver temporary and five bytes.
The original class and forwarding-operation spellings remain unknown.

The complete forwarding operation at 0x45C300 delegates to the existing Timer
integer addition at 0x4297A0. Both complete bodies strictly replay, respectively
26 and 33 bytes. The latter converts the signed integer to float before calling
the accepted Timer::add(float); the actual clock/mode/initialization behavior is
shared. Other native callers pass Timer-backed subobjects at +1930 and +2C.
Physical folding does not establish original source ownership or authorship;
both small operations retain pending origin classification.

The whole 115-byte native update at 0x4FB3A0:

1. Advances the actual Timer base by its signed argument.
2. Assigns 30 only when the resulting signed current time is greater than 30.
3. Increments raw counter +38 modulo 2^32 and copies it to +30.
4. Replaces +3C only when its signed value is less than signed +30.

The maintained word storage uses defined unsigned wrapping and explicit signed
comparison views. The separate counter getter continues to read +38 and folds
to its existing physical 17-byte unit without duplicate credit. The other
Timers and owner fields are untouched.

The natural shared update emits 114 bytes. The complete native body has an
additional NOP at 0x4FB3B5 after the first call. Correct per-source profile,
isolated compilation and an explicit member-call variant retain this gap.
The call/emission contract is unresolved; this complete function has no canonical
exact unit or byte credit. Its custom Player/Enemy timing and counter protocol
independently establishes authored origin. No target extent is shortened.

## Reward channels and complete dispatch

The actual PlayerRecord limit getter at 0x4AAFA0 returns 1,000. Each channel update
adds the signed argument modulo 2^32, compares the signed result against that
limit, then calls the getter again when saturating. A negative result is retained.
Only a threshold-reaching update can replace a negative field98; an existing
nonnegative selection is preserved, including values outside 0..3.

| Channel | Native update | First selection in field98 |
| --- | --- | ---: |
| +64 | 0x4A9EC0 | 0 |
| +68 | 0x4A9D80 | 1 |
| +6C | 0x4A9F20 | 2 |
| +70 | 0x4A9E60 | 3 |

All four complete 83-byte roots strictly replay. Their game-specific channel and
first-selection behavior establishes authored origin separately from emission.
The sixteen-byte limit getter retains pending origin classification.

PlayerRecord::add_reward at 0x4A9DE0 routes kind pairs 0/1, 2/3, 4/5 and 6/7 to
the four channels. Every other signed kind, including negatives, takes channel
+64. Its complete contribution is 95 ordinary bytes, one alignment NOP and the
eight-entry / 32-byte table. The unit records `size = 95` and `compare_size = 128`;
authored code and complete comparison coverage remain separate.

The table and all code replay together. Function-local COFF labels independently
bind the table at +96 and case heads at +31/+46/+61/+76 to the reconciled native
control-flow roles. No destination is solved from the field under comparison.

## Indexed ECL selection

| Complete method | Native entry | Bytes |
| --- | --- | ---: |
| EclManager::set_subroutine_index | 0x540530 | 25 |
| EclLoader::select_index | 0x540230 | 66 |
| EclManager::select_subroutine_index | 0x5401D0 | 40 |

The direct setter writes the actual current runtime's subroutine word. The
loader selector publishes itself on the Manager, writes the full signed index,
clears offset, writes positive-zero time and returns integer zero. It performs
no name/table lookup or bounds validation. Main and alternate current runtimes
are both valid receivers. Other frame state and the loader's borrowed resources
remain unchanged. The Manager wrapper caches its loader before forwarding.

All three complete roots strictly replay. The loader's custom ECL state protocol
establishes authored origin; the setter and routing wrapper retain pending origin
classification. Selection does not reset or execute the VM. The defeat caller
uses the maintained reset and selection bodies before its separate tick boundary.

## Actual-owner verification

The public O2/UBSan defeat fixture now calls the real Feedback update, reward
dispatcher/updates, ECL reset and indexed selectors. Four former captures are
removed. Its independent models and complete owner images pass:

- 38,400 Feedback cases over clock/null source, modes, initialization, signed
  Timer cap, full counter wrapping and signed maximum behavior.
- 8,064 reward cases over every channel, all dispatch pairs/defaults, signed
  extremes, upper saturation and first-selection preservation.
- 84 indexed-selection cases over main/alternate runtime, loader rebinding,
  full-width indices and positive zero, with complete loader/frame preservation.
- 10,240 complete defeat combinations, eight remaining external-call failures
  and five recursive topology cases. Later failures preserve real committed
  Feedback/reward state; script27C clears only after tick returns.

The existing guarded Player storage/pool fixture also passes with the actual
Timer base. Script stacks are reserved before the defeat matrix, and all owner
pointers are live. Timer conversion inputs are finite and int32-representable.
Standalone Feedback tests cover all counter bit patterns; the defeat multiplier
path retains its nonnegative-count domain. Resource-free startup and remaining
sound/animation/drop/Item/VM execution captures delimit runtime integration.

## Bounded build, evidence and retirement

Three headers and three implementation files change. Captured includes select
44 providers / 317 prior units; all fresh builds and strict replays pass. The
other 120 providers reuse valid evidence. Sixteen generated literal-name changes
retain full data and canonical roles. Complete EH support for 38 affected parents
is unchanged across 76 whole code/data sections, including relocation roles,
addends and local function labels; their prior independent bindings are reused.
Eleven new units pass their own canonical replay. No full CI or unfiltered
whole-graph replay is run.

Private evidence under `.analysis/` includes `core156-*native.asm`,
`core156-timer-wrapper-callers.txt`, `core156-independent-bindings.json`,
`core156-feedback-emission.json`, affected/new strict reports, EH reuse audit,
actual-owner test logs and graph audit. `core156-pre-state-inputs.json.gz` and
`core156-pre-registration-ledgers.json.gz` retain authentic originals. The
`core156-probe-v1-original-inputs.json.gz`, `core156-probe-v2-original-inputs.json.gz`,
`core156-probe-final-original-inputs.json.gz` and
`core156-member-call-original-inputs.json.gz` archives retain all rejected/current
probe texts and receipts. Cleanup verifies protected hashes with zero extra
build or replay invocations; current paths are in the handoff.
