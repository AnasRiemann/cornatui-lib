#ifndef CORNATUI_COLOR
#define CORNATUI_COLOR

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "cornatui_math_utilities_ans.hpp"

/*

#define CORNATUI_DISABLE_WIN32
#define CORNATUI_DISABLE_RANG_DOT_HPP

*/

#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)

#include <windows.h>

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


        inline std::string fg_color(const ans::IntRGB255 &colorValue);
        inline std::string bg_color(const ans::IntRGB255 &colorValue);
        inline std::string fg_color(const unsigned int color);
        inline std::string bg_color(const unsigned int color);

    }

    namespace str
    {

        inline constexpr std::string_view bold = "\033[1m";
        inline constexpr std::string_view dim = "\033[2m";
        inline constexpr std::string_view italic = "\033[3m";
        inline constexpr std::string_view underline = "\033[4m";
        inline constexpr std::string_view blink = "\033[5m";
        inline constexpr std::string_view rblink = "\033[6m";
        inline constexpr std::string_view reversed = "\033[7m";
        inline constexpr std::string_view conceal = "\033[8m";
        inline constexpr std::string_view crossed = "\033[9m";
        inline constexpr std::string_view double_underline = "\033[21m";
        inline constexpr std::string_view curly_underline = "\033[4:3m";
        inline constexpr std::string_view overline = "\033[53m";
        inline constexpr std::string_view reset = "\033[0m";

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

    }




    namespace detail
    {

#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)
        struct TerminalState
        {
            UINT output_cp = 0;
            UINT input_cp = 0;
            DWORD stdout_mode = 0;
            DWORD stderr_mode = 0;
            bool captured = false;
        };

        inline TerminalState &terminal_state()
        {
            static TerminalState state;
            return state;
        }

#endif

    }

    inline bool init_terminal()
    {
        bool ok = true;

#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)
        auto &state = detail::terminal_state();

        if (!state.captured)
        {
            state.output_cp = GetConsoleOutputCP();
            state.input_cp = GetConsoleCP();

            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            HANDLE hErr = GetStdHandle(STD_ERROR_HANDLE);
            if (hOut != INVALID_HANDLE_VALUE)
                GetConsoleMode(hOut, &state.stdout_mode);
            if (hErr != INVALID_HANDLE_VALUE)
                GetConsoleMode(hErr, &state.stderr_mode);

            state.captured = true;
        }

        ok &= (SetConsoleOutputCP(65001) != 0);
        ok &= (SetConsoleCP(65001) != 0);

        auto enable_vt = [](DWORD stdHandle) -> bool
        {
            HANDLE h = GetStdHandle(stdHandle);
            if (h == INVALID_HANDLE_VALUE)
                return false;
            DWORD mode = 0;
            if (!GetConsoleMode(h, &mode))
                return false;
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            return SetConsoleMode(h, mode) != 0;
        };

        ok &= enable_vt(STD_OUTPUT_HANDLE);
        ok &= enable_vt(STD_ERROR_HANDLE);
#endif

        return ok;
    }

    inline void restore_terminal()
    {
#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)
        auto &state = detail::terminal_state();
        if (!state.captured)
            return;

        SetConsoleOutputCP(state.output_cp);
        SetConsoleCP(state.input_cp);

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE hErr = GetStdHandle(STD_ERROR_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE)
            SetConsoleMode(hOut, state.stdout_mode);
        if (hErr != INVALID_HANDLE_VALUE)
            SetConsoleMode(hErr, state.stderr_mode);
#endif
    }





}

#endif
