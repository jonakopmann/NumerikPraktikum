#include <cmath>
#include <iostream>

#include "Utils.h"

long double Check(long double d)
{
    if (std::isnan(d) || !std::isfinite(d))
    {
        throw std::runtime_error("variable is nan or infinite.");
    }
    return d;
}