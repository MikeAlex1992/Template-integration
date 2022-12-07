#ifndef POINT_H
#define POINT_H

#include <type_traits>

struct Point {
    double x;
    double y;
    double z;
};

struct Point2d {
    double x;
    double y;
};

template <typename T>
struct GP_Point {
    T node;
    double weight;
};

template <auto Start, auto End, auto Inc, class F>
constexpr void constexpr_for(F&& f)
{
    if constexpr (Start < End)
    {
        f(std::integral_constant<decltype(Start), Start>());
        constexpr_for<Start + Inc, End, Inc>(f);
    }
}

#endif //POINT_H
