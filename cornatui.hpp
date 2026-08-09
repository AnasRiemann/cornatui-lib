#ifndef STYLE_cornatui
#define STYLE_cornatui
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#if defined(_WIN32)
#include <conio.h>
#endif
#include "cornatui_math_ans.hpp"

#include "rang.hpp"


namespace tui
{

enum class border : int
{
    single = 1,
    bold   = 2,
    star   = 3,
    hash   = 4,
    cross  = 5
};

// ---- console control (unconditional declaration; defined further down) ----
void init_terminal();

// Runs init_terminal() once automatically on program startup, so callers
// don't have to remember to invoke it before using colors.
namespace detail { inline int auto_init = (init_terminal(), 0); }


// ---- small utilities ----
inline void delay_ms(unsigned int ms) { if (ms > 0) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); } }

inline std::string ignore_spaces(const std::string &input)
{
    std::string result;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (input[i] != ' ')
        {
            result.push_back(input[i]);
        }
    }
    return result;
}

std::string edit_precision(long double number, int precision1, int precision2);


// ---- string-returning variants ----
// Basic colors (1-16) are always raw ANSI here because these build plain
// strings that may be reused outside a known terminal context, so rang's
// stream-based detection doesn't apply. Extended colors (17-255) and true
// RGB have no rang equivalent either way.
namespace str
{
    std::string fg_color(const unsigned int r, const unsigned int g, const unsigned int b);
    std::string bg_color(const unsigned int r, const unsigned int g, const unsigned int b);

    std::string fg_color(const unsigned int color);
    std::string bg_color(const int color);

    std::string hr(const std::size_t width = 80, const char fillChar = '_');
    std::string hr(int width = 80, const std::string &Lstyle = "=", const int linesNumber = 1);


    inline std::string fg_color(const unsigned int color)
    {
        if (color <= 0) { return "\033[0m"; }
        else if (color <= 16)
        {
            static const char* basic_colors[] = {"0", "30", "31", "32", "33", "34", "35", "36", "37", "90", "91", "92", "93", "94", "95", "96", "97"};
            return "\033[" + std::string(basic_colors[color]) + "m";
        }
        else if (color < 256) { return "\033[38;5;" + std::to_string(color) + "m"; }
        return "";
    }

    inline std::string bg_color(const int color)
    {
        if      (color <= 0) { return "\033[0m"; }
        else if (color <= 8) { return "\033[" + std::to_string(39 + color) + "m"; }
        else if (color <= 16) { return "\033[" + std::to_string(91 + color) + "m"; }
        else if (color < 256) { return "\033[48;5;" + std::to_string(color) + "m"; }
        return "";
    }

    inline std::string fg_color(const unsigned int r, const unsigned int g, const unsigned int b)
    {
        if (r <= 255 && g <= 255 && b <= 255)
        {
            std::ostringstream color;
            color << "\033[38;2;" << r << ";" << g << ";" << b << "m";
            return color.str();
        }
        return "";
    }

    inline std::string bg_color(const unsigned int r, const unsigned int g, const unsigned int b)
    {
        if (r <= 255 && g <= 255 && b <= 255)
        {
            std::ostringstream bg;
            bg << "\033[48;2;" << r << ";" << g << ";" << b << "m";
            return bg.str();
        }
        return "";
    }

    inline std::string hr(const std::size_t width, const char fillChar) { return "\n" + std::string(width, fillChar) + "\n\n"; }

    inline std::string hr(int width, const std::string &Lstyle, const int linesNumber)
    {
        std::string line;
        line.resize(width + 1);
        for (int l = 1; l <= width; l++) { line[l] = Lstyle[l % Lstyle.length()]; }
        return "\n" + line + std::string(linesNumber, '\n');
    }

    inline std::string create_border(const std::string& abc, border style = border::single)
    {
        std::ostringstream line;
        size_t length = abc.length() + 6;

        switch (style)
        {
            case border::single: line << str::hr(length, "-", 1) << "|  " << abc << "  |" << str::hr(length, "-", 1); break;
            case border::bold:   line << str::hr(length, "=", 1) << "|| " << abc << " ||" << str::hr(length, "=", 1); break;
            case border::star:   line << str::hr(length, ".", 1) << "*  " << abc << "  *" << str::hr(length, "*", 1); break;
            case border::hash:   line << str::hr(length, "#", 1) << "#  " << abc << "  #" << str::hr(length, "#", 1); break;
            case border::cross:  line << str::hr(length, "+", 1) << "=- " << abc << " -=" << str::hr(length, "+", 1); break;
        }
        return line.str();
    }

    inline std::string create_list(const std::vector<std::string>& Element)
    {
        std::ostringstream out;
        for (size_t i = 0; i < Element.size(); i++) { out << " [ " << i + 1 << " ] " << Element.at(i) << "\n\n"; }
        return out.str();
    }

    inline std::string create_page(const std::string &header, const std::vector<std::string>& Element)
    {
        std::ostringstream out;
        out << "\n";
        out << str::create_border(header, tui::border::bold);
        out << "\n";
        out << str::hr(80, "=", 2);
        out << create_list(Element);
        out << str::hr(80, "=", 2);
        out << " # Enter choice [ 1 , " << Element.size() << " ] to Select or [0] to go back : ";
        return out.str();
    }

    inline std::string create_list(const std::vector<std::vector<std::string>>& Element)
    {
        std::ostringstream out;
        if (Element.empty() || Element[0].empty()) return out.str();
        size_t rowN = Element.size();
        size_t colN = Element[0].size();
        size_t auto_width = 0;
        for (size_t i = 0; i < rowN; i++)
        {
            for (size_t j = 0; j < colN; j++)
            {
                std::string elementOutput = " [ " + std::to_string(i + 1) + std::to_string(j + 1) + " ] " + Element[i][j];
                if (auto_width < elementOutput.length()) { auto_width = elementOutput.length(); }
            }
        }
        auto_width += 1;

        for (size_t i = 0; i < rowN; i++)
        {
            for (size_t j = 0; j < colN; j++)
            {
                std::string elementOutput = " [ " + std::to_string(i + 1) + std::to_string(j + 1) + " ] " + Element[i][j];
                out << std::left << std::setw(static_cast<int>(auto_width)) << elementOutput;
            }
            out << "\n\n";
        }
        return out.str();
    }

    inline std::string create_page(const std::string &header, const std::vector<std::vector<std::string>>& Element)
    {
        std::ostringstream out;
        out << "\n\n";
        out << create_border(header);
        out << "\n";
        out << str::hr(80, "=", 2);
        out << create_list(Element);
        out << str::hr(80, "=", 2);
        out << " # Enter choice [ 11 , " << Element.size() << Element[0].size() << " ] to Select or [0] to go back : ";
        return out.str();
    }

} // namespace str


class Text
{
private:
    std::string content_;

    inline void read_ascii_only(const std::string &input)
    {
        std::string filtered;
        for (unsigned char c : input) { if (c < 128) filtered.push_back(c); }
        content_ = filtered;
    }

public:
    Text(const std::string &input) { read_ascii_only(input); }

    const std::string& content() const { return content_; }

    friend inline std::ostream& operator<<(std::ostream& print, const Text& output)
    {
        print << output.content();
        return print;
    }

    friend inline std::istream& operator>>(std::istream& read, Text& input)
    {
        read >> input.content_;
        return read;
    }

    inline std::string color(const size_t color) const
    {
        std::ostringstream os;
        if (color <= 0) { os << "\033[0m" << content() << "\033[0m"; }
        else if (color <= 16)
        {
            static const char* basic_colors[] = {"0", "30", "31", "32", "33", "34", "35", "36", "37", "90", "91", "92", "93", "94", "95", "96", "97"};
            os << "\033[" << basic_colors[color] << "m" << content() << "\033[0m";
        }
        else if (color < 256) { os << "\033[38;5;" << color << "m" << content() << "\033[0m"; }
        return os.str();
    }

    inline std::string lowercase() const
    {
        std::string result = content();
        for (size_t i = 0; i < result.length(); i++) { if (result[i] >= 'A' && result[i] <= 'Z') { result[i] = result[i] + ('a' - 'A'); } }
        return result;
    }

    inline std::string uppercase() const
    {
        std::string result = content();
        for (size_t i = 0; i < result.length(); i++) { if (result[i] >= 'a' && result[i] <= 'z') { result[i] = result[i] - ('a' - 'A'); } }
        return result;
    }

    inline std::string reverse() const
    {
        std::string result_Text = content();
        for (size_t i = 0; i < content().length(); i++) { result_Text[i] = content()[content().length() - (i + 1)]; }
        return result_Text;
    }

    inline std::string colorful(int start = 1, int end = 256) const
    {
        std::ostringstream colorfulText;
        for (size_t C = 0; C < content().length(); C++)
        {
            colorfulText << str::fg_color(ans::get_random_number(start, end), ans::get_random_number(start, end), ans::get_random_number(start, end)) << content()[C] << "\033[0m";
        }
        return colorfulText.str();
    }

    inline std::string bold() const { return "\033[1m" + content() + "\033[0m"; }
    inline std::string dim() const { return "\033[2m" + content() + "\033[0m"; }
    inline std::string italic() const { return "\033[3m" + content() + "\033[0m"; }
    inline std::string underline() const { return "\033[4m" + content() + "\033[0m"; }
    inline std::string blink() const { return "\033[5m" + content() + "\033[0m"; }

    inline std::string separate(const unsigned int space_length = 1) const
    {
        std::ostringstream os;
        std::string cleaned = ignore_spaces(content());
        os << cleaned[0];
        for (size_t i = 1; i < cleaned.length(); i++) { os << std::string(space_length, ' ') << cleaned[i]; }
        return os.str();
    }

    inline void write(const unsigned int duration = 50, std::ostream &print = std::cout) const
    {
        for (size_t i = 0; i < content().length(); i++)
        {
            print << content()[i];
            print.flush();
            delay_ms(duration);
        }
    }

    inline void write_colorful(const unsigned int time = 50, const int start = 1, const int end = 255) const
    {
        for (size_t i = 0; i < content().length(); i++)
        {
            std::cout << str::fg_color(ans::get_random_number(start, end), ans::get_random_number(start, end), ans::get_random_number(start, end)) << content()[i] << "\033[0m";
            std::cout.flush();
            delay_ms(time);
        }
    }

    inline std::string border(tui::border style = tui::border::bold) const { return str::create_border(content(), style); }
};


inline std::string edit_precision(long double number, int precision1, int precision2)
{
    std::ostringstream os;
    os << std::setprecision(precision1) << number;
    os.unsetf(std::ios::scientific); os.unsetf(std::ios::fixed);
    os << std::setprecision(precision2);
    return os.str();
}


// ---- console control ----
inline void pause(const std::string& message = " Press [ENTER] to continue...", int duration = 50)
{
    for (size_t i = 0; i < message.length(); i++)
    {
        std::cout << message[i];
        std::cout.flush();
        delay_ms(duration);
    }
    std::cin.clear();
    std::cin.sync();
    std::cin.get();
}

static const std::string breakKeywords[] = {"0", "_n", "_f", "_q", "exit", "quit", "break", "false"};

inline bool check_break_keywords(const std::string &user_input)
{
    int size = sizeof(breakKeywords) / sizeof(breakKeywords[0]);
    for (int i = 0; i < size; i++) { if (breakKeywords[i] == user_input) return true; }
    return false;
}

inline void display_cursor(bool show = true, std::ostream &print = std::cout) { if (show) { print << "\033[?25h"; } else { print << "\033[?25l"; } }

inline void Cls(bool clearScreen = true, std::ostream &print = std::cout) { if (clearScreen) { print << "\033[2J\033[H"; } }

inline void cls(bool clearScreen = true, std::ostream &print = std::cout) { if (clearScreen) { print << "\033[2J\033[3J\033[H"; } } /* does not work in all terminals */

#if defined(RANG_DOT_HPP)


inline void init_terminal() { rang::setControlMode(rang::control::Auto); rang::setWinTermMode(rang::winTerm::Auto); }

inline void fg_color(const int color, std::ostream &print = std::cout)
{
    if (color <= 0) { print << rang::fg::reset; }
    else if (color <= 16)
    {
        switch (color)
        {
            case 1:  print << rang::fg::black; break;
            case 2:  print << rang::fg::red; break;
            case 3:  print << rang::fg::green; break;
            case 4:  print << rang::fg::yellow; break;
            case 5:  print << rang::fg::blue; break;
            case 6:  print << rang::fg::magenta; break;
            case 7:  print << rang::fg::cyan; break;
            case 8:  print << rang::fg::gray; break;
            case 9:  print << rang::fgB::black; break;
            case 10: print << rang::fgB::red; break;
            case 11: print << rang::fgB::green; break;
            case 12: print << rang::fgB::yellow; break;
            case 13: print << rang::fgB::blue; break;
            case 14: print << rang::fgB::magenta; break;
            case 15: print << rang::fgB::cyan; break;
            case 16: print << rang::fgB::gray; break;
            default: print << rang::fg::reset; break;
        }
    }
    else if (color < 256) { print << "\033[38;5;" << color << "m"; }
}

inline void bg_color(const int color, std::ostream &print = std::cout)
{
    if (color <= 0) { print << rang::bg::reset; }
    else if (color <= 16)
    {
        switch (color)
        {
            case 1:  print << rang::bg::black; break;
            case 2:  print << rang::bg::red; break;
            case 3:  print << rang::bg::green; break;
            case 4:  print << rang::bg::yellow; break;
            case 5:  print << rang::bg::blue; break;
            case 6:  print << rang::bg::magenta; break;
            case 7:  print << rang::bg::cyan; break;
            case 8:  print << rang::bg::gray; break;
            case 9:  print << rang::bgB::black; break;
            case 10: print << rang::bgB::red; break;
            case 11: print << rang::bgB::green; break;
            case 12: print << rang::bgB::yellow; break;
            case 13: print << rang::bgB::blue; break;
            case 14: print << rang::bgB::magenta; break;
            case 15: print << rang::bgB::cyan; break;
            case 16: print << rang::bgB::gray; break;
            default: print << rang::bg::reset; break;
        }
    }
    else if (color < 256) { print << "\033[48;5;" << color << "m"; }
}

#else

inline void init_terminal() { /* no-op */ }

inline void fg_color(const int color, std::ostream &print = std::cout)
{
    if (color <= 0) { print << "\033[0m"; }
    else if (color <= 16)
    {
        static const char* basic_colors[] = {"0", "30", "31", "32", "33", "34", "35", "36", "37", "90", "91", "92", "93", "94", "95", "96", "97"};
        print << "\033[" << basic_colors[color] << "m";
    }
    else if (color < 256) { print << "\033[38;5;" << color << "m"; }
}

inline void bg_color(const int color, std::ostream &print = std::cout)
{
    if      (color <= 0) { print << "\033[0m"; }
    else if (color <= 8) { print << "\033[" << (39 + color) << "m"; }
    else if (color <= 16) { print << "\033[" << (91 + color) << "m"; }
    else if (color < 256) { print << "\033[48;5;" << color << "m"; }
}

#endif


inline void br(const size_t linesNumber = 1, std::ostream &print = std::cout) { print << std::string(linesNumber, '\n'); }

inline void hr(const std::size_t width = 80, const char fillChar = '_', std::ostream &print = std::cout) { print << str::hr(width, fillChar); }

inline void hr(int width, const std::string &style, const int linesNumber = 1, std::ostream &print = std::cout) { print << str::hr(width, style, linesNumber); }

inline void create_border(const std::string& abc, border style = border::single, std::ostream &print = std::cout) { print << str::create_border(abc, style); }

inline void create_list(const std::vector<std::string>& Element, std::ostream &print = std::cout) { print << str::create_list(Element); }

inline void create_page(const std::string &header, const std::vector<std::string>& Element, std::ostream &print = std::cout) { print << str::create_page(header, Element); }

inline void create_list(const std::vector<std::vector<std::string>>& Element, std::ostream &print = std::cout) { print << str::create_list(Element); }

inline void create_page(const std::string &header, const std::vector<std::vector<std::string>>& Element, std::ostream &print = std::cout) { print << str::create_page(header, Element); }


} // namespace tui

#endif