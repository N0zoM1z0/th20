# Window creation and window procedure (CLAUDE/EXACT-002)

Four functions are strict exact, 2,154 credited bytes in total:

| Address | Size | Function | Source |
| --- | --- | --- | --- |
| `0x0041CCF0` | 905 | `WindowState::create_window(HINSTANCE)` | `src/WindowCreation.cpp` |
| `0x0041D350` | 1,168 (+380 table bytes) | `window_procedure` (stdcall WNDPROC) | `src/WindowCreation.cpp` |
| `0x0041D0A0` | 25 | `Graphics::reference_rasterizer_enabled` | `src/GraphicsConfiguration.cpp` |
| `0x0041D0F0` | 56 | `Graphics::uses_desktop_display_mode` | `src/GraphicsConfiguration.cpp` |

## Window creation

The only caller is the WinMain body at `0x0041E7D0`, which passes
`window_state`. The routine selects the Japanese or English title by
`is_japanese_user_locale()` and registers the zeroed `"BASE"` class with
`BLACK_BRUSH`, `IDC_ARROW` and the window procedure. It then copies
`configuration.saved_display_mode` into WindowState and writes
`presentation.Windowed = mode >= 3`. The `unlimited` flag is set when
frame skip is 0 and presentation mode is 2. Afterwards it resets the four
repeat counters (15, 12, 12, 8), clears `input_latch` and calls
`compute_layout(1)`. It creates one of three windows: a `WS_POPUP|WS_VISIBLE`
fullscreen window, an app-window popup for modes 8 and 9, or a framed
`0x10CB0000` window at the saved position. The window rectangle and handle
are published to `process_graphics`.

Native shape facts that the source keeps:

- `repeat` is a C array. The four `imul/shl` constant-index address
  computations do not occur with `std::array::operator[]`.
- The return is `if (window == nullptr) return 1; return 0;`. Both
  `return window == nullptr;` and the ternary form add a stack temporary.
- The title must use `\u` escapes. The profile has no `/utf-8`, and a raw
  UTF-8 literal compiles to different bytes. The native wide literal at
  `0x0056CB00` is `東方錦上京　～ Fossilized Wonder. ver 1.00c`.

## Window procedure

There is one `switch (message)`. MSVC split it at `0x1C` into byte-indexed
tables for 5..0x14 and 0x20..0x112. The case bodies follow source order:
ERASEBKGND, PAINT, ACTIVATEAPP, DISPLAYCHANGE, SYSCOMMAND, SIZE, SYSKEYDOWN,
SETCURSOR, CLOSE. Alt+Enter (`WM_SYSKEYDOWN`/`VK_RETURN`) and maximize toggle
between fullscreen and windowed display modes. Modes 8 and 9 go back to the
windowed mode selected by `configuration.scale_choice`.

The native body contains three unreachable `jmp` instructions: after the
PAINT and DISPLAYCHANGE breaks, and before the single `SIZE_MAXIMIZED` label.
A second `break;` reproduces each one. An empty `default: break;` does not,
because the dispatch then targets the label instead of the switch end (a
small locked-compiler probe showed this; it was not retained). The orphan breaks
probably remain from case bodies removed in the original source.

The SIZE mode switch is `case 3, case 4, case 5/default, case 6`. Without the
explicit `case 5:` label, MSVC emits a compare chain instead of the native
four-entry table.

## Folded callees

`Graphics::windowed()` (`0x00415800`, `presentation.Windowed`) and
`WindowState::set_window()` (`0x004117A0`) compile byte-identical to bodies
already credited under other names. No duplicate units were added.

## Replay

`WindowState.hpp` and `Graphics.hpp` both changed. A source-filtered replay of
their 89-source include closure gives 182/182 exact units in 89 cold objects.
