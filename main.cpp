#include "integration.h"
#include <iostream>

double f(Point p)
{
    return p.x*p.x;
}

int main()
{
    std::cout << integration::volumeIntegrate(f) << std::endl;
    return 0;
}
