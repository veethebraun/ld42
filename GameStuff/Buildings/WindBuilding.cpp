//
// Created by vbrau on 8/11/2018.
//

#include "WindBuilding.h"

std::valarray<int> WindBuilding::getCost() {
    return {10, 0, -4, 0, 0};
}

WindBuilding::WindBuilding(int x, int y) : Building(x, y) {
    std::vector<Vector2d<int>> locs;

    Vector2d<int> loc;
    loc.x = 0; loc.y = 0;
    requiredLocs[loc] = true;
    locs.push_back(loc);
    loc.x = 0; loc.y = 1;
    requiredLocs[loc] = true;
    locs.push_back(loc);
    loc.x = 1; loc.y = 0;
    requiredLocs[loc] = true;
    locs.push_back(loc);
    loc.x = 1; loc.y = 1;
    requiredLocs[loc] = true;
    locs.push_back(loc);
    loc.x = 0; loc.y = 2;
    requiredLocs[loc] = true;
    locs.push_back(loc);

    setLocs(locs);
}
