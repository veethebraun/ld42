//
// Created by vbrau on 8/11/2018.
//

#include "MineBuilding.h"

void MineBuilding::resourceGeneration(Resources *resources) {
    if (!destroyed && resources->getPower() > 0) {
        resources->addResources({0, MINE_RATE, 0, 0, 0});
    }
}

std::valarray<int> MineBuilding::getCost() {
    return {-MINE_POWER,0,-MINE_STEEL_COST,0,0};
}

MineBuilding::MineBuilding(int x, int y) : Building(x, y) {
    locs.emplace_back(Point2d({0,1}));
    requiredLocs.emplace_back(Point2d({0,1}));
    locs.emplace_back(Point2d({1,1}));
    requiredLocs.emplace_back(Point2d({1,1}));
    locs.emplace_back(Point2d({1,0}));
    requiredLocs.emplace_back(Point2d({1,0}));
    locs.emplace_back(Point2d({2,1}));
    locs.emplace_back(Point2d({3,1}));
}

void MineBuilding::onDestroy(Resources *resources) {
    resources->addResources({MINE_POWER, 0, 0, 0, 0});
}

