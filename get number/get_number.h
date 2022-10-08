#ifndef GET_NUMBER_H
#define GET_NUMBER_H

#include <iostream>
#include <iomanip>
#include <climits>

enum class Types_Range
{
    UCHAR = 3,
    CHAR = 3,
    SHORT = 5,
    USHORT = 5,
    INT = 10,
    UINT = 10,
    LONG = 10,
    ULONG = 10,
    FLOAT = 10,
    DOUBLE = 19,
    ERROR = -1,
};

using range_t = Types_Range;

range_t getRange(const std::string type)
{
    if (type == "c")
        return range_t::CHAR;
    if (type == "h")
        return range_t::UCHAR;
    if (type == "s")
        return range_t::SHORT;
    if (type == "t")
        return range_t::USHORT;
    if (type == "i")
        return range_t::INT;
    if (type == "j")
        return range_t::UINT;
    if (type == "l")
        return range_t::LONG;
    if (type == "m")
        return range_t::ULONG;
    if (type == "f")
        return range_t::FLOAT;
    if (type == "d")
        return range_t::DOUBLE;

    return range_t::ERROR;
}

template <class T>
T getNumber()
{
    T number;

    range_t range = getRange(typeid(T).name());

    if (range == range_t::ERROR)
        throw std::runtime_error("Invalid type");

    std::cin >> std::setw(static_cast<std::int16_t>(range)) >> number;

    if (std::cin.fail())
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();
        throw std::runtime_error("Invalid number");
    }
    else
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.gcount() > 1)
            throw std::runtime_error("Invalid number");
    }

    return number;
}


#endif // GET_NUMBER_H

