#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <type_traits>
#include <utility>
#include "quad.h"
#include "legendre.h"

#define WEIGHT3D(i, lx, ux, ly, uy, lz, uz) QUADRATURE::GET_VOL_GPOINT<NDEG1D, i>(lx, ux, ly, uy, lz, uz).weight
#define   ABSC3D(i, lx, ux, ly, uy, lz, uz) QUADRATURE::GET_VOL_GPOINT<NDEG1D, i>(lx, ux, ly, uy, lz, uz).node

#define WEIGHT2D(i, lx, ux, ly, uy) QUADRATURE::GET_SURF_GPOINT<NDEG1D, i>(lx, ux, ly, uy).weight
#define   ABSC2D(i, lx, ux, ly, uy) QUADRATURE::GET_SURF_GPOINT<NDEG1D, i>(lx, ux, ly, uy).node

#define WEIGHT1D(i, lx, ux) QUADRATURE::GET_LINE_GPOINT<NDEG1D, i>(lx, ux).weight
#define   ABSC1D(i, lx, ux) QUADRATURE::GET_LINE_GPOINT<NDEG1D, i>(lx, ux).node

namespace integration {
    //GRAMM MATRIX
    /*template <size_t v>
        constexpr auto gramm_mat() {
            auto result = VolumeIntegrate([&](Point p){return LEG(v, p)*LEG(v, p);});
            return 1.0/result;
        }*/

    

    template <size_t NDEG1D, typename F>
        constexpr auto VolumeIntegrate(F&& f,   const double lower_bound_x = -1., const double upper_bound_x = 1.,
                                                const double lower_bound_y = -1., const double upper_bound_y = 1.,
                                                const double lower_bound_z = -1., const double upper_bound_z = 1. ) {
            using result_type = typename std::result_of<F(Point)>::type;
            result_type vol(0);
            constexpr_for<0, NDEG1D*NDEG1D*NDEG1D, 1> ( [&](auto i) { 
                    vol += WEIGHT3D(i, lower_bound_x, upper_bound_x, lower_bound_y, upper_bound_y, lower_bound_z, upper_bound_z)*
                    f(ABSC3D(i, lower_bound_x, upper_bound_x, lower_bound_y, upper_bound_y, lower_bound_z, upper_bound_z)); });
            return vol;
        }
    template <size_t NDEG1D, typename F>
        constexpr auto SurfaceIntegrate(F&& f,  const double lower_bound_x = -1., const double upper_bound_x = 1.,
                                                const double lower_bound_y = -1., const double upper_bound_y = 1.) {
            using result_type = typename std::result_of<F(Point2d)>::type;
            result_type surf(0);
            constexpr_for<0, NDEG1D*NDEG1D, 1>([&](auto i) { 
                    surf += WEIGHT2D(i, lower_bound_x, upper_bound_x, lower_bound_y, upper_bound_y)*
                            f(ABSC2D(i, lower_bound_x, upper_bound_x, lower_bound_y, upper_bound_y)); });
            return surf;
        }
    template <size_t NDEG1D, typename F>
        constexpr auto LineIntegrate(F&& f, const double lower_bound_x = -1., const double upper_bound_x = 1.) {
            using result_type = typename std::result_of<F(double)>::type;
            result_type lin(0);
            constexpr_for<0, NDEG1D, 1>([&](auto i) { 
                    lin += WEIGHT1D(i, lower_bound_x, upper_bound_x)*f(ABSC1D(i, lower_bound_x, upper_bound_x)); });
            return lin;
        }
};

#endif //INTEGRATION_H
