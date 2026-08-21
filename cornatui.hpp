
#ifndef CORNATUI
#define CORNATUI

#include <cmath>
#include <vector>
#include <functional>
#include <random>
#include <complex>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <cctype>



/*

#define CORNATUI_DISABLE_WIN32
#define CORNATUI_DISABLE_RANG_DOT_HPP

*/


#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)

#include <windows.h>
#include <conio.h>

#endif

#ifndef CORNATUI_DISABLE_RANG_DOT_HPP

#include "rang.hpp"

#endif

#include "cornatui_math_ans.hpp"

namespace tui
{

    enum class Border : int
    {
        single = 1,
        bold = 2,
        star = 3,
        hash = 4,
        cross = 5,
        wave = 6
    };

    enum class Screen : int
    {
        off = 0,
        view = 1,
        full = 2
    };

    enum class Page : int
    {
        list = 0,
        paragraph = 1,
        confirm = 2

        /*coming soon*/
    };

    enum class Method : int
    {
        padding = 0,
        ansi = 1,

    };

    // ---- small utilities ----

    inline void delay_ms(unsigned int ms)
    {
        if (ms > 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        }
    }

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

        inline std::string translate(const std::string &content, const size_t x, const size_t y, Method translation_method = Method::padding);
        inline std::string br(const size_t numberOfLines = 1, Method translation_method = Method::padding);
        inline std::string space(const size_t width, Method translation_method = Method::padding);

        inline std::string fg_color(const unsigned int r, const unsigned int g, const unsigned int b);
        inline std::string bg_color(const unsigned int r, const unsigned int g, const unsigned int b);

        inline std::string fg_color(const ans::IntRGB255 &colorValue);
        inline std::string bg_color(const ans::IntRGB255 &colorValue);

        inline std::string fg_color(const unsigned int color);
        inline std::string bg_color(const unsigned int color);

        inline std::string cls(Screen mode = Screen::full);
        inline std::string reset();

        inline std::string hr(const std::size_t width = 80, const char style = '-');
        inline std::string hr(const size_t width, const std::string &style, const size_t numberOfLines = 1);
        inline std::string line(const std::size_t width, const char style);
        inline std::string line(const size_t width, const std::string &style);

        inline std::string box(const std::string &abc, Border style = Border::single, const size_t padding = 0);
        inline std::string box(const std::string &abc, Border style, const ans::IntRGB255 &textColor, const ans::IntRGB255 &bgColor, const ans::IntRGB255 &borderColor, const size_t padding);

        inline std::string table(const std::vector<std::string> &text, Border style, const ans::IntRGB255 &textColor, const ans::IntRGB255 &bgColor, const ans::IntRGB255 &borderColor);

        inline std::string ordered_list(const std::vector<std::string> &Element);
        inline std::string unordered_list(const std::vector<std::string> &Element);
        inline std::string ordered_menu(const std::string &header, const std::vector<std::string> &Element);

        inline std::string unordered_list(const std::vector<std::vector<std::string>> &Element);
        inline std::string ordered_list(const std::vector<std::vector<std::string>> &Element);
        inline std::string ordered_menu(const std::string &header, const std::vector<std::vector<std::string>> &Element);

        inline std::string edit_precision(long double number, int precision1, int precision2);

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

        inline std::string validate_box_content(const std::string &input)
        {
            std::string filtered;
            filtered.reserve(input.size());

            for (size_t i = 0; i < input.length(); i++)
            {
                unsigned char c = static_cast<unsigned char>(input.at(i));

                if (c > 31 && c < 128)
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

        inline std::string fg_color(const unsigned int color)
        {
            static const int basic_codes[16] = {30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96, 97};

            if (color < 16)
            {
                return "\033[" + std::to_string(basic_codes[color]) + "m";
            }
            else if (color < 256)
            {
                return "\033[38;5;" + std::to_string(color) + "m";
            }
            return "";
        }

        inline std::string bg_color(const unsigned int color)
        {
            static const int basic_codes[16] = {40, 41, 42, 43, 44, 45, 46, 47, 100, 101, 102, 103, 104, 105, 106, 107};

            if (color < 16)
            {
                return "\033[" + std::to_string(basic_codes[color]) + "m";
            }
            else if (color < 256)
            {
                return "\033[48;5;" + std::to_string(color) + "m";
            }
            return "";
        }

        inline std::string fg_color(const unsigned int r, const unsigned int g, const unsigned int b)
        {
            if (r <= 255 && g <= 255 && b <= 255)
            {
                std::ostringstream fg;
                fg << "\033[38;2;" << r << ";" << g << ";" << b << "m";
                return fg.str();
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

        inline std::string fg_color(const ans::IntRGB255 &colorValue)
        {
            std::ostringstream fg;
            fg << "\033[38;2;" << colorValue.red() << ";" << colorValue.green() << ";" << colorValue.blue() << "m";
            return fg.str();
        }

        inline std::string bg_color(const ans::IntRGB255 &colorValue)
        {
            std::ostringstream bg;
            bg << "\033[48;2;" << colorValue.red() << ";" << colorValue.green() << ";" << colorValue.blue() << "m";
            return bg.str();
        }

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

        inline std::string reset() { return "\033[0m"; }

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

        struct BorderStyle
        {
        private:
            std::string leftchar_;
            std::string rightchar_;
            std::string outerChar_;
            std::string innerChar_;

        public:
            BorderStyle(const std::string &left, const std::string &right, const std::string &outer, const std::string &inner)
                : leftchar_(left), rightchar_(right), outerChar_(outer), innerChar_(inner) {}

            BorderStyle() = default;

            static BorderStyle wall(const Border style)
            {
                switch (style)
                {
                case Border::single:
                    return BorderStyle("|", "|", "-", "-");
                case Border::bold:
                    return BorderStyle("||", "||", "=", "-");
                case Border::star:
                    return BorderStyle("*", "*", "*", "*");
                case Border::hash:
                    return BorderStyle("#", "#", "#", "=");
                case Border::cross:
                    return BorderStyle("|=", "=|", "+", "-");
                case Border::wave:
                    return BorderStyle("~", "~", "~", "~");
                default:
                    return BorderStyle("|", "|", "-", "-");
                }
            }

            std::string get_left() const { return leftchar_; }
            std::string get_right() const { return rightchar_; }
            std::string get_outer() const { return outerChar_; }
            std::string get_inner() const { return innerChar_; }
        };

        inline std::string box(const std::string &abc, Border style, const size_t padding)
        {
            std::string content = validate_box_content(abc);
            BorderStyle wall = BorderStyle::wall(style);

            std::string hrChar = wall.get_outer();
            std::string leftBorder = wall.get_left();
            std::string rightBorder = wall.get_right();

            size_t innerWidth = content.length() + (padding * 2) + 2;
            size_t length = innerWidth + leftBorder.length() + rightBorder.length();

            std::string hrLine = line(length, hrChar) + br();

            std::ostringstream os;
            os << br() << hrLine;

            for (size_t i = 0; i < padding; i++)
                os << leftBorder << std::string(innerWidth, ' ') << rightBorder << "\n";

            os << leftBorder
               << " " << std::string(padding, ' ') << content << std::string(padding, ' ') << " "
               << rightBorder << "\n";

            for (size_t i = 0; i < padding; i++)
                os << leftBorder << std::string(innerWidth, ' ') << rightBorder << "\n";

            os << hrLine;
            return os.str();
        }

        inline std::string table(const std::vector<std::string> &text, Border style)
        {
            std::ostringstream os;

            if (text.empty())
                return os.str();

            std::vector<std::string> validStr(text.size());

            size_t maxLength = 0;
            for (size_t r = 0; r < text.size(); r++)
            {
                validStr[r] = validate_box_content(text[r]);
                if (validStr[r].length() > maxLength)
                    maxLength = validStr[r].length();
            }

            BorderStyle wall = BorderStyle::wall(style);
            std::string wallLeft = wall.get_left();
            std::string wallRight = wall.get_right();
            std::string outerChar = wall.get_outer();
            std::string innerChar = wall.get_inner();

            size_t length = maxLength + wallLeft.length() + wallRight.length() + 2;

            os << str::hr(length, outerChar, 1);

            for (size_t i = 0; i < text.size(); i++)
            {
                os << wallLeft << " " << validStr[i]
                   << std::string(maxLength - validStr[i].length(), ' ')
                   << " " << wallRight
                   << str::hr(length, (i + 1 < text.size()) ? innerChar : outerChar, 1);
            }

            return os.str();
        }

        inline std::string box(const std::string &abc, Border style, const ans::IntRGB255 &textColor, const ans::IntRGB255 &bgColor, const ans::IntRGB255 &borderColor, const size_t padding)
        {
            std::string content = validate_box_content(abc);
            BorderStyle wall = BorderStyle::wall(style);

            std::string hrChar = wall.get_outer();
            std::string leftBorder = wall.get_left();
            std::string rightBorder = wall.get_right();

            size_t innerWidth = content.length() + (padding * 2) + 2;
            size_t length = innerWidth + leftBorder.length() + rightBorder.length();

            std::string wallColor = fg_color(borderColor);
            std::string fill = fg_color(textColor) + bg_color(bgColor);
            std::string hrLine = wallColor + line(length, hrChar) + br() + reset();

            std::ostringstream os;
            os << br() << hrLine;

            for (size_t i = 0; i < padding; i++)
                os << wallColor << leftBorder << reset() << fill
                   << std::string(innerWidth, ' ') << reset()
                   << wallColor << rightBorder << reset() << "\n";

            os << wallColor << leftBorder << reset()
               << fill << " " << std::string(padding, ' ') << content << std::string(padding, ' ') << " " << reset()
               << wallColor << rightBorder << reset() << "\n";

            for (size_t i = 0; i < padding; i++)
                os << wallColor << leftBorder << reset() << fill
                   << std::string(innerWidth, ' ') << reset()
                   << wallColor << rightBorder << reset() << "\n";

            os << hrLine;
            return os.str();
        }

        inline std::string table(const std::vector<std::string> &text, Border style, const ans::IntRGB255 &textColor, const ans::IntRGB255 &bgColor, const ans::IntRGB255 &borderColor)
        {
            std::ostringstream os;

            if (text.empty())
                return os.str();

            std::vector<std::string> validStr(text.size());

            size_t maxLength = 0;
            for (size_t r = 0; r < text.size(); r++)
            {
                validStr[r] = validate_box_content(text[r]);
                if (validStr[r].length() > maxLength)
                    maxLength = validStr[r].length();
            }

            BorderStyle wall = BorderStyle::wall(style);
            std::string wallLeft = wall.get_left();
            std::string wallRight = wall.get_right();
            std::string outerChar = wall.get_outer();
            std::string innerChar = wall.get_inner();

            std::string borderColorStr = fg_color(borderColor);
            std::string contentColorStr = fg_color(textColor) + bg_color(bgColor);

            size_t length = maxLength + wallLeft.length() + wallRight.length() + 2;

            os << borderColorStr << str::hr(length, outerChar, 1);

            for (size_t i = 0; i < text.size(); i++)
            {
                os << borderColorStr
                   << wallLeft << contentColorStr << " " << validStr[i]
                   << std::string(maxLength - validStr[i].length(), ' ')
                   << " " << reset()
                   << borderColorStr
                   << wallRight
                   << str::hr(length, (i + 1 < text.size()) ? innerChar : outerChar, 1);
            }
            os << reset();

            return os.str();
        }

        inline std::string ordered_list(const std::vector<std::string> &Element)
        {
            std::ostringstream out;
            size_t length = std::to_string(Element.size()).length();

            for (size_t i = 0; i < Element.size(); i++)
            {
                if ((i) < Element.size() - 1)
                {
                    out << " [ " << std::setfill('0') << std::setw(length) << i + 1 << " ] " << Element.at(i) << "\n\n";
                }
                else
                {
                    out << " [ " << std::setfill('0') << std::setw(length) << i + 1 << " ] " << Element.at(i) << "\n";
                }
            }
            return out.str();
        }

        inline std::string unordered_list(const std::vector<std::string> &Element)
        {
            std::ostringstream out;
            size_t length = std::to_string(Element.size()).length();

            for (size_t i = 0; i < Element.size(); i++)
            {
                if ((i) < Element.size() - 1)
                {
                    out << " [#] " << Element.at(i) << "\n\n";
                }
                else
                {
                    out << " [#] " << Element.at(i) << "\n";
                }
            }
            return out.str();
        }


        
        inline std::string ordered_menu(const std::string &header, const std::vector<std::string> &Element)
        {
            std::ostringstream out;
            out << "\n";
            out << str::box(header, tui::Border::bold, 0);

            out << str::hr(80, "=", 2);
            out << ordered_list(Element);
            out << str::hr(80, "=", 2);
            out << " # Enter choice [ 1 , " << Element.size() << " ] to Select or [0] to go back : ";
            return out.str();
        }

        inline std::string ordered_list(const std::vector<std::vector<std::string>> &Element)
        {
            std::ostringstream out;
            if (Element.empty() || Element[0].empty())
                return out.str();
            size_t rowN = Element.size();
            size_t colN = Element[0].size();
            size_t auto_width = 0;

            for (size_t i = 0; i < rowN; i++)
            {
                for (size_t j = 0; j < colN; j++)
                {
                    std::string elementOutput = " [ " + std::to_string(i + 1) + std::to_string(j + 1) + " ] " + Element[i][j];
                    if (auto_width < elementOutput.length())
                    {
                        auto_width = elementOutput.length();
                    }
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
                if ((i) < Element.size() - 1)
                {
                    out << "\n\n";
                }
                else
                {
                    out << "\n";
                }
            }

            return out.str();
        }



        inline std::string unordered_list(const std::vector<std::vector<std::string>> &Element)
        {
            std::ostringstream out;
            if (Element.empty() || Element[0].empty())
                return out.str();
            size_t rowN = Element.size();
            size_t colN = Element[0].size();
            size_t auto_width = 0;

            for (size_t i = 0; i < rowN; i++)
            {
                for (size_t j = 0; j < colN; j++)
                {
                    std::string elementOutput = " [#] " + Element[i][j];
                    if (auto_width < elementOutput.length())
                    {
                        auto_width = elementOutput.length();
                    }
                }
            }

            auto_width += 1;

            for (size_t i = 0; i < rowN; i++)
            {

                for (size_t j = 0; j < colN; j++)
                {
                    std::string elementOutput = " [#] " + Element[i][j];
                    out << std::left << std::setw(static_cast<int>(auto_width)) << elementOutput;
                }
                if ((i) < Element.size() - 1)
                {
                    out << "\n\n";
                }
                else
                {
                    out << "\n";
                }
            }

            return out.str();
        }

        inline std::string ordered_menu(const std::string &header, const std::vector<std::vector<std::string>> &Element)
        {
            std::ostringstream out;
            out << "\n";
            out << box(header);
            out << str::hr(80, "=", 2);
            out << ordered_list(Element);
            out << str::hr(80, "=", 2);
            out << " # Enter choice [ 11 , " << Element.size() << Element[0].size() << " ] to Select or [0] to go back : ";
            return out.str();
        }

        inline std::string edit_precision(long double number, int precision1, int precision2)
        {
            std::ostringstream os;
            os << std::setprecision(precision1) << number;
            os.unsetf(std::ios::scientific);
            os.unsetf(std::ios::fixed);
            os << std::setprecision(precision2);
            return os.str();
        }

    } // namespace str

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

        inline std::string color(const size_t color) const
        {
            std::ostringstream os;
            if (color <= 0)
            {
                os << "\033[0m" << content() << "\033[0m";
            }
            else if (color <= 16)
            {
                static const char *basic_colors[] = {"0", "30", "31", "32", "33", "34", "35", "36", "37", "90", "91", "92", "93", "94", "95", "96", "97"};
                os << "\033[" << basic_colors[color] << "m" << content() << "\033[0m";
            }
            else if (color < 256)
            {
                os << "\033[38;5;" << color << "m" << content() << "\033[0m";
            }
            return os.str();
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

        inline std::string bold() const { return "\033[1m" + content() + "\033[0m"; }
        inline std::string dim() const { return "\033[2m" + content() + "\033[0m"; }
        inline std::string italic() const { return "\033[3m" + content() + "\033[0m"; }
        inline std::string underline() const { return "\033[4m" + content() + "\033[0m"; }
        inline std::string blink() const { return "\033[5m" + content() + "\033[0m"; }
        inline std::string rblink() const { return "\033[6m" + content() + "\033[0m"; }
        inline std::string reversed() const { return "\033[7m" + content() + "\033[0m"; }
        inline std::string conceal() const { return "\033[8m" + content() + "\033[0m"; }
        inline std::string crossed() const { return "\033[9m" + content() + "\033[0m"; }
        inline std::string double_underline() const { return "\033[21m" + content() + "\033[0m"; }
        inline std::string curly_underline() const { return "\033[4:3m" + content() + "\033[24m"; }
        inline std::string overline() const { return "\033[53m" + content() + "\033[55m"; }

        inline std::string separate(const unsigned int space_length = 1) const
        {
            std::ostringstream os;
            std::string cleaned = str::ignore_spaces(content());
            os << cleaned[0];
            for (size_t i = 1; i < cleaned.length(); i++)
            {
                os << std::string(space_length, ' ') << cleaned[i];
            }
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

        inline std::string border(tui::Border style = tui::Border::bold) const { return str::box(content(), style, 0); }

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
            print << str::cls(Screen::view);
            break;
        case Screen::full:
            print << str::cls(Screen::full);
            break;
        default:
            break;
        }
    }

#endif

#if defined(RANG_DOT_HPP) && !defined(CORNATUI_DISABLE_RANG_DOT_HPP)

    inline void init_terminal()
    {
        rang::setControlMode(rang::control::Auto);
        rang::setWinTermMode(rang::winTerm::Auto);
    }

    inline void set_color_mode(rang::control mode = rang::control::Auto) { rang::setControlMode(mode); }

    inline void set_win_term_mode(rang::winTerm mode = rang::winTerm::Auto) { rang::setWinTermMode(mode); }

    inline void disable_color() { rang::setControlMode(rang::control::Off); }

    inline void fg_color(const int color, std::ostream &print = std::cout)
    {
        static const rang::fg fg_codes[8] = {rang::fg::black, rang::fg::red, rang::fg::green, rang::fg::yellow, rang::fg::blue, rang::fg::magenta, rang::fg::cyan, rang::fg::gray};
        static const rang::fgB fgB_codes[8] = {rang::fgB::black, rang::fgB::red, rang::fgB::green, rang::fgB::yellow, rang::fgB::blue, rang::fgB::magenta, rang::fgB::cyan, rang::fgB::gray};

        if (color <= 0)
        {
            print << rang::fg::reset;
        }
        else if (color <= 8)
        {
            print << fg_codes[color - 1];
        }
        else if (color <= 16)
        {
            print << fgB_codes[color - 9];
        }
        else if (color < 256)
        {
            print << "\033[38;5;" << color << "m";
        }
    }

    inline void bg_color(const int color, std::ostream &print = std::cout)
    {
        static const rang::bg bg_codes[8] = {rang::bg::black, rang::bg::red, rang::bg::green, rang::bg::yellow, rang::bg::blue, rang::bg::magenta, rang::bg::cyan, rang::bg::gray};
        static const rang::bgB bgB_codes[8] = {rang::bgB::black, rang::bgB::red, rang::bgB::green, rang::bgB::yellow, rang::bgB::blue, rang::bgB::magenta, rang::bgB::cyan, rang::bgB::gray};

        if (color <= 0)
        {
            print << rang::bg::reset;
        }
        else if (color <= 8)
        {
            print << bg_codes[color - 1];
        }
        else if (color <= 16)
        {
            print << bgB_codes[color - 9];
        }
        else if (color < 256)
        {
            print << "\033[48;5;" << color << "m";
        }
    }

    inline void font_style(const int style, std::ostream &print = std::cout)
    {
        static const rang::style style_codes[9] = {
            rang::style::bold, rang::style::dim, rang::style::italic, rang::style::underline,
            rang::style::blink, rang::style::rblink, rang::style::reversed, rang::style::conceal, rang::style::crossed};

        if (style <= 0)
        {
            print << rang::style::reset;
        }
        else if (style <= 9)
        {
            print << style_codes[style - 1];
        }
    }

    inline void reset(std::ostream &print = std::cout) { print << rang::style::reset; }

#else

#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)

    inline void init_terminal()
    {

        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);

        HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
        if (h_out != INVALID_HANDLE_VALUE)
        {
            DWORD dw_mode = 0;
            if (GetConsoleMode(h_out, &dw_mode))
            {
                dw_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(h_out, dw_mode);
            }
        }
    }

#else

    inline void init_terminal() { /*coming soon*/ }

#endif

    inline void fg_color(const int color, std::ostream &print = std::cout)
    {
        if (color <= 0)
        {
            print << "\033[0m";
        }
        else if (color <= 16)
        {
            static const char *basic_colors[] = {"0", "30", "31", "32", "33", "34", "35", "36", "37", "90", "91", "92", "93", "94", "95", "96", "97"};
            print << "\033[" << basic_colors[color] << "m";
        }
        else if (color < 256)
        {
            print << "\033[38;5;" << color << "m";
        }
    }

    inline void bg_color(const int color, std::ostream &print = std::cout)
    {
        if (color <= 0)
        {
            print << "\033[0m";
        }
        else if (color <= 8)
        {
            print << "\033[" << (39 + color) << "m";
        }
        else if (color <= 16)
        {
            print << "\033[" << (91 + color) << "m";
        }
        else if (color < 256)
        {
            print << "\033[48;5;" << color << "m";
        }
    }

    inline void font_style(const int style, std::ostream &print = std::cout)
    {
        if (style <= 0)
        {
            print << "\033[0m";
        }
        else if (style <= 9)
        {
            print << "\033[" << style << "m";
        }
    }

    inline void reset(std::ostream &print = std::cout) { print << "\033[0m"; }

#endif

    static const std::string breakKeywords[] = {"0", "_n", "_f", "_q", "exit", "quit", "break", "false"};

    inline bool check_break_keywords(const std::string &user_input)
    {
        int size = sizeof(breakKeywords) / sizeof(breakKeywords[0]);
        for (int i = 0; i < size; i++)
        {
            if (breakKeywords[i] == user_input)
                return true;
        }
        return false;
    }

    namespace sound
    {

#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)

        inline void beep(DWORD frequency = 1024, DWORD durationMS = 512);
        inline void ring(std::ostream &print = std::cout);

        inline void beep(DWORD frequency, DWORD durationMS) { Beep(frequency, durationMS); }

        inline void ring(std::ostream &print) { print << '\a' << std::flush; }

#else

        inline void ring(std::ostream &print = std::cout);

        inline void ring(std::ostream &print) { print << '\a' << std::flush; }

#endif

    }

} // namespace tui

#endif