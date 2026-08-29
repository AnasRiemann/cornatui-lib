// cornatui — feature demo
//
// A guided, menu-driven tour of everything cornatui.hpp / cornatui_math_ans.hpp
// currently offers: colors, boxes & tables, Text styling, animation,
// positioning, string utilities, and an "INFO" section about the library
// and its author.
//
// Build:  g++ -std=c++17 -O2 test.cpp -o demo

#define CORNATUI_DISABLE_WIN32
#define CORNATUI_DISABLE_RANG_DOT_HPP
#include "cornatui/cornatui.hpp"



using namespace tui;

// ---- shared color theme for the demo's own boxes/tables ----
namespace theme
{
 ans::IntRGB255 text_color(ans::get_random_number(180,240), ans::get_random_number(180,240),  ans::get_random_number(180,240));
 ans::IntRGB255 bg_color(ans::get_random_number(10,30), ans::get_random_number(15,35),  ans::get_random_number(20,40));
 ans::IntRGB255 accent_color(ans::get_random_number(200,250), ans::get_random_number(190,245),  ans::get_random_number(200,250));
}

namespace demo
{

const std::vector<std::string> main_menu =
{
    "Colors                [ 16 named / 256 palette / RGB / IntRGB255 ]",
    "Boxes, Tables & Menus [ str::box , str::table , str::ordered_menu ]",
    "Text Effects          [ tui::Text class ]",
    "Typewriter Animation  [ Text::write , Text::write_colorful ]",
    "Positioning           [ str::translate , str::br , str::space ]",
    "String Utilities      [ trim / case / reverse / etc.. ]",
    "INFO                  [ about cornatui , license , compatibility ]",
};

void run();

void colors();
void boxes_tables_menus();
void text_effects();
void animation();
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
        << str::box(title, Border::mix, theme::text_color, theme::bg_color, theme::accent_color, 0)
        << str::fg_color(theme::accent_color)
        << str::hr(80, "=", 2)
        << str::reset();
}

void footer()
{
    std::cout << str::fg_color(theme::accent_color) << str::hr(80, "=", 2) << str::reset();
    pause();
}

} // namespace demo

int main()
{
    init_terminal();
    cls();
    display_cursor(false);
     std::vector<std::string> list;
    for (size_t i = 0; i < demo::main_menu.size(); i++)
        list.push_back("[ " + std::to_string(i + 1) + " ] " + demo::main_menu[i]);


    for(int i =0;i<10;i++)
{
std::ostringstream os;
ans::IntRGB255 fgColor(ans::get_random_number(150,240), ans::get_random_number(160,240),  ans::get_random_number(175,245));
ans::IntRGB255 bgColor(ans::get_random_number(10,50), ans::get_random_number(15,65),  ans::get_random_number(20,80));
ans::IntRGB255 aColor(ans::get_random_number(160,250), ans::get_random_number(180,245),  ans::get_random_number(200,250));
    cls();
       os
            << str::cls()
            << str::translate(
                   str::box(" Cornatui |> Developed By  A  n  a  s  R  i  e  m  a  n  n ", Border::bold,
                            fgColor, bgColor, aColor, 0)
                       + str::fg_color(fgColor)
                       + str::table(list, Border::cross, fgColor, bgColor, aColor )
                       + str::fg_color(aColor)
                       + str::hr(80, "=", 2)
                       + str::fg_color(fgColor)
                       + " # Select option [1-7] , to exit [0] |> option -> ",
                   2, 1);
            
                   std::cout<<os.str()<<std::flush;
                          delay_ms(75);
}
    demo::run();
    return 0;
}

namespace demo
{

void run()
{
    std::string option;

    std::vector<std::string> list;
    for (size_t i = 0; i < main_menu.size(); i++)
        list.push_back("[ " + std::to_string(i + 1) + " ] " + main_menu[i]);

    while (true)
    {
display_cursor(false);

ans::IntRGB255 fgColor(ans::get_random_number(150,240), ans::get_random_number(160,240),  ans::get_random_number(175,245));
ans::IntRGB255 bgColor(fgColor.inverse().darkness(2));
ans::IntRGB255 aColor(fgColor.inverse().brightness(3));
    cls();
        std::cout
            << str::cls()
            << str::translate(
                   str::box(" Cornatui |> Developed By  A  n  a  s  R  i  e  m  a  n  n ", Border::bold,
                            fgColor, bgColor, aColor, 0)
                       + str::fg_color(fgColor)
                       + str::table(list, Border::mix, fgColor, bgColor, aColor,1)
                       + str::fg_color(aColor)
                       + str::hr(80, "=", 2)
                       + str::fg_color(fgColor)
                       + " # Select option [1-7] , to exit [0] |> option -> ",
                   2, 1);
                   delay_ms(75);

display_cursor(true);
        std::cin >> option;
        std::cout << str::reset();

        if (option == "1") colors();
        else if (option == "2") boxes_tables_menus();
        else if (option == "3") text_effects();
        else if (option == "4") animation();
        else if (option == "5") positioning();
        else if (option == "6") string_utilities();
        else if (option == "7") info::menu();
        else if (check_break_keywords(option)) break;
    }
}

// ---------------------------------------------------------------- colors --

void colors()
{
    std::ostringstream os255fg,os255bg,osRGB;
    header("Colors  [ 255 named ] ( str::fg_color(1-255) )");

    for (unsigned int i = 0; i < 256; i++)
    { 

    os255fg << str::fg_color(i) << " #" << std::setfill('0') << std::setw(3) << i << " " << str::reset();
    if((i+1)%8==0)os255fg<<str::br();
    } 
    std::cout<<os255fg.str();
    footer();

    header("Colors  [ 255 named ] ( str::bg_color(1-255) )");

    for (unsigned int i = 0; i < 256; i++)
    { 

    os255bg << str::bg_color(i) << " #" << std::setfill('0') << std::setw(3) << i << " " << str::reset();
    if((i+1)%8==0)os255bg<<str::br();
    } 
    std::cout<<os255bg.str();
    footer();



  

   

    header("Colors  [ True RGB ]  ( str::fg_color(r,g,b) / str::bg_color(r,g,b) )");
    std::cout << "  ";
    for (int i = 0; i < 256; i++)
    {
        osRGB<< str::fg_color(255 - i, i, 128) << str::bg_color(i, 40, 255 - i) << " ## "<< str::reset();
        if ((i) % 17 == 0) osRGB << "\n  " ;
    }


    std::cout<<osRGB.str() << str::reset();
    footer();

    header("Colors  [ ans::IntRGB255 ]  -  a clamped 0-255 RGB value type");
    ans::IntRGB255 a(220, 60, 90), b(40, 180, 60);
    std::vector<std::string> rows =
    {
        "IntRGB255(220,60,90).hex()  -> " + a.hex(),
        "IntRGB255(40,180,60).hex()  -> " + b.hex(),
        "(a + b).hex()  -> " + (a + b).hex() + "   ( channels added, clamped to 255 )",
        "(a - b).hex()  -> " + (a - b).hex() + "   ( channels subtracted, clamped to 0 )",
    };
    std::cout
        << str::fg_color(a) << rows[0] << str::reset() << "\n"
        << str::fg_color(b) << rows[1] << str::reset() << "\n"
        << str::fg_color(a + b) << rows[2] << str::reset() << "\n"
        << str::fg_color(a - b) << rows[3] << str::reset() << "\n\n"
        << "  # str::fg_color() / str::bg_color() also accept an ans::IntRGB255 directly,\n"
        << "  # which is what the colored str::box() and str::table() overloads use.\n";
    footer();
}

// ------------------------------------------------------- boxes / tables ---

void boxes_tables_menus()
{
    header("Boxes  ( str::box )");
    std::cout
        << str::box("Plain box, single border, no padding", Border::single) 
        << str::box("Bold border, 1 line of padding", Border::bold, 1) 
        << str::box("Colored box ( text / background / border via IntRGB255 )",
                     Border::cross, theme::text_color, theme::bg_color, theme::accent_color, 1)<<str::br();
    footer();

    header("Border Styles  ( tui::Border )");
    std::vector<std::pair<std::string, Border>> styles =
    {
        {"single", Border::single}, {"bold", Border::bold}, {"star", Border::star},
        {"hash", Border::hash}, {"cross", Border::cross}, {"wave", Border::wave},
    };


    for (const auto &s : styles)std::cout << str::box(s.first, s.second);
    std::cout<<str::br();
    footer();

    header("Tables  ( str::table )  -  bordered, unnumbered rows");
    std::vector<std::string> rows = {"Row one", "Row two is a little longer", "Row three"};
    std::cout
        << str::table(rows, Border::cross) 
        << str::table(rows, Border::hash, theme::text_color, theme::bg_color, theme::accent_color) << "\n";
    footer();

    header("Menus  ( str::ordered_menu )  -  header + numbered list + prompt");
    std::vector<std::string> items = {"First choice", "Second choice", "Third choice"};
    std::cout << str::ordered_menu("Example Menu", items)<<str::br(3);
    footer();

    header("2D variant  ( str::ordered_menu_list on a vector<vector<string>> )");
    std::vector<std::vector<std::string>> grid = {{"A1", "A2"}, {"B1", "B2"}};
    std::cout << str::ordered_menu_list(grid) << "\n";
    footer();
}

// ------------------------------------------------------------ Text class --

void text_effects()
{
    header("Text Effects  ( tui::Text )");
    Text message = {"I Love Cornatui"};

    std::vector<std::string> rows =
    {
        "content()            -> " + message.content(),
        "color(5)             -> " + message.color(5),
        "lowercase()          -> " + message.lowercase(),
        "uppercase()          -> " + message.uppercase(),
        "reverse()            -> " + message.reverse(),
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
        "separate(2)          -> " + message.separate(2),
        "colorful(50,220)     -> " + message.colorful(50, 220),
        "bg_colorful()        -> " + message.bg_colorful(),
    };

    std::cout << str::unordered_menu_list(rows);
    footer();
}

// -------------------------------------------------------------- animation --

void animation()
{
    header("Animation  ( Text::write / Text::write_colorful )");

    display_cursor(false);

    Text line1 = {" # cornatui typewriter effect..."};
    line1.write(35);
    std::cout << "\n\n";

    Text line2 = {" # ...and now with a random color per character"};
    line2.write_colorful(35, 1, 255);
    std::cout << "\n\n";

    display_cursor(true);

    std::cout << "  # tui::sound::ring() just rang the terminal bell.\n";
    sound::ring();

#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)
    std::cout << "  # tui::sound::beep() is also available on native Windows builds.\n";
    sound::beep();
#endif

    std::cout << "\n";
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
    std::string sample = "   Hello, cornaTUI!   ";

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
        "format_number(3.14159L, 2, 6) -> [" + str::format_number(3.14159L, 4) + "]",
        "Text::merge({...})             -> [" + Text::merge({"Hello, ", "this ", "is ", "merged."}) + "]",
    };

    std::cout << str::unordered_menu_list(rows);
    footer();
}

// ----------------------------------------------------------------- info ----

namespace info
{

constexpr const char *Name       = "cornatui";
constexpr const char *NameOrigin = "C++ ornament text user interface";
constexpr const char *Version    = "0.3.7";
constexpr const char *Author     = "Anas Riemann";
constexpr const char *Repository = "https://github.com/AnasRiemann/cornatui-lib";
constexpr const char *License    = "MIT";

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
        "Dependencies  : cornatui_math_ans.hpp  ,  rang.hpp (optional)",
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
               str::box("MIT License", Border::bold, theme::text_color, theme::bg_color, theme::accent_color, 0)
                   + str::fg_color(theme::text_color)
                   + str::hr(80, "=", 1)
                   + MIT_LICENSE_Content
                   + str::hr(80, "=", 2),
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
        "Limitation    : tui::Text keeps ASCII characters only ( no UTF-8 content )"

    };

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
                  str::translate( str::box(" INFO ", Border::bold, theme::text_color, theme::bg_color, theme::accent_color, 1),8, 1)
                       + str::fg_color(theme::text_color)
                       + str::table(list, Border::cross, theme::text_color, theme::bg_color, theme::accent_color,2)
                       + str::fg_color(theme::accent_color)
                       + str::hr(80, "=", 2)
                       + str::fg_color(theme::text_color)
                       + " # Select option [1-3] , to go back [0] |> option -> ",
                   2, 1);

        std::cin >> select;
        select = str::lowercase(select);
        std::cout << str::reset();

        if (select == "1") about();
        else if (select == "2") license();
        else if (select == "3") compatibility();
        else if (check_break_keywords(select)) break;
    }
}

} // namespace info

} // namespace demo