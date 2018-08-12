//
// Created by vbrau on 8/11/2018.
//

#include "FuelRefinery.h"

void FuelRefinery::resourceGeneration(Resources *resources) {
    if (!destroyed) {
        int remaining = resources->getFuelStorage() - resources->getFuel();
        int output = std::min(std::min(FUEL_REFINERY_RATE, resources->getRawMaterial()), remaining);
        resources->addResources({0, -output, 0, output, 0});
    }
}

std::valarray<int> FuelRefinery::getCost() {
    return {-FUEL_REFINERY_POWER, 0, -FUEL_REFINERY_STEEL_COST, 0, 0};
}

FuelRefinery::FuelRefinery(int x, int y) : Building(x, y) {
    locs.emplace_back(Point2d({0,0}));
    requiredLocs.emplace_back(Point2d({0,0}));
    locs.emplace_back(Point2d({0,1}));
    requiredLocs.emplace_back(Point2d({0,1}));
}

void FuelRefinery::onDestroy(Resources *resources) {
}
