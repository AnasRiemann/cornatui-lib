<div align="center">

# cornatui

**A lightweight, header-only C++ library for building retro text UIs in the terminal**
*Colors · Borders · Animated Text · Menus · Positioning · Cross-Platform*

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)]()
[![Header-only](https://img.shields.io/badge/header--only-yes-brightgreen)]()

</div>

<br>

<p align="center">
  <sub>Everything you need to dress up a C++ console app — colored text, bordered menus,<br>a typewriter effect, 256-color/RGB palettes, and precise text positioning — in a single header.</sub>
</p>

---

## Features

- **Ready-made borders** in six styles: `single`, `bold`, `star`, `hash`, `cross`, `wave`
- **Three color tiers** — 16 named colors (rang-backed, Windows-safe when `rang.hpp` is available), the full 256-color ANSI palette, and true RGB color
- **`Text` class** for one-off formatting: `bold`, `dim`, `italic`, `underline`, `double_underline`, `curly_underline`, `overline`, `blink`, `rblink`, `reversed`, `conceal`, `crossed`, `uppercase`, `lowercase`, `reverse`, `separate`, `color`, `colorful`, `bg_colorful`, `borders`
- **Typewriter animation** via `write()` and `write_colorful()`
- **Menus & pages** out of the box — numbered (`ordered_list`) and unnumbered (`unordered_list`) lists, plus 2D/table variants and `create_page()`
- **Text positioning** via `translate()`, using either plain padding or raw ANSI cursor-movement codes (`Method::padding` / `Method::ansi`)
- **Screen control** via the `Screen` enum (`off`, `view`, `full`) for `cls()`
- **Terminal bell / beep** via `tui::sound::ring()` (and `tui::sound::beep()` on Windows)
- **Small utilities**: `hr`, `br`, `space`, `pause`, `cls`, `display_cursor`, `edit_precision`, `check_break_keywords`, `delay_ms`
- **Header-only** — drop the files in and go, no build step, no package manager
- Optional **`CORNATUI_DISABLE_WIN32`** macro to compile out the Windows console API code path (define it *before* including `cornatui.hpp`)

---

## Project Structure

```
cornatui/
├── cornatui.hpp             # The library itself (namespace tui)
├── cornatui_math_ans.hpp    # Random-number / math helper used by colorful()
├── rang.hpp                 # Vendored third-party library for cross-platform terminal colour (optional)
└── test.cpp                 # Interactive demo — colors, borders, animation, text effects, RGB, translate, info screens
```

Everything lives in `namespace tui`, with string-returning variants under `tui::str`, the animated/interactive class under `tui::Text`, and the terminal-bell helpers under `tui::sound`.

---

## Requirements

- A **C++17**-capable compiler
- [`rang.hpp`](https://github.com/agauniyal/rang) in the include path (optional — only affects the direct-print `fg_color`/`bg_color`/`font_style` helpers; string-returning `tui::str::*` color functions work without it)
- `cornatui_math_ans.hpp` (random-number generation used by `colorful()` / `bg_colorful()`)
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
    tui::cls();
    tui::create_border("Hello, cornatui!", tui::Border::bold);
    tui::br();

    tui::Text msg = {"I love C++"};
    std::cout << msg.color(5) << "\n";          // blue text
    std::cout << msg.bold() << "\n";            // bold text
    std::cout << msg.colorful(0, 255) << "\n";  // random color per character

    tui::hr(60, "=", 2);
    tui::pause();
    return 0;
}
```

## Build the Demo

```bash
g++ -std=c++17 -O2 test.cpp -o demo
./demo
```

---

## API Reference

### `namespace tui` — direct-print functions

| Function | Description |
|---|---|
| `cls(mode, ostream)` | Clear the screen (`Screen::off` / `view` / `full`, default `full`) |
| `br(n, ostream)` | Print `n` blank lines |
| `hr(width, fillChar, ostream)` / `hr(width, style, lines, ostream)` | Horizontal rule (single fill char, or a repeating style string) |
| `create_border(text, style, ostream)` | Print text inside a border (`Border`, default `single`) |
| `create_ordered_list(items, ostream)` / `create_unordered_list(items, ostream)` | Numbered / unnumbered list (1D or 2D table) |
| `create_page(header, items, ostream)` | Bordered header + numbered list + a selection prompt (1D or 2D) |
| `fg_color(n, ostream)` / `bg_color(n, ostream)` | Set foreground/background color (1–255) — uses `rang` if available, raw ANSI otherwise |
| `font_style(n, ostream)` | Set a text style code (bold, dim, italic, etc.) |
| `reset(ostream)` | Reset all active styling |
| `pause(msg, delay)` | Type out `msg`, then wait for a key/Enter |
| `delay_ms(ms)` | Sleep for `ms` milliseconds |
| `display_cursor(show, ostream)` | Show or hide the terminal cursor |
| `init_terminal()` | Initialize `rang`'s auto-detection (only relevant if `rang.hpp` is included) |
| `check_break_keywords(input)` | `true` if `input` matches an exit keyword (`"0"`, `"_n"`, `"_f"`, `"_q"`, `"exit"`, `"quit"`, `"break"`, `"false"`) |

### `namespace tui::str` — string-returning variants

| Function | Description |
|---|---|
| `fg_color(n)` / `bg_color(n)` | ANSI code as a string (1–255) |
| `fg_color(r,g,b)` / `bg_color(r,g,b)` | Truecolor ANSI code as a string |
| `hr(width, fillChar)` / `hr(width, style, lines)` | Horizontal rule as a string |
| `border(text, style)` | Bordered text as a string |
| `translate(content, x, y, method)` | Place text at column `x` / row `y`, via `Method::padding` (spaces/newlines) or `Method::ansi` (cursor-movement escapes) |
| `br(n, method)` / `space(width, method)` | Blank lines / horizontal spacing, in either method |
| `cls(mode)` | Clear-screen escape sequence as a string |
| `reset()` | Style-reset escape sequence as a string |
| `ordered_list(items)` / `unordered_list(items)` | Numbered / unnumbered list as a string (1D or 2D table) |
| `create_page(header, items)` | Full page (border + list + prompt) as a string (1D or 2D) |
| `edit_precision(number, p1, p2)` | Format a `long double` with precision `p1`, then re-set stream precision to `p2` |
| `ignore_character(text, ch)` / `ignore_spaces(text)` | Strip a given character / all spaces from a string |
| `get_ascii_only(text)` | Strip non-ASCII bytes from a string |

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
| `border(style)` | Wrap the text in a border |
| `write(delay, ostream)` | Typewriter-style print |
| `write_colorful(delay, start, end)` | Typewriter print with random colors |
| `merge(paragraph)` *(static)* | Concatenate a `vector<string>` into one string |

### Enums

| Enum | Values |
|---|---|
| `tui::Border` | `single` · `bold` · `star` · `hash` · `cross` · `wave` |
| `tui::Screen` | `off` · `view` · `full` |
| `tui::Method` | `padding` · `ansi` — controls how `translate()`, `str::br()`, and `str::space()` position text |
| `tui::Page` | `list` · `paragraph` · `confirm` — declared for upcoming paging features; not yet consumed by any function |

---

## Known Limitations

- `Text` keeps ASCII characters only (`get_ascii_only`) — no multi-byte Unicode/UTF-8 support in text content yet.
- `cls(Screen::full)` clears scrollback in addition to the visible screen; on Windows this is done via the native console buffer API, but on other platforms it relies on ANSI sequences that not every terminal honors.
- `tui::Page` is defined but not yet wired into any function — reserved for future paging support.
- `test.cpp` is an interactive manual demo, not an automated test suite.

## Roadmap

Not yet implemented — ideas for future versions:

- [ ] UTF-8 support in `Text`
- [ ] Wire up `Page`-based paging/navigation
- [ ] Automated test suite

## License

MIT — see [LICENSE](./LICENSE).

## Author

**Anas Riemann**
