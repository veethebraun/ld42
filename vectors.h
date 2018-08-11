//
// Created by vbrau on 8/10/2018.
//

#ifndef LD42_VECTORS_H
#define LD42_VECTORS_H

#include <tuple>
template<typename T>
struct Vector2d {
    T x = 0;
    T y = 0;

};

template<typename T>
bool operator <(const Vector2d<T>& lhs, const Vector2d<T>& rhs) {
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}

#endif //LD42_VECTORS_H
