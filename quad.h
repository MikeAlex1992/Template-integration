#ifndef LEGENDRE_H
#define LEGENDRE_H

#include <cmath>
#include <cstddef>

namespace GLOBAL
{
    constexpr size_t NDEG1D = 2;
    constexpr size_t NDEG2D = NDEG1D*NDEG1D;
    constexpr size_t NDEG3D = NDEG1D*NDEG1D*NDEG1D;
};

struct Point
{
    double x;
    double y;
    double z;
};

template <typename T>
struct GP_Point
{
    T node;
    double weight;
};

namespace QUADRATURE
{
    typedef GP_Point<double> GDOUBLE;
    typedef GP_Point<Point> GPOINT;

    constexpr auto remap(GDOUBLE r, const double a, const double b)
    {
        r.node = 0.5*(b-a)*r.node + 0.5*(b+a);
        r.weight = 0.5*(b-a)*r.weight;
        return r;
    }

    template <size_t NDEG1D, size_t i>
        constexpr auto GET_1D_GDOUBLE()
        {
            if constexpr(NDEG1D == 1)
            {
                return GDOUBLE{0.0, 1.0};
            }

            if constexpr(NDEG1D == 2)
            {
                if constexpr (i == 0) {return GDOUBLE{-0.5773502691896257645091488, 1.};}
                if constexpr (i == 1) {return GDOUBLE{ 0.5773502691896257645091488, 1.};}
            }
            else if constexpr(NDEG1D == 3)
            {
                if constexpr (i == 0) {return GDOUBLE{-0.7745966692414833770359, 0.5555555555555555555556};}
                if constexpr (i == 1) {return GDOUBLE{ 0.,                       0.8888888888888888888889};}
                if constexpr (i == 2) {return GDOUBLE{ 0.7745966692414833770359, 0.5555555555555555555556};}
            }
            else if constexpr(NDEG1D == 4)
            {
                if constexpr (i == 0) {return GDOUBLE{-0.861136311594052575224,  0.3478548451374538573731};}
                if constexpr (i == 1) {return GDOUBLE{-0.3399810435848562648027, 0.6521451548625461426269};}
                if constexpr (i == 2) {return GDOUBLE{ 0.3399810435848562648027, 0.6521451548625461426269};}
                if constexpr (i == 3) {return GDOUBLE{ 0.861136311594052575224,  0.3478548451374538573731};}
            }
            else if constexpr(NDEG1D == 5)
            {
                if constexpr (i == 0) {return GDOUBLE{-0.9061798459386639927976, 0.2369268850561890875143};}
                if constexpr (i == 1) {return GDOUBLE{-0.5384693101056830910363, 0.4786286704993664680413};}
                if constexpr (i == 2) {return GDOUBLE{ 0.,                       0.5688888888888888888889};}
                if constexpr (i == 3) {return GDOUBLE{ 0.5384693101056830910363, 0.4786286704993664680413};}
                if constexpr (i == 4) {return GDOUBLE{ 0.9061798459386639927976, 0.2369268850561890875143};}
            }
            else if constexpr(NDEG1D == 6)
            {
                if constexpr (i == 0) {return GDOUBLE{-0.9324695142031520278123, 0.1713244923791703450403};}
                if constexpr (i == 1) {return GDOUBLE{-0.661209386466264513661 , 0.3607615730481386075698};}
                if constexpr (i == 2) {return GDOUBLE{-0.2386191860831969086305, 0.4679139345726910473899};}
                if constexpr (i == 3) {return GDOUBLE{ 0.2386191860831969086305, 0.4679139345726910473899};}
                if constexpr (i == 4) {return GDOUBLE{ 0.661209386466264513661 , 0.3607615730481386075698};}
                if constexpr (i == 5) {return GDOUBLE{ 0.9324695142031520278123, 0.1713244923791703450403};}
            }
            else if constexpr(NDEG1D == 7)
            {
                if constexpr (i == 0) {return GDOUBLE{-0.9491079123427585245262, 0.1294849661688696932706};}
                if constexpr (i == 1) {return GDOUBLE{-0.7415311855993944398639, 0.2797053914892766679015};}
                if constexpr (i == 2) {return GDOUBLE{-0.4058451513773971669066, 0.38183005050511894495  };}
                if constexpr (i == 3) {return GDOUBLE{ 0.                      , 0.417959183673469387755 };}
                if constexpr (i == 4) {return GDOUBLE{ 0.4058451513773971669066, 0.38183005050511894495  };}
                if constexpr (i == 5) {return GDOUBLE{ 0.7415311855993944398639, 0.2797053914892766679015};}
                if constexpr (i == 6) {return GDOUBLE{ 0.9491079123427585245262, 0.1294849661688696932706};}
            }
            else if constexpr(NDEG1D == 8)
            {
                if constexpr (i == 0) {return GDOUBLE{-0.9602898564975362316836, 0.1012285362903762591525};}
                if constexpr (i == 1) {return GDOUBLE{-0.7966664774136267395916, 0.222381034453374470544 };}
                if constexpr (i == 2) {return GDOUBLE{-0.5255324099163289858177, 0.313706645877887287338 };}
                if constexpr (i == 3) {return GDOUBLE{-0.1834346424956498049395, 0.3626837833783619829652};}
                if constexpr (i == 4) {return GDOUBLE{ 0.1834346424956498049395, 0.3626837833783619829652};}
                if constexpr (i == 5) {return GDOUBLE{ 0.5255324099163289858177, 0.313706645877887287338 };}
                if constexpr (i == 6) {return GDOUBLE{ 0.7966664774136267395916, 0.222381034453374470544 };}
                if constexpr (i == 7) {return GDOUBLE{ 0.9602898564975362316836, 0.1012285362903762591525};}
            }
            else if constexpr(NDEG1D == 9)
            {
                if constexpr (i == 0) {return GDOUBLE{-0.9681602395076260898356, 0.0812743883615744119719};}
                if constexpr (i == 1) {return GDOUBLE{-0.8360311073266357942994, 0.1806481606948574040585};}
                if constexpr (i == 2) {return GDOUBLE{-0.6133714327005903973087, 0.2606106964029354623187};}
                if constexpr (i == 3) {return GDOUBLE{-0.3242534234038089290385, 0.312347077040002840069 };}
                if constexpr (i == 4) {return GDOUBLE{ 0.                      , 0.330239355001259763165 };}
                if constexpr (i == 5) {return GDOUBLE{ 0.3242534234038089290385, 0.312347077040002840069 };}
                if constexpr (i == 6) {return GDOUBLE{ 0.6133714327005903973087, 0.2606106964029354623187};}
                if constexpr (i == 7) {return GDOUBLE{ 0.8360311073266357942994, 0.1806481606948574040585};}
                if constexpr (i == 8) {return GDOUBLE{ 0.9681602395076260898356, 0.0812743883615744119719};}
            }
            else if constexpr(NDEG1D == 10)
            {
                if constexpr (i == 0) {return GDOUBLE{-0.973906528517171720078, 0.0666713443086881375936};}
                if constexpr (i == 1) {return GDOUBLE{-0.8650633666889845107321,0.149451349150580593146 };}
                if constexpr (i == 2) {return GDOUBLE{-0.6794095682990244062343,0.219086362515982043996 };}
                if constexpr (i == 3) {return GDOUBLE{-0.4333953941292471907993,0.2692667193099963550912};}
                if constexpr (i == 4) {return GDOUBLE{-0.1488743389816312108848,0.2955242247147528701739};}
                if constexpr (i == 5) {return GDOUBLE{ 0.1488743389816312108848,0.2955242247147528701739};}
                if constexpr (i == 6) {return GDOUBLE{ 0.4333953941292471907993,0.2692667193099963550912};}
                if constexpr (i == 7) {return GDOUBLE{ 0.6794095682990244062343,0.219086362515982043996 };}
                if constexpr (i == 8) {return GDOUBLE{ 0.8650633666889845107321,0.149451349150580593146 };}
                if constexpr (i == 9) {return GDOUBLE{ 0.973906528517171720078, 0.0666713443086881375936};}
            }
            static_assert((NDEG1D < 11), "NO SUCH DEGREE!");
        }

    template<size_t p>
        constexpr auto GET_VOL_GPOINT()
        {
            constexpr size_t k = static_cast<size_t>(p/(GLOBAL::NDEG1D*GLOBAL::NDEG1D));
            constexpr size_t j = static_cast<size_t>(p/GLOBAL::NDEG1D - k*GLOBAL::NDEG1D);
            constexpr size_t i = static_cast<size_t>(p - j*GLOBAL::NDEG1D - k*GLOBAL::NDEG1D*GLOBAL::NDEG1D);

            constexpr auto Di = GET_1D_GDOUBLE<GLOBAL::NDEG1D, i>();
            constexpr auto Dj = GET_1D_GDOUBLE<GLOBAL::NDEG1D, j>();
            constexpr auto Dk = GET_1D_GDOUBLE<GLOBAL::NDEG1D, k>();
            return GPOINT{{ Di.node, Dj.node, Dk.node}, Di.weight*Dj.weight*Dk.weight};
        }
};

#define weight(i) QUADRATURE::GET_VOL_GPOINT<i>().weight
#define node(i) QUADRATURE::GET_VOL_GPOINT<i>().node

#endif //LEGENDRE_H
