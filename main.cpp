#include <iostream>
#include "MathArray.h"
#include "variable_vector.h"
#include "flux_integration.h"
#include <vector>

MathArray<double, 5> var(Point p) {
    MathArray<double, 5> a(0);
    for (int i = 0; i < 5; ++i) {
        a[i] = p.x*p.x + p.y*p.y + p.z*p.z;
    }
    return a;
}

constexpr double vard(Point p) {
    return p.x*p.x + p.y*p.y + p.z*p.z;
}

constexpr double var2d(Point2d p) {
    return p.x*p.x + p.y*p.y;
}

template <typename T>
constexpr T f_examp(T var) {
    return var;     
}

int main()
{
    //const std::array<double, GLOBAL::NDOFS3D> k{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    //constexpr SINGLE_VARIABLE varaa(k);
    VARIABLE_VECTOR vvector;
    std::array<double, GLOBAL::FULL_NDOFS> res;
    for (double& r : res) {
        r = 1.0;
    }

    vvector.store(res);
    std::cout << vvector._at(Point{0., 0., 0.}) << std::endl;
    flux_integration::FluxIntegration fli;
    
    std::cout << fli.Integrate(vvector, 0.5) << std::endl;

    //double a = -1.0;
    //double b = 1.0;
    //std::cout << integration::VolumeIntegrate<GLOBAL::NDEG1D>([&vvector](Point p){return f_examp(vvector._at(p));}, a, b) << std::endl;
    //static_assert(integration::VolumeIntegrate<GLOBAL::NDEG1D>([&varaa](Point p){return f_examp(vard(p));}) == 8, "NOT OK");
    //auto I = integration::VolumeIntegrate([](Point p){return f_examp(var(p));});
    //std::cout << integration::VolumeIntegrate<GLOBAL::NDEG1D>([&varaa](Point p){return f_examp(varaa._at(p));}, 0., 0.5) << std::endl;
    //std::cout << integration::SurfaceIntegrate<GLOBAL::NDEG1D>([&varaa](Point2d p){return f_examp(var2d(p));}, 0., 0.5) << std::endl;
    //std::cout << integration::LineIntegrate<GLOBAL::NDEG1D>([](double p){return f_examp(p);}) << std::endl;
    return 0;
}
