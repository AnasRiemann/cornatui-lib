#ifndef  ANAS_MATH_HPP
#define  ANAS_MATH_HPP
#include <cmath>
#include<vector>
#include<functional>
#include <random>
#include <complex>
#include <algorithm>
namespace ans
{






namespace constant
{

constexpr long double PI = 3.14159265358979323846L;
constexpr long double EPSI = 1e-18L;

}


inline int get_random_number(int min, int max) 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}


inline int cycle(const int num1, const int num2 = 2)
{
if (num1 >= 0 && num2 >= 1){return (num1 % num2);}
else{return -1;}
}


inline long long cycle(const long long num1, const long long num2 = 2)
{
if (num1 >= 0 && num2 >= 1){return (num1 % num2);}
else{return -1;}
}





inline long double cycle(const long double num1, const long double num2 = 2) { return std::fmod(num1, num2); }



inline long double max_value(const long double *numarr, const int size, const int start = 0)
{
    long double max = numarr[start];
    for (int j = start + 1; j < size; j++)
    {
        if (max < numarr[j])
        {
            max = numarr[j];
        }
    }
    return max;
}

inline long double min_value(const long double *numarr, const int size, const int start = 0)
{
    long double min = numarr[start];
    for (int j = start + 1; j < size; j++)
    {
        if (min > numarr[j])
        {
            min = numarr[j];
        }
    }
    return min;
}

inline bool is_prime(const long long x)
{

    if (std::abs(x) < 2)
    {
        return false;
    }

    for (long long i = 2; i  <= std::abs(x) / i; i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }

    return true;
}


inline bool is_integer(const long double number){return (std::abs(number-std::trunc(number))<constant::EPSI) ? true : false;}


inline long long factorial(const int x)
{
    if (x < 0)return 0;

    long long result = 1;
    for (int i = 2; i <= x; i++)
    {
        result *= i;
    }
    return result;
}





inline long double get_sum(const long double *array, const long long size, const long long I = 0)
{
    long double Total_sum = 0;


    for (long long i = I; i < size; ++i)
    {
        Total_sum = Total_sum + array[i];
    }
    return Total_sum;
}





inline long double get_product(const long double *array, const long long size, const long long I = 0)
{
    long double Total_product = 1;

    for (long long i = I; i < size; ++i)
    {
        Total_product = Total_product * array[i];
    }
    return Total_product;
}




inline long double get_sum(const long long *array, const long long size, const long long I = 0)
{
    long double Total_sum = 0;

    for (long long i = I; i < size; ++i)
    {
        Total_sum = Total_sum + array[i];
    }
    return Total_sum;
}




inline long double get_product(const long long *array, const long long size, const long long I = 0)
{
    long double Total_product = 1;

    for (long long i = I; i < size; ++i)
    {
        Total_product = Total_product * array[i];
    }
    return Total_product;
}















inline std::vector<long double>apply_function_sequence(const std::vector<long double>&numberSequence ,long double (*functionPtr)(long double))
{

if(numberSequence.empty())return {NAN};

size_t size=numberSequence.size();
std::vector<long double>Sequence(size,0);
for(size_t i = 0;i<size;i++)
{
Sequence[i]=functionPtr(numberSequence[i]);

}
return Sequence;

}


inline std::vector<long double> apply_function_sequence(const std::vector<long double>& numberSequence, std::function<long double(long double)> function)
{
    if (numberSequence.empty()) return {NAN};

    size_t size = numberSequence.size();
    std::vector<long double> Sequence(size, 0);
    
    for (size_t i = 0; i < size; i++) 
    {
        Sequence[i] = function(numberSequence[i]);
    }
    return Sequence;
}



namespace unit
{


inline long double deg_rad(const long double angledeg)
{
    if(std::isnan(angledeg))return NAN;
    long double anglerad = angledeg * ( constant::PI / 180.0);
    return anglerad;
}

inline long double rad_deg(const long double anglerad)
{
    if(std::isnan(anglerad))return NAN;
    long double angledeg = anglerad / ( constant::PI / 180.0);
    return angledeg;
}

inline long double grad_rad(const long double anglegard)
{
    if(std::isnan(anglegard))return NAN;
    long double anglerad = anglegard * ( constant::PI / 200.0);
    return anglerad;
}
inline long double rad_grad(const long double anglerad)
{
     if(std::isnan(anglerad))return NAN;
    long double anglegard = anglerad / ( constant::PI / 200.0);
    return anglegard;
}

inline long double convert_angle(const long double angle, char input_type, char output_type)
{
    long double angle_input = angle;
    long double angle_output;

    if (input_type != output_type)
    {
        switch (input_type)
        {
        case 'D':
        case 'd':
            angle_input = deg_rad(angle_input);
            break;
        case 'R':
        case 'r':
            break;

        case 'G':
        case 'g':
            angle_input = grad_rad(angle_input);
            break;
        default:
        {
            angle_input = NAN;
            break;
        }
        }

        angle_output = cycle(angle_input, 2 *  constant::PI);

        switch (output_type)
        {
        case 'D':;
        case 'd':
            angle_output = rad_deg(angle_output);
            break;
        case 'r':;
        case 'R':
            angle_output = angle_input;
            break;
        case 'G':;
        case 'g':
            angle_output = rad_grad(angle_output);
            break;
        default:
        {
            angle_output = NAN;
            break;
        }
        }
    }
    else
    {
        angle_output = angle_input;
    }

    return angle_output;
}
 

inline long double min_s(const long double min) { return min * 60.0; }
inline long double s_min(const long double s) { return s / 60.0; }

inline long double hour_s(const long double hour) { return hour * 3600.0; }
inline long double s_hour(const long double s) { return s / 3600.0; }

inline long double day_s(const long double day) { return day * 86400.0; }
inline long double s_day(const long double s) { return s / 86400.0; }

inline long double convert_time(const long double time, char input_type, char output_type)
{
    long double time_input = time;
    long double time_output;

    if (input_type != output_type)
    {
        switch (input_type)
        {
        case 'S':
        case 's':
            time_input = time;
            break;
        case 'M':
        case 'm':
            time_input = min_s(time);
            break;
        case 'H':
        case 'h':
            time_input = hour_s(time);
            break;
        case 'D':
        case 'd':
            time_input = day_s(time);
            break;
        default:
        {
            time_input = NAN;
            break;
        }
        }

        time_output = time_input;

        switch (output_type)
        {
        case 'S':
        case 's':
            time_output = time_input;
            break;
        case 'M':
        case 'm':
            time_output = s_min(time_output);
            break;
        case 'H':
        case 'h':
            time_output = s_hour(time_output);
            break;
        case 'D':
        case 'd':
            time_output = s_day(time_output);
            break;
        default:
        {
            time_output = NAN;
            break;
        }
        }
    }
    else
    {
        time_output = time_input;
    }

    return time_output;
}


}










}



#endif