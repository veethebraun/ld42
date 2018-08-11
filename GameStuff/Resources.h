//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_RESOURCES_H
#define LD42_RESOURCES_H

#include <valarray>

class Resources {
public:
    Resources();

    int getPower() const;

    int getRawMaterial() const;
    int getRawMaterialStorage() const;

    int getSteel() const;
    int getSteelStorage() const;

    int getFuel() const;
    int getFuelStorage() const;

    int getLifeSupport() const;

    void addResources(std::valarray<int> inResources);

    void addStorage(std::valarray<int> inStorage);

    void resetResources();

private:
    std::valarray<int> resources;
    std::valarray<int> storage;
public:
    const std::valarray<int> &getStorage() const;

    const std::valarray<int> &getResources() const;

};


#endif //LD42_RESOURCES_H
