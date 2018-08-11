//
// Created by vbrau on 8/11/2018.
//

#include "MaterialStorage.h"

std::valarray<int> MaterialStorage::getCost() {
    return {0,0,-2,0,0};
}

std::valarray<int> MaterialStorage::getStorage() {
    return {0,30,30,0,0};
}

MaterialStorage::MaterialStorage(int x, int y) : Storage(x, y) {
    std::vector<Vector2d<int>> locs;

    Vector2d<int> loc;
    loc.x = 0; loc.y = 0;
    requiredLocs[loc] = true;
    locs.push_back(loc);

    setLocs(locs);

}
