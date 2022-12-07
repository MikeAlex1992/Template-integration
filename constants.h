#ifndef CONSTANTS_H
#define CONSTANTS_H
//#include <cstddef>
#include "MathArray.h"

namespace GLOBAL {
    constexpr size_t NDEG1D = 3;
    constexpr size_t NDEG2D = NDEG1D*NDEG1D;
    constexpr size_t NDEG3D = NDEG1D*NDEG1D*NDEG1D;

    constexpr size_t NDEG_PATH = 3;

    constexpr size_t NDOFS1D = 2;
    constexpr size_t NDOFS2D = NDOFS1D*(NDOFS1D + 1)/2;
    constexpr size_t NDOFS3D = NDOFS1D*(NDOFS1D+1)*(NDOFS1D+2)/6;

    constexpr size_t NVARS = 12;
    constexpr size_t FULL_NDOFS = NVARS*NDOFS3D;
};

using VarVector = MathArray<double, GLOBAL::NVARS>;

#endif //CONSTANTS_H
