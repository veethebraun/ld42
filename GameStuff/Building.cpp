//
// Created by vbrau on 8/10/2018.
//

#include "Building.h"

//std::valarray<int> Building::getCost() {
//    return {0,0,0,0,0};
//}

bool Building::canBuild(Resources *resources) {
    std::valarray<int> diff = resources->getResources() + this->getCost();
    return diff.min() >= 0;
}

void Building::onBuild(Resources *resources) {
    resources->addResources(this->getCost());
}

bool Building::isLocRequired(Point2d loc) {
    for (const auto &item : requiredLocs) {
        if (item == loc)
            return true;
    }
    return false;
}

void Building::dropLevel(Resources *resources) {
    x += 1;

    bool start = destroyed;

    for (const auto &loc : requiredLocs) {
        if (this->getX() + loc[0] >= GRID_ROWS) {
            destroyed = true;
        }
    }

    if (start != destroyed && destroyed)
        onDestroy(resources);
}

Point2d Building::getXY() {
    return Point2d({x,y});
}

bool Building::isOnBoard(int max_x, int max_y) {
    for (const auto &loc : locs) {
        if (isLocRequired(loc)) {
            if (x < max_x && y < max_y)
                return true;
        }
    }
    return false;
}

const std::vector<Point2d> &Building::getLocs() const {
    return locs;
}

bool Building::isDestroyed() const {
    return destroyed;
}
