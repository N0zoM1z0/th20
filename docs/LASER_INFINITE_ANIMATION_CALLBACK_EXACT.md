# Infinite Laser Animation script callback — exact native boundary

The callback at `0x004CF550` receives an `Animation*` and an integer script
parameter. The first Animation stores its owning `Laser*` in `user_data`. The
callback reads the Laser family type and color, checks the signed first word
of that BulletStyle's first color record, and, when nonnegative, remaps the
requested parameter through the selected color record. Otherwise it returns
the original parameter.

The natural implementation in
`src/LaserInfiniteAnimationCallback.cpp` strictly replays **105/105 bytes**.
Both original absolute references to `bullet_styles` resolve to `0x005C06A8`;
all 97 ordinary bytes and both relocation destinations match.
