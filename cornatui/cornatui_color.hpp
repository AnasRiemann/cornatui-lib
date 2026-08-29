#ifndef CORNATUI_COLOR
#define CORNATUI_COLOR


#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>


#include "cornatui_math_ans.hpp"


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



   namespace str
   {

        inline std::string fg_color(const unsigned int r, const unsigned int g, const unsigned int b);
        inline std::string bg_color(const unsigned int r, const unsigned int g, const unsigned int b);
        inline std::string fg_color(const ans::IntRGB255 &colorValue);
        inline std::string bg_color(const ans::IntRGB255 &colorValue);
        inline std::string fg_color(const unsigned int color);
        inline std::string bg_color(const unsigned int color);
        inline std::string bold();
        inline std::string dim();
        inline std::string italic();
        inline std::string underline();
        inline std::string blink();
        inline std::string rblink();
        inline std::string reversed();
        inline std::string conceal();
        inline std::string crossed();
        inline std::string double_underline();
        inline std::string curly_underline();
        inline std::string overline();
        inline std::string reset();


   }


    namespace str
    {

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

        inline std::string bold()             { return "\033[1m"; }
        inline std::string dim()              { return "\033[2m"; }
        inline std::string italic()           { return "\033[3m"; }
        inline std::string underline()        { return "\033[4m"; }
        inline std::string blink()            { return "\033[5m"; }
        inline std::string rblink()           { return "\033[6m"; }
        inline std::string reversed()         { return "\033[7m"; }
        inline std::string conceal()          { return "\033[8m"; }
        inline std::string crossed()          { return "\033[9m"; }
        inline std::string double_underline() { return "\033[21m"; }
        inline std::string curly_underline()  { return "\033[4:3m"; }
        inline std::string overline()         { return "\033[53m"; }
        inline std::string reset()            { return "\033[0m"; }

    }

    


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



}




#endif
