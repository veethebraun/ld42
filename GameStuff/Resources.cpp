//
// Created by vbrau on 8/11/2018.
//

#include "Resources.h"

Resources::Resources() : resources({0,0,0,0,0}), storage({0,0,0,0,0}) {

}

int Resources::getPower() const {
    return resources[0];
}

int Resources::getRawMaterial() const {
    return resources[1];
}

int Resources::getSteel() const {
    return resources[2];
}

int Resources::getFuel() const {
    return resources[3];
}

int Resources::getLifeSupport() const {
    return resources[4];
}

void Resources::addResources(std::valarray<int> inResources) {
    resources += inResources;
    for (int i=1;i<resources.size() - 1; i++)
    {
        resources[i] = std::min(resources[i], storage[i]);
    }
}

const std::valarray<int> &Resources::getResources() const {
    return resources;
}

const std::valarray<int> &Resources::getStorage() const {
    return storage;
}

void Resources::addStorage(std::valarray<int> inStorage) {
    storage += inStorage;
}

void Resources::resetResources() {
    resources = {0,0,0,0,0};
}

int Resources::getRawMaterialStorage() const {
    return storage[1];
}

int Resources::getSteelStorage() const {
    return storage[2];
}

int Resources::getFuelStorage() const {
    return storage[3];
}

