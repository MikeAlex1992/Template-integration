#ifndef FLUX_INTEGRATION_H
#define FLUX_INTEGRATION_H

#include "integration.h"
#include "constants.h"
#include "sides.h"

#define DLDX(i, p) LEGENDRE::LEG_POLY_3D_DER<geom::Direction::X, i>(p)
#define DLDY(i, p) LEGENDRE::LEG_POLY_3D_DER<geom::Direction::Y, i>(p)
#define DLDZ(i, p) LEGENDRE::LEG_POLY_3D_DER<geom::Direction::Z, i>(p)
#define LEG(i, p)  LEGENDRE::LEG_POLY_3D<i>(p)

#define VOL_INTEGR(func)    integration::VolumeIntegrate<GLOBAL::NDEG1D>([=](Point p){ func })
#define SURF_INTEGR(func)   integration::SurfaceIntegrate<GLOBAL::NDEG1D>([=](Point2d p2d){ \
                                Point p = geom::Convert2dTo3dPoint<side>(p2d); \
                                constexpr geom::Side revside = geom::GetReverseSide<side>();\
                                Point rp = geom::Convert2dTo3dPoint<revside>(p2d); \
                                func \
                            })

class BNFlux {
    private:
        int a = 0;

    public:
        VarVector Flux_X(VarVector u) const {
            return u;
        }

        VarVector Flux_Y(VarVector u) const {
            return u;
        }

        VarVector Flux_Z(VarVector u) const {
            return u;
        }

        template <geom::Side side>
            void PrepareSideParams() {
                a = 3;
            }

        VarVector SurfFlux(VarVector u_inner, VarVector u_outer) const {
            //return 0.5*(u_inner + u_outer);
            return u_inner;
        }
};

namespace flux_integration {

    class FluxIntegration {
        private:
            enum class FluxType {
                volume,
                surface,
                rhs,
                relax
            };

            BNFlux fl;
            VARIABLE_VECTOR u;
            NEIGHBORS un;

            template <FluxType flux>
            auto Integrate() {
                MathArray<double, GLOBAL::FULL_NDOFS> result;
                constexpr_for<0, GLOBAL::NDOFS3D, 1>([&](auto k) {
                    MathArray<double, GLOBAL::NVARS> one_dof_result;

                        if constexpr(flux == FluxType::volume)  { one_dof_result = VolFlux<k>();  }
                        if constexpr(flux == FluxType::surface) { one_dof_result = SurfFlux<k>(); }
                        if constexpr(flux == FluxType::rhs)     { one_dof_result = RHSFlux<k>(); }
                        if constexpr(flux == FluxType::relax)   { one_dof_result = RelFlux<k>(); }

                        for (int i = 0; i < one_dof_result.size(); ++i) { result[i*GLOBAL::NDOFS3D + k] = one_dof_result[i]; }
                        });
                return result;
            }

            template <size_t k>
                auto VolFlux() const {
                    return VOL_INTEGR( return   fl.Flux_X(u._at(p))*DLDX(k, p) +
                                                fl.Flux_Y(u._at(p))*DLDY(k, p) +
                                                fl.Flux_Z(u._at(p))*DLDZ(k, p); );
                }

            template <geom::Side side, size_t k>
                auto SurfSideFlux() {
                    return SURF_INTEGR(
                                        fl.PrepareSideParams<side>(); 
                                        return  fl.SurfFlux(u._at(p), u._at(rp))*LEG(k, p) ; );
                }

            template <size_t k>
                auto SurfFlux() {
                    MathArray<double, GLOBAL::NVARS> result;
                    constexpr_for<0, 6, 1>([this, &result](auto i)  {
                        constexpr auto side = geom::GetSide<i>();
                        result += SurfSideFlux<side, k>();
                    });
                    return result;
                }

            template <size_t k>
                auto RelFlux() const {
                    return VOL_INTEGR( return   fl.Flux_X(u._at(p))*DLDX(k, p) +
                                                fl.Flux_Y(u._at(p))*DLDY(k, p) +
                                                fl.Flux_Z(u._at(p))*DLDZ(k, p); );
                }

            template <size_t k>
                auto RHSFlux() const {
                    return VOL_INTEGR( return   fl.Flux_X(u._at(p))*DLDX(k, p) +
                                                fl.Flux_Y(u._at(p))*DLDY(k, p) +
                                                fl.Flux_Z(u._at(p))*DLDZ(k, p); );
                }

            auto Vol  () { return Integrate<FluxType::volume>(); }
            auto Surf () { return Integrate<FluxType::surface>(); }
            auto RHS  () { return Integrate<FluxType::rhs>(); }
            auto Relax() { return Integrate<FluxType::relax>(); }

            auto StoreDataU(const VARIABLE_VECTOR& u_) {u = u_;}
            auto StoreDataUN(const NEIGHBORS& un_) {un = un_;}
        public:
            auto Integrate(const VARIABLE_VECTOR& u_, const double coeff) { 
                StoreDataU(u_);
                return coeff*(Vol()-Surf()); 
            }
    };
};



#endif //FLUX_INTEGRATION
