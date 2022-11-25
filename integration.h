#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "quad.h"
#include <type_traits>

namespace integration
{
    template <auto Start, auto End, auto Inc, class F>
        constexpr void constexpr_for(F&& f)
        {
            if constexpr (Start < End)
            {
                f(std::integral_constant<decltype(Start), Start>());
                constexpr_for<Start + Inc, End, Inc>(f);
            }
        }

    template <typename F>
        constexpr double volumeIntegrate(F&& f) {
            auto vol = 0.0;
            constexpr_for<0, GLOBAL::NDEG3D, 1>([=, &vol](auto i) {
                    vol += weight(i)*f(node(i));
            });
            return vol;
        }
};

#endif //INTEGRATION_H
