//
// Created by vbrau on 8/11/2018.
//

#include "FuelRefinery.h"

void FuelRefinery::resourceGeneration(Resources *resources) {
    int remaining = resources->getFuelStorage() - resources->getFuel();
    int output = std::min(std::min(2, resources->getRawMaterial()), remaining);
    resources->addResources({0, -output, 0, output, 0});
}

std::valarray<int> FuelRefinery::getCost() {
    return {-3, 0, 6, 0, 0};
}

FuelRefinery::FuelRefinery(int x, int y) : Building(x, y) {
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
