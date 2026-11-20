# ScreenInf 82B solid-alpha update — strict native reconstruction

The original callback at `0x00424460` is the 82-byte ScreenInf solid-alpha update. Its complete natural C++ source is `src/ScreenSolidUpdate82.cpp`.

It first writes alpha `0xFF`, then checks the actual ScreenInf Timer against the configured duration. Expiration returns `7`; otherwise the Timer's original postfix increment runs and the callback returns `1`.

The canonical unit `screen_solid_update_82` verifies all 82 bytes and both original E8 relocations (`Timer::at_least` and Timer postfix increment). The independent native audit pins the complete original function hash and both call targets.
