
#ifndef CORNATUI
#define CORNATUI


#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>



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



#include "cornatui_math_ans.hpp"
#include "cornatui_color.hpp"
#include "cornatui_text.hpp"
#include "cornatui_table.hpp"
#include "cornatui_page.hpp"
namespace tui
{

  


    // ---- small utilities ----

    namespace str
    {


        

 

    }



    namespace str
    {

   

    } // namespace str



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