# Animation retirement state at +0x570

The Animation word at `+0x570` is a lifecycle state, not an opaque renderer
field. The original member spelling `field_570` remains available for the
already-exact `Animation::clear_field_570` function and its established
mangled symbol. A same-storage union alias, `retirement_state`, is used by the
renderer and retirement consumers.

Observed values and transitions:

- `0`: live/eligible. The active-list update path calls `Animation::update()`.
- `1`: marked for retirement. File detachment and recursive retirement
  marking set this value; the list update path queues the node for retirement.
- `2`: queued for retirement. The pending-retirement path appends the
  animation's +`0x53c` link once, then stores state 2 to prevent duplicate
  enqueueing.

The renderer rejects any nonzero retirement state before issuing draw calls.
Pool construction/reset and template application restore state 0. These
independent producers and consumers establish the lifecycle meaning across
file detach, active-list update, recursive marking, queue insertion, allocation,
and rendering. Both names are the same 32-bit member at +`0x570`; no storage
or padding changed. The original exact `clear_field_570` symbol is preserved.
