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
    locs.emplace_back(Point2d({0,0}));
    requiredLocs.emplace_back(Point2d({0,0}));
    locs.emplace_back(Point2d({0,1}));
    requiredLocs.emplace_back(Point2d({0,1}));
}

void FuelRefinery::onDestroy(Resources *resources) {
    destroyed = true;
}
