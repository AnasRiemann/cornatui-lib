#ifndef CORNATUI_MATH_UTILITIES_ANS
#define CORNATUI_MATH_UTILITIES_ANS

#include <cmath>
#include <vector>
#include <functional>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>

#include <stdexcept>


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


namespace ans
{

    namespace constant
    {

        constexpr long double PI = 3.14159265358979323846L;
        constexpr long double EPSI = 1e-18L;

    }

    struct IntRGB255
    {
    private:
        unsigned char red_{0};
        unsigned char green_{0};
        unsigned char blue_{0};

        static unsigned int clamp_color(int val)
        {
            if (val < 0)
                return 0;
            if (val > 255)
                return 255;
            return static_cast<unsigned int>(val);
        }

        void validate_value_rgb(unsigned int r, unsigned int g, unsigned int b)
        {
            red_ = static_cast<unsigned char>(clamp_color(static_cast<int>((r > 255) ? 255 : r)));
            green_ = static_cast<unsigned char>(clamp_color(static_cast<int>((g > 255) ? 255 : g)));
            blue_ = static_cast<unsigned char>(clamp_color(static_cast<int>((b > 255) ? 255 : b)));
        }
        inline double luminance() const { return 0.299 * red() + 0.587 * green() + 0.114 * blue(); }

    public:
        IntRGB255() = default;

        IntRGB255(unsigned int r, unsigned int g, unsigned int b) { validate_value_rgb(r, g, b); }

        unsigned int red() const { return red_; }
        unsigned int green() const { return green_; }
        unsigned int blue() const { return blue_; }

        std::string to_hex() const
        {
            std::ostringstream os;
            os << "#"
               << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<int>(red_)
               << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<int>(green_)
               << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<int>(blue_);
            return os.str();
        }

        static IntRGB255 from_hex(const std::string &hex)
        {
            std::string h = (!hex.empty() && hex[0] == '#') ? hex.substr(1) : hex;
            if (h.length() != 6)
                return black();
            unsigned int r, g, b;
            std::istringstream(h.substr(0, 2)) >> std::hex >> r;
            std::istringstream(h.substr(2, 2)) >> std::hex >> g;
            std::istringstream(h.substr(4, 2)) >> std::hex >> b;
            return {r, g, b};
        }

        inline unsigned int to_ansi256() const
        {

            auto to6 = [](unsigned int c)
            { return static_cast<unsigned int>(std::round(c / 255.0 * 5.0)); };

            unsigned int r6 = to6(red()), g6 = to6(green()), b6 = to6(blue());

            return 16 + 36 * r6 + 6 * g6 + b6;
        }

        friend inline std::ostream &operator<<(std::ostream &os, const IntRGB255 &c) { return os << c.to_hex(); }

        inline bool operator==(const IntRGB255 &other) const { return red() == other.red() && green() == other.green() && blue() == other.blue(); }
        inline bool operator!=(const IntRGB255 &other) const { return !(*this == other); }

        inline IntRGB255 operator+(const IntRGB255 &color) const
        {
            return {
                clamp_color(static_cast<int>(red()) + static_cast<int>(color.red())),
                clamp_color(static_cast<int>(green()) + static_cast<int>(color.green())),
                clamp_color(static_cast<int>(blue()) + static_cast<int>(color.blue()))};
        }

        inline IntRGB255 operator-(const IntRGB255 &color) const
        {
            return {
                clamp_color(static_cast<int>(red()) - static_cast<int>(color.red())),
                clamp_color(static_cast<int>(green()) - static_cast<int>(color.green())),
                clamp_color(static_cast<int>(blue()) - static_cast<int>(color.blue()))};
        }

        static IntRGB255 white() { return {255, 255, 255}; }
        static IntRGB255 black() { return {0, 0, 0}; }

        inline IntRGB255 inverse() const { return white() - *this; }

        inline IntRGB255 brightness(const unsigned int value) const
        {
            unsigned int v = (value > 255) ? 255 : value;
            return {
                clamp_color(static_cast<int>(red()) * static_cast<int>(v)),
                clamp_color(static_cast<int>(green()) * static_cast<int>(v)),
                clamp_color(static_cast<int>(blue()) * static_cast<int>(v))};
        }

        inline IntRGB255 darkness(const unsigned int value) const
        {
            if (value == 0)
                return black();
            unsigned int v = (value > 255) ? 255 : value;
            return {
                clamp_color(static_cast<int>(red()) / static_cast<int>(v)),
                clamp_color(static_cast<int>(green()) / static_cast<int>(v)),
                clamp_color(static_cast<int>(blue()) / static_cast<int>(v))};
        }

        inline IntRGB255 scale(double factor) const
        {
            return {
                clamp_color(static_cast<int>(std::round(red() * factor))),
                clamp_color(static_cast<int>(std::round(green() * factor))),
                clamp_color(static_cast<int>(std::round(blue() * factor)))};
        }

        inline IntRGB255 lerp(const IntRGB255 &to, double t) const
        {
            t = (t < 0.0) ? 0.0 : (t > 1.0 ? 1.0 : t);
            return {
                clamp_color(static_cast<int>(std::round(red() + t * (static_cast<int>(to.red()) - static_cast<int>(red()))))),
                clamp_color(static_cast<int>(std::round(green() + t * (static_cast<int>(to.green()) - static_cast<int>(green()))))),
                clamp_color(static_cast<int>(std::round(blue() + t * (static_cast<int>(to.blue()) - static_cast<int>(blue())))))};
        }

        inline double distance(const IntRGB255 &other) const
        {
            double dr = static_cast<double>(red()) - other.red();
            double dg = static_cast<double>(green()) - other.green();
            double db = static_cast<double>(blue()) - other.blue();
            return std::sqrt(dr * dr + dg * dg + db * db);
        }

        inline IntRGB255 contrast() const { return (luminance() > 128.0) ? black() : white(); }
    };





    
    inline unsigned int count_character(const std::string &text, unsigned char character)
    {
        unsigned int count = 0;
        for (unsigned char c : text)
        {
            if (c == character)
                count++;
        }
        return count;
    }

    inline int get_random_number(int min, int max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }


template <typename number>
    inline number max_value(const std::vector<number> &numbers)
    {
        number max = numbers[0];
        for (size_t j = 1; j < numbers.size(); j++)
        {
            if (max < numbers[j])
            {
                max = numbers[j];
            }
        }

        return max;
    }



    template <typename T>
    inline bool is_integer(const T value) { return (std::abs(value - std::trunc(value)) < constant::EPSI) ? true : false; }

    template <typename T>
    inline T factorial(const T x)
    {
        if (x < 0)
            return 0;
        T result = 1;
        for (T i = 2; i <= x; i++)
        {
            result *= i;
        }
        return result;
    }

    template <typename T>
    inline T get_sum(const T *array, const size_t size, const size_t I = 0)
    {
        T Total_sum = 0;

        for (size_t i = I; i < size; ++i)
        {
            Total_sum = Total_sum + array[i];
        }
        return Total_sum;
    }

    template <typename T>
    inline T get_product(const T *array, const size_t size, const size_t I = 0)
    {
        T Total_product = 1;
        for (size_t i = I; i < size; ++i)
        {
            Total_product = Total_product * array[i];
        }
        return Total_product;
    }

    template <typename T>
    inline std::vector<T> apply_function_sequence(const std::vector<T> &numberSequence, std::function<T(T)> function)
    {
        if (numberSequence.empty())
            return {NAN};

        size_t size = numberSequence.size();
        std::vector<T> Sequence(size, 0);

        for (size_t i = 0; i < size; i++)
        {
            Sequence[i] = function(numberSequence[i]);
        }
        return Sequence;
    }

    template <typename T>
    inline T cycle(const T num1, const T num2 = 2) { return ((is_integer(num1) && is_integer(num2)) ? num1 % num2 : std::fmod(num1, num2)); }



}

#endif