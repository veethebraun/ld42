//
// Created by vbrau on 8/11/2018.
//

#include "MineBuilding.h"

void MineBuilding::resourceGeneration(Resources *resources) {
    resources->addResources({0,5,0,0,0});
}

std::valarray<int> MineBuilding::getCost() {
    return {-5,0,-10,0,0};
}

MineBuilding::MineBuilding(int x, int y) : Building(x, y) {

    std::vector<Vector2d<int>> locs;

    Vector2d<int> loc;
    loc.x = -1; loc.y = 1;
    requiredLocs[loc] = true;
    locs.push_back(loc);

    loc.x = 0; loc.y = 1;
    requiredLocs[loc] = true;
    locs.push_back(loc);
    loc.x = 0; loc.y = 0;
    requiredLocs[loc] = true;
    locs.push_back(loc);
    loc.x = 1; loc.y = 1;
    requiredLocs[loc] = false;
    locs.push_back(loc);
    loc.x = 2; loc.y = 1;
    requiredLocs[loc] = false;
    locs.push_back(loc);
    setLocs(locs);

}

