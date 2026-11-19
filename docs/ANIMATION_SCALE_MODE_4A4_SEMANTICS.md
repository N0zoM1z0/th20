# Animation scale mode at +0x4A4

`AnimationBase::flags` begins at `Animation+0x498`; its byte at `+0x0c`
(absolute Animation offset `+0x4A4`) selects how geometry is scaled against
`window_state.scale`.

The observed producers and consumers support the contextual name
`scale_mode`:

- `AnimationParameters` initializes the byte to 1 for the normal scaled path.
- Position transformation treats modes 1/3 as full window scale and 2/4 as
  half window scale.
- Geometry generation treats modes 1 and 2 as full/half scale for its
  generated radii.
- Draw Boss, mode-8 drawing, and corner projection/rotation treat modes 1/5
  as full scale and 2/6 as half scale.

The original `field_0c` spelling remains as a same-byte, same-width bitfield
union alias. The byte is not widened, masked, or repacked; `AnimationFlags`
remains 0x20 bytes, and the following byte's asserted offset pins this slot at
0x0c. The exact values are still kept as byte constants because the
consumer-specific mode families are not fully unified into a single enum yet.
