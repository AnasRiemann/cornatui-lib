#ifndef CORNATUI_IO_HPP
#define CORNATUI_IO_HPP

#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <stdexcept>

#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)

#include <windows.h>
#include <conio.h>

#endif

#include "cornatui_time.hpp"


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


    namespace str
    {

        inline std::string cls(Screen mode = Screen::full);

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








    static constexpr std::array<std::string_view, 8> breakKeywords = {"0", "_n", "_f", "_q", "exit", "quit", "break", "false"};

    inline bool check_break_keywords(const std::string_view &user_input)
    {
        for (std::string_view i : breakKeywords)
        {
            if (i == user_input)
                return true;
        }
        return false;
    }

#if defined(_WIN32) && !defined(CORNATUI_DISABLE_WIN32)

    inline void pause(const std::string &message = " Press any Key to continue...", unsigned int duration = 50)
    {
        for (size_t i = 0; i < message.length(); i++)
        {
            std::cout << message[i];
            std::cout.flush();
            time::delay_ms(duration);
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

} // namespace tui

#endif // CORNATUI_IO_HPP
