#ifndef VARIABLE_VECTOR_H
#define VARIABLE_VECTOR_H

#include <cassert>
//#include "MathArray.h"
#include "constants.h"
#include "sides.h"
#include "legendre.h"
#include <array>

using NDOFS_VECTOR = std::array<double, GLOBAL::NDOFS3D>;
class SINGLE_VARIABLE {

    private:
        NDOFS_VECTOR ndofs;

    public:
        //SINGLE_VARIABLE(NDOFS_VECTOR&& _ndofs) : ndofs(std::move(_ndofs)) {}
        constexpr SINGLE_VARIABLE(const NDOFS_VECTOR& _ndofs) : ndofs(_ndofs) {} //only copy and default constructors!
        SINGLE_VARIABLE() { ndofs.fill(0.0); }

        constexpr double _at(Point p) const {
            double sum = 0.;
            constexpr_for<0, GLOBAL::NDOFS3D, 1>([&](auto k) {
                    sum += ndofs[k]*LEGENDRE::LEG_POLY_3D<k>(p);
                    });
            return sum;
        }

        template<geom::Direction der>
            constexpr double _derivative(Point p) const {
                double sum = 0.;
                constexpr_for<0, GLOBAL::NDOFS3D, 1>([&](auto k) {
                        sum += ndofs[k]*LEGENDRE::LEG_POLY_3D_DER<der, k>(p);
                        });
                return sum;
            }

        template<geom::Direction der>
            constexpr double _derivative2(Point p) const {
                double sum = 0.;
                constexpr_for<0, GLOBAL::NDOFS3D, 1>([&](auto k) {
                        sum += ndofs[k]*LEGENDRE::LEG_POLY_3D_DER2<der, k>(p);
                        });
                return sum;
            }

        template<geom::Direction der>
            constexpr double _derivative3(Point p) const {
                double sum = 0.;
                constexpr_for<0, GLOBAL::NDOFS3D, 1>([&](auto k) {
                        sum += ndofs[k]*LEGENDRE::LEG_POLY_3D_DER3<der, k>(p);
                        });
                return sum;
            }

        template<geom::Side side, size_t NDEG1D = GLOBAL::NDEG1D>
            constexpr double _boundside() const {
                double sum = 0.;
                /*constexpr_for<0, GLOBAL::NDEG2D, 1>([&](auto i) {
                  sum += QUADRATURE::GET_SURF_GPOINT<side, NDEG1D, i>().weight * _at(QUADRATURE::GET_SURF_GPOINT<side, NDEG1D, i>().node);
                  });*/
                return 0.25*sum;
            }

        constexpr const double& _ave() const {
            return ndofs[0];
        }

        constexpr const auto& _dofs() const {
            return ndofs;
        }
};

class VARIABLE_VECTOR {
    private:
        std::array<SINGLE_VARIABLE, GLOBAL::NVARS> vars;
        std::array<double, GLOBAL::FULL_NDOFS> vardofs;

    public:
        VARIABLE_VECTOR() : vars(std::array<SINGLE_VARIABLE, GLOBAL::NVARS>{}) {}

        void store(const std::array<double, GLOBAL::FULL_NDOFS>& result) {
            size_t start = 0;
            NDOFS_VECTOR var_ndofs;
            for (auto& var : vars) {
                for (size_t i = 0; i < var_ndofs.size(); ++i) {
                    var_ndofs[i] = result[start + i];
                }
                var = SINGLE_VARIABLE(var_ndofs);
                start += var_ndofs.size();
            }
            assert(start == result.size());
            vardofs = result;
        }

        constexpr VarVector _at(Point p) const
        {
            VarVector result;
            for (size_t k = 0; k < GLOBAL::NVARS; ++k) {
                result[k] = vars[k]._at(p);
            }
            return result;
        }
};

class NEIGHBORS {
    private:
        VARIABLE_VECTOR vars_x_minus, vars_y_minus, vars_z_minus,
                        vars_x_plus,  vars_y_plus,  vars_z_plus;

    public:
        template <geom::Side side>
            void store(const VARIABLE_VECTOR& input) {
                if constexpr (side == geom::Side::SIDE_X_MINUS) {vars_x_minus = input;}
                if constexpr (side == geom::Side::SIDE_Y_MINUS) {vars_y_minus = input;}
                if constexpr (side == geom::Side::SIDE_Z_MINUS) {vars_z_minus = input;}
                if constexpr (side == geom::Side::SIDE_X_PLUS) {vars_x_plus = input;}
                if constexpr (side == geom::Side::SIDE_Y_PLUS) {vars_y_plus = input;}
                if constexpr (side == geom::Side::SIDE_Z_PLUS) {vars_z_plus = input;}
            }

        template <geom::Side side>
            constexpr const VARIABLE_VECTOR& get() const {
                if constexpr (side == geom::Side::SIDE_X_MINUS) {return vars_x_minus;}
                if constexpr (side == geom::Side::SIDE_Y_MINUS) {return vars_y_minus;}
                if constexpr (side == geom::Side::SIDE_Z_MINUS) {return vars_z_minus;}
                if constexpr (side == geom::Side::SIDE_X_PLUS) {return vars_x_plus;}
                if constexpr (side == geom::Side::SIDE_Y_PLUS) {return vars_y_plus;}
                if constexpr (side == geom::Side::SIDE_Z_PLUS) {return vars_z_plus;}
            }
};

#endif //VARIABLE_VECTOR_H
