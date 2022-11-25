#include "integration.h"
#include <iostream>

constexpr double f(Point p)
{
    return p.x*p.x + p.y*p.y + p.z*p.z;
}

int main()
{
    static_assert(integration::volumeIntegrate(f) == 8, "OK");
    std::cout << integration::volumeIntegrate(f) << std::endl;
    return 0;
}
