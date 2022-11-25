#include "integration.h"
#include <iostream>

constexpr double f_examp(Point p)
{
    return p.x*p.x + p.y*p.y + p.z*p.z;
}

int main()
{
    static_assert(integration::volumeIntegrate(f_examp) == 8, "NOT OK");
    return 0;
}
