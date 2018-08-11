//
// Created by vbrau on 8/11/2018.
//

#include "WindBuilding.h"

std::valarray<int> WindBuilding::getCost() {
    return {10, 0, -4, 0, 0};
}

WindBuilding::WindBuilding(int x, int y) : Building(x, y) {

    locs.emplace_back(Point2d({0,0}));
    requiredLocs.emplace_back(Point2d({0,0}));
    locs.emplace_back(Point2d({0,1}));
    requiredLocs.emplace_back(Point2d({0,1}));
    locs.emplace_back(Point2d({1,0}));
    requiredLocs.emplace_back(Point2d({1,0}));
    locs.emplace_back(Point2d({1,1}));
    requiredLocs.emplace_back(Point2d({1,1}));
    locs.emplace_back(Point2d({0,2}));
    requiredLocs.emplace_back(Point2d({0,2}));
}

void WindBuilding::onDestroy(Resources *resources) {
    destroyed = true;

}
