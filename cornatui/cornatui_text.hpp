#ifndef CORNATUI_TEXT
#define CORNATUI_TEXT

#include <cmath>
#include <vector>

#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>

#include <cctype>


#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)

#include <windows.h>
#include <conio.h>

#endif



#include "cornatui_math_ans.hpp"
#include "cornatui_color.hpp"



/*

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

*/

namespace tui
{

        enum class Screen : int
    {
        off = 0,
        view = 1,
        full = 2
    };




    inline void delay_ms(unsigned int ms)
    {
        if (ms > 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        }
    }

    

    
    enum class Method : int
    {
        padding = 0,
        ansi = 1,

    };

    namespace str
    {

        inline std::string ignore_character(const std::string &input, const char character);
        inline std::string ignore_spaces(const std::string &input);
        inline std::string get_ascii_only(const std::string &input);
        inline std::string validate_box_content(const std::string &input);
        inline std::string lowercase(const std::string &text);
        inline std::string uppercase(const std::string &text);
        inline std::string reverse(const std::string &text);

        inline std::string ltrim(const std::string &text);
        inline std::string rtrim(const std::string &text);
        inline std::string trim(const std::string &text);
        inline std::string format_number(long double val, int decimal_precision = 5, bool trim_trailing_zeros = true, bool auto_scientific = false);
        inline std::string separate(const std::string &text, const unsigned int space_length = 1);
        inline std::string translate(const std::string &content, const size_t x, const size_t y, Method translation_method = Method::padding);

        inline std::string br(const size_t numberOfLines = 1, Method translation_method = Method::padding);
        inline std::string space(const size_t width, Method translation_method = Method::padding);

        inline std::string hr(const size_t width = 80, const char style = '-');
        inline std::string hr(const size_t width, const std::string &style, const size_t numberOfLines = 1);

        inline std::string line(const size_t width, const char style);
        inline std::string line(const size_t width, const std::string &style);
        inline std::string cls(Screen mode = Screen::full);
       

    }

    namespace str
    {

        inline std::string ignore_character(const std::string &input, const char character)
        {
            std::string result;

            for (size_t i = 0; i < input.length(); i++)
            {
                if (input[i] != character)
                {
                    result.push_back(input[i]);
                }
            }
            return result;
        }

        inline std::string ignore_spaces(const std::string &input) { return ignore_character(input, ' '); }

        inline std::string get_ascii_only(const std::string &input)
        {
            std::string filtered;
            for (unsigned char c : input)
            {
                if (c < 128)
                    filtered.push_back(c);
            }
            return filtered;
        }

        inline std::string ltrim(const std::string &text)
        {
            std::string result = text;
            result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch)
                                                      { return !std::isspace(ch); }));
            return result;
        }

        inline std::string rtrim(const std::string &text)
        {
            std::string result = text;
            result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch)
                                      { return !std::isspace(ch); })
                             .base(),
                         result.end());
            return result;
        }

        inline std::string trim(const std::string &text)
        {
            if (text.empty())
                return "";
            return ltrim(rtrim(text));
        }
        inline std::string validate_box_content(const std::string &input)
        {
            std::string filtered;
            filtered.reserve(input.size());

            for (size_t i = 0; i < input.length(); i++)
            {
                unsigned char c = static_cast<unsigned char>(input.at(i));

                if (c > 31 && c < 127)
                {
                    filtered.push_back(static_cast<char>(c));
                }
            }
            return trim(filtered);
        }

        inline std::string lowercase(const std::string &text)
        {
            std::string result = text;
            std::transform(result.begin(), result.end(), result.begin(),
                           [](unsigned char c)
                           { return std::tolower(c); });
            return result;
        }

        inline std::string uppercase(const std::string &text)
        {
            std::string result = text;
            std::transform(result.begin(), result.end(), result.begin(),
                           [](unsigned char c)
                           { return std::toupper(c); });
            return result;
        }

        inline std::string reverse(const std::string &text)
        {
            std::string result = text;
            std::reverse(result.begin(), result.end());
            return result;
        }

        inline std::string separate(const std::string &text, const unsigned int space_length)
        {
            std::ostringstream os;
            std::string cleaned = trim(text);
            os << cleaned[0];
            for (size_t i = 1; i < cleaned.length(); i++)
            {
                os << std::string(space_length, ' ') << cleaned[i];
            }
            return os.str();
        }

        inline std::string format_number(long double val, int decimal_precision, bool trim_trailing_zeros, bool auto_scientific)
        {
            std::ostringstream oss;

            if (auto_scientific && val != 0.0L)
            {
                long double absVal = std::fabs(val);
                if (absVal >= 1e15L || absVal < 1e-9L)
                {
                    oss << std::scientific << std::setprecision(7) << val;
                    return oss.str();
                }
            }

            oss << std::fixed << std::setprecision(decimal_precision) << val;
            std::string s = oss.str();

            if (trim_trailing_zeros && s.find('.') != std::string::npos)
            {
                size_t lastNonZero = s.find_last_not_of('0');
                if (s[lastNonZero] == '.')
                    lastNonZero--;
                s.erase(lastNonZero + 1);
            }

            if (s == "-0")
                s = "0";

            return s;
        }

        inline std::string translate(const std::string &content, const size_t x, const size_t y, Method translation_method)
        {

            std::ostringstream os;
            switch (translation_method)
            {

            case Method::padding:
            {
                os << std::string(y, '\n') << std::string(x, ' ');
                for (size_t i = 0; i < content.length(); i++)
                {
                    if (content.at(i) == '\n')
                    {
                        os << '\n'
                           << std::string(x, ' ');
                    }
                    else
                    {
                        os << content.at(i);
                    }
                }
                return os.str();
                break;
            }

            case Method::ansi:
            {
                if (y > 0)
                    os << "\033[" << y << "B";
                if (x > 0)
                    os << "\033[" << x << "C";

                for (size_t i = 0; i < content.length(); i++)
                {
                    if (content.at(i) == '\n')
                    {
                        os << '\n';
                        if (x > 0)
                            os << "\033[" << x << "C";
                    }
                    else
                    {
                        os << content.at(i);
                    }
                }
            }
            }

            return os.str();
        }

        inline std::string br(const size_t numberOfLines, Method translation_method)
        {
            switch (translation_method)
            {
            case Method::padding:
                return std::string(numberOfLines, '\n');
                break;

            case Method::ansi:
                return "\033[" + std::to_string(numberOfLines) + "B";
                break;
            default:
                return "";
                break;
            }

            return "";
        }

        inline std::string space(const size_t width, Method translation_method)
        {
            switch (translation_method)
            {
            case Method::padding:
                return std::string(width, ' ');
                break;

            case Method::ansi:
                return "\033[" + std::to_string(width) + "C";
                break;
            default:
                return "";
                break;
            }

            return "";
        }

        inline std::string line(const std::size_t width, const char style) { return std::string(width, style); }

        inline std::string line(const size_t width, const std::string &style)
        {
            if (style.empty() || width == 0)
                return "";
            std::string result;
            result.reserve(width);
            for (size_t l = 0; l < width; ++l)
            {
                result.push_back(style[l % style.length()]);
            }
            return result;
        }

        inline std::string hr(const std::size_t width, const char style) { return "\n" + line(width, style) + "\n"; }

        inline std::string hr(const size_t width, const std::string &style, const size_t numberOfLines) { return "\n" + line(width, style) + std::string(numberOfLines, '\n'); }



        
        inline std::string cls(Screen mode)
        {
            if (mode == Screen::off)
                return "";
            switch (mode)
            {
            case Screen::view:
                return "\033[2J\033[H";
                break;
            case Screen::full:
                return "\033[2J\033[3J\033[H";
                break;
            default:
                return "";
                break;
            }
        }



    }

    class Text
    {
    private:
        std::string content_;

        inline void get_ascii_only(const std::string &input)
        {
            std::string filtered;
            for (unsigned char c : input)
            {
                if (c < 128)
                    filtered.push_back(c);
            }
            content_ = filtered;
        }

    public:
        Text(const std::string &input) { get_ascii_only(input); }

        const std::string &content() const { return content_; }

        friend inline std::ostream &operator<<(std::ostream &print, const Text &output)
        {
            print << output.content();
            return print;
        }

        friend inline std::istream &operator>>(std::istream &read, Text &input)
        {

            read >> input.content_;
            input.get_ascii_only(input.content_);
            return read;
        }

        inline std::string color(const unsigned int colorIndex) const
        {
            if (colorIndex < 256)
            {
                return str::fg_color(colorIndex) + content() + str::reset();
            }
            return "";
        }
        inline std::string bg_color(const unsigned int colorIndex) const
        {
            if (colorIndex < 256)
            {
                return str::bg_color(colorIndex) + content() + str::reset();
            }
            return "";
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

        inline std::string bg_colorful(int start = 1, int end = 256) const
        {

            std::ostringstream colorfulText;
            for (size_t C = 0; C < content().length(); C++)
            {
                colorfulText << str::bg_color(ans::get_random_number(start, end), ans::get_random_number(start, end), ans::get_random_number(start, end)) << content()[C] << "\033[0m";
            }
            return colorfulText.str();
        }

        inline std::string bold() const { return str::bold() + content() + str::reset(); }
        inline std::string dim() const { return str::dim() + content() + str::reset(); }
        inline std::string italic() const { return str::italic() + content() + str::reset(); }
        inline std::string underline() const { return str::underline() + content() + str::reset(); }
        inline std::string blink() const { return str::blink() + content() + str::reset(); }
        inline std::string rblink() const { return str::rblink() + content() + str::reset(); }
        inline std::string reversed() const { return str::reversed() + content() + str::reset(); }
        inline std::string conceal() const { return str::conceal() + content() + str::reset(); }
        inline std::string crossed() const { return str::crossed() + content() + str::reset(); }
        inline std::string double_underline() const { return str::double_underline() + content() + str::reset(); }
        inline std::string curly_underline() const { return str::curly_underline() + content() + str::reset(); }
        inline std::string overline() const { return str::overline() + content() + str::reset(); }

        inline std::string lowercase() const
        {
            std::string result = content();
            for (size_t i = 0; i < result.length(); i++)
            {
                if (result[i] >= 'A' && result[i] <= 'Z')
                {
                    result[i] = result[i] + ('a' - 'A');
                }
            }
            return result;
        }

        inline std::string uppercase() const
        {
            std::string result = content();
            for (size_t i = 0; i < result.length(); i++)
            {
                if (result[i] >= 'a' && result[i] <= 'z')
                {
                    result[i] = result[i] - ('a' - 'A');
                }
            }
            return result;
        }

        inline std::string reverse() const
        {
            std::string result_Text = content();
            for (size_t i = 0; i < content().length(); i++)
            {
                result_Text[i] = content()[content().length() - (i + 1)];
            }
            return result_Text;
        }

        inline std::string separate(const unsigned int space_length) const { return str::separate(content(), space_length); }

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

        static std::string merge(const std::vector<std::string> &paragraph)
        {
            if (paragraph.empty())
                return " ";
            std::ostringstream os;

            for (size_t i = 0; i < paragraph.size(); i++)
            {
                os << paragraph[i];
            }
            return os.str();
        }
    };




#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)

    inline void pause(const std::string &message = " Press any Key to continue...", unsigned int duration = 50)
    {
        for (size_t i = 0; i < message.length(); i++)
        {
            std::cout << message[i];
            std::cout.flush();
            delay_ms(duration);
        }

        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

        if (hInput != INVALID_HANDLE_VALUE && hInput != NULL)
        {
            FlushConsoleInputBuffer(hInput);
        }

        _getch();
    }

    namespace detail
    {
        inline HANDLE console_output_handle(const std::ostream &print) noexcept
        {
            if (&print == &std::cerr || &print == &std::clog)
            {
                return GetStdHandle(STD_ERROR_HANDLE);
            }
            return GetStdHandle(STD_OUTPUT_HANDLE);
        }
    }

    inline void display_cursor(bool show = true, std::ostream &print = std::cout)
    {

        HANDLE hConsole = detail::console_output_handle(print);
        CONSOLE_CURSOR_INFO cursorInfo;
        if (hConsole != INVALID_HANDLE_VALUE && GetConsoleCursorInfo(hConsole, &cursorInfo))
        {
            cursorInfo.bVisible = show;
            SetConsoleCursorInfo(hConsole, &cursorInfo);
            return;
        }
    }

    inline void cls(Screen mode = Screen::full, std::ostream &print = std::cout)
    {
        if (mode == Screen::off)
        {
            return;
        }

        print << str::cls(mode);
        HANDLE hConsole = detail::console_output_handle(print);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (hConsole != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hConsole, &csbi))
        {
            const DWORD cellCount = static_cast<DWORD>(csbi.dwSize.X) * static_cast<DWORD>(csbi.dwSize.Y);
            const COORD home = {0, 0};
            DWORD written;
            FillConsoleOutputCharacter(hConsole, ' ', cellCount, home, &written);
            FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, home, &written);
            SetConsoleCursorPosition(hConsole, home);
            return;
        }
    }

#else

    inline void pause(const std::string &message = " Press [ENTER] to continue...", int duration = 50)
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

    inline void display_cursor(bool show = true, std::ostream &print = std::cout)
    {
        if (show)
        {
            print << "\033[?25h";
        }
        else
        {
            print << "\033[?25l";
        }
    }

    inline void cls(Screen mode = Screen::full, std::ostream &print = std::cout)
    {
        if (mode == Screen::off)
        {
            return;
        }
        switch (mode)
        {
        case Screen::view:
            print << str::cls(Screen::view) << std::flush;
            break;
        case Screen::full:
            print << str::cls(Screen::full) << std::flush;
            break;
        default:
            break;
        }
    }

#endif






}

#endif
