<div align="center">

# cornatui

**A lightweight, header-only C++ library for building retro text UIs in the terminal**
*Colors · Borders · Animated Text · Menus · Cross-Platform*

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)]()
[![Header-only](https://img.shields.io/badge/header--only-yes-brightgreen)]()

</div>

<br>

<p align="center">
  <sub>Everything you need to dress up a C++ console app — colored text, bordered menus,<br>a typewriter effect, and 256-color palettes — in a single header.</sub>
</p>

---

## Features

- **Ready-made borders** in five styles: `single`, `bold`, `star`, `hash`, `cross`
- **Three color tiers** — 16 named colors (rang-backed, Windows-safe), the full 256-color ANSI palette, and true RGB color
- **`Text` class** for one-off formatting: `bold`, `italic`, `underline`, `blink`, `dim`, `reverse`, `uppercase`, `lowercase`, color, borders
- **Typewriter animation** via `write()` and `write_colorful()`
- **Menus & pages** out of the box (`create_list`, `create_page`)
- **Small utilities**: `hr`, `br`, `pause`, `cls`, `display_cursor`, `format_number`, `check_break_keywords`
- **Header-only** — drop the file in and go, no build step, no package manager

---

## Project Structure

```
cornatui/
├── cornatui.hpp             # The library itself (namespace tui)
├── cornatui_math_ans.hpp    # Random-number helper used by colorful()
├── rang.hpp                 # Vendored third-party library for cross-platform terminal colour (optional)
└── test.cpp                 # Interactive demo — color list, borders, animation, text effects
```

Everything lives in `namespace tui`, with string-returning variants under `tui::str` and the animated/interactive class under `tui::Text`.

---

## Requirements

- A **C++17**-capable compiler
- [`rang.hpp`](https://github.com/agauniyal/rang) in the include path (optional — see [Colors](#colors-rang-vs-raw-ansi) above)
- `cornatui_math_ans.hpp` (random-number generation for `colorful()`)

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
    tui::create_border("Hello, cornatui!", tui::border::bold);
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
| `cls()` / `Cls()` | Clear the screen |
| `br(n)` | Print `n` blank lines |
| `hr(width, style, lines)` | Horizontal rule |
| `create_border(text, style)` | Print text inside a border |
| `create_list(items)` / `create_page(header, items)` | Numbered interactive list / page |
| `fg_color(n)` / `bg_color(n)` | Set foreground/background color (1–255) |
| `pause(msg, delay)` | Wait for Enter, typing the prompt out first |
| `delay_ms(ms)` | Sleep for `ms` milliseconds |
| `display_cursor(show)` | Show or hide the cursor |
| `check_break_keywords(input)` | True if `input` is an exit keyword (`exit`, `quit`, `0`, …) |
| `format_number(val, precision)` | Format a decimal, trimming trailing zeros |

### `namespace tui::str` — string-returning variants

| Function | Description |
|---|---|
| `fg_color(n)` / `bg_color(n)` | ANSI code as a string (1–255) |
| `fg_color(r,g,b)` / `bg_color(r,g,b)` | Truecolor ANSI code as a string |
| `hr(width, style, lines)` | Horizontal rule as a string |
| `create_border(text, style)` | Bordered text as a string |

### `class tui::Text`

Constructed from a string (ASCII-only content is kept), exposing:

| Method | Description |
|---|---|
| `content()` | The original text |
| `color(n)` | Colorize the whole string |
| `bold()`, `dim()`, `italic()`, `underline()`, `blink()` | Text styling |
| `uppercase()` / `lowercase()` | Case conversion |
| `reverse()` | Reverse character order |
| `separate(n)` | Insert spacing between characters |
| `colorful(start, end)` | Random color per character |
| `border(style)` | Wrap the text in a border |
| `write(delay)` | Typewriter-style print |
| `write_colorful(delay, start, end)` | Typewriter print with random colors |

### `enum class tui::border`

`single` · `bold` · `star` · `hash` · `cross`

---

## Known Limitations

- `Text` keeps ASCII characters only (`read_ascii_only`) — no multi-byte Unicode/UTF-8 support in text content yet.
- `cls()` (which also clears scrollback) doesn't work in every terminal.

## Roadmap

Not yet implemented — ideas for future versions:

- [ ] UTF-8 support in `Text`
- [ ] Additional border styles
- [ ] Automated test suite

## License

MIT — see [LICENSE](./LICENSE).

## Author

**Anas Riemann**
