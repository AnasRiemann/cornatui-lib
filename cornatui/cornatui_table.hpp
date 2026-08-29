#ifndef CORNATUI_TABLE
#define CORNATUI_TABLE

#include <string>
#include <vector>
#include <sstream>


#include "cornatui_math_ans.hpp"
#include "cornatui_color.hpp"
#include "cornatui_text.hpp"



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

    enum class Border : int
    {
        single = 1,
        bold = 2,
        star = 3,
        hash = 4,
        cross = 5,
        wave = 6,
        mix = 7,
        zero = 8
    };

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
                case Border::mix:
                return BorderStyle("(#|", "|#)", "=", "~");
                  case Border::zero:
                return BorderStyle("|0|", "|0|", "o", "o");
            default:
                return BorderStyle("|", "|", "-", "-");
            }
        }

        std::string get_left() const { return leftchar_; }
        std::string get_right() const { return rightchar_; }
        std::string get_outer() const { return outerChar_; }
        std::string get_inner() const { return innerChar_; }
    };

    namespace str
    {

        inline std::string box(const std::string &abc, Border style = Border::single, const size_t padding = 0);
        inline std::string box(const std::string &abc, Border style, const ans::IntRGB255 &textColor, const ans::IntRGB255 &bgColor, const ans::IntRGB255 &borderColor, const size_t padding=0);
              inline std::string box(const std::string &abc, Border style,  const unsigned int textColor,  const unsigned int bgColor,  const unsigned int borderColor, const size_t padding=0);
        inline std::string table(const std::vector<std::string> &text, Border style, const ans::IntRGB255 &textColor, const ans::IntRGB255 &bgColor, const ans::IntRGB255 &borderColor, const size_t padding = 0);

        inline std::string table(const std::vector<std::string> &text, Border style, const unsigned int textColor, const unsigned int bgColor, const unsigned int borderColor, const size_t padding = 0);
        inline std::string table(const std::vector<std::string> &text, Border style, const size_t padding = 0);
    }

    namespace str
    {

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

        

        inline std::string box(const std::string &abc, Border style,  const unsigned int textColor,  const unsigned int bgColor,  const unsigned int borderColor, const size_t padding)
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










       
        inline std::string table(const std::vector<std::string> &text, Border style, const ans::IntRGB255 &textColor, const ans::IntRGB255 &bgColor, const ans::IntRGB255 &borderColor, const size_t padding)
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

            size_t length = maxLength + wallLeft.length() + wallRight.length() + 2 * padding + 2;

            os << borderColorStr << str::hr(length, outerChar, 1);

            for (size_t i = 0; i < text.size(); i++)
            {
                os << borderColorStr;

                for (size_t j = 0; j < padding; j++)
                {
                    os << borderColorStr << wallLeft << reset()
                       << contentColorStr
                       << std::string(maxLength + 2 * padding + 2, ' ')
                       << reset() << borderColorStr << wallRight << "\n";
                }

                os << borderColorStr
                   << wallLeft << contentColorStr
                   << std::string(padding, ' ') << ' ' << validStr[i]
                   << std::string(maxLength - validStr[i].length(), ' ')
                   << std::string(padding, ' ') << ' ' << reset()
                   << borderColorStr
                   << wallRight;

                for (size_t j = 0; j < padding; j++)
                {
                    os << "\n"
                       << borderColorStr << wallLeft << reset() << contentColorStr
                       << std::string(maxLength + 2 * padding + 2, ' ')
                       << reset() << borderColorStr << wallRight;
                }
                os << str::hr(length, (i + 1 < text.size()) ? innerChar : outerChar, 1);
            }
            os << reset();

            return os.str();
        }



        inline std::string table(const std::vector<std::string> &text, Border style, const unsigned int textColor, const unsigned int bgColor, const unsigned int borderColor, const size_t padding)
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

            size_t length = maxLength + wallLeft.length() + wallRight.length() + 2 * padding + 2;

            os << borderColorStr << str::hr(length, outerChar, 1);

            for (size_t i = 0; i < text.size(); i++)
            {
                os << borderColorStr;

                for (size_t j = 0; j < padding; j++)
                {
                    os << borderColorStr << wallLeft << reset()
                       << contentColorStr
                       << std::string(maxLength + 2 * padding + 2, ' ')
                       << reset() << borderColorStr << wallRight << "\n";
                }

                os << borderColorStr
                   << wallLeft << contentColorStr
                   << std::string(padding, ' ') << ' ' << validStr[i]
                   << std::string(maxLength - validStr[i].length(), ' ')
                   << std::string(padding, ' ') << ' ' << reset()
                   << borderColorStr
                   << wallRight;

                for (size_t j = 0; j < padding; j++)
                {
                    os << "\n"
                       << borderColorStr << wallLeft << reset() << contentColorStr
                       << std::string(maxLength + 2 * padding + 2, ' ')
                       << reset() << borderColorStr << wallRight;
                }
                os << str::hr(length, (i + 1 < text.size()) ? innerChar : outerChar, 1);
            }
            os << reset();

            return os.str();
        }







        inline std::string table(const std::vector<std::string> &text, Border style,const size_t padding)
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


            size_t length = maxLength + wallLeft.length() + wallRight.length() + 2 * padding + 2;

            os  << str::hr(length, outerChar, 1);

            for (size_t i = 0; i < text.size(); i++)
            {
               

                for (size_t j = 0; j < padding; j++)
                {
                    os << wallLeft << std::string(maxLength + 2 * padding + 2, ' ')<< wallRight << "\n";
                }

                os 
                   << wallLeft 
                   << std::string(padding, ' ') << ' ' << validStr[i]
                   << std::string(maxLength - validStr[i].length(), ' ')
                   << std::string(padding, ' ') << ' ' << reset()
                  
                   << wallRight;

                for (size_t j = 0; j < padding; j++)
                {
                os << "\n"<< wallLeft << std::string(maxLength + 2 * padding + 2, ' ')<< wallRight;
                }
                os << str::hr(length, (i + 1 < text.size()) ? innerChar : outerChar, 1);
            }
         

            return os.str();
        }

    }

}

#endif