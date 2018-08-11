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
    locs.emplace_back(Point2d({0,0}));
    requiredLocs.emplace_back(Point2d({0,0}));
    locs.emplace_back(Point2d({0,1}));
    requiredLocs.emplace_back(Point2d({0,1}));
}

void SteelRefinery::onDestroy(Resources *resources) {
    destroyed = true;

}
