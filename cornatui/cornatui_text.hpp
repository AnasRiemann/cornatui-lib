#ifndef CORNATUI_TEXT
#define CORNATUI_TEXT

#include <cmath>
#include <vector>
#include<stdexcept>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>

#include <cctype>

#include "cornatui_math_utilities_ans.hpp"
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

        inline std::string separate(const std::string &text, const unsigned int space_length = 1);

        template <typename T>
        inline std::string to_scientific(T val, const unsigned int precision);
        template <typename T>
        inline std::string to_fixed_trimmed(T val, int precision);



        inline std::string center(const std::string &text, size_t width, const char fill = ' ');
        inline std::string truncate(const std::string &text, size_t maxLength, const std::string &ellipsis = "...");
        
        inline std::string translate(const std::string &content, const size_t x, const size_t y, Method translation_method = Method::padding);
        inline std::string br(const size_t numberOfLines = 1, Method translation_method = Method::padding);
        inline std::string space(const size_t width, Method translation_method = Method::padding);

        inline std::string hr(const size_t width = 80, const char style = '-');
        inline std::string hr(const size_t width, const std::string &style, const size_t numberOfLines = 1);
        inline std::string line(const size_t width, const char style);
        inline std::string line(const size_t width, const std::string &style);

    }

    namespace str
    {

        inline std::string ignore_character(const std::string &input, const char character)
        {
            std::string result;
            for (unsigned char c : input)
            {
                if (c != character)
                {
                    result.push_back(c);
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

            for (unsigned char c : input)
            {
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
            std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
                           { return std::tolower(c); });
            return result;
        }

        inline std::string uppercase(const std::string &text)
        {
            std::string result = text;
            std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
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
            if (text.empty())return "";

            std::ostringstream os;
            std::string cleaned = trim(text);
            for (unsigned char c : cleaned) {os << c << std::string(space_length, ' ');}
            return rtrim(os.str());
        }

        template <typename T>
        inline std::string to_scientific(T val, const unsigned int precision)
        {
            std::ostringstream oss;
            oss << std::scientific << std::setprecision(precision) << val;
            return oss.str();
        }

        template <typename T>
        inline std::string to_fixed_trimmed(T val, int precision)
        {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(precision) << val;
            std::string s = oss.str();
            if (s.find('.') != std::string::npos)
            {
            size_t lastNonZero = s.find_last_not_of('0');if (s[lastNonZero] == '.')lastNonZero--;s.erase(lastNonZero + 1);
            }
            if (s == "-0")s = "0";
            return s;
        }


        inline std::string center(const std::string &text, size_t width, const char fill)
        {
            std::string validText = get_ascii_only(text); 
            if (validText.length() >= width)
                return validText;
            size_t totalPad = width - validText.length();
            size_t left = totalPad / 2;
            return std::string(left, fill) + validText + std::string(totalPad - left, fill);
        }

        inline std::string truncate(const std::string &text, size_t maxLength, const std::string &ellipsis)
        {
            std::string validText = get_ascii_only(text);
            if (validText.length() <= maxLength)
                return validText;
            if (maxLength <= ellipsis.length())
                return validText.substr(0, maxLength);
            return validText.substr(0, maxLength - ellipsis.length()) + ellipsis;
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


    }

    class Text
    {
    private:
        std::string content_;

        inline void get_ascii_only(const std::string &input) { content_ = str::get_ascii_only(input); }

        inline std::string initialize_ansi_effects(const std::string &ansi_code, const std::string &content) const
        {
            std::string result;
            result.reserve(ansi_code.length() + content.length() + str::reset.length());

            result += ansi_code;
            result += content;
            result += std::string(str::reset);

            return result;
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

        inline std::string color(const ans::IntRGB255 &colorIndex) const { return initialize_ansi_effects(str::fg_color(colorIndex), content()); }
        inline std::string bg_color(const ans::IntRGB255 &colorIndex) const { return initialize_ansi_effects(str::bg_color(colorIndex), content()); }
        inline std::string color(const unsigned int &colorIndex) const { return initialize_ansi_effects(str::fg_color(colorIndex), content()); }
        inline std::string bg_color(const unsigned int &colorIndex) const { return initialize_ansi_effects(str::bg_color(colorIndex), content()); }

        inline std::string colorful(unsigned int start = 0, unsigned int end = 255, bool enableRGB = true) const
        {
            auto fgColor = [&]()
            { return ((enableRGB) ? str::fg_color(ans::IntRGB255(ans::get_random_number(start, end), ans::get_random_number(start, end), ans::get_random_number(start, end))) : str::fg_color(ans::get_random_number(start, end))); };
            std::ostringstream colorfulText;
            for (unsigned char c : content())
            {
                colorfulText << fgColor() << c << std::string(str::reset);
            }
            return colorfulText.str();
        }

        inline std::string bg_colorful(unsigned int start = 0, unsigned int end = 255, bool enableRGB = true) const
        {
            auto bgColor = [&]()
            { return ((enableRGB) ? str::bg_color(ans::IntRGB255(ans::get_random_number(start, end), ans::get_random_number(start, end), ans::get_random_number(start, end))) : str::bg_color(ans::get_random_number(start, end))); };
            std::ostringstream colorfulText;
            for (unsigned char c : content())
            {
                colorfulText << bgColor() << c << std::string(str::reset);
            }
            return colorfulText.str();
        }

        inline std::string bold() const { return initialize_ansi_effects(std::string(str::bold), content()); }
        inline std::string dim() const { return initialize_ansi_effects(std::string(str::dim), content()); }
        inline std::string italic() const { return initialize_ansi_effects(std::string(str::italic), content()); }
        inline std::string underline() const { return initialize_ansi_effects(std::string(str::underline), content()); }
        inline std::string blink() const { return initialize_ansi_effects(std::string(str::blink), content()); }
        inline std::string rblink() const { return initialize_ansi_effects(std::string(str::rblink), content()); }
        inline std::string reversed() const { return initialize_ansi_effects(std::string(str::reversed), content()); }
        inline std::string conceal() const { return initialize_ansi_effects(std::string(str::conceal), content()); }
        inline std::string crossed() const { return initialize_ansi_effects(std::string(str::crossed), content()); }
        inline std::string double_underline() const { return initialize_ansi_effects(std::string(str::double_underline), content()); }
        inline std::string curly_underline() const { return initialize_ansi_effects(std::string(str::curly_underline), content()); }
        inline std::string overline() const { return initialize_ansi_effects(std::string(str::overline), content()); }

        inline Text lowercase() const { return Text(str::lowercase(content())); }
        inline Text uppercase() const { return Text(str::uppercase(content())); }
        inline Text reverse() const { return Text(str::reverse(content())); }
        inline Text separate(const unsigned int padding) const { return Text(str::separate(content(), padding)); }

        static std::string merge(const std::vector<std::string> &paragraph)
        {
            if (paragraph.empty())throw std::invalid_argument("The vector is empty");

            std::ostringstream os;
            for (const std::string &word : paragraph){os << word;}
            return os.str();
        }


    };


  

}

#endif
