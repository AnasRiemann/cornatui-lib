
#ifndef CORNATUI
#define CORNATUI

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>
#include <atomic>
#include <cstdlib>
#include <cstring>

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



        inline std::string translate(const std::string &content, const size_t x, const size_t y, Method translation_method = Method::padding);
        inline std::string br(const size_t numberOfLines = 1 , Method translation_method = Method::padding);
        inline std::string space(const size_t width , Method translation_method =  Method::padding );



        inline std::string fg_color(const unsigned int r, const unsigned int g, const unsigned int b);
        inline std::string bg_color(const unsigned int r, const unsigned int g, const unsigned int b);
        inline std::string fg_color(const unsigned int color);
        inline std::string bg_color(const unsigned int color); 
        inline std::string cls(Screen mode = Screen::full);
        inline std::string reset();



    
        inline std::string hr(const std::size_t width = 80, const char style = '-');
        inline std::string hr(const size_t width, const std::string &style, const size_t numberOfLines = 1);

        inline std::string border(const std::string &abc, Border style = Border::single);
    
        inline std::string ordered_list(const std::vector<std::string> &Element);
        inline std::string unordered_list(const std::vector<std::string> &Element);
        inline std::string create_page(const std::string &header, const std::vector<std::string> &Element);

        inline std::string unordered_list(const std::vector<std::vector<std::string>> &Element);
        inline std::string ordered_list(const std::vector<std::vector<std::string>> &Element);
        inline std::string create_page(const std::string &header, const std::vector<std::vector<std::string>> &Element);

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


        
        inline std::string br(const size_t numberOfLines , Method translation_method)
        { 
         switch (translation_method)
         {
         case Method::padding:return std::string(numberOfLines, '\n'); break;
         
         case Method::ansi:return "\033[" + std::to_string (numberOfLines) + "B"; break;
         default:return "";break;
         }
        
            return "";
        }

        inline std::string space(const size_t width , Method translation_method)
        {
         switch (translation_method)
         {
         case Method::padding:return std::string(width, ' '); break;
         
         case Method::ansi:return "\033[" + std::to_string (width) + "C"; break;
         default:return "";break;
         }
        
            return "";

        }




        inline std::string fg_color(const unsigned int color)
        {
            if (color == 0)
            {
                return "\033[0m";
            }

            else if (color <= 16)
            {
                static const char *basic_colors[] = {"0", "30", "31", "32", "33", "34", "35", "36", "37", "90", "91", "92", "93", "94", "95", "96", "97"};
                return "\033[" + std::string(basic_colors[color]) + "m";
            }

            else if (color < 256)
            {
                return "\033[38;5;" + std::to_string(color) + "m";
            }
            return "";
        }

        inline std::string bg_color(const unsigned int color)
        {
            if (color == 0)
            {
                return "\033[0m";
            }
            else if (color <= 8)
            {
                return "\033[" + std::to_string(39 + color) + "m";
            }
            else if (color <= 16)
            {
                return "\033[" + std::to_string(91 + color) + "m";
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








        inline std::string hr(const std::size_t width, const char style) { return "\n" + std::string(width, style) + "\n"; }

        inline std::string hr(const size_t width, const std::string &style, const size_t numberOfLines)
        {
            if (style.empty() || width == 0)
                return "";
            std::string line;
            line.resize(width);
            for (size_t l = 0; l < width; l++)
            {
                line[l] = style[l % style.length()];
            }

            return "\n" + line + std::string(numberOfLines, '\n');
        }


        inline std::string border(const std::string &title, Border style)
        {
            std::ostringstream line;
            std::string abc ;
            abc.reserve(title.size());
            for (char c : title) /*size_t i = 0; i < title.length(); i++*/{if (c != '\n' && c != '\r' && c != '\t') { abc.push_back(c); }}

            size_t length = abc.length() + 6;

            switch (style)
            {
            case Border::single:
                line << str::hr(length, "-", 1) << "|  " << abc << "  |" << str::hr(length, "-", 1);
                break;
            case Border::bold:
                line << str::hr(length, "=", 1) << "|| " << abc << " ||" << str::hr(length, "=", 1);
                break;
            case Border::star:
                line << str::hr(length, ".", 1) << "*  " << abc << "  *" << str::hr(length, "*", 1);
                break;
            case Border::hash:
                line << str::hr(length, "#", 1) << "#  " << abc << "  #" << str::hr(length, "#", 1);
                break;
            case Border::cross:
                line << str::hr(length, "+", 1) << "=- " << abc << " -=" << str::hr(length, "+", 1);
                break;
            case Border::wave:
                line << str::hr(length, "~", 1) << "~  " << abc << "  ~" << str::hr(length, "~", 1);
                break;

            default:
                line << str::hr(length, "-", 1) << "|  " << abc << "  |" << str::hr(length, "-", 1);
                break;
            }
            return line.str();
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
                    out << " [#] "<< Element.at(i) << "\n\n";
                }
                else
                {
                    out << " [#] " << Element.at(i) << "\n";
                }
            }
            return out.str();
        }



        inline std::string create_page(const std::string &header, const std::vector<std::string> &Element)
        {
            std::ostringstream out;
            out << "\n";
            out << str::border(header, tui::Border::bold);

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
                    std::string elementOutput =  " [#] " + Element[i][j];
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


        

        inline std::string create_page(const std::string &header, const std::vector<std::vector<std::string>> &Element)
        {
            std::ostringstream out;
            out << "\n";
            out << border(header);
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

        inline std::string border(tui::Border style = tui::Border::bold) const
        {
            return str::border(content(), style);
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

    




#if defined(RANG_DOT_HPP)&& ! defined(CORNATUI_DISABLE_RANG_DOT_HPP)

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
        if (color <= 0)
        {
            print << rang::fg::reset;
        }
        else if (color <= 16)
        {
            switch (color)
            {
            case 1:
                print << rang::fg::black;
                break;
            case 2:
                print << rang::fg::red;
                break;
            case 3:
                print << rang::fg::green;
                break;
            case 4:
                print << rang::fg::yellow;
                break;
            case 5:
                print << rang::fg::blue;
                break;
            case 6:
                print << rang::fg::magenta;
                break;
            case 7:
                print << rang::fg::cyan;
                break;
            case 8:
                print << rang::fg::gray;
                break;
            case 9:
                print << rang::fgB::black;
                break;
            case 10:
                print << rang::fgB::red;
                break;
            case 11:
                print << rang::fgB::green;
                break;
            case 12:
                print << rang::fgB::yellow;
                break;
            case 13:
                print << rang::fgB::blue;
                break;
            case 14:
                print << rang::fgB::magenta;
                break;
            case 15:
                print << rang::fgB::cyan;
                break;
            case 16:
                print << rang::fgB::gray;
                break;
            default:
                print << rang::fg::reset;
                break;
            }
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
            print << rang::bg::reset;
        }
        else if (color <= 16)
        {
            switch (color)
            {
            case 1:
                print << rang::bg::black;
                break;
            case 2:
                print << rang::bg::red;
                break;
            case 3:
                print << rang::bg::green;
                break;
            case 4:
                print << rang::bg::yellow;
                break;
            case 5:
                print << rang::bg::blue;
                break;
            case 6:
                print << rang::bg::magenta;
                break;
            case 7:
                print << rang::bg::cyan;
                break;
            case 8:
                print << rang::bg::gray;
                break;
            case 9:
                print << rang::bgB::black;
                break;
            case 10:
                print << rang::bgB::red;
                break;
            case 11:
                print << rang::bgB::green;
                break;
            case 12:
                print << rang::bgB::yellow;
                break;
            case 13:
                print << rang::bgB::blue;
                break;
            case 14:
                print << rang::bgB::magenta;
                break;
            case 15:
                print << rang::bgB::cyan;
                break;
            case 16:
                print << rang::bgB::gray;
                break;
            default:
                print << rang::bg::reset;
                break;
            }
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
            print << rang::style::reset;
        }
        else if (style <= 9)
        {
            switch (style)
            {
            case 1:
                print << rang::style::bold;
                break;
            case 2:
                print << rang::style::dim;
                break;
            case 3:
                print << rang::style::italic;
                break;
            case 4:
                print << rang::style::underline;
                break;
            case 5:
                print << rang::style::blink;
                break;
            case 6:
                print << rang::style::rblink;
                break;
            case 7:
                print << rang::style::reversed;
                break;
            case 8:
                print << rang::style::conceal;
                break;
            case 9:
                print << rang::style::crossed;
                break;
            default:
                print << rang::style::reset;
                break;
            }
        }
    }

    inline void reset(std::ostream &print = std::cout) { print << rang::style::reset; }

#else

    inline void init_terminal() { /* no-op */ }

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
    
   



    inline void br(const size_t numberOfLines = 1, std::ostream &print = std::cout) { print << str::br(numberOfLines); }

    inline void hr(const std::size_t width = 80, const char fillChar = '_', std::ostream &print = std::cout) { print << str::hr(width, fillChar); }

    inline void hr(int width, const std::string &style, const int numberOfLines = 1, std::ostream &print = std::cout) { print << str::hr(width, style, numberOfLines); }

    inline void create_border(const std::string &abc, Border style = Border::single, std::ostream &print = std::cout) { print << str::border(abc, style); }

    inline void create_ordered_list(const std::vector<std::string> &Element, std::ostream &print = std::cout) { print << str::ordered_list(Element); }

    inline void create_unordered_list(const std::vector<std::string> &Element, std::ostream &print = std::cout) { print << str::unordered_list(Element); }

    inline void create_page(const std::string &header, const std::vector<std::string> &Element, std::ostream &print = std::cout) { print << str::create_page(header, Element); }

    inline void create_ordered_list(const std::vector<std::vector<std::string>> &Element, std::ostream &print = std::cout) { print << str::ordered_list(Element); }

    inline void create_page(const std::string &header, const std::vector<std::vector<std::string>> &Element, std::ostream &print = std::cout) { print << str::create_page(header, Element); }



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