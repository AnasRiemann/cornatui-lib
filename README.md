<div align="center">

# cornatui

**A lightweight, header-only C++ library for building retro text UIs in the terminal**
*Colors · Boxes & Tables · Animated Text · Menus · Positioning · Cross-Platform*

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)]()
[![Header-only](https://img.shields.io/badge/header--only-yes-brightgreen)]()

</div>

<br>

<p align="center">
  <sub>Everything you need to dress up a C++ console app — colored text, bordered boxes and tables,<br>a typewriter effect, true RGB color, and precise text positioning — in a single header.</sub>
</p>

---

## Features

- **Boxes & tables** — `str::box()` for a single bordered block of text, `str::table()` for a bordered, row-per-item list, in six border styles: `single`, `bold`, `star`, `hash`, `cross`, `wave`
- **Menus** — `str::ordered_menu()` builds a numbered menu (header + numbered list + selection prompt) in one call, 1D or 2D
- **Three color tiers** — 16 named colors (rang-backed, Windows-safe when `rang.hpp` is available), the full 256-color ANSI palette, and true RGB color via `ans::IntRGB255` or raw `r,g,b`
- **`ans::IntRGB255`** — a small clamped RGB color value type with `.hex()` and `+`/`-` blending, used directly by the colored `box()`/`table()`/`fg_color()`/`bg_color()` overloads
- **`Text` class** for one-off formatting: `bold`, `dim`, `italic`, `underline`, `double_underline`, `curly_underline`, `overline`, `blink`, `rblink`, `reversed`, `conceal`, `crossed`, `uppercase`, `lowercase`, `reverse`, `separate`, `color`, `colorful`, `bg_colorful`, `border`
- **Typewriter animation** via `Text::write()` and `Text::write_colorful()`
- **String utilities** — `lowercase`, `uppercase`, `reverse`, `ltrim`, `rtrim`, `trim`, `ignore_character`, `ignore_spaces`, `get_ascii_only`, `validate_box_content`
- **Text positioning** via `str::translate()`, using either plain padding or raw ANSI cursor-movement codes (`Method::padding` / `Method::ansi`)
- **Screen control** via the `Screen` enum (`off`, `view`, `full`) for `cls()`
- **Terminal bell / beep** via `tui::sound::ring()` (and `tui::sound::beep()` on Windows)
- **Small utilities**: `hr`, `line`, `br`, `space`, `pause`, `cls`, `display_cursor`, `edit_precision`, `check_break_keywords`, `delay_ms`, `init_terminal`
- **Header-only** — drop the files in and go, no build step, no package manager
- Optional **`CORNATUI_DISABLE_WIN32`** macro to compile out the Windows console API code path, and **`CORNATUI_DISABLE_RANG_DOT_HPP`** to compile out the `rang.hpp` dependency (define either *before* including `cornatui.hpp`)

> **API note:** everything that builds structured output (boxes, tables, menus, rules, spacing) lives under `tui::str::*` and *returns a string* — nothing is printed directly. Build up the string you want, then print it once with `std::cout <<`. Only the low-level, single-shot helpers (`fg_color`, `bg_color`, `font_style`, `reset`, `cls`, `pause`, `display_cursor`, `delay_ms`) print straight to a stream from `tui::*`.

---

## Screenshots

|  cornatui test - Git Bash | 

 ![cornatui test](./cornatui_test_screenshots/example_cornatui_demo.png) 


---

## Project Structure

```
cornatui/
├── cornatui.hpp             # The library itself (namespace tui)
├── cornatui_math_ans.hpp    # Random-number / math / IntRGB255 helper used by colorful() and colored box()/table()
├── rang.hpp                 # Vendored third-party library for cross-platform terminal colour (optional)
└── test.cpp                 # Demo — renders a colored box + table menu ("Poincare")
```

Everything lives in `namespace tui`, with string-returning variants under `tui::str`, the animated/interactive class under `tui::Text`, RGB color values under `ans::IntRGB255`, and the terminal-bell helpers under `tui::sound`.

---

## Requirements

- A **C++17**-capable compiler
- [`rang.hpp`](https://github.com/agauniyal/rang) in the include path (optional — only affects the direct-print `fg_color`/`bg_color`/`font_style` helpers; string-returning `tui::str::*` color functions work without it)
- `cornatui_math_ans.hpp` (random-number generation and `ans::IntRGB255`, used by `colorful()`/`bg_colorful()` and the colored `box()`/`table()` overloads)
- On Windows, `<windows.h>` / `<conio.h>` are used automatically unless `CORNATUI_DISABLE_WIN32` is defined before including the header

## Install

Copy the files into your project:

```
your_project/
├── cornatui.hpp
├── cornatui_math_ans.hpp
├── rang.hpp          # optional
└── main.cpp
```

```cpp
#include "cornatui.hpp"
```

## Quick Start

```cpp
#include "cornatui.hpp"

int main()
{
    tui::init_terminal();

    std::cout
        << tui::str::cls()
        << tui::str::translate(
               tui::str::box(
                   "Hello, cornatui!",
                   tui::Border::bold,
                   ans::IntRGB255(220, 250, 255),  // text color
                   ans::IntRGB255(25, 20, 45),     // background color
                   ans::IntRGB255(255, 105, 180),  // border color
                   1                                // padding
               ),
               2, 1
           );

    tui::Text msg = {"I love C++"};
    std::cout << msg.color(5) << "\n";          // blue text
    std::cout << msg.bold() << "\n";            // bold text
    std::cout << msg.colorful(0, 255) << "\n";  // random color per character

    std::cout << tui::str::hr(60, "=", 2);
    tui::pause();
    return 0;
}
```

## Build the Demo

```bash
g++ -std=c++17 -O2 test.cpp -o demo
./demo
```

On Windows this also works from PowerShell, `cmd.exe`, Git Bash, or Windows Terminal (see screenshots above) — the `.gitignore` expects the built binary to be named `test.exe`.

---

## API Reference

### `namespace tui` — low-level, direct-print functions

| Function | Description |
|---|---|
| `cls(mode, ostream)` | Clear the screen (`Screen::off` / `view` / `full`, default `full`) |
| `fg_color(n, ostream)` / `bg_color(n, ostream)` | Set foreground/background color (1–255) — uses `rang` if available, raw ANSI otherwise |
| `font_style(n, ostream)` | Set a text style code (bold, dim, italic, etc.) |
| `reset(ostream)` | Reset all active styling |
| `pause(msg, delay)` | Type out `msg`, then wait for a key/Enter |
| `delay_ms(ms)` | Sleep for `ms` milliseconds |
| `display_cursor(show, ostream)` | Show or hide the terminal cursor |
| `init_terminal()` | Initializes `rang`'s auto-detection if `rang.hpp` is included; on native Windows console (no `rang`) also switches the console to UTF‑8 and enables ANSI (VT) processing |
| `check_break_keywords(input)` | `true` if `input` matches an exit keyword (`"0"`, `"_n"`, `"_f"`, `"_q"`, `"exit"`, `"quit"`, `"break"`, `"false"`) |

### `namespace tui::str` — string-returning functions

| Function | Description |
|---|---|
| `box(text, style, padding)` | Bordered block of text as a string |
| `box(text, style, textColor, bgColor, borderColor, padding)` | Same, colored via `ans::IntRGB255` |
| `table(items, style)` | Bordered, unnumbered list — one row per item, as a string |
| `table(items, style, textColor, bgColor, borderColor)` | Same, colored via `ans::IntRGB255` |
| `ordered_menu(header, items)` | Bordered header + numbered list + selection prompt, as a string (1D or 2D) |
| `ordered_list(items)` / `unordered_list(items)` | Numbered / unnumbered list as a string (1D or 2D table) |
| `fg_color(n)` / `bg_color(n)` | ANSI code as a string (1–255) |
| `fg_color(r,g,b)` / `bg_color(r,g,b)` | Truecolor ANSI code as a string |
| `fg_color(IntRGB255)` / `bg_color(IntRGB255)` | Truecolor ANSI code from an `ans::IntRGB255` value |
| `hr(width, fillChar)` / `hr(width, style, lines)` | Horizontal rule as a string |
| `line(width, fillChar)` / `line(width, style)` | A single repeating-character line, no surrounding newlines (used internally by `hr`/`box`/`table`) |
| `translate(content, x, y, method)` | Place text at column `x` / row `y`, via `Method::padding` (spaces/newlines) or `Method::ansi` (cursor-movement escapes) |
| `br(n, method)` / `space(width, method)` | Blank lines / horizontal spacing, in either method |
| `cls(mode)` | Clear-screen escape sequence as a string |
| `reset()` | Style-reset escape sequence as a string |
| `edit_precision(number, p1, p2)` | Format a `long double` with precision `p1`, then re-set stream precision to `p2` |
| `lowercase(text)` / `uppercase(text)` / `reverse(text)` | Case conversion / character-order reversal |
| `ltrim(text)` / `rtrim(text)` / `trim(text)` | Strip leading / trailing / both-side whitespace |
| `ignore_character(text, ch)` / `ignore_spaces(text)` | Strip a given character / all spaces from a string |
| `get_ascii_only(text)` | Strip non-ASCII bytes from a string |
| `validate_box_content(text)` | Strip control characters and trim, used internally to sanitize `box()`/`table()` input |

### `namespace tui::sound`

| Function | Description |
|---|---|
| `ring(ostream)` | Print the terminal bell character (`\a`) |
| `beep(frequency, durationMS)` | Play a system beep (Windows only, via `Beep()`) |

### `class tui::Text`

Constructed from a string (only ASCII bytes are kept), exposing:

| Method | Description |
|---|---|
| `content()` | The stored (ASCII-filtered) text |
| `color(n)` | Colorize the whole string (1–255) |
| `bold()`, `dim()`, `italic()`, `underline()`, `double_underline()`, `curly_underline()`, `overline()`, `blink()`, `rblink()`, `reversed()`, `conceal()`, `crossed()` | Text styling |
| `uppercase()` / `lowercase()` | Case conversion |
| `reverse()` | Reverse character order |
| `separate(n)` | Insert `n` spaces between characters |
| `colorful(start, end)` / `bg_colorful(start, end)` | Random foreground / background color per character |
| `border(style)` | Wrap the text in a box (equivalent to `str::box(content(), style, 0)`) |
| `write(delay, ostream)` | Typewriter-style print |
| `write_colorful(delay, start, end)` | Typewriter print with random colors |
| `merge(paragraph)` *(static)* | Concatenate a `vector<string>` into one string |

### `struct ans::IntRGB255`

A clamped 0–255 RGB color value, used by the colored `box()`/`table()`/`fg_color()`/`bg_color()` overloads.

| Member | Description |
|---|---|
| `IntRGB255(r, g, b)` | Constructs a color; out-of-range channels (`> 255`) are reset to `0` |
| `red()` / `green()` / `blue()` | Read a channel |
| `hex()` | Uppercase `"#RRGGBB"` string |
| `operator+` / `operator-` | Per-channel add/subtract, clamped to `[0, 255]` |

### Enums

| Enum | Values |
|---|---|
| `tui::Border` | `single` · `bold` · `star` · `hash` · `cross` · `wave` |
| `tui::Screen` | `off` · `view` · `full` |
| `tui::Method` | `padding` · `ansi` — controls how `str::translate()`, `str::br()`, and `str::space()` position text |
| `tui::Page` | `list` · `paragraph` · `confirm` — declared for upcoming paging features; not yet consumed by any function |

---

## Known Limitations

- **No direct-print wrappers for structured output.** Unlike the low-level color/cursor/screen helpers, `box`, `table`, `ordered_menu`, `hr`, and `br` only exist as `tui::str::*` string builders — build the full string first, then print it once. There is currently no `tui::create_border`/`tui::create_page`-style shortcut that prints directly.
- **`str::fg_color(0)` / `str::bg_color(0)` are not a reset.** They return the ANSI code for plain black (`30`/`40`), not `"\033[0m"`. If you want to clear styling, use `tui::str::reset()` (or the direct-print `tui::fg_color(0, ostream)`, which *does* still treat `0` as reset).
- `Text` keeps ASCII characters only (`get_ascii_only`) — no multi-byte Unicode/UTF-8 support in `Text` content yet, even though `init_terminal()` now switches the native Windows console to UTF‑8.
- `Text::separate()` indexes the first character of the (space-stripped) string without checking it isn't empty.
- `cls(Screen::full)` clears scrollback in addition to the visible screen; on Windows this is done via the native console buffer API, but on other platforms it relies on ANSI sequences that not every terminal honors.
- `tui::Page` is defined but not yet wired into any function — reserved for future paging support.
- `test.cpp` currently only renders the initial menu; the eight listed options are not yet dispatched to any functionality.

## Roadmap

Not yet implemented — ideas for future versions:

- [ ] UTF-8 support in `Text`
- [ ] Wire up `Page`-based paging/navigation
- [ ] Wire up the demo menu's eight options to real functionality
- [ ] Automated test suite

## Repository
cornatui repository: [github.com/AnasRiemann/cornatui-lib](https://github.com/AnasRiemann/cornatui-lib.git)
## License

MIT — see [LICENSE](./LICENSE).

## Author

 [**Anas Riemann**](https://github.com/AnasRiemann)