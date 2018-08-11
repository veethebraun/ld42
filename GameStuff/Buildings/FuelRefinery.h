//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_FUELREFINERY_H
#define LD42_FUELREFINERY_H


#include "../Building.h"

class FuelRefinery : public Building {
public:
    FuelRefinery(int x, int y);

    void resourceGeneration(Resources* resources) override;
protected:
    std::valarray<int> getCost() override;

};


#endif //LD42_FUELREFINERY_H
