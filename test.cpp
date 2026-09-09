// cornatui — feature demo
//
// A guided, menu-driven tour of everything cornatui.hpp currently offers:
// colors, boxes & tables, text styling, positioning, string utilities,
// and an "INFO" section about the library and its author.
//
// Build:  g++ -std=c++17 -O2 demo.cpp -o demo

// #define CORNATUI_DISABLE_WIN32

#include "cornatui/cornatui.hpp"

using namespace tui;

// ---- shared color theme used consistently across every screen ----
namespace theme
{
    const ans::IntRGB255 text_color(ans::get_random_number(180, 240), ans::get_random_number(180, 240), ans::get_random_number(180, 240));
    const ans::IntRGB255 bg_color(ans::get_random_number(10, 30), ans::get_random_number(15, 35), ans::get_random_number(20, 40));
    const ans::IntRGB255 accent_color(ans::get_random_number(200, 250), ans::get_random_number(190, 245), ans::get_random_number(200, 250));
}

namespace demo
{

    const std::vector<std::string> main_menu =
        {
            "Colors           [ 16 named / 256 palette / IntRGB255 ]",
            "Boxes & Tables   [ str::box , str::table , str::*_menu ]",
            "Text Effects     [ tui::Text class ]",
            "Positioning      [ str::translate , str::br , str::space ]",
            "String Utilities [ trim / case / reverse / etc.. ]",
            "INFO             [ about cornatui , license , compatibility ]",
    };

    void run();

    void colors_palette();
    void colors_transformations();
    void colors_math();
    void boxes_and_borders();
    void tables_and_menus();
    void text_effects();
    void positioning();
    void string_utilities();

    namespace info
    {
        void about();
        void license();
        void compatibility();
        void menu();
    }

    // ---- small helpers shared by every section ----

    void header(const std::string &title)
    {
        std::cout
            << str::cls()
            << str::box(title, Border::bubble, theme::text_color, theme::bg_color, theme::accent_color, 0)
            << str::fg_color(theme::accent_color)
            << str::hr(100, "=", 2)
            << str::reset;
    }

    void footer()
    {
        std::cout << str::fg_color(theme::accent_color) << str::hr(100, "=", 2) << str::reset;
        pause();
    }

    std::string prompt_range(size_t count)
    {
        return " # Select option [1-" + std::to_string(count) + "] , to exit [0] |> option -> ";
    }

    std::string menu_frame()
    {

        std::vector<std::string> list = tui::str::prefix_each(demo::main_menu);

        return str::translate(
            str::box(" Cornatui |> Developed By  A  n  a  s  R  i  e  m  a  n  n ", Border::bold,
                     theme::text_color, theme::bg_color, theme::accent_color, 1) +
                str::fg_color(theme::text_color) + str::table(list, Border::mix, theme::text_color, theme::bg_color, theme::accent_color, 1) + str::fg_color(theme::accent_color) + str::hr(90, "=", 2) + str::fg_color(theme::text_color) + prompt_range(main_menu.size()),
            2, 1);
    }

} // namespace demo

int main()
{
    init_terminal();
    display_cursor(false);

    // single clean splash frame — no artificial flicker loop
    std::cout << str::cls() << demo::menu_frame() << std::flush;
    time::delay_ms(400);

    demo::run();

    display_cursor(true);
    tui::restore_terminal();
    return 0;
}

namespace demo
{

    void run()
    {
        std::string option;

        while (true)
        {
            std::cout << str::cls() << menu_frame();

            display_cursor(true);
            std::cin >> option;
            std::cout << str::reset;
            display_cursor(false);

            if (option == "1")
            {
                colors_palette();
                colors_transformations();
                colors_math();
            }
            else if (option == "2")
            {
                boxes_and_borders();
                tables_and_menus();
            }
            else if (option == "3")
                text_effects();
            else if (option == "4")
                positioning();
            else if (option == "5")
                string_utilities();
            else if (option == "6")
                info::menu();
            else if (check_break_keywords(option))
                break;
        }
    }

    // ---------------------------------------------------------------- colors --

    void colors_palette()
    {
        std::ostringstream os;
        header("Colors  [ 256 palette ] ( str::fg_color / str::bg_color )");

        for (unsigned int i = 0; i < 256; i++)
        {
            os << str::fg_color(i) << " #" << std::setfill('0') << std::setw(3) << i << " " << str::reset;
            if ((i + 1) % 16 == 0)
                os << str::br();
        }
        os << str::br();
        for (unsigned int i = 0; i < 256; i++)
        {
            os << str::bg_color(i) << " #" << std::setfill('0') << std::setw(3) << i << " " << str::reset;
            if ((i + 1) % 16 == 0)
                os << str::br();
        }

        std::cout << os.str();
        footer();
    }

    void colors_transformations()
    {
        std::ostringstream os;
        header("Color Transformations  [ lerp / scale / inverse / contrast ]");

        os << "RGB Gradient  ( IntRGB255::lerp , red -> blue ):\n";
        ans::IntRGB255 from(255, 0, 0), to(0, 0, 255);
        const int steps = 64;
        for (int row = 0; row < 4; row++)
        {
            for (int i = 0; i < steps; i++)
            {
                double t = static_cast<double>(i) / (steps - 1);
                os << str::bg_color(from.lerp(to, t)) << " " << str::reset;
            }
            os << str::br();
        }
        os << str::br();

        os << "Brightness  ( IntRGB255::scale , x0.2 -> x1.8 ):\n";
        ans::IntRGB255 base(0, 140, 255);
        for (double factor = 0.2; factor <= 1.8; factor += 0.2)
        {
            os << str::fg_color(base.scale(factor))
               << " x" << std::fixed << std::setprecision(1) << factor << " "
               << str::reset;
        }
        os << str::br() << str::br();

        os << "Inverse & Contrast  ( IntRGB255::inverse / contrast ):\n";
        ans::IntRGB255 samples[] = {
            {230, 30, 30}, {30, 200, 60}, {40, 60, 220}, {230, 220, 40}, {20, 20, 20}, {235, 235, 235}};
        for (const auto &c : samples)
        {
            ans::IntRGB255 inv = c.inverse();
            os << str::bg_color(c) << str::fg_color(c.contrast())
               << " " << c.to_hex() << " " << str::reset
               << "  ->  "
               << str::bg_color(inv) << str::fg_color(inv.contrast())
               << " " << inv.to_hex() << " " << str::reset
               << str::br();
        }

        std::cout << os.str();
        footer();
    }

    void colors_math()
    {
        std::ostringstream os;
        header("Color Math  [ to_ansi256 / hex / distance / operators ]");

        os << "Truecolor -> ANSI256:\n";
        ans::IntRGB255 ansiSamples[] = {
            {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 165, 0}, {128, 0, 128}, {0, 255, 255}};
        for (const auto &c : ansiSamples)
        {
            unsigned int idx = c.to_ansi256();
            os << str::fg_color(c) << " " << c.to_hex() << " " << str::reset
               << "  ≈  "
               << str::fg_color(idx) << " #" << std::setfill('0') << std::setw(3) << idx << " " << str::reset
               << str::br();
        }
        os << str::br();

        os << "Hex Roundtrip  ( to_hex / from_hex ):\n";
        const char *hexes[] = {"#FF5733", "#33FF57", "#3357FF", "#F1C40F", "#8E44AD"};
        for (const char *h : hexes)
        {
            ans::IntRGB255 c = ans::IntRGB255::from_hex(h);
            os << str::bg_color(c) << "   " << str::reset
               << " " << h << " -> " << c.to_hex()
               << str::br();
        }
        os << str::br();

        os << "Distance  ( similarity between two colors ):\n";
        ans::IntRGB255 base(255, 0, 0);
        ans::IntRGB255 candidates[] = {{250, 10, 10}, {200, 50, 0}, {0, 255, 0}, {128, 0, 0}};
        for (const auto &c : candidates)
        {
            os << str::fg_color(base) << " " << base.to_hex() << " " << str::reset
               << " <-> "
               << str::fg_color(c) << " " << c.to_hex() << " " << str::reset
               << "  d = " << std::fixed << std::setprecision(2) << base.distance(c)
               << str::br();
        }
        os << str::br();

        os << "Arithmetic  ( operator+ / operator- ):\n";
        ans::IntRGB255 a(200, 60, 20), b(40, 100, 220);
        auto swatch = [&](const std::string &label, const ans::IntRGB255 &c)
        { os << str::fg_color(c) << " " << label << " " << c.to_hex() << " " << str::reset << str::br(); };
        swatch("A    ", a);
        swatch("B    ", b);
        swatch("A + B", a + b);
        swatch("A - B", a - b);

        std::cout << os.str();
        footer();
    }

    // ------------------------------------------------------- boxes / tables ---

    void boxes_and_borders()
    {
        std::ostringstream os;
        header("Boxes & Border Styles  ( str::box )");

        std::vector<std::pair<std::string, Border>> styles =
            {
                {"single", Border::single}, {"bold", Border::bold}, {"star", Border::star}, {"hash", Border::hash}, {"cross", Border::cross}, {"wave", Border::wave}, {"retro", Border::retro}};
        for (const auto &s : styles)
            os << str::box(s.first, s.second);

        std::cout << os.str() << tui::str::br();
        footer();
    }

    void tables_and_menus()
    {
        std::ostringstream os;
        header("Tables & Menus  ( str::table , str::ordered_menu )");

        std::vector<std::string> rows = {"Row one", "Row two is a little longer", "Row three"};
        os << str::table(rows, Border::cross)
           << str::table(rows, Border::hash, theme::text_color, theme::bg_color, theme::accent_color)
           << str::br();

        std::cout << os.str();
        footer();
    }

    // ------------------------------------------------------------ Text class --

    void text_effects()
    {
        header("Text Effects  ( tui::Text )");
        Text message = {"i love cornatui!"};

        std::vector<std::string> rows =
            {
                "content()            -> " + message.content(),
                "color(5)             -> " + message.color(5),
                "lowercase()          -> " + message.lowercase().content(),
                "uppercase()          -> " + message.uppercase().content(),
                "reverse()            -> " + message.reverse().content(),
                "bold()               -> " + message.bold(),
                "dim()                -> " + message.dim(),
                "italic()             -> " + message.italic(),
                "underline()          -> " + message.underline(),
                "double_underline()   -> " + message.double_underline(),
                "curly_underline()    -> " + message.curly_underline(),
                "overline()           -> " + message.overline(),
                "blink()              -> " + message.blink(),
                "reversed()           -> " + message.reversed(),
                "crossed()            -> " + message.crossed(),
                "separate(2)          -> " + message.separate(2).content(),
                "colorful(50,220)     -> " + message.colorful(50, 220),
                "bg_colorful()        -> " + message.bg_colorful(),
            };

        std::cout << str::unordered_menu_list(rows);
        footer();
    }

    // ------------------------------------------------------------- positioning --

    void positioning()
    {
        header("Positioning  ( str::translate , str::br , str::space )");

        std::cout << "Normal text, no offset\n\n";
        std::cout << str::translate("Method::padding, x=10 y=1\nsecond line", 10, 1, Method::padding);
        std::cout << "\n";
        std::cout << str::translate("Method::ansi, x=20 y=1\nsecond line", 20, 1, Method::ansi);
        std::cout << "\n\n";
        std::cout << "str::space(10) between brackets: [" << str::space(10) << "]\n";
        std::cout << "str::br(2) inserts two blank lines below this one:" << str::br(2);
        std::cout << "  # tui::Screen (off / view / full) controls how much cls() clears -\n"
                     "  # this whole page was drawn with the default str::cls(Screen::full).\n\n";
        footer();
    }

    // -------------------------------------------------------- string utilities --

    void string_utilities()
    {
        header("String Utilities  ( tui::str::* )");
        std::string sample = " Hello, cornaTUI! ";

        std::vector<std::string> rows =
            {
                "input                          -> [" + sample + "]",
                "trim(input)                    -> [" + str::trim(sample) + "]",
                "ltrim(input)                   -> [" + str::ltrim(sample) + "]",
                "rtrim(input)                   -> [" + str::rtrim(sample) + "]",
                "lowercase(input)               -> [" + str::lowercase(sample) + "]",
                "uppercase(input)               -> [" + str::uppercase(sample) + "]",
                "reverse(input)                 -> [" + str::reverse(sample) + "]",
                "ignore_spaces(input)           -> [" + str::ignore_spaces(sample) + "]",
                "ignore_character(input, 'l')   -> [" + str::ignore_character(sample, 'l') + "]",
                "get_ascii_only(input)          -> [" + str::get_ascii_only(sample) + "]",
                "validate_box_content(input)    -> [" + str::validate_box_content(sample) + "]",
                "center(input, 30, '~')         -> [" + str::center(sample, 30, '~') + "]",
                "truncate(input, 10)            -> [" + str::truncate(sample, 10) + "]",
                "to_scientific(123456789.0, 3)  -> [" + str::to_scientific(123456789.0133, 3) + "]",
                "to_fixed_trimmed(3.14159L, 4)  -> [" + str::to_fixed_trimmed(3.14159L, 4) + "]",
                "Text::merge({...})             -> [" + Text::merge({"Hello, ", "this ", "is ", "merged."}) + "]",
            };

        std::cout << str::unordered_menu_list(rows);
        footer();
    }

    // ----------------------------------------------------------------- info ----

    namespace info
    {

        constexpr const char *Name = "cornatui";
        constexpr const char *NameOrigin = "C++ ornament text user interface";
        constexpr const char *Version = "0.4.3";
        constexpr const char *Author = "Anas Riemann";
        constexpr const char *Repository = "https://github.com/AnasRiemann/cornatui-lib";
        constexpr const char *License = "MIT";

        inline const std::string MIT_LICENSE_Content = R"LICENSE(
 MIT License

 Copyright (c) 2026 Anas Riemann

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
)LICENSE";

        void about()
        {
            header("About cornatui");

            std::vector<std::string> rows =
                {
                    "Name          : " + std::string(Name),
                    "Name origin   : " + std::string(Name) + " = " + std::string(NameOrigin),
                    "Version       : " + std::string(Version),
                    "Author        : " + std::string(Author),
                    "Repository    : " + std::string(Repository),
                    "License       : " + std::string(License),
                    "Build date    : " + std::string(__DATE__) + "  " + std::string(__TIME__),
                    "Language      : C++ version " + std::to_string(__cplusplus),
                    "Dependencies  : standard library only ( <windows.h> optionally, on Win32 )",
                };

            std::cout << str::table(rows, Border::hash, theme::text_color, theme::bg_color, theme::accent_color);
            footer();
        }

        void license()
        {
            std::cout
                << str::cls()
                << str::fg_color(theme::text_color)
                << str::translate(
                       str::box("MIT License", Border::bold, theme::text_color, theme::bg_color, theme::accent_color, 0) + str::fg_color(theme::text_color) + str::hr(80, "=", 1) + MIT_LICENSE_Content + str::hr(80, "=", 2),
                       2, 1);
            pause();
        }

        void compatibility()
        {
            header("Compatibility");

            std::vector<std::string> rows =
                {
                    "Windows 10+   : cmd.exe , PowerShell , Windows Terminal , Git Bash",
                    "Linux         : GNOME Terminal , Konsole , xterm and friends",
                    "macOS 10.14+  : Terminal.app , iTerm2",
                    "16 colors     : always available",
                    "256 colors    : most modern terminals",
                    "True RGB      : Windows Terminal , most Linux/macOS terminals",
                    "Limitation    : tui::Text keeps ASCII characters only ( no UTF-8 content )"};

            std::cout << str::table(rows, Border::single, theme::text_color, theme::bg_color, theme::accent_color);
            footer();
        }

        void menu()
        {
            const std::vector<std::string> items = {"About cornatui", "License", "Compatibility"};
            std::vector<std::string> list;
            for (size_t i = 0; i < items.size(); i++)
                list.push_back("[ " + std::to_string(i + 1) + " ] " + items[i]);

            std::string select;
            while (true)
            {
                std::cout
                    << str::cls()
                    << str::translate(
                           str::translate(str::box(" INFO ", Border::bold, theme::text_color, theme::bg_color, theme::accent_color, 1), 8, 1) + str::fg_color(theme::text_color) + str::table(list, Border::cross, theme::text_color, theme::bg_color, theme::accent_color, 2) + str::fg_color(theme::accent_color) + str::hr(80, "=", 2) + str::fg_color(theme::text_color) + prompt_range(items.size()),
                           2, 1);

                std::cin >> select;
                select = str::lowercase(select);
                std::cout << str::reset;

                if (select == "1")
                    about();
                else if (select == "2")
                    license();
                else if (select == "3")
                    compatibility();
                else if (check_break_keywords(select))
                    break;
            }
        }

    } // namespace info

} // namespace demo