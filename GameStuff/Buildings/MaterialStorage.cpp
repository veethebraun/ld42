//
// Created by vbrau on 8/11/2018.
//

#include "MaterialStorage.h"

std::valarray<int> MaterialStorage::getCost() {
    return {0,0,-MIN_STORE_STEEL_COST,0,0};
}

std::valarray<int> MaterialStorage::getStorage() {
    return {0,MIN_STORE_AMOUNT,MIN_STORE_AMOUNT,0,0};
}

MaterialStorage::MaterialStorage(int x, int y) : Storage(x, y) {
    locs.emplace_back(Point2d({0,0}));
    requiredLocs.emplace_back(Point2d({0,0}));
}
