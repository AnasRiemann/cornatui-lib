
#ifndef CORNATUI_PAGE
#define CORNATUI_PAGE

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>


#include "cornatui_math_utilities_ans.hpp"
#include "cornatui_color.hpp"
#include "cornatui_text.hpp"
#include "cornatui_table.hpp"

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

    enum class Page : int
    {
        list = 0,
        paragraph = 1,
        confirm = 2

    };

    namespace str
    {
         
        inline std::string ordered_menu_list(const std::vector<std::string> &Element);
        inline std::string unordered_menu_list(const std::vector<std::string> &Element);
        inline std::string ordered_menu(const std::string &header, const std::vector<std::string> &Element);

        inline std::string unordered_menu_list(const std::vector<std::vector<std::string>> &Element);
        inline std::string ordered_menu_list(const std::vector<std::vector<std::string>> &Element);
        
        inline std::string ordered_menu(const std::string &header, const std::vector<std::vector<std::string>> &Element);

        inline std::vector<std::string> prefix_each(const std::vector<std::string> &list, const std::function<std::string(unsigned int)> &prefix = [](unsigned int i){ return "[ " + std::to_string(i + 1) + " ] "; });
        template <typename T>
        inline std::string join(const std::vector<T> &elements, const std::function<std::string(const T &element)> &formatter);
    }

    namespace str
    {

    

        
        inline std::string ordered_menu_list(const std::vector<std::string> &Element)
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

        inline std::string unordered_menu_list(const std::vector<std::string> &Element)
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
            out << ordered_menu_list(Element);
            out << str::hr(80, "=", 2);
            out << " # Enter choice [ 1 , " << Element.size() << " ] to Select or [0] to go back : ";
            return out.str();
        }

        inline std::string ordered_menu_list(const std::vector<std::vector<std::string>> &Element)
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



        inline std::string unordered_menu_list(const std::vector<std::vector<std::string>> &Element)
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
            out << ordered_menu_list(Element);
            out << str::hr(80, "=", 2);
            out << " # Enter choice [ 11 , " << Element.size() << Element[0].size() << " ] to Select or [0] to go back : ";
            return out.str();
        }





        inline std::vector<std::string> prefix_each(const std::vector<std::string> &list, const std::function<std::string(unsigned int)> &prefix)
        {
            if (list.empty())
                throw std::invalid_argument("Error: vector is empty");
            std::vector<std::string> result;
            result.reserve(list.size());
            for (size_t i = 0; i < list.size(); ++i)
                result.push_back(prefix(static_cast<unsigned int>(i)) + list.at(i));
            return result;
        }

        template <typename T>
        inline std::string join(const std::vector<T> &elements, const std::function<std::string(const T &element)> &formatter)
        {
            if (elements.empty())throw std::invalid_argument("Error: vector is empty");
            std::ostringstream stream;
            for (const T &element : elements){stream << formatter(element);}
            return stream.str();
        }

        

    } // namespace str

} // namespace tui

#endif