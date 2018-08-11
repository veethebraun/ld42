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
    std::vector<Vector2d<int>> locs;

    Vector2d<int> loc;
    loc.x = 0; loc.y = 0;
    requiredLocs[loc] = true;
    locs.push_back(loc);
    loc.x = 1; loc.y = 0;
    requiredLocs[loc] = true;
    locs.push_back(loc);

    setLocs(locs);
}
