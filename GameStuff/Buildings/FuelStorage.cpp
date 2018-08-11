//
// Created by vbrau on 8/11/2018.
//

#include "FuelStorage.h"

std::valarray<int> FuelStorage::getCost() {
    return {-1, 0, -3, 0, 0};
}

std::valarray<int> FuelStorage::getStorage() {
    return {0,0,0,15,0};
}

FuelStorage::FuelStorage(int x, int y) : Storage(x, y) {
    locs.emplace_back(Point2d({0,0}));
    requiredLocs.emplace_back(Point2d({0,0}));
    locs.emplace_back(Point2d({1,0}));
    requiredLocs.emplace_back(Point2d({1,0}));
}
