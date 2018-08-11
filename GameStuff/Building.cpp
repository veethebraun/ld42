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

const std::vector<Vector2d<int>> &Building::getLocs() const {
    return locs;
}

void Building::setLocs(const std::vector<Vector2d<int>> &locs) {
    Building::locs = locs;
}

bool Building::isLocRequired(Vector2d<int> loc) {
    return requiredLocs[loc];
}
