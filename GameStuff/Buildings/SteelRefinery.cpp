//
// Created by vbrau on 8/11/2018.
//

#include "SteelRefinery.h"

void SteelRefinery::resourceGeneration(Resources *resources) {
    int remaining = resources->getSteelStorage() - resources->getSteel();
    int output = std::min(std::min(3, resources->getRawMaterial()), remaining);
    resources->addResources({0, -output, output, 0, 0});

}

std::valarray<int> SteelRefinery::getCost() {
    return {-3,0,-5,0,0};
}

SteelRefinery::SteelRefinery(int x, int y) : Building(x, y) {
    std::vector<Vector2d<int>> locs;

    Vector2d<int> loc;
    loc.x = 0; loc.y = 0;
    requiredLocs[loc] = true;
    locs.push_back(loc);
    loc.x = 0; loc.y = 1;
    requiredLocs[loc] = true;
    locs.push_back(loc);

    setLocs(locs);

}
