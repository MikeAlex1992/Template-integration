#ifndef LEGENDRE_H
#define LEGENDRE_H

#include <cstddef>
#include <array>
#include "sides.h"
#include "point.h"

namespace LEGENDRE {
    using namespace geom;

    template<size_t DOF_NUM>
        constexpr double LEG_POLY(const double& x) {
            if constexpr (DOF_NUM == 0)      {return 1.0;}
            else if constexpr (DOF_NUM == 1) {return x;  }
            else if constexpr (DOF_NUM == 2) {return 0.5*(3.*x*x - 1.);}
            else if constexpr (DOF_NUM == 3) {return 0.5*(5.*x*x*x - 3.*x);}
            else if constexpr (DOF_NUM == 4) {return 0.125*(35.*x*x*x*x - 30.*x*x + 3.);}
        }

    template<size_t DOF_NUM>
        constexpr double LEG_POLY_DER(const double& x) {
            if constexpr (DOF_NUM == 0)      {return 0.0;}
            else if constexpr (DOF_NUM == 1) {return 1.0;}
            else if constexpr (DOF_NUM == 2) {return 3.0*x;}
            else if constexpr (DOF_NUM == 3) {return 1.5*(5*x*x - 1);}
            else if constexpr (DOF_NUM == 4) {return 2.5*(7*x*x*x - 3*x);}
        }

    template<size_t DOF_NUM>
        constexpr double LEG_POLY_DER2(const double& x) {
            if constexpr (DOF_NUM == 0)      {return 0.0;}
            else if constexpr (DOF_NUM == 1) {return 0.0;}
            else if constexpr (DOF_NUM == 2) {return 3.0;}
            else if constexpr (DOF_NUM == 3) {return 15.*x;}
            else if constexpr (DOF_NUM == 4) {return 7.5*(7.0*x*x - 1.0);}
        }

    template<size_t DOF_NUM>
        constexpr double LEG_POLY_DER3(const double& x) {
            if constexpr (DOF_NUM == 0)      {return 0.0;}
            else if constexpr (DOF_NUM == 1) {return 0.0;}
            else if constexpr (DOF_NUM == 2) {return 0.0;}
            else if constexpr (DOF_NUM == 3) {return 15.;}
            else if constexpr (DOF_NUM == 4) {return 105.0*x;}
        }


    template<size_t DOF_NUM>
        constexpr double LEG_POLY_DER4(const double& x) {
            if constexpr (DOF_NUM == 0)      {return 0.0;}
            else if constexpr (DOF_NUM == 1) {return 0.0;}
            else if constexpr (DOF_NUM == 2) {return 0.0;}
            else if constexpr (DOF_NUM == 3) {return 0.0;}
            else if constexpr (DOF_NUM == 4) {return 105.0;}
        }

    template<size_t v>
        constexpr auto dof_index() {
            if constexpr (v == 0)  {return std::array{0, 0, 0};}
            if constexpr (v == 1)  {return std::array{1, 0, 0};}
            if constexpr (v == 2)  {return std::array{0, 1, 0};}
            if constexpr (v == 3)  {return std::array{0, 0, 1};}
            if constexpr (v == 4)  {return std::array{1, 1, 0};}
            if constexpr (v == 5)  {return std::array{1, 0, 1};}
            if constexpr (v == 6)  {return std::array{0, 1, 1};}
            if constexpr (v == 7)  {return std::array{2, 0, 0};}
            if constexpr (v == 8)  {return std::array{0, 2, 0};}
            if constexpr (v == 9)  {return std::array{0, 0, 2};}
            if constexpr (v == 10) {return std::array{1, 1, 1};}
            if constexpr (v == 11) {return std::array{2, 1, 0};}
            if constexpr (v == 12) {return std::array{1, 2, 0};}
            if constexpr (v == 13) {return std::array{2, 0, 1};}
            if constexpr (v == 14) {return std::array{1, 0, 2};}
            if constexpr (v == 15) {return std::array{0, 1, 2};}
            if constexpr (v == 16) {return std::array{0, 2, 1};}
            if constexpr (v == 17) {return std::array{3, 0, 0};}
            if constexpr (v == 18) {return std::array{0, 3, 0};}
            if constexpr (v == 19) {return std::array{0, 0, 3};}
        }

    template<size_t v>
        constexpr auto LEG_POLY_3D(const Point& p) {
            constexpr auto vv = dof_index<v>();
            return LEG_POLY<vv[0]>(p.x)*LEG_POLY<vv[1]>(p.y)*LEG_POLY<vv[2]>(p.z);
        }

    template<size_t i, size_t j, size_t k>
        constexpr auto LEG_POLY_3D_DER_X(const Point& p) {
            return LEG_POLY_DER<i>(p.x)*LEG_POLY<j>(p.y)*LEG_POLY<k>(p.z);
        }

    template<size_t i, size_t j, size_t k>
        constexpr auto LEG_POLY_3D_DER_Y(const Point& p) {
            return LEG_POLY<i>(p.x)*LEG_POLY_DER<j>(p.y)*LEG_POLY<k>(p.z);
        }

    template<size_t i, size_t j, size_t k>
        constexpr auto LEG_POLY_3D_DER_Z(const Point& p) {
            return LEG_POLY<i>(p.x)*LEG_POLY<j>(p.y)*LEG_POLY_DER<k>(p.z);
        }

    template<size_t i, size_t j, size_t k>
        constexpr auto LEG_POLY_3D_2DER_X(const Point& p) {
            return LEG_POLY_DER2<i>(p.x)*LEG_POLY<j>(p.y)*LEG_POLY<k>(p.z);
        }

    template<size_t i, size_t j, size_t k>
        constexpr auto LEG_POLY_3D_2DER_Y(const Point& p) {
            return LEG_POLY<i>(p.x)*LEG_POLY_DER2<j>(p.y)*LEG_POLY<k>(p.z);
        }

    template<size_t i, size_t j, size_t k>
        constexpr auto LEG_POLY_3D_2DER_Z(const Point& p) {
            return LEG_POLY<i>(p.x)*LEG_POLY<j>(p.y)*LEG_POLY_DER2<k>(p.z);
        }

    template<size_t i, size_t j, size_t k>
        constexpr auto LEG_POLY_3D_3DER_X(const Point& p) {
            return LEG_POLY_DER3<i>(p.x)*LEG_POLY<j>(p.y)*LEG_POLY<k>(p.z);
        }

    template<size_t i, size_t j, size_t k>
        constexpr auto LEG_POLY_3D_3DER_Y(const Point& p) {
            return LEG_POLY<i>(p.x)*LEG_POLY_DER3<j>(p.y)*LEG_POLY<k>(p.z);
        }

    template<size_t i, size_t j, size_t k>
        constexpr auto LEG_POLY_3D_3DER_Z(const Point& p) {
            return LEG_POLY<i>(p.x)*LEG_POLY<j>(p.y)*LEG_POLY_DER3<k>(p.z);
        }

    template<Direction der, size_t v>
        constexpr auto LEG_POLY_3D_DER(const Point& p) {
            constexpr auto vv = dof_index<v>();

            if constexpr(der == Direction::X) {return LEG_POLY_3D_DER_X<vv[0], vv[1], vv[2]>(p);}
            if constexpr(der == Direction::Y) {return LEG_POLY_3D_DER_Y<vv[0], vv[1], vv[2]>(p);}
            if constexpr(der == Direction::Z) {return LEG_POLY_3D_DER_Z<vv[0], vv[1], vv[2]>(p);}
            static_assert((der == Direction::X || der == Direction::Y || der == Direction::Z), "WRONG DERIVATIVE DIRECTION NAME!");
        }


    template<Direction der, size_t v>
        constexpr auto LEG_POLY_3D_DER2(const Point& p) {
            constexpr auto vv = dof_index<v>();

            if constexpr(der == Direction::X) {return LEG_POLY_3D_2DER_X<vv[0], vv[1], vv[2]>(p);}
            if constexpr(der == Direction::Y) {return LEG_POLY_3D_2DER_Y<vv[0], vv[1], vv[2]>(p);}
            if constexpr(der == Direction::Z) {return LEG_POLY_3D_2DER_Z<vv[0], vv[1], vv[2]>(p);}
            static_assert((der == Direction::X || der == Direction::Y || der == Direction::Z), "WRONG DERIVATIVE DIRECTION NAME!");
        }

    template<Direction der, size_t v>
        constexpr auto LEG_POLY_3D_DER3(const Point& p) {
            constexpr auto vv = dof_index<v>();

            if constexpr(der == Direction::X) {return LEG_POLY_3D_3DER_X<vv[0], vv[1], vv[2]>(p);}
            if constexpr(der == Direction::Y) {return LEG_POLY_3D_3DER_Y<vv[0], vv[1], vv[2]>(p);}
            if constexpr(der == Direction::Z) {return LEG_POLY_3D_3DER_Z<vv[0], vv[1], vv[2]>(p);}
            static_assert((der == Direction::X || der == Direction::Y || der == Direction::Z), "WRONG DERIVATIVE DIRECTION NAME!");
        }
};


#endif //LEGENDRE_H
