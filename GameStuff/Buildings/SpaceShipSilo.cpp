//
// Created by vbrau on 8/12/2018.
//

#include "SpaceShipSilo.h"

std::valarray<int> SpaceShipSilo::getCost() {
    return {0, 0, -ROCKET_STEEL_COST, -ROCKET_FUEL_COST, 0};
}

SpaceShipSilo::SpaceShipSilo(int x, int y) : Building(x, y) {
    locs.emplace_back(Point2d({0,0}));
    requiredLocs.emplace_back(Point2d({0,0}));
    locs.emplace_back(Point2d({1,0}));
    requiredLocs.emplace_back(Point2d({1,0}));
    locs.emplace_back(Point2d({2,0}));
    requiredLocs.emplace_back(Point2d({2,0}));
}
