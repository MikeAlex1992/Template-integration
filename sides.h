#ifndef SIDES_H
#define SIDES_H

#include "point.h" 

namespace geom {
    enum class Side {
        SIDE_X_PLUS,
        SIDE_X_MINUS,
        SIDE_Y_PLUS,
        SIDE_Y_MINUS,
        SIDE_Z_PLUS,
        SIDE_Z_MINUS,
    };

    enum class Direction {
        X,
        Y,
        Z
    };

    template <Direction dir>
        constexpr auto GetPositiveDirectionSide() {
            if constexpr(dir == Direction::X) {return Side::SIDE_X_PLUS;}
            if constexpr(dir == Direction::Y) {return Side::SIDE_Y_PLUS;}
            if constexpr(dir == Direction::Z) {return Side::SIDE_Z_PLUS;}
        }

    template <Direction dir>
        constexpr auto GetNegativeDirectionSide() {
            if constexpr(dir == Direction::X) {return Side::SIDE_X_MINUS;}
            if constexpr(dir == Direction::Y) {return Side::SIDE_Y_MINUS;}
            if constexpr(dir == Direction::Z) {return Side::SIDE_Z_MINUS;}
        }

    template <size_t i> 
        constexpr auto GetSide() {   
            if constexpr(i == 0) {return Side::SIDE_X_MINUS;}
            if constexpr(i == 1) {return Side::SIDE_X_PLUS;}
            if constexpr(i == 2) {return Side::SIDE_Y_MINUS;}
            if constexpr(i == 3) {return Side::SIDE_Y_PLUS;}
            if constexpr(i == 4) {return Side::SIDE_Z_MINUS;}
            if constexpr(i == 5) {return Side::SIDE_Z_PLUS;}
        }

    template <size_t i> 
        constexpr auto GetPositiveSide() {   
            if constexpr(i == 0) {return Side::SIDE_X_PLUS;}
            if constexpr(i == 1) {return Side::SIDE_Y_PLUS;}
            if constexpr(i == 2) {return Side::SIDE_Z_PLUS;}
        }

    template <Side side>
        constexpr auto GetReverseSide() {
            if constexpr(side == Side::SIDE_X_PLUS) {return Side::SIDE_X_MINUS;}
            if constexpr(side == Side::SIDE_X_MINUS) {return Side::SIDE_X_PLUS;}
            if constexpr(side == Side::SIDE_Y_PLUS) {return Side::SIDE_Y_MINUS;}
            if constexpr(side == Side::SIDE_Y_MINUS) {return Side::SIDE_Y_PLUS;}
            if constexpr(side == Side::SIDE_Z_PLUS) {return Side::SIDE_Z_MINUS;}
            if constexpr(side == Side::SIDE_Z_MINUS) {return Side::SIDE_Z_PLUS;}
        }

    template <Side side>
        constexpr auto GetOuterNorm() {
            if constexpr(side == Side::SIDE_X_PLUS ) {return std::array{ 1, 0, 0};}
            if constexpr(side == Side::SIDE_X_MINUS) {return std::array{-1, 0, 0};}
            if constexpr(side == Side::SIDE_Y_PLUS ) {return std::array{ 0, 1, 0};}
            if constexpr(side == Side::SIDE_Y_MINUS) {return std::array{ 0,-1, 0};}
            if constexpr(side == Side::SIDE_Z_PLUS ) {return std::array{ 0, 0, 1};}
            if constexpr(side == Side::SIDE_Z_MINUS) {return std::array{ 0, 0,-1};}
        }

    template <Side side>
        constexpr auto GetDirectionNorm() {
            if constexpr(   side == Side::SIDE_X_PLUS  ||
                            side == Side::SIDE_Y_PLUS  ||
                            side == Side::SIDE_Z_PLUS  ) {return 1;}
            if constexpr(   side == Side::SIDE_X_MINUS ||
                            side == Side::SIDE_Y_MINUS ||
                            side == Side::SIDE_Z_MINUS ) {return -1;}
        }

    template <Side side>
        constexpr auto GetDirectionBySide() {
            if constexpr(side == Side::SIDE_X_PLUS ) {return  Direction::X;}
            if constexpr(side == Side::SIDE_X_MINUS) {return  Direction::X;}
            if constexpr(side == Side::SIDE_Y_PLUS ) {return  Direction::Y;}
            if constexpr(side == Side::SIDE_Y_MINUS) {return  Direction::Y;}
            if constexpr(side == Side::SIDE_Z_PLUS ) {return  Direction::Z;}
            if constexpr(side == Side::SIDE_Z_MINUS) {return  Direction::Z;}
        }

    template <Side side>
        Point Convert2dTo3dPoint(Point2d p) {
            if constexpr(side == Side::SIDE_X_PLUS ) {return  Point{ 1.0,  p.x,  p.y};}
            if constexpr(side == Side::SIDE_X_MINUS) {return  Point{-1.0,  p.x,  p.y};}
            if constexpr(side == Side::SIDE_Y_PLUS ) {return  Point{ p.x,  1.0,  p.y};}
            if constexpr(side == Side::SIDE_Y_MINUS) {return  Point{ p.x, -1.0,  p.y};}
            if constexpr(side == Side::SIDE_Z_PLUS ) {return  Point{ p.x,  p.y,  1.0};}
            if constexpr(side == Side::SIDE_Z_MINUS) {return  Point{ p.x,  p.y, -1.0};}
        }

};

#endif //SIDES_H
